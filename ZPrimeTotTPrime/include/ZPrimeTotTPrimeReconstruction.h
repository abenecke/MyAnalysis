#pragma once

#include "UHH2/core/include/AnalysisModule.h"
#include "TMinuit.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/PrimaryLepton.h"

#include <UHH2/ZPrimeTotTPrime/include/ZPrimeTotTPrimeReconstructionHypothesis.h>

typedef std::function< std::vector<LorentzVector>  (const LorentzVector & lepton, const LorentzVector & met)> NeutrinoReconstructionMethod;

class ZPrimeTotTPrimeReconstruction: public uhh2::AnalysisModule {
public:

    explicit ZPrimeTotTPrimeReconstruction(uhh2::Context & ctx, const NeutrinoReconstructionMethod & neutrinofunction, const std::string & label="ZprimeTotTPrimeReconstruction");

    virtual bool process(uhh2::Event & event) override;

    virtual ~ZPrimeTotTPrimeReconstruction();
    std::vector<Jet>* AK4cleaning(std::vector<Jet>* ak4, TopJet ak8);
    void LepTop(std::vector<Jet>* ak4,  std::vector<LorentzVector> neutrinos, const Particle & lepton , ZPrimeTotTPrimeReconstructionHypothesis hyp,std::vector<TopJet> Tag );
    void LepHadTop(std::vector<Jet>* ak4,  std::vector<LorentzVector> neutrinos, const Particle & lepton , ZPrimeTotTPrimeReconstructionHypothesis hyp,std::vector<TopJet> Tag );


private:
    NeutrinoReconstructionMethod m_neutrinofunction;
    uhh2::Event::Handle<std::vector<ZPrimeTotTPrimeReconstructionHypothesis>> h_recohyps;
    uhh2::Event::Handle<FlavorParticle> h_primlep;
    uhh2::Event::Handle<ZPrimeGen> h_zprimegen;
    uhh2::Event::Handle<std::vector<TopJet> > h_toptag;
    uhh2::Event::Handle<std::vector<TopJet> > h_higgstag;
    uhh2::Event::Handle<std::vector<TopJet> > h_ZWtag;
    std::string btopjet;
    // std::unique_ptr<std::vector<Jet> > ak4jets;
    //std::vector<Jet>*ak4jets;
    std::vector<ZPrimeTotTPrimeReconstructionHypothesis> recoHyps;
};


std::vector<LorentzVector> NeutrinoReconstruction(const LorentzVector & lepton, const LorentzVector & met);

