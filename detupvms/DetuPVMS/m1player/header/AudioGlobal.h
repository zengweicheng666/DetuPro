#ifndef _AUDIO_GLOBAL_H
#define _AUDIO_GLOBAL_H

//copy from ijkplayer, modify for m1

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef int8_t      Sint8;
typedef uint8_t     Uint8;
typedef int16_t     Sint16;
typedef uint16_t    Uint16;
typedef int32_t     Sint32;
typedef uint32_t    Uint32;
typedef int64_t     Sint64;
typedef uint64_t    Uint64;
typedef uint16_t	SDL_AudioFormat;

#define SDL_AUDIO_MASK_BITSIZE       (0xFF)
#define SDL_AUDIO_MASK_DATATYPE      (1<<8)
#define SDL_AUDIO_MASK_ENDIAN        (1<<12)
#define SDL_AUDIO_MASK_SIGNED        (1<<15)
#define SDL_AUDIO_BITSIZE(x)         (x & SDL_AUDIO_MASK_BITSIZE)
#define SDL_AUDIO_ISFLOAT(x)         (x & SDL_AUDIO_MASK_DATATYPE)
#define SDL_AUDIO_ISBIGENDIAN(x)     (x & SDL_AUDIO_MASK_ENDIAN)
#define SDL_AUDIO_ISSIGNED(x)        (x & SDL_AUDIO_MASK_SIGNED)
#define SDL_AUDIO_ISINT(x)           (!SDL_AUDIO_ISFLOAT(x))
#define SDL_AUDIO_ISLITTLEENDIAN(x)  (!SDL_AUDIO_ISBIGENDIAN(x))
#define SDL_AUDIO_ISUNSIGNED(x)      (!SDL_AUDIO_ISSIGNED(x))

#define AUDIO_INVALID   0x0000
#define AUDIO_U8        0x0008  /**< Unsigned 8-bit samples */
#define AUDIO_S8        0x8008  /**< Signed 8-bit samples */
#define AUDIO_U16LSB    0x0010  /**< Unsigned 16-bit samples */
#define AUDIO_S16LSB    0x8010  /**< Signed 16-bit samples */
#define AUDIO_U16MSB    0x1010  /**< As above, but big-endian byte order */
#define AUDIO_S16MSB    0x9010  /**< As above, but big-endian byte order */
#define AUDIO_U16       AUDIO_U16LSB
#define AUDIO_S16       AUDIO_S16LSB

#define AUDIO_S32LSB    0x8020  /**< 32-bit integer samples */
#define AUDIO_S32MSB    0x9020  /**< As above, but big-endian byte order */
#define AUDIO_S32       AUDIO_S32LSB

#define AUDIO_F32LSB    0x8120  /**< 32-bit floating point samples */
#define AUDIO_F32MSB    0x9120  /**< As above, but big-endian byte order */
#define AUDIO_F32       AUDIO_F32LSB

#define AUDIO_U16SYS    AUDIO_U16LSB
#define AUDIO_S16SYS    AUDIO_S16LSB
#define AUDIO_S32SYS    AUDIO_S32LSB
#define AUDIO_F32SYS    AUDIO_F32LSB

#define SDL_MIX_MAXVOLUME (128)

#define SDL_AUDIO_MAX_CALLBACKS_PER_SEC (30)
#define SDL_AUDIO_MIN_BUFFER_SIZE 512

typedef void(*SDL_AudioCallback) (void *userdata, Uint8 * stream, int len);

typedef struct SDL_AudioSpec
{
	int freq;                   /**< DSP frequency -- samples per second */
	SDL_AudioFormat format;     /**< Audio data format */
	Uint8 channels;             /**< Number of channels: 1 mono, 2 stereo */
	Uint8 silence;              /**< Audio buffer silence value (calculated) */
	Uint16 samples;             /**< Audio buffer size in samples (power of 2) */
	Uint16 padding;             /**< NOT USED. Necessary for some compile environments */
	Uint32 size;                /**< Audio buffer size in bytes (calculated) */
	SDL_AudioCallback callback;
	void *userdata;
} SDL_AudioSpec;

void SDL_CalculateAudioSpec(SDL_AudioSpec * spec);

void SDL_MixAudio(Uint8*       dst,
				  const Uint8* src,
				  Uint32       len,
				  int          volume,
				  SDL_AudioSpec * spec);

#endif
