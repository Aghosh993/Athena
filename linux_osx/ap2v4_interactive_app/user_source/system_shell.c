#include "system_shell.h"

#include "serial_comms_highlevel.h"

extern serialport console_serial_port;

/*
  BSD 3-Clause License

  Copyright (c) 2017, Abhimanyu Ghosh
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

static volatile command ctable[CMD_TABLE_MAXLEN];
static volatile int ctable_depth;

void show_help(int argc, char** argv)
{
	int i = 0;
	printf("\r\nAvailable commands:\r\n");
	for(i = 0; i<ctable_depth; ++i)
	{
		printf("%s\r\n", ctable[i].cmdname);
	}
}

#if defined SYSTEM_SHELL_BAREMETAL
	ssize_t getline(char **lineptr, size_t *n, FILE *stream)
	{
		/*
			If we have a non-allocated buffer, we allocate a chunk
		 */
		if(*lineptr == NULL)
		{
			*lineptr = (char *)malloc(CMD_BUFSIZE_INIT * sizeof(char));
			*n = (size_t)CMD_BUFSIZE_INIT;
		}
		if(stream == stdin)
		{
			size_t i = 0;
			char c = ' ';
			*n = (size_t)CMD_BUFSIZE_INIT;

			char *read_pos = *lineptr;

			/*
				While the user hasn't yet provided a CR (Carriage Return) or 
				NL (Newline), we keep reading, expanding the buffer as required:
			 */
			while(c != '\r' && c != '\n')
			{
				if(i+1 < *n) // Must reserve 1 byte for null ending...
				{
					c = (char)getchar();
					*read_pos = c;
					++read_pos;
				}
				else // If we're out of space, reallocate double space and read bytes
				{
					*lineptr = realloc(*lineptr, *n * 2);
					if(lineptr == NULL)
					{
						errno = ENOMEM;
						return -1;
					}
					*n *= 2;
					c = (char)getchar();
					*read_pos = c;
					++read_pos;
				}
				#ifdef GETLINE_ECHO_ENABLE
					printf("%c", c);
				#endif
				++i;
			}
			/*
				Add a null char and reallocate to fit the buffer to required size:
			 */
			*read_pos = '\0';
			++i;
			
			// if(*lineptr != NULL && i > 1)
			// {
			// 	printf("\r\nTrying to realloc\r\n");
			// 	char *tmp = realloc(*lineptr, i);
			// 	if(tmp != NULL)
			// 	{
			// 		*lineptr = tmp;
			// 	}
			// }
			// printf("\r\nDone..\r\n");
			*n = i;

			/*
				Return how many bytes we've actually read:
			 */
			return (ssize_t)i;
		}
	}
#endif

void clear_buffer(void)
{
	printf("\e");
	printf("[2J");
	printf("\e");
	printf("[H");
}

static void strip_newline(char *s)
{
	int i = 0;
	int len = strlen(s);
	for(i=0; i<strlen(s); ++i)
	{
		if(s[i] == '\r')
		{
			s[i] = '\0';
		}
	}
}

void setup_system_shell(void)
{
	/*
	Initialize SCI1 at 460800 baud, 8n1:
	*/
	serialport_init(&console_serial_port, PORT1);
	
	/*
	Disable buffered I/O for UART comms:
	*/
	setvbuf(stdin,NULL,_IONBF,0);   // Sets stdin in unbuffered mode (normal for usart com)
	setvbuf(stdout,NULL,_IONBF,0);  // Sets stdin in unbuffered mode (normal for usart com)

	clear_buffer();
	printf("Welcome to YaSH (Yet another SHell)!!\r\n");
	printf("(c) Abhimanyu Ghosh, 2017\r\n");
	printf("\r\n __     __    _____ _    _ \r\n");
	printf(" \\ \\   / /   / ____| |  | |\r\n");
	printf("  \\ \\_/ /_ _| (___ | |__| |\r\n");
	printf("   \\   / _` |\\___ \\|  __  |\r\n");
	printf("    | | (_| |____) | |  | |\r\n");
	printf("    |_|\\__,_|_____/|_|  |_|\r\n");
	printf("\r\n");

	int i = 0;
	int j = 0;
	for(i=0; i<CMD_TABLE_MAXLEN; ++i)
	{
		ctable[i].cmdname = (char *)malloc(CMD_NAME_MAXLEN*sizeof(char));
		for(j=0; j<CMD_NAME_MAXLEN; ++j)
		{
			ctable[i].cmdname[j] = ' ';
		}
	}
	ctable_depth = 0;

	install_cmd("help", show_help);
}

int run_cmd(char* cmd, int arglen, char* args)
{
	int i = 0;
	for(i=0; i<ctable_depth; ++i)
	{
		int cmp = strncmp(ctable[i].cmdname, cmd, CMD_NAME_MAXLEN);
		if(cmp == 0)
		{
			ctable[i].app(arglen, args);
			return 0;
		}
	}
	return -1;
}

int install_cmd(char *cmd_name, void (*prog)(int, char**))
{
	if(ctable_depth < CMD_TABLE_MAXLEN)
	{
		ctable[ctable_depth].app = prog;
		strcpy(ctable[ctable_depth].cmdname, cmd_name);
		++ctable_depth;
		return 0;
	}
	return -1;
}

void shell_run(void)
{
	char *c = (char *)malloc(CMD_BUFSIZE_INIT*sizeof(char));
	if(c == NULL)
	{
		printf("ALLOC ERROR\r\n");
	}
	size_t readbuflen = (size_t)CMD_BUFSIZE_INIT;
	printf("user@ap2v4-rm48-shell:");
	
	ssize_t res = getline(&c, &readbuflen, stdin);
	printf("\r\n");
	char *cmd = NULL;

	if(res > 0)
	{
		cmd = strtok(c, (const char *)" ");
		// }

		char **args = NULL;
		int iter = 0;
		char *arg_token = NULL;

		if(cmd != NULL)
		{
			strip_newline(cmd);

			args = (char **)malloc((CMD_ARGSIZE_INIT)*sizeof(char *));
			if(args == NULL)
			{
				printf("ERROR allocating arg buf!!\r\n");
			}

			arg_token = strtok(NULL, (const char *)" ");
			if(arg_token != NULL)
			{
				args[iter] = arg_token;
				++iter;
			}

			while(arg_token != NULL)
			{
				arg_token = strtok(NULL, (const char *)" ");
				if(arg_token != NULL)
				{
					if(iter < CMD_ARGSIZE_INIT)
					{
						args[iter] = arg_token;
						strip_newline(args[iter]);
						++iter;
					}
					else
					{
						args = realloc(args, CMD_ARGSIZE_INIT*2);
						args[iter] = arg_token;
						strip_newline(args[iter]);
						++iter;
					}
				}
			}
			// args = realloc(args, iter);
			printf("\r\n");
			if(run_cmd(cmd, iter, args) < 0)
			{
				printf("\r\nERROR!!\r\n");
			}
		}
		// if(c != NULL)
		// {
		// 	free(c);
		// }
		// if(args != NULL)
		// {
		// 	free(args);
		// }
	}
}