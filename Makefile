debug:
	pio run -e native-debug && .pio/build/native-debug/program

native:
	pio run -e native-dev && .pio/build/native-dev/program

arduino:
	pio run -e arduino
