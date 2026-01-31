#ifndef CLOCKSTAR_FIRMWARE_IMAGEGALLERY_H
#define CLOCKSTAR_FIRMWARE_IMAGEGALLERY_H

#include "Filepaths.hpp"
#include "LV_Interface/LVScreen.h"
#include "Devices/Input.h"
#include "Util/Events.h"

class ImageGallery : public LVScreen {
public:
	ImageGallery();

private:
	static constexpr const char* Images[] = {
			File::Intro::Artemis,
			File::Intro::CircuitMess,
			File::Intro::GeekClub,
			File::Intro::Space,
			File::Intro::OrangeBackground,
			File::Intro::BlackBackground
	};
	static constexpr size_t ImageCount = sizeof(Images) / sizeof(Images[0]);

	lv_obj_t* bg = nullptr;
	lv_obj_t* image = nullptr;
	size_t currentIndex = 0;

	EventQueue queue;

	void showImage();
	void handleInput(Input::Data& event);

	void onStart() override;
	void onStop() override;
	void loop() override;
};

#endif //CLOCKSTAR_FIRMWARE_IMAGEGALLERY_H
