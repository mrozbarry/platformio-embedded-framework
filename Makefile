debug:
	pio run -e native-debug && .pio/build/native-debug/program

native:
	pio run -e native-dev && .pio/build/native-dev/program

arduino:
	pio run -e arduino

htop:
	htop -p $(pgrep program | paste -s -d,)

up:
	touch ./dev/btn-up/press && sleep 1

down:
	touch ./dev/btn-down/press && sleep 1

left:
	touch ./dev/btn-left/press && sleep 1

right:
	touch ./dev/btn-right/press && sleep 1

select:
	touch ./dev/btn-select/press && sleep 1
