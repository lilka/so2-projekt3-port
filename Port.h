class Port{
  bool promInside=false;
  int promInsideId=-1; 
public:
  Port();
  void drawPort(); 
  int getPromInsideId();
  void setPromInsideId(int);
  bool isPromInside(); 
  void setPromInside(bool);

};