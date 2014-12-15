#include "AnalysisEvent.h"
#include <vector>
#include <map>
#include "plots.h"
#include <fstream>
#include "TLorentzVector.h"

class Cuts{
  bool makeLeptonCuts(AnalysisEvent*,float*,std::map<std::string,Plots*>, TH1F*);
  bool invertIsoCut(AnalysisEvent*,float*,std::map<std::string,Plots*>, TH1F*);
  std::vector<int> makeJetCuts(AnalysisEvent*,int);
  std::vector<int> makeMetCuts(AnalysisEvent*);
  std::vector<int> makeBCuts(AnalysisEvent*, std::vector<int>);
  
  std::vector<int> getTightEles(AnalysisEvent* event);
  std::vector<int> getInvIsoEles(AnalysisEvent* event);
  std::vector<int> getLooseEles(AnalysisEvent* event);
  std::vector<int> getTightMuons(AnalysisEvent* event);
  std::vector<int> synchTightMuons(AnalysisEvent* event);
  std::vector<int> getInvIsoMuons(AnalysisEvent* event);
  std::vector<int> getLooseMuons(AnalysisEvent* event);
  float getZCand(AnalysisEvent*, std::vector<int>, std::vector<int>);
  bool triggerCuts(AnalysisEvent*);
  
  //Method for running the synchronisation with Jeremy.
  bool synchCuts(AnalysisEvent * event);
  int getLooseLepsNum(AnalysisEvent * event); //Mimic preselection skims
  int getLooseElecs(AnalysisEvent* event);
  int getLooseMus(AnalysisEvent* event);

  //Simple deltaR function, because the reco namespace doesn't work or something
  double deltaR(float,float,float,float);
  void dumpToFile(AnalysisEvent * event, int);

  //Function to get lepton SF
  float getLeptonWeight(AnalysisEvent*);
  float eleSF(float, float);
  float muonSF(float, float);

  // Tight electron cuts
  unsigned int numTightEle_;
  float tightElePt_;
  float tightEleEta_;
  float tightEled0_;
  int tightEleMissLayers_;
  bool tightEleCheckPhotonVeto_;
  float tightEleMVA_;
  float tightEleRelIso_;
  
  //Loose electron cuts
  unsigned int numLooseEle_;
  float looseElePt_;
  float looseEleEta_;
  float looseEleMVA_;
  float looseEleRelIso_;

  //Tight muon cuts
  unsigned int numTightMu_;
  float tightMuonPt_;
  float tightMuonEta_;
  float tightMuonRelIso_;

  //Loose muon cuts
  unsigned int numLooseMu_;
  float looseMuonPt_;
  float looseMuonEta_;
  float looseMuonRelIso_;
  

  //Tight jet cuts
  unsigned int numJets_;
  float jetPt_;
  float jetEta_;
  int jetNConsts_;
  bool jetIDDo_;

  //B-Disc cut
  unsigned int numbJets_;
  float bDiscCut_;
  
  //set to true to fill in histograms.
  bool doPlots_;
  bool fillCutFlow_; // Fill cut flows
  bool invertIsoCut_; // For background estimation
  bool synchCutFlow_; //For synch
  bool tighterMuonID_; //Tighter muon ID.
  bool singleEventInfoDump_; //For dropping info on event for synching.

  //For producing post-lepsel skims
  TTree* postLepSelTree_;

  //Some things that will be used for JEC uncertainties.
  std::vector<float> ptMinJEC_;
  std::vector<float> ptMaxJEC_;
  std::vector<float> etaMinJEC_;
  std::vector<float> etaMaxJEC_;
  std::vector<std::vector <float> > jecSFUp_;
  std::vector<std::vector <float> > jecSFDown_;
  void initialiseJECCors();
  float getJECUncertainty(float,float,int);
  TLorentzVector getJetLVec(AnalysisEvent*,int,int);

  //Histogram to be used in synchronisation.
  TH1F* synchCutFlowHist_;
  TH1I* synchNumEles_;
  TH1I* synchNumMus_;
  TH1I* synchMuonCutFlow_;
  bool makeEventDump_;
  ofstream step0EventDump_;
  ofstream step2EventDump_;
  ofstream step4EventDump_;
  ofstream step6EventDump_;
  //Sets whether to do MC or data cuts. Set every time a new dataset is processed in the main loop.
  bool isMC_;
  std::string triggerFlag_;
  std::string postfixName_;

  //Sets trigger from config file
  std::string cutConfTrigLabel_;

 public:
  Cuts(bool,bool,bool,bool,bool,bool);
  ~Cuts();
  bool makeCuts(AnalysisEvent*,float*,std::map<std::string,Plots*>, TH1F*,int);
  void setTightEle(float pt = 20, float eta = 2.5, float d0 = 0.04);
  void setMC(bool isMC) {isMC_ = isMC;};
  void setCloneTree(TTree* tree) {postLepSelTree_ = tree;};
  void setTriggerFlag(std::string triggerFlag) {triggerFlag_ = triggerFlag;};
  bool parse_config(std::string);
  void dumpLeptonInfo(AnalysisEvent*);
  void dumpLooseLepInfo(AnalysisEvent*);
  TH1F* getSynchCutFlow();
  int numFound(){return synchCutFlowHist_->GetBinContent(4);};
  void setEventInfoFlag(bool flag){singleEventInfoDump_ = flag;};
};
