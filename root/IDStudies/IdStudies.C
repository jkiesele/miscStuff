#define IdStudies_cxx


#include "IdStudies.h"
#include <TH2.h>
#include <TStyle.h>
#include "TCanvas.h"


void IdStudies::Begin(TTree * /*tree*/)
{
  

   TString option = GetOption();

}

void IdStudies::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

   totalcount=0;
   const int nptbins=4;
   double ptbins [nptbins+1] = {20, 30, 40, 50, 150};
   const    int netabins=3;
    double etabins [netabins+1] = {-2.4, -1, 1, 2.4};

   probePt = new TH1D("probePt","probePt", nptbins, ptbins);
   probePtPassed = new TH1D("probePtPassed","probePtPassed", nptbins, ptbins);
   probeEta  = new TH1D("probeEta","probeEta", netabins, etabins);
   probeEtaPassed  = new TH1D("probeEtaPassed","probeEtaPassed", netabins, etabins);
   PtDist = new TH1D("PtDist","PtDist", nptbins, ptbins);
   EtaDist = new TH1D("EtaDist","EtaDist", netabins, etabins);

   dimDist = new TH2D("dimDist","dimDist", netabins, etabins,  nptbins, ptbins);
   dimDistPassed = new TH2D("dimDistPassed","dimDistPassed", netabins, etabins,  nptbins, ptbins);

   MCprobePt = new TH1D("MCprobePt","MCprobePt", nptbins, ptbins);
   MCprobePtPassed = new TH1D("MCprobePtPassed","MCprobePtPassed", nptbins, ptbins);
   MCprobeEta  = new TH1D("MCprobeEta","MCprobeEta", netabins, etabins);
   MCprobeEtaPassed  = new TH1D("MCprobeEtaPassed","MCprobeEtaPassed", netabins, etabins);
   MCPtDist = new TH1D("MCPtDist","MCPtDist", nptbins, ptbins);
   MCEtaDist = new TH1D("MCEtaDist","MCEtaDist", netabins, etabins);

   MCdimDist = new TH2D("MCdimDist","MCdimDist", netabins, etabins,  nptbins, ptbins);
   MCdimDistPassed = new TH2D("MCdimDistPassed","MCdimDistPassed", netabins, etabins,  nptbins, ptbins);

   probed=0;
   passed=0;
   MCprobed=0;
   MCpassed=0;




  probefirst=true;
  leptontype = -1;


}

Bool_t IdStudies::Process(Long64_t entry)
{
   GetAllBranches(entry);
  totalcount++;

  if((100* totalcount) % 6310000 ==0)std::cout << "events: " << 100*totalcount/6310000 << " %"<< std::endl;

  std::vector<double> VLepPt, VLepEta, VLepPhi, VLepE, VLepPx, VLepPy, VLepPz, VLepPfIso, VLepCombIso;
  std::vector<double> NCVLepPt, NCVLepEta, NCVLepPhi, NCVLepE, NCVLepPx, NCVLepPy, NCVLepPz, NCVLepPfIso, NCVLepCombIso;
  std::vector<int> VLepQ, VLepType;
  std::vector<bool> VLepPassed;

  std::vector<int> NCVLepQ, NCVLepType;

  TString DataType;  
  DataType="def";
  DataType=(TString)*(dataType->begin());


  //Fill first nocutLepton all vectors size minsize=2

  int CheckCharge = 0;
  if(leptontype==1) add="mumu";
  else add="ee";

  if(lepPt->size()>1){
    if(probefirst){
      VLepPt.push_back(*(lepPt->begin()));
      VLepEta.push_back(*(lepEta->begin()));
      VLepE.push_back(*(lepE->begin()));
      VLepPx.push_back(*(lepPx->begin()));
      VLepPy.push_back(*(lepPy->begin()));
      VLepPz.push_back(*(lepPz->begin()));
      VLepQ.push_back(*(lepQ->begin()));
      VLepType.push_back(*(lepType->begin()));
      VLepPhi.push_back(*(lepPhi->begin()));
      VLepPassed.push_back(*(passedId->begin()));
      CheckCharge=*(lepQ->begin());
    
      for(unsigned int i=0; i<lepPt->size(); i++){ // Fill oppo charged highest pt passed
	if( *(lepQ->begin()+i) != CheckCharge && *(passedId->begin()+i)){
	  VLepPt.push_back(*(lepPt->begin()+i));
	  VLepEta.push_back(*(lepEta->begin()+i));
	  VLepE.push_back(*(lepE->begin()+i));
	  VLepPx.push_back(*(lepPx->begin()+i));
	  VLepPy.push_back(*(lepPy->begin()+i));
	  VLepPz.push_back(*(lepPz->begin()+i));
	  VLepQ.push_back(*(lepQ->begin()+i));
	  VLepType.push_back(*(lepType->begin()+i));
	  VLepPhi.push_back(*(lepPhi->begin()+i));
	  VLepPassed.push_back(*(passedId->begin()+i));
	  CheckCharge=*(lepQ->begin()+i);
	  break;
	}
      }
    }
    else{
      for(unsigned int i=0; i<lepPt->size(); i++){ // Fill  highest pt passed
	if( *(lepQ->begin()+i) != CheckCharge && *(passedId->begin()+i)){
	  VLepPt.push_back(*(lepPt->begin()+i));
	  VLepEta.push_back(*(lepEta->begin()+i));
	  VLepE.push_back(*(lepE->begin()+i));
	  VLepPx.push_back(*(lepPx->begin()+i));
	  VLepPy.push_back(*(lepPy->begin()+i));
	  VLepPz.push_back(*(lepPz->begin()+i));
	  VLepQ.push_back(*(lepQ->begin()+i));
	  VLepType.push_back(*(lepType->begin()+i));
	  VLepPhi.push_back(*(lepPhi->begin()+i));
	  VLepPassed.push_back(*(passedId->begin()+i));
	  CheckCharge=*(lepQ->begin()+i);
	  break;
	}
      }
      for(unsigned int i=0; i<lepPt->size(); i++){ // Fill  highest pt oppo charged
	if( *(lepQ->begin()+i) != CheckCharge ){
	  VLepPt.push_back(*(lepPt->begin()+i));
	  VLepEta.push_back(*(lepEta->begin()+i));
	  VLepE.push_back(*(lepE->begin()+i));
	  VLepPx.push_back(*(lepPx->begin()+i));
	  VLepPy.push_back(*(lepPy->begin()+i));
	  VLepPz.push_back(*(lepPz->begin()+i));
	  VLepQ.push_back(*(lepQ->begin()+i));
	  VLepType.push_back(*(lepType->begin()+i));
	  VLepPhi.push_back(*(lepPhi->begin()+i));
	  VLepPassed.push_back(*(passedId->begin()+i));
	  CheckCharge=*(lepQ->begin()+i);
	  break;
	}
      }
    }
  }

  int probenumber=0;
  int tagnumber=1;
  if(!probefirst){ 
    probenumber=1;
    tagnumber=0;
  }

  double dimass=-1;
  if(VLepPt.size()>1){
    TLorentzVector diLepVector = TLorentzVector(VLepPx[0] + VLepPx[1], 
						VLepPy[0] + VLepPy[1], 
						VLepPz[0] + VLepPz[1], 
						VLepE[0] + VLepE[1]);
    dimass=diLepVector.M();
  }
  if(dimass > 76 && dimass < 106 
     && VLepType[0] == leptontype 
     && VLepType[1] == leptontype ){ 

    if(DataType == add+"_200rereco.root" 
       || DataType == add+"_800prompt.root" 
       || DataType == add+"_run161119.root"){

      probePt->Fill(VLepPt[probenumber], 1);
      probeEta->Fill(VLepEta[probenumber], 1);
      dimDist->Fill(VLepEta[probenumber],VLepPt[probenumber],1);
      probed++;

      if(VLepPassed[probenumber]){
	probePtPassed->Fill(VLepPt[probenumber], 1);
	probeEtaPassed->Fill(VLepEta[probenumber], 1);
	dimDistPassed->Fill(VLepEta[probenumber],VLepPt[probenumber],1);
	passed++;
      }
    }
    else if (DataType == add+"_Z"+add+".root"
	     || DataType == add+"_ttbarsignal.root"
	     || DataType == add+"_ttbarviatau.root"){ //MC

      if(DataType == add+"_ttbarsignal.root"
	 || DataType == add+"_ttbarviatau.root") PUweight=PUweight * 2.;

      MCprobePt->Fill(VLepPt[probenumber], PUweight);
      MCprobeEta->Fill(VLepEta[probenumber], PUweight);
      MCdimDist->Fill(VLepEta[probenumber],VLepPt[probenumber],PUweight);
      MCprobed++;
      if(VLepPassed[probenumber]){
	MCprobePtPassed->Fill(VLepPt[probenumber], PUweight);
	MCprobeEtaPassed->Fill(VLepEta[probenumber], PUweight);
	MCdimDistPassed->Fill(VLepEta[probenumber],VLepPt[probenumber],PUweight);
	MCpassed++;
      }
    }
  }

   return kTRUE;
}

void IdStudies::SlaveTerminate()
{

  if(probefirst) add= add+"_first_";
  else add= add+ "_sec_";

  TFile *f = new TFile(add+"IdEff.root", "recreate");

  PtDist->Divide(probePtPassed, probePt,1,1,"B");
  EtaDist->Divide(probeEtaPassed, probeEta,1,1,"B");
  MCPtDist->Divide(MCprobePtPassed, MCprobePt,1,1,"B");
  MCEtaDist->Divide(MCprobeEtaPassed, MCprobeEta,1,1,"B");


  for(int bin=1; bin< PtDist->GetNbinsX() +1; bin++){
    double err = sqrt((1- PtDist->GetBinContent(bin))/probePtPassed->GetBinContent(bin));
    PtDist->SetBinError(bin, err);

  }
  for(int bin=1; bin< EtaDist->GetNbinsX() +1; bin++){
    double err = sqrt((1- EtaDist->GetBinContent(bin))/probeEtaPassed->GetBinContent(bin));
    EtaDist->SetBinError(bin, err);

  }
  for(int bin=1; bin< MCPtDist->GetNbinsX() +1; bin++){
    double err = sqrt((1- MCPtDist->GetBinContent(bin))/MCprobePtPassed->GetBinContent(bin));
    MCPtDist->SetBinError(bin, err);

  }
  for(int bin=1; bin< MCEtaDist->GetNbinsX() +1; bin++){
    double err = sqrt((1- MCEtaDist->GetBinContent(bin))/MCprobeEtaPassed->GetBinContent(bin));
    MCEtaDist->SetBinError(bin, err);

  }


  PtDist->Write();
  EtaDist->Write();
  MCPtDist->Write();
  MCEtaDist->Write();

  TH2D *data2d = (TH2D*) dimDist->Clone();
  data2d->GetXaxis()->SetTitle("#eta");
  data2d->SetTitle("data2d");
  data2d->SetName("data2d");

  for(int binx = 1; binx < dimDist->GetNbinsX()+1; binx++){
    for(int biny = 1; biny <  dimDist->GetNbinsY()+1; biny++){
      double content=dimDistPassed->GetCellContent(binx,biny) / dimDist->GetCellContent(binx,biny);
      double err=sqrt((1-(dimDistPassed->GetCellContent(binx,biny) / dimDist->GetCellContent(binx,biny)))/dimDist->GetCellContent(binx,biny));
      data2d->SetCellContent(binx,biny,content);
      data2d->SetCellError(binx,biny,err);
    }
  }
  data2d->Write();

  TH2D *MC2d = (TH2D*) MCdimDist->Clone();
  MC2d->GetXaxis()->SetTitle("#eta");
  MC2d->SetTitle("MC2d");
  MC2d->SetName("MC2d");

  for(int binx = 1; binx < MCdimDist->GetNbinsX()+1; binx++){
    for(int biny = 1; biny <  MCdimDist->GetNbinsY()+1; biny++){
      double content=MCdimDistPassed->GetCellContent(binx,biny) / MCdimDist->GetCellContent(binx,biny);
      double err=sqrt((1-(MCdimDistPassed->GetCellContent(binx,biny) / MCdimDist->GetCellContent(binx,biny)))/MCdimDist->GetCellContent(binx,biny));
      MC2d->SetCellContent(binx,biny,content);
      MC2d->SetCellError(binx,biny,err);
    }
  }
  MC2d->Write();

  TH2D *corrfactors = (TH2D*) MCdimDist->Clone();
  corrfactors->SetTitle("corrFactors");
  corrfactors->SetName("corrFactors");

  for(int binx = 1; binx < MCdimDist->GetNbinsX()+1; binx++){
    for(int biny = 1; biny <  MCdimDist->GetNbinsY()+1; biny++){
      double content=data2d->GetCellContent(binx,biny) / MC2d->GetCellContent(binx,biny);
      double err=sqrt((content/MC2d->GetCellContent(binx,biny)*MC2d->GetCellError(binx,biny))
		      *(content/MC2d->GetCellContent(binx,biny)*MC2d->GetCellError(binx,biny))
		      +(content/data2d->GetCellContent(binx,biny) * data2d->GetCellError(binx,biny))
                      *(content/data2d->GetCellContent(binx,biny) * data2d->GetCellError(binx,biny)));
      corrfactors->SetCellContent(binx,biny,content);
      corrfactors->SetCellError(binx,biny,err);
    }
  }
  corrfactors->Write();



  TH1D * ratiopt = (TH1D*)MCPtDist->Clone();
  ratiopt->SetName("corrFactor Pt");
  ratiopt->SetTitle("corrFactor Pt");


  for(int bin=1; bin< ratiopt->GetNbinsX() +1; bin++){
    double content=PtDist->GetBinContent(bin) / MCPtDist->GetBinContent(bin);
    double err = sqrt((PtDist->GetBinError(bin)/(MCPtDist->GetBinContent(bin)))*(PtDist->GetBinError(bin)/(MCPtDist->GetBinContent(bin))) 
		      + (MCPtDist->GetBinError(bin)*(PtDist->GetBinContent(bin))/(MCPtDist->GetBinContent(bin) * MCPtDist->GetBinContent(bin)))
		      *(MCPtDist->GetBinError(bin)*(PtDist->GetBinContent(bin))/(MCPtDist->GetBinContent(bin) * MCPtDist->GetBinContent(bin))));

    ratiopt->SetBinContent(bin, content);
    ratiopt->SetBinError(bin, err);

  }
  ratiopt->Write();

  TH1D * ratioeta = (TH1D*)MCEtaDist->Clone();
  ratioeta->SetName("corrFactor Eta");
  ratioeta->SetTitle("corrFactor Eta");



  for(int bin=1; bin< ratioeta->GetNbinsX() +1; bin++){
    double content=EtaDist->GetBinContent(bin) / MCEtaDist->GetBinContent(bin);
    double err = sqrt((EtaDist->GetBinError(bin)/(MCEtaDist->GetBinContent(bin)))*(EtaDist->GetBinError(bin)/(MCEtaDist->GetBinContent(bin))) 
		      + (MCEtaDist->GetBinError(bin)*(EtaDist->GetBinContent(bin))/(MCEtaDist->GetBinContent(bin) * MCEtaDist->GetBinContent(bin)))
		      *(MCEtaDist->GetBinError(bin)*(EtaDist->GetBinContent(bin))/(MCEtaDist->GetBinContent(bin) * MCEtaDist->GetBinContent(bin))));

    ratioeta->SetBinContent(bin, content);
    ratioeta->SetBinError(bin, err);

  }
  ratioeta->Write();

  TCanvas *c = new TCanvas("bla","bla");
  c->cd();
//   PtDist->Draw("e1");
//   c->Print(add+"pt.eps");
//   EtaDist->Draw("e1");
//   c->Print(add+"eta.eps");
//   MCPtDist->Draw("e1");
//   c->Print(add+"MCpt.eps");
//   MCEtaDist->Draw("e1");
//   c->Print(add+"MCeta.eps");

  PtDist->Draw("e1");
  MCPtDist->SetLineColor(kRed);
  MCPtDist->Draw("e1, same");
  //c->Print(add+"ptBoth.eps");
  c->Write();



  std::cout << "Total data: " << probed << "   passed: " << passed << std::endl;
  std::cout << "Total MC:   " << MCprobed << "   passed: " << MCpassed << std::endl;
  double dataerr=sqrt((1-passed/probed)/probed);
  double MCerr=sqrt((1-MCpassed/MCprobed)/MCprobed);
  std::cout << "DataEff "   << passed/probed  << " +- " << dataerr <<std::endl;
  std::cout << "MC Eff  "   << MCpassed/MCprobed  << " +- " << MCerr <<std::endl;
  double correrr=sqrt((dataerr/(MCpassed/MCprobed))*(dataerr/(MCpassed/MCprobed)) 
		      + (MCerr*(passed/probed)/(MCpassed/MCprobed * MCpassed/MCprobed))
		      *(MCerr*(passed/probed)/(MCpassed/MCprobed * MCpassed/MCprobed)));
  std::cout << "\ncorr Factor:  "   << (passed/probed)/(MCpassed/MCprobed)  << " +- " << correrr <<std::endl;

  TH1D * totalSF = new TH1D("totalFactor", "totalFactor", 1, 0, 2);
  totalSF->SetBinContent(1, (passed/probed)/(MCpassed/MCprobed));
  totalSF->SetBinError(1, correrr);
  totalSF->Write();

  f->Close();
}

void IdStudies::Terminate()
{
  

}
