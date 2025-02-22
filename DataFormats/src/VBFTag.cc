#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/VBFTag.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"

using namespace flashgg;

VBFTag::VBFTag() {}

VBFTag::~VBFTag() {}

VBFTag::VBFTag( edm::Ptr<flashgg::DiPhotonCandidate> diPho, edm::Ptr<DiPhotonMVAResult> mvaRes, edm::Ptr<VBFDiPhoDiJetMVAResult> vbfDiPhoDiJet_mvaRes, edm::Ptr<GluGluHMVAResult> ggh_mvaRes, edm::Ptr<VHhadMVAResult> vh_mvaRes) :
    VBFTag::VBFTag( diPho, *mvaRes, *vbfDiPhoDiJet_mvaRes, *ggh_mvaRes, *vh_mvaRes) {}

VBFTag::VBFTag( edm::Ptr<DiPhotonCandidate> dipho, DiPhotonMVAResult mvares, VBFDiPhoDiJetMVAResult vbfDiPhoDiJet_mvaRes, GluGluHMVAResult ggh_mvaRes, VHhadMVAResult vh_mvaRes) :
    DiPhotonTagBase::DiPhotonTagBase( dipho, mvares )
{
    vbfDiPhoDiJet_mva_result_ = vbfDiPhoDiJet_mvaRes;
    ggh_mvaRes_ = ggh_mvaRes;
    vh_mvaRes_  = vh_mvaRes;
    alphaUp_ = 0.;
    alphaDown_ = 0.;
    for (unsigned i = 0 ; i < 3 ; i++) {
        scaleUp_[i] = 0.;
        scaleDown_[i] = 0.;
    }
    for (unsigned i = 0 ; i < 60 ; i++) {
        pdf_[i] = 0.;
    }
}


const VBFDiPhoDiJetMVAResult VBFTag::VBFDiPhoDiJetMVA() const
{
    return vbfDiPhoDiJet_mva_result_;
}
const VBFMVAResult VBFTag::VBFMVA() const
{
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult;
}

const GluGluHMVAResult VBFTag::GluGluHMVA() const
{
    return ggh_mvaRes_;
}

const VHhadMVAResult VBFTag::VHhadMVA() const
{
    return vh_mvaRes_;
}

const reco::Candidate::LorentzVector VBFTag::leadingJet() const
{
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.leadJet;
}

const reco::Candidate::LorentzVector  VBFTag::subLeadingJet() const
{
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.subleadJet;
}

const reco::Candidate::LorentzVector  VBFTag::subSubLeadingJet() const
{
    //! adding a third jets for the VBF studies
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.subsubleadJet;
}

const reco::Candidate::LorentzVector  VBFTag::fourthJet() const
{
    //! adding a fourth jets for the VBF studies
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.fourthJet;
}

const edm::Ptr<Jet> VBFTag::leadingJet_ptr() const
{
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.leadJet_ptr;
}

const edm::Ptr<Jet> VBFTag::subLeadingJet_ptr() const
{
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.subleadJet_ptr;
}

const edm::Ptr<Jet> VBFTag::subSubLeadingJet_ptr() const
{
    //! adding a third jets for the VBF studies
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.subsubleadJet_ptr;
}

const edm::Ptr<Jet> VBFTag::fourthJet_ptr() const
{
    //! adding a fourth jets for the VBF studies
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.fourthJet_ptr;
}

const bool VBFTag::hasValidVBFTriJet() const
{
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.hasValidVBFTriJet;
}

const bool VBFTag::hasValidVBFTetraJet() const
{
    return vbfDiPhoDiJet_mva_result_.vbfMvaResult.hasValidVBFTetraJet;
}

const float VBFTag::ptHjj() const {
    if (! hasValidVBFDiJet() ) { 
        return -1.;
    }
    return (leadingJet_ptr()->p4() + subLeadingJet_ptr()->p4() + diPhoton()->p4()).pt();
}

// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

