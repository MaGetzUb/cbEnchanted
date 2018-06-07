#include "precomp.h"
#include "cbenchanted.h"
#include "soundinterface.h"
#include "variablestack.h"
#include "animinterface.h"
#include "debug.h"
#include "errorsystem.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_video.h>


#ifndef CBE_LIB
AnimInterface::AnimInterface() {
	cbeInstance = CBEnchanted::instance();
	
}

AnimInterface::~AnimInterface() {

}

bool AnimInterface::initializeAnimInterface() {
	return al_init_video_addon();
}

void AnimInterface::commandStopAnimation(void) {
	if(video) al_close_video(video);
	video = nullptr;
}

void AnimInterface::commandDrawAnimation(void) {
	al_draw_scaled_bitmap(currentFrame, 0, 0, videoWidth, videoHeight, 0, 0, scaleX, scaleY, 0);
}

void AnimInterface::functionPlayAnimation(void) {
	ISString input = cbeInstance->popValue().toString();
	if(input.empty()) {
		cbeInstance->errors->createError("Cannot play animation! Given path is empty!");
	}

	if(video) al_close_video(video);

	std::string path = input.getStdString();
	video = al_open_video(path.c_str());
	if(video == nullptr) {
		cbeInstance->pushValue((int)0);
		return;
	}
	
	al_register_event_source(cbeInstance->getEventQueue(), al_get_video_event_source(video));
	al_start_video(video, cbeInstance->soundInterface->getMixer());
}

void AnimInterface::functionAnimationWidth(void) {
	if(video) {
		cbeInstance->pushValue((int)((float)videoWidth * scaleX));
		return;
	}
	cbeInstance->errors->createFatalError("There isn't video playing!");
	cbeInstance->pushValue((int)0);
}

void AnimInterface::functionAnimationHeight(void) {
	if(video) {
		cbeInstance->pushValue((int)((float)videoWidth * scaleX));
		return;
	}
	cbeInstance->errors->createFatalError("There isn't video playing!");
	cbeInstance->pushValue((int)0);
}

void AnimInterface::functionAnimationPlaying(void) {
	cbeInstance->pushValue((int)(video != nullptr));
}

void AnimInterface::acquireNewFrame() {
	currentFrame = al_get_video_frame(video);
	scaleX = al_get_video_scaled_width(video);
	scaleY = al_get_video_scaled_height(video);
	videoWidth = 1.0f * al_get_bitmap_width(currentFrame);
	videoHeight = 1.0f * al_get_bitmap_height(currentFrame);
}

#endif
