#include "gnss.h"
void audio_init(void);
#include <Audio.h>

#define AUDIO_VOLUME -160

AudioClass *theAudio;

void audio_init(void)
{
  /* start audio system */
  theAudio = AudioClass::getInstance();
  theAudio->begin(audio_attention_cb);

  puts("I2S DAC Initialize");
  int err = theAudio->setThroughMode(AudioClass::I2sIn, AudioClass::None, true, 160, AS_SP_DRV_MODE_LINEOUT);
  if (err != AUDIOLIB_ECODE_OK)
  {
    printf("I2S DAC initialize error\n");
    exit(1);
  }

  theAudio->setVolume(AUDIO_VOLUME);
  if (err != AUDIOLIB_ECODE_OK)
  {
    printf("Set Volume error\n");
    exit(1);
  }
}

void setup()
{
  audio_init();
  gnss_init();
}

void loop()
{
  gnss_loop();
}

static void audio_attention_cb(const ErrorAttentionParam *atprm)
{
  puts("Attention!");

  if (atprm->error_code >= AS_ATTENTION_CODE_WARNING)
  {
    exit(1);
  }
}
