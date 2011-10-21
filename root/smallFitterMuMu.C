#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPad.h"
#include "TPaveText.h"
#include <sstream>
#include "TROOT.h"
#include "TStyle.h"

#include <iomanip>

void smallFitterMuMu(){

  bool drawdata=true;

  double rangemin=85;
  double rangemax=97;

  TFile * f = new TFile("MuMu_Analysis.root");

  TH1D *MC;
  TH1D *data;

  MC = (TH1D*)f->Get("dimassMC");
  data = (TH1D*)f->Get("dimassData");

  gROOT -> SetStyle("Plain");
  gStyle->SetOptStat(0);
  //MC->Scale(1/MC->GetEntries());
  //data->Scale(1/data->GetEntries());

  data->Rebin();
  MC->SetLineColor(kRed);
 MC->SetTitle("Z^{0} peak MC");
 MC->SetName("Z^{0} peak MC");

  MC->GetXaxis()->SetTitle("m_{#mu#mu}[GeV]");
  //MC->GetYaxis()->SetTitle("N");

   data->SetTitle("Z^{0} peak data");
   data->SetName("Z^{0} peak data");
  data->GetXaxis()->SetTitle("m_{#mu#mu}[GeV]");
  //data->Draw("same");

  //([3]*(x) +[4]) //([3]*(x-[1]))

  TF1 *myfit = new TF1("myfit","[0]*(1-0.3*exp(([1]-x)*([1]-x)/[5]))*((x-[1])*[3]+1)/((x*x - [1]*[1])*(x*x - [1]*[1]) + [1]*[1]*[2]*[2])", rangemin, rangemax);
  //TF1 *myfit = new TF1("myfit","[0]*(1-0.4*exp(([1]-x)*([1]-x)/80))*([3]*(x) +[4])/((x*x - [1]*[1])*(x*x - [1]*[1]) + [1]*[1]*[2]*[2])", 88, 94);

  //(exp(([1]-x)*([1]-x)/[5])-[6])*

  double entries = MC->GetEntries();
  if(drawdata) entries = data->GetEntries();

  myfit->SetParName(1, "Peak");
  myfit->SetParName(2, "width");
  myfit->SetParameter(0, entries);
  myfit->SetParameter(1, 91.1);
  myfit->SetParLimits(1, 89, 94);
  myfit->SetParameter(2, 10);
  myfit->SetParLimits(2, 4, 20);
  myfit->SetParameter(3, -0.1);
  // myfit->SetParLimits(3, -1, 0);
  //myfit->SetParameter(4, entries);
  myfit->SetParameter(5, 80);
  myfit->SetParLimits(5, 10, 100);
  myfit->SetParameter(6, 0.5);
  myfit->SetParLimits(6, 0, 0.7);
  std::cout << "MC Parameter" << MC->GetName() << std::endl;
  if(!drawdata){
    MC->Fit("myfit", "R");
    MC->SetDrawOption("e1");
  }
  else{
  myfit->SetParameter(0, data->GetEntries());

  data->SetDrawOption("e1");
  std::cout << "data Parameter" << data->GetName() << std::endl;
  data->Fit("myfit", "R");
  data->SetDrawOption("e1");

  std::cout << myfit->GetParError(1) << std::endl;
  }
TPad *p1=new TPad("p1","Fit params",0.3, 0.2, 0.7, 0.4, 0, 1);  //sets the area for the text box
 p1->Draw();
 p1->cd();

  stringstream peak;
  peak << std::setprecision (3) << std::fixed <<  (double)myfit->GetParameter(1);
  stringstream error;
  error << std::setprecision (3) << std::fixed << (double)myfit->GetParError(1);



  TPaveText *pt11=new TPaveText(0.0, 0.0, 1.0, 1.0);     //location of the text
  pt11->AddText("Fitting result:");
  pt11->AddText("Peak:  "+(TString)peak.str()+" #pm "+ (TString)error.str()+ " GeV");
  pt11->SetLabel("");
  pt11->SetFillColor(0);
  pt11->SetBorderSize(0.0);
  pt11->Draw(); 

  std::cout << "Correction factor compared to PDG Zmass (91.1876GeV) " << 91.1876/myfit->GetParameter(1) << " +- " << myfit->GetParError(1) / myfit->GetParameter(1) *(91.1876/myfit->GetParameter(1)) << std::endl;

}
