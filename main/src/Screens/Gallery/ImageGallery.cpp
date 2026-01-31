#include "ImageGallery.h"
#include "Screens/MainMenu/MainMenu.h"

ImageGallery::ImageGallery() : queue(4) {
	bg = lv_obj_create(*this);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_size(bg, 128, 128);
	lv_obj_set_style_bg_color(bg, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(bg, LV_OPA_COVER, 0);

	image = lv_img_create(bg);
	lv_obj_center(image);

	showImage();
}

void ImageGallery::showImage(){
	if(currentIndex >= ImageCount){
		currentIndex = 0;
	}

	lv_img_set_src(image, Images[currentIndex]);
}

void ImageGallery::handleInput(Input::Data& event){
	if(event.action != Input::Data::Press){
		return;
	}

	if(event.btn == Input::Alt){
		transition([](){ return std::make_unique<MainMenu>(); });
		return;
	}

	if(event.btn == Input::Up){
		currentIndex = (currentIndex + ImageCount - 1) % ImageCount;
		showImage();
		return;
	}

	if(event.btn == Input::Down || event.btn == Input::Select){
		currentIndex = (currentIndex + 1) % ImageCount;
		showImage();
	}
}

void ImageGallery::loop(){
	Event evt{};
	if(queue.get(evt, 0)){
		if(evt.facility == Facility::Input){
			auto eventData = (Input::Data*) evt.data;
			handleInput(*eventData);
		}
		free(evt.data);
	}
}

void ImageGallery::onStart(){
	Events::listen(Facility::Input, &queue);
}

void ImageGallery::onStop(){
	Events::unlisten(&queue);
}
