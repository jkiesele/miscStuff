#include "TH1D.h"




double sq(double var)
{

  return var*var;

}

TH1D ratiohisto(TH1D * hist1, TH1D * hist2)
{
  TH1D hratio;
  hratio = *((TH1D*)hist1->Clone());



  for(int bin=1; bin<hist1->GetNbinsX()+1; bin++){
    double entry1=hist1->GetBinContent(bin);
    double entry2=hist2->GetBinContent(bin);
    double err1=hist1->GetBinError(bin);
    double err2=hist2->GetBinError(bin);

    double ratio=entry1/entry2;
    double binerr=sqrt(sq((entry1/(entry2*entry2)*err2)) + sq((err1/entry2)));

    hratio.SetBinContent(bin, ratio);
    hratio.SetBinError(bin, binerr);


  }


    return hratio;


}

