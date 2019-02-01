# STCImplementation background estimates and plots

import ROOT
from math import sqrt
import re
import sys
import os
from os.path import isfile,join
import subprocess


sys.path.append("../Nifty")

import NiftyUtils

# Suppresses warnings about TH1::Sumw2
ROOT.gErrorIgnoreLevel = ROOT.kError

verbose = False # Print more status messages

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(False)
ROOT.gStyle.SetLegendTextSize(0.1)
ROOT.gStyle.SetPaintTextFormat("#3.3g")
ROOT.gStyle.SetLegendBorderSize(0)
simplecanvas = ROOT.TCanvas("plotter")
simplecanvas.SetCanvasSize(600,600)
simplecanvas.SetTicks(1,1)
simplecanvas.SetLeftMargin(0.16)
simplecanvas.SetTopMargin(0.12)
simplecanvas.SetRightMargin(0.16)

ROOT.gPad.SetPhi(-135)

makepngs = True

if len(sys.argv) < 2: 
    print "Which file?"
    exit()

filename = sys.argv[1]
shortname = filename[filename.rfind("/")+1:filename.find(".")]

isData = shortname.split("_")[0] == "data"
year = shortname.split("_")[1]
tag = shortname.split("_")[2]

filepath = "output_unmerged/{0}_{1}/".format(year,tag) if year != "2017and2018" else "output_unmerged/{0}_{1}/".format("2017",tag)
if isData: filepath += "data/"
inputlist = [filepath+f for f in os.listdir(filepath) if isfile(join(filepath, f))]
filelist = [ROOT.TFile.Open(infile) for infile in inputlist]

os.system("mkdir -p output")
os.system("mkdir -p pngs/{0}".format(shortname))

tfile = ROOT.TFile.Open(filename,"READ")
names = tfile.GetKeyNames()

outfile = ROOT.TFile.Open("output/Fshort_{}.root".format(shortname),"RECREATE")
outfile.cd()

def getAsymmetricErrors(y):
    yp=0.0
    ym=0.0
    yerr=[]
    alpha=1 - 0.6827
    if(y==0):
        ym = 0.0
    else:
        ym = ROOT.Math.gamma_quantile(alpha/2,y,1);
    yp =  ROOT.Math.gamma_quantile_c(alpha/2,y+1,1)
    ym=y-ym
    yp=yp-y
    yerr.append(yp)
    yerr.append(ym)
    return yerr


# loop over every key and process histograms 
for rawname in names:
    name = rawname[1:] # Get rid of leading /
    # Fshort histograms
    if name.find("max_weight") >= 0: continue
    if name.find("fs") > 0:
        h_fs = tfile.Get(name)
        h_fs_up = h_fs.Clone(name+"_up")
        h_fs_dn = h_fs.Clone(name+"_dn")
        for length in range(1,h_fs.GetNbinsX()+1):
            den = h_fs.GetBinContent(length,3)
            if den == 0: # don't care about these cases
                h_fs.SetBinContent(length,1,-1)
                h_fs.SetBinError(length,1,0)
                continue
            num = h_fs.GetBinContent(length,2)
            if num == 0: # don't care about these cases
                h_fs.SetBinContent(length,1,0)
                h_fs.SetBinError(length,1,(getAsymmetricErrors(num)[0] if isData else h_fs.GetBinError(length,1))/den) # upper error on this fshort is the upper error of the numerator, divided by the denominator
                continue
            h_fs.SetBinContent(length,1,num / den)
            # MC errors still symmetric
            derr = getAsymmetricErrors(den) if isData else [h_fs.GetBinError(length, 3)]*2
            nerr = getAsymmetricErrors(num) if isData else [h_fs.GetBinError(length, 2)]*2
            # there's an additional statistical error in the MC numerator coming from high weight events in the denominator not entering the numerator that we don't handle
            # quick check of where our largest events are from / how large they are
            if not isData: 
                max_weight = 0
                max_f = None
                for f in filelist:
                    h_max_weight = f.Get(name+"_max_weight_ST")
                    this_max_weight = h_max_weight.GetBinContent(length)
                    if this_max_weight > max_weight:
                        max_weight = this_max_weight
                        max_f = f
                print "max_weight for",name,max_weight,"from",f.GetName()
            newerr_up = sqrt( (derr[0]/den)**2 + (nerr[0]/num)**2 ) * num/den
            newerr_dn = sqrt( (derr[1]/den)**2 + (nerr[1]/num)**2 ) * num/den            
            h_fs_up.SetBinError(length, 1, newerr_up)
            h_fs_dn.SetBinError(length, 1, newerr_dn)
        h_fs.SetMarkerSize(1.8)
        h_fs.Draw("text E")
        simplecanvas.SaveAs("pngs/{0}/{1}.png".format(shortname,name))
        h_fs.Write()
        h_fs_up.Write()
        h_fs_dn.Write()
    # etaphi histograms
    elif not makepngs: continue
    elif name.find("etaphi") > 0:
        h_etaphi = tfile.Get(name)
        st_or_stc = "STC" if name.find("STC") >= 0 else "ST"
        track_type = name[name.rfind("_")+1:] + " " + st_or_stc + "s"
        if track_type[0:4] == "Lrej": track_type = "L " + st_or_stc +"s in Rejected M_{T}p_{T} Box"
        h_etaphi.SetTitle(h_etaphi.GetTitle()+", "+track_type+" ("+year+");#eta;#phi")
        h_etaphi.Draw()
        simplecanvas.SaveAs("pngs/{0}/{1}.png".format(shortname,name))
#    # Look at transfer factor as a function of MT2
#    elif name.find("mt2") > 0:
#        h_mt2 = tfile.Get(name)
#        h_mt2.SetLineWidth(3)
#        h_mt2.SetTitle(h_mt2.GetTitle()+";M_{T2} (GeV);Count")
#        h_mt2.Draw()
#        simplecanvas.SaveAs("pngs/{0}/{1}.png".format(shortname,name))
#    # Track mt x pt distribution
    elif name.find("mtpt") > 0:
        h_mtpt = tfile.Get(name)
        h_mtpt.GetXaxis().SetTitle("M_{T}(Track,MET) (GeV)")
        h_mtpt.GetXaxis().SetTitleOffset(2.2)
        h_mtpt.GetYaxis().SetTitle("p_{T} (GeV)")
        h_mtpt.GetYaxis().SetTitleOffset(2.2)
        xmax = h_mtpt.GetNbinsX()
        ymax = h_mtpt.GetNbinsY()
        for xbin in range(1,xmax+1):
            overflow = h_mtpt.GetBinContent(xbin,ymax+1)
            h_mtpt.SetBinContent(xbin,ymax,h_mtpt.GetBinContent(xbin,ymax)+overflow)
        for ybin in range(1,ymax+1):
            overflow = h_mtpt.GetBinContent(xmax+1,ybin)
            h_mtpt.SetBinContent(xmax,ybin,h_mtpt.GetBinContent(xmax,ybin)+overflow)
        upper_right_overflow = h_mtpt.GetBinContent(xmax+1,ymax+1)
        h_mtpt.SetBinContent(xmax,ymax,h_mtpt.GetBinContent(xmax,ymax)+upper_right_overflow)            
        h_mtpt.Draw("LEGO2Z")
        simplecanvas.SaveAs("pngs/{0}/{1}.png".format(shortname,name))
    # else it's a 1D plot
    elif name.find("layer") > 0:
        h = tfile.Get(name)
        h.SetTitle("Number of Tracker Layers with Measurement;N_{layer};Track Count")
        h.SetLineColor(ROOT.kBlack)
        h.SetLineWidth(3)
        simplecanvas.SetLogy()
        h.Draw()
        simplecanvas.SaveAs("pngs/{0}/{1}.png".format(shortname,name))
        simplecanvas.SetLogy(False)
    else:
        h = tfile.Get(name)
        h.Draw()
        simplecanvas.SaveAs("pngs/{0}/{1}.png".format(shortname,name))
        
# Now that we've processed every hist, loop back over and find the systematic associated with every baseline hist
for rawname in names:
    name = rawname[1:] # Get rid of leading /
    # Fshort histograms
    if name.find("fs") < 0: continue
    if name.find("max_weight") >= 0: continue
    if name.find("Baseline") < 0: continue
    if name.find("MR") < 0 and name.find("VR") < 0: continue
    if name.find("_dn") >= 0 or name.find("_up") >= 0: continue
    if verbose: print name
    h_fs = outfile.Get(name)
    h_fs_up = outfile.Get(name+"_up")
    h_fs_dn = outfile.Get(name+"_dn")
    h_syst = ROOT.TH1D(name+"_syst","Systematic f_{short} Error",h_fs.GetNbinsX(),0,h_fs.GetNbinsX())
    for length in range(1,h_fs.GetNbinsX()+1): 
        if verbose: print length            
        fs = h_fs.GetBinContent(length,1)
        if fs == 0:
            # Assume true fshort is no larger than 1
            systematic = 1
        else:
            fserr_up = h_fs_up.GetBinError(length,1)
            fserr_dn = h_fs_dn.GetBinError(length,1)
            max_variation_in_sigma = 0
            max_delta = 0
            max_variation_total_error = 0
            max_variation_stat_error = 0
            max_var = ""
            for variation in ["HT250","HT450","HT450MET100","MET30","MET100","MET250"]:
                h_fs_var = outfile.Get(name.replace("Baseline",variation))
                h_fs_var_up = outfile.Get(name.replace("Baseline",variation)+"_up")
                h_fs_var_dn = outfile.Get(name.replace("Baseline",variation)+"_dn")
                fs_var = h_fs_var.GetBinContent(length,1)
                if fs_var <= 0: continue
                if isData:
                    if fs_var < fs:
                        fserr = fserr_dn
                        fserr_var = h_fs_var_up.GetBinError(length,1)
                    else:
                        fserr = fserr_up
                        fserr_var = h_fs_var_dn.GetBinError(length,1)
                else:
                    fserr = h_fs.GetBinError(length,1)
                    fserr_var = h_fs_var.GetBinError(length,1)
                overall_error = sqrt(fserr**2 + fserr_var**2)
                delta_in_sigma = abs(fs - fs_var) / overall_error
                if delta_in_sigma > max_variation_in_sigma:
                    max_variation_in_sigma = delta_in_sigma
                    max_delta = fs-fs_var
                    max_variation_stat_error = fserr_var                    
                    max_var = variation
            # Now assign systematic large enough to move largest variation within 1 sigma of baseline
            # max_delta**2 = syst**2 + fserr**2 + fs_var**2 => syst = sqrt(max_delta**2 - fs**2 - fs_var**2)
            # If max_delta < sqrt(fserr**2*maxerr**2) already, no systematic is needed, but assign 10% anyway
            expr = max_delta**2-(fserr_up if max_delta < 0 else fserr_dn)**2-max_variation_stat_error**2
            if expr < 0: systematic = 0.1*fs
            else: systematic = max( sqrt(expr), 0.1*fs )
            if verbose: print "name: {} length: {} fs: {} fserr: {} max_delta: {} max_variation_stat_error: {} max_var: {} systematic: {}".format(name,length,fs,fserr,max_delta,max_variation_stat_error,max_var,systematic)
#        if verbose: print name,length,fs,fserr,systematic
        h_syst.SetBinContent(length, 1, systematic)
    h_syst.Write()

  
outfile.Close()

tfile.Close()

for f in filelist:
    f.Close()

print "Done"
