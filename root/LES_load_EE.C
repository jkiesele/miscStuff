{
  TFile *f1 = TFile::Open(" dcap://dcache-cms-dcap.desy.de//pnfs/desy.de/cms/tier2/store/user/jkiesele/Trees/corrLE/ee_Full.root");
  TDirectory *d = (TDirectory*) f1->Get("writeNTuple");
  TTree *t = (TTree*)d->Get("NTuple");
  t->Process("EE_Analysis.C++");



}
