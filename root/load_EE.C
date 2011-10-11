{
  TFile *f1 = new TFile("dcap://dcache-cms-dcap.desy:22125/pnfs/desy.de/cms/tier2/store/user/jkiesele/Trees/ee_1fb.root");
  TDirectory *d = (TDirectory*) f1->Get("writeNTuple");
  TTree *t = (TTree*)d->Get("NTuple");
  t->Process("EE_Analysis.C++");



}
