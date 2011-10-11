// -*- C++ -*-
//
// Package:    NTupleWriter_two
// Class:      NTupleWriter_two
// 
/**\class NTupleWriter_two NTupleWriter_two.cc TopAnalysis/NTupleWriter_two/src/NTupleWriter_two.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jan Kieseler,,,DESY
//         Created:  Thu Aug 11 16:37:05 CEST 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "TopAnalysis/TopAnalyzer/interface/PUEventWeight.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include <string>
 

//
// class declaration
//

class NTupleWriter : public edm::EDAnalyzer {
   public:
      explicit NTupleWriter(const edm::ParameterSet&);
      ~NTupleWriter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

  edm::InputTag jets_, met_, weight_, trigResults_, dType_ , elecs_, muons_, vertices_ ;
  bool includeTrig_;
  edm::ParameterSet conf_;



  TTree* Ntuple;

  int runno;
  int lumibl;
  int eventno;

  std::vector<std::string> datatype;

  ////////dileptons and leptons/////
  std::vector<double> VlepPt;
  std::vector<double> VlepEta ;
  std::vector<double> VlepPhi ;
  std::vector<double> VlepE ;
  std::vector<double> VlepPx ;
  std::vector<double> VlepPy ;
  std::vector<double> VlepPz ;
  std::vector<int>    VlepQ ; //and more possible
  std::vector<int>    VlepType; // -1 for electron, 1 for muon
  std::vector<double> VlepPfIso;
  std::vector<double> VlepCombIso;

  /////////jets///////////
  std::vector<double> VjetPt;
  std::vector<double> VjetEta;


  std::vector<double> VjetPhi;

  std::vector<double> VjetBTagTCHE;
  std::vector<double> VjetBTagSSVHE;

  int jetMulti;

  /////////met///////////
  std::vector<double> VmetEt;

  std::vector<double> VmetPhi;

  ////////triggers/////////
  std::vector<std::string> VfiredTriggers;

  ///////////weight//////////
  double PUweight;


  ////Vertices////

  int vertMulti;





};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
NTupleWriter::NTupleWriter(const edm::ParameterSet& iConfig):
  conf_(iConfig)
{

  muons_             =iConfig.getParameter<edm::InputTag>    ( "muons"      );
  elecs_             =iConfig.getParameter<edm::InputTag>    ( "elecs"      );
  jets_              =iConfig.getParameter<edm::InputTag>    ( "jets"           );
  met_               =iConfig.getParameter<edm::InputTag>    ( "met"            );
  vertices_          =iConfig.getParameter<edm::InputTag>    ( "vertices"            );
  


  weight_            =iConfig.getParameter<edm::InputTag>    ("weight"          );
  dType_             =iConfig.getParameter<edm::InputTag>    ("datatype"          );
  includeTrig_       =iConfig.getParameter<bool>             ("includeTrigger"          );
  trigResults_       =iConfig.getParameter<edm::InputTag>    ( "triggerResults" );


}


NTupleWriter::~NTupleWriter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
NTupleWriter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   PUweight = getPUEventWeight(iEvent, weight_);

   /////////////clear vectors!!////////////////////////////////////

   runno=0;
   lumibl=0;
   eventno=0;

   datatype.clear();

   ////////dileptons and leptons/////
   VlepPt.clear();
   VlepEta.clear() ;
   VlepPhi.clear() ;
   VlepE.clear() ;
   VlepPx.clear() ;
   VlepPy.clear() ;
   VlepPz.clear() ;
   VlepQ.clear() ; 
   VlepType.clear() ;
   VlepPfIso.clear();
   VlepCombIso.clear();


   /////////jets///////////
   VjetPt.clear();
   VjetEta.clear();
   VjetPhi.clear();

   VjetBTagTCHE.clear();
   VjetBTagSSVHE.clear();


   /////////met///////////
   VmetEt.clear();
   VmetPhi.clear();


   /////////Triggers/////////
   VfiredTriggers.clear();

   //////vertices
   vertMulti=-1;


  datatype.push_back(dType_.encode());


  Handle<edm::View< pat::Jet > > jets;
  iEvent.getByLabel(jets_, jets);

  Handle<edm::View<pat::MET> > met;
  iEvent.getByLabel(met_, met);

  Handle<std::vector<pat::Muon> > muons;
  iEvent.getByLabel(muons_, muons);

  Handle<std::vector<pat::Electron> > electrons;
  iEvent.getByLabel(elecs_, electrons);

  //////////////////////////////dilepton and lepton properties/////////////////////



   //////fill pfiso///maybe other iso??

  std::vector<pat::Muon>::const_iterator amuon  = muons->begin();
  std::vector<pat::Electron>::const_iterator anelectron  = electrons->begin();

  bool writemuon=false;
  bool writeelec=false;

  while(amuon < muons->end() || anelectron < electrons->end()){ //sort input leptons by pt

    writemuon=false;
    writeelec=false;

    if(amuon < muons->end() && anelectron < electrons->end()){
      if( amuon->pt() > anelectron->pt()) writemuon=true ;
      else writeelec=true;
    }
    if(anelectron == electrons->end())  writemuon=true ;
    if(amuon == muons->end())           writeelec=true;

    if(writemuon){
      //Fill muonstuff
      VlepPt.push_back(amuon->pt());
      VlepEta.push_back(amuon->eta()) ;
      VlepPhi.push_back(amuon->phi()) ;
      VlepE.push_back(amuon->energy()) ;
      VlepPx.push_back(amuon->px()) ;
      VlepPy.push_back(amuon->py()) ;
      VlepPz.push_back(amuon->pz()) ;
      VlepQ.push_back(amuon->charge()) ; 
      VlepType.push_back(1) ;
      VlepPfIso.push_back(((amuon->chargedHadronIso()+amuon->neutralHadronIso()+amuon->photonIso()) / amuon->pt()));
      VlepCombIso.push_back((amuon->trackIso()+amuon->caloIso())/amuon->pt());

      amuon++;
      
    }
    if(writeelec){
      //Fill elestuff 
      VlepPt.push_back(anelectron->pt());
      VlepEta.push_back(anelectron->eta()) ;
      VlepPhi.push_back(anelectron->phi()) ;
      VlepE.push_back(anelectron->energy()) ;
      VlepPx.push_back(anelectron->px()) ;
      VlepPy.push_back(anelectron->py()) ;
      VlepPz.push_back(anelectron->pz()) ;
      VlepQ.push_back(anelectron->charge()) ; 
      VlepType.push_back(-1) ;
      VlepPfIso.push_back(((anelectron->chargedHadronIso()+anelectron->neutralHadronIso()+anelectron->photonIso()) / anelectron->pt()));

      if( fabs(anelectron->superCluster()->eta()) > 1.479 ){
	VlepCombIso.push_back((anelectron->dr03TkSumPt()+anelectron->dr03EcalRecHitSumEt()+anelectron->dr03HcalTowerSumEt())/TMath::Max(20.,anelectron->pt()));
      }
      if( fabs(anelectron->superCluster()->eta()) <= 1.479 ){
	VlepCombIso.push_back((anelectron->dr03TkSumPt()+TMath::Max(0.,anelectron->dr03EcalRecHitSumEt()-1.)+anelectron->dr03HcalTowerSumEt())/TMath::Max(20.,anelectron->pt()));
      }

      anelectron++;
      
    }
  }

//   if(VlepPt.size() >2){
//     for(unsigned int i=0; i< VlepPt.size(); i++){
//       std::cout << VlepPt[i] << "    " << VlepType[i] << std::endl;
//     }
//     std::cout << '\n' << std::endl;
//   }


   ///////////////////////////////////Jet properties/////////////////////////

   jetMulti=jets->size();

   for (edm::View<pat::Jet>::const_iterator ajet  = jets->begin() ; ajet != jets->end(); ajet++)
    {
        VjetPt.push_back(ajet->pt());
	VjetEta.push_back(ajet->eta());
	VjetPhi.push_back(ajet->phi());

	VjetBTagTCHE.push_back(ajet->bDiscriminator("trackCountingHighEffBJetTags"));
	VjetBTagSSVHE.push_back(ajet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags"));
    }








   ///////////////////////////////////Met properties///////////////////////////

   for (edm::View<pat::MET>::const_iterator Met  = met->begin() ; Met != met->end(); Met++)
     {
       VmetEt.push_back(Met->et());
       VmetPhi.push_back(Met->phi());
     }


   //////////////////////////////Event Info/////////////////////
  runno= iEvent.id().run();
  lumibl=iEvent.id().luminosityBlock();
  eventno=iEvent.id().event();


  //////////////////Trigger Stuff///////////////hltPaths_[i].c_str()



  if(includeTrig_){
    Handle<TriggerResults> trigResults;
    iEvent.getByLabel(trigResults_, trigResults);



    if(!trigResults.failedToGet()){
      int n_Triggers = trigResults->size();
      TriggerNames trigName = iEvent.triggerNames(*trigResults);

      for(int i_Trig = 0; i_Trig<n_Triggers; ++i_Trig){
	if(trigResults.product()->accept(i_Trig)){
	  VfiredTriggers.push_back(trigName.triggerName(i_Trig));
	}
      }
    }
  }

  edm::Handle<std::vector<reco::Vertex> > vertices;
  iEvent.getByLabel(vertices_, vertices);


  vertMulti=vertices->size();

  Ntuple ->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
NTupleWriter::beginJob()
{
  edm::Service<TFileService> fs;

  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  Ntuple=fs->make<TTree>("NTuple","NTuple");


  ///////////////dilepton and lepton properties//////////
  Ntuple->Branch("lepPt",&VlepPt);
  Ntuple->Branch("lepEta",&VlepEta);
  Ntuple->Branch("lepPhi",&VlepPhi);
  Ntuple->Branch("lepE",&VlepE);
  Ntuple->Branch("lepPx",&VlepPx);
  Ntuple->Branch("lepPy",&VlepPy);
  Ntuple->Branch("lepPz",&VlepPz);
  Ntuple->Branch("lepQ",&VlepQ);
  Ntuple->Branch("lepType",&VlepType);
  Ntuple->Branch("lepPfIso",&VlepPfIso);
  Ntuple->Branch("lepCombIso",&VlepCombIso);


  /////////////jet properties////////////
  Ntuple->Branch("jetPt",&VjetPt);
  Ntuple->Branch("jetEta",&VjetEta);
  Ntuple->Branch("jetPhi",&VjetPhi);

  Ntuple->Branch("jetBTagTCHE",&VjetBTagTCHE);
  Ntuple->Branch("jetBTagSSVHE",&VjetBTagSSVHE);

  Ntuple->Branch("jetMulti",&jetMulti, "jetMulti/I");

  /////////////met properties///////////
  Ntuple->Branch("metEt",&VmetEt);

  Ntuple->Branch("metPhi",&VmetPhi);


  ///////////event info///////////
  Ntuple->Branch("runNumber",&runno, "runNumber/I");
  Ntuple->Branch("lumiBlock",&lumibl,"lumiBlock/I");
  Ntuple->Branch("eventNumber",&eventno, "eventNumber/I");

  Ntuple->Branch("dataType",&datatype);


  ////////////triggers//////////////////
  if(includeTrig_) Ntuple->Branch("firedTriggers",&VfiredTriggers);

  ////////////weight////////////
  Ntuple->Branch("PUweight",&PUweight, "PUweight/D");

  /////////vertices

  Ntuple->Branch("vertMulti",&vertMulti, "vertMulti/I");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
NTupleWriter::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
NTupleWriter::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
NTupleWriter::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
NTupleWriter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
NTupleWriter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NTupleWriter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NTupleWriter);
