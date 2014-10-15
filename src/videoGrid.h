#ifndef VIDEOGRID_H
#define VIDEOGRID_H

#include "ofMain.h"
#include "ofSnap.h"
#include "textButton.h"
#include "ofxXmlSettings.h"
#include "Utils.h"
class videoGrid {

    public:
        // methods
        void update();
        void draw();
        void getContents();
        void mouseMoved(int x, int y);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void keyPressed(int key);
		    void keyReleased(int key);

        //void threadedVideoEvent(ofxThreadedVideoEvent & event);
		//void mouseDragged(int x, int y, int button);
        videoGrid(int rows, int columns, float _x, float _y); // constructor - used to initialize an object, if no properties are passed
                  //               the program sets them to the default value

        //variables
        int rows, columns, lastcell[10], until, currentVideo,pages, currentPage, nVideoToLoad;
        float x,y, posx, posy, originx, originy;
        bool isOver, isSelected, bhavevideo, alreadyLoaded;
        ofRectangle fondo, fondoTop;
        int letters[26];
        string p;
        vector <int> pagesMemory;


    private: // place private functions or variables declarations here
        ofSnap** mySnap;
        int nSnap;

                //button
        void setStatus(string newStatus);
        void convertWindowsToUnixPath(string & path);
        ofTrueTypeFont font;
        ofTrueTypeFont titleFont;
        ofTrueTypeFont secondFont;
        ofxXmlSettings XML;
        textButton  button,page[10];
        vector < textButton > buttons;
        vector<ofFile> files;
        string status;
        string defaultLoc, appToRoot, result;
        float statusSetTime;
        float statusEnergy;
}; // dont't forget the semicolon!!

#endif
