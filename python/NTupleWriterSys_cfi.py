import FWCore.ParameterSet.Config as cms
#from TopAnalysis.TopUtils.EventWeightPU_cfi import *

writeNTuple = cms.EDAnalyzer('NTupleWriterSys',
                       muons = cms.InputTag("muons"),
                       #noCutMuons = cms.InputTag("noCutMuons"),
                       elecs = cms.InputTag("elecs"),
                       #noCutElecs = cms.InputTag("noCutElecs"),
                       weight    =  cms.InputTag('eventWeightPU', 'eventWeightPU'),
                       datatype  =  cms.InputTag("data"),
)

