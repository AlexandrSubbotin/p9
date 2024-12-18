#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include <vector>
#include <iostream>



void func(){
    TFile* file=TFile::Open("output2.root");
    TTree* tree= (TTree*)file->Get("new_tree_name");
    tree->Print();

    Int_t nph;
    Float_t *eph = new Float_t[100];
    Float_t *phiph= new Float_t[100];
    Float_t * thetaph= new Float_t[100];

    tree->SetBranchAddress("eph",eph);
    tree->SetBranchAddress("thetaph",thetaph);
    tree->SetBranchAddress("phiph",phiph);
    tree->SetBranchAddress("nph",&nph);

    TH1F* Hphi=new TH1F("hMass","распределение инвариатной массы двух кандидатов",100,0.1,0.3);
    TH1F* htheta= new TH1F("hangle","распределение углов",50,0,3.2);
    Long64_t nentries = tree->GetEntries();
    for (int i=0;i<nentries;i++){
        int cand=0;
        double *mass_arr=new double[100];
        tree->GetEntry(i);
        for(int j=0;j<nph;j++){
            for(int k=j+1;k<nph;k++){
                TLorentzVector p1,p2;
                p1.SetPtEtaPhiE(eph[j]*sin(thetaph[j])*sin(phiph[j]),thetaph[j],phiph[j],eph[j]);
                p2.SetPtEtaPhiE(eph[k]*sin(thetaph[k])*sin(phiph[k]),thetaph[k],phiph[k],eph[k]);
                double mass= (p1+p2).M();
                double angle=p1.Angle(p2.Vect());
                if(mass>0.1&&mass<=0.2){
                    cand++;
                    Hphi->Fill(phiph[j]);
                    Hphi->Fill(phiph[k]);
                }
            }
        }
        if(cand==1){

        }
    }

    TCanvas *c1= new TCanvas("c1","",600,800);
    Hphi->Draw();
}