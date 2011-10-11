{
  TFile *f1 = new TFile("/scratch/hh/current/cms/user/kieseler/Tuples_0610/ee_Full.root");
  TDirectory *d = (TDirectory*) f1->Get("writeNTuple");
  TTree *t = (TTree*)d->Get("NTuple");
  t->Process("EE_Analysis.C++");



}
