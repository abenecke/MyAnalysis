#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/Utils.h>

#include <UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimePreSelections.h>
#include <UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeSelections.h>
#include <UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeHists.h>

using namespace uhh2examples;
using namespace uhh2;

class ZPrimeTotTPrimePreSelectionModule: public uhh2::AnalysisModule {

public:
  explicit ZPrimeTotTPrimePreSelectionModule(uhh2::Context& ctx);
  virtual bool process(uhh2::Event&) override;

private:
  std::string channel_;

  // cleaners
  std::unique_ptr<MuonCleaner>     muo_cleaner;
  std::unique_ptr<ElectronCleaner> ele_cleaner;

  std::unique_ptr<JetCorrector>     jet_corrector;
  std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
  std::unique_ptr<JetCleaner>       jet_cleaner;
  std::unique_ptr<JetResolutionSmearer> jetER_smearer;

  std::unique_ptr<JetCleaner>                topjet_IDcleaner;
  std::unique_ptr<TopJetCorrector>           topjet_corrector;
  // std::unique_ptr<TopJetLeptonDeltaRCleaner> topjetlepton_cleaner;
  std::unique_ptr<TopJetCleaner>             topjet_cleaner;


  //selections
  std::unique_ptr<uhh2::Selection> muo1_sel;
  std::unique_ptr<uhh2::Selection> ele1_sel;
  std::unique_ptr<uhh2::Selection> jet2_sel;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  std::unique_ptr<uhh2::Selection> genmttbar_sel;

  //histograms
  std::unique_ptr<uhh2::Hists> input_h_event;
  std::unique_ptr<uhh2::Hists> input_h_muo;
  std::unique_ptr<uhh2::Hists> input_h_ele;
  std::unique_ptr<uhh2::Hists> input_h_jet;
  std::unique_ptr<Hists> input_h_eff;


  std::unique_ptr<uhh2::Hists> cleaner_h_event;
  std::unique_ptr<uhh2::Hists> cleaner_h_muo;
  std::unique_ptr<uhh2::Hists> cleaner_h_ele;
  std::unique_ptr<uhh2::Hists> cleaner_h_jet;
  std::unique_ptr<Hists> cleaner_h_eff;

  std::unique_ptr<uhh2::Hists> lepton_h_event;
  std::unique_ptr<uhh2::Hists> lepton_h_muo;
  std::unique_ptr<uhh2::Hists> lepton_h_ele;
  std::unique_ptr<uhh2::Hists> lepton_h_jet;
  std::unique_ptr<Hists> lepton_h_eff;

  std::unique_ptr<uhh2::Hists> output_h_event;
  std::unique_ptr<uhh2::Hists> output_h_muo;
  std::unique_ptr<uhh2::Hists> output_h_ele;
  std::unique_ptr<uhh2::Hists> output_h_jet;
  std::unique_ptr<Hists> output_h_eff;

  std::string filename;
 
};

ZPrimeTotTPrimePreSelectionModule::ZPrimeTotTPrimePreSelectionModule(uhh2::Context& ctx){

  const std::string ttbar_gen_label ("ttbargen");

 
  if(ctx.get("dataset_version") == "TTbarAll"){ genmttbar_sel.reset(new GenMttbarCut(ctx, 0., 700., ttbar_gen_label));}
 


  const bool isMC = (ctx.get("dataset_type") == "MC");
  channel_ = ctx.get("channel", "lepton");
  if(channel_!="muon" && channel_!="electron" && channel_!="lepton")
    throw std::runtime_error("undefined argument for 'channel' key in xml file (must be 'muon', 'electron' or 'lepton'): "+channel_);


  // set up object cleaners
  muo_cleaner.reset(new MuonCleaner (AndId<Muon> (PtEtaCut (15., 2.5), MuonIDMedium())));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(PtEtaSCCut(20., 2.5), ElectronID_MVAnotrig_Spring15_25ns_loose)));

  std::vector<std::string> JEC_AK4, JEC_AK8;
  if(isMC){

    JEC_AK4 = JERFiles::Summer15_25ns_L123_AK4PFchs_MC;
    JEC_AK8 = JERFiles::Summer15_25ns_L123_AK8PFchs_MC;
  }
  else {

    JEC_AK4 = JERFiles::Summer15_25ns_L123_AK4PFchs_DATA;
    JEC_AK8 = JERFiles::Summer15_25ns_L123_AK8PFchs_DATA;
  }

  jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
  jetlepton_cleaner.reset(new JetLeptonCleaner(ctx,JEC_AK4));
  jetER_smearer.reset(new JetResolutionSmearer(ctx));
  jetlepton_cleaner->set_drmax(.4);
  jet_cleaner.reset(new JetCleaner(ctx,15., 2.5));

  topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
  topjet_cleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.5))));

  // set up selections
  muo1_sel.reset(new NMuonSelection(1)); // at least 1 muon
  ele1_sel.reset(new NElectronSelection(1)); // at least 1 electron
  jet2_sel.reset(new NJetSelection(2)); // at least 2 jets

  // set up histograms
  input_h_event.reset(new EventHists   (ctx, "input_Event"));
  input_h_muo.reset(new MuonHists (ctx, "input_Muons"));
  input_h_ele.reset(new ElectronHists(ctx, "input_Electrons"));
  input_h_jet.reset(new JetHists     (ctx, "input_Jets"));
  input_h_eff.reset(new ZPrimeTotTPrimeHists(ctx, "input_eff"));

  cleaner_h_event.reset(new EventHists   (ctx, "cleaner_Event"));
  cleaner_h_muo.reset(new MuonHists (ctx, "cleaner_Muons"));
  cleaner_h_ele.reset(new ElectronHists(ctx, "cleaner_Electrons"));
  cleaner_h_jet.reset(new JetHists     (ctx, "cleaner_Jets"));
  cleaner_h_eff.reset(new ZPrimeTotTPrimeHists(ctx, "cleaner_eff"));

  lepton_h_event.reset(new EventHists   (ctx, "lepton_Event"));
  lepton_h_muo.reset(new MuonHists (ctx, "lepton_Muons"));
  lepton_h_ele.reset(new ElectronHists(ctx, "lepton_Electrons"));
  lepton_h_jet.reset(new JetHists     (ctx, "lepton_Jets"));
  lepton_h_eff.reset(new ZPrimeTotTPrimeHists(ctx, "lepton_eff"));

  output_h_event.reset(new EventHists   (ctx, "output_Event"));
  output_h_muo.reset(new MuonHists (ctx, "output_Muons"));
  output_h_ele.reset(new ElectronHists(ctx, "output_Electrons"));
  output_h_jet.reset(new JetHists     (ctx, "output_Jets"));
  output_h_eff.reset(new ZPrimeTotTPrimeHists(ctx, "output_eff"));
  
  filename =  ctx.get("dataset_version");

}

bool ZPrimeTotTPrimePreSelectionModule::process(Event & event) {

  if(filename == "TTBarAll"){
    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;
  }

  // dump input content
  input_h_event ->fill(event);
  input_h_muo ->fill(event);
  input_h_ele   ->fill(event);
  input_h_jet   ->fill(event);
  input_h_eff ->fill(event);

  // LEPTON CLEANING
  muo_cleaner->process(event);
  ele_cleaner->process(event);

  // keep Jets *before cleaning* to store them in the ntuple if event is accepted
  std::unique_ptr< std::vector<Jet> >    uncleaned_jets   (new std::vector<Jet>   (*event.jets));
  std::unique_ptr< std::vector<TopJet> > uncleaned_topjets(new std::vector<TopJet>(*event.topjets));

  // JET CLEANING
  jet_corrector->process(event);
  jetlepton_cleaner->process(event);
  jet_cleaner->process(event);

  topjet_corrector->process(event);
  //topjetlepton_cleaner->process(event);
  topjet_cleaner->process(event);

  //Lepton Pre-Selection
  bool pass_lep(false);
  if     (channel_ == "lepton")   pass_lep = (muo1_sel->passes(event) || ele1_sel->passes(event));
  else if(channel_ == "muon")     pass_lep = muo1_sel->passes(event);
  else if(channel_ == "electron") pass_lep = ele1_sel->passes(event);
  else throw std::runtime_error("undefined argument for 'channel' key in xml file (must be 'muon', 'electron' or 'lepton'): "+channel_);


  cleaner_h_event ->fill(event);
  cleaner_h_muo ->fill(event);
  cleaner_h_ele   ->fill(event);
  cleaner_h_jet   ->fill(event);
  cleaner_h_eff->fill(event);



  // exit if lepton selection fails, otherwise proceed to jet selection
  if(!pass_lep) return false;


  lepton_h_event ->fill(event);
  lepton_h_muo ->fill(event);
  lepton_h_ele   ->fill(event);
  lepton_h_jet   ->fill(event);
  lepton_h_eff   ->fill(event);


 // JET PRE-SELECTION
  const bool pass_jet = jet2_sel->passes(event);

  // exit if jet preselection fails
  if(!pass_jet) return false;


// dump output content
  output_h_event ->fill(event);
  output_h_muo ->fill(event);
  output_h_ele   ->fill(event);
  output_h_jet   ->fill(event);
  output_h_eff ->fill(event);
 

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZPrimeTotTPrimePreSelectionModule)
