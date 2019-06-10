class Port{
  bool promInside=false;
  int promInsideId=-1; 
public:
  Port();
  void drawPort(); 
  int getPromInsideId();
  void setPromInsideId(int Id);
  bool isPromInside(); 

};