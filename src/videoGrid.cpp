#include "videoGrid.h"

videoGrid::videoGrid(int _rows, int _columns, float _x, float _y)
{

//init var
    currentVideo = 1;
    nVideoToLoad = 0;
    for(int i=0;i<10;i++){
    lastcell[i] = 0;
    }
    currentPage = 1;
    pages = 1;
    alreadyLoaded = false;
    for(int i=0; i< 26;i++){
      letters[i] = 97+i;
    }
    rows = _rows;
    columns = _columns;
    x = _x;
    y = _y;
    bhavevideo = false;
    int index = 0;
    originx = x + 10;
    originy = y + 10;
    fondo.x = x;
    fondo.y = y;
    fondo.width = (columns*120) + (5*columns) + 20;
    fondo.height = 10 + (rows*80) + (10*rows);
    fondoTop.x = x;
    fondoTop.y = y-70;
    fondoTop.width = (columns*120) + (5*columns) + 20;
    fondoTop.height = 110;
    nSnap = columns*rows;
    mySnap = new ofSnap*[nSnap];
    for (int i = 0; i < columns; i++){
             for (int j = 0; j < rows; j++){
    posx = originx+(120*i)+(i*5);
    posy = originy+(80*j)+(j*5);
    mySnap[index] = new ofSnap(posx, posy, index, letters[index]);
    index++;
        }
    }

     // button
    font.loadFont("fonts/Inconsolata.otf", 9, true,false,false,0.3,90);
    titleFont.loadFont("fonts/Inconsolata.otf", 28, true,false,false,0.3,90);
    secondFont.loadFont("fonts/Inconsolata.otf", 11, true,false,false,0.3,90);
    button.font = &font;
    button.secondFont = &secondFont;
    button.prefix = "Directory: ";
	  button.topLeftAnchor.set(x+12, y-50); //set top button position - others are set relative to this.
    button.setText("open directory");
    button.bDrawLong = false;
    buttons.push_back(button);
    for(int i=0;i<10;i++){
      page[i].font = &secondFont;
      page[i].setText(ofToString(i+1));
      page[i].bDrawLong = false;
	    page[i].topLeftAnchor.set(x+12+(i*25),y-12); //set top button position - others are set relative to this.
      page[i].bSelected = false;
      buttons.push_back(page[i]);
      }
      buttons[1].bSelected = true;
       
    for (int i = 0; i < buttons.size(); i++){
        buttons[i].calculateRect();
    }

    XML.loadFile("settings/projectGeneratorSettings.xml");
    appToRoot = XML.getValue("appToRoot", "../../../../");
    defaultLoc = XML.getValue("defaultNewProjectLocation", "apps/myApps");
}


void videoGrid::update(){
    for (int i = 0; i < nSnap; i++){
        mySnap[i]->update();
            }
    for (int i = 0; i < buttons.size(); i++){
        buttons[i].calculateRect();
        buttons[i].checkMouseOver(ofPoint(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY));
    }


}

void videoGrid::draw(){
    ofSetColor(0, 0, 0);
    ofRect(fondoTop);
    ofSetColor(30, 60, 190);
    ofRectRounded( fondo, 10 );


    for (int i = 0; i < nSnap; i++){
        ofPushStyle();
        mySnap[i]->draw();
        ofPopStyle();

    }
    for (int i = 0; i < buttons.size(); i++){
      if(i == pages) buttons[i].bSelected = true;
      else buttons[i].bSelected = false;
			buttons[i].draw();
		}
    
}


void videoGrid::setStatus(string newStatus){
    statusEnergy = 1;
    status = newStatus;
    statusSetTime = ofGetElapsedTimef();
}

void convertWindowsToUnixPath(string & path){
    for (int i = 0; i < path.size(); i++){
        if (path[i] == '\\') path[i] = '/';
    }
}

void videoGrid::mouseMoved(int x, int y){
   for (int i = 0; i < nSnap; i++){
    mySnap[i]->_mouseMoved(x,y);
    }


}
void videoGrid::mousePressed(int x, int y, int button){

        //mousePressed for ofSnap 
     for (int i = 0; i < nSnap; i++){
            mySnap[i]->_mousePressed(x,y, button);
        }
        //check page buttons
     for (int i = 0; i < buttons.size(); i++){
            buttons[i].checkMouseOver(ofPoint(x, y));
            if(i != 0){
              if(buttons[i].bMouseOver == true){
                  currentPage = i;              
                  if(currentPage != pages){
                      pages = currentPage;
                      //ofLog() << "current page: " << pages;
                    }                  
            //questo deve succedere solo dentro l'over non solo qando premo il mouse!!!!!
            //check if here are images in memory for current page
      for(int i=0; i< pagesMemory.size(); i++){
          if(pagesMemory[i] == pages-1)  alreadyLoaded = true;
          else alreadyLoaded = false;
                    //giá é stata caricata
                    //ofLog() << "pagine caricate: " << pagesMemory[i];
                  
        }
       //if areadyLoaded -> bhavesnap
     for (int i = 0; i < nSnap; i++){
            if(i < lastcell[pages]) mySnap[i]->bhavesnap = alreadyLoaded ;
            else mySnap[i]->bhavesnap = false ;
            //ofLog() << pages;
            mySnap[i]->page = pages;
              }
            }
        
      for(int i=0; i< pagesMemory.size(); i++){
          ofLog() << "pageMemory "<< i << " value " << pagesMemory[i];
          //if(pagesMemory[i] == pages)  ofLog() << "pagina giá caricata";
                    //else ofLog() << "pagina non caricata  ancora " ;
       } 
                }
            } 
                  
        
        
            if (buttons[0].bMouseOver == true){

            string command = "";

            ofDirectory dir(ofFilePath::join(getOFRoot(),defaultLoc));
            ofFileDialogResult res = ofSystemLoadDialog("please select video folder", true, dir.path());
            if (res.bSuccess){
                result = res.filePath;
                //convertWindowsToUnixPath(result);
                buttons[0].setText( result );

                setStatus("videos loaded from: " + result);
            

                //some path, may be absolute or relative to bin/data

                ofDirectory currentVideoDirectory(ofToDataPath(result, true));
                //only show png files
                currentVideoDirectory.allowExt("mov");
                currentVideoDirectory.allowExt("avi");
                currentVideoDirectory.allowExt("mp4");
                currentVideoDirectory.allowExt("mpeg");
                //populate the directory object
                currentVideoDirectory.listDir();
            
                // distribute video to all cells
                nVideoToLoad = currentVideoDirectory.size();
                lastcell[pages] = currentVideo-1;

                for(int i = 0; i < (int)currentVideoDirectory.size(); i++){
                        p = currentVideoDirectory.getPath(i);
                        ofLog() << lastcell[pages];
                        mySnap[lastcell[pages]]->loadImage(p,currentVideo);
                        nVideoToLoad--;
                        currentVideo++;
                        lastcell[pages] += 1;
                        if(lastcell[pages] >= nSnap){
                            lastcell[pages] = 0;
                        }
               }
                      ofLog() << "aggiungo pagina " << pages;
                      pagesMemory.push_back(pages);
              }
        }
              

}
void videoGrid::mouseReleased(int x, int y, int button){

   for (int i = 0; i < nSnap; i++){
    mySnap[i]->_mouseReleased(x,y, button);
    }

}

void videoGrid::keyPressed(int key){

   for (int i = 0; i < nSnap; i++){
    mySnap[i]->_keyPressed(key);
    }

}
