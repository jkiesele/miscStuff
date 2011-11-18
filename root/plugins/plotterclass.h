
#ifndef plotterclass_h
#define plotterclass_h

#include "THStack.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include "TCanvas.h"
#include "TLegend.h"
#include <sstream>
//#include <Int_t.h>




class Plotter {

 public:
  Plotter();
  Plotter(TString, TString, TString, int, double, double, double);
  ~Plotter();
  void   setOptions(TString, TString, TString, int, double, double, double);
  void   setDataSet(std::vector<TString>, std::vector<double>, std::vector<TString>, std::vector<int>, TString);
  void   setDataSet(TString);
  void   fill(TString, float, Double_t);
  void   fill(TString, double, Double_t);
  void   fill(TString, int, Double_t);
  void   fill(TString, std::vector<float>, Double_t);
  void   fill(TString, std::vector<double>, Double_t);
  void   fill(TString, std::vector<int>, Double_t);

  void setStyle(TH1F&, unsigned int);
  void   write();
  void writeRescaleHisto(TString, std::vector<TString> ); //for specific samples
  void writeRescaleHisto(TString);                        //for all MC


 private:
  TString name;
  TString title;
  int bins;
  double rangemin;
  double rangemax;
  std::vector<TString> dataset;
  std::vector<double> scales;
  std::vector<TString> legends;
  std::vector<int> colors;
  double DYScale;
  TString DYEntry;
  TString YAxis;

  std::vector<TH1F> hists;
  bool initialized;


};



Plotter::Plotter()
{
  setDataSet("ee");
  title="defaultTitle";
  name="defaultName";
  bins=10;
  rangemin=0;
  rangemax=3;
  DYScale=1;
  YAxis="N_{events}";
  initialized=false;
  
}

Plotter::Plotter(TString title_, TString name_, TString YAxis_, int bins_, double rangemin_, double rangemax_, double DYScale_)
{
  setDataSet("ee");
  title=title_;
  name=name_;
  bins=bins_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  DYScale=DYScale_;
  YAxis=YAxis_;
  initialized=false;
}

Plotter::~Plotter()
{
}

void Plotter::setOptions(TString title_, TString name_, TString YAxis_, int bins_, double rangemin_, double rangemax_, double DYScale_)
{
  title=title_;
  name=name_;
  bins=bins_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  DYScale=DYScale_;
  YAxis=YAxis_;
}




void Plotter::setDataSet(std::vector<TString> dataset_, std::vector<double> scales_, std::vector<TString> legends_, std::vector<int> colors_, TString DYEntry_)
{
  dataset.clear();
  scales.clear();
  legends.clear();
  colors.clear();
  dataset=dataset_;
  scales=scales_;
  legends=legends_;
  colors=colors_;
  DYEntry=DYEntry_;
}

void Plotter::setDataSet(TString mode)
{


  double Lumi=1141;



  if(mode=="ee"){  DYEntry = "Z^{0} / #gamma* #rightarrow ee";

  dataset.clear();
  scales.clear();
  legends.clear();
  colors.clear();



  dataset.push_back("ee_200rereco.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("ee_800prompt.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("ee_run161119.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("ee_ttbarsignal.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} signal");
  colors.push_back(kRed+1);

  dataset.push_back("ee_ttbarviatau.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} signal");
  colors.push_back(kRed+1);

  dataset.push_back("ee_ttbarbg.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} background");
  colors.push_back(kRed+2);

  dataset.push_back("ee_singletop_tw.root");
  scales.push_back(Lumi*7.87/814390);
  legends.push_back("tW");
  colors.push_back(kMagenta);

  dataset.push_back("ee_singleantitop_tw.root");
  scales.push_back(Lumi*7.87/809984);
  legends.push_back("tW");
  colors.push_back(kMagenta);

  dataset.push_back("ee_wwto2l2nu.root");
  scales.push_back(Lumi*4.51/210667.);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("ee_wzto3lnu.root");
  scales.push_back(Lumi*0.61/204725.);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("ee_zzto2l2nu.root");
  scales.push_back(Lumi*7.4/4187885);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("ee_dytautau1020.root");
  scales.push_back(Lumi*3457./2200000);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("ee_dytautau2050.root");
  scales.push_back(Lumi*1666./2032536.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("ee_dytautau50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("ee_dyee1020.root");
  scales.push_back(Lumi*3457./2121872);
  legends.push_back("Z^{0} / #gamma* #rightarrow ee");
  colors.push_back(kAzure-2);

  dataset.push_back("ee_dyee2050.root");
  scales.push_back(Lumi*1666./2254925);
  legends.push_back("Z^{0} / #gamma* #rightarrow ee");
  colors.push_back(kAzure-2);

  dataset.push_back("ee_dyee50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow ee");
  colors.push_back(kAzure-2);

  dataset.push_back("ee_wtolnu.root");
  scales.push_back(Lumi*31314./56789563);
  legends.push_back("W #rightarrow ll");
  colors.push_back(kGreen-3);

  dataset.push_back("ee_qcdem2030.root");
  scales.push_back(Lumi*2.361E8 * 0.0106 /35729669);
  legends.push_back("QCD");
  colors.push_back(kYellow);

  dataset.push_back("ee_qcdem3080.root");
  scales.push_back(Lumi*5.944E7 * 0.061/70392060);
  legends.push_back("QCD");
  colors.push_back(kYellow);

  dataset.push_back("ee_qcdem80170.root");
  scales.push_back(Lumi*898200.0*0.159/8150672);
  legends.push_back("QCD");
  colors.push_back(kYellow);
  }

  if(mode=="mumu"){

  DYEntry = "Z^{0} / #gamma* #rightarrow #mu#mu";

  dataset.clear();
  scales.clear();
  legends.clear();
  colors.clear();



  dataset.push_back("mumu_200rereco.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("mumu_800prompt.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("mumu_run161119.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("mumu_ttbarsignal.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} signal");
  colors.push_back(kRed+1);

  dataset.push_back("mumu_ttbarviatau.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} signal");
  colors.push_back(kRed+1);

  dataset.push_back("mumu_ttbarbg.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} background");
  colors.push_back(kRed+2);

  dataset.push_back("mumu_singletop_tw.root");
  scales.push_back(Lumi*7.87/814390);
  legends.push_back("tW");
  colors.push_back(kMagenta);

  dataset.push_back("mumu_singleantitop_tw.root");
  scales.push_back(Lumi*7.87/809984);
  legends.push_back("tW");
  colors.push_back(kMagenta);

  dataset.push_back("mumu_wwto2l2nu.root");
  scales.push_back(Lumi*4.51/210667.);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("mumu_wzto3lnu.root");
  scales.push_back(Lumi*0.61/204725.);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("mumu_zzto2l2nu.root");
  scales.push_back(Lumi*7.4/4187885);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("mumu_dytautau1020.root");
  scales.push_back(Lumi*3457./2200000);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("mumu_dytautau2050.root");
  scales.push_back(Lumi*1666./2032536.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("mumu_dytautau50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("mumu_dymumu1020.root");
  scales.push_back(Lumi*3457./2121872);
  legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu");
  colors.push_back(kAzure-2);

  dataset.push_back("mumu_dymumu2050.root");
  scales.push_back(Lumi*1666./2254925);
  legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu");
  colors.push_back(kAzure-2);

  dataset.push_back("mumu_dymumu50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu");
  colors.push_back(kAzure-2);

  dataset.push_back("mumu_wtolnu.root");
  scales.push_back(Lumi*31314./56789563);
  legends.push_back("W #rightarrow ll");
  colors.push_back(kGreen-3);

  dataset.push_back("mumu_qcdmu15.root");
  scales.push_back(Lumi*2.966E8*2.855E-4 /20258122);
  legends.push_back("QCD");
  colors.push_back(kYellow);
  }
  if(mode == "emu"){


  dataset.clear();
  scales.clear();
  legends.clear();
  colors.clear();



  dataset.push_back("emu_200rereco.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("emu_800prompt.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("emu_run161119.root");
  scales.push_back(1);
  legends.push_back("data");
  colors.push_back(kBlack);

  dataset.push_back("emu_ttbarsignal.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} signal");
  colors.push_back(kRed+1);

  dataset.push_back("emu_ttbarviatau.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} signal");
  colors.push_back(kRed+1);

  dataset.push_back("emu_ttbarbg.root");
  scales.push_back(Lumi*157.5/3581947.);
  legends.push_back("t#bar{t} background");
  colors.push_back(kRed+2);

  dataset.push_back("emu_singletop_tw.root");
  scales.push_back(Lumi*5.3/814390.);
  legends.push_back("tW");
  colors.push_back(kMagenta);

  dataset.push_back("emu_singleantitop_tw.root");
  scales.push_back(Lumi*5.3/809984.);
  legends.push_back("tW");
  colors.push_back(kMagenta);

  dataset.push_back("emu_wwto2l2nu.root");
  scales.push_back(Lumi*4.51/210667.);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("emu_wzto3lnu.root");
  scales.push_back(Lumi*0.61/204725.);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("emu_zztoall.root");
  scales.push_back(Lumi*7.4/4187885.);
  legends.push_back("VV");
  colors.push_back(kYellow-10);

  dataset.push_back("emu_dytautau1020.root");
  scales.push_back(Lumi*3457./2200000.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("emu_dytautau2050.root");
  scales.push_back(Lumi*1666./2032536.);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("emu_dytautau50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau");
  colors.push_back(kAzure+8);

  dataset.push_back("emu_dyee1020.root");
  scales.push_back(Lumi*3457./2121872.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");
  colors.push_back(kAzure-2);

  dataset.push_back("emu_dyee2050.root");
  scales.push_back(Lumi*1666./2254925.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");
  colors.push_back(kAzure-2);

  dataset.push_back("emu_dyee50inf.root");
  scales.push_back(Lumi*3048./35101516.);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");
  colors.push_back(kAzure-2);

  dataset.push_back("mumu_dymumu1020.root");
  scales.push_back(Lumi*3457./2121872);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");
  colors.push_back(kAzure-2);

  dataset.push_back("mumu_dymumu2050.root");
  scales.push_back(Lumi*1666./2254925);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");
  colors.push_back(kAzure-2);

  dataset.push_back("mumu_dymumu50inf.root");
  scales.push_back(Lumi*3048./35101516);
  legends.push_back("Z^{0} / #gamma* #rightarrow ll");
  colors.push_back(kAzure-2);

  dataset.push_back("emu_wtolnu.root");
  scales.push_back(Lumi*31314./56789563.);
  legends.push_back("W #rightarrow ll");
  colors.push_back(kGreen-3);

  dataset.push_back("emu_qcdem2030.root");
  scales.push_back(Lumi*2.361E8 * 0.0106 /35729669.);
  legends.push_back("QCD");
  colors.push_back(kYellow);

  dataset.push_back("emu_qcdem3080.root");
  scales.push_back(Lumi*5.944E7 * 0.061/70392060.);
  legends.push_back("QCD");
  colors.push_back(kYellow);

  dataset.push_back("emu_qcdem80170.root");
  scales.push_back(Lumi*898200.0*0.159/8150672.);
  legends.push_back("QCD");
  colors.push_back(kYellow);

  dataset.push_back("emu_qcdmu15.root");
  scales.push_back(Lumi*2.966E8*2.855E-4 /20258122);
  legends.push_back("QCD");
  colors.push_back(kYellow);



  }


}





void Plotter::fill(TString dataType, float no, Double_t weight)
{
  if(!initialized){

    TH1F hist = TH1F(title, name, bins, rangemin, rangemax);

    for(unsigned int i=0; i<dataset.size(); i++){
      hists.push_back(hist);
    }
    initialized=true;
  }

  for(unsigned int j = 0; j < dataset.size(); j++){
    if(dataType == dataset[j]){
      hists[j].Fill(no, weight);
    }
  }

}

void Plotter::fill(TString dataType, int  no, Double_t weight)
{
  fill(dataType, (float) no, weight);
}

void Plotter::fill(TString dataType, double  no, Double_t weight)
{
  fill(dataType, (float) no, weight);
}

void Plotter::fill(TString dataType, std::vector<int> no, Double_t weight)
{
  for(unsigned int i=0; i< no.size(); i++){
  fill(dataType, (float) no[i], weight);
  }
}

void Plotter::fill(TString dataType, std::vector<double> no, Double_t weight)
{
  for(unsigned int i=0; i< no.size(); i++){
  fill(dataType, (float) no[i], weight);
  }
}

void Plotter::fill(TString dataType, std::vector<float> no, Double_t weight)      //// DONT HAND OVER POINTERS!!!
{
  for(unsigned int i=0; i< no.size(); i++){
  fill(dataType, no[i], weight);
  }
}



void Plotter::write() // do scaling, stacking, legending, and write in file MISSING: DY Rescale
{
  //hists[0].Write();
  //c->Write();

  if(initialized){

  TCanvas * c = new TCanvas(title,title);

// fill(dataset[0], -999, 1);

  THStack * stack=  new THStack("def", "def");
  TLegend * leg =  new TLegend(0.70,0.65,0.95,0.90);


  TH1F *drawhists[hists.size()];

  stringstream ss;
  ss << DYScale;
  TString scale;

  scale=(TString)ss.str();

  leg->Clear();
  c->Clear();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  c->SetName(title);
  c->SetTitle(title);

  for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
    drawhists[i]=(TH1F*) hists[i].Clone();
    setStyle(*drawhists[i], i);
    if(legends[i] != "data"){
      drawhists[i]->Scale(scales[i]);
      if(legends[i] == DYEntry) drawhists[i]->Scale(DYScale);
      if(i > 1){
	if(legends[i] != legends[i-1]){
	  if(legends[i] == DYEntry && DYScale != 1) leg->AddEntry(drawhists[i], legends[i]+ "*" + scale,"f");
	  else leg->AddEntry(drawhists[i], legends[i] ,"f");
	}
      }
      stack->Add(drawhists[i]);  
    }
    else{
      if(i==0) leg->AddEntry(drawhists[i], legends[i] ,"pe");
      if(i>0){
	if(legends[i] != legends[i-1]){
	  leg->AddEntry(drawhists[i], legends[i] ,"pe");
	}
	if(legends[i] == legends[0]){
	  drawhists[0]->Add(drawhists[i]);
	}
      }
    }
  }
  drawhists[0]->Draw("e1");
  stack->Draw("same");
  drawhists[0]->Draw("same, e1");
  
  leg->Draw();
  gPad->RedrawAxis();

  c->Write();
  c->Clear();
  leg->Clear();
  delete c;
  delete leg;
  delete stack;
  }
  else std::cout << "Histogram " << title << " not filled during the process." << std::endl;
}

void Plotter::setStyle(TH1F &hist, unsigned int i)
{

  hist.SetFillColor(colors[i]);
  hist.SetLineColor(colors[i]);

  if(legends[i] == "data"){
    hist.SetMarkerStyle(20); 
    hist.SetMarkerSize(1.);
    hist.SetLineWidth(1);
    hist.GetXaxis()->SetLabelFont(42);
    hist.GetXaxis()->SetTitle(name);
    hist.GetXaxis()->SetTitleSize(0.06);
    hist.GetXaxis()->SetTitleOffset(0.7);
    hist.GetYaxis()->SetTitle("N");
    hist.GetYaxis()->SetTitleSize(0.06);
    hist.GetYaxis()->SetTitleOffset(0.7);
  }
}


void Plotter::writeRescaleHisto(TString histname, std::vector<TString> samples)
{

  if(initialized && hists.size()>0){
    TH1F h = hists[0];
    h.SetName(histname);
    h.SetTitle(histname);

    for(int binIter=1; binIter<hists[0].GetNbinsX()+1; binIter++){
      float nMC=0;
      float nData=0;
      float nSample=0;

      for(unsigned int i=0; i<hists.size() ; i++){
	if(legends[i] == "data") nData=nData + scales[i] * hists[i].GetBinContent(binIter);
	else                     nMC=nMC + scales[i] * hists[i].GetBinContent(binIter);
	for(unsigned int j=0; j<samples.size(); j++){
	  if(dataset[i] == samples[j]) nSample=nSample + scales[i] * hists[i].GetBinContent(binIter);
	}
      }
      if(nSample!=0 && 1+(nData-nMC)/nSample > 0) h.SetBinContent(binIter, 1+(nData-nMC)/nSample);
      else           h.SetBinContent(binIter, 1);
      std::cout << nData << " d  " << nMC << " MC   " << nSample << " S  in bin " << binIter << std::endl;
    }
    h.Write();
  }
  else std::cout << "Histogram " << title << " not filled during the process." << std::endl;

}
void Plotter::writeRescaleHisto(TString histname)
{

  if(initialized && hists.size()>0){
    TH1F h = hists[0];
    h.SetName(histname);
    h.SetTitle(histname);

    std::vector<TString> samples=dataset;

    for(int binIter=1; binIter<hists[0].GetNbinsX()+1; binIter++){
      float nMC=0;
      float nData=0;

      for(unsigned int i=0; i<hists.size() ; i++){
	if(legends[i] == "data") nData=nData +  hists[i].GetBinContent(binIter);
	else                     nMC=nMC + scales[i] * hists[i].GetBinContent(binIter);
	
      }
      if(nMC!=0 && nData!=0) h.SetBinContent(binIter, (nData/nMC));
      else                   h.SetBinContent(binIter, 1);
      std::cout << nData << " d  " << nMC << " MC  in bin " << binIter << std::endl;
    }
    h.Write();
  }
  else std::cout << "Histogram " << title << " not filled during the process." << std::endl;

}
// void plotterclass(){ /////just for testing!!!!

//   TFile *f = new TFile("test.root", "RECREATE");

//   Plotter test; 
//   test.setOptions("test", "testname", 10, 0, 10, 1);
//   Plotter test2 = Plotter("test2", "testname2", 10, 0, 10, 1);
//   test.setDataSet("ee");
//   test2.setDataSet("ee");

//   test.fill("ee_200rereco.root", 3,1);
//   test.fill("ee_800prompt.root", 2,1);
//   test.fill("ee_ttbarsignal.root", 2,1);

//   test2.fill("ee_200rereco.root", 5,1);
//   test2.fill("ee_800prompt.root", 6,1);
//   test2.fill("ee_ttbarsignal.root", 2,1);


//   std::cout << "check!" << std::endl;
//   test.write();
//   test2.write();
//   //return 0;

//   f->Close();
//   //delete f;
// }
/*
void drawRatio(const TH1* histNumerator, TH1* histDenominator, const Double_t& ratioMin, const Double_t& ratioMax)
  {
    // this function draws a pad with the ratio of 'histNumerator' and 'histDenominator'
    // the range of the ratio is 'ratioMin' to 'ratioMax'
    // to the systematic variation "sys" of the enumerator "systematicVariation"
    // per default only the gaussian error of the 'histNumerator' is considered:
    // (error(bin i) = sqrt(histNumerator->GetBinContent(i))/histDenominator->GetBinContent(i))
    // if 'err_' is present and its size equals the number of bins in the histos,
    // its valus are considered as error for the ratio
    // NOTE: x Axis is transferred from histDenominator to the bottom of the canvas
    // modified quantities: none
    // used functions: none
    // used enumerators: none
    int verbose=0;

    const std::vector<double> err_=std::vector<double>(0);
    // check that histos have the same binning
    if(histNumerator->GetNbinsX()!=histDenominator->GetNbinsX()){
      std::cout << "error when calling drawRatio - histos have different number of bins" << std::endl;
      return;
    }
    if(verbose>1){
      std::cout << "building ratio plot of " << histNumerator->GetName();
      std::cout << " and " << histDenominator->GetName() << std::endl;
    }
    // create ratio
    TH1F* ratio = (TH1F*)histNumerator->Clone();
    ratio->Divide(histDenominator);
    // calculate error for ratio
    // a) from err_
    if(err_.size()==(unsigned int)histNumerator->GetNbinsX()){
      if(verbose>0) std::cout << "ratio error from vector" << std::endl;
      for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
	ratio->SetBinError(bin, err_[bin-1]);
      }
    }
    else{
      // b) default: only gaussian error of histNumerator
      if(verbose>0) std::cout << "ratio error from statistical error of " << histNumerator->GetName() << " only" << std::endl;
      for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
	ratio->SetBinError(bin, sqrt(histNumerator->GetBinContent(bin))/histDenominator->GetBinContent(bin));
      }
    }
    // get some values from old pad
    //Int_t    logx = gPad->GetLogx();
    //Double_t left = gPad->GetLeftMargin();
    //Double_t right = gPad->GetRightMargin();

    Int_t    logx  = myStyle.GetOptLogx();
    Double_t left  = myStyle.GetPadLeftMargin();
    Double_t right = myStyle.GetPadRightMargin();

    // y:x size ratio for canvas
    double canvAsym = 4./3.;
    // ratio size of pad with plot and pad with ratio
    double ratioSize = 0.36;
    // change old pad
    gPad->SetBottomMargin(ratioSize);
    gPad->SetRightMargin(right);
    gPad->SetLeftMargin(left);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(0);
    gPad->SetFillColor(10);
    // create new pad for ratio plot
    TPad *rPad;
    rPad = new TPad("rPad","",0,0,1,ratioSize+0.001);

    rPad->SetFillStyle(0);
    rPad->SetFillColor(0);
    rPad->SetBorderSize(0);
    rPad->SetBorderMode(0);
    rPad->Draw();
    rPad->cd();
    rPad->SetLogy(0);
    rPad->SetLogx(logx);
    rPad->SetTicky(1);
    // configure ratio plot
    double scaleFactor = 1./(canvAsym*ratioSize);
    ratio->SetStats(kFALSE);
    ratio->SetTitle("");
    ratio->SetMaximum(ratioMax);
    ratio->SetMinimum(ratioMin);
    ratio->SetLineWidth(1);
    // configure axis of ratio plot
    ratio->GetXaxis()->SetTitleSize(histDenominator->GetXaxis()->GetTitleSize()*scaleFactor*1.3);
    ratio->GetXaxis()->SetTitleOffset(histDenominator->GetXaxis()->GetTitleOffset()*0.9);
    ratio->GetXaxis()->SetLabelSize(histDenominator->GetXaxis()->GetLabelSize()*scaleFactor*1.4);
    ratio->GetXaxis()->SetTitle(histDenominator->GetXaxis()->GetTitle());
    ratio->GetXaxis()->SetNdivisions(histDenominator->GetNdivisions());
    ratio->GetYaxis()->CenterTitle();
    ratio->GetYaxis()->SetTitle("#frac{N_{data}}{N_{MC}}");
    ratio->GetYaxis()->SetTitleSize(histDenominator->GetYaxis()->GetTitleSize()*scaleFactor);
    ratio->GetYaxis()->SetTitleOffset(histDenominator->GetYaxis()->GetTitleOffset()/scaleFactor);
    ratio->GetYaxis()->SetLabelSize(histDenominator->GetYaxis()->GetLabelSize()*scaleFactor);
    ratio->GetYaxis()->SetLabelOffset(histDenominator->GetYaxis()->GetLabelOffset()*3.3);
    ratio->GetYaxis()->SetTickLength(0.03);
    ratio->GetYaxis()->SetNdivisions(505);
    ratio->GetXaxis()->SetRange(histDenominator->GetXaxis()->GetFirst(), histDenominator->GetXaxis()->GetLast());
    // delete axis of initial plot
    histDenominator->GetXaxis()->SetLabelSize(0);
    histDenominator->GetXaxis()->SetTitleSize(0);
    // draw ratio plot
    ratio->DrawClone("p e X0");
    ratio->SetMarkerSize(1.2);
    ratio->DrawClone("p e X0 same");
    rPad->SetTopMargin(0.0);
    rPad->SetBottomMargin(0.15*scaleFactor);
    rPad->SetRightMargin(right);
    gPad->SetLeftMargin(left);
    gPad->RedrawAxis();
    // draw grid
    rPad->SetGrid(1,1);

    // draw a horizontal lines on a given histogram
    // a) at 1
    Double_t xmin = ratio->GetXaxis()->GetXmin();
    Double_t xmax = ratio->GetXaxis()->GetXmax();
    TString height = ""; height += 1;
    TF1 *f = new TF1("f", height, xmin, xmax);
    f->SetLineStyle(1);
    f->SetLineWidth(1);
    f->SetLineColor(kBlack);
    f->Draw("L same");
    // b) at upper end of ratio pad
    TString height2 = ""; height2 += ratioMax;
    TF1 *f2 = new TF1("f2", height2, xmin, xmax);
    f2->SetLineStyle(1);
    f2->SetLineWidth(1);
    f2->SetLineColor(kBlack);
    f2->Draw("L same");
  }

*/

#endif
