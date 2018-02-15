LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define sx 20
#define sy 4
#define linelength 64

class Line{
  char buff[linelength];
  char index,y;
public:
  Line(){
    index=0;
    for(int i=0;i<linelength;i++) buff[i]=NULL;
  }
  void add(char c){
    if(index<linelength){
      buff[index++]=c;
    }
  }
  void del(){
    if(index>0){
      buff[--index]=NULL;
    }
  }
  void draw(){
    char c;
    char x=index;
    /*for(int i=0;i<linelength;i++){
      if(buff[i]==NULL){
        x=i;
        break;
      }
    }*/
    if(x<sx){
      lcd.setCursor(0,this->y);
      for(int i=0;i<x;i++){
        lcd.write(buff[i]);
      }
      for(int i=1;i<sx-x;i++){
        lcd.write(' ');
      }
      lcd.setCursor(x,y);
    }else{
      lcd.setCursor(0,this->y);
      for(int i=x-sx+1;i<x;i++){
        lcd.write(buff[i]);
      }
    }
  }
  void setY(char y){
    this->y=y;
  }
  char *getbuff(){
    return this->buff;
  }
  void setbuff(char newbuff[]){
    for(int i=0;i<linelength;i++){
      this->buff[i] = newbuff[i];
    }
    this->index=20;
  }
  char getIndex(){
    return this->index;
  }
  void setIndex(char i){
    this->index=i;
  }
  void clear(){

    for(int i=0;i<linelength;i++) this->buff[i]=NULL;
    this->index=0;
  }
};

class Screen{
  Line l1,l2,l3,l4;
public:
  Screen(){
    this->l1.setY(0);
    this->l2.setY(1);
    this->l3.setY(2);
    this->l4.setY(3);
  }
  void add(char c){
    l4.add(c);
  }
  void drawAll(){
    l1.draw();
    l2.draw();
    l3.draw();
    l4.draw();
  }
  void draw(){
    l4.draw();
  }
  void del(){
    l4.del();
  }
  void enter(){
    l1.setbuff(l2.getbuff());
    l1.setIndex(l2.getIndex());
    l2.setbuff(l3.getbuff());
    l2.setIndex(l3.getIndex());
    l3.setbuff(l4.getbuff());
    l3.setIndex(l4.getIndex());
    l4.clear();
    this->drawAll();
  }
};


