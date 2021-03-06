#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include "UHH2/common/include/PrintingModules.h"
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>
#include "UHH2/common/include/CollectionProducer.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/PrimaryLepton.h"

#include <UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeSelections.h>
#include <UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeHists.h>
#include <UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeGenSelections.h>


#include "UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeReconstructionHypothesis.h"
#include "UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeReconstructionHypothesisDiscriminators.h"
#include "UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeReconstruction.h"
#include "UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeHypothesisHists.h" 

// #include <UHH2/common/include/HypothesisHists.h>
// #include <UHH2/common/include/TTbarReconstruction.h>
// #include <UHH2/common/include/ReconstructionHypothesis.h>
// #include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

using namespace uhh2examples;
using namespace uhh2;

class ZPrimeTotTPrimeSelectionModule : public uhh2::AnalysisModule {

 public:
  explicit ZPrimeTotTPrimeSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  enum lepton { muon, elec };
  lepton channel_;

  // cleaners
  std::unique_ptr<MuonCleaner>     muo_cleaner;
  std::unique_ptr<ElectronCleaner> ele_cleaner;
  std::unique_ptr<JetCleaner>      jet_IDcleaner;
  std::unique_ptr<JetCleaner>      jet_cleaner2;
  std::unique_ptr<JetCleaner>      jet_cleaner1;
  std::unique_ptr<JetCleaner>      topjet_IDcleaner;
  std::unique_ptr<TopJetCleaner>   topjet_cleaner;
  std::unique_ptr<TopJetCleaner>   toptag_cleaner;
  std::unique_ptr<TopJetCleaner>   higgstag_cleaner;
  std::unique_ptr<TopJetCleaner>   ZWtag_cleaner;
  std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
  std::unique_ptr<JetCleaner>  ak4_cleaner;
  std::vector<std::unique_ptr<AnalysisModule>> htcalc;

  // Data/MC scale factors
  std::unique_ptr<uhh2::AnalysisModule> pileup_SF;
  std::unique_ptr<uhh2::AnalysisModule> lumiweight;

  //Selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> lep1_sel; //  one lepton (comment out )
  //  std::unique_ptr<uhh2::Selection> jet1_sel;    // at least 1 AK4 jets
  std::unique_ptr<uhh2::Selection> TOPjet2_sel; // pT,1 > 250 GeV, pT,2 > 100 GeV
  std::unique_ptr<uhh2::Selection> TOPjet1_sel; // at least 2 jets
  std::unique_ptr<uhh2::Selection> chi2cut_sel; // chi2min <50

  std::unique_ptr<uhh2::Selection> twodcut_sel;// pt 20 rel 0.4
  std::unique_ptr<uhh2::Selection> reliso_sel; //relIso < 0.35


  //TOP TAGGER
  std::unique_ptr<Selection> toptag_sel; // at least one toptag
  uhh2::Event::Handle< std::vector<TopJet> > h_toptag;

  //HIGGS TAGGER
  std::unique_ptr<Selection> higgstag_sel;
  uhh2::Event::Handle< std::vector<TopJet> > h_higgstag;

  //Z/W TAGGER
  std::unique_ptr<Selection> ZWtag_sel;
  uhh2::Event::Handle< std::vector<TopJet> > h_ZWtag;

  // reconstruction ZPrime for Signal
  std::unique_ptr<uhh2::AnalysisModule> ZprimeTotTPrimeprod;
  std::unique_ptr<uhh2::AnalysisModule> reco_primlep;
  std::unique_ptr<uhh2::AnalysisModule> ZprimeTotTPrime_reco;
  std::unique_ptr<uhh2::AnalysisModule> ttbar_reco;
  std::unique_ptr<uhh2::AnalysisModule> ZprimeTotTPrime_chi;
  std::unique_ptr<uhh2::AnalysisModule> ttbar_chi;

  // reconstruction TTBar for Background
  std::unique_ptr<uhh2::Selection> genmttbar_sel;
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;

  
  ////////////////////HISTS///////////////////////////////////////
  //Input Hists
  std::unique_ptr<Hists> input_event_h;
  std::unique_ptr<Hists> input_lep_h;
  std::unique_ptr<Hists> input_eff_h;
  std::unique_ptr<Hists> input_jet_h; 
  std::unique_ptr<Hists> input_topjet_h;
  
  //Hists lep1
  std::unique_ptr<Hists> event_lep1_h;
  std::unique_ptr<Hists> topjet_lep1_h;
  std::unique_ptr<Hists> jet_lep1_h;
  std::unique_ptr<Hists> muon_lep1_h;
  std::unique_ptr<Hists> eff_lep1_h;
 
  //Hist Topjet2
  std::unique_ptr<Hists> eff_topjet2_h;
  std::unique_ptr<Hists> jet_topjet2_h;
  std::unique_ptr<Hists> muon_topjet2_h;
  std::unique_ptr<Hists> event_topjet2_h;
  std::unique_ptr<Hists> topjet_topjet2_h;


  // //Jet 2 Hists
  // std::unique_ptr<Hists> jet2_h;
  // std::unique_ptr<Hists> eff_jet2_h;
  // std::unique_ptr<Hists> Topjet_jet2_h;
  // std::unique_ptr<Hists> muon_jet2_h;
  // std::unique_ptr<TopJetHists> higgstag_jet2_h;
  // std::unique_ptr<TopJetHists> zwtag_jet2_h;
  // std::unique_ptr<Hists> event_jet_h;

  //reliso Hists
  std::unique_ptr<Hists> eff_reliso_h;
  std::unique_ptr<Hists> jet_reliso_h;
  std::unique_ptr<Hists> topjet_reliso_h;
  std::unique_ptr<Hists> muon_reliso_h;
 std::unique_ptr<Hists> event_reliso_h;

  //2DCut Hists
  std::unique_ptr<Hists> eff_twodcut_h;
  std::unique_ptr<Hists> jet_twodcut_h;
  std::unique_ptr<Hists> topjet_twodcut_h;
  std::unique_ptr<Hists> muon_twodcut_h;
 std::unique_ptr<Hists> event_twodcut_h;
   
//Higgstag Hists
  std::unique_ptr<TopJetHists> input_higgstag_h;
  std::unique_ptr<TopJetHists> output_higgstag_h;

  std::unique_ptr<Hists> topjet_higgstag_h;
  std::unique_ptr<Hists> eff_higgstag_h;
  std::unique_ptr<Hists> jet_higgstag_h;
  std::unique_ptr<Hists> muon_higgstag_h;
  std::unique_ptr<Hists> event_higgstag_h;

  //ZWTagg Hists
  std::unique_ptr<TopJetHists> input_zwtag_h;
  std::unique_ptr<TopJetHists> output_zwtag_h;

  std::unique_ptr<Hists> topjet_zwtag_h;
  std::unique_ptr<Hists> eff_zwtag_h;
  std::unique_ptr<Hists> jet_zwtag_h;
  std::unique_ptr<Hists> muon_zwtag_h;
  std::unique_ptr<Hists> event_zwtag_h;

  //Higgstag || ZWtag Hists
  std::unique_ptr<Hists> output_combined_h;

  //Toptag Hists
  std::unique_ptr<TopJetHists> input_toptag_h;
  std::unique_ptr<TopJetHists> output_toptag_h;

  std::unique_ptr<Hists> topjet_toptag_h;
  std::unique_ptr<Hists> eff_toptag_h;
  std::unique_ptr<Hists> muon_toptag_h;
  std::unique_ptr<Hists> jet_toptag_h;
  std::unique_ptr<Hists> event_toptag_h;

  std::unique_ptr<TopJetHists> higgs_top_topjet_toptag_h;
  std::unique_ptr<TopJetHists> zw_top_topjet_toptag_h;
  std::unique_ptr<TopJetHists> higgs_notop_topjet_toptag_h;
  std::unique_ptr<TopJetHists> zw_notop_topjet_toptag_h;

  //Hist Tagger
  std::unique_ptr<Hists> topjet_tagger_h;
  std::unique_ptr<Hists> eff_tagger_h;
  std::unique_ptr<Hists> jet_tagger_h;
  std::unique_ptr<Hists> muon_tagger_h;
  std::unique_ptr<Hists> event_tagger_h;

  std::unique_ptr<TopJetHists> higgs_top_topjet_tagger_h;
  std::unique_ptr<TopJetHists> zw_top_topjet_tagger_h;
  std::unique_ptr<TopJetHists> higgs_notop_topjet_tagger_h;
  std::unique_ptr<TopJetHists> zw_notop_topjet_tagger_h;

  //Hist Reco
  std::unique_ptr<Hists> chi2min_reco_h;
  std::unique_ptr<Hists> eff_reco_h;
  std::unique_ptr<Hists> jet_reco_h;
  std::unique_ptr<Hists> muon_reco_h;
  std::unique_ptr<Hists> topjet_reco_h;
  std::unique_ptr<Hists> event_reco_h;

 std::unique_ptr<Hists> chi2min_test_h;
  std::unique_ptr<Hists> eff_test_h;
  std::unique_ptr<Hists> jet_test_h;
  std::unique_ptr<Hists> muon_test_h;
  std::unique_ptr<Hists> topjet_test_h;
  std::unique_ptr<Hists> event_test_h;

  std::unique_ptr<TopJetHists> higgs_top_topjet_reco_h;
  std::unique_ptr<TopJetHists> zw_top_topjet_reco_h;
  std::unique_ptr<TopJetHists> higgs_notop_topjet_reco_h;
  std::unique_ptr<TopJetHists> zw_notop_topjet_reco_h;
  std::unique_ptr<Hists> higgs_top_chi2min_reco_h;
  std::unique_ptr<Hists> zw_top_chi2min_reco_h;
  std::unique_ptr<Hists> higgs_notop_chi2min_reco_h;
  std::unique_ptr<Hists> zw_notop_chi2min_reco_h;


  //Hist Chi2cut
  std::unique_ptr<Hists> chi2min_chi2cut_h;
  std::unique_ptr<Hists> eff_chi2cut_h;
  std::unique_ptr<Hists> jet_chi2cut_h;
  std::unique_ptr<Hists> muon_chi2cut_h;
  std::unique_ptr<Hists> topjet_chi2cut_h;
  std::unique_ptr<Hists> event_chi2cut_h;

  std::unique_ptr<TopJetHists> higgs_top_topjet_chi2cut_h;
  std::unique_ptr<TopJetHists> zw_top_topjet_chi2cut_h;
  std::unique_ptr<TopJetHists> higgs_notop_topjet_chi2cut_h;
  std::unique_ptr<TopJetHists> zw_notop_topjet_chi2cut_h;
  std::unique_ptr<Hists> higgs_top_chi2min_chi2cut_h;
  std::unique_ptr<Hists> zw_top_chi2min_chi2cut_h;
  std::unique_ptr<Hists> higgs_notop_chi2min_chi2cut_h;
  std::unique_ptr<Hists> zw_notop_chi2min_chi2cut_h;

  //leptop
  std::unique_ptr<Hists> topjet_leptop_h;
  std::unique_ptr<Hists>   eff_leptop_h;
  std::unique_ptr<Hists>   jet_leptop_h;
  std::unique_ptr<Hists>   muon_leptop_h;
  std::unique_ptr<Hists>   chi2min_leptop_h;
  std::unique_ptr<Hists> event_leptop_h;

  std::unique_ptr<TopJetHists> higgs_top_topjet_leptop_h;
  std::unique_ptr<TopJetHists> zw_top_topjet_leptop_h;
  std::unique_ptr<TopJetHists> higgs_notop_topjet_leptop_h;
  std::unique_ptr<TopJetHists> zw_notop_topjet_leptop_h;
  std::unique_ptr<Hists> higgs_top_chi2min_leptop_h;
  std::unique_ptr<Hists> zw_top_chi2min_leptop_h;
  std::unique_ptr<Hists> higgs_notop_chi2min_leptop_h;
  std::unique_ptr<Hists> zw_notop_chi2min_leptop_h;

  std::unique_ptr<Hists>   chi2min_met_h;

 //toppt
  std::unique_ptr<Hists> topjet_toppt_h;
  std::unique_ptr<Hists>   eff_toppt_h;
  std::unique_ptr<Hists>   jet_toppt_h;
  std::unique_ptr<Hists>   muon_toppt_h;
  std::unique_ptr<Hists>   chi2min_toppt_h;
  std::unique_ptr<Hists> event_toppt_h;

  std::unique_ptr<TopJetHists> higgs_top_topjet_toppt_h;
  std::unique_ptr<TopJetHists> zw_top_topjet_toppt_h;
  std::unique_ptr<TopJetHists> higgs_notop_topjet_toppt_h;
  std::unique_ptr<TopJetHists> zw_notop_topjet_toppt_h;
  std::unique_ptr<Hists> higgs_top_chi2min_toppt_h;
  std::unique_ptr<Hists> zw_top_chi2min_toppt_h;
  std::unique_ptr<Hists> higgs_notop_chi2min_toppt_h;
  std::unique_ptr<Hists> zw_notop_chi2min_toppt_h;

  //general
  std::string filename;
  uhh2::Event::Handle<std::vector<ZPrimeTotTPrimeReconstructionHypothesis> > h_ZprimeTotTPrime_hyps;
  std::unique_ptr<AnalysisModule> printer;
};


ZPrimeTotTPrimeSelectionModule::ZPrimeTotTPrimeSelectionModule(uhh2::Context& ctx){


  //choose channel
  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("ZprimeSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

  const bool isMC = (ctx.get("dataset_type") == "MC");
  //// COMMON MODULES
  if(isMC){ pileup_SF.reset(new MCPileupReweight(ctx)); lumiweight.reset(new MCLumiWeight(ctx));}
  else     lumi_sel.reset(new LumiSelection(ctx));

  std::vector<std::string> JEC_AK4, JEC_AK8;
  if(isMC){

    JEC_AK4 = JERFiles::Summer15_25ns_L123_AK4PFchs_MC;
    JEC_AK8 = JERFiles::Summer15_25ns_L123_AK8PFchs_MC;
  }
  else {

    JEC_AK4 = JERFiles::Summer15_25ns_L123_AK4PFchs_DATA;
    JEC_AK8 = JERFiles::Summer15_25ns_L123_AK8PFchs_DATA;
  }

  //// OBJ CLEANING
  muo_cleaner.reset(new MuonCleaner    (AndId<Muon>    (PtEtaCut  (50., 2.1), MuonIDMedium())));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(PtEtaSCCut(50., 2.5), ElectronID_MVAnotrig_Spring15_25ns_loose)));

  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));
  jet_IDcleaner.reset(new JetCleaner(ctx,jetID));
  jet_cleaner2.reset(new JetCleaner(ctx,15., 2.5));
  jet_cleaner1.reset(new JetCleaner(ctx,30., 2.5));
  jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JEC_AK4));
  jetlepton_cleaner->set_drmax(.4);
  ak4_cleaner.reset(new JetCleaner(ctx,JetId(ZPrimeTotTPrimeAK4cleaner(1.2))));
  htcalc.push_back(std::unique_ptr<AnalysisModule>(new HTCalculator(ctx)));
  htcalc.push_back(std::unique_ptr<AnalysisModule>(new PrimaryLepton(ctx)));
  htcalc.push_back(std::unique_ptr<AnalysisModule>(new HTlepCalculator(ctx)));
  // SELECTIONS
  //jet1_sel.reset(new NJetSelection(1,-1, JetId(PtEtaCut(0.,2.5))));
  
  // TOPJET SELECTIONS
  TOPjet1_sel.reset(new NTopJetSelection(2, -1, TopJetId(PtEtaCut( 50., 2.5))));
  TOPjet2_sel.reset(new ZPrimeTotTPrimeNTopJetCut(2,-1,250,100, 2.5));
 
  //2D Cut
  twodcut_sel.reset(new TwoDCut(.4, 25.));
  reliso_sel.reset(new ZPrimeTotTPrimeRelIsoCut(0.15));

  //TOP TAGGER
  const TopJetId topjetID = AndId<TopJet>(Type2TopTag(150,240,Type2TopTag::MassType::groomed), Tau32(0.6));
  toptag_sel.reset(new NTopJetSelection(1, -1, topjetID));
  toptag_cleaner.reset(new TopJetCleaner(ctx,topjetID));


  //Higgs TAGGER
   const TopJetId higgsjetID = AndId<TopJet>(HiggsTag(100,150), Tau21(1));
  higgstag_sel.reset(new NTopJetSelection(1, -1, higgsjetID));
  higgstag_cleaner.reset(new TopJetCleaner(ctx,higgsjetID));

  //W/Z TAGGER
  const TopJetId ZWjetID = AndId<TopJet>(Type2TopTag(60,115,Type2TopTag::MassType::groomed), Tau21(0.6));
  ZWtag_sel.reset(new NTopJetSelection(1, -1, ZWjetID));
  ZWtag_cleaner.reset(new TopJetCleaner(ctx,ZWjetID));


  //LEPTONSELECTION
  lep1_sel.reset(new uhh2::AndSelection(ctx));

  if(channel_ == muon){

    lep1_sel->add<NMuonSelection>    ("muoN == 1", 1, 1);
    lep1_sel->add<NElectronSelection>("eleN == 0", 0, 0);
  }
  else if(channel_ == elec){

    lep1_sel->add<NMuonSelection>    ("muoN == 0", 0, 0);
    lep1_sel->add<NElectronSelection>("eleN == 1", 1, 1);
  }


  /* KINEMATICAL RECO */
  const std::string ZprimeTotTPrime_gen_label ("zprimegen");
  const std::string ZprimeTotTPrime_hyps_label("ZPrimeTotTPrimeReconstruction");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ZprimeTotTPrime_chi2_label("Chi2");
  const std::string ttbar_chi2_label("Chi2");
  const std::string ttbar_gen_label ("ttbargen");

  reco_primlep.reset(new PrimaryLepton(ctx));

  ZprimeTotTPrime_reco.reset(new ZPrimeTotTPrimeReconstruction(ctx, NeutrinoReconstruction, ZprimeTotTPrime_hyps_label));
  ZprimeTotTPrime_chi.reset(new ZPrimeTotTPrimeChi2Discriminator(ctx, ZprimeTotTPrime_hyps_label));
  ZprimeTotTPrimeprod.reset(new ZPrimeGenProducer(ctx, ZprimeTotTPrime_gen_label, false));
  h_ZprimeTotTPrime_hyps = ctx.get_handle<std::vector<ZPrimeTotTPrimeReconstructionHypothesis>>(ZprimeTotTPrime_hyps_label);
  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));


  chi2cut_sel.reset(new ZPrimeTotTPrimeChiCut( ctx,50,ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));

  // Select of the inclusiv ttbar sample only events from 0 to 700 GeV
  if(ctx.get("dataset_version") == "TTbarAll"){ genmttbar_sel.reset(new GenMttbarCut(ctx, 0., 700., ttbar_gen_label));}
  else                                                    genmttbar_sel.reset(new uhh2::AndSelection(ctx));


  // Hists Input
  input_event_h.reset(new EventHists(ctx, "input"));
  input_lep_h.reset(new MuonHists(ctx, "input_Lep"));
  input_jet_h.reset(new JetHists (ctx, "input_Jet"));
  input_topjet_h.reset(new TopJetHists (ctx, "input_TopJet"));
  input_eff_h.reset(new ZPrimeTotTPrimeHists(ctx, "input_eff"));

  // Hists lep1
  topjet_lep1_h.reset(new TopJetHists(ctx, "topjet_lep1"));
  event_lep1_h.reset(new EventHists(ctx, "event_lep1"));
  muon_lep1_h.reset(new MuonHists(ctx, "muon_lep1"));
  jet_lep1_h.reset(new JetHists(ctx, "jet_lep1"));
  eff_lep1_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_lep1"));

  //Hists topjet2
  topjet_topjet2_h.reset(new TopJetHists(ctx, "topjet_topjet2"));
  eff_topjet2_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_topjet2"));
  jet_topjet2_h.reset(new JetHists(ctx, "jet_topjet2"));
  muon_topjet2_h.reset(new MuonHists(ctx, "muon_topjet2"));
  event_topjet2_h.reset(new EventHists(ctx, "event_topjet2"));

 
 //  //Hist jet2
 //  jet2_h.reset(new JetHists(ctx, "jet2"));
 //  eff_jet2_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_jet2"));
 //  Topjet_jet2_h.reset(new TopJetHists(ctx, "topjet_jet2"));
 //  muon_jet2_h.reset(new MuonHists(ctx, "muon_jet2"));
 //  higgstag_jet2_h.reset(new TopJetHists(ctx, "higgstag_jet2"));
 //  higgstag_jet2_h->set_TopJetId(higgsjetID);
 //  zwtag_jet2_h.reset(new TopJetHists(ctx, "zwtag_jet2"));
 //  zwtag_jet2_h->set_TopJetId(ZWjetID);
 // event_topjet2_h.reset(new EventHists(ctx, "event_jet2"));

  //Hist reliso
  topjet_reliso_h.reset(new TopJetHists(ctx, "topjet_reliso"));
  eff_reliso_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_reliso"));
  jet_reliso_h.reset(new JetHists(ctx, "jet_reliso"));
  muon_reliso_h.reset(new MuonHists(ctx, "muon_reliso"));
  event_reliso_h.reset(new EventHists(ctx, "event_reliso"));


  //Hist twodcut
  topjet_twodcut_h.reset(new TopJetHists(ctx, "topjet_twodcut"));
  eff_twodcut_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_twodcut"));
  jet_twodcut_h.reset(new JetHists(ctx, "jet_twodcut"));
  muon_twodcut_h.reset(new MuonHists(ctx, "muon_twodcut"));
  event_twodcut_h.reset(new EventHists(ctx, "event_twodcut"));

  //HIGGSTAG HISTS
  input_higgstag_h.reset(new TopJetHists(ctx, "input_higgstag"));
  output_higgstag_h.reset(new TopJetHists(ctx, "output_higgstag"));
  output_higgstag_h->set_TopJetId(higgsjetID);

  eff_higgstag_h.reset(new ZPrimeTotTPrimeHists(ctx,"eff_higgstag"));
  jet_higgstag_h.reset(new JetHists(ctx, "jet_higgstag"));
  muon_higgstag_h.reset(new MuonHists(ctx, "muon_higgstag"));
  event_higgstag_h.reset(new EventHists(ctx, "event_higgstag"));
  topjet_higgstag_h.reset(new TopJetHists(ctx, "topjet_higgstag"));
 
  //Z/W TAG HISTS
  input_zwtag_h.reset(new TopJetHists(ctx, "input_zwtag"));
  output_zwtag_h.reset(new TopJetHists(ctx, "output_zwtag"));
  output_zwtag_h->set_TopJetId(ZWjetID);

  eff_zwtag_h.reset(new ZPrimeTotTPrimeHists(ctx,"eff_zwtag"));
  jet_zwtag_h.reset(new JetHists(ctx, "jet_zwtag"));
  muon_zwtag_h.reset(new MuonHists(ctx, "muon_zwtag"));
  event_zwtag_h.reset(new EventHists(ctx, "event_zwtag"));
  topjet_zwtag_h.reset(new TopJetHists(ctx, "topjet_zwtag"));

  // Hists Toptag
  input_toptag_h.reset(new TopJetHists(ctx, "input_toptag"));
  output_toptag_h.reset(new TopJetHists(ctx, "output_toptag"));
  output_toptag_h->set_TopJetId(topjetID);

  eff_toptag_h.reset(new ZPrimeTotTPrimeHists(ctx,"eff_toptag"));
  jet_toptag_h.reset(new JetHists(ctx, "jet_toptag"));
  muon_toptag_h.reset(new MuonHists(ctx, "muon_toptag"));
  event_toptag_h.reset(new EventHists(ctx, "event_toptag"));
  topjet_toptag_h.reset(new TopJetHists(ctx, "topjet_toptag"));

  higgs_top_topjet_toptag_h.reset(new TopJetHists(ctx, "higgs_top_topjet_toptag"));
  higgs_notop_topjet_toptag_h.reset(new TopJetHists(ctx, "higgs_notop_topjet_toptag"));
  zw_top_topjet_toptag_h.reset(new TopJetHists(ctx, "zw_top_topjet_toptag"));
  zw_notop_topjet_toptag_h.reset(new TopJetHists(ctx, "zw_notop_topjet_toptag"));

  //Hists tagger
  eff_tagger_h.reset(new ZPrimeTotTPrimeHists(ctx,"eff_tagger"));
  jet_tagger_h.reset(new JetHists(ctx, "jet_tagger"));
  muon_tagger_h.reset(new MuonHists(ctx, "muon_tagger"));
  event_tagger_h.reset(new EventHists(ctx, "event_tagger"));
  topjet_tagger_h.reset(new TopJetHists(ctx, "topjet_tagger"));

  higgs_top_topjet_tagger_h.reset(new TopJetHists(ctx, "higgs_top_topjet_tagger"));
  higgs_notop_topjet_tagger_h.reset(new TopJetHists(ctx, "higgs_notop_topjet_tagger"));
  zw_top_topjet_tagger_h.reset(new TopJetHists(ctx, "zw_top_topjet_tagger"));
  zw_notop_topjet_tagger_h.reset(new TopJetHists(ctx, "zw_notop_topjet_tagger"));
 
  //Hists Reco
  topjet_reco_h.reset(new TopJetHists(ctx, "topjet_reco"));
  eff_reco_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_reco"));
  jet_reco_h.reset(new JetHists(ctx, "jet_reco"));
  muon_reco_h.reset(new MuonHists(ctx, "muon_reco"));
  event_reco_h.reset(new EventHists(ctx, "event_reco"));
  chi2min_reco_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "chi2min_reco",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label ));

 topjet_test_h.reset(new TopJetHists(ctx, "topjet_test"));
  eff_test_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_test"));
  jet_test_h.reset(new JetHists(ctx, "jet_test"));
  muon_test_h.reset(new MuonHists(ctx, "muon_test"));
  event_test_h.reset(new EventHists(ctx, "event_test"));
  chi2min_test_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "chi2min_test",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label ));

  higgs_top_topjet_reco_h.reset(new TopJetHists(ctx, "higgs_top_topjet_reco"));
  higgs_notop_topjet_reco_h.reset(new TopJetHists(ctx, "higgs_notop_topjet_reco"));
  zw_top_topjet_reco_h.reset(new TopJetHists(ctx, "zw_top_topjet_reco"));
  zw_notop_topjet_reco_h.reset(new TopJetHists(ctx, "zw_notop_topjet_reco"));

  higgs_top_chi2min_reco_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_top_chi2min_reco",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  higgs_notop_chi2min_reco_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_notop_chi2min_reco",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_top_chi2min_reco_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_top_chi2min_reco",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_notop_chi2min_reco_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_notop_chi2min_reco",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
 
 //Hists Chi2cut
  topjet_chi2cut_h.reset(new TopJetHists(ctx, "topjet_chi2cut"));
  eff_chi2cut_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_chi2cut"));
  jet_chi2cut_h.reset(new JetHists(ctx, "jet_chi2cut"));
  muon_chi2cut_h.reset(new MuonHists(ctx, "muon_chi2cut"));
  event_chi2cut_h.reset(new EventHists(ctx, "event_chi2cut"));
  chi2min_chi2cut_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "chi2min_chi2cut",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label ));

  higgs_top_topjet_chi2cut_h.reset(new TopJetHists(ctx, "higgs_top_topjet_chi2cut"));
  higgs_notop_topjet_chi2cut_h.reset(new TopJetHists(ctx, "higgs_notop_topjet_chi2cut"));
  zw_top_topjet_chi2cut_h.reset(new TopJetHists(ctx, "zw_top_topjet_chi2cut"));
  zw_notop_topjet_chi2cut_h.reset(new TopJetHists(ctx, "zw_notop_topjet_chi2cut"));

  higgs_top_chi2min_chi2cut_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_top_chi2min_chi2cut",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  higgs_notop_chi2min_chi2cut_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_notop_chi2min_chi2cut",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_top_chi2min_chi2cut_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_top_chi2min_chi2cut",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_notop_chi2min_chi2cut_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_notop_chi2min_chi2cut",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));

  //toplep
  topjet_leptop_h.reset(new TopJetHists(ctx, "topjet_leptop"));
  eff_leptop_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_leptop"));
  jet_leptop_h.reset(new JetHists(ctx, "jet_leptop"));
  muon_leptop_h.reset(new MuonHists(ctx, "muon_leptop"));
  event_leptop_h.reset(new EventHists(ctx, "event_leptop"));
  chi2min_leptop_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "chi2min_leptop",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label ));

  higgs_top_topjet_leptop_h.reset(new TopJetHists(ctx, "higgs_top_topjet_leptop"));
  higgs_notop_topjet_leptop_h.reset(new TopJetHists(ctx, "higgs_notop_topjet_leptop"));
  zw_top_topjet_leptop_h.reset(new TopJetHists(ctx, "zw_top_topjet_leptop"));
  zw_notop_topjet_leptop_h.reset(new TopJetHists(ctx, "zw_notop_topjet_leptop"));

  higgs_top_chi2min_leptop_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_top_chi2min_leptop",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  higgs_notop_chi2min_leptop_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_notop_chi2min_leptop",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_top_chi2min_leptop_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_top_chi2min_leptop",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_notop_chi2min_leptop_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_notop_chi2min_leptop",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));

  chi2min_met_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "chi2min_met",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label ));

  //toplep
  topjet_toppt_h.reset(new TopJetHists(ctx, "topjet_toppt"));
  eff_toppt_h.reset(new ZPrimeTotTPrimeHists(ctx, "eff_toppt"));
  jet_toppt_h.reset(new JetHists(ctx, "jet_toppt"));
  muon_toppt_h.reset(new MuonHists(ctx, "muon_toppt"));
  event_toppt_h.reset(new EventHists(ctx, "event_toppt"));
  chi2min_toppt_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "chi2min_toppt",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label ));

  higgs_top_topjet_toppt_h.reset(new TopJetHists(ctx, "higgs_top_topjet_toppt"));
  higgs_notop_topjet_toppt_h.reset(new TopJetHists(ctx, "higgs_notop_topjet_toppt"));
  zw_top_topjet_toppt_h.reset(new TopJetHists(ctx, "zw_top_topjet_toppt"));
  zw_notop_topjet_toppt_h.reset(new TopJetHists(ctx, "zw_notop_topjet_toppt"));

  higgs_top_chi2min_toppt_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_top_chi2min_toppt",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  higgs_notop_chi2min_toppt_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "higgs_notop_chi2min_toppt",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_top_chi2min_toppt_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_top_chi2min_toppt",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));
  zw_notop_chi2min_toppt_h.reset(new ZPrimeTotTPrimeHypothesisHists(ctx, "zw_notop_chi2min_toppt",ZprimeTotTPrime_hyps_label,ZprimeTotTPrime_chi2_label));


  //Higgstag || ZWTag
  output_combined_h.reset(new ZPrimeTotTPrimeHists(ctx, "output_combined"));
 

  //general
  filename =  ctx.get("dataset_version");
  h_toptag = ctx.declare_event_output< std::vector<TopJet> > ("TopTag");
  h_higgstag = ctx.declare_event_output< std::vector<TopJet> > ("HiggsTag");
  h_ZWtag = ctx.declare_event_output< std::vector<TopJet> > ("ZWTag");
  printer.reset(new GenParticlesPrinter(ctx));
 
}



bool ZPrimeTotTPrimeSelectionModule::process(uhh2::Event& event){
  
  std::cout<<"/////////////////////////////////////SelectionModule L:218 Am Anfang///////////////////////////////////////////////////////////////////////////////"<<std::endl;

  for (auto & mod : htcalc) {
      mod->process(event);
    }



  //Select of the inclusiv ttbar sample only events from 0 to 700 GeV
  if(filename  == "TTbarAll"){
    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;
  }

  //ZPrime Genrator Level
  if(filename.find("MC_ZPrime")!=std::string::npos){
    ZprimeTotTPrimeprod->process(event); 
  }

  std::cout<<"SelectionModule L:232 vor Input Histogrammen"<<std::endl;
  /////////////////////////////////////////////////////////// Input Histogramme ///////////////////////////////////////////////////////////////////////////////
 
  input_eff_h ->fill(event);
  input_event_h->fill(event);
  input_topjet_h->fill(event);
  input_jet_h->fill(event);
  input_lep_h->fill(event);
  /////////////////////////////////////////////////////////// Common Modules   ///////////////////////////////////////////////////////////////////////////////


  //common Modules
  /* luminosity sections from CMS golden-JSON file */
  if(event.isRealData && !lumi_sel->passes(event)) return false;
  /* pileup SF */
  if(!event.isRealData){ pileup_SF->process(event);lumiweight->process(event);}
  ////

  // OBJ CLEANING
  muo_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  ele_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  jet_IDcleaner->process(event);
  jetlepton_cleaner->process(event);
  jet_cleaner2->process(event); 
  
  sort_by_pt<Jet>(*event.jets);
  sort_by_pt<TopJet>(*event.topjets);



 std::cout<<"SelectionModule L:268 vor LeptonSelection"<<std::endl;
  /////////////////////////////////////////////////////////// LEPTON selection ///////////////////////////////////////////////////////////////////////////////
  const bool pass_lep1 = lep1_sel->passes(event);
  if(!pass_lep1) return false;
  muon_lep1_h->fill(event);
  eff_lep1_h ->fill(event);
  event_lep1_h->fill(event);
  eff_lep1_h->fill(event);
  topjet_lep1_h->fill(event);

  std::cout<<"SelectionModule L:268 vor TopJetSelection"<<std::endl;
  ////////////////////////////////////////////////////////// TopJET selection//////////////////////////////////////////////////////////////////////////////////

  const bool pass_Topjet1 = TOPjet1_sel->passes(event);
  if(!pass_Topjet1) return false;

  // PT Cuts 
  const bool pass_Topjet2 = TOPjet2_sel->passes(event);
  if(!pass_Topjet2) return false;
  topjet_topjet2_h->fill(event);
  eff_topjet2_h->fill(event);
  jet_topjet2_h->fill(event);
  muon_topjet2_h->fill(event);
  event_topjet2_h->fill(event);


  // std::cout<<"SelectionModule L:294 vor JetSelection"<<std::endl;  
  // ////////////////////////////////////////////////////////// JET selection//////////////////////////////////////////////////////////////////////////////////
  // const bool pass_jet1 = jet1_sel->passes(event);
  // if(!pass_jet1) return false;
  // jet2_h->fill(event);
  // eff_jet2_h->fill(event);
  // muon_jet2_h->fill(event);
  // Topjet_jet2_h->fill(event);
  // higgstag_jet2_h->fill(event);
  // zwtag_jet2_h->fill(event);
  //event_jet2_h->fill(event);

  std::cout<<"SelectionModule L:294 vor RelIso"<<std::endl;  
  ////////////////////////////////////////////////////////// Reliso //////////////////////////////////////////////////////////////////////////////////
  bool pass_reliso= reliso_sel->passes(event);
  if(pass_reliso){
    topjet_reliso_h->fill(event);
    eff_reliso_h->fill(event);
    jet_reliso_h->fill(event);
    muon_reliso_h->fill(event);
    event_reliso_h->fill(event);
  }

  std::cout<<"SelectionModule L:294 vor TwoDCut"<<std::endl;  
  ////////////////////////////////////////////////////////// TwoDCut //////////////////////////////////////////////////////////////////////////////////
  const bool pass_twodcut = twodcut_sel->passes(event);
  if(!pass_twodcut) return false;
  topjet_twodcut_h->fill(event);
  eff_twodcut_h->fill(event);
  jet_twodcut_h->fill(event);
  muon_twodcut_h->fill(event);


  jet_cleaner1->process(event);
  event_twodcut_h->fill(event);

  std::cout<<"SelectionModule L:338 vor HiggsTAGGER"<<std::endl;
  // ///////////////////////////////////////////////////////// Higgs TAGGER //////////////////////////////////////////////////////////////////////////////////
 
  std::unique_ptr< std::vector<TopJet> > higgsjets_all (new std::vector<TopJet> (*event.topjets));
  //cleanen der topjets um sie in einen neuen Vektor zu speichern
  higgstag_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);
  ak4_cleaner->process(event);
  std::unique_ptr< std::vector<TopJet>>  topjets_higgstag(new std::vector<TopJet> (*event.topjets));
  if(topjets_higgstag->size()) { std::cout <<"Size der subjets Higgstag"<< topjets_higgstag->at(0).subjets().size()<< std::endl;}
  // zurueck speichern der all topjets
  event.topjets->clear();
  event.topjets->reserve(higgsjets_all->size());
  for(const auto & j : *higgsjets_all) event.topjets->push_back(j); 
  sort_by_pt<TopJet>(*event.topjets);
  //handle auf toptag Topjets
  event.set(h_higgstag,*topjets_higgstag );

  //Higgstag
  const bool pass_higgstag = higgstag_sel->passes(event);
  input_zwtag_h->fill(event);
  input_higgstag_h->fill(event);
  if(pass_higgstag){
    output_higgstag_h->fill(event);
    topjet_higgstag_h->fill(event);
    eff_higgstag_h->fill(event);
    jet_higgstag_h->fill(event);
    muon_higgstag_h->fill(event);
    event_higgstag_h->fill(event);
  }

  bool pass_zwtag=false;
  if(!pass_higgstag){
    std::cout<<"SelectionModule L:338 vor ZWTAGGER"<<std::endl;  
    ///////////////////////////////////////////////////////// ZW TAGGER //////////////////////////////////////////////////////////////////////////////////
 
    std::unique_ptr< std::vector<TopJet> > ZWjets_all(new std::vector<TopJet> (*event.topjets));
    //cleanen der topjets um sie in einen neuen Vektor zu speichern
    ZWtag_cleaner->process(event);
    sort_by_pt<TopJet>(*event.topjets);
    ak4_cleaner->process(event);
    std::unique_ptr< std::vector<TopJet>>  topjets_ZWtag(new std::vector<TopJet> (*event.topjets));
    if(topjets_ZWtag->size()) { std::cout <<"Size der subjets zwtag "<< topjets_ZWtag->at(0).subjets().size()<<" v4 des ersten " <<topjets_ZWtag->at(0).subjets().at(0).v4() << std::endl;}
    // zurueck speichern der all topjets
    event.topjets->clear();
    event.topjets->reserve(ZWjets_all->size());
    for(const auto & j : *ZWjets_all) event.topjets->push_back(j); 
    sort_by_pt<TopJet>(*event.topjets);
    //handle auf toptag Topjets
    event.set(h_ZWtag,*topjets_ZWtag );

 


 ///////////////////////////////////////////////////////// HIGGSTAGGER || ZW TAGGER //////////////////////////////////////////////////////////////////////////////////

    pass_zwtag = ZWtag_sel->passes(event);
    if(!pass_zwtag) return false;
    output_zwtag_h->fill(event);
    topjet_zwtag_h->fill(event);
    eff_zwtag_h->fill(event);
    jet_zwtag_h->fill(event);
    muon_zwtag_h->fill(event);
    event_zwtag_h->fill(event);
  }

 

  output_combined_h->fill(event); 


  // std::cout<<"SelectionModule L:483 vor Test Selection"<<std::endl; 
  // // ///////////////////////////////////////////////////////// Test Selection //////////////////////////////////////////////////////////////////////////////////

  // const bool test1 = TOPdrmin_sel ->passes(event);
  // if(!test1) return false; 
  // drmin_h ->fill(event);
  // eff_drmin_h->fill(event);
  // jet_drmin_h->fill(event);
  // muon_drmin_h->fill(event);
  // higgstag_drmin_h->fill(event);
  // zwtag_drmin_h->fill(event);

  std::cout<<"SelectionModule L:338 vor TopTAGGER"<<std::endl;  
  ///////////////////////////////////////////////////////// TOP TAGGER //////////////////////////////////////////////////////////////////////////////////

  //alle topjets
  std::unique_ptr< std::vector<TopJet> > topjets_all (new std::vector<TopJet> (*event.topjets));
  //cleanen der topjets um sie in einen neuen Vektor zu speichern
  toptag_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);
  std::unique_ptr< std::vector<TopJet>>  topjets_toptag(new std::vector<TopJet> (*event.topjets));
  // zurueck speichern der all topjets
  event.topjets->clear();
  event.topjets->reserve(topjets_all->size());
  for(const auto & j : *topjets_all) event.topjets->push_back(j); 
  sort_by_pt<TopJet>(*event.topjets);
  //handle auf toptag Topjets
  event.set(h_toptag,*topjets_toptag );

  //Toptag
  const bool pass_toptag = toptag_sel->passes(event);
  output_toptag_h->fill(event);
  topjet_toptag_h->fill(event);
  eff_toptag_h->fill(event);
  jet_toptag_h->fill(event);
  muon_toptag_h->fill(event);
  event_toptag_h->fill(event);

  if(pass_higgstag && pass_toptag) higgs_top_topjet_toptag_h->fill(event);
  if(pass_higgstag && !pass_toptag) higgs_notop_topjet_toptag_h->fill(event);
  if(pass_zwtag && pass_toptag)zw_top_topjet_toptag_h->fill(event);
  if(pass_zwtag && !pass_toptag)zw_notop_topjet_toptag_h->fill(event);
 
 ///////////////////////////////////////////////////////////////// Tagger Hist ///////////////////////////////////////////////////////
  topjet_tagger_h->fill(event);
  eff_tagger_h->fill(event);
  jet_tagger_h->fill(event);
  muon_tagger_h->fill(event);
  event_tagger_h->fill(event);

  if(pass_higgstag && pass_toptag) higgs_top_topjet_tagger_h->fill(event);
  if(pass_higgstag && !pass_toptag) higgs_notop_topjet_tagger_h->fill(event);
  if(pass_zwtag && pass_toptag)zw_top_topjet_tagger_h->fill(event);
  if(pass_zwtag && !pass_toptag)zw_notop_topjet_tagger_h->fill(event);

  std::cout<<"SelectionModule L:303 vor KinReco"<<std::endl;
  //////////////////////////////////////////////////////////// KIN RECO///////////////////////////////////////////////////////////////////////////////////
  
  reco_primlep->process(event);
  if(!(ZprimeTotTPrime_reco->process(event)))return false;
  ZprimeTotTPrime_chi->process(event); 
  // save only the chi2-best ttbar hypothesis in output sub-ntuple
  std::vector<ZPrimeTotTPrimeReconstructionHypothesis>& hyps = event.get(h_ZprimeTotTPrime_hyps);
  const ZPrimeTotTPrimeReconstructionHypothesis* hyp = get_best_hypothesis(hyps, "Chi2");
  if(!hyp) std::runtime_error("ZprimeTotTPrimeSelectionModule::process -- best hypothesis for reconstruction not found");
  const ZPrimeTotTPrimeReconstructionHypothesis hyp_obj(*hyp);
  std::cout << "Test in Selection Module " << hyp->HZW_subjets().size() << " v4 des ersten " <<hyp->HZW_subjets().at(0).v4()<<std::endl;
  chi2min_reco_h->fill(event);
  topjet_reco_h->fill(event);
  eff_reco_h->fill(event);
  jet_reco_h->fill(event);
  muon_reco_h->fill(event);
  event_reco_h->fill(event);

  if(pass_higgstag && pass_toptag) higgs_top_topjet_reco_h->fill(event);
  if(pass_higgstag && !pass_toptag) higgs_notop_topjet_reco_h->fill(event);
  if(pass_zwtag && pass_toptag)zw_top_topjet_reco_h->fill(event);
  if(pass_zwtag && !pass_toptag)zw_notop_topjet_reco_h->fill(event);

  if(pass_higgstag && pass_toptag) higgs_top_chi2min_reco_h->fill(event);
  if(pass_higgstag && !pass_toptag) higgs_notop_chi2min_reco_h->fill(event);
  if(pass_zwtag && pass_toptag)zw_top_chi2min_reco_h->fill(event);
  if(pass_zwtag && !pass_toptag)zw_notop_chi2min_reco_h->fill(event);

  hyps.clear();
  hyps.push_back(hyp_obj);
  std::cout << "SelectionModule L:715 vor Chi2Cut"<<std::endl;
  //////////////////////////////////////////////////////////  CHi2 Cut  ////////////////////////////////////////////////////////
  bool pass_chi2cut = chi2cut_sel->passes(event);
  if(!pass_chi2cut) return false;

  chi2min_chi2cut_h->fill(event);
  topjet_chi2cut_h->fill(event);
  eff_chi2cut_h->fill(event);
  jet_chi2cut_h->fill(event);
  muon_chi2cut_h->fill(event);
  event_chi2cut_h->fill(event);

  if(pass_higgstag && pass_toptag) higgs_top_topjet_chi2cut_h->fill(event);
  if(pass_higgstag && !pass_toptag) higgs_notop_topjet_chi2cut_h->fill(event);
  if(pass_zwtag && pass_toptag)zw_top_topjet_chi2cut_h->fill(event);
  if(pass_zwtag && !pass_toptag)zw_notop_topjet_chi2cut_h->fill(event);

  if(pass_higgstag && pass_toptag) higgs_top_chi2min_chi2cut_h->fill(event);
  if(pass_higgstag && !pass_toptag) higgs_notop_chi2min_chi2cut_h->fill(event);
  if(pass_zwtag && pass_toptag)zw_top_chi2min_chi2cut_h->fill(event);
  if(pass_zwtag && !pass_toptag)zw_notop_chi2min_chi2cut_h->fill(event);


  ////////////////////////////////////////////////////////Test Section////////////////////////////////////////////////////////////////////////////////////////
  
  if(hyp->toplep_v4().M()<130){
    //  printer->process(event);
    chi2min_leptop_h->fill(event);
    topjet_leptop_h->fill(event);
    eff_leptop_h->fill(event);
    jet_leptop_h->fill(event);
    muon_leptop_h->fill(event);
    event_leptop_h->fill(event);

    if(pass_higgstag && pass_toptag) higgs_top_topjet_leptop_h->fill(event);
    if(pass_higgstag && !pass_toptag) higgs_notop_topjet_leptop_h->fill(event);
    if(pass_zwtag && pass_toptag)zw_top_topjet_leptop_h->fill(event);
    if(pass_zwtag && !pass_toptag)zw_notop_topjet_leptop_h->fill(event);

    if(pass_higgstag && pass_toptag) higgs_top_chi2min_leptop_h->fill(event);
    if(pass_higgstag && !pass_toptag) higgs_notop_chi2min_leptop_h->fill(event);
    if(pass_zwtag && pass_toptag)zw_top_chi2min_leptop_h->fill(event);
    if(pass_zwtag && !pass_toptag)zw_notop_chi2min_leptop_h->fill(event);

    if(event.met->pt() > 50){
      chi2min_met_h->fill(event);
    }
  }
  if(hyp->toplep_v4().pt() >100){
    //  printer->process(event);
    chi2min_toppt_h->fill(event);
    topjet_toppt_h->fill(event);
    eff_toppt_h->fill(event);
    jet_toppt_h->fill(event);
    muon_toppt_h->fill(event);
    event_toppt_h->fill(event);

    if(pass_higgstag && pass_toptag) higgs_top_topjet_toppt_h->fill(event);
    if(pass_higgstag && !pass_toptag) higgs_notop_topjet_toppt_h->fill(event);
    if(pass_zwtag && pass_toptag)zw_top_topjet_toppt_h->fill(event);
    if(pass_zwtag && !pass_toptag)zw_notop_topjet_toppt_h->fill(event);

    if(pass_higgstag && pass_toptag) higgs_top_chi2min_toppt_h->fill(event);
    if(pass_higgstag && !pass_toptag) higgs_notop_chi2min_toppt_h->fill(event);
    if(pass_zwtag && pass_toptag)zw_top_chi2min_toppt_h->fill(event);
    if(pass_zwtag && !pass_toptag)zw_notop_chi2min_toppt_h->fill(event);
  }



  return true;
}


UHH2_REGISTER_ANALYSIS_MODULE(ZPrimeTotTPrimeSelectionModule)
