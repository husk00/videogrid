#include "ofSnap.h"

ofSnap::ofSnap( float x, float y, int _id, float _letter)
{

//init var
    this->isOver = false;
    this->isSelected = false;
    this->snapos.set(x,y);
	  this->snapwidth = 120;
	  this->snapheight = 80;
	  this->id = _id;
    this->blackSnap.x = this->snapos.x;
    this->blackSnap.y = this->snapos.y;
    this->blackSnap.width = this->snapwidth;
    this->blackSnap.height = this->snapheight;
    this->bloadsnap = false;
    this->bhavesnap = false;
    this->snapImage.allocate(320,240, OF_IMAGE_COLOR);
    this->letter = _letter;
    this->page = 1;

}


void ofSnap::update(){
    video.update();
    if(bloadsnap){
    snapImage.setFromPixels(video.getPixelsRef());
    snapImage.getPixelsRef().resize(120,80);
    snapImage.saveImage("images/"+ofToString(this->page)+"/image"+ofToString(this->id)+".png");
    video.stop();
    bloadsnap = false;
    bhavesnap = true;
    }
}

void ofSnap::draw(){
        if(bhavesnap){
          loadSnap();
        } else {
            if(this->isSelected) {
                ofSetColor(255,0,0);
                ofRectRounded(this->blackSnap,10);
            } else {
                ofSetColor(0);
                ofRectRounded(this->blackSnap,10);
            }
        }
}
void ofSnap::loadSnap(){
            if(this->isSelected) {
                ofSetColor(255,0,0);
                //snapImage.loadImage("images/"+ofToString(this->page)+"/image"+ofToString(this->id)+".png");
                snapImage.draw(this->snapos.x,this->snapos.y);
            } else {
            //ofLog() << "carico la snap numero " << this->id;
            ofSetColor(255,255,255);
            snapImage.loadImage("images/"+ofToString(this->page)+"/image"+ofToString(this->id)+".png");
            snapImage.draw(this->snapos.x,this->snapos.y);
            }
}
void ofSnap::_mouseMoved(int x, int y){
    this->x = x;
    this->y = y;
    if(x > this->snapos.x && this->x < this->snapos.x+this->snapwidth && this->y > this->snapos.y && this->y < this->snapos.y+this->snapheight ){
        this->isOver = true;
    } else{
        this->isOver = false;
    }

}
void ofSnap::_mousePressed(int x, int y, int button){
    if(this->isOver){
        this->isSelected =true;
        //path = video.getMoviePath();
         //ofLog() << "is selected? " << this->isSelected << " id " << id << "path: " << this->path;
    }

}
void ofSnap::_mouseReleased(int x, int y, int button){
    if(!this->isOver){
        this->isSelected=false;
    }

}

void ofSnap::_keyPressed(int key){
    if(key == letter){
      this->isSelected = true;
      } else {
      this->isSelected = false;
      
      }
}

void ofSnap::loadImage(string p, int currentVideo){
    video.stop();
    video.close();
    video.loadMovie(p);
    video.setVolume(0);
    video.play();
    video.setFrame(ofRandom(0, video.getTotalNumFrames()));
    this->path = video.getMoviePath();
    this->id = currentVideo;
    bloadsnap = true;
    //ofAddListener(video.threadedVideoEvent, this, &ofSnap::threadedVideoEvent);

}
