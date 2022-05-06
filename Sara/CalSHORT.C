void CalSHORT(TString fname="DATA/SHORT/wave_0_reco.root"){
   //cout<<fname.Data()<<endl;
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

	gStyle->SetOptFit(0111);
   gStyle->SetStatFontSize(0.02);
	TF1* f1 = new TF1("f1","gaus + exp(-x/[3])",0,50e-9);
	f1->SetParameter(0,300); 
   f1->SetParameter(1,-50);
   f1->SetParameter(2,2);          
	f1->SetParameter(3,1000);  
	f1->SetParNames ("Constant","Mean","Sigma","p3");
   TCanvas * c1 = new TCanvas();
   TH1D* h1 = new TH1D("h1",";ToF1-ToF0 [samples]; Events",80,-56,-43);
   ToF0->Draw("ToF1.Time-ToF0.Time>>h1","","colz");
   h1->Fit("f1","L");  
   gPad->SetLogy();
   //h1->SetStats(1);
   c1->SaveAs("IMAGES/ToF1ToF0.png");
   c1->Draw();
  
   TF1* f2 = new TF1("f2","gaus + exp(-x/[3])",0,50e-9);
	f2->SetParameter(0,300); 
   f2->SetParameter(1,-26);
   f2->SetParameter(2,2);          
	f2->SetParameter(3,1000);  
   f2->SetParNames ("Constant","Mean","Sigma","p3");
   TCanvas * c2 = new TCanvas();
   TH1D* h2 = new TH1D("h2",";ToF2-ToF0 [samples]; Events",80,-33,-19);
   ToF0->Draw("ToF2.Time-ToF0.Time>>h2","","colz");
   h2->Fit("f2","L");
   gPad->SetLogy();
   c2->SaveAs("IMAGES/ToF2ToF0.png");
   c2->Draw();
	
	//TF1* f3 = new TF1("f3","gaus",0,50e-9);
	//f3->SetParameter(0,300); 
   //f3->SetParameter(1,-26);
   //f3->SetParameter(2,2);          
   TCanvas * c3 = new TCanvas();
   TH1D* h3 = new TH1D("h3",";ToF3-ToF0 [samples]; Events",80,-34,-20);
   ToF0->Draw("ToF3.Time-ToF0.Time>>h3","","colz");
   //h3->Fit("f3","L", "");
   h3->Fit("gaus","L", "");
   gPad->SetLogy();
   c3->SaveAs("IMAGES/ToF3ToF0.png");
   c3->Draw();
  
  return;

}
