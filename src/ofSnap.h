#ifndef _OF_SNAP // if this class hasn't been defined, the program can define it
#define _OF_SNAP // by using this if statement you prevent the class to be called more
                 // than once which would confuse the compiler

#include "ofMain.h"
#include "ofxThreadedVideo.h"

class ofSnap {

    public:
        // methods
        void update();
        void draw();
        void _mouseMoved(int x, int y);
        void _mousePressed(int x, int y, int button);
        void _mouseReleased(int x, int y, int button);
        void _keyPressed(int key);
        void loadSnap();

       ofSnap(float x, float y, int id, float letter); // constructor - used to initialize an object, if no properties are passed
                  //               the program sets them to the default value

        //variables
        ofImage snapImage;
        ofVec2f snapos;
        int snapwidth, snapheight, id, x,y,page;
        bool isOver, isSelected, bloadsnap, bhavesnap;
        string path;
        ofRectangle blackSnap;
        ofVideoPlayer video;
        float letter;
        void threadedVideoEvent(ofxThreadedVideoEvent & event);
        void loadImage(string p,int currentVideo);


    private: // place private functions or variables declarations here

}; // dont't forget the semicolon!!

#endif
