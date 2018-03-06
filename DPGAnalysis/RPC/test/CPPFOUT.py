#! /usr/bin/env python

from ROOT import *
gROOT.SetBatch(False)

def main():

    print '\n******************************CPPF Unpacker*****************************'

    ################################
    #####   Load input files   #####
    ################################

    in_dir = '/afs/cern.ch/user/c/chengl/public/cppftest/'
    in_file_name = in_dir+'testRPCCPPF.root'
#    out_file = TFile('plots/CPPFOUT.root','recreate')

    in_tree_name = 'Events'

    in_file = TFile.Open(in_file_name)
    in_tree = in_file.Get(in_tree_name)
    
    print 'Number of entries: %d\n' % (in_tree.GetEntries())
    for iEny in range(0,100):
        in_tree.GetEntry(iEny)
        Event = in_tree.EventAuxiliary    #RPCDetIdRPCDigiMuonDigiCollection_RPCCPPFRawToDigi__testRPCCPPF#RPCCPPFDigis_RPCCPPFRawToDigi__testRPCCPPF
        CPPFRPCDigi = in_tree.RPCCPPFDigis_RPCCPPFRawToDigi__testRPCCPPF
        nhits=CPPFRPCDigi.size()
        print 'iEny=%d  nhits=%d' % (iEny, nhits)
    
        for ihit in range(nhits):
            hit = CPPFRPCDigi.at(ihit)
            print '\nRPCDetId.region=%d  ring=%d station=%d sector=%d layer=%d subsector=%d roll=%d\n' % (hit.getRPCDetId().region(),hit.getRPCDetId().ring(),hit.getRPCDetId().station(),hit.getRPCDetId().sector(),hit.getRPCDetId().layer(),hit.getRPCDetId().subsector(),hit.getRPCDetId().roll())
            print 'BX=%d  Theta=%d  Phi=%d\n' % (hit.getBX(),hit.getTheta(),hit.getPhi())
#    out_file.Close()
    del in_tree
    in_file.Close()

if __name__ == '__main__':
    main()

