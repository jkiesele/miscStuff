{
  TFile *f1 = TFile::Open(" dcap://dcache-cms-dcap.desy.de//pnfs/desy.de/cms/tier2/store/user/jkiesele/Trees/emu_1fb.root");
  TDirectory *d = (TDirectory*) f1->Get("writeNTuple");
  TTree *t = (TTree*)d->Get("NTuple");
  t->Process("EMuAnalysis.C++");


 
}
