#! /usr/bin/env python
## run this on the output of makeQCDHistos.py to get pretty plots

import os
import sys
import ROOT
import QCDPlotMaker as pm

ROOT.gROOT.SetBatch(1)

outdir = "rphi_plots/test_prescale"
infile = "output/test_prescale/QCDhistos.root"

try:
    os.makedirs(outdir)
except:
    pass

fin = ROOT.TFile(infile)

ht_reg_names = ["ht200to450","ht450to575","ht575to1000","ht1000to1500","ht1500toInf"]
nj_reg_names = ["j2to3","j4to6","j7toInf"]

## r_phi
for reg in ht_reg_names:
    h_qcd = fin.Get("rphi_{0}/h_qcd_rphi".format(reg))
    h_all = fin.Get("rphi_{0}/h_mcall_rphi".format(reg))
    if type(h_qcd)!=type(ROOT.TH1D()) or type(h_all)!=type(ROOT.TH1D()):
        raise Exception("ERROR: could not get MC rphi hists!!")
    outfile = os.path.join(outdir,"rphi_MC_{0}".format(reg))
    pm.makeRphiPlot(h_all,h_qcd, reg, False, outfile)

    h_qcd = fin.Get("rphi_{0}/h_datasub_rphi".format(reg))
    h_all = fin.Get("rphi_{0}/h_data_rphi".format(reg))
    if type(h_qcd)!=type(ROOT.TH1D()) or type(h_all)!=type(ROOT.TH1D()):
        raise Exception("ERROR: could not get data rphi hists!!")
    outfile = os.path.join(outdir,"rphi_data_{0}".format(reg))
    pm.makeRphiPlot(h_all,h_qcd, reg, True, outfile)

## f_j
for reg in ht_reg_names:
    h_qcd = fin.Get("fj_{0}/h_qcd_fj".format(reg))
    h_data = fin.Get("fj_{0}/h_data_fj".format(reg))
    if type(h_qcd)!=type(ROOT.TH1D()) or type(h_data)!=type(ROOT.TH1D()):
        raise Exception("ERROR: could not get f_j hists!!")
    outfile = os.path.join(outdir,"fj_{0}".format(reg))
    pm.makeFjPlot(h_qcd,h_data, reg, outfile)

## r_b
for reg in nj_reg_names:
    h_qcd = fin.Get("rb_{0}/h_qcd_rb".format(reg))
    h_data = fin.Get("rb_{0}/h_data_rb".format(reg))
    if type(h_qcd)!=type(ROOT.TH1D()) or type(h_data)!=type(ROOT.TH1D()):
        raise Exception("ERROR: could not get r_b hists!!")
    outfile = os.path.join(outdir,"rb_{0}".format(reg))
    pm.makeRbPlot(h_qcd,h_data, reg, outfile)

fin.Close()
