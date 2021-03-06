#include "Bplusdsigmadpt_1ptbins.h"
#include "iostream"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TLine.h>
#include <TLegend.h>
#include "TLegendEntry.h"
using namespace std;
void PlotXsec(){
    TString inputmc;
    TString cut;
    TString seldata_2y;
    TString selmc;
    TString selmcgen;
//    inputmc="/net/hisrv0001/home/tawei/HeavyFlavor_20131030/Bmeson_PbPbAna/Samples/BntupleMC_BfinderMC_Pyquen_CMSSW742_Unquenched_PbPb_2760GeV_step3_BuKp_20150526_100kevt_20150604_20150608.root";
//    inputmc="/net/hisrv0001/home/tawei/HeavyFlavor_20131030/Bmeson_PbPbAna/Samples/BntupleMC_BfinderMC_Pyquen_CMSSW742_Unquenched_PbPb_2760GeV_GEN_SIM_PU_BuKp_20150526_100kevt_20150505_20150609.root";
    inputmc="/afs/cern.ch/user/t/twang/public/Files/BntupleMC_BfinderMC_Pyquen_CMSSW742_Unquenched_PbPb_2760GeV_GEN_SIM_PU_BuKp_20150526_100kevt_20150505_20150609.root";

//    cut="((abs(mu1eta)<1.0 && mu1pt>3.4) || (abs(mu1eta)>1.0 && abs(mu1eta)<1.5 && mu1pt>(5.8-2.4*abs(mu1eta))) || (abs(mu1eta)>1.5 && abs(mu1eta)<2.4 && mu1pt>(3.4-0.78*abs(mu1eta))))&&((abs(mu2eta)<1.0 && mu2pt>3.4) || (abs(mu2eta)>1.0 && abs(mu2eta)<1.5 && mu2pt>(5.8-2.4*abs(mu2eta))) || (abs(mu2eta)>1.5 && abs(mu2eta)<2.4 && mu2pt>(3.4-0.78*abs(mu2eta))))&&mu1TMOneStationTight && mu2TMOneStationTight && mu1isGlobalMuon && mu2isGlobalMuon && mu1trackerhit>10 && mu2trackerhit>10 && mu1InPixelLayer>1 && mu2InPixelLayer>1 && mu1normchi2<1.8 && mu2normchi2<1.8 && mu1dxyPV<3 && mu2dxyPV<3 && mu1dzPV<30 && mu2dzPV<30 && mumupt>3 && trk1Pt>1 && pt>10 && pt < 60 && mass>5&&mass<6 && abs(y)<2.4 && abs(mumumass-3.096916)<0.15 && isbestchi2 && chi2cl > 0.004345 && cos(dtheta) > 0.256418 && d0/d0Err > 6.679356";//pt10, acc muon, hp tk, SA
    cut="((abs(mu1eta)<1.0 && mu1pt>3.4) || (abs(mu1eta)>1.0 && abs(mu1eta)<1.5 && mu1pt>(5.8-2.4*abs(mu1eta))) || (abs(mu1eta)>1.5 && abs(mu1eta)<2.4 && mu1pt>(3.4-0.78*abs(mu1eta))))&&((abs(mu2eta)<1.0 && mu2pt>3.4) || (abs(mu2eta)>1.0 && abs(mu2eta)<1.5 && mu2pt>(5.8-2.4*abs(mu2eta))) || (abs(mu2eta)>1.5 && abs(mu2eta)<2.4 && mu2pt>(3.4-0.78*abs(mu2eta))))&&mu1TMOneStationTight && mu2TMOneStationTight && mu1isGlobalMuon && mu2isGlobalMuon && mu1trackerhit>10 && mu2trackerhit>10 && mu1InPixelLayer>1 && mu2InPixelLayer>1 && mu1normchi2<1.8 && mu2normchi2<1.8 && mu1dxyPV<3 && mu2dxyPV<3 && mu1dzPV<30 && mu2dzPV<30 && mumupt>3 && trk1Pt>1 && mass>5&&mass<6 && abs(y)<2.4 && abs(mumumass-3.096916)<0.15 && isbestchi2 && chi2cl > 0.004345 && cos(dtheta) > 0.256418 && d0/d0Err > 6.679356";//
//    cut="((abs(mu1eta)<1.0 && mu1pt>3.4) || (abs(mu1eta)>1.0 && abs(mu1eta)<1.5 && mu1pt>(5.8-2.4*abs(mu1eta))) || (abs(mu1eta)>1.5 && abs(mu1eta)<2.4 && mu1pt>(3.4-0.78*abs(mu1eta))))&&((abs(mu2eta)<1.0 && mu2pt>3.4) || (abs(mu2eta)>1.0 && abs(mu2eta)<1.5 && mu2pt>(5.8-2.4*abs(mu2eta))) || (abs(mu2eta)>1.5 && abs(mu2eta)<2.4 && mu2pt>(3.4-0.78*abs(mu2eta)))) && mu1TMOneStationTight && mu2TMOneStationTight && mumupt>3 && trk1Pt>1 && abs(y)<2.4 && trk1Chi2ndf < 5";
//    cut="mu1TMOneStationTight && mu2TMOneStationTight && mumupt>3 && trk1Pt>1 && abs(y)<2.4 && trk1Chi2ndf < 5";
    selmc=Form("abs(y)<2.4&&gen==23333&&%s",cut.Data());
    selmcgen="abs(y)<2.4&&abs(pdgId)==521&&isSignal==1";
    TFile *infMC = new TFile(inputmc.Data());
    TTree *ntMC = (TTree*)infMC->Get("ntKp");
    TTree *ntGen = (TTree*)infMC->Get("ntGen");
    TH1D *hPtMC = new TH1D("hPtMC","",1,5,100);
    TH1D *hPtGen = new TH1D("hPtGen","",1,5,100);
    
	double diffXsec = 0;
    double BRchain=6.09604e-5;
    double Fraction=0.401;
	
	const int BINS = 8;
	double apt[BINS];
	double asigma[BINS];
	double aptl[BINS];
	double aerrorl[BINS];
	double aerrorh[BINS];
	double aerrorl2[BINS];
	double aerrorh2[BINS];
	double aerrorl3[BINS];
	double aerrorh3[BINS];
	double genB[BINS];
	double effB[BINS];
	double recoB[BINS];
	double bins[BINS+1] = {5,10,15,20,25,30,40,50,100};
	double raa[BINS] = {0.35, 0.305, 0.285, 0.27, 0.27, 0.275, 0.3, 0.375};
	double sysErr[BINS] = {0.18/0.15, 0.18/0.15, 0.15/0.15, 0.19/0.14, 0.19/0.14, 0.19/0.14, 0.19/0.14, 0.19/0.14};
	for(int i = 0; i < BINS; i++){
		Bplusdsigmadpt_1ptbins(false, diffXsec, bins[i], bins[i+1]);
		cout<<"diffXsec: "<<diffXsec<<endl;
		apt[i] = (bins[i]+bins[i+1])/2;
		asigma[i] = diffXsec;
		aptl[i] = (bins[i+1]-bins[i])/2;
		aerrorl[i] = 0;
		aerrorh[i] = 0;

//		genB[i] = 0.5 * 2 * 166e-6*10 * 208*208 * diffXsec * (bins[i+1]-bins[i]);
		genB[i] = raa[i] * 2 * 1.5e-3 * 208*208 * diffXsec * (bins[i+1]-bins[i]);
		aerrorl2[i] = 0;
		aerrorh2[i] = 0;
		cout<<"genB: "<<genB[i]<<endl;
		//Assuming RAA = 0.5, Luminosity = 10 times 2011 PbPb data
		
    	hPtMC = new TH1D(Form("hPtMC%d", i),"",1,bins[i],bins[i+1]);
		hPtGen = new TH1D(Form("hPtGen%d", i),"",1,bins[i],bins[i+1]);
    	ntMC->Project(Form("hPtMC%d", i),"pt",(TCut(selmc.Data())&&"gen==23333"));
	    ntGen->Project(Form("hPtGen%d", i),"pt",(TCut(selmcgen.Data())));
		effB[i] = hPtMC->GetBinContent(1)/hPtGen->GetBinContent(1);
		cout<<hPtMC->GetBinContent(1)<<endl;
		cout<<hPtGen->GetBinContent(1)<<endl;
		cout<<"eff: "<<effB[i]<<endl;
		//if(hPtGen->GetBinContent(1)<500) effB[i] = effB[i-1];//too few statistic 
		recoB[i] = genB[i]*effB[i]*BRchain*Fraction;
		aerrorl3[i] = recoB[i]*sqrt(effB[i]*(1-effB[i])/hPtGen->GetBinContent(1));//binomial error
		aerrorh3[i] = recoB[i]*sqrt(effB[i]*(1-effB[i])/hPtGen->GetBinContent(1));
		cout<<"aerrorl3: "<<aerrorl3[i]<<endl;
		cout<<"recoB: "<<recoB[i]<<endl;
	}

	TFile *outf = new TFile("output.root", "recreate");
	outf->cd();

    TCanvas* cr = new TCanvas("cr","cr",600,500);
    gStyle->SetOptTitle(1);
    cr->SetLogy();

    TH2F* hempty=new TH2F("hempty","",1,0,100,10.,10,10000000);
	hempty->SetTitle("average B meson dsigma/dpt");
    hempty->Draw();
    TGraphAsymmErrors* dXsec = new TGraphAsymmErrors(BINS, apt, asigma, aptl, aptl, aerrorl, aerrorh);
	dXsec->SetLineWidth(3);
	dXsec->SetLineColor(4);
	dXsec->Draw("p same");

    TH2F* hempty2=new TH2F("hempty2","",1,0,100,10.,1e2,1e11);
	hempty2->SetTitle("# of produced B meson");
	hempty2->GetXaxis()->SetTitle("B pt");
    hempty2->Draw();
    TGraphAsymmErrors* GenB = new TGraphAsymmErrors(BINS, apt, genB, aptl, aptl, aerrorl2, aerrorh2);
	GenB->SetLineWidth(3);
	GenB->SetLineColor(4);
	GenB->Draw("p same");
	cr->SaveAs("Plots/GenB.png");

    TH2F* hempty3=new TH2F("hempty3","",1,0,100,10.,1e-2,1e4);
	hempty3->SetTitle("# of reconstructed B+");
	hempty3->GetXaxis()->SetTitle("B pt");
    hempty3->Draw();
    TGraphAsymmErrors* RecoB = new TGraphAsymmErrors(BINS, apt, recoB, aptl, aptl, aerrorl3, aerrorh3);
	RecoB->SetLineWidth(3);
	RecoB->SetLineColor(4);
	RecoB->Draw("p same");
	cr->SaveAs("Plots/RecoB.png");

	RecoB->Write();
	//Make the RAA projection
	TH1D* RAApj = new TH1D("sys","",BINS,bins);
	TH1D* RAApj2 = new TH1D("stat","",BINS,bins);
	RAApj->SetMinimum(0.001);
	RAApj->SetMaximum(1.4);
	RAApj2->SetMinimum(0.001);
	RAApj2->SetMaximum(1.4);
    for(int i = 0; i < BINS; i++){
		float val = raa[i];
		float err = 1/sqrt(recoB[i]);
		//cout<<recoB[i]<<endl;
		//cout<<err<<endl;
		err = err*val;
		RAApj2->SetBinContent(i+1,val);
		RAApj2->SetBinError(i+1,err);
		err = err*sysErr[i];
		RAApj->SetBinContent(i+1,val);
		RAApj->SetBinError(i+1,err);
	}
    cr->SetLogy(0);
	RAApj->SetFillStyle(3001);
	RAApj->SetFillColor(kOrange+8);
	RAApj->Draw("E2");
	RAApj2->SetLineWidth(2);
	RAApj2->SetMarkerSize(3);
	RAApj2->SetLineColor(kRed+1);
	RAApj2->Draw("p e same");

	TLine *line;
    line = new TLine(1.0,1,100,1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw();

	TLatex* texlumi = new TLatex(0.19,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 1.5 nb^{-1} (5.02 TeV PbPb)");
	texlumi->SetNDC();
	//texlumi->SetTextAlign(31);
	texlumi->SetTextFont(42);
	texlumi->SetTextSize(0.038);
	texlumi->SetLineWidth(2);
	texlumi->Draw();
	TLatex* texcms = new TLatex(0.22,0.88,"CMS");
	texcms->SetNDC();
	texcms->SetTextAlign(13);
	texcms->SetTextFont(62);//61
	texcms->SetTextSize(0.06);
	texcms->SetLineWidth(2);
	texcms->Draw();
	TLatex* texpre = new TLatex(0.22,0.82,"2018 Projection");
	texpre->SetNDC();
	texpre->SetTextAlign(13);
	texpre->SetTextFont(52);
	texpre->SetTextSize(0.04);
	texpre->SetLineWidth(2);
	texpre->Draw();

	TLegend *legendSigma=new TLegend(0.55,0.7,0.90,0.8,"");//0.5100806,0.6268644,0.8084677,0.7805932
	legendSigma->SetBorderSize(0);
	legendSigma->SetLineColor(0);
	legendSigma->SetFillColor(0);
	legendSigma->SetFillStyle(1001);
	legendSigma->SetTextFont(42);
	legendSigma->SetTextSize(0.04);//0.05
	legendSigma->Draw();
	
	TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(RAApj, "R_{AA} B.","pf");
	ent_Dhighpt->SetTextFont(42);
	ent_Dhighpt->SetLineColor(1);
	ent_Dhighpt->SetMarkerColor(1);
	ent_Dhighpt->SetTextSize(0.04);

	cr->SaveAs("Plots/RAApj.png");
	RAApj->Write();
	RAApj2->Write();
	
	outf->Close();
}
