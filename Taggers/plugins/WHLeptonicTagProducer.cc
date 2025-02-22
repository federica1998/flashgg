#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "flashgg/DataFormats/interface/Jet.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/WHLeptonicTag.h"
#include "flashgg/DataFormats/interface/Electron.h"
#include "flashgg/DataFormats/interface/Muon.h"
#include "flashgg/DataFormats/interface/Met.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "flashgg/Taggers/interface/LeptonSelection.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "flashgg/DataFormats/interface/VHTagTruth.h"
#include "flashgg/DataFormats/interface/TagTruthBase.h"
#include "DataFormats/Common/interface/RefToPtr.h"

#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "TLorentzVector.h"
#include "TMath.h"
#include "TMVA/Reader.h"

using namespace std;
using namespace edm;


namespace flashgg {
    class WHLeptonicTagProducer : public EDProducer
    {

    public:
        WHLeptonicTagProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        int  chooseCategoryAC( float, float );
        int  computeStage1Kinematics( const WHLeptonicTag );

        EDGetTokenT<View<DiPhotonCandidate> > diPhotonToken_;
        EDGetTokenT<View<Electron> > electronToken_;
        EDGetTokenT<View<flashgg::Muon> > muonToken_;
        std::vector<edm::EDGetTokenT<View<flashgg::Jet> > > tokenJets_;
        std::vector<edm::InputTag> inputTagJets_;
        EDGetTokenT<View<flashgg::Met> > METToken_;
        EDGetTokenT<View<reco::Vertex> > vertexToken_;
        EDGetTokenT<double> rhoTag_;
        EDGetTokenT<View<DiPhotonMVAResult> > mvaResultToken_;
        EDGetTokenT<View<reco::GenParticle> > genParticleToken_;
        string systLabel_;

        typedef std::vector<edm::Handle<edm::View<flashgg::Jet> > > JetCollectionVector;

        //Thresholds
        double leadPhoOverMassThreshold_      ; 
        double subleadPhoOverMassThreshold_   ; 
        double PhoMVAThreshold_               ; 
        double MVAThreshold_                  ; 
        double electronPtThreshold_           ; 
        vector<double> electronEtaThresholds_ ; 
        double deltaRPhoElectronThreshold_    ; 
        double DeltaRTrkElec_                 ; 
        double deltaMassElectronZThreshold_   ; 
        double muonPtThreshold_               ; 
        double muonEtaThreshold_              ; 
        double muPFIsoSumRelThreshold_        ; 
        double deltaRMuonPhoThreshold_        ; 
        double jetsNumberThreshold_           ; 
        double jetPtThreshold_                ; 
        double jetEtaThreshold_               ; 
        double deltaRJetPhoThreshold_         ;
        double deltaRJetLepThreshold_         ;
        double METThreshold_                  ; 

        //WHMVA
        unique_ptr<TMVA::Reader>WHMva_;

        float _pho1_eta         ; 
        float _pho2_eta         ; 
        float _pho1_ptoM        ; 
        float _pho2_ptoM        ; 
        float _min_phoId        ; 
        float _max_phoId        ; 
        float _pho1_psv         ; 
        float _pho2_psv         ; 
        float _cosdphi_dipho    ; 
        float _lep_pt           ; 
        float _lep_eta          ; 
        float _dr_pho1_lep      ; 
        float _dr_pho2_lep      ; 
        float _met              ; 
        float _met_sumEt        ; 
        float _lnu_mt           ; 
        float _dphi_dipho_lnu   ; 
        float _pt_balance       ; 
        float _njet             ; 
        float _max_jet_pt       ; 
        float _max_jet_dCSV     ; 
        float _min_dphi_jet_lnu ;
        float _leptonType       ; 

        FileInPath WHMVAweightfile_ ;

        vector<double> boundaries_GT150;
        vector<double> boundaries_75_150;
        vector<double> boundaries_0_75;
        vector<double> acBoundaries; //AC BDT Boundaries...



        //Adding MVA variables for AC BDT for WHLeptonic
        //TMVA
        unique_ptr<TMVA::Reader> WHiggs0MToGG_MVA_;
        unique_ptr<TMVA::Reader> WHiggs0PHToGG_MVA_;
        unique_ptr<TMVA::Reader> WHiggs0L1ToGG_MVA_;
        //Feature Variables
        //Photon
        float _Anom_MVA_pho1_eta;
        float _Anom_MVA_pho1_phi;
        float _Anom_MVA_pho1_full5x5_r9;
        float _Anom_MVA_pho1_idmva;
        float _Anom_MVA_pho2_eta;
        float _Anom_MVA_pho2_phi;
        float _Anom_MVA_pho2_full5x5_r9;
        float _Anom_MVA_pho2_idmva;
        float _Anom_MVA_pho1_ptOverMgg;
        float _Anom_MVA_pho2_ptOverMgg;

        //Muon
        float _Anom_MVA_mu1_pt;
        float _Anom_MVA_mu1_phi;
        float _Anom_MVA_mu1_eta;
        float _Anom_MVA_mu1_energy;
        float _Anom_MVA_mu2_pt;
        float _Anom_MVA_mu2_phi;
        float _Anom_MVA_mu2_eta;
        float _Anom_MVA_mu2_energy;

        //Ele
        float _Anom_MVA_ele1_pt;
        float _Anom_MVA_ele1_phi;
        float _Anom_MVA_ele1_eta;
        float _Anom_MVA_ele1_energy;

        float _Anom_MVA_ele2_pt;
        float _Anom_MVA_ele2_phi;
        float _Anom_MVA_ele2_eta;
        float _Anom_MVA_ele2_energy;

        //Jet
        float _Anom_MVA_jet1_pt;
        float _Anom_MVA_jet1_phi;
        float _Anom_MVA_jet1_eta;
        float _Anom_MVA_jet1_energy;
        float _Anom_MVA_jet2_pt;
        float _Anom_MVA_jet2_phi;
        float _Anom_MVA_jet2_eta;
        float _Anom_MVA_jet2_energy;

        //Angular Vars
        float _Anom_MVA_cosPhiGG;
        float _Anom_MVA_cosPhiG1_Mu1;
        float _Anom_MVA_cosPhiG1_Ele1;
        float _Anom_MVA_cosPhiG2_Mu1;
        float _Anom_MVA_cosPhiG2_Ele1;


        float _Anom_MVA_dR_Pho1Ele1_wh;
        float _Anom_MVA_dR_Pho2Ele1_wh;
        float _Anom_MVA_dR_Pho1Mu1_wh;
        float _Anom_MVA_dR_Pho2Mu1_wh;

        float _Anom_MVA_dR_Pho1Jet1_wh;
        float _Anom_MVA_dR_Pho2Jet1_wh;
        float _Anom_MVA_dR_Pho1Jet2_wh;
        float _Anom_MVA_dR_Pho2Jet2_wh;

        float _Anom_MVA_dR_Mu1Jet1_wh;
        float _Anom_MVA_dR_Mu1Jet2_wh;
        float _Anom_MVA_dR_Ele1Jet1_wh;
        float _Anom_MVA_dR_Ele1Jet2_wh;

        FileInPath WHiggs0MToGG_weights_;
        FileInPath WHiggs0PHToGG_weights_;
        FileInPath WHiggs0L1ToGG_weights_;

    };

    WHLeptonicTagProducer::WHLeptonicTagProducer( const ParameterSet &iConfig ) :
        diPhotonToken_( consumes<View<flashgg::DiPhotonCandidate> >( iConfig.getParameter<InputTag> ( "DiPhotonTag" ) ) ),
        electronToken_( consumes<View<flashgg::Electron> >( iConfig.getParameter<InputTag> ( "ElectronTag" ) ) ),
        muonToken_( consumes<View<flashgg::Muon> >( iConfig.getParameter<InputTag>( "MuonTag" ) ) ),
        inputTagJets_( iConfig.getParameter<std::vector<edm::InputTag> >( "inputTagJets" ) ),
        METToken_( consumes<View<flashgg::Met> >( iConfig.getParameter<InputTag> ( "METTag" ) ) ),
        vertexToken_( consumes<View<reco::Vertex> >( iConfig.getParameter<InputTag> ( "VertexTag" ) ) ),
        rhoTag_( consumes<double>( iConfig.getParameter<InputTag>( "rhoTag" ) ) ),
        mvaResultToken_( consumes<View<flashgg::DiPhotonMVAResult> >( iConfig.getParameter<InputTag> ( "MVAResultTag" ) ) ),
        genParticleToken_( consumes<View<reco::GenParticle> >( iConfig.getParameter<InputTag> ( "GenParticleTag" ) ) ),
        systLabel_( iConfig.getParameter<string> ( "SystLabel" ) )
    {

        //Photon
        leadPhoOverMassThreshold_    = iConfig.getParameter<double>( "leadPhoOverMassThreshold");
        subleadPhoOverMassThreshold_ = iConfig.getParameter<double>( "subleadPhoOverMassThreshold");
        PhoMVAThreshold_             = iConfig.getParameter<double>( "PhoMVAThreshold");
        MVAThreshold_                = iConfig.getParameter<double>( "MVAThreshold");

        //Electron
        electronPtThreshold_         = iConfig.getParameter<double>( "electronPtThreshold");
        electronEtaThresholds_       = iConfig.getParameter<vector<double > >( "electronEtaThresholds");
        deltaRPhoElectronThreshold_  = iConfig.getParameter<double>( "deltaRPhoElectronThreshold");
        DeltaRTrkElec_               = iConfig.getParameter<double>( "DeltaRTrkElec");
        deltaMassElectronZThreshold_ = iConfig.getParameter<double>( "deltaMassElectronZThreshold");
        
        //Muon
        muonPtThreshold_             = iConfig.getParameter<double>( "muonPtThreshold");
        muonEtaThreshold_            = iConfig.getParameter<double>( "muonEtaThreshold");
        muPFIsoSumRelThreshold_      = iConfig.getParameter<double>( "muPFIsoSumRelThreshold");
        deltaRMuonPhoThreshold_      = iConfig.getParameter<double>( "deltaRMuonPhoThreshold");

        //Jet
        jetsNumberThreshold_         = iConfig.getParameter<double>( "jetsNumberThreshold");
        jetPtThreshold_              = iConfig.getParameter<double>( "jetPtThreshold");
        jetEtaThreshold_             = iConfig.getParameter<double>( "jetEtaThreshold");
        deltaRJetPhoThreshold_       = iConfig.getParameter<double>( "deltaRJetPhoThreshold");
        deltaRJetLepThreshold_       = iConfig.getParameter<double>( "deltaRJetLepThreshold");

        //Met
        METThreshold_                = iConfig.getParameter<double>( "METThreshold");

        for (unsigned i = 0 ; i < inputTagJets_.size() ; i++) {
            auto token = consumes<View<flashgg::Jet> >(inputTagJets_[i]);
            tokenJets_.push_back(token);
        }
        
        // $$$$$$$$$$$$$$$$$$$$ AC BDT Initialize $$$$$$$$$$$$$$$$$$$$

        //Load Weights files...
        WHiggs0MToGG_weights_          = iConfig.getParameter<edm::FileInPath>( "WHiggs0MToGG_weights" );     
        WHiggs0PHToGG_weights_         = iConfig.getParameter<edm::FileInPath>( "WHiggs0PHToGG_weights" );       
        WHiggs0L1ToGG_weights_         = iConfig.getParameter<edm::FileInPath>( "WHiggs0L1ToGG_weights" );       


        //Initialize Variables all to -999
        _Anom_MVA_pho1_eta = -999;
        _Anom_MVA_pho1_phi = -999;
        _Anom_MVA_pho1_full5x5_r9 = -999;
        _Anom_MVA_pho1_idmva = -999;
        _Anom_MVA_pho1_ptOverMgg = -999;

        _Anom_MVA_pho2_eta = -999;
        _Anom_MVA_pho2_phi = -999;
        _Anom_MVA_pho2_full5x5_r9 = -999;
        _Anom_MVA_pho2_idmva = -999;
        _Anom_MVA_pho2_ptOverMgg = -999;

        _Anom_MVA_mu1_pt = -999;
        _Anom_MVA_mu1_phi = -999;
        _Anom_MVA_mu1_eta = -999;
        _Anom_MVA_mu1_energy = -999;
        _Anom_MVA_mu2_pt = -999;
        _Anom_MVA_mu2_phi = -999;
        _Anom_MVA_mu2_eta = -999;
        _Anom_MVA_mu2_energy = -999;


        _Anom_MVA_ele1_pt = -999;
        _Anom_MVA_ele1_phi = -999;
        _Anom_MVA_ele1_eta = -999;
        _Anom_MVA_ele1_energy = -999;
        _Anom_MVA_ele2_pt = -999;
        _Anom_MVA_ele2_phi = -999;
        _Anom_MVA_ele2_eta = -999;
        _Anom_MVA_ele2_energy = -999;

        _Anom_MVA_jet1_pt = -999;
        _Anom_MVA_jet1_phi = -999;
        _Anom_MVA_jet1_eta = -999;
        _Anom_MVA_jet1_energy = -999;
        _Anom_MVA_jet2_pt = -999;
        _Anom_MVA_jet2_phi = -999;
        _Anom_MVA_jet2_eta = -999;
        _Anom_MVA_jet2_energy = -999;

        _Anom_MVA_cosPhiGG = -999;
        _Anom_MVA_cosPhiG1_Mu1 = -999;
        _Anom_MVA_cosPhiG1_Ele1 = -999;
        _Anom_MVA_cosPhiG2_Mu1 = -999;
        _Anom_MVA_cosPhiG2_Ele1 = -999;

        _Anom_MVA_dR_Pho1Ele1_wh = -999;
        _Anom_MVA_dR_Pho2Ele1_wh = -999;
        _Anom_MVA_dR_Pho1Mu1_wh = -999;
        _Anom_MVA_dR_Pho2Mu1_wh = -999;
        
        _Anom_MVA_dR_Pho1Jet1_wh = -999;
        _Anom_MVA_dR_Pho2Jet1_wh = -999;
        _Anom_MVA_dR_Pho1Jet2_wh = -999;
        _Anom_MVA_dR_Pho2Jet2_wh = -999;

        _Anom_MVA_dR_Mu1Jet1_wh = -999;
        _Anom_MVA_dR_Mu1Jet2_wh = -999;
        _Anom_MVA_dR_Ele1Jet1_wh = -999;
        _Anom_MVA_dR_Ele1Jet2_wh = -999;


        // Adding variables to TMVA 
        WHiggs0MToGG_MVA_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        WHiggs0MToGG_MVA_->AddVariable( "pho1_eta"             ,&_Anom_MVA_pho1_eta              );
        WHiggs0MToGG_MVA_->AddVariable( "pho1_phi"             ,&_Anom_MVA_pho1_phi              );
        WHiggs0MToGG_MVA_->AddVariable( "pho1_full5x5_r9"      ,&_Anom_MVA_pho1_full5x5_r9       );
        WHiggs0MToGG_MVA_->AddVariable( "pho1_idmva"           ,&_Anom_MVA_pho1_idmva            );
        WHiggs0MToGG_MVA_->AddVariable( "pho2_eta"             ,&_Anom_MVA_pho2_eta              );
        WHiggs0MToGG_MVA_->AddVariable( "pho2_phi"             ,&_Anom_MVA_pho2_phi              );
        WHiggs0MToGG_MVA_->AddVariable( "pho2_full5x5_r9"      ,&_Anom_MVA_pho2_full5x5_r9       );
        WHiggs0MToGG_MVA_->AddVariable( "pho2_idmva"           ,&_Anom_MVA_pho2_idmva            );
        WHiggs0MToGG_MVA_->AddVariable( "pho1_ptOverMgg"       ,&_Anom_MVA_pho1_ptOverMgg        );
        WHiggs0MToGG_MVA_->AddVariable( "pho2_ptOverMgg"       ,&_Anom_MVA_pho2_ptOverMgg        );

        WHiggs0MToGG_MVA_->AddVariable( "mu1_pt"               ,&_Anom_MVA_mu1_pt                );  
        WHiggs0MToGG_MVA_->AddVariable( "mu1_phi"              ,&_Anom_MVA_mu1_phi               );   
        WHiggs0MToGG_MVA_->AddVariable( "mu1_eta"              ,&_Anom_MVA_mu1_eta               );   
        WHiggs0MToGG_MVA_->AddVariable( "mu1_energy"           ,&_Anom_MVA_mu1_energy            );      
        // WHiggs0MToGG_MVA_->AddVariable( "mu2_pt"               ,&_Anom_MVA_mu2_pt                );  
        // WHiggs0MToGG_MVA_->AddVariable( "mu2_phi"              ,&_Anom_MVA_mu2_phi               );   
        // WHiggs0MToGG_MVA_->AddVariable( "mu2_eta"              ,&_Anom_MVA_mu2_eta               );   
        // WHiggs0MToGG_MVA_->AddVariable( "mu2_energy"           ,&_Anom_MVA_mu2_energy            );      
        WHiggs0MToGG_MVA_->AddVariable( "ele1_pt"              ,&_Anom_MVA_ele1_pt               );   
        WHiggs0MToGG_MVA_->AddVariable( "ele1_phi"             ,&_Anom_MVA_ele1_phi              );    
        WHiggs0MToGG_MVA_->AddVariable( "ele1_eta"             ,&_Anom_MVA_ele1_eta              );    
        WHiggs0MToGG_MVA_->AddVariable( "ele1_energy"          ,&_Anom_MVA_ele1_energy           );       
        // WHiggs0MToGG_MVA_->AddVariable( "ele2_pt"              ,&_Anom_MVA_ele2_pt               );   
        // WHiggs0MToGG_MVA_->AddVariable( "ele2_phi"             ,&_Anom_MVA_ele2_phi              );    
        // WHiggs0MToGG_MVA_->AddVariable( "ele2_eta"             ,&_Anom_MVA_ele2_eta              );    
        // WHiggs0MToGG_MVA_->AddVariable( "ele2_energy"          ,&_Anom_MVA_ele2_energy           );       
        WHiggs0MToGG_MVA_->AddVariable( "jet1_pt"              ,&_Anom_MVA_jet1_pt               );   
        WHiggs0MToGG_MVA_->AddVariable( "jet1_phi"             ,&_Anom_MVA_jet1_phi              );    
        WHiggs0MToGG_MVA_->AddVariable( "jet1_eta"             ,&_Anom_MVA_jet1_eta              );    
        WHiggs0MToGG_MVA_->AddVariable( "jet1_energy"          ,&_Anom_MVA_jet1_energy           );       
        WHiggs0MToGG_MVA_->AddVariable( "jet2_pt"              ,&_Anom_MVA_jet2_pt               );   
        WHiggs0MToGG_MVA_->AddVariable( "jet2_phi"             ,&_Anom_MVA_jet2_phi              );    
        // WHiggs0MToGG_MVA_->AddVariable( "jet2_eta"             ,&_Anom_MVA_jet2_eta              );    
        // WHiggs0MToGG_MVA_->AddVariable( "jet2_energy"          ,&_Anom_MVA_jet2_energy           );       
        WHiggs0MToGG_MVA_->AddVariable( "cosPhiGG"             ,&_Anom_MVA_cosPhiGG             );    
        WHiggs0MToGG_MVA_->AddVariable( "cosPhiG1_Mu1"         ,&_Anom_MVA_cosPhiG1_Mu1          );        
        WHiggs0MToGG_MVA_->AddVariable( "cosPhiG1_Ele1"        ,&_Anom_MVA_cosPhiG1_Ele1         );         
        WHiggs0MToGG_MVA_->AddVariable( "cosPhiG2_Mu1"         ,&_Anom_MVA_cosPhiG2_Mu1          );        
        WHiggs0MToGG_MVA_->AddVariable( "cosPhiG2_Ele1"        ,&_Anom_MVA_cosPhiG2_Ele1         );  
        WHiggs0MToGG_MVA_->AddVariable( "dR_Pho1Ele1_wh"       ,&_Anom_MVA_dR_Pho1Ele1_wh        );          
        WHiggs0MToGG_MVA_->AddVariable( "dR_Pho2Ele1_wh"       ,&_Anom_MVA_dR_Pho2Ele1_wh        );          
        WHiggs0MToGG_MVA_->AddVariable( "dR_Pho1Mu1_wh"        ,&_Anom_MVA_dR_Pho1Mu1_wh         );         
        WHiggs0MToGG_MVA_->AddVariable( "dR_Pho2Mu1_wh"        ,&_Anom_MVA_dR_Pho2Mu1_wh         );  
        WHiggs0MToGG_MVA_->AddVariable( "dR_Pho1Jet1_wh"       ,&_Anom_MVA_dR_Pho1Jet1_wh        );          
        WHiggs0MToGG_MVA_->AddVariable( "dR_Pho2Jet1_wh"       ,&_Anom_MVA_dR_Pho2Jet1_wh        );          
        WHiggs0MToGG_MVA_->AddVariable( "dR_Pho1Jet2_wh"       ,&_Anom_MVA_dR_Pho1Jet2_wh        );          
        // WHiggs0MToGG_MVA_->AddVariable( "dR_Pho2Jet2_wh"       ,&_Anom_MVA_dR_Pho2Jet2_wh        );  
        WHiggs0MToGG_MVA_->AddVariable( "dR_Mu1Jet1_wh"        ,&_Anom_MVA_dR_Mu1Jet1_wh         );         
        WHiggs0MToGG_MVA_->AddVariable( "dR_Mu1Jet2_wh"        ,&_Anom_MVA_dR_Mu1Jet2_wh         );         
        WHiggs0MToGG_MVA_->AddVariable( "dR_Ele1Jet1_wh"       ,&_Anom_MVA_dR_Ele1Jet1_wh        );          
        // WHiggs0MToGG_MVA_->AddVariable( "dR_Ele1Jet2_wh"       ,&_Anom_MVA_dR_Ele1Jet2_wh        );          
        WHiggs0MToGG_MVA_->BookMVA( "BDT", WHiggs0MToGG_weights_.fullPath() );


        WHiggs0PHToGG_MVA_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        WHiggs0PHToGG_MVA_->AddVariable( "pho1_eta"             ,&_Anom_MVA_pho1_eta              );
        WHiggs0PHToGG_MVA_->AddVariable( "pho1_phi"             ,&_Anom_MVA_pho1_phi              );
        WHiggs0PHToGG_MVA_->AddVariable( "pho1_full5x5_r9"      ,&_Anom_MVA_pho1_full5x5_r9       );
        WHiggs0PHToGG_MVA_->AddVariable( "pho1_idmva"           ,&_Anom_MVA_pho1_idmva            );
        WHiggs0PHToGG_MVA_->AddVariable( "pho2_eta"             ,&_Anom_MVA_pho2_eta              );
        WHiggs0PHToGG_MVA_->AddVariable( "pho2_phi"             ,&_Anom_MVA_pho2_phi              );
        WHiggs0PHToGG_MVA_->AddVariable( "pho2_full5x5_r9"      ,&_Anom_MVA_pho2_full5x5_r9       );
        WHiggs0PHToGG_MVA_->AddVariable( "pho2_idmva"           ,&_Anom_MVA_pho2_idmva            );
        WHiggs0PHToGG_MVA_->AddVariable( "pho1_ptOverMgg"       ,&_Anom_MVA_pho1_ptOverMgg        );
        WHiggs0PHToGG_MVA_->AddVariable( "pho2_ptOverMgg"       ,&_Anom_MVA_pho2_ptOverMgg        );

        WHiggs0PHToGG_MVA_->AddVariable( "mu1_pt"               ,&_Anom_MVA_mu1_pt                );  
        WHiggs0PHToGG_MVA_->AddVariable( "mu1_phi"              ,&_Anom_MVA_mu1_phi               );   
        WHiggs0PHToGG_MVA_->AddVariable( "mu1_eta"              ,&_Anom_MVA_mu1_eta               );   
        WHiggs0PHToGG_MVA_->AddVariable( "mu1_energy"           ,&_Anom_MVA_mu1_energy            );      
        // WHiggs0PHToGG_MVA_->AddVariable( "mu2_pt"               ,&_Anom_MVA_mu2_pt                );  
        // WHiggs0PHToGG_MVA_->AddVariable( "mu2_phi"              ,&_Anom_MVA_mu2_phi               );   
        // WHiggs0PHToGG_MVA_->AddVariable( "mu2_eta"              ,&_Anom_MVA_mu2_eta               );   
        // WHiggs0PHToGG_MVA_->AddVariable( "mu2_energy"           ,&_Anom_MVA_mu2_energy            );      
        WHiggs0PHToGG_MVA_->AddVariable( "ele1_pt"              ,&_Anom_MVA_ele1_pt               );   
        WHiggs0PHToGG_MVA_->AddVariable( "ele1_phi"             ,&_Anom_MVA_ele1_phi              );    
        WHiggs0PHToGG_MVA_->AddVariable( "ele1_eta"             ,&_Anom_MVA_ele1_eta              );    
        WHiggs0PHToGG_MVA_->AddVariable( "ele1_energy"          ,&_Anom_MVA_ele1_energy           );       
        // WHiggs0PHToGG_MVA_->AddVariable( "ele2_pt"              ,&_Anom_MVA_ele2_pt               );   
        // WHiggs0PHToGG_MVA_->AddVariable( "ele2_phi"             ,&_Anom_MVA_ele2_phi              );    
        // WHiggs0PHToGG_MVA_->AddVariable( "ele2_eta"             ,&_Anom_MVA_ele2_eta              );    
        // WHiggs0PHToGG_MVA_->AddVariable( "ele2_energy"          ,&_Anom_MVA_ele2_energy           );       
        WHiggs0PHToGG_MVA_->AddVariable( "jet1_pt"              ,&_Anom_MVA_jet1_pt               );   
        WHiggs0PHToGG_MVA_->AddVariable( "jet1_phi"             ,&_Anom_MVA_jet1_phi              );    
        WHiggs0PHToGG_MVA_->AddVariable( "jet1_eta"             ,&_Anom_MVA_jet1_eta              );    
        WHiggs0PHToGG_MVA_->AddVariable( "jet1_energy"          ,&_Anom_MVA_jet1_energy           );       
        WHiggs0PHToGG_MVA_->AddVariable( "jet2_pt"              ,&_Anom_MVA_jet2_pt               );   
        WHiggs0PHToGG_MVA_->AddVariable( "jet2_phi"             ,&_Anom_MVA_jet2_phi              );    
        // WHiggs0PHToGG_MVA_->AddVariable( "jet2_eta"             ,&_Anom_MVA_jet2_eta              );    
        // WHiggs0PHToGG_MVA_->AddVariable( "jet2_energy"          ,&_Anom_MVA_jet2_energy           );       
        WHiggs0PHToGG_MVA_->AddVariable( "cosPhiGG"             ,&_Anom_MVA_cosPhiGG             );    
        WHiggs0PHToGG_MVA_->AddVariable( "cosPhiG1_Mu1"         ,&_Anom_MVA_cosPhiG1_Mu1          );        
        WHiggs0PHToGG_MVA_->AddVariable( "cosPhiG1_Ele1"        ,&_Anom_MVA_cosPhiG1_Ele1         );         
        WHiggs0PHToGG_MVA_->AddVariable( "cosPhiG2_Mu1"         ,&_Anom_MVA_cosPhiG2_Mu1          );        
        WHiggs0PHToGG_MVA_->AddVariable( "cosPhiG2_Ele1"        ,&_Anom_MVA_cosPhiG2_Ele1         );  
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho1Ele1_wh"       ,&_Anom_MVA_dR_Pho1Ele1_wh        );          
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho2Ele1_wh"       ,&_Anom_MVA_dR_Pho2Ele1_wh        );          
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho1Mu1_wh"        ,&_Anom_MVA_dR_Pho1Mu1_wh         );         
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho2Mu1_wh"        ,&_Anom_MVA_dR_Pho2Mu1_wh         );  
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho1Jet1_wh"       ,&_Anom_MVA_dR_Pho1Jet1_wh        );          
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho2Jet1_wh"       ,&_Anom_MVA_dR_Pho2Jet1_wh        );          
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho1Jet2_wh"       ,&_Anom_MVA_dR_Pho1Jet2_wh        );          
        // WHiggs0PHToGG_MVA_->AddVariable( "dR_Pho2Jet2_wh"       ,&_Anom_MVA_dR_Pho2Jet2_wh        );  
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Mu1Jet1_wh"        ,&_Anom_MVA_dR_Mu1Jet1_wh         );         
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Mu1Jet2_wh"        ,&_Anom_MVA_dR_Mu1Jet2_wh         );         
        WHiggs0PHToGG_MVA_->AddVariable( "dR_Ele1Jet1_wh"       ,&_Anom_MVA_dR_Ele1Jet1_wh        );          
        // WHiggs0PHToGG_MVA_->AddVariable( "dR_Ele1Jet2_wh"       ,&_Anom_MVA_dR_Ele1Jet2_wh        );          
        WHiggs0PHToGG_MVA_->BookMVA( "BDT", WHiggs0PHToGG_weights_.fullPath() );


        WHiggs0L1ToGG_MVA_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho1_eta"             ,&_Anom_MVA_pho1_eta              );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho1_phi"             ,&_Anom_MVA_pho1_phi              );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho1_full5x5_r9"      ,&_Anom_MVA_pho1_full5x5_r9       );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho1_idmva"           ,&_Anom_MVA_pho1_idmva            );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho2_eta"             ,&_Anom_MVA_pho2_eta              );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho2_phi"             ,&_Anom_MVA_pho2_phi              );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho2_full5x5_r9"      ,&_Anom_MVA_pho2_full5x5_r9       );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho2_idmva"           ,&_Anom_MVA_pho2_idmva            );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho1_ptOverMgg"       ,&_Anom_MVA_pho1_ptOverMgg        );
        WHiggs0L1ToGG_MVA_->AddVariable( "pho2_ptOverMgg"       ,&_Anom_MVA_pho2_ptOverMgg        );

        WHiggs0L1ToGG_MVA_->AddVariable( "mu1_pt"               ,&_Anom_MVA_mu1_pt                );  
        WHiggs0L1ToGG_MVA_->AddVariable( "mu1_phi"              ,&_Anom_MVA_mu1_phi               );   
        WHiggs0L1ToGG_MVA_->AddVariable( "mu1_eta"              ,&_Anom_MVA_mu1_eta               );   
        WHiggs0L1ToGG_MVA_->AddVariable( "mu1_energy"           ,&_Anom_MVA_mu1_energy            );      
        // WHiggs0L1ToGG_MVA_->AddVariable( "mu2_pt"               ,&_Anom_MVA_mu2_pt                );  
        // WHiggs0L1ToGG_MVA_->AddVariable( "mu2_phi"              ,&_Anom_MVA_mu2_phi               );   
        // WHiggs0L1ToGG_MVA_->AddVariable( "mu2_eta"              ,&_Anom_MVA_mu2_eta               );   
        // WHiggs0L1ToGG_MVA_->AddVariable( "mu2_energy"           ,&_Anom_MVA_mu2_energy            );      
        WHiggs0L1ToGG_MVA_->AddVariable( "ele1_pt"              ,&_Anom_MVA_ele1_pt               );   
        WHiggs0L1ToGG_MVA_->AddVariable( "ele1_phi"             ,&_Anom_MVA_ele1_phi              );    
        WHiggs0L1ToGG_MVA_->AddVariable( "ele1_eta"             ,&_Anom_MVA_ele1_eta              );    
        WHiggs0L1ToGG_MVA_->AddVariable( "ele1_energy"          ,&_Anom_MVA_ele1_energy           );       
        // WHiggs0L1ToGG_MVA_->AddVariable( "ele2_pt"              ,&_Anom_MVA_ele2_pt               );   
        // WHiggs0L1ToGG_MVA_->AddVariable( "ele2_phi"             ,&_Anom_MVA_ele2_phi              );    
        // WHiggs0L1ToGG_MVA_->AddVariable( "ele2_eta"             ,&_Anom_MVA_ele2_eta              );    
        // WHiggs0L1ToGG_MVA_->AddVariable( "ele2_energy"          ,&_Anom_MVA_ele2_energy           );       
        WHiggs0L1ToGG_MVA_->AddVariable( "jet1_pt"              ,&_Anom_MVA_jet1_pt               );   
        WHiggs0L1ToGG_MVA_->AddVariable( "jet1_phi"             ,&_Anom_MVA_jet1_phi              );    
        WHiggs0L1ToGG_MVA_->AddVariable( "jet1_eta"             ,&_Anom_MVA_jet1_eta              );    
        WHiggs0L1ToGG_MVA_->AddVariable( "jet1_energy"          ,&_Anom_MVA_jet1_energy           );       
        WHiggs0L1ToGG_MVA_->AddVariable( "jet2_pt"              ,&_Anom_MVA_jet2_pt               );   
        WHiggs0L1ToGG_MVA_->AddVariable( "jet2_phi"             ,&_Anom_MVA_jet2_phi              );    
        // WHiggs0L1ToGG_MVA_->AddVariable( "jet2_eta"             ,&_Anom_MVA_jet2_eta              );    
        // WHiggs0L1ToGG_MVA_->AddVariable( "jet2_energy"          ,&_Anom_MVA_jet2_energy           );       
        WHiggs0L1ToGG_MVA_->AddVariable( "cosPhiGG"             ,&_Anom_MVA_cosPhiGG             );    
        WHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG1_Mu1"         ,&_Anom_MVA_cosPhiG1_Mu1          );        
        WHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG1_Ele1"        ,&_Anom_MVA_cosPhiG1_Ele1         );         
        WHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG2_Mu1"         ,&_Anom_MVA_cosPhiG2_Mu1          );        
        WHiggs0L1ToGG_MVA_->AddVariable( "cosPhiG2_Ele1"        ,&_Anom_MVA_cosPhiG2_Ele1         );  
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho1Ele1_wh"       ,&_Anom_MVA_dR_Pho1Ele1_wh        );          
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho2Ele1_wh"       ,&_Anom_MVA_dR_Pho2Ele1_wh        );          
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho1Mu1_wh"        ,&_Anom_MVA_dR_Pho1Mu1_wh         );         
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho2Mu1_wh"        ,&_Anom_MVA_dR_Pho2Mu1_wh         );  
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho1Jet1_wh"       ,&_Anom_MVA_dR_Pho1Jet1_wh        );          
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho2Jet1_wh"       ,&_Anom_MVA_dR_Pho2Jet1_wh        );          
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho1Jet2_wh"       ,&_Anom_MVA_dR_Pho1Jet2_wh        );          
        // WHiggs0L1ToGG_MVA_->AddVariable( "dR_Pho2Jet2_wh"       ,&_Anom_MVA_dR_Pho2Jet2_wh        );  
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Mu1Jet1_wh"        ,&_Anom_MVA_dR_Mu1Jet1_wh         );         
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Mu1Jet2_wh"        ,&_Anom_MVA_dR_Mu1Jet2_wh         );         
        WHiggs0L1ToGG_MVA_->AddVariable( "dR_Ele1Jet1_wh"       ,&_Anom_MVA_dR_Ele1Jet1_wh        );          
        // WHiggs0L1ToGG_MVA_->AddVariable( "dR_Ele1Jet2_wh"       ,&_Anom_MVA_dR_Ele1Jet2_wh        );          
        WHiggs0L1ToGG_MVA_->BookMVA( "BDT", WHiggs0L1ToGG_weights_.fullPath() );

        // $$$$$$$$$$$$$$$$$$$$      AC BDT END       $$$$$$$$$$$$$$$$$$$$

        //WHMVA
        WHMVAweightfile_ = iConfig.getParameter<edm::FileInPath>( "WHMVAweightfile" );
 
        _pho1_eta         = -999.; 
        _pho2_eta         = -999.; 
        _pho1_ptoM        = -999.; 
        _pho2_ptoM        = -999.; 
        _min_phoId        = -999.; 
        _max_phoId        = -999.; 
        _pho1_psv         = -999.; 
        _pho2_psv         = -999.; 
        _cosdphi_dipho    = -999.; 
        _lep_pt           = -999.; 
        _lep_eta          = -999.; 
        _dr_pho1_lep      = -999.; 
        _dr_pho2_lep      = -999.; 
        _met              = -999.; 
        _met_sumEt        = -999.; 
        _lnu_mt           = -999.; 
        _dphi_dipho_lnu   = -999.; 
        _pt_balance       = -999.; 
        _njet             = -999.; 
        _max_jet_pt       = -999.; 
        _max_jet_dCSV     = -999.; 
        _min_dphi_jet_lnu = -999.; 
        _leptonType       = -999.; 

        WHMva_.reset( new TMVA::Reader( "!Color:!Silent" ) );
        WHMva_->AddVariable( "pho1_eta"             ,& _pho1_eta          ); 
        WHMva_->AddVariable( "pho2_eta"             ,& _pho2_eta          ); 
        WHMva_->AddVariable( "pho1_ptoM"            ,& _pho1_ptoM         ); 
        WHMva_->AddVariable( "pho2_ptoM"            ,& _pho2_ptoM         ); 
        WHMva_->AddVariable( "min_phoId"            ,& _min_phoId         ); 
        WHMva_->AddVariable( "max_phoId"            ,& _max_phoId         ); 
        WHMva_->AddVariable( "pho1_psv"             ,& _pho1_psv          ); 
        WHMva_->AddVariable( "pho2_psv"             ,& _pho2_psv          ); 
        WHMva_->AddVariable( "cosdphi_dipho"        ,& _cosdphi_dipho     ); 
        WHMva_->AddVariable( "lep_pt"               ,& _lep_pt            ); 
        WHMva_->AddVariable( "lep_eta"              ,& _lep_eta           ); 
        WHMva_->AddVariable( "dr_pho1_lep"          ,& _dr_pho1_lep       ); 
        WHMva_->AddVariable( "dr_pho2_lep"          ,& _dr_pho2_lep       ); 
        WHMva_->AddVariable( "met"                  ,& _met               ); 
        WHMva_->AddVariable( "met_sumEt"            ,& _met_sumEt         ); 
        WHMva_->AddVariable( "lnu_mt"               ,& _lnu_mt            ); 
        WHMva_->AddVariable( "dphi_dipho_lnu"       ,& _dphi_dipho_lnu    ); 
        WHMva_->AddVariable( "pt_balance"           ,& _pt_balance        ); 
        WHMva_->AddVariable( "njet"                 ,& _njet              ); 
        WHMva_->AddVariable( "max_jet_pt"           ,& _max_jet_pt        ); 
        WHMva_->AddVariable( "max_jet_dCSV"         ,& _max_jet_dCSV      ); 
        WHMva_->AddVariable( "min_dphi_jet_lnu"     ,& _min_dphi_jet_lnu  ); 
        WHMva_->AddSpectator( "leptonType"        ,&_leptonType    ); 
        WHMva_->BookMVA( "BDT", WHMVAweightfile_.fullPath() );

        boundaries_GT150  = iConfig.getParameter<vector<double > >( "Boundaries_GT150" );
        boundaries_75_150 = iConfig.getParameter<vector<double > >( "Boundaries_75_150" );
        boundaries_0_75   = iConfig.getParameter<vector<double > >( "Boundaries_0_75" );
        assert( is_sorted( boundaries_GT150.begin(), boundaries_GT150.end() ) ); // we are counting on ascending order - update this to give an error message or exception
        assert( is_sorted( boundaries_75_150.begin(), boundaries_75_150.end() ) ); // we are counting on ascending order - update this to give an error message or exception
        assert( is_sorted( boundaries_0_75.begin(), boundaries_0_75.end() ) ); // we are counting on ascending order - update this to give an error message or exception


        produces<vector<WHLeptonicTag> >();
        //produces<vector<VHTagTruth> >();
        acBoundaries  = iConfig.getParameter< vector<double> >( "acBoundaries" );

    }

    int WHLeptonicTagProducer::chooseCategoryAC( float stxs_mva, float ac_mva )
    {
        //tag_number {each tag should have 4 boundaries}
        for (uint tag_num=0;tag_num < acBoundaries.size(); tag_num+=4){
            if ((stxs_mva <= acBoundaries[tag_num + 0]) && (stxs_mva > acBoundaries[tag_num + 1]) && (ac_mva <= acBoundaries[tag_num + 2]) && (ac_mva > acBoundaries[tag_num + 3])){
                // std::cout<<"WH "<<tag_num/4<<" "<<stxs_mva<<" "<<ac_mva<<std::endl;
                return tag_num/4;
            }
        }

        // std::cout<<"WH "<<"-1"<<" "<<stxs_mva<<" "<<ac_mva<<std::endl;
        return -1; // Does not pass, object will not be produced
    }

    void WHLeptonicTagProducer::produce( Event &evt, const EventSetup & )
    {
        Handle<View<flashgg::DiPhotonCandidate> > diPhotons;
        evt.getByToken( diPhotonToken_, diPhotons );

        Handle<View<flashgg::Electron> > theElectrons;
        evt.getByToken( electronToken_, theElectrons );

        Handle<View<flashgg::Muon> > theMuons;
        evt.getByToken( muonToken_, theMuons );

        JetCollectionVector Jets( inputTagJets_.size() );
        for( size_t j = 0; j < inputTagJets_.size(); ++j ) {
            evt.getByToken( tokenJets_[j], Jets[j] );
        }

        Handle<View<flashgg::Met> > METs;
        evt.getByToken( METToken_, METs );

        Handle<View<reco::Vertex> > vertices;
        evt.getByToken( vertexToken_, vertices );

        edm::Handle<double>  rho;
        evt.getByToken(rhoTag_,rho);
        // double rho_    = *rho;

        Handle<View<flashgg::DiPhotonMVAResult> > mvaResults;
        evt.getByToken( mvaResultToken_, mvaResults );
        assert( diPhotons->size() == mvaResults->size() );

        Handle<View<reco::GenParticle> > genParticles;
        evt.getByToken( genParticleToken_, genParticles );


        std::unique_ptr<vector<WHLeptonicTag> > whleptonictags( new vector<WHLeptonicTag> );
        //std::unique_ptr<vector<VHTagTruth> > truths( new vector<VHTagTruth> );
        //edm::RefProd<vector<VHTagTruth> > rTagTruth = evt.getRefBeforePut<vector<VHTagTruth> >();

        bool associatedZ   = 0;
        bool associatedW   = 0;
        bool VhasDaughters = 0;
        bool VhasNeutrinos = 0;
        bool VhasLeptons   = 0;
        bool VhasHadrons   = 0;
        bool VhasMissingLeptons = 0;
        float Vpt = 0;

        if ( !evt.isRealData() ) {

            for( unsigned int genLoop = 0 ; genLoop < genParticles->size(); genLoop++ ) {
                int pdgid = genParticles->ptrAt( genLoop )->pdgId();
                int dpdgid[2] = {0, 0};

                //Search for Z boson
                if(pdgid ==23) {
                    associatedZ=1;
                    if( genParticles->ptrAt( genLoop )->numberOfDaughters()==2) {
                        VhasDaughters = 1;
                        dpdgid[0] = genParticles->ptrAt(genLoop)->daughter(0)->pdgId();
                        //dpdgid[1]=genParticles->ptrAt(genLoop)->daughter(1)->pdgId();
                        Vpt = genParticles->ptrAt( genLoop )->pt();
                        if(fabs(dpdgid[0]) == 12 || fabs(dpdgid[0]) == 14 || fabs(dpdgid[0]) == 16) VhasNeutrinos = 1;//look for neutrino decay of Z
                        if(fabs(dpdgid[0]) == 11 || fabs(dpdgid[0]) == 13 || fabs(dpdgid[0]) == 15) VhasLeptons = 1;//look for lepton decay of Z  
                        if(fabs(dpdgid[0]) > 0 && fabs(dpdgid[0]) < 9) VhasHadrons = 1;//look for quark decay of Z   
                    }
                }
                //Search for W boson
                if(fabs(pdgid)==24) {
                    associatedW=1;
                    if( genParticles->ptrAt( genLoop )->numberOfDaughters()==2) {
                        VhasDaughters = 1;
                        Vpt = genParticles->ptrAt( genLoop )->pt();
                        dpdgid[0] = genParticles->ptrAt(genLoop)->daughter(0)->pdgId();
                        //dpdgid[1]=genParticles->ptrAt(genLoop)->daughter(1)->pdgId();
                        if(fabs(dpdgid[0]) == 12 || fabs(dpdgid[0]) == 14 || fabs(dpdgid[0]) == 16) { VhasNeutrinos = 1; VhasLeptons = 1; }//look for neutrino decay of W
                        if(fabs(dpdgid[0]) == 11 || fabs(dpdgid[0]) == 13 || fabs(dpdgid[0]) == 15) { VhasNeutrinos = 1; VhasLeptons = 1; }//look for lepton decay of W
                        if(fabs(dpdgid[0]) > 0 && fabs(dpdgid[0]) < 9) VhasHadrons = 1;//look for quark decay of W 
                    }
                }

            }
        }

        // unsigned int idx = 0;

        for( unsigned int diphoIndex = 0; diphoIndex < diPhotons->size(); diphoIndex++ ) {

            edm::Ptr<flashgg::DiPhotonCandidate> dipho = diPhotons->ptrAt( diphoIndex );
            edm::Ptr<flashgg::DiPhotonMVAResult> mvares = mvaResults->ptrAt( diphoIndex );

            WHLeptonicTag whleptonictags_obj( dipho, mvares );
            whleptonictags_obj.includeWeights( *dipho );

            double idmva1 = dipho->leadingPhoton()->phoIdMvaDWrtVtx( dipho->vtx() );
            double idmva2 = dipho->subLeadingPhoton()->phoIdMvaDWrtVtx( dipho->vtx() );
            
            if( dipho->leadingPhoton()->pt()    < dipho->mass() * leadPhoOverMassThreshold_ ) continue;
            if( dipho->subLeadingPhoton()->pt() < dipho->mass() * subleadPhoOverMassThreshold_ ) continue;
            if( idmva1 <= PhoMVAThreshold_ || idmva2 <= PhoMVAThreshold_ ) continue;
            if( mvares->result < MVAThreshold_ ) continue;

            // Lepton
            std::vector<edm::Ptr<flashgg::Muon> > goodMuons =
                LeptonSelection2018::selectMuons(theMuons->ptrs(), dipho, vertices->ptrs(), 
                        muonPtThreshold_, muonEtaThreshold_, muPFIsoSumRelThreshold_, deltaRMuonPhoThreshold_);
            std::vector<edm::Ptr<Electron> >goodElectrons =
                LeptonSelection2018::selectElectrons(theElectrons->ptrs(), dipho, 
                        electronPtThreshold_, electronEtaThresholds_, deltaRPhoElectronThreshold_, deltaMassElectronZThreshold_, DeltaRTrkElec_);

            bool hasGoodElec  = ( goodElectrons.size() == 1 );
            bool hasGoodMuons = ( goodMuons.size() == 1 );

            if( !hasGoodElec && !hasGoodMuons ) { continue; }

            //WHMVA
            double ele_pt = -999.;
            double mu_pt  = -999.;

            if (hasGoodElec)  ele_pt = goodElectrons[0]->pt();
            if (hasGoodMuons) mu_pt  = goodMuons[0]->pt();

            TLorentzVector diphoP4(dipho->px(), dipho->py(), dipho->pz(), dipho->energy());
            TLorentzVector lepP4;

            if (ele_pt > mu_pt) {
                lepP4.SetPtEtaPhiE( goodElectrons[0]->pt(), goodElectrons[0]->eta(), goodElectrons[0]->phi(), goodElectrons[0]->energy() );
                _leptonType    = 11.;
                whleptonictags_obj.includeWeights( *goodElectrons.at(0) );
            } else {
                lepP4.SetPtEtaPhiE( goodMuons[0]->pt(), goodMuons[0]->eta(), goodMuons[0]->phi(), goodMuons[0]->energy() );
                _leptonType    = 13.;
                whleptonictags_obj.includeWeights( *goodMuons.at(0) );
            }

            //MET
            Ptr<flashgg::Met> theMET = METs->ptrAt( 0 );
            if ( theMET->getCorPt() < METThreshold_ ) continue;

            TVector2 lepP2 = lepP4.Vect().XYvector();
            TVector2 metP2; metP2.SetMagPhi(theMET->getCorPt(), theMET->getCorPhi());
            TVector2 V_P2 = lepP2 + metP2;
            TVector2 H_P2 = diphoP4.Vect().XYvector();

            //Jets
            float max_jet_pt          = -1.;
            float max_jet_dCSV        = -2.;
            float minDeltaPhiJetLNu   = 4.0;

            std::vector<edm::Ptr<Jet> > tagJets;
            unsigned int jetCollectionIndex = diPhotons->ptrAt( diphoIndex )->jetCollectionIndex();
            for( unsigned int candIndex_outer = 0; candIndex_outer < Jets[jetCollectionIndex]->size() ; candIndex_outer++ ) {

                edm::Ptr<flashgg::Jet> thejet = Jets[jetCollectionIndex]->ptrAt( candIndex_outer );
                if( !thejet->passesJetID ( flashgg::Tight2017 ) ) continue;
                if( fabs( thejet->eta() ) > jetEtaThreshold_ ) continue;
                if( thejet->pt() < jetPtThreshold_ ) continue;
                float dRPhoLeadJet = deltaR( thejet->eta(), thejet->phi(), 
                                            dipho->leadingPhoton()->superCluster()->eta(), dipho->leadingPhoton()->superCluster()->phi() ) ;
                float dRPhoSubLeadJet = deltaR( thejet->eta(), thejet->phi(), 
                                            dipho->subLeadingPhoton()->superCluster()->eta(), dipho->subLeadingPhoton()->superCluster()->phi() );

                if( dRPhoLeadJet < deltaRJetPhoThreshold_ || dRPhoSubLeadJet < deltaRJetPhoThreshold_ ) continue;

                float dRJetLep = deltaR( thejet->eta(), thejet->phi(), lepP4.Eta(), lepP4.Phi() ) ;
                if( dRJetLep < deltaRJetLepThreshold_ ) continue;

                float pt             = thejet->pt(); 
                float dcsv_val       = thejet->bDiscriminator("pfDeepCSVJetTags:probb") + thejet->bDiscriminator("pfDeepCSVJetTags:probbb");

                TVector2 jet_P2(thejet->px(), thejet->py());
                float deltaPhiJetLNu = fabs( jet_P2.DeltaPhi(V_P2) );

                if (pt > max_jet_pt)                     max_jet_pt   = pt;
                if (dcsv_val > max_jet_dCSV)             max_jet_dCSV = dcsv_val;
                if (deltaPhiJetLNu < minDeltaPhiJetLNu)  minDeltaPhiJetLNu = deltaPhiJetLNu;

                tagJets.push_back( thejet );
 
            }

            if (tagJets.size() > jetsNumberThreshold_) continue;

            //WHLeptonicTag MVA
            _pho1_eta         = dipho->leadingPhoton()->eta();
            _pho2_eta         = dipho->subLeadingPhoton()->eta();
            _pho1_ptoM        = dipho->leadingPhoton()->pt() / dipho->mass();
            _pho2_ptoM        = dipho->subLeadingPhoton()->pt() / dipho->mass();
            _min_phoId        = TMath::Min(idmva1, idmva2);
            _max_phoId        = TMath::Max(idmva1, idmva2);
            _pho1_psv         = dipho->leadingPhoton()->hasPixelSeed() > 0.5 ? 0. : 1.;
            _pho2_psv         = dipho->subLeadingPhoton()->hasPixelSeed() > 0.5 ? 0. : 1.;
            _cosdphi_dipho    = TMath::Cos( fabs(deltaPhi(dipho->leadingPhoton()->phi(), dipho->subLeadingPhoton()->phi())) );
            _lep_pt           = lepP4.Pt();
            _lep_eta          = lepP4.Eta();
            _dr_pho1_lep      = deltaR( lepP4.Eta(), lepP4.Phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi() ) ;
            _dr_pho2_lep      = deltaR( lepP4.Eta(), lepP4.Phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi() ) ;
            _met              = theMET->getCorPt();
            _met_sumEt        = theMET->sumEt();
            _lnu_mt           = sqrt( 2. * lepP4.Et() * theMET->getCorPt() * ( 1 - cos( lepP4.Phi() - theMET->getCorPhi() ) ) );
            _dphi_dipho_lnu   = fabs(H_P2.DeltaPhi(V_P2))                 ;
            _pt_balance       = (diphoP4.Pt() - V_P2.Mod())/diphoP4.Pt()  ;
            _njet             = tagJets.size();
            _max_jet_pt       = max_jet_pt;
            _max_jet_dCSV     = max_jet_dCSV;
            _min_dphi_jet_lnu = minDeltaPhiJetLNu; 

            float whmva    = WHMva_->EvaluateMVA( "BDT" );
            // float ptV = dipho->pt();


            // Getting the variables for AC-BDT
            _Anom_MVA_pho1_eta             = dipho->leadingPhoton()->eta();
            _Anom_MVA_pho1_phi             = dipho->leadingPhoton()->phi();
            _Anom_MVA_pho1_idmva           = dipho->leadPhotonId();
            _Anom_MVA_pho1_full5x5_r9      = dipho->leadingPhoton()->full5x5_r9();
            _Anom_MVA_pho1_ptOverMgg       = dipho->leadingPhoton()->pt() / dipho->mass();
            
            _Anom_MVA_pho2_eta             = dipho->subLeadingPhoton()->eta();
            _Anom_MVA_pho2_phi             = dipho->subLeadingPhoton()->phi();
            _Anom_MVA_pho2_idmva           = dipho->subLeadPhotonId();
            _Anom_MVA_pho2_full5x5_r9      = dipho->subLeadingPhoton()->full5x5_r9();
            _Anom_MVA_pho2_ptOverMgg       = dipho->subLeadingPhoton()->pt() / dipho->mass();
            

            _Anom_MVA_mu1_pt               = goodMuons.size()>0 ? goodMuons[0]->pt()     : -100;
            _Anom_MVA_mu1_eta              = goodMuons.size()>0 ? goodMuons[0]->eta()    : -100;
            _Anom_MVA_mu1_phi              = goodMuons.size()>0 ? goodMuons[0]->phi()    : -100;
            _Anom_MVA_mu1_energy           = goodMuons.size()>0 ? goodMuons[0]->energy() : -100;

            _Anom_MVA_mu2_pt               = goodMuons.size()>1 ? goodMuons[1]->pt()     : -100;
            _Anom_MVA_mu2_eta              = goodMuons.size()>1 ? goodMuons[1]->eta()    : -100;
            _Anom_MVA_mu2_phi              = goodMuons.size()>1 ? goodMuons[1]->phi()    : -100;
            _Anom_MVA_mu2_energy           = goodMuons.size()>1 ? goodMuons[1]->energy() : -100;


            _Anom_MVA_ele1_pt              = goodElectrons.size()>0 ? goodElectrons[0]->pt()     : -100;             
            _Anom_MVA_ele1_eta             = goodElectrons.size()>0 ? goodElectrons[0]->eta()    : -100;
            _Anom_MVA_ele1_phi             = goodElectrons.size()>0 ? goodElectrons[0]->phi()    : -100;
            _Anom_MVA_ele1_energy          = goodElectrons.size()>0 ? goodElectrons[0]->energy() : -100;

            _Anom_MVA_ele2_pt              = goodElectrons.size()>1 ? goodElectrons[1]->pt()     : -100;             
            _Anom_MVA_ele2_eta             = goodElectrons.size()>1 ? goodElectrons[1]->eta()    : -100;
            _Anom_MVA_ele2_phi             = goodElectrons.size()>1 ? goodElectrons[1]->phi()    : -100;
            _Anom_MVA_ele2_energy          = goodElectrons.size()>1 ? goodElectrons[1]->energy() : -100;
            
            _Anom_MVA_jet1_pt              = tagJets.size()>0 ? tagJets[0]->pt()     : -100;
            _Anom_MVA_jet1_phi             = tagJets.size()>0 ? tagJets[0]->phi()    : -100;
            _Anom_MVA_jet1_eta             = tagJets.size()>0 ? tagJets[0]->eta()    : -100;
            _Anom_MVA_jet1_energy          = tagJets.size()>0 ? tagJets[0]->energy() : -100;

            _Anom_MVA_jet2_pt              = tagJets.size()>1 ? tagJets[1]->pt()     : -100;
            _Anom_MVA_jet2_phi             = tagJets.size()>1 ? tagJets[1]->phi()    : -100;
            _Anom_MVA_jet2_eta             = tagJets.size()>1 ? tagJets[1]->eta()    : -100;
            _Anom_MVA_jet2_energy          = tagJets.size()>1 ? tagJets[1]->energy() : -100;

            _Anom_MVA_cosPhiGG             = TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), dipho->subLeadingPhoton()->phi()) );
            _Anom_MVA_cosPhiG1_Mu1         = goodMuons.size() > 0     ? TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), goodMuons[0]->phi()) )      : -100;
            _Anom_MVA_cosPhiG1_Ele1        = goodElectrons.size() > 0 ? TMath::Cos( deltaPhi(dipho->leadingPhoton()->phi(), goodElectrons[0]->phi()) )  : -100;
            _Anom_MVA_cosPhiG2_Mu1         = goodMuons.size() > 0     ? TMath::Cos( deltaPhi(dipho->subLeadingPhoton()->phi(), goodMuons[0]->phi()) )      : -100;
            _Anom_MVA_cosPhiG2_Ele1        = goodElectrons.size() > 0 ? TMath::Cos( deltaPhi(dipho->subLeadingPhoton()->phi(), goodElectrons[0]->phi()) )  : -100;


            _Anom_MVA_dR_Pho1Ele1_wh       = goodElectrons.size() > 0 ? deltaR(goodElectrons[0]->eta(), goodElectrons[0]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Ele1_wh       = goodElectrons.size() > 0 ? deltaR(goodElectrons[0]->eta(), goodElectrons[0]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho1Mu1_wh        = goodMuons.size() > 0 ? deltaR(goodMuons[0]->eta(), goodMuons[0]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Mu1_wh        = goodMuons.size() > 0 ? deltaR(goodMuons[0]->eta(), goodMuons[0]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;



            _Anom_MVA_dR_Pho1Jet1_wh       = tagJets.size() > 0 ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho1Jet2_wh       = tagJets.size() > 1 ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), dipho->leadingPhoton()->eta(), dipho->leadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Jet1_wh       = tagJets.size() > 0 ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;
            _Anom_MVA_dR_Pho2Jet2_wh       = tagJets.size() > 1 ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), dipho->subLeadingPhoton()->eta(), dipho->subLeadingPhoton()->phi()) : -100;

            _Anom_MVA_dR_Mu1Jet1_wh        = ((goodMuons.size() > 0)&&(tagJets.size() > 0))      ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), goodMuons[0]->eta(), goodMuons[0]->phi())         : -100;
            _Anom_MVA_dR_Mu1Jet2_wh        = ((goodMuons.size() > 0)&&(tagJets.size() > 1))      ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), goodMuons[0]->eta(), goodMuons[0]->phi())         : -100;
            
            _Anom_MVA_dR_Ele1Jet1_wh       = ((goodElectrons.size() > 0)&&(tagJets.size() > 0)) ? deltaR(tagJets[0]->eta(), tagJets[0]->phi(), goodElectrons[0]->eta(), goodElectrons[0]->phi()) : -100;
            _Anom_MVA_dR_Ele1Jet2_wh       = ((goodElectrons.size() > 0)&&(tagJets.size() > 1)) ? deltaR(tagJets[1]->eta(), tagJets[1]->phi(), goodElectrons[0]->eta(), goodElectrons[0]->phi()) : -100;



            // Evaluating Anomalous MVA
            float WHiggs0MToGG_MVA                = WHiggs0MToGG_MVA_->EvaluateMVA( "BDT" );   
            float WHiggs0PHToGG_MVA               = WHiggs0PHToGG_MVA_->EvaluateMVA( "BDT" );    
            float WHiggs0L1ToGG_MVA               = WHiggs0L1ToGG_MVA_->EvaluateMVA( "BDT" );    


            //AC MVA we are currently look at fa3=1
            float anom_mva = WHiggs0MToGG_MVA;


            // Categorization by WHMVA & ptV (0~75, 75~150, 150~)
            int catnum = chooseCategoryAC( whmva, anom_mva );

            if( catnum != -1 ) {
                whleptonictags_obj.setCategoryNumber( catnum );
                int chosenTag = computeStage1Kinematics( whleptonictags_obj );
                whleptonictags_obj.setStage1recoTag( chosenTag );
                whleptonictags_obj.setJets( tagJets );
                whleptonictags_obj.setMuons( goodMuons );
                whleptonictags_obj.setElectrons( goodElectrons );
                whleptonictags_obj.setDiPhotonIndex( diphoIndex );
                whleptonictags_obj.setSystLabel( systLabel_ );
                whleptonictags_obj.setMET( theMET );
                //STXS MVA & AC MVA
                whleptonictags_obj.set_VHmva(whmva);
                whleptonictags_obj.set_WHiggs0MToGG_MVA(WHiggs0MToGG_MVA);
                whleptonictags_obj.set_WHiggs0PHToGG_MVA(WHiggs0PHToGG_MVA);
                whleptonictags_obj.set_WHiggs0L1ToGG_MVA(WHiggs0L1ToGG_MVA);

                if( ! evt.isRealData() ) {
                    whleptonictags_obj.setAssociatedZ( associatedZ );
                    whleptonictags_obj.setAssociatedW( associatedW );
                    whleptonictags_obj.setVhasNeutrinos( VhasNeutrinos );
                    whleptonictags_obj.setVhasLeptons( VhasLeptons );
                    whleptonictags_obj.setVhasHadrons( VhasHadrons );
                    whleptonictags_obj.setVpt( Vpt );
                }

                whleptonictags->push_back( whleptonictags_obj );

                if( ! evt.isRealData() ) {
                    VHTagTruth truth_obj;
                    truth_obj.setAssociatedZ( associatedZ );
                    truth_obj.setAssociatedW( associatedW );
                    truth_obj.setVhasDaughters( VhasDaughters );
                    truth_obj.setVhasNeutrinos( VhasNeutrinos );
                    truth_obj.setVhasLeptons( VhasLeptons );
                    truth_obj.setVhasHadrons( VhasHadrons );
                    truth_obj.setVhasMissingLeptons( VhasMissingLeptons );
                    truth_obj.setVpt( Vpt );
                    //truths->push_back( truth_obj );
                    //whleptonictags->back().setTagTruth( edm::refToPtr( edm::Ref<vector<VHTagTruth> >( rTagTruth, idx++ ) ) );
                }
            }
        }
        evt.put( std::move( whleptonictags ) );
        //evt.put( std::move( truths ) );
    }

    int WHLeptonicTagProducer::computeStage1Kinematics( const WHLeptonicTag tag_obj )
    {
        int chosenTag_ = DiPhotonTagBase::stage1recoTag::LOGICERROR;
        int catNum = tag_obj.categoryNumber();

        if ( catNum == 0 ) {
            chosenTag_ = DiPhotonTagBase::stage1recoTag::RECO_WH_LEP_Tag0;
        }
        else if ( catNum == 1 ) {
            chosenTag_ = DiPhotonTagBase::stage1recoTag::RECO_WH_LEP_Tag1;
        }
        else if ( catNum == 2 ) {
            chosenTag_ = DiPhotonTagBase::stage1recoTag::RECO_WH_LEP_Tag2;
        }
        else if ( catNum == 3 ) {
            chosenTag_ = DiPhotonTagBase::stage1recoTag::RECO_WH_LEP_Tag3;
        }

        return chosenTag_;
    }

}
typedef flashgg::WHLeptonicTagProducer FlashggWHLeptonicTagProducer;
DEFINE_FWK_MODULE( FlashggWHLeptonicTagProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

