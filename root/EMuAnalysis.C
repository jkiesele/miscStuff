#define EMuAnalysis_cxx

//

#include "EMuAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include "TLorentzVector.h"
#include "plugins/rescaleFunctions.h"




  //Lepton Scaling factors check AN-11-186 to see pt and eta ranges where are applied
   float eSF1=1.0094, eSF2=1.0027, eSF3=0.9987, eSF4=0.9990;
   float eSF5=1.0537, eSF6=1.0324, eSF7=1.0110, eSF8=1.0056;
   float muSF1=1.0030, muSF2=0.9945, muSF3=0.9988, muSF4=1.0022;
   float muSF5=0.9984, muSF6=0.9921, muSF7=0.9901, muSF8=0.9896;
   float muSF9=0.9870, muSF10=0.9811, muSF11=0.9924, muSF12=0.9947;

   //B-tagging Scale factor
double btagSF=1.;//0.94;

   //Trigger Scale Factor 
double triggSF=1.;//0.987;  //Just for EMu events


//Dilepton mass cut

double llmass=12.;//20.;// 30.;//40.;//50.;//



void EMuAnalysis::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
  totalEventCount=0;


   ///init counters
   TString dataset="emu";

   //rescaleVert0_h = readin("MuMu_Analysis_Rescaler.root", "vertMulti0R");


   c_step0.setOptions("c_step0 after 1 iso", 1);
   c_step0.setDataSet(dataset);
   c_step1.setDataSet(dataset);
   c_step1.setOptions("c_step1 after charge", 1);
   c_step2.setDataSet(dataset);
   c_step2.setOptions("c_step2 channel", 1);
   c_step3.setDataSet(dataset);
   c_step3.setOptions("c_step3 fulldi = QCD + channel", 1);
   c_step4.setDataSet(dataset);
   c_step4.setOptions("c_step4 (ZVeto)", 1);
   c_step5.setDataSet(dataset);
   c_step5.setOptions("c_step5 (oneJet)", 1);
   c_step6.setDataSet(dataset);
   c_step6.setOptions("c_step6 (twoJets)", 1);
   c_step7.setDataSet(dataset);
   c_step7.setOptions("c_step7 (met)", 1);
   c_step8.setDataSet(dataset);
   c_step8.setOptions("c_step8 (1btag)", 1);
   c_step9.setDataSet(dataset);
   c_step9.setOptions("c_step9 (1btag medium WP)", 1);

   //init jer jes pu syst counters

   //init plotters

   //testplotter for some things

   h_testplotter.setDataSet(dataset);
   h_testplotter.setOptions("dimass3 barrel", "m_{ll}", "N", 100, 0, 200, 1);
   h_testplotter2.setDataSet(dataset);
   h_testplotter2.setOptions("dimass3 EC", "m_{ll}", "N", 100, 0, 200, 1);

   //standard plotters

h_vertMulti0.   setDataSet(dataset);
h_vertMulti0.   setOptions("vertMulti0", "N_{vertex}", "N_{evts}", 30, 0, 30, 1);
   h_combIso0.setDataSet(dataset);
   h_combIso0.setOptions("combIso0", "Iso_{comb}", "N", 100, 0, 1, 1);
   h_PfIso0.setDataSet(dataset);
   h_PfIso0.setOptions("PFIso0", "I_{PF}", "N_{l}", 100, 0, 1, 1);
   h_lepPt0.setDataSet(dataset);
   h_lepPt0.setOptions("lepPt0", "p_{t, l}", "N_{l}", 100, 0, 300, 1);
   h_lepEta0.setDataSet(dataset);
   h_lepEta0.setOptions("lepEta1", "#eta_{l}", "N_{l}", 10, -3, 3, 1);

   h_lepType0.setDataSet(dataset);
   h_lepType0.setOptions("lepType0", "Type", "N_{l}", 6, -3, 3, 1);

   h_lepQ0.setDataSet(dataset);
   h_lepQ0.setOptions("lepQ0", "Q", "N_{l}", 6, -3, 3, 1);

   h_lepMulti0.setDataSet(dataset);
   h_lepMulti0.setOptions("lepMulti0 - 50+GeV", "N_{l}", "N_{l}", 6, 0, 6, 1);

   h_combIso1.setDataSet(dataset);
   h_combIso1.setOptions("combIso1", "Iso_{comb}", "N", 100, 0, 1, 1);
   h_PfIso1.setDataSet(dataset);
   h_PfIso1.setOptions("PFIso1", "I_{PF}", "N_{l}", 100, 0, 1, 1);
   h_lepMulti1.setDataSet(dataset);
   h_lepMulti1.setOptions("lepMulti1 - 12-50GeV", "N_{l}", "N_{l}", 6, 0, 6, 1);

   float DYScale=1;
h_vertMulti3.   setDataSet(dataset);
h_vertMulti3.   setOptions("vertMulti3", "N_{vertex}", "N_{evts}", 30, 0, 30, DYScale);
   h_diMass3.   setDataSet(dataset);
   h_diMass3.   setOptions("dileptonMass3", "m_{ll}", "N_{ll}", 100, 0, 300, DYScale);
   h_lepPt3.    setDataSet(dataset);
   h_lepPt3.    setOptions("lepPt3", "p_{t, l}", "N_{l}", 100, 0, 300, DYScale);
   h_lepEta3.   setDataSet(dataset);
   h_lepEta3.   setOptions("lepEta3", "#eta_{l}", "N_{l}", 10, -3, 3, DYScale);
   h_jetPt3.    setDataSet(dataset);
   h_jetPt3.    setOptions("jetPt3", "p_{t, jet}", "N_{jets}", 30, 0, 300, DYScale);
   h_jetEta3.   setDataSet(dataset);
   h_jetEta3.   setOptions("jetEta3", "#eta_{jet}", "N_{jets}", 10, -3, 3, DYScale);
   h_jetMulti3. setDataSet(dataset);
   h_jetMulti3. setOptions("jetMulti3", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);
   h_metEt3.    setDataSet(dataset);
   h_metEt3.    setOptions("metEt3", "E_{t}", "N_{evts}", 30, 0, 300, DYScale);
   h_btagN3.    setDataSet(dataset);
   h_btagN3.    setOptions("btag3", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);

   //check dimass 12-50GeV

h_vertMulti3a.   setDataSet(dataset);
h_vertMulti3a.   setOptions("vertMulti3a", "N_{vertex}", "N_{evts}", 30, 0, 30, DYScale);
   h_diMass3a.   setDataSet(dataset);
   h_diMass3a.   setOptions("dileptonMass3 12-50GeV", "m_{ll}", "N_{ll}", 100, 0, 300, DYScale);
   h_lepPt3a.    setDataSet(dataset);
   h_lepPt3a.    setOptions("lepPt3 12-50GeV", "p_{t, l}", "N_{l}", 100, 0, 300, DYScale);
   h_lepEta3a.   setDataSet(dataset);
   h_lepEta3a.   setOptions("lepEta3 12-50GeV", "#eta_{l}", "N_{l}", 10, -3, 3, DYScale);
   h_jetPt3a.    setDataSet(dataset);
   h_jetPt3a.    setOptions("jetPt3 12-50GeV", "p_{t, jet}", "N_{jets}", 30, 0, 300, DYScale);
   h_jetEta3a.   setDataSet(dataset);
   h_jetEta3a.   setOptions("jetEta3 12-50GeV", "#eta_{jet}", "N_{jets}", 10, -3, 3, DYScale);
   h_jetMulti3a. setDataSet(dataset);
   h_jetMulti3a. setOptions("jetMulti3 12-50GeV", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);
   h_metEt3a.    setDataSet(dataset);
   h_metEt3a.    setOptions("metEt3 12-50GeV", "E_{t}", "N_{evts}", 30, 0, 300, DYScale);
   h_btagN3a.    setDataSet(dataset);
   h_btagN3a.    setOptions("btag3 12-50GeV", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);

   DYScale=1;

h_vertMulti4.   setDataSet(dataset);
h_vertMulti4.   setOptions("vertMulti4", "N_{vertex}", "N_{evts}", 30, 0, 30, DYScale);
   h_diMass4.   setDataSet(dataset);
   h_diMass4.   setOptions("dileptonMass4", "m_{ll}", "N_{ll}", 100, 0, 300, DYScale);
   h_lepPt4.    setDataSet(dataset);
   h_lepPt4.    setOptions("lepPt4", "p_{t, l}", "N_{l}", 100, 0, 300, DYScale);
   h_lepEta4.   setDataSet(dataset);
   h_lepEta4.   setOptions("lepEta4", "#eta_{l}", "N_{l}", 10, -3, 3, DYScale);
   h_jetPt4.    setDataSet(dataset);
   h_jetPt4.    setOptions("jetPt4", "p_{t, jet}", "N_{jets}", 30, 0, 300, DYScale);
   h_jetEta4.   setDataSet(dataset);
   h_jetEta4.   setOptions("jetEta4", "#eta_{jet}", "N_{jets}", 10, -3, 3, DYScale);
   h_jetMulti4. setDataSet(dataset);
   h_jetMulti4. setOptions("jetMulti4", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);
   h_metEt4.    setDataSet(dataset);
   h_metEt4.    setOptions("metEt4", "E_{t}", "N_{evts}", 30, 0, 300, DYScale);
   h_btagN4.    setDataSet(dataset);
   h_btagN4.    setOptions("btag4", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);

   DYScale=1;

h_vertMulti5.   setDataSet(dataset);
h_vertMulti5.   setOptions("vertMulti5", "N_{vertex}", "N_{evts}", 30, 0, 30, DYScale);
   h_diMass5.   setDataSet(dataset);
   h_diMass5.   setOptions("dileptonMass5", "m_{ll}", "N_{ll}", 100, 0, 300, DYScale);
   h_lepPt5.    setDataSet(dataset);
   h_lepPt5.    setOptions("lepPt5", "p_{t, l}", "N_{l}", 100, 0, 300, DYScale);
   h_lepEta5.   setDataSet(dataset);
   h_lepEta5.   setOptions("lepEta5", "#eta_{l}", "N_{l}", 10, -3, 3, DYScale);
   h_jetPt5.    setDataSet(dataset);
   h_jetPt5.    setOptions("jetPt5", "p_{t, jet}", "N_{jets}", 30, 0, 300, DYScale);
   h_jetEta5.   setDataSet(dataset);
   h_jetEta5.   setOptions("jetEta5", "#eta_{jet}", "N_{jets}", 10, -3, 3, DYScale);
   h_jetMulti5. setDataSet(dataset);
   h_jetMulti5. setOptions("jetMulti5", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);
   h_metEt5.    setDataSet(dataset);
   h_metEt5.    setOptions("metEt5", "E_{t}", "N_{evts}", 30, 0, 300, DYScale);
   h_btagN5.    setDataSet(dataset);
   h_btagN5.    setOptions("btag5", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);

   DYScale=1;

h_vertMulti6.   setDataSet(dataset);
h_vertMulti6.   setOptions("vertMulti6", "N_{vertex}", "N_{evts}", 30, 0, 30, DYScale);
   h_diMass6.   setDataSet(dataset);
   h_diMass6.   setOptions("dileptonMass6", "m_{ll}", "N_{ll}", 40, 0, 300, DYScale);
   h_lepPt6.    setDataSet(dataset);
   h_lepPt6.    setOptions("lepPt6", "p_{t, l}", "N_{l}", 100, 0, 300, DYScale);
   h_lepEta6.   setDataSet(dataset);
   h_lepEta6.   setOptions("lepEta6", "#eta_{l}", "N_{l}", 10, -3, 3, DYScale);
   h_jetPt6.    setDataSet(dataset);
   h_jetPt6.    setOptions("jetPt6", "p_{t, jet}", "N_{jets}", 30, 0, 300, DYScale);
   h_jetEta6.   setDataSet(dataset);
   h_jetEta6.   setOptions("jetEta6", "#eta_{jet}", "N_{jets}", 10, -3, 3, DYScale);
   h_jetMulti6. setDataSet(dataset);
   h_jetMulti6. setOptions("jetMulti6", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);
   h_metEt6.    setDataSet(dataset);
   h_metEt6.    setOptions("metEt6", "E_{t}", "N_{evts}", 30, 0, 300, DYScale);
   h_btagN6.    setDataSet(dataset);
   h_btagN6.    setOptions("btag6", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);

   DYScale=1.;

h_vertMulti7.   setDataSet(dataset);
h_vertMulti7.   setOptions("vertMulti7", "N_{vertex}", "N_{evts}", 30, 0, 30, DYScale);
   h_diMass7.   setDataSet(dataset);
   h_diMass7.   setOptions("dileptonMass7", "m_{ll}", "N_{ll}", 30, 0, 300, DYScale);
   h_lepPt7.    setDataSet(dataset);
   h_lepPt7.    setOptions("lepPt7", "p_{t, l}", "N_{l}", 100, 0, 300, DYScale);
   h_lepEta7.   setDataSet(dataset);
   h_lepEta7.   setOptions("lepEta7", "#eta_{l}", "N_{ets}", 10, -3, 3, DYScale);
   h_jetPt7.    setDataSet(dataset);
   h_jetPt7.    setOptions("jetPt7", "p_{t, jet}", "N_{l}", 30, 0, 300, DYScale);
   h_jetEta7.   setDataSet(dataset);
   h_jetEta7.   setOptions("jetEta7", "#eta_{jet}", "N_{jets}", 10, -3, 3, DYScale);
   h_jetMulti7. setDataSet(dataset);
   h_jetMulti7. setOptions("jetMulti7", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);
   h_metEt7.    setDataSet(dataset);
   h_metEt7.    setOptions("metEt7", "E_{t}", "N_{evts}", 30, 0, 300, DYScale);
   h_btagN7.    setDataSet(dataset);
   h_btagN7.    setOptions("btag7", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);

   // DYScale=1;

h_vertMulti8.   setDataSet(dataset);
h_vertMulti8.   setOptions("vertMulti8", "N_{vertex}", "N_{evts}", 30, 0, 30, DYScale);
   h_diMass8.   setDataSet(dataset);
   h_diMass8.   setOptions("dileptonMass8", "m_{ll}", "N_{ll}", 30, 0, 300, DYScale);
   h_lepPt8.    setDataSet(dataset);
   h_lepPt8.    setOptions("lepPt8", "p_{t, l}", "N_{l}", 100, 0, 300, DYScale);
   h_lepEta8.   setDataSet(dataset);
   h_lepEta8.   setOptions("lepEta8", "#eta_{l}", "N_{l}", 10, -3, 3, DYScale);
   h_jetPt8.    setDataSet(dataset);
   h_jetPt8.    setOptions("jetPt8", "p_{t, jet}", "N_{jets}", 30, 0, 300, DYScale);
   h_jetEta8.   setDataSet(dataset);
   h_jetEta8.   setOptions("jetEta8", "#eta_{jet}", "N_{jets}", 10, -3, 3, DYScale);
   h_jetMulti8. setDataSet(dataset);
   h_jetMulti8. setOptions("jetMulti8", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);
   h_metEt8.    setDataSet(dataset);
   h_metEt8.    setOptions("metEt8", "E_{t}", "N_{evts}", 30, 0, 300, DYScale);
   h_btagN8.    setDataSet(dataset);
   h_btagN8.    setOptions("btag8", "N_{jets}", "N_{evts}", 7, 0, 7, DYScale);


   h_diMassZ8.   setDataSet(dataset);
   h_diMassZ8.   setOptions("dileptonMassZ8", "m_{ll}", "N_{ll}", 30, 0, 300, DYScale);
   h_diMassZ7.   setDataSet(dataset);
   h_diMassZ7.   setOptions("dileptonMassZ7", "m_{ll}", "N_{ll}", 50, 0, 300, DYScale);
   DYScale=1;
   h_diMassZ6.   setDataSet(dataset);
   h_diMassZ6.   setOptions("dileptonMassZ6", "m_{ll}", "N_{ll}", 50, 0, 300, DYScale);
   h_diMassZ5.   setDataSet(dataset);
   h_diMassZ5.   setOptions("dileptonMassZ5", "m_{ll}", "N_{ll}", 50, 0, 300, DYScale);
   h_diMassZ4.   setDataSet(dataset);
   h_diMassZ4.   setOptions("dileptonMassZ4", "m_{ll}", "N_{ll}", 50, 0, 300, DYScale);


   testcounter=0;

}

void EMuAnalysis::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t EMuAnalysis::Process(Long64_t entry)
{
   GetAllBranches(entry);


  totalEventCount++;
  double totalevents=9.66875e+06;
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

  //  bool rescale=true;

  float isocutmuons = 0.2;//999999;//0.3;//0.2; //0.2;  //0.2;//0.2; pf // 0.15 comb
  float isocutelecs = 0.17;//999999; //0.3;//0.17;//0.17; //0.17; //0.17;//0.17;
  bool pfIso = true;
  //  float leptontype = 1; // 1 muon -1 electron
  bool oppocharge=true;
  float globalElecEnergyScale=1.0;
  //if(DataType == "ee_200rereco.root" || DataType == "ee_800prompt.root" ) globalElecEnergyScale=1.005; //just play around



  float tempiso=100;

  std::vector<double> VLepPt;
  std::vector<double> VLepEta, VLepPhi, VLepE, VLepPx, VLepPy, VLepPz, VLepPfIso, VLepCombIso;
  std::vector<int> VLepQ, VLepType;
 

  h_combIso0.  fill(DataType,*lepCombIso , PUweight);
  h_PfIso0.    fill(DataType,*lepPfIso , PUweight);
  h_lepPt0.    fill(DataType,*lepPt , PUweight);
  h_lepEta0.   fill(DataType,*lepEta , PUweight);
  h_lepType0.  fill(DataType,*lepType , PUweight);
  h_lepQ0.  fill(DataType,*lepQ , PUweight);
    h_vertMulti0.   fill(DataType,vertMulti ,  PUweight);

  //h_lepMulti0.fill(DataType, (int)lepPt->size(), PUweight);
  
  int CheckCharge=100;
  for(unsigned int i=0; i<lepPt->size(); i++){ //isocut and chargecut -> builds leptonvectors
    if(pfIso) tempiso=*(lepPfIso->begin()+i);
    else tempiso=*(lepCombIso->begin()+i);


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
    }
    if(VLepType.size()==1 && oppocharge) CheckCharge=VLepQ[0];
    else if(VLepType.size()==1 && !oppocharge) CheckCharge= - VLepQ[0];
  }

  

 
  c_step0.fill(DataType, PUweight);



  PUweight=1;



  double dimass=-1;

  if(VLepPt.size() > 1){  //two isolated leptons create dimass out of highest pt pair

    TLorentzVector diLepVector = TLorentzVector(VLepPx[0] + VLepPx[1], VLepPy[0] + VLepPy[1], VLepPz[0] + VLepPz[1], VLepE[0] + VLepE[1]);

    dimass=diLepVector.M();

    b_step1=true;
    testcounter++;
      
    if((VLepType[0] == 1 &&  VLepType[1] == -1 )||(VLepType[0] == -1 &&  VLepType[1] == 1 ) ) b_step2=true;
    if(dimass > 12)                     b_step3=true;
    //   if((dimass < 76.0 || dimass > 106.0))     b_step4=true; //dimass > 50 &&  
    b_step4=true; //no cut on Z in emu
    if(jetMulti>0)                      b_step5=true;
    if(jetMulti>1)                      b_step6=true;
    if(*(metEt->begin()) > 30)          b_step7=true;
    b_step7=true;

  }

  double btagWPM=3.3;
  double btagWP=1.7;
  int btagmultiM=0;
  int btagmulti=0;

  for(std::vector<double>::const_iterator ajetTCHE = jetBTagTCHE->begin(); ajetTCHE < jetBTagTCHE->end(); ajetTCHE++){
    if(*ajetTCHE > btagWPM) btagmultiM++;
    if(*ajetTCHE > btagWP) btagmulti++;
  }

  if(btagmulti > 0 && dimass> llmass) b_step8=true;
  if(btagmultiM > 0) b_step9=true;



  //Lepton scaling factor selection
  double lepSF[2]={0.,0.};

  for (int i=0; i<2; i++)
    {
      if(VLepType[i]== -1)
	{
	  if(20.0<= VLepPt[i] && VLepPt[i] <30.)
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=eSF1;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=eSF5;};
	    }
	  else if(30.0<= VLepPt[i] && VLepPt[i] <40.)
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=eSF2;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=eSF6;};
	    }
	  else if(40.0<= VLepPt[i] && VLepPt[i] <50.)
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=eSF3;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=eSF7;};
	    }
	  else if(50.0<= VLepPt[i])
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=eSF4;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=eSF8;};
	    };
	}
      else if(VLepType[i]== 1)
	{
	  if(20.0<= VLepPt[i] && VLepPt[i] <30.)
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=muSF1;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=muSF5;};
	    }
	  else if(30.0<= VLepPt[i] && VLepPt[i] <40.)
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=muSF2;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=muSF6;};
	    }
	  else if(40.0<= VLepPt[i] && VLepPt[i] <50.)
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=muSF3;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=muSF7;};
	    }
	  else if(50.0<= VLepPt[i])
	    {
	      if (VLepEta[i]<=1.5)     {lepSF[i]=muSF4;}
	      else if (VLepEta[i]>1.5) {lepSF[i]=muSF8;};
	    };
	 };    
    };



  bool STEP1=0;
  bool STEP2=0;
  bool STEP3=0;
  bool STEP4=0;
  bool STEP5=0;
  bool STEP6=0;
  bool STEP7=0;
  bool STEP8=0;



  //Fill the histograms etc apart from step 0 (this is filled at the top




  if (b_step1){

    h_PfIso1.    fill(DataType,VLepPfIso , PUweight);
    h_combIso1.  fill(DataType,VLepCombIso , PUweight);
    c_step1.fill(DataType, PUweight);
    
    STEP1=1;

  }
  if (b_step1 && b_step2) {c_step2.fill(DataType, PUweight);  STEP2=1;};
  

  
  std::vector<TString> samples;//only used below for MC rescaling
  samples.push_back("mumu_dymumu1020.root");  //why MuMu samples and NOT EMu samples?
  samples.push_back("mumu_dymumu2050.root");
  samples.push_back("mumu_dymumu50inf.root");



 //MC reweighting: Lept SF, Trigger SF, BTag SF
  if (!isData) PUweight=PUweight*lepSF[0]*lepSF[1]*triggSF*btagSF;



  if(b_step1 && b_step2 && b_step3){
    c_step3.fill(DataType, PUweight);

    if(dimass < 50) h_lepMulti1.fill(DataType, (int)lepPt->size(), PUweight);
    else h_lepMulti0.fill(DataType, (int)lepPt->size(), PUweight);

    h_vertMulti3.   fill(DataType,vertMulti ,  PUweight);
    h_diMass3.  fill(DataType, dimass,  PUweight);
    h_lepPt3.   fill(DataType, VLepPt,    PUweight);
    h_lepEta3.  fill(DataType, VLepEta ,  PUweight);
    h_jetPt3.   fill(DataType, *jetPt ,   PUweight);
    h_jetMulti3.fill(DataType, jetMulti , PUweight);
    h_metEt3.   fill(DataType, *metEt ,   PUweight);
    h_btagN3.   fill(DataType, btagmulti ,PUweight);

    if(VLepEta[0] < 1.79 && VLepEta[1] < 1.79) h_testplotter.  fill(DataType, dimass,  PUweight);
    else if(VLepEta[0] > 1.79 && VLepEta[1] > 1.79) h_testplotter2.  fill(DataType, dimass,  PUweight);


     STEP3=1;
  }


  if(b_step1 && b_step2 && b_step3 && dimass < 50){


    h_vertMulti3a.   fill(DataType,vertMulti ,  PUweight);
    h_diMass3a.  fill(DataType, dimass,  PUweight);
    h_lepPt3a.   fill(DataType, VLepPt,    PUweight);
    h_lepEta3a.  fill(DataType, VLepEta ,  PUweight);
    h_jetPt3a.   fill(DataType, *jetPt ,   PUweight);
    h_jetMulti3a.fill(DataType, jetMulti , PUweight);
    h_metEt3a.   fill(DataType, *metEt ,   PUweight);
    h_btagN3a.   fill(DataType, btagmulti ,PUweight);

  }

  
  if(b_step1 && b_step2 && b_step3){
    h_diMassZ4.  fill(DataType, dimass,  PUweight);
    if(b_step4){
      c_step4.fill(DataType, PUweight);

    h_vertMulti4.   fill(DataType,vertMulti ,  PUweight);
      h_diMass4.  fill(DataType, dimass,  PUweight);
      h_lepPt4.   fill(DataType, VLepPt,    PUweight);
      h_lepEta4.  fill(DataType, VLepEta ,  PUweight);
      h_jetPt4.   fill(DataType, *jetPt ,   PUweight);
      h_jetMulti4.fill(DataType, jetMulti , PUweight);
      h_metEt4.   fill(DataType, *metEt ,   PUweight);
      h_btagN4.   fill(DataType, btagmulti ,PUweight);

      STEP4=1;
    }
  }
  
  if(b_step1 && b_step2 && b_step3 &&  b_step5){
    h_diMassZ5.  fill(DataType, dimass,  PUweight);
    if(b_step4){
      c_step5.fill(DataType, PUweight);

    h_vertMulti5.   fill(DataType,vertMulti ,  PUweight);
      h_diMass5.  fill(DataType, dimass,  PUweight);
      h_lepPt5.   fill(DataType, VLepPt,    PUweight);
      h_lepEta5.  fill(DataType, VLepEta ,  PUweight);
      h_jetPt5.   fill(DataType, *jetPt ,   PUweight);
      h_jetMulti5.fill(DataType, jetMulti , PUweight);
      h_metEt5.   fill(DataType, *metEt ,   PUweight);
      h_btagN5.   fill(DataType, btagmulti ,PUweight);

      STEP5=1;
    }
  }



//   for(unsigned int i=0; i< samples.size() ;i++){
//     if(rescale && samples[i] == DataType) PUweight = PUweight * reweightWeight(rescaleVert6_h, vertMulti);
  
//   }


  if(b_step1 && b_step2 && b_step3 &&  b_step5 && b_step6){
    h_diMassZ6.  fill(DataType, dimass,  PUweight);
    if(b_step4){
      c_step6.fill(DataType, PUweight);

    h_vertMulti6.   fill(DataType,vertMulti ,  PUweight);
      h_diMass6.  fill(DataType, dimass,  PUweight);
      h_lepPt6.   fill(DataType, VLepPt,    PUweight);
      h_lepEta6.  fill(DataType, VLepEta ,  PUweight);
      h_jetPt6.   fill(DataType, *jetPt ,   PUweight);
      h_jetMulti6.fill(DataType, jetMulti , PUweight);
      h_metEt6.   fill(DataType, *metEt ,   PUweight);
      h_btagN6.   fill(DataType, btagmulti ,PUweight);

      STEP6=1;
    }
  }
 
  if(b_step1 && b_step2 && b_step3 &&  b_step5 && b_step6 && b_step7){
    h_diMassZ7.  fill(DataType, dimass,  PUweight);
    if(b_step4){
      c_step7.fill(DataType, PUweight);

    h_vertMulti7.   fill(DataType,vertMulti ,  PUweight);
      h_diMass7.  fill(DataType, dimass,  PUweight);
      h_lepPt7.   fill(DataType, VLepPt,    PUweight);
      h_lepEta7.  fill(DataType, VLepEta ,  PUweight);
      h_jetPt7.   fill(DataType, *jetPt ,   PUweight);
      h_jetMulti7.fill(DataType, jetMulti , PUweight);
      h_metEt7.   fill(DataType, *metEt ,   PUweight);
      h_btagN7.   fill(DataType, btagmulti ,PUweight);

      STEP7=1;

    }
  }
 
  if(b_step1 && b_step2 && b_step3 && b_step5 && b_step6 && b_step7 && b_step8){
    /*
  std::cout <<"================================================================"<<std::endl;
  std::cout <<"Event Number = "<< eventNumber<<std::endl;
  std::cout <<"-----------------------------------------------------"<<std::endl;
  std::cout <<"Lepton 0:"<<std::endl;
  std::cout <<"Lepton type (1=muon, -1=electron)="<<VLepType[0]<<std::endl;
  std::cout <<"(px, py, pz, E) = ("<< VLepPx[0]<<" , "<<VLepPy[0]<<" , "<<VLepPz[0]<<" , "<<VLepE[0]<<")"<<std::endl;
  std::cout <<"p_T = "<<VLepPt[0]<<std::endl;
  std::cout <<"Lepton Charge = "<<VLepQ[0]<<std::endl;
  std::cout <<"Particle Flow Isolation (I_e<0.20, I_mu<0.17) = "<< VLepPfIso[0]<<std::endl;
  std::cout <<"-----------------------------------------------------"<<std::endl;
  std::cout <<"Lepton 1"<<std::endl;
  std::cout <<"Lepton type (1=muon, -1=electron)="<<VLepType[1]<<std::endl;
  std::cout <<"(px, py, pz, E) = ("<< VLepPx[1]<<" , "<<VLepPy[1]<<" , "<<VLepPz[1]<<" , "<<VLepE[1]<<")"<<std::endl;
  std::cout <<"p_T = "<<VLepPt[1]<<std::endl;
  std::cout <<"Lepton Charge = "<<VLepQ[1]<<std::endl;
  std::cout <<"Particle Flow Isolation (I_e<0.20, I_mu<0.17) = "<< VLepPfIso[1]<<std::endl;

    */
    h_diMassZ8.  fill(DataType, dimass,  PUweight);
    if(b_step4){
    c_step8.fill(DataType, PUweight);

    h_vertMulti8.   fill(DataType,vertMulti ,  PUweight);
    h_diMass8.  fill(DataType, dimass,  PUweight);
    h_lepPt8.   fill(DataType, VLepPt,    PUweight);
    h_lepEta8.  fill(DataType, VLepEta ,  PUweight);
    h_jetPt8.   fill(DataType, *jetPt ,   PUweight);
    h_jetMulti8.fill(DataType, jetMulti , PUweight);
    h_metEt8.   fill(DataType, *metEt ,   PUweight);
    h_btagN8.   fill(DataType, btagmulti ,PUweight);

    STEP8=1;

    }
  }

  if(b_step1 && b_step2 && b_step3 && b_step4 && b_step5 && b_step6 && b_step7 && b_step9){

    c_step9.fill(DataType, PUweight);

  }

  /*
  if ( (int)totalEventCount%250==0 )
    {
  std::cout <<"================================================================"<<std::endl;
  std::cout <<"Event Number = "<< eventNumber<<std::endl;
  std::cout <<"-----------------------------------------------------"<<std::endl;
  std::cout <<"Lepton 0:"<<std::endl;
  std::cout <<"Lepton type (1=muon, -1=electron)="<<VLepType[0]<<std::endl;
  std::cout <<"(px, py, pz, E) = ("<< VLepPx[0]<<" , "<<VLepPy[0]<<" , "<<VLepPz[0]<<" , "<<VLepE[0]<<")"<<std::endl;
  std::cout <<"p_T = "<<VLepPt[0]<<std::endl;
  std::cout <<"Lepton Charge = "<<VLepQ[0]<<std::endl;
  std::cout <<"Particle Flow Isolation (I_e<0.20, I_mu<0.17) = "<< VLepPfIso[0]<<std::endl;
  std::cout <<"-----------------------------------------------------"<<std::endl;
  std::cout <<"Lepton 1"<<std::endl;
  std::cout <<"Lepton type (1=muon, -1=electron)="<<VLepType[1]<<std::endl;
  std::cout <<"(px, py, pz, E) = ("<< VLepPx[1]<<" , "<<VLepPy[1]<<" , "<<VLepPz[1]<<" , "<<VLepE[1]<<")"<<std::endl;
  std::cout <<"p_T = "<<VLepPt[1]<<std::endl;
  std::cout <<"Lepton Charge = "<<VLepQ[1]<<std::endl;
  std::cout <<"Particle Flow Isolation (I_e<0.20, I_mu<0.17) = "<< VLepPfIso[1]<<std::endl;
  std::cout <<"******************************************************"<< std::endl;
  std::cout <<"step1: "<<b_step1<<" STEP1= "<<STEP1<<std::endl;
  std::cout <<"step2: "<<b_step2<<" STEP2= "<<STEP2<<std::endl;
  std::cout <<"step3: "<<b_step3<<" STEP3= "<<STEP3<<std::endl;
  std::cout <<"step4: "<<b_step4<<" STEP4= "<<STEP4<<std::endl;
  std::cout <<"step5: "<<b_step5<<" STEP5= "<<STEP5<<std::endl;
  std::cout <<"step6: "<<b_step6<<" STEP6= "<<STEP6<<std::endl;
  std::cout <<"step7: "<<b_step7<<" STEP7= "<<STEP7<<std::endl;
  std::cout <<"step8: "<<b_step8<<" STEP8= "<<STEP8<<std::endl;
    };

  */

   return kTRUE;
}

void EMuAnalysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.


}

void EMuAnalysis::Terminate()
{
 
 
  TFile *f = new TFile("/scratch/hh/current/cms/user/asincruz/NTuples/EMu_AnalysisM12.root","RECREATE");


h_testplotter.write();
h_testplotter2.write();

 TDirectory *d0=(TDirectory*)f->mkdir("Step0");
 d0->cd();
    h_vertMulti0.   write();
  h_lepQ0.write();
  h_combIso0.write();
  h_combIso1.write();
  h_PfIso1.write();
  h_PfIso0.write();

  h_lepPt0.    write();
  h_lepEta0.   write();
  h_lepType0.  write();
  h_lepMulti0. write();

  h_lepMulti1. write();

  d0->Clear();
  d0->Close();


  TDirectory *d3=(TDirectory*)f->mkdir("Step3");
  d3->cd();
    h_vertMulti3.   write();
  h_diMass3.   write();
  h_lepPt3.    write();
  h_lepEta3.   write();
  h_jetPt3.    write();
  h_jetMulti3. write();
  h_metEt3.    write();
  h_btagN3.    write();
  d3->Close();
  d3->Clear();

  TDirectory *d3a=(TDirectory*)f->mkdir("Step3a");
  d3a->cd();
    h_vertMulti3a.   write();
  h_diMass3a.   write();
  h_lepPt3a.    write();
  h_lepEta3a.   write();
  h_jetPt3a.    write();
  h_jetMulti3a. write();
  h_metEt3a.    write();
  h_btagN3a.    write();
  d3a->Close();
  d3a->Clear();

  TDirectory *d4=(TDirectory*)f->mkdir("Step4");
  d4->cd();
    h_vertMulti4.   write();
  h_diMass4.   write();
  h_lepPt4.    write();
  h_lepEta4.   write();
  h_jetPt4.    write();
  h_jetMulti4. write();
  h_metEt4.    write();
  h_btagN4.    write();
  d4->Close();
  d4->Clear();

   TDirectory *d5=(TDirectory*)f->mkdir("Step5");
   d5->cd();
    h_vertMulti5.   write();
  h_diMass5.   write();
  h_lepPt5.    write();
  h_lepEta5.   write();
  h_jetPt5.    write();
  h_jetMulti5. write();
  h_metEt5.    write();
  h_btagN5.    write();
  d5->Close();
  d5->Clear();

  TDirectory *d6=(TDirectory*)f->mkdir("Step6");
  d6->cd();
    h_vertMulti6.   write();
  h_diMass6.   write();
  h_lepPt6.    write();
  h_lepEta6.   write();
  h_jetPt6.    write();
  h_jetMulti6. write();
  h_metEt6.    write();
  h_btagN6.    write();
  d6->Close();
  d6->Clear();

  TDirectory *d7=(TDirectory*)f->mkdir("Step7");
  d7->cd();
    h_vertMulti7.   write();
  h_diMass7.   write();
  h_lepPt7.    write();
  h_lepEta7.   write();
  h_jetPt7.    write();
  h_jetMulti7. write();
  h_metEt7.    write();
  h_btagN7.    write();
  d7->Close();
  d7->Clear();

  TDirectory *d8=(TDirectory*)f->mkdir("Step8");
  d8->cd();
    h_vertMulti8.   write();
  h_diMass8.   write();
  h_lepPt8.    write();
  h_lepEta8.   write();
  h_jetPt8.    write();
  h_jetMulti8. write();
  h_metEt8.    write();
  h_btagN8.    write();
  d8->Close();
  d8->Clear();

  TDirectory *dpk=(TDirectory*)f->mkdir("DYPeak");
  dpk->cd();
  h_diMassZ4.  write();
  h_diMassZ5.  write();
  h_diMassZ6.  write();
  h_diMassZ7.  write();
  h_diMassZ8.  write();
  dpk->Close();
  dpk->Clear();

  c_step0.coutNs();

  c_step1.coutNs();
  c_step2.coutNs();

  c_step3.coutNs();
  c_step4.coutNs();
  c_step5.coutNs();
  c_step6.coutNs();
  c_step7.coutNs();
  c_step7.coutNsig("t#bar{t} signal");
  c_step8.coutNs();
  c_step8.coutNsig("t#bar{t} signal");
  c_step9.coutNs();
  c_step9.coutNsig("t#bar{t} signal");


  std::cout <<"Number of total events processed = "<<  testcounter << std::endl;

  f->Close();

}
