#! /usr/bin/env python

from ROOT import *
gROOT.SetBatch(False)

def main():

    print '\nInside CPPF_EMTF_xunwu\n'

    ################################
    #####   Load input files   #####
    ################################

    in_dir = '/afs/cern.ch/work/a/abrinke1/public/EMTF/Commissioning/2017/'
    in_file_name = in_dir+'EMTF_Tree_DoubleMuon_300122_500k.root'
    out_file = TFile('plots/CPPF_EMTF_xunwu_300122_500k_hits.root','recreate')


    in_tree_name = 'Events'

    in_file = TFile.Open(in_file_name)
    in_tree = in_file.Get(in_tree_name)

    ################################
    #####   Loop over events   #####
    ################################
    
    for iEvt in range(5):                #*what is an event, what is a tree here
        
        in_tree.GetEntry(iEvt)

        ## Get branches from the trees
        Event  = in_tree.EventAuxiliary
        UnpHits = in_tree.l1tEMTFHits_emtfStage2Digis__L1TMuonEmulation
        UnpTrks = in_tree.l1tEMTFTracks_emtfStage2Digis__L1TMuonEmulation
        EmuHits = in_tree.l1tEMTFHits_simEmtfDigis__L1TMuonEmulation
        EmuTrks = in_tree.l1tEMTFTracks_simEmtfDigis__L1TMuonEmulation

        nUnpHits = UnpHits.size()
        nUnpTrks = UnpTrks.size()
        nEmuHits = EmuHits.size()
        nEmuTrks = EmuTrks.size()

        if nUnpTrks == 0: continue          ## no track


	for iUnpHit in range(nUnpHits):
            UnpHit = UnpHits.at(iUnpHit)
	    print UnpHit.Is_RPC()

        for endcap in [-1, 1]:  ## Endcaps +/-1
            for sector in range(1, 7):  ## Sectors 1 - 6

                has_unp_trk = False  ## Check for an unpacked track that matches all criteria
                
                ## Loop over all unpacked tracks
                for iUnpTrk in range(nUnpTrks):      ## for covers all lines with more indentation
                    UnpTrk = UnpTrks.at(iUnpTrk)

                    print UnpTrk.Sector()       
                ## End loop: for iUnpTrk in range(nUnpTrks):


    #######################################
    #####   Write output histograms   #####
    #######################################




    out_file.Close()
    del in_tree
    in_file.Close()

if __name__ == '__main__':
    main()
