//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 10 14:37:26 2011 by ROOT version 5.27/06b
// from TTree NTuple/NTuple
// found on file: /scratch/hh/current/cms/user/kieseler/Tuples_0610/ee_Full.root
//////////////////////////////////////////////////////////

#ifndef EE_Analysis_h
#define EE_Analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

#include "plugins/plotterclass.h"
#include "plugins/CountTools.h"
#include <vector>
#include <string>
#include <TString.h>
#include <TH1.h>

class EE_Analysis : public TSelector {
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
   vector<double>  *jetPt;
   vector<double>  *jetEta;
   vector<double>  *jetPhi;
   vector<double>  *jetBTagTCHE;
   vector<double>  *jetBTagSSVHE;
   Int_t           jetMulti;
   vector<double>  *metEt;
   vector<double>  *metPhi;
   Int_t           runNumber;
   Int_t           lumiBlock;
   Int_t           eventNumber;
   vector<string>  *dataType;
   Double_t        PUweight;
   Int_t           vertMulti;

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
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetBTagTCHE;   //!
   TBranch        *b_jetBTagSSVHE;   //!
   TBranch        *b_jetMulti;   //!
   TBranch        *b_metEt;   //!
   TBranch        *b_metPhi;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_dataType;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_vertMulti;   //!

   EE_Analysis(TTree * /*tree*/ =0) { }
   virtual ~EE_Analysis() { }
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

   ///////////user entries////////////

   void GetAllBranches(Long64_t &);


   //Plotters
   Plotter h_testplotter, h_testplotter2;

   Plotter h_lepQ0, h_combIso0, h_PfIso0, h_lepPt0, h_lepEta0, h_lepMulti0, h_lepType0;
   Plotter h_combIso1, h_PfIso1, h_lepMulti1;

   Plotter h_diMass3, h_lepPt3, h_lepEta3, h_jetPt3, h_jetEta3, h_jetMulti3, h_metEt3, h_btagN3;
   Plotter h_vertMulti3, h_vertMulti3a; 
   Plotter h_diMass3a, h_lepPt3a, h_lepEta3a, h_jetPt3a, h_jetEta3a, h_jetMulti3a, h_metEt3a, h_btagN3a;
   Plotter h_diMass4, h_lepPt4, h_lepEta4, h_jetPt4, h_jetEta4, h_jetMulti4, h_metEt4, h_btagN4;
   Plotter h_diMass5, h_lepPt5, h_lepEta5, h_jetPt5, h_jetEta5, h_jetMulti5, h_metEt5, h_btagN5;
   Plotter h_diMass6, h_lepPt6, h_lepEta6, h_jetPt6, h_jetEta6, h_jetMulti6, h_metEt6, h_btagN6;
   Plotter h_diMass7, h_lepPt7, h_lepEta7, h_jetPt7, h_jetEta7, h_jetMulti7, h_metEt7, h_btagN7;
   Plotter h_diMass8, h_lepPt8, h_lepEta8, h_jetPt8, h_jetEta8, h_jetMulti8, h_metEt8, h_btagN8;

   Plotter h_diMassZ4,h_diMassZ5,h_diMassZ6,h_diMassZ7,h_diMassZ8;

   //Counters
   CountTools c_step0, c_step1, c_step2, c_step3, c_step4, c_step5, c_step6, c_step7, c_step8, c_step9;

   double totalEventCount;
   double testcounter;


   TH1D *h_dataZEC;
   TH1D *h_MCZEC;
   TH1D *h_dataZB;
   TH1D *h_MCZB;

   //////////////
   ClassDef(EE_Analysis,0);
};

#endif

#ifdef EE_Analysis_cxx
void EE_Analysis::Init(TTree *tree)
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
   jetPt = 0;
   jetEta = 0;
   jetPhi = 0;
   jetBTagTCHE = 0;
   jetBTagSSVHE = 0;
   metEt = 0;
   metPhi = 0;
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
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetBTagTCHE", &jetBTagTCHE, &b_jetBTagTCHE);
   fChain->SetBranchAddress("jetBTagSSVHE", &jetBTagSSVHE, &b_jetBTagSSVHE);
   fChain->SetBranchAddress("jetMulti", &jetMulti, &b_jetMulti);
   fChain->SetBranchAddress("metEt", &metEt, &b_metEt);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("dataType", &dataType, &b_dataType);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
   fChain->SetBranchAddress("vertMulti", &vertMulti, &b_vertMulti);
}

Bool_t EE_Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}
void EE_Analysis::GetAllBranches(Long64_t & entry)
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
           b_jetPt->GetEntry(entry);   //!
           b_jetEta->GetEntry(entry);   //!
           b_jetPhi->GetEntry(entry);   //!
           b_jetBTagTCHE->GetEntry(entry);   //!
           b_jetBTagSSVHE->GetEntry(entry);   //!
           b_jetMulti->GetEntry(entry);   //!
           b_metEt->GetEntry(entry);   //!
           b_metPhi->GetEntry(entry);   //!
           b_runNumber->GetEntry(entry);   //!
           b_lumiBlock->GetEntry(entry);   //!
           b_eventNumber->GetEntry(entry);   //!
           b_dataType->GetEntry(entry);   //!
           b_PUweight->GetEntry(entry);   //!
           b_vertMulti->GetEntry(entry);   //!
}
#endif // #ifdef EE_Analysis_cxx
