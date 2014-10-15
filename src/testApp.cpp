#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    myGrid = new videoGrid(5,4, 100, 100);


}

//--------  ------------------------------------------------------
void testApp::update(){
    myGrid->update();

}

//--------------------------------------------------------------
void testApp::draw(){
    myGrid->draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  myGrid->keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

   myGrid->mouseMoved(x,y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
//myGrid->mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    myGrid->mousePressed(x,y,button);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
//          for (int i = 0; i < nSnap; i++){
                //ofLog() << "index " << mySnap[i]->id << "+ over " << mySnap[i]->isOver;
        myGrid->mouseReleased(x,y,button);
       // }
}

//--------------------------------------------------------------

void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
