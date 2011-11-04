//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov  3 11:38:45 2011 by ROOT version 5.27/06b
// from TTree NTuple/NTuple
// found on file: eeId.root
//////////////////////////////////////////////////////////

#ifndef IdStudies_h
#define IdStudies_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <vector>
#include "TH1D.h"
#include "TH2D.h"
#include <iostream>
#include "TLorentzVector.h"

class IdStudies : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   vector<double>  *lepPt;
   vector<double>  *lepEta;
   vector<double>  *lepPhi;
   vector<double>  *lepE;
   vector<double>  *lepPx;
   vector<double>  *lepPy;
   vector<double>  *lepPz;
   vector<int>     *lepQ;
   vector<int>     *lepType;
   vector<double>  *lepPfIso;
   vector<double>  *lepCombIso;
   vector<bool>    *passedId;
   Int_t           runNumber;
   Int_t           lumiBlock;
   Int_t           eventNumber;
   vector<string>  *dataType;
   Double_t        PUweight;

   // List of branches
   TBranch        *b_lepPt;   //!
   TBranch        *b_lepEta;   //!
   TBranch        *b_lepPhi;   //!
   TBranch        *b_lepE;   //!
   TBranch        *b_lepPx;   //!
   TBranch        *b_lepPy;   //!
   TBranch        *b_lepPz;   //!
   TBranch        *b_lepQ;   //!
   TBranch        *b_lepType;   //!
   TBranch        *b_lepPfIso;   //!
   TBranch        *b_lepCombIso;   //!
   TBranch        *b_passedId;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_dataType;   //!
   TBranch        *b_PUweight;   //!

   IdStudies(TTree * /*tree*/ =0) { }
   virtual ~IdStudies() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
   ///////USER ENTRIES

   void GetAllBranches(Long64_t &);

   TH1D *probePt, *probePtPassed;
   TH1D *probeEta, *probeEtaPassed;
   TH1D *PtDist, *EtaDist;
   TH2D *dimDist;
   TH2D *dimDistPassed;

   TH1D *MCprobePt, *MCprobePtPassed;
   TH1D *MCprobeEta, *MCprobeEtaPassed;
   TH1D *MCPtDist, *MCEtaDist;
   TH2D *MCdimDist;
   TH2D *MCdimDistPassed;

   int totalcount;

   double probed, passed;
   double MCprobed, MCpassed;



   TString add;
   bool probefirst;

   int leptontype;


   /////////
   ClassDef(IdStudies,0);
};

#endif

#ifdef IdStudies_cxx
void IdStudies::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   lepPt = 0;
   lepEta = 0;
   lepPhi = 0;
   lepE = 0;
   lepPx = 0;
   lepPy = 0;
   lepPz = 0;
   lepQ = 0;
   lepType = 0;
   lepPfIso = 0;
   lepCombIso = 0;
   passedId = 0;
   dataType = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("lepPt", &lepPt, &b_lepPt);
   fChain->SetBranchAddress("lepEta", &lepEta, &b_lepEta);
   fChain->SetBranchAddress("lepPhi", &lepPhi, &b_lepPhi);
   fChain->SetBranchAddress("lepE", &lepE, &b_lepE);
   fChain->SetBranchAddress("lepPx", &lepPx, &b_lepPx);
   fChain->SetBranchAddress("lepPy", &lepPy, &b_lepPy);
   fChain->SetBranchAddress("lepPz", &lepPz, &b_lepPz);
   fChain->SetBranchAddress("lepQ", &lepQ, &b_lepQ);
   fChain->SetBranchAddress("lepType", &lepType, &b_lepType);
   fChain->SetBranchAddress("lepPfIso", &lepPfIso, &b_lepPfIso);
   fChain->SetBranchAddress("lepCombIso", &lepCombIso, &b_lepCombIso);
   fChain->SetBranchAddress("passedId", &passedId, &b_passedId);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("dataType", &dataType, &b_dataType);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
}

Bool_t IdStudies::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}
void IdStudies::GetAllBranches(Long64_t & entry)
{


           b_lepPt->GetEntry(entry);   //!
           b_lepEta->GetEntry(entry);   //!
           b_lepPhi->GetEntry(entry);   //!
           b_lepE->GetEntry(entry);   //!
           b_lepPx->GetEntry(entry);   //!
           b_lepPy->GetEntry(entry);   //!
           b_lepPz->GetEntry(entry);   //!
           b_lepQ->GetEntry(entry);   //!
           b_lepType->GetEntry(entry);   //!
           b_lepPfIso->GetEntry(entry);   //!
           b_lepCombIso->GetEntry(entry);   //!
           b_passedId->GetEntry(entry);   //!
           b_runNumber->GetEntry(entry);   //!
           b_lumiBlock->GetEntry(entry);   //!
           b_eventNumber->GetEntry(entry);   //!
           b_dataType->GetEntry(entry);   //!
           b_PUweight->GetEntry(entry);   //!


}

#endif // #ifdef IdStudies_cxx
