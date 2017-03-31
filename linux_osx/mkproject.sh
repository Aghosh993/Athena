#!/bin/bash
if [ $# -eq 0 ]
	then
		echo "Usage: ./mkproject.sh PROJECT_NAME [PLATFORM]"
		echo "Example: ./mkproject.sh foo F3 --> Make an F3 Discovery project named foo."
		echo "Available platforms:"
		echo "f3: STM32 F3 Discovery"
		echo "f4: STM32 F4 Discovery"
		echo "tm4c: Tiva TM4C Launchpad with TM4C123Gx"
		echo "ap2v4: Hercules Autopilot 2.4 project with RM48x MCU"
		echo "f3_stdperiph: STM32 F3 Discovery project using the legacy Standard Peripheral Library from STMicroelectronics [NOT TESTED YET]"
		echo "f4_stdperiph: STM32 F3 Discovery project using the legacy Standard Peripheral Library from STMicroelectronics [NOT TESTED YET]"
		exit 0
fi

PROJ_NAME=$1
PROJ_PLATFORM=$2

if [ "$2" = "F3" ] || [ "$2" = "f3" ]; then
	echo "Creating F3 Discovery project..."
	BASE_PROJ_NAME=f3discovery_basic_app
fi
if [ "$2" = "F3_STDPERIPH" ] || [ "$2" = "f3_stdperiph" ]; then
	echo "Creating F3 Discovery Standard Peripheral Library project..."
	BASE_PROJ_NAME=f3discovery_s tdperiph_basic_app
fi
if [ "$2" = "F4" ] || [ "$2" = "f4" ]; then
	echo "Creating F4 Discovery project..."
	BASE_PROJ_NAME=f4discovery_basic_app
fi
if [ "$2" = "F4_STDPERIPH" ] || [ "$2" = "f4_stdperiph" ]; then
	echo "Creating F4 Discovery Standard Peripheral Library project..."
	BASE_PROJ_NAME=f4discovery_stdperiph_basic_app
fi
if [ "$2" = "tm4c" ] || [ "$2" = "TM4C" ]; then
	echo "Creating TM4C Tiva Launchpad project..."
	BASE_PROJ_NAME=tm4c_launchpad_basic_app
fi
if [ "$2" = "ap2v4" ] || [ "$2" = "AP2V4" ]; then
	echo "Creating an RM48 Autopilot 2.4 project..."
	BASE_PROJ_NAME=ap2v4_basic_app
fi

if [ "$2" = "tms570" ] || [ "$2" = "TMS570" ]; then
	echo "Creating a TMS570 Launchpad project..."
	BASE_PROJ_NAME=tms570_hercules_basic_app
fi

if [ -v $BASE_PROJ_NAME ]; then
	echo "ERROR: No valid target selected!!"
	exit 0
fi

PROJ_BASE_NAME=`basename $PROJ_NAME`
ATHENA_RELPATH=`realpath --relative-to=$PROJ_NAME ..`

echo "Creating project with name:"
echo $PROJ_BASE_NAME
echo "Relative path:"
echo $ATHENA_RELPATH

cp -r $BASE_PROJ_NAME $PROJ_NAME
mv $PROJ_NAME/$BASE_PROJ_NAME.c $PROJ_NAME/$PROJ_BASE_NAME.c
echo $PROJ_BASE_NAME > $PROJ_NAME/proj_name
sed -i "s/$BASE_PROJ_NAME/$PROJ_BASE_NAME/g" $PROJ_NAME/runme*.gdb
sed -i "s/$BASE_PROJ_NAME/$PROJ_BASE_NAME/g" $PROJ_NAME/Makefile
sed -i "s|athroot|$ATHENA_RELPATH|g" $PROJ_NAME/Makefile
