// Macro per calcolare la velocità dei muoni
void Beta(TString fname="../LONG/wave_0_reco.root"){
  //fname="../GROUPB/SHORT/wave_0_reco.root";
  //  fname="../GROUPB/FLIP/wave_0_reco.root";
  TFile* F0 = TFile::Open(fname.Data());
  TTree* ToF0 = (TTree*) F0->Get("tree");
  ToF0->SetName("ToF0");
  ToF0->SetTitle("ToF0");
  fname.ReplaceAll("0_reco.root","1_reco.root");
  TFile* F1 = TFile::Open(fname.Data());
  TTree* ToF1 = (TTree*) F1->Get("tree");
  ToF1->SetName("ToF1");
  ToF1->SetTitle("ToF1");
  fname.ReplaceAll("1_reco.root","2_reco.root");
  TFile* F2 = TFile::Open(fname.Data());
  TTree* ToF2 = (TTree*) F2->Get("tree");
  ToF2->SetName("ToF2");
  ToF2->SetTitle("ToF2");
  fname.ReplaceAll("2_reco.root","3_reco.root");
  TFile* F3 = TFile::Open(fname.Data());
  TTree* ToF3 = (TTree*) F3->Get("tree");
  ToF3->SetName("ToF3");
  ToF3->SetTitle("ToF3");
  
  ToF0->AddFriend(ToF1);
  ToF0->AddFriend(ToF2);
  ToF0->AddFriend(ToF3);

  ToF0->SetAlias("T0","(ToF0.Time)");
  ToF0->SetAlias("T1","(ToF1.Time-(-5.01928e+01-4.97773e+01)/2.)");
  ToF0->SetAlias("T2","(ToF2.Time-(-2.81118e+01-2.63210e+01)/2.)");
  ToF0->SetAlias("T3","(ToF3.Time-(-2.90898e+01-2.68916e+01)/2.)");

  TCanvas * c1 = new TCanvas();
  TH1D* h1 = new TH1D("h1","",2000,-100,100);
  ToF0->Draw("T1-T0>>h1","","colz");
  h1->Fit("gaus","L");
  gPad->SetLogy();

  TCanvas * c2 = new TCanvas();
  TH1D* h2 = new TH1D("h2","",2000,-100,100);
  ToF0->Draw("T2-T0>>h2","","colz");
  h2->Fit("gaus","L");
  gPad->SetLogy();

  TCanvas * c3 = new TCanvas();
  TH1D* h3 = new TH1D("h3","",2000,-100,100);
  ToF0->Draw("T3-T0>>h3","","colz");
  h3->Fit("gaus","L");
  gPad->SetLogy();

  TCanvas * c4 = new TCanvas();
  ToF0->SetAlias("beta","(365/(T0-T3))/29.979");
  ToF0->SetAlias("TRMS","(sqrt((T1*T1+T2*T2+T3*T3)/3.-(T1+T2+T3)*(T1+T2+T3)/9.))");
  TH2D* h2b = new TH2D("h2b","",200,-2,2,200,-2,2);
  ToF0->Draw("1./beta:log10(TRMS)>>h2b","","colz");

  TCanvas * c5 = new TCanvas();
  TH1D* h4 = new TH1D("h4","",200,-2,0);
  ToF0->Draw("1./beta>>h4","abs(1/beta+1)<1");
  h4->Fit("gaus","L");
  return;
}
