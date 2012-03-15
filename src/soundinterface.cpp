#include "precomp.h"
#include "soundinterface.h"
#include "cbenchanted.h"
#include "any.h"

SoundInterface::SoundInterface() : cb(static_cast <CBEnchanted *> (this)),idCounter(0) {
	
}

SoundInterface::~SoundInterface() {
	
}

void SoundInterface::commandPlaySound(void) {
	/*int32_t freg = */cb->popValue().toInt();
	float balance = cb->popValue().toFloat()/100.0;
	float volume = cb->popValue().toFloat();
	Any any = cb->popValue();
	if (any.type() == Any::Int) {//Loaded sound
		CBSound *sound = cbSounds[any.getInt()];
		if (sound->isMusic)
		{
			//sound->music->SetPitch(balance);
			sound->music->setVolume(volume);
			sound->music->play();
		}
		else
		{
			//sound->sound->SetPitch(balance);
			sound->sound->setVolume(volume);
			sound->sound->play();
		}
	}
	else {
		const string &filepath = any.toString().getRef();
		CBSound *music = new CBSound;
		music->music = new sf::Music;
		if (!music->music->openFromFile(filepath)) {
			delete music->music;
			delete music;
			cb->pushValue(int32_t(0));
		}
		//music->music->SetPitch(balance);
		music->music->setVolume(volume);
		music->isMusic = true;
		music->file = filepath;
		music->music->play();
		deleteWhenStop.insert(music);//User can't use it any more, so delete it after it stops.
		int32_t id = nextId();
		cbSounds[id] = music;
	}
}

void SoundInterface::commandSetSound(void) {
	/*int32_t freg = */cb->popValue().toInt();
	float balance = cb->popValue().toFloat() / 100.0;
	float volume = cb->popValue().toFloat();
	bool looping = cb->popValue().toInt();
	CBSound *sound = cbSounds[cb->popValue().getInt()];
	if (sound->isMusic) {
		sound->music->setLoop(looping);
		sound->music->setVolume(volume);
		//sound->music->SetPitch(balance);
	}
	else {
		sound->sound->setLoop(looping);
		sound->sound->setVolume(volume);
		//sound->sound->SetPitch(balance);
	}
}

void SoundInterface::commandStopSound(void) {
	CBSound *sound = cbSounds[cb->popValue().getInt()];
	if (sound->isMusic) {
		set<CBSound*>::iterator i = deleteWhenStop.find(sound);
		if (i != deleteWhenStop.end()) {
			deleteWhenStop.erase(i);
			cbSounds.erase(sound->id);
			delete sound->music;
			delete sound;
			return;
		}
		sound->music->stop();
	}
	else {
		sound->sound->stop();
	}
}

void SoundInterface::commandDeleteSound(void) {
	CBSound *sound = cbSounds[cb->popValue().getInt()];
	if (sound->isMusic) {
		set<CBSound*>::iterator i = deleteWhenStop.find(sound);
		if (i != deleteWhenStop.end()) {
			deleteWhenStop.erase(i);
		}
		cbSounds.erase(sound->id);
		delete sound->music;
		delete sound;
	}
	else {
		cbSounds.erase(sound->id);
		delete sound->sound;
		delete sound->soundBuffer;
		delete sound;
	}
}

void SoundInterface::functionLoadSound(void) {
	string filepath = cb->popValue().toString().getRef();
	CBSound *sound = new CBSound;
	sound->isMusic = false;
	sound->file = filepath;
	sound->soundBuffer = new sf::SoundBuffer;
	if (!sound->soundBuffer->loadFromFile(filepath)) {
		delete sound->soundBuffer;
		delete sound;
		cb->pushValue(int32_t(0));
		return;
	}
	sound->sound = new sf::Sound(*sound->soundBuffer);
	sound->sound->setLoop(false);
	int32_t id = nextId();
	sound->id = id;
	cbSounds[id] = sound;
	cb->pushValue(id);
}

void SoundInterface::functionPlaySound(void) {
	/*int32_t freg = */cb->popValue().toInt();
	float balance = cb->popValue().toFloat();
	float volume = cb->popValue().toFloat();
	Any any = cb->popValue();
	if (any.type() == Any::Int) {//Loaded sound
		int32_t id = any.getInt();
		CBSound *sound =cbSounds[id];
		if (sound->isMusic)
		{
			//sound->music->SetPitch(balance);
			sound->music->setVolume(volume);
			sound->music->play();
		}
		else
		{
			//sound->sound->SetPitch(balance);
			sound->sound->setVolume(volume);
			sound->sound->play();
		}
		cb->pushValue(id);
	}
	else {
		string filepath = any.toString().getRef();
		CBSound *music = new CBSound;
		music->music = new sf::Music;
		if (!music->music->openFromFile(filepath)) {
			delete music->music;
			delete music;
			cb->pushValue(int32_t(0));
		}
		//music->music->SetPitch(balance);
		music->music->setVolume(volume);
		music->isMusic = true;
		music->file = filepath;
		music->music->play();
		int32_t id = nextId();
		music->id = id;
		cbSounds[id] = music;
		cb->pushValue(id);
	}

}

void SoundInterface::functionSoundPlaying(void) {
	CBSound *sound = cbSounds[cb->popValue().getInt()];
	if (sound->isMusic) {
		cb->pushValue(int32_t(sound->music->getStatus() == sf::SoundStream::Playing));
	}
	else {
		cb->pushValue(int32_t(sound->sound->getStatus() == sf::Sound::Playing));
	}
}

void SoundInterface::updateAudio(void) {
	for (set<CBSound*>::iterator i = deleteWhenStop.begin(); i != deleteWhenStop.end();) {
		CBSound *sound = *i;
		if (sound->music->getStatus() == sf::SoundStream::Stopped) {
			delete sound->music;
			delete sound;
			set<CBSound*>::iterator dt = i;i++;
			deleteWhenStop.erase(dt);
		}
		else {
			i++;
		}
	}
}

//Deletes all sounds.
void SoundInterface::cleanupSoundInterface() {
	for (map<int32_t, CBSound*>::iterator i = cbSounds.begin(); i != cbSounds.end(); i++) {
		delete i->second;
	}
}

int32_t SoundInterface::nextId() {
	return ++idCounter;
}
