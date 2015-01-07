#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h> 
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TPad.h"
#include "config_parser.h"
#include "AnalysisEvent.h"
#include "cutClass.h"
#include <libconfig.h++>
#include "histogramPlotter.h"
#include <iomanip>
#include <map>
#include <math.h>

//This method is here to set up a load of branches in the TTrees that I will be analysing. Because it's vastly quicker to not load the whole damned thing.
void setBranchStatusAll(TTree * chain, bool isMC, std::string triggerFlag){
  //Get electron branches
  chain->SetBranchStatus("numElePF2PAT",1);  
  chain->SetBranchStatus("elePF2PATPT",1);
  chain->SetBranchStatus("elePF2PATPX",1);
  chain->SetBranchStatus("elePF2PATPY",1);
  chain->SetBranchStatus("elePF2PATPZ",1);
  chain->SetBranchStatus("elePF2PATE",1);
  chain->SetBranchStatus("elePF2PATIsGsf",1);
  chain->SetBranchStatus("elePF2PATGsfPx",1);
  chain->SetBranchStatus("elePF2PATGsfPy",1);
  chain->SetBranchStatus("elePF2PATGsfPz",1);
  chain->SetBranchStatus("elePF2PATGsfE",1);
  chain->SetBranchStatus("elePF2PATEta",1);
  chain->SetBranchStatus("elePF2PATPhi",1);
  chain->SetBranchStatus("elePF2PATBeamSpotCorrectedTrackD0",1);
  chain->SetBranchStatus("elePF2PATMissingInnerLayers",1);
  chain->SetBranchStatus("elePF2PATPhotonConversionVeto",1);
  chain->SetBranchStatus("elePF2PATMVA",1);
  chain->SetBranchStatus("elePF2PATComRelIsoRho",1);
  chain->SetBranchStatus("elePF2PATComRelIsodBeta",1);
  chain->SetBranchStatus("elePF2PATComRelIso",1);
  chain->SetBranchStatus("elePF2PATChHadIso",1);
  chain->SetBranchStatus("elePF2PATNtHadIso",1);
  chain->SetBranchStatus("elePF2PATGammaIso",1);
  chain->SetBranchStatus("elePF2PATRhoIso",1);
  chain->SetBranchStatus("elePF2PATAEff03",1);
  chain->SetBranchStatus("elePF2PATCharge",1);
  chain->SetBranchStatus("elePF2PATTrackD0",1);
  chain->SetBranchStatus("elePF2PATTrackDBD0",1);
  chain->SetBranchStatus("elePF2PATD0PV",1);
  chain->SetBranchStatus("elePF2PATBeamSpotCorrectedTrackD0",1);
  chain->SetBranchStatus("elePF2PATSCEta",1);
  //get muon branches
  chain->SetBranchStatus("muonPF2PATIsPFMuon",1);
  chain->SetBranchStatus("muonPF2PATGlobalID",1);
  chain->SetBranchStatus("muonPF2PATTrackID",1);
  chain->SetBranchStatus("numMuonPF2PAT",1);
  chain->SetBranchStatus("muonPF2PATPt",1);
  chain->SetBranchStatus("muonPF2PATPX",1);
  chain->SetBranchStatus("muonPF2PATPY",1);
  chain->SetBranchStatus("muonPF2PATPZ",1);
  chain->SetBranchStatus("muonPF2PATE",1);  
  chain->SetBranchStatus("muonPF2PATEta",1);
  chain->SetBranchStatus("muonPF2PATPhi",1);
  chain->SetBranchStatus("muonPF2PATCharge",1);  
  chain->SetBranchStatus("muonPF2PATComRelIsodBeta",1);
  chain->SetBranchStatus("muonPF2PATTrackDBD0",1);
  chain->SetBranchStatus("muonPF2PATD0",1);
  chain->SetBranchStatus("muonPF2PATDBInnerTrackD0",1);
  chain->SetBranchStatus("muonPF2PATTrackDBD0",1);
  chain->SetBranchStatus("muonPF2PATBeamSpotCorrectedD0",1);
  chain->SetBranchStatus("muonPF2PATD0",1);
  chain->SetBranchStatus("muonPF2PATChi2",1);
  chain->SetBranchStatus("muonPF2PATNDOF",1);
  chain->SetBranchStatus("muonPF2PATVertX",1);
  chain->SetBranchStatus("muonPF2PATVertY",1);
  chain->SetBranchStatus("muonPF2PATVertZ",1);
  chain->SetBranchStatus("muonPF2PATNChambers",1);
  chain->SetBranchStatus("muonPF2PATTrackNHits",1);
  chain->SetBranchStatus("muonPF2PATMuonNHits",1);
  chain->SetBranchStatus("muonPF2PATTkLysWithMeasurements",1);
  chain->SetBranchStatus("muonPF2PATGlbTkNormChi2",1);
  chain->SetBranchStatus("muonPF2PATDBPV",1);
  chain->SetBranchStatus("muonPF2PATDZPV",1);
  chain->SetBranchStatus("muonPF2PATVldPixHits",1);
  chain->SetBranchStatus("muonPF2PATMatchedStations",1);
    //Jet variables
  chain->SetBranchStatus("numJetPF2PAT",1);
  chain->SetBranchStatus("jetPF2PATPx",1);
  chain->SetBranchStatus("jetPF2PATPy",1);
  chain->SetBranchStatus("jetPF2PATPz",1);
  chain->SetBranchStatus("jetPF2PATE",1);
  chain->SetBranchStatus("jetPF2PATEt",1);
  chain->SetBranchStatus("jetPF2PATPt",1);
  chain->SetBranchStatus("jetPF2PATPtRaw",1);
  chain->SetBranchStatus("jetPF2PATUnCorPt",1);
  chain->SetBranchStatus("jetPF2PATEta",1);
  chain->SetBranchStatus("jetPF2PATPhi",1);
  chain->SetBranchStatus("jetPF2PATNConstituents",1);
  chain->SetBranchStatus("jetPF2PAT*EnergyFractionCorr",1);
  chain->SetBranchStatus("jetPF2PAT*EnergyFraction",1);
  chain->SetBranchStatus("jetPF2PATChargedMultiplicity",1);
  chain->SetBranchStatus("jetPF2PATdRClosestLepton",1);
  //BTag
  chain->SetBranchStatus("jetPF2PATBDiscriminator",1);
  //MET variables - for plotting (no cuts on these)
  chain->SetBranchStatus("metPF2PATEt",1);
  chain->SetBranchStatus("metPF2PATPt",1);
  //primary vertex info. For muon cut
  chain->SetBranchStatus("pvX",1);
  chain->SetBranchStatus("pvY",1);
  chain->SetBranchStatus("pvZ",1);
  //Event info
  chain->SetBranchStatus("eventNum",1);
  chain->SetBranchStatus("eventRun",1);
  chain->SetBranchStatus("eventLumiblock",1);

  if (!isMC){
    chain->SetBranchStatus("HLT_Mu17_Mu8_v*",1);
    chain->SetBranchStatus("HLT_Mu17_TkMu8_v*",1);
    chain->SetBranchStatus("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_*",1);
    chain->SetBranchStatus("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_*",1);
    chain->SetBranchStatus("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",1);
  }
  else{
    chain->SetBranchStatus("HLT_Mu17_Mu8_v12",1);
    chain->SetBranchStatus("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_v9",1);
    chain->SetBranchStatus("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_v9",1);
    chain->SetBranchStatus("HLT_Mu17_TkMu8_v5",1);
    chain->SetBranchStatus("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v11",1);
  }
}

static void show_usage(std::string name){
  std::cerr << "Usage: " << name << " <options>"
	    << "Options:\n"
	    << "\t-c  --config\tCONFIGURATION\tThe configuration file to be run over\n"
	    << "\t-p\t\t\t\tMake all plots. Currently segfaults if this isn't set, I believe.\n"
            << "\t-n\t\t\t\tSet the number of events to run over. Leave blank for all.\n"
            << "\t-l\t\t\t\tIf this option is set, scale MC plots to a fixed lumi. Default is lumi from data samples.\n"
	    << "\t-o  --outFolder\tOUTFOLDER\tOutput folder for plots. If set overwrites what may be in the config file.\n"
	    << "\t-s  --postfix\tPOSTFIX\t\tPostfix for produced plots. Over-rides anything set in a configuration file.\n"
	    << "\t-d\t\t\t\tDump event info. For now this is the yield at each stage. May also include event lists later on. \n\t\t\t\t\tIf this flag is set all event weights are 1.\n"
	    << "\t-x  --cutConf\tCUTCONF\t\tOverrides the cut configuration given in the usual configuration file.\n\t\t\t\t\tThis is mostly so that MC can be run on different cuts without having to make wqhole new confs.\n"
	    << "\t    --plotConf\tPLOTCONF\tOverrides the plot configuration file in the usual configuration file. \n\t\t\t\t\tFor various reasons I guess. Also sets -p flag automatically. If you don't want plots, DON'T USE THIS OPTION.\n"
	    << "\t-i\t\t\t\tInvert the isolation cut of the third lepton. This is for background estimation purposes. \n\t\t\t\t\tWho knows how I am supposed to use that though.\n"
	    << "\t-a  --synch\t\t\tMakes cutflows for synch exercise i.e. detailed lepSel cutflows. Doesn't do full event selection.\n"
	    << "\t-e\t\t\t\tGive a comma separated list of events to run on. This is for synch, but might be useful later?\n"
	    << "\t-f  --nFiles NFILES\t\tUses a specific number of files to run over. \n\t\t\t\t\tThis is useful if testing stuff so that it doesn't have to access the T2 a lot etc.\n"
	    << "\t-m\t\t\t\tMonte carlo only mode. Will not run over any data in the configuration.\n"
	    << "\t-b\t\t\t\tData only mode. Only runs over data, skips all MC.\n"
	    << "\t-t\t\t\t\tUse b-tagging efficiencies to reweight MC\n"
	    << "\t-y\t\t\t\tProduces a file of event dumps for stages of the synch.\n"
	    << "\t-g\t\t\t\tMakes post-lepSel tree\n"
	    << "\t-u\t\t\t\tUses post-lepSel trees\n"
	    << "\t-z  --makeMVATree\t\tProduce a tree after event selection for MVA purposes\n"
	    << "\t-v  --syst  SYST\t\tDo the desired systematic. Brief workaround here, not final yet\n"
	    << "\t-j\t\t\t\tMake b-tagging efficiency histograms. Probably doesn't need to be run too many times.\n"
	    << "\t-h  --help\t\t\tShow this help message\n"
	    << std::endl;
}
		       
int main(int argc, char* argv[]){

  //Set up environment a little.
  std::cerr << std::setprecision(1) << std::fixed;
  std::cout << std::setprecision(1) << std::fixed;
  // "This is the main function. It basically just loads a load of other stuff.";
  //Parse command line arguments - looking for config file.
  if (argc < 3){
    show_usage(argv[0]);
    return 1;
  }
  //Various variables that will be used in the analysis. These should really be in a .h file but... I'm lazy. Sorry.
  std::string config = "";
  bool plots = false;
  double usePreLumi = 20000.;
  long nEvents = 0.;
  std::string outFolder = "plots/";
  std::string postfix = "default";
  std::string channel = "";
  bool infoDump = false;
  bool invertIsoCut = false; //For z+jets background estimation
  bool synchCutFlow = false; // For synch
  bool skipData = false; //utility stuff. True if flags are set and will skip either data or mc.
  bool skipMC = false;
  std::string* cutConfName = new std::string("");
  std::string* plotConfName = new std::string("");
  int numFiles = -1;
  bool readEventList = false;
  bool dumpEventNumbers = false;
  bool makePostLepTree = false;
  bool makeMVATree = false;
  bool usePostLepTree = false;
  bool usebTagWeight = false;
  int systToRun = 0;
  bool makeBTagEffPlots = false;

  // variables for plotting. 
  std::vector<std::string> plotNames;
  std::vector<float> xMin;
  std::vector<float> xMax;
  std::vector<int> nBins,cutStage;
  std::vector<std::string> fillExp;
  std::vector<std::string> xAxisLabels;
  std::vector<int> eventNumbers;


  // Loop for parsing command line arguments.
  for (int i = 1; i < argc; ++i){
    std::string arg = argv[i];
    if ((arg=="-h") || (arg == "--help")){ // Display help stuff
      show_usage(argv[0]);
      return 0;
    }
    else if ((arg=="-c")||(arg=="--config")){ // Sets configuration file - Required!
      if (i + 1 < argc) {
      config = argv[++i];
      } else{
	std::cerr << "--config requires an argument!";
	return 0;
      }
    }
    else if (arg=="-n") { // using this option sets the number of entries to run over.
      if (i+1 < argc){
	nEvents = atol(argv[++i]);
      }else{
	std::cerr << "-n requires a number of events to run over! You idiot!";
      }
    }
    else if (arg=="-p") {
      plots = true;
    }
    else if ((arg=="-o")||(arg=="--outFolder")){//Set output folder
      if (i + 1 < argc){
	outFolder = argv[++i];
      } else{
	std::cerr << "requires a string for output folder name.";
      }
    }
    else if ((arg=="-s")||(arg=="--postfix")){//Set plot postfix
      if (i + 1 < argc){
	postfix = argv[++i];
      } else{
	std::cerr << "requires a string for plot postfix.";
      }
    }
    else if (arg=="-l"){
      if (i+1 < argc){
	usePreLumi = atof(argv[++i]);
      }else{
	std::cerr << "-l requries a float!";
	return 0;
      }
    }
    else if (arg == "-d"){//Option for dumping event information about selected events.
      infoDump = true;
    }
    else if (arg == "-x" || arg == "--cutConf"){
      if (i+1 < argc){
	*cutConfName = argv[++i];
      }else{
	std::cerr <<" -x requires an argument";
	return 0;
      }
    }
    else if (arg == "--plotConf"){
      if (i+1 < argc){
	*plotConfName = argv[++i];
	plots = true;
      }else{
	std::cerr <<" --plotConf requires an argument";
	return 0;
      }
    }
    else if (arg == "-i"){ //Set up anti-isolation cut for 
      invertIsoCut = true;
    }
    else if (arg == "-a" || arg == "--synch"){ // Change to synch exercise cut flow.
      synchCutFlow = true;
    }
    else if (arg == "-m"){
      skipData = true;
    }
    else if (arg == "-b"){
      skipMC = true;
    }
    else if (arg == "-y"){
      dumpEventNumbers = true;
    }
    else if (arg == "-t"){
      usebTagWeight = true;
    }
    else if (arg == "-f" || arg == "--nFiles"){
      if (i+1 < argc){
	numFiles = atoi(argv[++i]);
      }else{
	 std::cerr << "-f requires an int";
	 return 0;
      }
    }
    else if (arg == "-e"){
      readEventList = true;
      std::stringstream ss(argv[++i]);
      std::string item;
      while (std::getline(ss,item,',')){
	eventNumbers.push_back(atoi(item.c_str()));
      }
    }
    else if (arg == "-g"){
      makePostLepTree = true;
    }
    else if (arg == "-z" || arg == "--makeMVATree"){
      makeMVATree = true;
    }
    else if (arg == "-u"){
      usePostLepTree = true;
    }
    else if (arg == "-v" || arg == "--syst"){
      if (i+1 < argc){
	systToRun = atoi(argv[++i]);
      }
      else{
	std::cerr << "-v requires an int";
	return 0;
      }
    }
    else if (arg == "-j"){
      makeBTagEffPlots = true;
    }
    
    
    
  } // End command line arguments loop.
  if (config == ""){
    std::cerr << "We need a configuration file! Type -h for usage. Error";
    return 0;
  }
  if (usebTagWeight && !usePostLepTree){
    std::cerr << "At the moment only getting btag weights from post lep-sel trees is supported. Sorry everyone.";
    return 0;
  }
  if (usebTagWeight && makeBTagEffPlots){
    std::cerr << "I doubt that set of options is a good idea, so I'm going to just quietly exit here. Don't generate and use b-tag efficiency numbers at the same time...";
    return 0;
  }

  //Make some vectors that will be filled in the parsing.
  std::vector<Dataset> datasets;
  double totalLumi = 0;
  double* lumiPtr = &totalLumi;
  if (!Parser::parse_config(config,&datasets,lumiPtr,&plotNames,&xMin,&xMax,&nBins,&fillExp,&xAxisLabels,&cutStage,cutConfName,plotConfName,&outFolder,&postfix,&channel)){
    std::cerr << "There was an error parsing the config file.\n";
    return 0;
  }

  //Making a vector of strings that will give systematics name.
  std::vector<std::string> systNames;
  systNames.push_back("");
  systNames.push_back("__trig__plus");
  systNames.push_back("__trig__minus");
  systNames.push_back("__jer__plus");
  systNames.push_back("__jer__minus");
  systNames.push_back("__jes__plus");
  systNames.push_back("__jes__minus");
  systNames.push_back("__pileup__plus");
  systNames.push_back("__pileup__minus");

  //Make cuts object. The methods in it should perhaps just be i nthe AnalysisEvent class....
  Cuts * cutObj = new Cuts(plots,plots||infoDump,invertIsoCut,synchCutFlow,dumpEventNumbers);
  if (!cutObj->parse_config(*cutConfName)){
    std::cerr << "There was a problem with parsing the config!" << std::endl;
    return 0;
  };
  
  //Make pileupReweighting stuff here
  TFile * dataPileupFile = new TFile("pileup/truePileupTest.root","READ");
  TH1F* dataPU = (TH1F*)(dataPileupFile->Get("pileup")->Clone());
  TFile * mcPileupFile = new TFile("pileup/pileupMC.root","READ");
  TH1F* mcPU = (TH1F*)(mcPileupFile->Get("pileup")->Clone());

  //Get systematic files too.
  TFile * systUpFile = new TFile("pileup/truePileupUp.root","READ");
  TH1F* pileupUpHist = (TH1F*)(systUpFile->Get("pileup")->Clone());
  TFile * systDownFile = new TFile("pileup/truePileupDown.root","READ");
  TH1F* pileupDownHist = (TH1F*)(systDownFile->Get("pileup")->Clone());

  TH1F* puReweight = (TH1F*)dataPU->Clone();
  puReweight->Scale(1.0/puReweight->Integral());
  mcPU->Scale(1.0/mcPU->Integral());
  puReweight->Divide(mcPU);
  puReweight->SetDirectory(0);

  /// And do the same for systematic sampl
  TH1F* puSystUp = (TH1F*)pileupUpHist->Clone();
  puSystUp->Scale(1.0/puSystUp->Integral());
  puSystUp->Divide(mcPU);
  puSystUp->SetDirectory(0);
  TH1F* puSystDown = (TH1F*)pileupDownHist->Clone();
  puSystDown->Scale(1.0/puSystDown->Integral());
  puSystDown->Divide(mcPU);
  puSystDown->SetDirectory(0);

  dataPileupFile->Close();
  mcPileupFile->Close();
  systUpFile->Close();
  systDownFile->Close();

  //Do a little initialisation for the plots here. Will later on be done in a config file.
  
  //Initialise plot stage names.
  std::vector<std::string> stageNames (4);
  stageNames = {"lepSel","zMass","jetSel","bTag"};

  //Make the plots. If plots have been set. Changing this to a map.
  std::map<std::string, std::map<std::string, Plots*> > plotsMap;
  std::map<std::string, TH1F*> cutFlowMap;

  //A couple of things for plotting. These will soon be set in a config file.
  std::vector<std::string> legOrder;
  std::vector<std::string> plotOrder;
  std::map<std::string, datasetInfo> datasetInfos;

  if (totalLumi == 0.) totalLumi = usePreLumi;
  for (std::vector<Dataset>::iterator dataset = datasets.begin(); dataset!=datasets.end(); ++dataset){
    if (dataset->isMC() && skipMC) continue;
    if (!dataset->isMC() && skipData) continue;
    if (plots||infoDump) { // Initialise a load of stuff that's required by the plotting macro.
      int systMask = 1;
      for (unsigned int systInd = 0; systInd < systNames.size(); systInd++){
	if (systInd > 0 && !(systToRun & systMask)){
	  systMask = systMask << 1;
	  continue;
	}
	if (cutFlowMap.find(dataset->getFillHisto()+systNames[systInd]) == cutFlowMap.end()){
	  legOrder.push_back(dataset->getFillHisto());
	  plotOrder.push_back(dataset->getFillHisto());
	  cutFlowMap[dataset->getFillHisto()] = new TH1F((dataset->getFillHisto()+systNames[systInd]+"cutFlow").c_str(),(dataset->getFillHisto()+systNames[systInd]+"cutFlow").c_str(),4,0,4); //Hopefully make this configurable later on. Same deal as the rest of the plots I guess, work out libconfig.
	  if (systInd == 0){
	    datasetInfos[dataset->getFillHisto()] = datasetInfo();
	    datasetInfos[dataset->getFillHisto()].colour = dataset->getColour();
	    datasetInfos[dataset->getFillHisto()].legLabel = dataset->getPlotLabel();
	    datasetInfos[dataset->getFillHisto()].legType = dataset->getPlotType();
	  }
	  if (plots){ // Only make all the plots if it's entirely necessary.
	    plotsMap[(dataset->getFillHisto()+systNames[systInd]).c_str()] = std::map<std::string,Plots*>();
	  
	    for (unsigned int j = 0; j < stageNames.size(); j++){
	      plotsMap[(dataset->getFillHisto()+systNames[systInd]).c_str()][stageNames[j]] = new Plots(plotNames, xMin, xMax,nBins, fillExp, xAxisLabels, cutStage, j, dataset->getFillHisto()+"_"+stageNames[j]+systNames[systInd]);
	    }
	  }
	}//end cutFlow find loop
	if (systInd > 0) systMask = systMask << 1;
      }//end systematic loop
      
    } //end plots if
    //If making either plots or doing the event dump, make cut flow object.
    std::cerr << "Processing dataset " << dataset->name() << std::endl;
    TChain * datasetChain = new TChain(dataset->treeName().c_str());
    if (!usePostLepTree){
      if (!dataset->fillChain(datasetChain,numFiles)){
	std::cerr << "There was a problem constructing the chain for " << dataset->name() << ". Continuing with next dataset.\n";
	continue;
      }
    }
    else{
      std::string inputPostfix = "";
      inputPostfix += postfix;
      inputPostfix += invertIsoCut?"invIso":"";
      std::cout << "skims/"+dataset->name()+inputPostfix + "SmallSkim.root" << std::endl;
      datasetChain->Add(("skims/"+dataset->name()+inputPostfix + "SmallSkim.root").c_str());
      std::ifstream secondTree(("skims/"+dataset->name()+inputPostfix + "SmallSkim1.root").c_str());
      if (secondTree.good()) datasetChain->Add(("skims/"+dataset->name()+inputPostfix + "SmallSkim1.root").c_str());
    }
    cutObj->setMC(dataset->isMC());
    cutObj->setEventInfoFlag(readEventList);
    cutObj->setTriggerFlag(dataset->getTriggerFlag());
    std::cout << "Trigger flag: " << dataset->getTriggerFlag() << std::endl;

    //Here we will initialise the b-tag eff plots if we are doing b-tag efficiencies
    std::vector<TH2D*> bTagEffPlots;
    std::vector<std::string> denomNum {"Denom","Num"};
    std::vector<std::string> typesOfEff {"b","c","uds","g"};
    if (makeBTagEffPlots && dataset->isMC()){
      int ptBins = 4, etaBins = 4;
      float ptMin = 0., ptMax = 200., etaMin = 0., etaMax = 2.4;
      for (int unsigned denNum = 0; denNum < denomNum.size(); denNum++){
	for (int unsigned type = 0; type < typesOfEff.size(); type++){
	  bTagEffPlots.push_back(new TH2D(("bTagEff_"+denomNum[denNum]+"_"+typesOfEff[type]).c_str(),("bTagEff_"+denomNum[denNum]+"_"+typesOfEff[type]).c_str(),ptBins,ptMin,ptMax,etaBins,etaMin,etaMax));
	}
      }
      cutObj->setBTagPlots(bTagEffPlots,true);
    }//end btag eff plots.
    if (usePostLepTree && usebTagWeight && dataset->isMC()){
      //Get efficiency plots from the file. Will have to be from post-lep sel trees I guess.
      std::string inputPostfix = "";
      inputPostfix += postfix;
      inputPostfix += invertIsoCut?"invIso":"";
      TFile * datasetFileForHists = new TFile(("skims/"+dataset->name() + inputPostfix + "SmallSkim.root").c_str(), "READ");
      for (int unsigned denNum = 0; denNum < denomNum.size(); denNum++){
	for (int unsigned eff = 0; eff < typesOfEff.size(); eff++){
	  bTagEffPlots.push_back((TH2D*)(datasetFileForHists->Get(("bTagEff_"+denomNum[denNum]+"_"+typesOfEff[eff]).c_str())->Clone()));
	}
      }
      for (int unsigned plotIt = 0; plotIt < bTagEffPlots.size(); plotIt++){
	bTagEffPlots[plotIt]->SetDirectory(0);
      }
      cutObj->setBTagPlots(bTagEffPlots,false);
      datasetFileForHists->Close();
    }
    //extract the dataset weight.
    float datasetWeight = dataset->getDatasetWeight(totalLumi);


    //Apply trigger SF here. Also does systematic for trigger +-
    if (infoDump) datasetWeight = 1;
    std::cout << datasetChain->GetEntries() << " number of items in tree. Dataset weight: " << datasetWeight << std::endl;
    AnalysisEvent * event = new AnalysisEvent(dataset->isMC(),dataset->getTriggerFlag(),datasetChain);

    //Adding in some stuff here to make a skim file out of post lep sel stuff
    TTree * cloneTree = 0;
    TTree * cloneTree2 = 0;
    if (makePostLepTree){
      cloneTree = datasetChain->CloneTree(0);
      cloneTree2 = datasetChain->CloneTree(0);
      cutObj->setCloneTree(cloneTree,cloneTree2);
    }
    //If we're making the MVA tree, set it up here. 
    std::vector<TTree *> mvaTree;
    //Add a few variables into the MVA tree for easy access of stuff like lepton index etc
    float eventWeight = 0;
    int zLep1Index = -1; // Addresses in elePF2PATWhatever of the z lepton
    int zLep2Index = -1;
    int wLepIndex = -1;
    int jetInd[15];  // The index of the selected jets;
    int bJetInd[10]; // Index of selected b-jets;
    //Now add in the branches:
    
    if (makeMVATree){
      int systMask = 1;
      std::cout << "Making systematic trees for " << dataset->name() << ": ";
      for (unsigned int systIn = 0; systIn < systNames.size(); systIn++){
	std::cout << systNames[systIn] << " ";
	//	std::cout << "Making systs: " << systMask << " " << systToRun << " " << systIn << " " << (systMask & systToRun) << std::endl;
	/*	if (systIn > 0 && !(systMask & systToRun)){
	  if (systIn > 0) systMask = systMask << 1;
	  continue;
	  }*/
	mvaTree.push_back(datasetChain->CloneTree(0));
	mvaTree[systIn]->SetName((mvaTree[systIn]->GetName()+systNames[systIn]).c_str());
	mvaTree[systIn]->Branch("eventWeight", &eventWeight, "eventWeight/F");
	mvaTree[systIn]->Branch("zLep1Index",&zLep1Index,"zLep1Index/I");
	mvaTree[systIn]->Branch("zLep2Index",&zLep2Index,"zLep2Index/I");
	mvaTree[systIn]->Branch("wLepIndex",&wLepIndex,"wLepIndex/I");
	mvaTree[systIn]->Branch("jetInd",jetInd,"jetInd[15]/I");
	mvaTree[systIn]->Branch("bJetInd",bJetInd,"jetInd[10]/I");

	if (systIn > 0) systMask = systMask << 1;
      }
      std::cout <<std::endl;
    }
    /*    else{
      event->fChain->SetBranchStatus("*",0); //Should disable most branches.
      setBranchStatusAll(event->fChain,dataset->isMC(),dataset->getTriggerFlag());
      }*/

    int numberOfEvents = datasetChain->GetEntries();
    if (nEvents && nEvents < numberOfEvents) numberOfEvents = nEvents;
    //    datasetChain->Draw("numElePF2PAT","numMuonPF2PAT > 2");
    //    TH1F * htemp = (TH1F*)gPad->GetPrimitive("htemp");
    //    htemp->SaveAs("tempCanvas.png");
    int foundEvents = 0;
    for (int i = 0; i < numberOfEvents; i++){
      if (i % 500 < 0.01) std::cerr << i << " (" << 100*float(i)/numberOfEvents << "%) with " << event->numElePF2PAT << " electrons. Found " << (synchCutFlow?cutObj->numFound():foundEvents) << " events.\r";
      event->GetEntry(i);
      //Do the systematics indicated by the systematic flag, oooor just do data if that's your thing. Whatevs.
      int systMask = 1;
      for (unsigned int systInd = 0; systInd < systNames.size(); systInd++){
	if (!dataset->isMC() && systInd > 0) break;
	//	std::cout << systInd << " " << systMask << std::endl;
	if (systInd > 0 && !(systMask & systToRun)) {
	  if (systInd > 0) systMask = systMask << 1;
	  continue;
	}
	eventWeight = event->getEventWeight(i);
	//apply trigger weights here.
	if (dataset->isMC()){
	  float pileupWeight = puReweight->GetBinContent(puReweight->GetXaxis()->FindBin(event->numVert));
	  if (systMask == 64) pileupWeight = puSystUp->GetBinContent(puSystUp->GetXaxis()->FindBin(event->numVert));
	  if (systMask == 128) pileupWeight = puSystDown->GetBinContent(puSystDown->GetXaxis()->FindBin(event->numVert));
	  eventWeight *= pileupWeight;
	  if (channel == "eee"){
	    float twgt = 0.9975;
	    if (systInd > 0 && (systMask == 1)) twgt += 0.0455;
	    if (systInd > 0 && (systMask == 2)) twgt -= 0.0354;
	    eventWeight *= twgt;
	  }
	  else if (channel == "eemu"){
	    float twgt = 0.9451;
	    if (systInd > 0 && (systMask == 1)) twgt += 0.0394;
	    if (systInd > 0 && (systMask == 2)) twgt -= 0.0408;
	    eventWeight *= twgt;
	  }
	  if (channel == "emumu"){
	    float twgt = 0.9001;
	    if (systInd > 0 && (systMask == 1)) twgt += 0.0565;
	    if (systInd > 0 && (systMask == 2)) twgt -= 0.0422;
	    eventWeight *= twgt;
	  }
	  if (channel == "mumumu"){
	    float twgt = 0.9871;
	    if (systInd > 0 && (systMask == 1)) twgt += 0.0242;
	    if (systInd > 0 && (systMask == 2)) twgt -= 0.0212;
	    eventWeight *= twgt;
	  }
	}

	if (infoDump) eventWeight = 1;
	if (readEventList) {
	  bool tempBool = false;
	  for (unsigned int i = 0; i < eventNumbers.size(); i++){
	    if (eventNumbers[i] == event->eventNum) {
	      tempBool = true;
	      break;
	    }
	  }
	  if (!tempBool) continue;
	  std::cout << event->eventNum << " " << event->eventRun << " " << event->eventLumiblock << " " << datasetChain->GetFile()->GetName() << std::endl;
	  cutObj->dumpLooseLepInfo(event);
	  cutObj->dumpLeptonInfo(event);
	
	}
	eventWeight*=datasetWeight;
	if (!cutObj->makeCuts(event,&eventWeight,plotsMap[dataset->getFillHisto()+systNames[systInd]],cutFlowMap[dataset->getFillHisto()+systNames[systInd]],systInd?systMask:systInd)) {
	  if (systInd) systMask = systMask << 1;
	  continue;
	}
	//      if (synchCutFlow){
	//	std::cout << event->eventNum << " " << event->eventRun << " " << event->eventLumiblock << " " << std::endl;
	//}
	if (makeMVATree){
	  zLep1Index = event->zPairIndex.first;
	  zLep2Index = event->zPairIndex.second;
	  wLepIndex = event->wLepIndex;
	  for (unsigned int jetIndexIt = 0; jetIndexIt < 15; jetIndexIt++){
	    if (jetIndexIt < event->jetIndex.size()) jetInd[jetIndexIt] = event->jetIndex[jetIndexIt];
	    else jetInd[jetIndexIt] = -1;
	  }
	  for (unsigned int bJetIt = 0; bJetIt < 10; bJetIt++){
	    if (bJetIt < event->bTagIndex.size()) bJetInd[bJetIt] = event->bTagIndex[bJetIt];
	    else bJetInd[bJetIt] = -1;
	  }
	  mvaTree[systInd]->Fill();
	  
	}

	foundEvents++;
	if (systInd > 0) systMask = systMask << 1;
      }// End systematics loop.
    } //end event loop

    //If we're making post lepSel skims save the tree here
    if (makePostLepTree){
      TFile outFile(("skims/"+dataset->name() + postfix + (invertIsoCut?"invIso":"") + "SmallSkim.root").c_str(),"RECREATE");
      outFile.cd();
      std::cout << "\nPrinting some info on the tree " <<dataset->name() << " " << cloneTree->GetEntries() << std::endl;
      std::cout << "But there were :" <<  datasetChain->GetEntries() << " entries in the original tree" << std::endl;
      cloneTree->Write();
      //If we're doing b-tag efficiencies, let's save them here.
      if (makeBTagEffPlots){
	for (int unsigned i = 0; i < bTagEffPlots.size(); i++){
	  bTagEffPlots[i]->Write();
	}
      }
      outFile.Write();
      outFile.Close();
      delete cloneTree;

      //If we have any events in the second tree:
      if (cloneTree2->GetEntriesFast() > 0){
	TFile outFile1(("skims/"+dataset->name() + postfix + (invertIsoCut?"invIso":"") + "SmallSkim1.root").c_str(),"RECREATE");
	outFile1.cd();
	cloneTree2->Write();
	outFile1.Write();
	outFile1.Close();
      }
      delete cloneTree2;
    }


    
    //Save mva outputs
    if (makeMVATree){
      TFile mvaOutFile(("mvaTest/" + dataset->name() + postfix + (invertIsoCut?"invIso":"")  +  "mvaOut.root").c_str(),"RECREATE");
      mvaOutFile.cd();
      std::cout << std::endl;
      int systMask = 1;
      std::cout << "Saving Systematics: ";
      for (unsigned int systInd = 0; systInd < systNames.size(); systInd++){
	if (systInd > 0 && !(systToRun & systMask)){
	  systMask = systMask << 1;
	  continue;
	}
	std::cout << systNames[systInd] << ": " << mvaTree[systInd]->GetEntriesFast() << " " << std::flush;
	mvaTree[systInd]->Write();
	if (systInd > 0) systMask = systMask << 1;
	if (!dataset->isMC()) break;
      }
      std::cout << std::endl;
      //Save the efficiency plots for b-tagging here if we're doing that.
      if (makeBTagEffPlots){
	for (int unsigned i = 0; i < bTagEffPlots.size(); i++){
	  bTagEffPlots[i]->Write();
	}
      }
      mvaOutFile.Write();
      mvaOutFile.Close();
      for (unsigned int i = 0; i < mvaTree.size(); i++){
	delete mvaTree[i];
      }
    }
    if (infoDump){
      std::cout << "In dataset " << dataset->getFillHisto() << " the cut flow looks like:" << std::endl;
      for (int i = 0; i < cutFlowMap[dataset->getFillHisto()]->GetNbinsX(); i++){
	std::cout << stageNames[i] << "\t" << cutFlowMap[dataset->getFillHisto()]->GetBinContent(i+1) << std::endl;
      }
    }
    std::cerr << "\nFound " << foundEvents << " in " << dataset->name() << std::endl;
    //Delete plots from out btag vector. Avoid memory leaks, kids.
    if (makeBTagEffPlots){
      for (int unsigned i = 0; i < bTagEffPlots.size(); i++){
	delete bTagEffPlots[i];
      }
    }
    //datasetChain->MakeClass("AnalysisEvent");
    delete datasetChain;
  } //end dataset loop

  //Save all plot objects. For testing purposes.
  
  //Now test out the histogram plotter class I just wrote.
  //Make the plotting object.
  if (plots||infoDump){
    HistogramPlotter plotObj = HistogramPlotter(legOrder,plotOrder,datasetInfos);
    plotObj.setLabelOne("CMS Preliminary");
    plotObj.setLabelTwo("Some amount of lumi");
    plotObj.setPostfix(postfix);
    plotObj.setOutputFolder(outFolder);

    if (plots)
      plotObj.plotHistos(plotsMap);
  
    
    std::vector<std::string> cutFlowLabels (4);
    cutFlowLabels = {"lepSel","zMass","jetSel","bTag"};
    //std::cout << cutFlowMap << std::endl;
    plotObj.makePlot(cutFlowMap,"cutFlow",cutFlowLabels);
  }
  if (synchCutFlow){
    cutObj->getSynchCutFlow();
  }

  /*  for (std::vector<Dataset>::iterator dataset = datasets.begin(); dataset!=datasets.end(); ++dataset){
    for (unsigned int j = 0; j < stageNames.size(); j++){
    plotsMap[dataset->getFillHisto()][stageNames[j]]->saveAllPlots();
    }
    cutFlowMap[dataset->getFillHisto()]->SaveAs(("plots/"+dataset->name()+"_cutFlow.root").c_str());    
    cutFlowMap[dataset->getFillHisto()]->Draw();
    cutFlowMap[dataset->getFillHisto()]->SaveAs(("plots/"+dataset->name()+"_cutFlow.png").c_str());
    }*/

  //Delete all the plot objects.

  std::cerr << "Gets to the delete bit" << std::endl;
  if (plots || infoDump){
    for (std::vector<Dataset>::iterator dataset = datasets.begin(); dataset!=datasets.end(); ++dataset){
      if (cutFlowMap.find(dataset->getFillHisto()) == cutFlowMap.end()) continue;
      delete cutFlowMap[dataset->getFillHisto()];
      if (!plots) continue;
      for (unsigned int j = 0; j < stageNames.size(); j++){
	int systMask = 1;
	for (unsigned int systInd = 0; systInd < systNames.size(); systInd++){
	  if (systInd > 0 && !(systInd & systMask)) {
	    systMask = systMask << 1;
	    continue;
	  }
	  delete plotsMap[dataset->getFillHisto()+systNames[systInd]][stageNames[j]];
	  if (systInd > 0) systMask = systMask << 1;
	}
      }
    }

  }
  delete cutConfName;
  delete plotConfName;

  
  std::cerr  << "But not past it" << std::endl;
}
