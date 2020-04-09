#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>


int main(int argc, char** argv){
  std::ifstream f(argv[1]);
  std::string ss;
  std::hash<std::string> s_hash;
  unsigned count;
  std::unordered_map<size_t, unsigned> mymap;
  std::unordered_map<size_t, unsigned>::iterator it;
  //f << std::stdin;
  while(getline(f, ss)){
    //std::cout << 1 << std::endl;
    it = mymap.find(s_hash(ss));
    if (it != mymap.end()){
      //std::cout << 1 << std::endl;
      //mymap.insert(std::pair<size_t, unsigned>(s_hash(ss), 1));
      mymap[s_hash(ss)]++;
    }
    else{
      //std::cout << 1 << std::endl;
      mymap.insert(it, std::pair<size_t, unsigned>(s_hash(ss), 0));
    }
  }
  while(getline(std::cin, ss)){
    //std::cout << 1 << std::endl;
    it = mymap.find(s_hash(ss));
    if (it != mymap.end()){
      //std::cout << 1 << std::endl;
      //mymap.insert(std::pair<size_t, unsigned>(s_hash(ss), 1));
      mymap[s_hash(ss)]++;
    }
    else{
      //std::cout << 1 << std::endl;
      mymap.insert(it, std::pair<size_t, unsigned>(s_hash(ss), 0));
    }
  }
  int i = 0;
  for (std::unordered_map<size_t, unsigned>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
    if(it->second > 0){
      i++;
    }
  }
    std::cout<< mymap.size() <<std::endl;
    std::cout<< i <<std::endl;
  return EXIT_SUCCESS;  
}
