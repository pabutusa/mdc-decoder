#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "mdc_decode.h"

void mdcCallBack(int numFrames, unsigned char op, unsigned char arg, unsigned short unitID,\
                  unsigned char extra0, unsigned char extra1, unsigned char extra2, \
                  unsigned char extra3, void *context){
    char out_buffer[80];
    snprintf(out_buffer, sizeof(out_buffer), "%02d %02x %02x %04x", numFrames, op, arg, unitID);
    fprintf(stdout, "%s\n", out_buffer);
}


static void read_input(char *pathname) {
    // General
    int sample_rate = 16000;
    mdc_sample_t *buffer;
    int i;
    int error;
    int overlap = 0;
    static int integer_only = true;
    int fd = 0;
    unsigned char *sp;
    int len;

    // MDC1200
    mdc_decoder_t *m_decoder;
    unsigned char op, arg, extra0, extra1, extra2, extra3;
    unsigned short unitID;
    m_decoder = mdc_decoder_new(sample_rate);
    mdc_decoder_set_callback(m_decoder, mdcCallBack, 0);
    int m_result;


    // Loop over finite file if reading file
    FILE *fp = fopen(pathname, "r");
    if (!fp) {
      fprintf(stderr, "File open failed\n");
      exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);     // seek to end of file
    len = ftell(fp);            // get current file pointer
    fseek(fp, 0, SEEK_SET);     // seek back to beginning of file

    buffer=malloc(len);

    while (fread(buffer, len, 1, fp)) {
      m_result = mdc_decoder_process_samples(m_decoder, buffer, len/2);
      if (m_result == -1) {
        fprintf(stderr, "MDC Decoder Error\n");
        exit(1);
      }
    }
    free(buffer);
    fclose(fp);
}

int main(int argc, char *argv[]) {

    char *pathname;

    if (argc == 2) {
      pathname = malloc(strlen(argv[1]) + 1);
      strcpy(pathname, argv[1]);
    } else {
      fprintf(stderr, "Invalid input\n");
      exit(EXIT_FAILURE);
    }

    read_input(pathname);

    exit(0);
}
