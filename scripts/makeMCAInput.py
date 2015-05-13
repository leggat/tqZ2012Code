#A tool to pull a load of information from the mva trees. Should be all easy jazz...

from ROOT import *

import numpy as n
import sys
import os
from array import array
from jetCorrectionUncertainty import JetCorrectionUncertainty

def sortOutLeptons(tree,channel):
    ###Returns three TLorentzVectors containing the two z leptons and the w lepton. This will be VERY useful for making all of the plots.
    #Reads the position of the w and z leptons from variables stored at mvaTree making time, because I'm great and finally got around to doing it.
    zMass = 100
    zLep1,zLep2,wLep = 0,0,0
    #Let's try commenting this out and see if everything breaks? Hopefully it won't do...
    #if tree.numElePF2PAT < 3:
    #    return (0,0,0)
    if channel == "eee":
        wLep = TLorentzVector(tree.elePF2PATGsfPx[tree.wLepIndex],tree.elePF2PATGsfPy[tree.wLepIndex],tree.elePF2PATGsfPz[tree.wLepIndex],tree.elePF2PATGsfE[tree.wLepIndex])
        zLep1 = TLorentzVector(tree.elePF2PATGsfPx[tree.zLep1Index],tree.elePF2PATGsfPy[tree.zLep1Index],tree.elePF2PATGsfPz[tree.zLep1Index],tree.elePF2PATGsfE[tree.zLep1Index])
        zLep2 = TLorentzVector(tree.elePF2PATGsfPx[tree.zLep2Index],tree.elePF2PATGsfPy[tree.zLep2Index],tree.elePF2PATGsfPz[tree.zLep2Index],tree.elePF2PATGsfE[tree.zLep2Index])
    if channel == "eemu":
        zLep1 = TLorentzVector(tree.elePF2PATGsfPx[tree.zLep1Index],tree.elePF2PATGsfPy[tree.zLep1Index],tree.elePF2PATGsfPz[tree.zLep1Index],tree.elePF2PATGsfE[tree.zLep1Index])
        zLep2 = TLorentzVector(tree.elePF2PATGsfPx[tree.zLep2Index],tree.elePF2PATGsfPy[tree.zLep2Index],tree.elePF2PATGsfPz[tree.zLep2Index],tree.elePF2PATGsfE[tree.zLep2Index])
        wLep = TLorentzVector(tree.muonPF2PATPx[tree.wLepIndex],tree.muonPF2PATPy[tree.wLepIndex],tree.muonPF2PATPz[tree.wLepIndex],tree.muonPF2PATE[tree.wLepIndex])
    if channel == "emumu":
        zLep1 = TLorentzVector(tree.muonPF2PATPx[tree.zLep1Index],tree.muonPF2PATPy[tree.zLep1Index],tree.muonPF2PATPz[tree.zLep1Index],tree.muonPF2PATE[tree.zLep1Index])
        zLep2 = TLorentzVector(tree.muonPF2PATPx[tree.zLep2Index],tree.muonPF2PATPy[tree.zLep2Index],tree.muonPF2PATPz[tree.zLep2Index],tree.muonPF2PATE[tree.zLep2Index])
        wLep = TLorentzVector(tree.elePF2PATGsfPx[tree.wLepIndex],tree.elePF2PATGsfPy[tree.wLepIndex],tree.elePF2PATGsfPz[tree.wLepIndex],tree.elePF2PATGsfE[tree.wLepIndex])
    if channel == "mumumu":
        zLep1 = TLorentzVector(tree.muonPF2PATPx[tree.zLep1Index],tree.muonPF2PATPy[tree.zLep1Index],tree.muonPF2PATPz[tree.zLep1Index],tree.muonPF2PATE[tree.zLep1Index])
        zLep2 = TLorentzVector(tree.muonPF2PATPx[tree.zLep2Index],tree.muonPF2PATPy[tree.zLep2Index],tree.muonPF2PATPz[tree.zLep2Index],tree.muonPF2PATE[tree.zLep2Index])
        wLep = TLorentzVector(tree.muonPF2PATPx[tree.wLepIndex],tree.muonPF2PATPy[tree.wLepIndex],tree.muonPF2PATPz[tree.wLepIndex],tree.muonPF2PATE[tree.wLepIndex])
    return (zLep1,zLep2,wLep)

def getJets(tree,syst,jetUnc,met):
    #Makes a short list of indices of the jets in the event
    jetList = []
    jetVecList = []
    for i in range(15):
        if tree.jetInd[i] > -.5:
            jetList.append(tree.jetInd[i])
            jetVecList.append(getJetVec(tree,tree.jetInd[i],syst,jetUnc,met))
        else: continue
    return (jetList,jetVecList)

def getBjets(tree,syst,jetUnc,met,jets):
    #Return a list of the indices of the b-jets in the event
    bJetList = []
    bJetVecList = []
    for i in range(10):
        if tree.bJetInd[i] > -0.5:
            bJetList.append(tree.bJetInd[i])
            bJetVecList.append(getJetVec(tree,jets[tree.bJetInd[i]],syst,jetUnc,met))
        else:continue
#    print len(bJetList)
    return (bJetList,bJetVecList)

def getJetVec(tree, index, syst, jetUnc, metVec):
    #Gets a vector for a jet and applies jet corrections.
    oldSmearCorr = 0.;
    if (fabs(tree.jetPF2PATEta[index]) <= 1.1):
        oldSmearCorr = 0.066
    elif (fabs(tree.jetPF2PATEta[index]) <= 1.7):
        oldSmearCorr = 0.191
    elif (fabs(tree.jetPF2PATEta[index]) <= 2.3):
        oldSmearCorr = 0.096;
    else:
        oldSmearCorr = 0.166;
    oldSmearValue = 1.0;
    if (jetUnc and tree.genJetPF2PATPT[index] > -990.) :
        oldSmearValue = max(0.0, tree.jetPF2PATPtRaw[index] + (tree.jetPF2PATPtRaw[index] - tree.genJetPF2PATPT[index]) * oldSmearCorr)/tree.jetPF2PATPtRaw[index];
    newJECCorr = 0.;
    if (fabs(tree.jetPF2PATEta[index]) <= 0.5) :
        newJECCorr = 1.079;
        if (syst == 16): newJECCorr = 1.105;
        elif (syst == 32): newJECCorr = 1.053;
    elif (fabs(tree.jetPF2PATEta[index]) <= 1.1) :
        newJECCorr = 1.099;
        if (syst == 16): newJECCorr = 1.127;
        elif (syst == 32): newJECCorr = 1.071;
    elif (fabs(tree.jetPF2PATEta[index]) <= 1.7) :
        newJECCorr = 1.121;
        if (syst == 16): newJECCorr = 1.150;
        elif (syst == 32): newJECCorr = 1.092
    elif (fabs(tree.jetPF2PATEta[index]) <= 2.3) :
        newJECCorr = 1.208;
        if (syst == 16): newJECCorr = 1.254;
        elif (syst == 32): newJECCorr = 1.162;
    elif (fabs(tree.jetPF2PATEta[index]) <= 2.8):
        newJECCorr = 1.254;
        if (syst == 16): newJECCorr = 1.316;
        elif (syst == 32): newJECCorr = 1.192;
    elif (fabs(tree.jetPF2PATEta[index]) <= 3.2):
        newJECCorr = 1.395;
        if (syst == 16): newJECCorr = 1.458;
        elif (syst == 32): newJECCorr = 1.332;
    else :
        newJECCorr = 1.056;
        if (syst == 16): newJECCorr = 1.247;
        elif (syst == 32): newJECCorr = 0.865;
    newSmearValue = 1.0;
    if (jetUnc and tree.genJetPF2PATPT[index] > -990.): newSmearValue = max(0.0, tree.jetPF2PATPtRaw[index] + (tree.jetPF2PATPtRaw[index] - tree.genJetPF2PATPT[index]) * newJECCorr)/tree.jetPF2PATPtRaw[index];
    returnJet = TLorentzVector(0);
    if (newSmearValue < 0.01): returnJet.SetPxPyPzE(0.0001,0.0001,0.0001,0.0001);
    else :
        #Propogate through the met. But only do it if the smear jet isn't 0.
        metVec.SetPx(metVec.Px()+tree.jetPF2PATPx[index])
        metVec.SetPy(metVec.Py()+tree.jetPF2PATPy[index])
        returnJet.SetPxPyPzE(newSmearValue*tree.jetPF2PATPx[index]/oldSmearValue,newSmearValue*tree.jetPF2PATPy[index]/oldSmearValue,newSmearValue*tree.jetPF2PATPz[index]/oldSmearValue,newSmearValue*tree.jetPF2PATE[index]/oldSmearValue);
    if syst == 16:
        returnJet *= 1+ jetUnc.getUncertainty(returnJet.Pt(), returnJet.Eta(),1)
    elif syst == 32:
        returnJet *= 1+ jetUnc.getUncertainty(returnJet.Pt(), returnJet.Eta(),2)
    metVec.SetPx(metVec.Px()-returnJet.Px())
    metVec.SetPy(metVec.Py()-returnJet.Py())
    return returnJet

def doUncMet(tree,met,zLep1,zLep2,wLep,jetVecs,syst):
    #Subtracts all items from met and then varies what's left by 10% for systematic purposes.
    uncMetX = met.Px() + zLep1.Px() + zLep2.Px() + wLep.Px()
    uncMetY = met.Py() + zLep1.Py() + zLep2.Py() + wLep.Py()
    for i in range(len(jetVecs)):
        uncMetX += jetVecs[i].Px()
        uncMetY += jetVecs[i].Py()
    if syst == 1028:
        met.SetPx(met.Px() + 0.1*uncMetX)
        met.SetPy(met.Py() + 0.1*uncMetY)
    else:
        met.SetPx(met.Px() - 0.1*uncMetX)
        met.SetPy(met.Py() - 0.1*uncMetY)
    return met

def setupInputVars():
    #Make the variables we want to save
    inputVars = {}
    inputVars["eventWeight"] = array('f',[0.])
    inputVars["mTW"] = array('f',[0.])
    inputVars["leptWPt"] = array('f',[0.])
    inputVars["leadJetPt"] = array('f',[0.])
    inputVars["totPt"] = array('f',[0.])
    inputVars["totEta"] = array('f',[0.])
    inputVars["totPtVec"] = array('f',[0.])
    inputVars["totVecM"] = array('f',[0.])
    inputVars["chan"] = array('i',[0])
    inputVars["nJets"] = array('f',[0.])
    inputVars["nBjets"] = array('f',[0.])
    inputVars["met"] = array('f',[0.])
    inputVars["lepPt"] = array('f',[0.])
    inputVars["lepMetPt"] = array('f',[0.])
    inputVars["totPt2Jet"] = array('f',[0.])
    inputVars["leadJetbTag"] = array('f',[0.])
    inputVars["leadJetEta"] = array('f',[0.])
    inputVars["secJetbTag"] = array('f',[0.])
    inputVars["secJetPt"] = array('f',[0.])
    inputVars["secJetEta"] = array('f',[0.])
    inputVars["bTagDisc"] = array('f',[0.])
    inputVars["topMass"] = array('f',[0.])
    inputVars["topPt"] = array('f',[0.])
    inputVars["topEta"] = array('f',[0.])
    inputVars["zPt"] = array('f',[0.])
    inputVars["zEta"] = array('f',[0.])
    inputVars["wLepEta"] = array('f',[0.])
    inputVars["wZdelR"] = array('f',[0.])
    inputVars["j1j2delR"] = array('f',[0.])
    inputVars["minZJetR"] = array('f',[0.])
    inputVars["zWLepdelR"] = array('f',[0.])
    inputVars["zmetdelPhi"] = array('f',[0.])
    inputVars["zWLepdelPhi"] = array('f',[0.])
    inputVars["lbDelR"] = array('f',[0.])
    inputVars["lbDelPhi"] = array('f',[0.])
    inputVars["zlb1DelR"] = array('f',[0.])
    inputVars["zlb1DelPhi"] = array('f',[0.])
    inputVars["zlb2DelR"] = array('f',[0.])
    inputVars["zlb2DelPhi"] = array('f',[0.])
    inputVars["totHt"] = array('f',[0.])
    inputVars["lepHt"] = array('f',[0.])
    inputVars["jetHt"] = array('f',[0.])
    inputVars["lepMetHt"] = array('f',[0.])
    inputVars["totHtOverPt"] = array('f',[0.])
    inputVars["zMass"] = array('f',[0.])
    return inputVars

def setupBranches(tree,varMap):
    tree.Branch("tree_EvtWeight", varMap["eventWeight"], "tree_EvtWeight/F")
    tree.Branch("tree_mTW", varMap["mTW"], "tree_mTW/F")
    tree.Branch("tree_leptWPt", varMap["leptWPt"], "tree_leptWPt/F")
    tree.Branch("tree_leadJetPt",varMap["leadJetPt"],"tree_leadJetPt/F")
    tree.Branch("tree_totPt",varMap["totPt"],"tree_totPt/F")
    tree.Branch("tree_totEta",varMap["totEta"],"tree_totEta/F")
    tree.Branch("tree_totPtVec",varMap["totPtVec"],"tree_totPtVec/F")
    tree.Branch("tree_totVecM",varMap["totVecM"],"tree_totVecM/F")
    tree.Branch("tree_Channel",varMap["chan"],"tree_Channel/I")
    tree.Branch("tree_NJets",varMap["nJets"],"tree_NJets/F")
    tree.Branch("tree_NBJets",varMap["nBjets"],"tree_NBJets/F")
    tree.Branch("tree_met",varMap["met"],"tree_met/F")
    tree.Branch("tree_lepPt",varMap["lepPt"],"tree_lepPt/F")
    tree.Branch("tree_lepMetPt",varMap["lepMetPt"],"tree_lepMetPt/F")
    tree.Branch("tree_totPt2Jet",varMap["totPt2Jet"],"tree_totPt2Jet/F")
    tree.Branch("tree_btagDiscri",varMap["bTagDisc"],"btagDiscri/F")
    tree.Branch("tree_leadJetbTag",varMap["leadJetbTag"],"leadJetbTag/F")
    tree.Branch("tree_leadJetEta",varMap["leadJetEta"],"leadJetEta/F")
    tree.Branch("tree_secJetbTag",varMap["secJetbTag"],"secJetbTag/F")
    tree.Branch("tree_secJetPt",varMap["secJetPt"],"secJetPt/F")
    tree.Branch("tree_secJetEta",varMap["secJetEta"],"secJetEta/F")
    tree.Branch("tree_topMass",varMap["topMass"],"tree_topMass/F")
    tree.Branch("tree_topPt",varMap["topPt"],"tree_topPt/F")
    tree.Branch("tree_topEta",varMap["topEta"],"tree_topEta/F")
    tree.Branch("tree_Zpt",varMap["zPt"],"tree_Zpt/F")
    tree.Branch("tree_Zeta",varMap["zEta"],"tree_Zeta/F")
    tree.Branch("tree_leptWEta",varMap["wLepEta"],"tree_leptWEta/F")
    tree.Branch("tree_wzdelR",varMap["wZdelR"],"tree_wzdelR/F")
    tree.Branch("tree_jjdelR",varMap["j1j2delR"],"tree_jjdelR/F")
    tree.Branch("tree_zjminR",varMap["minZJetR"],"tree_zjminR/F")

