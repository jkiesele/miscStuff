#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include <iostream>
#include <vector>








TH1D  readin(TString filename, TString histname)
{
  TFile f = TFile(filename);
  TH1D  h = *((TH1D*)(f.Get(histname)));
  //delete f;
  return h;
}
TH1D  readinErrorsUp(TString filename, TString histname)
{
  TFile f = TFile(filename);
  TH1D  h1 = *((TH1D*)(f.Get(histname)));
  TH1D  h2 = *((TH1D*)(f.Get(histname)));

  for(int i=1; i<h1.GetNbinsX()+1; i++){
    h2.SetBinContent(i, h1.GetBinContent(i) + h1.GetBinError(i));
  }

  //delete f;
  return h2;
}
TH1D  readinErrorsDown(TString filename, TString histname)
{
  TFile f = TFile(filename);
  TH1D  h1 = *((TH1D*)(f.Get(histname)));
  TH1D  h2 = *((TH1D*)(f.Get(histname)));

  for(int i=1; i<h1.GetNbinsX()+1; i++){
    h2.SetBinContent(i, h1.GetBinContent(i) - h1.GetBinError(i));
  }

  //delete f;
  return h2;
}

TH2D  readin2D(TString filename, TString histname)
{
  TFile f = TFile(filename);
  TH2D  h = *((TH2D*)(f.Get(histname)));
  //delete f;
  return h;
}

double reweightWeight(TH1D& h, double var)
{
  double weight=1;
  int bin=0;
  if(h.FindBin(var)){
    bin=h.FindBin(var);
    weight=(double)h.GetBinContent(bin);
  }
  
  return weight;

}

double reweightWeight(TH2D& h, double var1, double var2)
{
  float weight=1;
  int bin=0;
  if(h.FindBin(var1, var2)){
    bin=h.FindBin(var1, var2);
    weight=(double)h.GetBinContent(bin);
  }
  
  return weight;

}
// void test()
// {

// TH1D * h2 = readin("../dimuon_Analysis_resclaer.root", "dimass3Rescale");
//  h2->Draw();

 

//  std::cout << reweightWeight(h2, 70) <<std::endl;

// }
