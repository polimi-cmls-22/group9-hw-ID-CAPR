import controlP5.*;
import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;
NetAddress localAddress;
NetAddress localAddressStatus;
ControlP5 cp5;

float x,y,z,d;  //coordinates of the shape (translation)

PImage[] labyrinths = new PImage[4];
PImage labyrinthsToDraw;

//CAPR
PImage logo;


//CHICK
boolean boomC = false;
float xChick = random(0,600);
float yChick = random(0,600);

int numFramesC = 12;
int currentFrameC = 0;
PImage[] gifChick = new PImage[numFramesC];

//PIG
boolean boomP = false;
float xPig = random(0,600);
float yPig = random(0,600);

int numFramesP = 12;
int currentFrameP = 0;
PImage[] gifPig = new PImage[numFramesP];

//BULL
boolean boomB = false;
float xBull = random(0,600);
float yBull = random(0,600);

int numFramesB = 12;
int currentFrameB = 0;
PImage[] gifBull = new PImage[numFramesB];

//VELOCIRAPTOR
boolean boomV = false;
float xVeloc = random(0,600);
float yVeloc = random(0,600);

int numFramesV = 19;
int currentFrameV = 0;
PImage[] gifVeloc = new PImage[numFramesV];

//PEOPLE
boolean boomPeople = false;
int casePeople;

int numFramesCla = 40;
int currentFrameCla = 0;
PImage[] gifCla = new PImage[numFramesCla];

int numFramesAndrew = 24;
int currentFrameAndrew = 0;
PImage[] gifAndrew = new PImage[numFramesAndrew];

int numFramesPier = 40;
int currentFramePier = 0;
PImage[] gifPier = new PImage[numFramesPier];

int numFramesRick = 40;
int currentFrameRick = 0;
PImage[] gifRick = new PImage[numFramesRick];


float xPeople = random(0,600);
float yPeople = random(0,600);

float wPeople = 375/9;
float hPeople = 666/9;


float xPoint;
float yPoint;
float xVel = 5;
float yVel = 5;

//SIZE ELEMENTS
float diamCapr = 60;
float diam =50;

//SET ELEMENTS
boolean setDrawC = false;
boolean setDrawB = false;
boolean setDrawV = false;
boolean setDrawP = false;
boolean setDrawPeople = false;


//Color Positions
float touch_r_down; 
float touch_g_down; 
float touch_b_down ;
  
float touch_r_up ;
float touch_g_up;
float touch_b_up;
  
float touch_r_left; 
float touch_g_left;
float touch_b_left;

float touch_r_right;
float touch_g_right;
float touch_b_right;


//GIF BACKGROUND
int numFrames = 1;
int currentFrame = 0;
PImage[] images = new PImage[numFrames];

//values to send
float xToSend;
float yToSend;

void setup(){
  
  size(600, 600);

  oscP5 = new OscP5(this,7563);
  
  //SET MAZE
  int i = int(random(0,labyrinths.length));
  labyrinthsToDraw = labyrinths[i];
  labyrinthsToDraw= loadImage("maze"+i+".png");
  
  
  //GIF BACKGROUND
  for(int b=0; b<images.length; b++){
    images[b] = loadImage("gif_"+b+".gif");
  }
  
  //CAPR
  logo = loadImage("logo.png");
  
  //GIFCHICK
  for(int c=0; c<gifChick.length; c++){
    gifChick[c] = loadImage("chick_"+c+".gif");
  }
  
  //GIFVEL
  for(int v=0; v<gifVeloc.length; v++){
    gifVeloc[v] = loadImage("veloc_"+v+".gif");
  }
  
  //GIFBULL
  for(int b=0; b<gifBull.length; b++){
    gifBull[b] = loadImage("bull_"+b+".gif");
  }
  
  //GIFPIG
  for(int p=0; p<gifPig.length; p++){
    gifPig[p] = loadImage("pig_"+p+".gif");
  }
  
  //LEAD PEOPLE
  for(int indCla=0; indCla<gifCla.length; indCla++){
    gifCla[indCla] = loadImage("cla"+indCla+".png");
  }
  for(int indAndrew=0; indAndrew<gifAndrew.length; indAndrew++){
    gifAndrew[indAndrew] = loadImage("andrew"+indAndrew+".png");
  }
  for(int indPier=0; indPier<gifPier.length; indPier++){
    gifPier[indPier] = loadImage("pier"+indPier+".png");
  }
  for(int indRick=0; indRick<gifRick.length; indRick++){
    gifRick[indRick] = loadImage("rick"+indRick+".png");
  }
  
  casePeople = (int)random(0,3);
  
  xPoint = width/2;
  yPoint = height/2;
  
  //myRemoteLocation = new NetAddress("192.168.6.2",9001);
  localAddress = new NetAddress("127.0.0.1", 9000);
  localAddressStatus = new NetAddress("127.0.0.1", 9001);
}

void draw()
{
  //MID
  touch_r_down = red(get((int)xPoint, (int)(yPoint+diamCapr/2)));
  touch_g_down = green(get((int)xPoint,(int)(yPoint+diamCapr/2)));
  touch_b_down = blue(get((int)xPoint,(int)(yPoint+diamCapr/2)));
  
  touch_r_up = red(get((int)xPoint,(int)(yPoint-diamCapr/2)));
  touch_g_up = green(get((int)xPoint,(int)(yPoint-diamCapr/2)));
  touch_b_up = blue(get((int)xPoint,(int)(yPoint-diamCapr/2)));
  
  touch_r_left = red(get((int)(xPoint-diamCapr/2),(int)yPoint));
  touch_g_left = green(get((int)(xPoint-diamCapr/2),(int)yPoint));
  touch_b_left = blue(get((int)(xPoint-diamCapr/2),(int)yPoint));
  
  touch_r_right = red(get((int)(xPoint+diamCapr/2),(int)yPoint));
  touch_g_right = green(get((int)(xPoint+diamCapr/2),(int)yPoint));
  touch_b_right = blue(get((int)(xPoint+diamCapr/2),(int)yPoint));
  
  //GIF BACKGROUND
  frameRate(24);
  currentFrame = (currentFrame+1) % numFrames;
  background(images[currentFrame]);
  imageMode(CENTER);
  
  //MAZE
  imageMode(CENTER);
  image(labyrinthsToDraw,width/2,height/2);
  
  //SET PEOPLE

  while(setDrawPeople == false){
    float xNewPeople = random(0,width);
    float yNewPeople = random(0,height);
    
    if (red(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && green(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && blue(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
        
    && red(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && green(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && blue(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople-hPeople/2))) != 0

    && red(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && green(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && blue(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
        
    &&red(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && green(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && blue(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
        
    && red(get((int)(xNewPeople), (int)(yNewPeople+hPeople/2))) != 0
    && green(get((int)(xNewPeople), (int)(yNewPeople+hPeople/2))) != 0
    && blue(get((int)(xNewPeople), (int)(yNewPeople+hPeople/2))) != 0
        
    && red(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople))) != 0
    && green(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople))) != 0
    && blue(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople))) != 0
        
    && red(get((int)(xNewPeople), (int)(yNewPeople-hPeople/2))) != 0
    && green(get((int)(xNewPeople), (int)(yNewPeople-hPeople/2))) != 0
    && blue(get((int)(xNewPeople), (int)(yNewPeople-hPeople/2))) != 0
        
    && red(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople))) != 0
    && green(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople))) != 0
    && blue(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople))) != 0) {
          
    xPeople = xNewPeople;
    yPeople = yNewPeople;
    setDrawPeople = true;
    }
  }
  imageMode(CENTER);
   switch(casePeople){
     case 0:
      currentFrameCla = (currentFrameCla+1) % numFramesCla;
      image(gifCla[currentFrameCla],xPeople,yPeople,wPeople,hPeople);
      break;
      case 1:
      currentFrameAndrew = (currentFrameAndrew+1) % numFramesAndrew;
      image(gifAndrew[currentFrameAndrew],xPeople,yPeople,wPeople,hPeople);
      break;
      case 2:
      currentFramePier = (currentFramePier+1) % numFramesPier;
      image(gifPier[currentFramePier],xPeople,yPeople,wPeople,hPeople);
      break;
      case 3:
      currentFrameRick = (currentFrameRick+1) % numFramesRick;
      image(gifRick[currentFrameRick],xPeople,yPeople,wPeople,hPeople);
      break;
      }

  
  //PEOPLE
  if(xPoint >= xPeople - (diam/2) && xPoint <= xPeople + (diam/2)
  && yPoint >= yPeople - (diam/2) && yPoint <= yPeople + (diam/2)
  && boomPeople == false){
    imageMode(CENTER);
    image(logo,width/2,height/2,diamCapr,diamCapr);
    xPoint = width/2;
    yPoint = height/2;
    sendHitMessage();
  }

  if(xPoint >= xPeople - (diamCapr) && xPoint <= xPeople + (diamCapr)
  && yPoint >= yPeople - (diamCapr) && yPoint <= yPeople + (diamCapr)
  && z == 0){ 
    sendBoomMessage();
    boolean canDraw = false;
    while(canDraw == false){
    float xNewPeople = random(0,width);
    float yNewPeople = random(0,height);
    
    if (red(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && green(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && blue(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
        
    && red(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && green(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && blue(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople-hPeople/2))) != 0

    && red(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && green(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
    && blue(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople+hPeople/2))) != 0
        
    &&red(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && green(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
    && blue(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople-hPeople/2))) != 0
        
    && red(get((int)(xNewPeople), (int)(yNewPeople+hPeople/2))) != 0
    && green(get((int)(xNewPeople), (int)(yNewPeople+hPeople/2))) != 0
    && blue(get((int)(xNewPeople), (int)(yNewPeople+hPeople/2))) != 0
        
    && red(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople))) != 0
    && green(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople))) != 0
    && blue(get((int)(xNewPeople+wPeople/2), (int)(yNewPeople))) != 0
        
    && red(get((int)(xNewPeople), (int)(yNewPeople-hPeople/2))) != 0
    && green(get((int)(xNewPeople), (int)(yNewPeople-hPeople/2))) != 0
    && blue(get((int)(xNewPeople), (int)(yNewPeople-hPeople/2))) != 0
        
    && red(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople))) != 0
    && green(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople))) != 0
    && blue(get((int)(xNewPeople-wPeople/2), (int)(yNewPeople))) != 0) {
          
    xPeople = xNewPeople;
    yPeople = yNewPeople;
    imageMode(CENTER);
    
    switch(casePeople){
      case 0:
      currentFrameAndrew = (currentFrameAndrew+1) % numFramesAndrew;
      image(gifAndrew[currentFrameAndrew],xPeople,yPeople,wPeople,hPeople);
      casePeople = 1;
      canDraw = true;
      break;
      case 1:
      currentFramePier = (currentFramePier+1) % numFramesPier;
      image(gifPier[currentFramePier],xPeople,yPeople,wPeople,hPeople);
      casePeople = 2;
      canDraw = true;
      break;
      case 2:
      currentFrameRick = (currentFrameRick+1) % numFramesRick;
      image(gifRick[currentFrameRick],xPeople,yPeople,wPeople,hPeople);
      casePeople = 3;
      canDraw = true;
      break;
      case 3:
      currentFrameCla = (currentFrameCla+1) % numFramesCla;
      image(gifCla[currentFrameCla],xPeople,yPeople,wPeople,hPeople);
      casePeople = 0;
      canDraw = true;
      break;
    }
  }
}
}

   
  //SET ANIMALS
  if(boomC == false){
    while(setDrawC == false){
      float xNewChick = random(0,width);
      float yNewChick = random(0,height);
    
      if (red(get((int)(xNewChick+diam/2), (int)(yNewChick+diam/2))) != 0
      && green(get((int)(xNewChick+diam/2), (int)(yNewChick+diam/2))) != 0
      && blue(get((int)(xNewChick+diam/2), (int)(yNewChick+diam/2))) != 0
       
      && red(get((int)(xNewChick+diam/2), (int)(yNewChick-diam/2))) != 0
      && green(get((int)(xNewChick+diam/2), (int)(yNewChick-diam/2))) != 0
      && blue(get((int)(xNewChick+diam/2), (int)(yNewChick-diam/2))) != 0
        
      && red(get((int)(xNewChick-diam/2), (int)(yNewChick+diam/2))) != 0
      && green(get((int)(xNewChick-diam/2), (int)(yNewChick+diam/2))) != 0
      && blue(get((int)(xNewChick-diam/2), (int)(yNewChick+diam/2))) != 0
       
      &&red(get((int)(xNewChick-diam/2), (int)(yNewChick-diam/2))) != 0
      && green(get((int)(xNewChick-diam/2), (int)(yNewChick-diam/2))) != 0
      && blue(get((int)(xNewChick-diam/2), (int)(yNewChick-diam/2))) != 0
       
      && red(get((int)(xNewChick), (int)(yNewChick+diam/2))) != 0
      && green(get((int)(xNewChick), (int)(yNewChick+diam/2))) != 0
      && blue(get((int)(xNewChick), (int)(yNewChick+diam/2))) != 0
        
      && red(get((int)(xNewChick+diam/2), (int)(yNewChick))) != 0
      && green(get((int)(xNewChick+diam/2), (int)(yNewChick))) != 0
      && blue(get((int)(xNewChick+diam/2), (int)(yNewChick))) != 0
        
      && red(get((int)(xNewChick), (int)(yNewChick-diam/2))) != 0
      && green(get((int)(xNewChick), (int)(yNewChick-diam/2))) != 0
      && blue(get((int)(xNewChick), (int)(yNewChick-diam/2))) != 0
      
      && red(get((int)(xNewChick-diam/2), (int)(yNewChick))) != 0
      && green(get((int)(xNewChick-diam/2), (int)(yNewChick))) != 0
      && blue(get((int)(xNewChick-diam/2), (int)(yNewChick))) != 0){
        xChick = xNewChick;
        yChick = yNewChick;
        setDrawC = true;       
        boomC = false; 
      }
    }
    currentFrameC = (currentFrameC+1) % numFramesC;
    image(gifChick[currentFrameC],xChick,yChick,diam,diam);
  }
  
  if (boomV == false){
    while(setDrawV == false){
      float xNewVeloc = random(0,width);
      float yNewVeloc = random(0,height);
    
      if (red(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc+diam/2))) != 0
      && green(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc+diam/2))) != 0
      && blue(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc+diam/2))) != 0
       
      && red(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc-diam/2))) != 0
      && green(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc-diam/2))) != 0
      && blue(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc-diam/2))) != 0
        
      && red(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc+diam/2))) != 0
      && green(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc+diam/2))) != 0
      && blue(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc+diam/2))) != 0
       
      &&red(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc-diam/2))) != 0
      && green(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc-diam/2))) != 0
      && blue(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc-diam/2))) != 0
       
      && red(get((int)(xNewVeloc), (int)(yNewVeloc+diam/2))) != 0
      && green(get((int)(xNewVeloc), (int)(yNewVeloc+diam/2))) != 0
      && blue(get((int)(xNewVeloc), (int)(yNewVeloc+diam/2))) != 0
        
      && red(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc))) != 0
      && green(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc))) != 0
      && blue(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc))) != 0
        
      && red(get((int)(xNewVeloc), (int)(yNewVeloc-diam/2))) != 0
      && green(get((int)(xNewVeloc), (int)(yNewVeloc-diam/2))) != 0
      && blue(get((int)(xNewVeloc), (int)(yNewVeloc-diam/2))) != 0
      
      && red(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc))) != 0
      && green(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc))) != 0
      && blue(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc))) != 0){
        xVeloc = xNewVeloc;
        yVeloc = yNewVeloc;
        setDrawV = true;       
        boomV = false; 
      }
    }
    currentFrameV = (currentFrameV+1) % numFramesV;
    image(gifVeloc[currentFrameV],xVeloc,yVeloc,diam,diam);
  }
  
  if (boomB == false){
    while(setDrawB == false){
      float xNewBull = random(0,width);
      float yNewBull = random(0,height);
    
      if (red(get((int)(xNewBull+diam/2), (int)(yNewBull+diam/2))) != 0
      && green(get((int)(xNewBull+diam/2), (int)(yNewBull+diam/2))) != 0
      && blue(get((int)(xNewBull+diam/2), (int)(yNewBull+diam/2))) != 0

      && red(get((int)(xNewBull+diam/2), (int)(yNewBull-diam/2))) != 0
      && green(get((int)(xNewBull+diam/2), (int)(yNewBull-diam/2))) != 0
      && blue(get((int)(xNewBull+diam/2), (int)(yNewBull-diam/2))) != 0
        
      && red(get((int)(xNewBull-diam/2), (int)(yNewBull+diam/2))) != 0
      && green(get((int)(xNewBull-diam/2), (int)(yNewBull+diam/2))) != 0
      && blue(get((int)(xNewBull-diam/2), (int)(yNewBull+diam/2))) != 0
       
      &&red(get((int)(xNewBull-diam/2), (int)(yNewBull-diam/2))) != 0
      && green(get((int)(xNewBull-diam/2), (int)(yNewBull-diam/2))) != 0
      && blue(get((int)(xNewBull-diam/2), (int)(yNewBull-diam/2))) != 0
       
      && red(get((int)(xNewBull), (int)(yNewBull+diam/2))) != 0
      && green(get((int)(xNewBull), (int)(yNewBull+diam/2))) != 0
      && blue(get((int)(xNewBull), (int)(yNewBull+diam/2))) != 0
        
      && red(get((int)(xNewBull+diam/2), (int)(yNewBull))) != 0
      && green(get((int)(xNewBull+diam/2), (int)(yNewBull))) != 0
      && blue(get((int)(xNewBull+diam/2), (int)(yNewBull))) != 0
        
      && red(get((int)(xNewBull), (int)(yNewBull-diam/2))) != 0
      && green(get((int)(xNewBull), (int)(yNewBull-diam/2))) != 0
      && blue(get((int)(xNewBull), (int)(yNewBull-diam/2))) != 0
      
      && red(get((int)(xNewBull-diam/2), (int)(yNewBull))) != 0
      && green(get((int)(xNewBull-diam/2), (int)(yNewBull))) != 0
      && blue(get((int)(xNewBull-diam/2), (int)(yNewBull))) != 0){
        xBull = xNewBull;
        yBull = yNewBull;
        setDrawB = true;       
        boomB = false; 
      }
    }
    currentFrameB = (currentFrameB+1) % numFramesB;
    image(gifBull[currentFrameB],xBull,yBull,diam,diam);
  }
  
  if (boomP == false){
    while(setDrawP == false){
      float xNewPig = random(0,width);
      float yNewPig = random(0,height);
    
      if (red(get((int)(xNewPig+diam/2), (int)(yNewPig+diam/2))) != 0
      && green(get((int)(xNewPig+diam/2), (int)(yNewPig+diam/2))) != 0
      && blue(get((int)(xNewPig+diam/2), (int)(yNewPig+diam/2))) != 0

      && red(get((int)(xNewPig+diam/2), (int)(yNewPig-diam/2))) != 0
      && green(get((int)(xNewPig+diam/2), (int)(yNewPig-diam/2))) != 0
      && blue(get((int)(xNewPig+diam/2), (int)(yNewPig-diam/2))) != 0
        
      && red(get((int)(xNewPig-diam/2), (int)(yNewPig+diam/2))) != 0
      && green(get((int)(xNewPig-diam/2), (int)(yNewPig+diam/2))) != 0
      && blue(get((int)(xNewPig-diam/2), (int)(yNewPig+diam/2))) != 0
       
      &&red(get((int)(xNewPig-diam/2), (int)(yNewPig-diam/2))) != 0
      && green(get((int)(xNewPig-diam/2), (int)(yNewPig-diam/2))) != 0
      && blue(get((int)(xNewPig-diam/2), (int)(yNewPig-diam/2))) != 0
       
      && red(get((int)(xNewPig), (int)(yNewPig+diam/2))) != 0
      && green(get((int)(xNewPig), (int)(yNewPig+diam/2))) != 0
      && blue(get((int)(xNewPig), (int)(yNewPig+diam/2))) != 0
        
      && red(get((int)(xNewPig+diam/2), (int)(yNewPig))) != 0
      && green(get((int)(xNewPig+diam/2), (int)(yNewPig))) != 0
      && blue(get((int)(xNewPig+diam/2), (int)(yNewPig))) != 0
        
      && red(get((int)(xNewPig), (int)(yNewPig-diam/2))) != 0
      && green(get((int)(xNewPig), (int)(yNewPig-diam/2))) != 0
      && blue(get((int)(xNewPig), (int)(yNewPig-diam/2))) != 0
      
      && red(get((int)(xNewPig-diam/2), (int)(yNewPig))) != 0
      && green(get((int)(xNewPig-diam/2), (int)(yNewPig))) != 0
      && blue(get((int)(xNewPig-diam/2), (int)(yNewPig))) != 0){
        xPig = xNewPig;
        yPig = yNewPig;
        setDrawP = true;       
        boomP = false; 
      }
    }
    currentFrameP = (currentFrameP+1) % numFramesP;
    image(gifPig[currentFrameP],xPig,yPig,diam,diam);
  }

  //SET CAPR
  imageMode(CENTER);
  image(logo,xPoint,yPoint,diamCapr,diamCapr);
  
  //CHICKEN
  if(xPoint >= xChick - (diam/2) && xPoint <= xChick + (diam/2)
  && yPoint >= yChick - (diam/2) && yPoint <= yChick + (diam/2)
  && boomC == false){
    imageMode(CENTER);
    image(logo,width/2,height/2,diamCapr,diamCapr);
    xPoint = width/2;
    yPoint = height/2;
    sendHitMessage();
  }
  
  
  if(xPoint >= xChick - (diamCapr) && xPoint <= xChick + (diamCapr)
  && yPoint >= yChick - (diamCapr) && yPoint <= yChick + (diamCapr)
  && boomC == false && d == 1){
    sendBoomMessage();
    boomC = true;
    boolean canDraw = false;
    while(canDraw == false){
    
      float xNewChick = random(0,width);
      float yNewChick = random(0,height);
    
    if (red(get((int)(xNewChick+diam/2), (int)(yNewChick+diam/2))) != 0
        && green(get((int)(xNewChick+diam/2), (int)(yNewChick+diam/2))) != 0
        && blue(get((int)(xNewChick+diam/2), (int)(yNewChick+diam/2))) != 0
        
        && red(get((int)(xNewChick+diam/2), (int)(yNewChick-diam/2))) != 0
        && green(get((int)(xNewChick+diam/2), (int)(yNewChick-diam/2))) != 0
        && blue(get((int)(xNewChick+diam/2), (int)(yNewChick-diam/2))) != 0
        
        && red(get((int)(xNewChick-diam/2), (int)(yNewChick+diam/2))) != 0
        && green(get((int)(xNewChick-diam/2), (int)(yNewChick+diam/2))) != 0
        && blue(get((int)(xNewChick-diam/2), (int)(yNewChick+diam/2))) != 0
        
        &&red(get((int)(xNewChick-diam/2), (int)(yNewChick-diam/2))) != 0
        && green(get((int)(xNewChick-diam/2), (int)(yNewChick-diam/2))) != 0
        && blue(get((int)(xNewChick-diam/2), (int)(yNewChick-diam/2))) != 0
        
        && red(get((int)(xNewChick), (int)(yNewChick+diam/2))) != 0
        && green(get((int)(xNewChick), (int)(yNewChick+diam/2))) != 0
        && blue(get((int)(xNewChick), (int)(yNewChick+diam/2))) != 0
        
        && red(get((int)(xNewChick+diam/2), (int)(yNewChick))) != 0
        && green(get((int)(xNewChick+diam/2), (int)(yNewChick))) != 0
        && blue(get((int)(xNewChick+diam/2), (int)(yNewChick))) != 0
        
        && red(get((int)(xNewChick), (int)(yNewChick-diam/2))) != 0
        && green(get((int)(xNewChick), (int)(yNewChick-diam/2))) != 0
        && blue(get((int)(xNewChick), (int)(yNewChick-diam/2))) != 0
        
        && red(get((int)(xNewChick-diam/2), (int)(yNewChick))) != 0
        && green(get((int)(xNewChick-diam/2), (int)(yNewChick))) != 0
        && blue(get((int)(xNewChick-diam/2), (int)(yNewChick))) != 0) {
    
          xChick = xNewChick;
          yChick = yNewChick;
          canDraw = true;
          boomC = false;
    } 
  }
}
  
  //VELOCIRAPTOR
  if(xPoint >= xVeloc - (diam/2) && xPoint <= xVeloc + (diam/2)
  && yPoint >= yVeloc - (diam/2) && yPoint <= yVeloc + (diam/2)
  && boomV == false){
    imageMode(CENTER);
    image(logo,width/2,height/2,diamCapr,diamCapr);
    xPoint = width/2;
    yPoint = height/2;
    sendHitMessage();
  }
  
  if(xPoint >= xVeloc - (diamCapr) && xPoint <= xVeloc + (diamCapr)
  && yPoint >= yVeloc - (diamCapr) && yPoint <= yVeloc + (diamCapr)
  && boomV == false && d == 1){
    sendBoomMessage();
    boomV = true;
    boolean canDraw = false;
    while(canDraw == false){
    
      float xNewVeloc = random(0,width);
      float yNewVeloc = random(0,height);
    
    if (red(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc+diam/2))) != 0
        && green(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc+diam/2))) != 0
        && blue(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc+diam/2))) != 0
        
        && red(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc-diam/2))) != 0
        && green(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc-diam/2))) != 0
        && blue(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc-diam/2))) != 0
        
        && red(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc+diam/2))) != 0
        && green(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc+diam/2))) != 0
        && blue(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc+diam/2))) != 0
        
        &&red(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc-diam/2))) != 0
        && green(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc-diam/2))) != 0
        && blue(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc-diam/2))) != 0
        
        && red(get((int)(xNewVeloc), (int)(yNewVeloc+diam/2))) != 0
        && green(get((int)(xNewVeloc), (int)(yNewVeloc+diam/2))) != 0
        && blue(get((int)(xNewVeloc), (int)(yNewVeloc+diam/2))) != 0
        
        && red(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc))) != 0
        && green(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc))) != 0
        && blue(get((int)(xNewVeloc+diam/2), (int)(yNewVeloc))) != 0
        
        && red(get((int)(xNewVeloc), (int)(yNewVeloc-diam/2))) != 0
        && green(get((int)(xNewVeloc), (int)(yNewVeloc-diam/2))) != 0
        && blue(get((int)(xNewVeloc), (int)(yNewVeloc-diam/2))) != 0
        
        && red(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc))) != 0
        && green(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc))) != 0
        && blue(get((int)(xNewVeloc-diam/2), (int)(yNewVeloc))) != 0) {
    
          xVeloc = xNewVeloc;
          yVeloc = yNewVeloc;
          canDraw = true;
          boomV = false;
    } 
  }
}
  
  //PIG
  if(xPoint >= xPig - (diam/2) && xPoint <= xPig + (diam/2)
  && yPoint >= yPig - (diam/2) && yPoint <= yPig + (diam/2)
  && boomP == false){
    imageMode(CENTER);
    image(logo,width/2,height/2,diamCapr,diamCapr);
    xPoint = width/2;
    yPoint = height/2;
    sendHitMessage();
  }
  if(xPoint >= xPig - (diamCapr) && xPoint <= xPig + (diamCapr)
  && yPoint >= yPig - (diamCapr) && yPoint <= yPig + (diamCapr)
  && boomP == false && d == 1){
    sendBoomMessage();
    boomP = true;
    boolean canDraw = false;
    while(canDraw == false){
      
      float xNewPig = random(0,width);
      float yNewPig = random(0,height);
    if (red(get((int)(xNewPig+diam/2), (int)(yNewPig+diam/2))) != 0
        && green(get((int)(xNewPig+diam/2), (int)(yNewPig+diam/2))) != 0
        && blue(get((int)(xNewPig+diam/2), (int)(yNewPig+diam/2))) != 0
        
        && red(get((int)(xNewPig+diam/2), (int)(yNewPig-diam/2))) != 0
        && green(get((int)(xNewPig+diam/2), (int)(yNewPig-diam/2))) != 0
        && blue(get((int)(xNewPig+diam/2), (int)(yNewPig-diam/2))) != 0
        
        && red(get((int)(xNewPig-diam/2), (int)(yNewPig+diam/2))) != 0
        && green(get((int)(xNewPig-diam/2), (int)(yNewPig+diam/2))) != 0
        && blue(get((int)(xNewPig-diam/2), (int)(yNewPig+diam/2))) != 0
        
        &&red(get((int)(xNewPig-diam/2), (int)(yNewPig-diam/2))) != 0
        && green(get((int)(xNewPig-diam/2), (int)(yNewPig-diam/2))) != 0
        && blue(get((int)(xNewPig-diam/2), (int)(yNewPig-diam/2))) != 0
        
        && red(get((int)(xNewPig), (int)(yNewPig+diam/2))) != 0
        && green(get((int)(xNewPig), (int)(yNewPig+diam/2))) != 0
        && blue(get((int)(xNewPig), (int)(yNewPig+diam/2))) != 0
        
        && red(get((int)(xNewPig+diam/2), (int)(yNewPig))) != 0
        && green(get((int)(xNewPig+diam/2), (int)(yNewPig))) != 0
        && blue(get((int)(xNewPig+diam/2), (int)(yNewPig))) != 0
        
        && red(get((int)(xNewPig), (int)(yNewPig-diam/2))) != 0
        && green(get((int)(xNewPig), (int)(yNewPig-diam/2))) != 0
        && blue(get((int)(xNewPig), (int)(yNewPig-diam/2))) != 0
        
        && red(get((int)(xNewPig-diam/2), (int)(yNewPig))) != 0
        && green(get((int)(xNewPig-diam/2), (int)(yNewPig))) != 0
        && blue(get((int)(xNewPig-diam/2), (int)(yNewPig))) != 0) {
    
    xPig = xNewPig;
    yPig = yNewPig;
    canDraw = true;
    boomP = false;
        }
    }
  }
  
  //BULL
  if(xPoint >= xBull - (diam/2) && xPoint <= xBull + (diam/2)
  && yPoint >= yBull - (diam/2) && yPoint <= yBull + (diam/2)
  && boomB == false){
    imageMode(CENTER);
    image(logo,width/2,height/2,diamCapr,diamCapr);
    xPoint = width/2;
    yPoint = height/2;
    sendHitMessage();
  }
  if(xPoint >= xBull - (diamCapr) && xPoint <= xBull + (diamCapr)
  && yPoint >= yBull - (diamCapr) && yPoint <= yBull + (diamCapr)
  && boomB == false && d == 1){
    sendBoomMessage();
    boomB = true;
    boolean canDraw = false;
    while(canDraw == false){
      float xNewBull = random(0,width);
      float yNewBull = random(0,height);
    if (red(get((int)(xNewBull+diam/2), (int)(yNewBull+diam/2))) != 0
        && green(get((int)(xNewBull+diam/2), (int)(yNewBull+diam/2))) != 0
        && blue(get((int)(xNewBull+diam/2), (int)(yNewBull+diam/2))) != 0
        
        && red(get((int)(xNewBull+diam/2), (int)(yNewBull-diam/2))) != 0
        && green(get((int)(xNewBull+diam/2), (int)(yNewBull-diam/2))) != 0
        && blue(get((int)(xNewBull+diam/2), (int)(yNewBull-diam/2))) != 0
        
        && red(get((int)(xNewBull-diam/2), (int)(yNewBull+diam/2))) != 0
        && green(get((int)(xNewBull-diam/2), (int)(yNewBull+diam/2))) != 0
        && blue(get((int)(xNewBull-diam/2), (int)(yNewBull+diam/2))) != 0

        &&red(get((int)(xNewBull-diam/2), (int)(yNewBull-diam/2))) != 0
        && green(get((int)(xNewBull-diam/2), (int)(yNewBull-diam/2))) != 0
        && blue(get((int)(xNewBull-diam/2), (int)(yNewBull-diam/2))) != 0
        
        && red(get((int)(xNewBull), (int)(yNewBull+diam/2))) != 0
        && green(get((int)(xNewBull), (int)(yNewBull+diam/2))) != 0
        && blue(get((int)(xNewBull), (int)(yNewBull+diam/2))) != 0
        
        && red(get((int)(xNewBull+diam/2), (int)(yNewBull))) != 0
        && green(get((int)(xNewBull+diam/2), (int)(yNewBull))) != 0
        && blue(get((int)(xNewBull+diam/2), (int)(yNewBull))) != 0
        
        && red(get((int)(xNewBull), (int)(yNewBull-diam/2))) != 0
        && green(get((int)(xNewBull), (int)(yNewBull-diam/2))) != 0
        && blue(get((int)(xNewBull), (int)(yNewBull-diam/2))) != 0
        
        && red(get((int)(xNewBull-diam/2), (int)(yNewBull))) != 0
        && green(get((int)(xNewBull-diam/2), (int)(yNewBull))) != 0
        && blue(get((int)(xNewBull-diam/2), (int)(yNewBull))) != 0) {
    
    xBull = xNewBull;
    yBull = yNewBull;
    canDraw = true;
    boomB = false;
    }
  }
}
  
}

void sendXMessage(float xRecieved){
xToSend = xRecieved;
OscMessage messageToSend = new OscMessage("/coordinates/xCoordinate");
messageToSend.add(xToSend);
oscP5.send(messageToSend, localAddress);
}

void sendYMessage(float yRecieved){
yToSend = height-yRecieved;
OscMessage messageToSend = new OscMessage("/coordinates/yCoordinate");
messageToSend.add(yToSend);
oscP5.send(messageToSend, localAddress);
}

void sendHitMessage(){
  OscMessage messageToSend = new OscMessage("/hit");
  messageToSend.add("hit");
  oscP5.send(messageToSend, localAddressStatus);
}

void sendBoomMessage(){
  OscMessage messageToSend = new OscMessage("/boom");
  messageToSend.add("boom");
  oscP5.send(messageToSend, localAddressStatus);
}




/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
 
  //If address of oscMessage is /colour then change the shape and colour visualized
  if (theOscMessage.checkAddrPattern("/movement/xPosition"))
  {
    //Get X value
    x = theOscMessage.get(0).floatValue();
   
    //Move to left & control black pixel
    if (Math.round(x) == -1){
      //println("mi sposto a sinistra"+ x);
      if((touch_r_left == 0 && touch_g_left == 0 && touch_b_left == 0)){   
        xPoint = xPoint + xVel;
        sendXMessage(xPoint);
      }
      else{
        xPoint = xPoint - xVel;//move to left 
        sendXMessage(xPoint);
      }
    }
    
    //Move to right & control black pixel
    if(Math.round(x) == 1) {
      //println("mi sposto a destra"+ x);
      if((touch_r_right == 0 && touch_r_right == 0 && touch_r_right == 0)){   
         xPoint = xPoint - xVel;
         sendXMessage(xPoint);
      }
      else{
        xPoint = xPoint + xVel;//move to right
        sendXMessage(xPoint);
      }
    }
  }
    if (theOscMessage.checkAddrPattern("/movement/yPosition"))
  {
    //Get Y value
    y = theOscMessage.get(0).floatValue();
    
    //Move Up & control black pixel
    if (Math.round(y) == 1){
      if((touch_r_up == 0 && touch_g_up == 0 && touch_b_up == 0)){   
         yPoint = yPoint + yVel;
         sendYMessage(yPoint);
      }
      else{
        yPoint = yPoint - yVel;//move up
        sendYMessage(yPoint);
      }
    }
  
    //Move Down & control black pixel
    if(y < 0.4) {
      if((touch_r_down == 0 && touch_g_down == 0 && touch_b_down == 0)){   
         yPoint = yPoint - yVel;
         sendYMessage(yPoint);
      }
      else{
        yPoint = yPoint + yVel;//move down
        sendYMessage(yPoint);
      }
    }
  } 
  if (theOscMessage.checkAddrPattern("/movement/zPosition")) {
    //Get Z digital value
  z = theOscMessage.get(0).floatValue();
  //println("z: "+z);
  }
  
  if (theOscMessage.checkAddrPattern("/movement/statusPosition")) {
  //Get digital value of the sensor
  d = theOscMessage.get(0).floatValue();
  //println("d: "+d);
  }
}
