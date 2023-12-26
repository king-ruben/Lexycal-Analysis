#include <iostream>
#include <fstream>
// clang++ fstream.cpp -o fstream.bin && ./fstream.bin && rm ./fstream.bin
int main(void) 
{
  std::ofstream archivo("result.cpp", std::ios::app);
  std::string includes  = "#include <iostream>\n";
  std::string main = "int main(void) { return 0; } ";
  if(archivo.is_open())  { 
   archivo << includes << std::endl;
   archivo.close();
  } else {
    std::cerr << "Error" << std::endl;
  }
  
  
return 0;

}
