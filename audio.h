
using namespace std;

class Audio {
private:
    int audioRate = 44100;
    int audioChannels = 2;
    int audioBuffers = 2048;

public:
    Mix_Music *theme = NULL;
    Mix_Chunk *fire = NULL;
    Mix_Chunk *run = NULL;
    Mix_Chunk *explosion = NULL;
    Mix_Chunk *dinoFire = NULL;

    void LoadAudio() {
        Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, audioBuffers);
        theme = Mix_LoadMUS("audio/theme.mp3");
        fire = Mix_LoadWAV("audio/fire.wav");
        run = Mix_LoadWAV("audio/run.wav");
        explosion = Mix_LoadWAV("audio/explosion.wav");
        dinoFire = Mix_LoadWAV("audio/dinoFire.wav");
        Mix_Volume(3, 20);
        Mix_Volume(4, 20);
    }

    void Theme() {
        Mix_PlayMusic(theme, -1);
    }

    void PlayerFire() {
        Mix_PlayChannel(0, fire, 0);
    }

    bool CheckPlayingChannel1() {
        return Mix_Playing(1);
    }
 
    void Run() {
        Mix_PlayChannel(1, run, -1);
    }

    void EndRun() {
        Mix_HaltChannel(1);
    }

    void FirewExplosion() {
        Mix_PlayChannel(2, explosion, 0);
    }

    void DinoFire() {
        Mix_PlayChannel(3, dinoFire, 0);
    }

    void HedgehogFire() {
        Mix_PlayChannel(4, dinoFire, 0);
    }

};