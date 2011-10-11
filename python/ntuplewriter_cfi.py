import FWCore.ParameterSet.Config as cms
#from TopAnalysis.TopUtils.EventWeightPU_cfi import *

writeNTuple = cms.EDAnalyzer('NTupleWriter',
                       muons = cms.InputTag("muons"),
                       elecs = cms.InputTag("elecs"),
                       jets      = cms.InputTag("jets"),
                       met       = cms.InputTag("met"),
                       vertices  = cms.InputTag('offlinePrimaryVertices'),
                       weight    =  cms.InputTag('eventWeightPU', 'eventWeightPU'),
                       datatype  =  cms.InputTag("data"),
                       includeTrigger = cms.bool(False),
                       triggerResults = cms.InputTag('TriggerResults','','HLT')
)

