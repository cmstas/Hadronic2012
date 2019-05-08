#! /usr/bin/env python
import ROOT
from ResultPlotMaker import *
import ResultPlotUtils as utils

datacard_dir = "../CardMaker/cards_V00-10-16_FullRunII_newQCD"
outdir = "/home/users/bemarsh/public_html/mt2/result_plots/2019_FSR/V00-10-16_FullRunII_newQCD_v2"

# datacard_dir = "../cards_V00-10-10_FullRunII_17MCfor18_ttbbWeights_withZNJetWeights/"
# datacard_name = "datacard_{0}_{1}_{2}_DUMMYSIG_-1_-1.txt"

doSignal = False
MODEL = "rpvMonoPhi"
point = (1250,900)
sigName = "{0}_{1}_{2}".format(MODEL, *point)

doPostfit = False

if not doPostfit or doSignal:
    if not doSignal:
        utils.LoadPickledDatacards(os.path.join(datacard_dir,"templates","template_datacards.pkl"))
    else:
        utils.LoadPickledDatacards(os.path.join(datacard_dir,MODEL, sigName, "signal_datacards.pkl"))

if doPostfit:
    utils.LoadPostfitFile("/home/users/bemarsh/analysis/mt2/current/MT2Analysis/limits/postfit/V00-10-16_FullRunII/fitDiagnostics_all.root")



# utils.lumi = 59.97
# utils.lumi = 35.9
utils.lumi = 137

# scalePred = 15.0 / 136.3
# scalePred = (35.9+10+15) / 136.3
scalePred = 1.0

MakePlot("HT250to450", outdir, userMax=1e8, drawObs=True, doPostfit=doPostfit, scalePred=scalePred, drawSignal=doSignal, sigName=sigName, ratioRange=(0,2 if doPostfit else 3), makeSBplot=doSignal)
MakePlot("HT450to575", outdir, userMax=7e6, drawObs=True, doPostfit=doPostfit, scalePred=scalePred, drawSignal=doSignal, sigName=sigName, makeSBplot=doSignal)
MakePlot("HT575to1200", outdir, userMax=7e6, drawObs=True, doPostfit=doPostfit, scalePred=scalePred, drawSignal=doSignal, sigName=sigName, ratioRange=(0,3), makeSBplot=doSignal)
MakePlot("HT1200to1500", outdir, userMax=7e5, drawObs=True, doPostfit=doPostfit, scalePred=scalePred, drawSignal=doSignal, sigName=sigName, ratioRange=(0,4), makeSBplot=doSignal)
MakePlot("HT1500toInf", outdir, userMax=7e4, drawObs=True, doPostfit=doPostfit, scalePred=scalePred, drawSignal=doSignal, sigName=sigName, ratioRange=(0,4), makeSBplot=doSignal)
# monojet is handled specially, just use "monojet" as the ht region name
MakePlot("monojet", outdir, userMax=7e7, drawObs=True, doPostfit=doPostfit, scalePred=scalePred, drawSignal=doSignal, sigName=sigName, makeSBplot=doSignal)

# MakePlot("HT250to450", outdir, userMax=5e7, drawObs=True, scalePred=scalePred, doPull=True)
# MakePlot("HT450to575", outdir, userMax=7e6, drawObs=True, scalePred=scalePred, doPull=True)
# MakePlot("HT575to1200", outdir, userMax=7e6, drawObs=True, scalePred=scalePred, doPull=True, ratioRange=(-4,4))
# MakePlot("HT1200to1500", outdir, userMax=7e6, drawObs=True, scalePred=scalePred, doPull=True, ratioRange=(-4,4))
# MakePlot("HT1500toInf", outdir, userMax=7e5, drawObs=True, scalePred=scalePred, doPull=True, ratioRange=(-5,5))
# MakePlot("monojet", outdir, userMax=7e7, drawObs=True, scalePred=scalePred, doPull=True)

# MakeHTBinPlot(datacard_dir, datacard_name, outdir, userMax=1e8, scalePred=scalePred, ratioRange=(0.5,1.5))

MakeInclusivePlot(outdir, userMax=1e8, ratioRange=(0,3))
# MakeInclusivePlot(outdir, userMax=7e4, ratioRange=(0,3), do_ht_regs=["HT1200to1500"])





# datacard_dir_eth = "/home/users/bemarsh/analysis/mt2/current/MT2Analysis/scripts/cards_test_eth"
# datacard_name_eth = "datacard_{0}_{1}_{2}.txt"
# MakeComparison("HT200to450", datacard_dir, datacard_dir_eth, datacard_name, datacard_name_eth, outdir, iBkgd=1, userMax=7e5)
# MakeComparison("HT200to450", datacard_dir, datacard_dir_eth, datacard_name, datacard_name_eth, outdir, iBkgd=2, userMax=7e5)
# MakeComparison("HT575to1000", datacard_dir, datacard_dir_eth, datacard_name, datacard_name_eth, outdir, iBkgd=1, userMax=7e5)
# MakeComparison("HT575to1000", datacard_dir, datacard_dir_eth, datacard_name, datacard_name_eth, outdir, iBkgd=2, userMax=7e5)

#datacard_name_topo = "datacard_{0}_{1}_ttw_mg_lo.txt"
#MakeMacroRegionPlot(1,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
#MakeMacroRegionPlot(2,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
#MakeMacroRegionPlot(3,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
#MakeMacroRegionPlot(4,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
#MakeMacroRegionPlot(5,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
#MakeMacroRegionPlot(6,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
#MakeMacroRegionPlot(7,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
#MakeMacroRegionPlot(8,datacard_dir, datacard_name_topo, outdir, userMax=5e6)
