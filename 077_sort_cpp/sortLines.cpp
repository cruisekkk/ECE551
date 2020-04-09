#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char ** argv){
  //stdin
  if (argc == 1){
    std::string s;
    std::vector<std::string> v;
    while(getline(std::cin, s)){
      // cin meet eof, ctrl+D = quit
      v.push_back(s);
    }
    std::sort(v.begin(), v.end());
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++){
      std::cout<<*it<<std::endl;
    };
    v.clear();
    return EXIT_SUCCESS;
  }    
  //comman line
  for (int i = 1; i < argc; i++){
    std::vector<std::string> v;
    std::ifstream ifs (argv[i], std::ifstream::in);
    // char c = ifs.get();
    if(!ifs){
      fprintf(stderr, "cannot open");
      return EXIT_FAILURE;
    }
    
    std::string s;
    while(getline(ifs, s)){
      v.push_back(s);
    }
    //string s = ifs.getline;
    //while (ifs.good()) {
    // v.push_back(s);
    //  c = ifs.get();
          
    //sort
    std::sort(v.begin(), v.end());
    //print
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++){
      std::cout<<*it<<std::endl;
    };
    //std::cout<<std::endl;
    v.clear();
    ifs.close();
  };
  return EXIT_SUCCESS;
}

