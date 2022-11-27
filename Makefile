debug:
	pio run -e native-debug && .pio/build/native-debug/program

native:
	pio run -e native-dev && .pio/build/native-dev/program

arduino:
	pio run -e arduino

htop:
	htop -p $(pgrep program | paste -s -d,)

up:
	touch ./dev/btn-up/press

down:
	touch ./dev/btn-down/press

left:
	touch ./dev/btn-left/press

right:
	touch ./dev/btn-right/press

select:
	touch ./dev/btn-select/press
