#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TPad.h"
#include "TPaveText.h"
#include <sstream>
#include "TROOT.h"
#include "TStyle.h"

#include <iomanip>

void smallFitter(){

  bool takeEndcaps=true;
  bool drawdata=false;

  TFile * f = new TFile("EE_Analysis_reweighted.root");

  TH1D *MC;
  TH1D *data;

  if(takeEndcaps) MC = (TH1D*)f->Get("ZpeakMCEC");
  else            MC = (TH1D*)f->Get("ZpeakMCB");
  if(takeEndcaps) data = (TH1D*)f->Get("ZpeakEC");
  else            data = (TH1D*)f->Get("ZpeakB");

  gROOT -> SetStyle("Plain");
  gStyle->SetOptStat(0);
  //MC->Scale(1/MC->GetEntries());
  //data->Scale(1/data->GetEntries());

  data->Rebin();
  MC->SetLineColor(kRed);
  if(takeEndcaps)MC->SetTitle("Z^{0} peak Endcap MC");
  else MC->SetTitle("Z^{0} peak Barrel MC");
  if(takeEndcaps)MC->SetName("Z^{0} peak Endcap MC");
  else MC->SetName("Z^{0} peak Barrel MC");

  MC->GetXaxis()->SetTitle("m_{ee}[GeV]");
  //MC->GetYaxis()->SetTitle("N");

  if(takeEndcaps)data->SetTitle("Z^{0} peak Endcap data");
  else data->SetTitle("Z^{0} peak Barrel data");
  if(takeEndcaps)data->SetName("Z^{0} peak Endcap data");
  else data->SetName("Z^{0} peak Barrel data");
  data->GetXaxis()->SetTitle("m_{ee}[GeV]");
  //data->Draw("same");

  //([3]*(x) +[4])

  TF1 *myfit = new TF1("myfit","[0]*(1-0.2*exp(([1]-x)*([1]-x)/80))*([3]*(x) +[4])/((x*x - [1]*[1])*(x*x - [1]*[1]) + [1]*[1]*[2]*[2])", 83, 100);

  //(exp(([1]-x)*([1]-x)/[5])-[6])*

  myfit->SetParName(1, "Peak");
  myfit->SetParName(2, "width");
  myfit->SetParameter(0, MC->GetEntries());
  myfit->SetParameter(1, 91.5);
  myfit->SetParameter(2, 20);
  myfit->SetParameter(3, 0.01);
  myfit->SetParameter(4, 2);
  //myfit->SetParameter(5, 700);
  myfit->SetParameter(6, 0.1);
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
  peak << std::setprecision (2) << std::fixed <<  (double)myfit->GetParameter(1);
  stringstream error;
  error << std::setprecision (2) << std::fixed << (double)myfit->GetParError(1);



  TPaveText *pt11=new TPaveText(0.0, 0.0, 1.0, 1.0);     //location of the text
  pt11->AddText("Fitting result:");
  pt11->AddText("Peak:  "+(TString)peak.str()+" #pm "+ (TString)error.str()+ " GeV");
  pt11->SetLabel("");
  pt11->SetFillColor(0);
  pt11->SetBorderSize(0.0);
  pt11->Draw(); 

}
