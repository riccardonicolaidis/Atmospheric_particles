// Macro per calcolare la velocità dei muoni
void Beta(TString fname="DATA/LONG/wave_0_reco.root"){
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
  ToF0->SetAlias("T1","(ToF1.Time-(-4.97815e+01-5.01835e+01)/2.)");
  ToF0->SetAlias("T2","(ToF2.Time-(-2.63188e+01-2.81133e+01)/2.)");
  ToF0->SetAlias("T3","(ToF3.Time-(-2.68886e+01-2.90723e+01)/2.)");

	gStyle->SetOptFit(0111);
   gStyle->SetStatFontSize(0.02);
	
  TCanvas * c1 = new TCanvas();
  TF1* f1 = new TF1("f1","gaus + exp(-x/[3])",-6,30);
	f1->SetParameter(0,300); 
   f1->SetParameter(1,10);
   f1->SetParameter(2,10);          
	f1->SetParameter(3,1000);  
	f1->SetParNames("Constant","Mean","Sigma","p3");
   TH1D* h1 = new TH1D("h1",";T1-T0;Events",100,-10,30);
  ToF0->Draw("T1-T0>>h1","","colz");
  h1->Fit("f1","L");
  gPad->SetLogy();
  c1->SaveAs("IMAGES/T1_T0.png");
	
return;
  TCanvas * c2 = new TCanvas();
  TF1* f2 = new TF1("f2","gaus + gaus(4) + exp(-x/[3])",-20,40);
	f2->SetParameter(0,3000); 
   f2->SetParameter(1,10);
   f2->SetParameter(2,2);          
	f2->SetParameter(3,1000); 
	f2->SetParameter(4,10); 
	f2->SetParameter(5,25); 
	f2->SetParameter(6,1); 
	f2->SetParNames("Constant","Mean","Sigma","p3","p4","p5","p6");
  TH1D* h2 = new TH1D("h2",";T2-T0;Events",100,-100,100);
  ToF0->Draw("T2-T0>>h2","","colz");
  h2->Fit("f2","L");
  gPad->SetLogy();
	c2->SaveAs("IMAGES/T2_T0.png");
	
  TCanvas * c3 = new TCanvas();
  //TF1* f3 = new TF1("f3","gaus +[7]/x + gaus(4) + exp(-x/[3])",-100,100);
	TF1* f3 = new TF1("f3","gaus +[3] /(1 + (x/[4])**[5])",-100,100);
	f3->SetParameter(0,3000); 
   f3->SetParameter(1,5);
   f3->SetParameter(2,9);          
	f3->SetParameter(3,10);  
	f3->SetParameter(4,2e-9); 
	f3->SetParameter(5,20); 
	//f3->SetParameter(6,1);
	//f3->SetParameter(7,1); 
 	f3->SetParNames("Constant","Mean","Sigma","p3");
	TH1D* h3 = new TH1D("h3",";T3-T0;Events",100,-100,100);
  ToF0->Draw("T3-T0>>h3","","colz");
  h3->Fit("f3","L");
  gPad->SetLogy();
  c3->Draw();
  c3->SaveAs("IMAGES/T3_T0.png");
	
/*
  TCanvas * c4 = new TCanvas();
  ToF0->SetAlias("beta","(330.5/(T0-T3))/29.979");
  ToF0->SetAlias("TRMS","(sqrt((T1*T1+T2*T2+T3*T3)/3.-(T1+T2+T3)*(T1+T2+T3)/9.))");
  TH2D* h2b = new TH2D("h2b",";log10(RMS(#beta));1/#beta",40,-1.2,0.5,40,-1.5,-0.4);
  ToF0->Draw("1./beta:log10(TRMS)>>h2b","","colz");
  h2b->SetStats(0);
	c4->SaveAs("IMAGES/beta_error2D.png");
	
  TCanvas * c5 = new TCanvas();
  TH1D* h5 = new TH1D("h5",";1/#beta;",100,-2,0);
  ToF0->Draw("1./beta>>h5","abs(1/beta+1)<1","colz");
  c5->SaveAs("IMAGES/beta_peak.png");*/
  return;
}
