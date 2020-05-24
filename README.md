# mdc-decoder
Given a raw wav file decode any mdc1200 UNIT TAGS
This project relies on the great work done by Matthew Kaufman and his
https://github.com/atmatthewat/mdc-encode-decode project

Use is pretty simple, give a raw wave file decode and write to STDOUT 
all of the decoded mdc1200 tags.

Currently the processes expects a headerless 16bit signed 16000 bitrate wav file.

A compatible file can be created with the command:
`sox <INFILE> -b 16 -e signed-integer -r16000 -t raw <OUTFILE>`

The output is: number of frames, op code, argument, unit id
Example:
```
~/mdc-decode$ ./mdc_decoder test_data/emsresp_20200521-140602.raw
01 01 00 4651
01 01 80 4651
01 01 00 4651
01 01 80 4651
```
