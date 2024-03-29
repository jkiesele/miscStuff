
#ifndef CountTools_h
#define CountTools_h

#include <vector>
#include <iostream>
#include "TString.h"


class CountTools {


public:
  CountTools();
  ~CountTools();

  void   setDataSet(TString);
  void   setOptions(TString, double);
  TString getName();
  std::vector<double> getNs();
  std::vector<TString> getNames();
  void coutNs();
  double getNsig(TString);
  double getNsig(std::vector<TString>);
  double coutNsig(TString);
  double coutNsig(std::vector<TString>);
  void fill(TString, float);
  void fill(TString, double);
  bool isData(TString);
  double getEff(std::vector<TString>, double);
  void setLumi(double);

private:


  std::vector<TString> dataset;
  std::vector<double> scales;
  std::vector<TString> legends;
  std::vector<double> numbers;

  double DYScale;
  TString DYEntry;
  TString name;
  double Lumi;

};






CountTools::CountTools()
{

  Lumi=1141;
  setDataSet("ee");
  numbers.clear();
  for(unsigned int i=0;  i < dataset.size(); i++){
    numbers.push_back(0);
  }
}

CountTools::~CountTools()
{


}

void CountTools::setLumi(double lumi){
  Lumi=lumi;
}

TString CountTools::getName(){
  return name;
}


double CountTools::getEff(std::vector<TString> datasets, double startEvts){

  double MCsum=0.;
  for(unsigned int j=0; j < numbers.size(); j++){
    bool isSignalMC=false;
    for(unsigned int i = 0; i< datasets.size() ; i++){
      if(dataset[j] == datasets[i]) isSignalMC=true;
    }
    if(isSignalMC && legends[j] != "data") MCsum=MCsum + numbers[j];


  }

  return MCsum/startEvts;

}




void   CountTools::setOptions(TString name_, double DYScale_)
{
  name=name_;
  DYScale=DYScale_;

}

void   CountTools::fill(TString datatype, float weight)
{

  for(unsigned int i=0; i< dataset.size(); i++){
    if(dataset[i] == datatype){
      if(legends[i]==DYEntry){
	weight=weight*DYScale;
      }
      numbers[i]=numbers[i]+weight;
    }
  }
}

void   CountTools::fill(TString datatype, double weight)
{

  for(unsigned int i=0; i< dataset.size(); i++){
    if(dataset[i] == datatype){
      if(legends[i]==DYEntry){
	weight=weight*DYScale;
      }
      numbers[i]=numbers[i]+weight;
    }
  }
}

std::vector<double> CountTools::getNs(){

  double numberhelper=0.;
  double scalehelper;
  std::vector<double> numbervec;

  //std::cout << '\n' << name << std::endl;

  for(unsigned int i=0; i < numbers.size(); i++){

    scalehelper=scales[i];

    numberhelper=numbers[i]*scalehelper+numberhelper;

    if(i+1 < legends.size() && legends[i] != legends[i+1]){
      numbervec.push_back(numberhelper);
      numberhelper=0;
    }
    else if(i+1 == legends.size()){
      numbervec.push_back(numberhelper);
      numberhelper=0;
    }
  }
  if(numbers.size()>0) return numbervec;
  else{
    std::vector<double> vec;
    vec.push_back(0);
    return vec;
  }

}


std::vector<TString> CountTools::getNames(){


    std::vector<TString> vec;

  for(unsigned int i=0; i < numbers.size(); i++){


    if(i+1 < legends.size() && legends[i] != legends[i+1]){
      vec.push_back(legends[i]);
    }
    else if(i+1 == legends.size()){
      vec.push_back(legends[i]);
    }
  }
  
  return vec;


}
void CountTools::coutNs(){

  double numberhelper=0.;
  double scalehelper;

  std::cout << '\n' << name << std::endl;

  for(unsigned int i=0; i < numbers.size(); i++){

    scalehelper=scales[i];

    numberhelper=numbers[i]*scalehelper+numberhelper;

    if(i+1 < legends.size() && legends[i] != legends[i+1]){
      std::cout << legends[i] << "   " << numberhelper << std::endl;
      numberhelper=0;
    }
    else if(i+1 == legends.size()){
      std::cout << legends[i] << "   " << numberhelper << std::endl;
      numberhelper=0;
    }
  }


}

double CountTools::getNsig(TString nameSig){
  double MCsum=0.;
  double DataSum=0.;


  for(unsigned int i=0; i < numbers.size(); i++){
    if(legends[i]!=nameSig && legends[i] != "data") MCsum=MCsum+numbers[i]*scales[i];
    else if(legends[i] == "data") DataSum=DataSum+numbers[i]*scales[i];
  }

  //std::cout << "\nnumber of Signal Events " << name << " " << DataSum-MCsum << std::endl;
  return  DataSum-MCsum;
}

double CountTools::coutNsig(TString nameSig){
  double MCsum=0.;
  double DataSum=0.;


  for(unsigned int i=0; i < numbers.size(); i++){
    if(legends[i]!=nameSig && legends[i] != "data") MCsum=MCsum+numbers[i]*scales[i];
    else if(legends[i] == "data") DataSum=DataSum+numbers[i]*scales[i];
  }

  std::cout << "\nnumber of Signal Events " << name << " " << DataSum-MCsum << std::endl;
  return  DataSum-MCsum;
}

double CountTools::coutNsig(std::vector<TString> datasets){
  
  double MCsum=0.;
  double DataSum=0.;
  for(unsigned int j=0; j < numbers.size(); j++){
    bool isSignalMC=false;
    for(unsigned int i = 0; i< datasets.size() ; i++){
      if(dataset[j] == datasets[i]) isSignalMC=true;
    }
    if(!isSignalMC && legends[j] != "data") MCsum=MCsum + numbers[j]*scales[j];
    else if(legends[j] == "data")           DataSum=DataSum+numbers[j]*scales[j];


  }

  std::cout << "\nnumber of Signal Events " << name << " " << DataSum-MCsum << std::endl;
  return DataSum-MCsum;;

}

double CountTools::getNsig(std::vector<TString> datasets){

  double MCsum=0.;
  double DataSum=0.;
  for(unsigned int j=0; j < numbers.size(); j++){
    bool isSignalMC=false;
    for(unsigned int i = 0; i< datasets.size() ; i++){
      if(dataset[j] == datasets[i]) isSignalMC=true;
    }
    if(!isSignalMC && legends[j] != "data") MCsum=MCsum + numbers[j]*scales[j];
    else if(legends[j] == "data")           DataSum=DataSum+numbers[j]*scales[j];


  }

  return DataSum-MCsum;;

}


void CountTools::setDataSet(TString mode)
{





  if(mode=="ee"){  DYEntry = "Z^{0} / #gamma* #rightarrow ee";

  dataset.clear();
  scales.clear();
  legends.clear();



  dataset.push_back("ee_200rereco.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("ee_800prompt.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("ee_run161119.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("ee_ttbarsignal.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} signal");

  dataset.push_back("ee_ttbarviatau.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} signal");

  dataset.push_back("ee_ttbarbg.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} background");

  dataset.push_back("ee_singletop_tw.root");
  scales.push_back(Lumi*5.3/814390.);
  legends.push_back("tW");

  dataset.push_back("ee_singleantitop_tw.root");
  scales.push_back(Lumi*5.3/809984.);
  legends.push_back("tW");

  dataset.push_back("ee_wwto2l2nu.root");
  scales.push_back(Lumi*4.51/210667.);
  legends.push_back("VV");

  dataset.push_back("ee_wzto3lnu.root");
  scales.push_back(Lumi*0.61/204725.);
  legends.push_back("VV");

  dataset.push_back("ee_zztoall.root");
  scales.push_back(Lumi*7.4/4187885.);
  legends.push_back("VV");

  dataset.push_back("ee_dytautau1020.root");
  scales.push_back(Lumi*3457./2200000.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("ee_dytautau2050.root");
  scales.push_back(Lumi*1666./2032536.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("ee_dytautau50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("ee_dyee1020.root");
  scales.push_back(Lumi*3457./2121872.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ee");

  dataset.push_back("ee_dyee2050.root");
  scales.push_back(Lumi*1666./2254925.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ee");

  dataset.push_back("ee_dyee50inf.root");
  scales.push_back(Lumi*3048./35101516.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ee");

  dataset.push_back("ee_wtolnu.root");
  scales.push_back(Lumi*31314./56789563.);
  legends.push_back("W #rightarrow ll");

  dataset.push_back("ee_qcdem2030.root");
  scales.push_back(Lumi*2.361E8 * 0.0106 /35729669.);
  legends.push_back("QCD");

  dataset.push_back("ee_qcdem3080.root");
  scales.push_back(Lumi*5.944E7 * 0.061/70392060.);
  legends.push_back("QCD");

  dataset.push_back("ee_qcdem80170.root");
  scales.push_back(Lumi*898200.0*0.159/8150672.);
  legends.push_back("QCD");

  }

  if(mode=="mumu"){

  DYEntry = "Z^{0} / #gamma* #rightarrow #mu#mu";

  dataset.clear();
  scales.clear();
  legends.clear();



  dataset.push_back("mumu_200rereco.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("mumu_800prompt.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("mumu_run161119.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("mumu_ttbarsignal.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} signal");

  dataset.push_back("mumu_ttbarviatau.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} signal");

  dataset.push_back("mumu_ttbarbg.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} background");

  dataset.push_back("mumu_singletop_tw.root");
  scales.push_back(Lumi*5.3/814390);
  legends.push_back("tW");

  dataset.push_back("mumu_singleantitop_tw.root");
  scales.push_back(Lumi*5.3/809984);
  legends.push_back("tW");

  dataset.push_back("mumu_wwto2l2nu.root");
  scales.push_back(Lumi*4.51/210667.);
  legends.push_back("VV");

  dataset.push_back("mumu_wzto3lnu.root");
  scales.push_back(Lumi*0.61/204725.);
  legends.push_back("VV");

  dataset.push_back("mumu_zzto2l2nu.root");
  scales.push_back(Lumi*7.4/4187885);
  legends.push_back("VV");

  dataset.push_back("mumu_dytautau1020.root");
  scales.push_back(Lumi*3457./2200000);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("mumu_dytautau2050.root");
  scales.push_back(Lumi*1666./2032536.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("mumu_dytautau50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("mumu_dymumu1020.root");
  scales.push_back(Lumi*3457./2121872);
  legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu");

  dataset.push_back("mumu_dymumu2050.root");
  scales.push_back(Lumi*1666./2254925);
  legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu");

  dataset.push_back("mumu_dymumu50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu");

  dataset.push_back("mumu_wtolnu.root");
  scales.push_back(Lumi*31314./56789563);
  legends.push_back("W #rightarrow ll");

  dataset.push_back("mumu_qcdmu15.root");
  scales.push_back(Lumi*2.966E8*2.855E-4 /20258122);
  legends.push_back("QCD");
  }

  if(mode == "emu"){


  dataset.clear();
  scales.clear();
  legends.clear();



  dataset.push_back("emu_200rereco.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("emu_800prompt.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("emu_run161119.root");
  scales.push_back(1);
  legends.push_back("data");

  dataset.push_back("emu_ttbarsignal.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} signal");

  dataset.push_back("emu_ttbarviatau.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} signal");

  dataset.push_back("emu_ttbarbg.root");
  scales.push_back(Lumi*169.9/3581947.);
  legends.push_back("t#bar{t} background");

  dataset.push_back("emu_singletop_tw.root");
  scales.push_back(Lumi*5.3/814390.);
  legends.push_back("tW");

  dataset.push_back("emu_singleantitop_tw.root");
  scales.push_back(Lumi*5.3/809984.);
  legends.push_back("tW");

  dataset.push_back("emu_wwto2l2nu.root");
  scales.push_back(Lumi*4.51/210667.);
  legends.push_back("VV");

  dataset.push_back("emu_wzto3lnu.root");
  scales.push_back(Lumi*0.61/204725.);
  legends.push_back("VV");

  dataset.push_back("emu_zztoall.root");
  scales.push_back(Lumi*7.4/4187885.);
  legends.push_back("VV");

  dataset.push_back("emu_dytautau1020.root");
  scales.push_back(Lumi*3457./2200000.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("emu_dytautau2050.root");
  scales.push_back(Lumi*1666./2032536.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("emu_dytautau50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");

  dataset.push_back("emu_dyee1020.root");
  scales.push_back(Lumi*3457./2121872.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");

  dataset.push_back("emu_dyee2050.root");
  scales.push_back(Lumi*1666./2254925.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");

  dataset.push_back("emu_dyee50inf.root");
  scales.push_back(Lumi*3048./35101516.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");

  dataset.push_back("emu_dymumu1020.root");
  scales.push_back(Lumi*3457./2121872);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");

  dataset.push_back("emu_dymumu2050.root");
  scales.push_back(Lumi*1666./2254925);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");

  dataset.push_back("emu_dymumu50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");

  dataset.push_back("emu_wtolnu.root");
  scales.push_back(Lumi*31314./56789563.);
  legends.push_back("W #rightarrow ll");

  dataset.push_back("emu_qcdem2030.root");
  scales.push_back(Lumi*2.361E8 * 0.0106 /35729669.);
  legends.push_back("QCD");

  dataset.push_back("emu_qcdem3080.root");
  scales.push_back(Lumi*5.944E7 * 0.061/70392060.);
  legends.push_back("QCD");

  dataset.push_back("emu_qcdem80170.root");
  scales.push_back(Lumi*898200.0*0.159/8150672.);
  legends.push_back("QCD");

  dataset.push_back("emu_qcdmu15.root");
  scales.push_back(Lumi*2.966E8*2.855E-4 /20258122);
  legends.push_back("QCD");



  }


  numbers.clear();
  for(unsigned int  i=0;  i < dataset.size(); i++){
    numbers.push_back(0);
  }

}

bool CountTools::isData(TString datatype)
{
  bool isdata=false;
  for(unsigned int i=0; i< legends.size(); i++){
    if(datatype == dataset[i]){
      if ("data" == legends[i])       isdata=true;
      break;
    }
  }

  return isdata;
}




#endif

