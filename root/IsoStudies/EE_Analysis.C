#define EE_Analysis_cxx


#include "EE_Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include "TLorentzVector.h"
#include "plugins/rescaleFunctions.h"
#include "ratio.h"
//#include "gROOT.h"

void EE_Analysis::Begin(TTree * /*tree*/)
{
  totalEventCount=0;
   TString option = GetOption();

   ///init counters
   TString dataset="ee";

  const Int_t nbinseta=3;
  const Int_t nbinspt=4;
  const Double_t binseta[nbinseta+1] = {0, 1.2, 2.4, 4.8};
  const Double_t binspt[nbinspt+1] = {20, 30,  40, 50, 150};

  IsoStudiesData0 = new TH1D("IsoStudiesData0","IsoStudiesData0", nbinspt, binspt);
  IsoStudiesData1 = new TH1D("IsoStudiesData1","IsoStudiesData1", nbinspt, binspt);
  IsoStudiesZMC0 = new TH1D("IsoStudiesZMC0","IsoStudiesZMC0", nbinspt, binspt);
  IsoStudiesZMC1 = new TH1D("IsoStudiesZMC1","IsoStudiesZMC1", nbinspt, binspt);
  IsoStudiesttMC0 = new TH1D("IsoStudiesttMC0","IsoStudiesttMC0", nbinspt, binspt);
  IsoStudiesttMC1 = new TH1D("IsoStudiesttMC1","IsoStudiesttMC1", nbinspt, binspt);


   c_step0.setDataSet(dataset);
 


}

void EE_Analysis::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t EE_Analysis::Process(Long64_t entry)
{

  GetAllBranches(entry);


  totalEventCount++;
  double totalevents=8.125e+06;
  if((int)(100*totalEventCount)%(int)(totalevents) ==0) std::cout << totalEventCount << "\t\tEvents processed \tca. " << (int) totalEventCount/totalevents* 100 << "%" << std::endl;

   TString DataType;  
  DataType="def";
  DataType=(TString)*(dataType->begin());

  bool isData=c_step0.isData(DataType);

 

  bool b_step1=false; 
  bool b_step2=false; 
  bool b_step3=false; 
  bool b_step4=false; 
  bool b_step5=false; 
  bool b_step6=false; 
  bool b_step7=false; 
  bool b_step8=false;
  bool b_step9=false;

  //loop over leptons

  bool rescale=true;

  float isocutmuons = 0.2;//0.3;//0.2; //0.2;  //0.2;//0.2; pf // 0.15 comb
  float isocutelecs = 0.17; //0.3;//0.17;//0.17; //0.17; //0.17;//0.17;
  bool pfIso = true;
  float leptontype = -1; // 1 muon -1 electron
  TString dataset;
  if(leptontype==1) dataset="mumu";
  else dataset = "ee";
  bool oppocharge=true;
  float globalElecEnergyScale=1.0;
  //if(DataType == "ee_200rereco.root" || DataType == "ee_800prompt.root" ) globalElecEnergyScale=1.005; //just play around

  bool probefirst=true;  // Also set switch down in terminate!!!

  double isocut;
  if(leptontype == 1) isocut = isocutmuons;
  else                isocut = isocutelecs;

  float tempiso=100;

  std::vector<float> VLepPt;
  std::vector<float> VLepEta, VLepPhi, VLepE, VLepPx, VLepPy, VLepPz, VLepPfIso, VLepCombIso;
  std::vector<int> VLepQ, VLepType;


  //h_lepMulti0.fill(DataType, (int)lepPt->size(), PUweight);
  
  int CheckCharge=100;
  if(probefirst){
    CheckCharge=*(lepQ->begin());                // take first leading lepton
    VLepPt.push_back(*(lepPt->begin()));
    VLepEta.push_back(*(lepEta->begin()));
    VLepCombIso.push_back(*(lepCombIso->begin()));
    VLepPfIso.push_back(*(lepPfIso->begin()));
    VLepE.push_back(*(lepE->begin()));
    VLepPx.push_back(*(lepPx->begin()));
    VLepPy.push_back(*(lepPy->begin()));
    VLepPz.push_back(*(lepPz->begin()));
    VLepQ.push_back(*(lepQ->begin()));
    VLepType.push_back(*(lepType->begin()));
    VLepPhi.push_back(*(lepPhi->begin()));
    //new
  }

  int k=0;
  for(unsigned int i=0; i<lepPt->size(); i++){ //isocut and chargecut -> builds leptonvectors start with the second leading pt lepton!!!
    if(pfIso) tempiso=*(lepPfIso->begin()+i);
    else tempiso=*(lepCombIso->begin()+i);
    k++;

    if(tempiso < isocutmuons && *(lepType->begin()+i) == 1 && *(lepQ->begin()+i) != CheckCharge){ //
      VLepPt.push_back(*(lepPt->begin()+i));
      VLepEta.push_back(*(lepEta->begin()+i));
      VLepCombIso.push_back(*(lepCombIso->begin()+i));
      VLepPfIso.push_back(*(lepPfIso->begin()+i));
      VLepE.push_back(*(lepE->begin()+i));
      VLepPx.push_back(*(lepPx->begin()+i));
      VLepPy.push_back(*(lepPy->begin()+i));
      VLepPz.push_back(*(lepPz->begin()+i));
      VLepQ.push_back(*(lepQ->begin()+i));
      VLepType.push_back(*(lepType->begin()+i));
      VLepPhi.push_back(*(lepPhi->begin()+i));
      CheckCharge=VLepQ[0]; //new
      break; //new
    }
    else if(tempiso < isocutelecs && *(lepType->begin()+i) == -1 && *(lepQ->begin()+i) != CheckCharge){ //
      VLepPt.push_back(*(lepPt->begin()+i)*globalElecEnergyScale);
      VLepEta.push_back(*(lepEta->begin()+i));
      VLepCombIso.push_back(*(lepCombIso->begin()+i));
      VLepPfIso.push_back(*(lepPfIso->begin()+i));
      VLepE.push_back(*(lepE->begin()+i)*globalElecEnergyScale);
      VLepPx.push_back(*(lepPx->begin()+i)*globalElecEnergyScale);
      VLepPy.push_back(*(lepPy->begin()+i)*globalElecEnergyScale);
      VLepPz.push_back(*(lepPz->begin()+i)*globalElecEnergyScale);
      VLepQ.push_back(*(lepQ->begin()+i));
      VLepType.push_back(*(lepType->begin()+i));
      VLepPhi.push_back(*(lepPhi->begin()+i));
      CheckCharge=VLepQ[0]; //new
      break; //new
    }
    //if(VLepType.size()==1 && oppocharge) CheckCharge=VLepQ[0];
    //else if(VLepType.size()==1 && !oppocharge) CheckCharge= - VLepQ[0];
  }

  //second leading probe lep
  if(!probefirst){
    for(unsigned int i=0; i<lepPt->size(); i++){ //isocut and chargecut -> builds leptonvectors start with the second leading pt lepton!!!
      if(pfIso) tempiso=*(lepPfIso->begin()+i);
      else tempiso=*(lepCombIso->begin()+i);
      k++;

      if( *(lepType->begin()+i) == 1 && *(lepQ->begin()+i) != CheckCharge){ //
	VLepPt.push_back(*(lepPt->begin()+i));
	VLepEta.push_back(*(lepEta->begin()+i));
	VLepCombIso.push_back(*(lepCombIso->begin()+i));
	VLepPfIso.push_back(*(lepPfIso->begin()+i));
	VLepE.push_back(*(lepE->begin()+i));
	VLepPx.push_back(*(lepPx->begin()+i));
	VLepPy.push_back(*(lepPy->begin()+i));
	VLepPz.push_back(*(lepPz->begin()+i));
	VLepQ.push_back(*(lepQ->begin()+i));
	VLepType.push_back(*(lepType->begin()+i));
	VLepPhi.push_back(*(lepPhi->begin()+i));
	break; //new
      }
      else if( *(lepType->begin()+i) == -1 && *(lepQ->begin()+i) != CheckCharge){ //
	VLepPt.push_back(*(lepPt->begin()+i)*globalElecEnergyScale);
	VLepEta.push_back(*(lepEta->begin()+i));
	VLepCombIso.push_back(*(lepCombIso->begin()+i));
	VLepPfIso.push_back(*(lepPfIso->begin()+i));
	VLepE.push_back(*(lepE->begin()+i)*globalElecEnergyScale);
	VLepPx.push_back(*(lepPx->begin()+i)*globalElecEnergyScale);
	VLepPy.push_back(*(lepPy->begin()+i)*globalElecEnergyScale);
	VLepPz.push_back(*(lepPz->begin()+i)*globalElecEnergyScale);
	VLepQ.push_back(*(lepQ->begin()+i));
	VLepType.push_back(*(lepType->begin()+i));
	VLepPhi.push_back(*(lepPhi->begin()+i));
	break; //new
      }
    }

  }




  double dimass=-1;

  if(VLepPt.size() > 1){  //two isolated leptons create dimass out of highest pt pair

    TLorentzVector diLepVector = TLorentzVector(VLepPx[0] + VLepPx[1], VLepPy[0] + VLepPy[1], VLepPz[0] + VLepPz[1], VLepE[0] + VLepE[1]);

    dimass=diLepVector.M();

    b_step1=true;
    testcounter++;
      
    if(VLepType[0] == leptontype &&  VLepType[1] == leptontype) b_step2=true;
    if(dimass > 12)                     b_step3=true;
    if((dimass < 76.0 || dimass > 106.0))     b_step4=true; //dimass > 50 && 
    if(jetMulti>0)                      b_step5=true;
    if(jetMulti>1)                      b_step6=true;
    if(*(metEt->begin()) > 30)          b_step7=true;

  }

  if(b_step1 && b_step2 && b_step3 && !b_step4 && b_step6){     // select Z peak

    int lepno;
    if(probefirst) lepno=0;
    else lepno=1;

    if(isData) IsoStudiesData0->Fill(VLepPt[lepno]);      // Fill histo pt dependent with first lepton
    if(DataType== dataset+"_dy"+dataset+"50inf.root") IsoStudiesZMC0->Fill(VLepPt[lepno]); 
    if(DataType== dataset+"_ttbarsignal.root" || DataType== dataset+" _ttbarviatau.root")   IsoStudiesttMC0->Fill(VLepPt[lepno]);         //Fill pt dep for Z MC



    if(VLepPfIso[lepno]<isocut){ //new
      if(isData) IsoStudiesData1->Fill(VLepPt[lepno]);
      if(DataType== dataset+"_dy"+dataset+"50inf.root") IsoStudiesZMC1->Fill(VLepPt[lepno]);  
    if(DataType== dataset+"_ttbarsignal.root" || DataType== dataset+" _ttbarviatau.root")   IsoStudiesttMC1->Fill(VLepPt[lepno]);
       
    }

  }



  double btagWPM=3.3;
  double btagWP=1.7;
  int btagmultiM=0;
  int btagmulti=0;

  for(std::vector<double>::const_iterator ajetTCHE = jetBTagTCHE->begin(); ajetTCHE < jetBTagTCHE->end(); ajetTCHE++){
    if(*ajetTCHE > btagWPM) btagmultiM++;
    if(*ajetTCHE > btagWP) btagmulti++;
  }

  if(btagmulti > 0) b_step8=true;
  if(btagmultiM > 0) b_step9=true;









   return kTRUE;
}

void EE_Analysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void EE_Analysis::Terminate()
{

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  TH1D *DataEff;
  DataEff = (TH1D*)IsoStudiesData0->Clone();
  DataEff->SetTitle("DataIsoEff");
  DataEff->SetName("DataIsoEff");

  for(int bin=1; bin<IsoStudiesData0->GetNbinsX()+1; bin++){
    double eff=IsoStudiesData1->GetBinContent(bin)/IsoStudiesData0->GetBinContent(bin);
    double binerr=sqrt((1-eff)/IsoStudiesData1->GetBinContent(bin));

    DataEff->SetBinContent(bin, eff);
    DataEff->SetBinError(bin, binerr);

  }

  TH1D *ZMCEff;
  ZMCEff = (TH1D*)IsoStudiesZMC0->Clone();
  ZMCEff->SetTitle("ZMCIsoEff");
  ZMCEff->SetName("ZMCIsoEff");
  for(int bin=1; bin<IsoStudiesZMC0->GetNbinsX()+1; bin++){
    double eff=IsoStudiesZMC1->GetBinContent(bin)/IsoStudiesZMC0->GetBinContent(bin);
    double binerr=sqrt((1-eff)/IsoStudiesZMC1->GetBinContent(bin));

    ZMCEff->SetBinContent(bin, eff);
    ZMCEff->SetBinError(bin, binerr);

  }



  TH1D *ttMCEff;
  ttMCEff = (TH1D*)IsoStudiesttMC0->Clone();
  ttMCEff->SetTitle("ttMCIsoEff");
  ttMCEff->SetName("ttMCIsoEff");

  for(int bin=1; bin<IsoStudiesttMC0->GetNbinsX()+1; bin++){
    double eff=IsoStudiesttMC1->GetBinContent(bin)/IsoStudiesttMC0->GetBinContent(bin);
    double binerr=sqrt((1-eff)/IsoStudiesttMC1->GetBinContent(bin));

    ttMCEff->SetBinContent(bin, eff);
    ttMCEff->SetBinError(bin, binerr);

  }

  bool probefirst=true;

  TH1D ratioh = ratiohisto(DataEff, ZMCEff);
  ratioh.SetName("Ratio");
  ratioh.SetTitle("Ratio");

  TCanvas *c = new TCanvas("Isolation Eff", "Isolation Eff");
  c->cd();

  TString lep;

  TFile *f;
  if(probefirst)lep= "1stLep";
  else          lep= "2ndLep"; 

  TString add="2jets";


  f = new TFile("EE_Analysis_IsoStudies_"+lep+add+".root","RECREATE");

  IsoStudiesData1->Write();
  IsoStudiesData0->Write();
  DataEff->Write();
  DataEff->Draw();
  c->Print("eps/EEDataEff"+lep+add+".eps");
  IsoStudiesZMC0->Write();
  IsoStudiesZMC1->Write();
  ZMCEff->Write();
  ZMCEff->Draw();
  c->Print("eps/EEMCZEff"+lep+add+".eps");
  IsoStudiesttMC0->Write();
  IsoStudiesttMC1->Write();
  ttMCEff->Write();
  ratioh.Write();
  ratioh.Draw();
  c->Print("eps/EERatio"+lep+add+".eps");


  DataEff->Draw();
  ZMCEff->SetLineColor(kRed);
  ZMCEff->Draw("same");
  c->Print("eps/EEDataMc"+lep+add+".eps");
  c->Write();

  f->Close();





//   TFile *f2 = new TFile("EE_Analysis_Rescaler.root","UPDATE");

// //   h_vertMulti3.writeRescaleHisto("vertMulti3R");
// //   h_vertMulti3a.writeRescaleHisto("vertMulti3aR");

//   h_diMass3.writeRescaleHisto("dimass3R", samples);

//    f2->Close();

}
