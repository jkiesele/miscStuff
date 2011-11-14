#include "CountTools.h"
#include <fstream>
#include <cmath>


void writeYieldTable(std::vector<CountTools> vec, TString filename){
  if(vec.size()>0){
    std::vector<TString> names = vec[0].getNames();

    ofstream myfile;
    myfile.open (filename, ios::out | ios::app);
    for(unsigned int j = 0 ; j < vec.size() ; j++){
      myfile << "  && \t";
      myfile << (vec[j].getName());
    }
    myfile << " \\\\ \\hline\n";
    for(unsigned int i=1; i< names.size(); i++){
      names[i].ReplaceAll("#", "\\");
      names[i].ReplaceAll(" ", "\\ ");
      myfile << "$";
      myfile << names[i];
      myfile << "$\t";
      for(unsigned int j = 0 ; j < vec.size() ; j++){
	myfile << "  && \t";
	myfile << (vec[j].getNs())[i];
      }
      myfile << "  \\\\ \n";
    }
    myfile << "\\hline\n";
    myfile << "MC sum ";
    for(unsigned int j = 0 ; j < vec.size() ; j++){
      myfile << "  && \t";
      myfile << (vec[j].getNsig("fg") + (vec[j].getNs())[0]);
    }
    myfile << "\\\\ \n";
    myfile << "$Data$\t";
    for(unsigned int j = 0 ; j < vec.size() ; j++){
      myfile << "  && \t";
      myfile << (vec[j].getNs())[0];
      myfile << "$\\pm$";
      myfile << sqrt((vec[j].getNs())[0]);
    }
    myfile << " \\\\ \\hline \n";
    myfile.close();




  }
  else std::cout << "empty countervector" << std::endl;
}
