all: ppmrw.c
	gcc ppmrw.c -o ppmrw

clean:
	# added "ppmrw.exe" and "ppmrw" in case the all target does not create "ppmrw.exe" but "ppmrw" or vice versa
	rm -rf ppmrw.exe ppmrw
