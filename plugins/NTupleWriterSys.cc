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

class NTupleWriterSys : public edm::EDAnalyzer {
   public:
      explicit NTupleWriterSys(const edm::ParameterSet&);
      ~NTupleWriterSys();

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

  edm::InputTag  weight_,  dType_ , elecs_, muons_; // noCutElecs_, noCutMuons_, vertices_ ;
  
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
  std::vector<int>    VlepQ ;             //and more possible
  std::vector<int>    VlepType;           // -1 for electron, 1 for muon
  std::vector<double> VlepPfIso;
  std::vector<double> VlepCombIso;
  std::vector<bool> VpassedId;

//   std::vector<double> VNoCutLepPt;
//   std::vector<double> VNoCutLepEta ;
//   std::vector<double> VNoCutLepPhi ;
//   std::vector<double> VNoCutLepE ;
//   std::vector<double> VNoCutLepPx ;
//   std::vector<double> VNoCutLepPy ;
//   std::vector<double> VNoCutLepPz ;
//   std::vector<int>    VNoCutLepQ ;             //and more possible
//   std::vector<int>    VNoCutLepType;           // -1 for electron, 1 for muon
//   std::vector<double> VNoCutLepPfIso;
//   std::vector<double> VNoCutLepCombIso;


  ///////////weight//////////
  double PUweight;







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
NTupleWriterSys::NTupleWriterSys(const edm::ParameterSet& iConfig):
  conf_(iConfig)
{

  muons_             =iConfig.getParameter<edm::InputTag>    ( "muons"      );
  //noCutMuons_             =iConfig.getParameter<edm::InputTag>    ( "noCutMuons"      );
  elecs_             =iConfig.getParameter<edm::InputTag>    ( "elecs"      );
  //noCutElecs_             =iConfig.getParameter<edm::InputTag>    ( "noCutElecs"      );
  


  weight_            =iConfig.getParameter<edm::InputTag>    ("weight"          );
  dType_             =iConfig.getParameter<edm::InputTag>    ("datatype"          );


}


NTupleWriterSys::~NTupleWriterSys()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
NTupleWriterSys::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
   VpassedId.clear();





  datatype.push_back(dType_.encode());


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

      if(amuon-> isGlobalMuon() 
         && amuon->  isTrackerMuon()
         && fabs(amuon->  dB()) < 0.02
         && amuon->pfCandidateRef()->muonRef().isNonnull() // associated pfCandidate
         && amuon->pfCandidateRef()->muonRef()->innerTrack().isNonnull()
         && amuon->pfCandidateRef()->muonRef()->globalTrack().isNonnull()
         && amuon->pfCandidateRef()->muonRef()->innerTrack()->numberOfValidHits() >10
         && amuon->pfCandidateRef()->muonRef()->outerTrack()->hitPattern().numberOfValidHits() > 0
         && amuon->pfCandidateRef()->muonRef()->globalTrack()->normalizedChi2() < 10.0 )
	VpassedId.push_back(true) ;
      
      else VpassedId.push_back(false) ;

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

      if(fabs(anelectron->dB()) < 0.04
         //&& anelectron->electronID("eidTightMC")== 0
         && (int)anelectron->electronID("eidTightMC") & 5 == 5
         //&& (int)anelectron->electronID("eidTightMC")  == 5
         //&& test_bit(anelectron->electronID("eidTightMC"), 0)
         && anelectron-> pfCandidateRef()->gsfTrackRef().isNonnull()
         && anelectron-> pfCandidateRef()->gsfTrackRef()->trackerExpectedHitsInner().numberOfLostHits() < 2)
	VpassedId.push_back(true) ;
      
      else VpassedId.push_back(false) ;

      anelectron++;
      
    }
  }






   //////////////////////////////Event Info/////////////////////
  runno= iEvent.id().run();
  lumibl=iEvent.id().luminosityBlock();
  eventno=iEvent.id().event();




  Ntuple ->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
NTupleWriterSys::beginJob()
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
  Ntuple->Branch("passedId",&VpassedId);






  ///////////event info///////////
  Ntuple->Branch("runNumber",&runno, "runNumber/I");
  Ntuple->Branch("lumiBlock",&lumibl,"lumiBlock/I");
  Ntuple->Branch("eventNumber",&eventno, "eventNumber/I");

  Ntuple->Branch("dataType",&datatype);


  ////////////weight////////////
  Ntuple->Branch("PUweight",&PUweight, "PUweight/D");


}

// ------------ method called once each job just after ending the event loop  ------------
void 
NTupleWriterSys::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
NTupleWriterSys::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
NTupleWriterSys::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
NTupleWriterSys::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
NTupleWriterSys::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NTupleWriterSys::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NTupleWriterSys);
