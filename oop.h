LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define sx 20
#define sy 4
#define linelength 64
#define lines 8

class Line{
  char buff[linelength];
  char index;
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
  void draw(char y){
    if(y>=0){
      char c;
      char x=index;
      if(x<sx){
        lcd.setCursor(0,y);
        for(int i=0;i<x;i++){
          lcd.write(buff[i]);
        }
        for(int i=1;i<sx-x;i++){
          lcd.write(' ');
        }
        lcd.setCursor(x,y);
      }
      else{
        lcd.setCursor(0,y);
        for(int i=x-sx+1;i<x;i++){
          lcd.write(buff[i]);
        }
      }
    }
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
  Line line[lines];
public:
  void add(char c){
    line[lines-1].add(c);
  }
  void drawAll(){
    for(int i=0;i<lines;i++){
      this->line[i].draw(sy-lines+i); 
    }
  }
  void draw(){
    line[lines-1].draw(sy-1);
  }
  void del(){
    line[lines-1].del();
  }
  void enter(){
    for(int i=lines-1;i>=1;i--){
      line[lines-1-i].setbuff(line[lines-i].getbuff());
      line[lines-1-i].setIndex(line[lines-i].getIndex());
    }
    line[lines-1].clear();
    this->drawAll();
  }
  void back(){
    for(int i=0;i<lines-1;i++){
      line[lines-1-i].setbuff(line[lines-i-2].getbuff());
      line[lines-1-i].setIndex(line[lines-i-2].getIndex());
    }
    line[0].clear();
    this->drawAll();
  }
  void print(String s){
    for(int i=0;i<s.length();i++) this->add(s[i]);
  }
};




