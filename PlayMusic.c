// libraries
#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

// main function
int main(int argc, char *argv[])
{
    // check arguments
    if (argc != 2) {
        printf("Usage: %s file.wav\n", argv[0]);
        exit(1);
    }

    // open WAV file
    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", argv[1]);
        exit(1);
    }

    // read WAV header
    char riff[4];
    unsigned int size;
    char wave[4];
    char fmt[4];
    unsigned int fmt_size;
    unsigned short format;
    unsigned short channels;
    unsigned int sample_rate;
    unsigned int byte_rate;
    unsigned short block_align;
    unsigned short bits_per_sample;
    char data[4];
    unsigned int data_size;

    fread(riff, 1, 4, fp); // "RIFF"
    fread(&size, 4, 1, fp); // file size
    fread(wave, 1, 4, fp); // "WAVE"
    fread(fmt, 1, 4, fp); // "fmt "
    fread(&fmt_size, 4, 1, fp); // fmt chunk size
    fread(&format, 2, 1, fp); // audio format
    fread(&channels, 2, 1, fp); // number of channels
    fread(&sample_rate, 4, 1, fp); // sample rate
    fread(&byte_rate, 4, 1, fp); // byte rate
    fread(&block_align, 2, 1, fp); // block align
    fread(&bits_per_sample, 2, 1, fp); // bits per sample
    fread(data, 1, 4, fp); // "data"
    fread(&data_size, 4, 1, fp); // data chunk size

    // print WAV info
    printf("File: %s\n", argv[1]);
    printf("RIFF: %c%c%c%c\n", riff[0], riff[1], riff[2], riff[3]);
    printf("Size: %u\n", size);
    printf("WAVE: %c%c%c%c\n", wave[0], wave[1], wave[2], wave[3]);
    printf("fmt : %c%c%c%c\n", fmt[0], fmt[1], fmt[2], fmt[3]);
    printf("fmt size: %u\n", fmt_size);
    printf("Format: %u\n", format);
    printf("Channels: %u\n", channels);
    printf("Sample rate: %u\n", sample_rate);
    printf("Byte rate: %u\n", byte_rate);
    printf("Block align: %u\n", block_align);
    printf("Bits per sample: %u\n", bits_per_sample);
    printf("data: %c%c%c%c\n", data[0], data[1], data[2], data[3]);
    printf("data size: %u\n", data_size);

    // check WAV format
    if (format != 1) {
        printf("Unsupported audio format: %u\n", format);
        exit(1);
    }
    
     if (bits_per_sample != 8 && bits_per_sample != 16) {
        printf("Unsupported bits per sample: %u\n", bits_per_sample);
        exit(1);
     }

     if (channels != 1 && channels != 2) {
        printf("Unsupported number of channels: %u\n", channels);
        exit(1);
     }

     // allocate buffer for audio data
     int buffer_size = data_size > 4096 ? 4096 : data_size;
     char *buffer = malloc(buffer_size);

     if (buffer == NULL) {
        printf("Failed to allocate buffer\n");
        exit(1);
     }

     // open alsa device for playback
     snd_pcm_t *handle;
     snd_pcm_hw_params_t *params;
     snd_pcm_uframes_t frames;

     int rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);

     if (rc < 0) {
        printf("Failed to open device: %s\n", snd_strerror(rc));
        exit(1);
     }

     // set hardware parameters
     snd_pcm_hw_params_alloca(&params);
     snd_pcm_hw_params_any(handle, params);
     snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
     snd_pcm_hw_params_set_format(handle, params, bits_per_sample == 8 ? SND_PCM_FORMAT_U8 : SND_PCM_FORMAT_S16_LE);
     snd_pcm_hw_params_set_channels(handle, params, channels);
     snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, NULL);
     frames = 32;
     snd_pcm_hw_params_set_period_size_near(handle, params, &frames, NULL);
     rc = snd_pcm_hw_params(handle, params);

     if (rc < 0) {
        printf("Failed to set hardware parameters: %s\n", snd_strerror(rc));
        exit(1);
     }

     // get period size
     snd_pcm_hw_params_get_period_size(params, &frames, NULL);

     // play audio data
     while (data_size > 0) {
        // read data from file
        int size = buffer_size > data_size ? data_size : buffer_size;
        int len = fread(buffer, 1, size, fp);

        if (len != size) {
            printf("Failed to read data from file\n");
            break;
        }

        // write data to device
        rc = snd_pcm_writei(handle, buffer, frames);

        if (rc == -EPIPE) {
            // underrun occurred
            printf("Underrun occurred\n");
            snd_pcm_prepare(handle);
        } else if (rc < 0) {
            printf("Failed to write data to device: %s\n", snd_strerror(rc));
            break;
        } else if (rc != (int)frames) {
            printf("Short write: %d\n", rc);
        }

        // update data size
        data_size -= size;
    }

    // free buffer
    free(buffer);

    // close file
    fclose(fp);

    // close device
    snd_pcm_drain(handle);
    snd_pcm_close(handle);

    return 0;
}

