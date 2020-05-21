
mdc_decoder:	mdc_decoder.c mdc_decode.o
		cc -g -o mdc_decoder mdc_decoder.c mdc_decode.o

mdc_decode.o:	mdc_decode.c mdc_decode.h mdc_common.c
		cc -g -c mdc_decode.c

clean:
	rm -f mdc_decode.o mdc_decoder
