#ifndef PORT_H
#define PORT_H

class Port{
  bool promInside=false;
  int promInsideId=-1; 
  int passangerCount = 0;
public:
  Port();
  void draw(); 
  int getPromInsideId();
  void setPromInsideId(int Id);
  bool isPromInside(); 
  void addPassanger();

};

#endif
