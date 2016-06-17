# MT2PlotUtils.py
# various plotting utilities

def GetCRName(cr):
    names = {"crrlbase": "Removed Lepton CR",
             "crgjbase": "#gamma+jets CR",
             "crdybase": "Z #rightarrow #font[12]{l}^{#plus}#font[12]{l}^{#minus} CR",
             "crslbase": "Single Lepton CR",
             "crslwjets": "Single Lepton CR (wjets)",
             "crslttbar": "Single Lepton CR (ttbar)",
             "crslelbase": "Single Lepton CR (els)",
             "crslmubase": "Single Lepton CR (mus)",
             "crqcdbaseJ": "QCD Monojet CR",
             }

    # use the above name if defined, otherwise use cr itself
    return names.get(cr,cr)

def GetSampleName(sample):
    names = {"wjets_ht": "W+Jets",
             "wjets_incl": "W+Jets",
             "dyjetsll_ht": "Z(#font[12]{ll})+Jets",
             "dyjetsll_incl": "Z(#font[12]{ll})+Jets",
             "zinv_ht": "Z(#nu#nu)+Jets",
             "top": "Top",
             "gjets_ht": "Prompt #gamma",
             "fakephoton": "Fake #gamma",
             "fragphoton": "Frag. #gamma",
             "qcd_ht": "QCD",
             }

    # use the above name if defined, otherwise use sample itself
    return names.get(sample,sample)

def GetVarName(var):
    names = {"ht": "H_{T}",
             "met": "E_{T}^{miss}",
             "mt2": "M_{T2}",
             "mt2bins": "M_{T2}",
             "nJet30": "N(jet)",
             "nBJet20": "N(b jet)",
             "letppt": "P_{T}(lep)",
             "lepeta": "#eta(lep)",
             "nlepveto": "N(lep veto)",
             "zllmass": "m_{#font[12]{ll}}",
             "gammaPt": "P_{T}(#gamma)",
             "gammaEta": "#eta(#gamma)",
             "J1pt": "Subleading jet p_{T}",
             }

    # use the above name if defined, otherwise use var itself
    return names.get(var,var)

def GetUnit(vn):
    noUnit = ["nJet","nBJet","eta","nlep","drMin","chiso"]
    for s in noUnit:
        if s in vn:
            return None

    return "GeV"

def GetSubtitles(dirname):
    if dirname=="crqcdbaseJ":
        return ["p_{T}(jet1) > 200 GeV", "N(jet) = 2"]
    if dirname[-1:]=="J":
        return ["H_{T} > 200 GeV","M_{T2} > 200 GeV", "1j"]
    if dirname[-2:]=="VL":
        return ["200 < H_{T} < 450 GeV","M_{T2} > 200 GeV", "#geq 2j"]
    if dirname[-1:]=="L":
        return ["450 < H_{T} < 575 GeV","M_{T2} > 200 GeV", "#geq 2j"]
    if dirname[-1:]=="M":
        return ["575 < H_{T} < 1000 GeV","M_{T2} > 200 GeV", "#geq 2j"]
    if dirname[-2:]=="UH":
        return ["H_{T} > 1500 GeV","M_{T2} > 200 GeV", "#geq 2j"]
    if dirname[-1:]=="H":
        return ["1000 < H_{T} < 1500 GeV","M_{T2} > 200 GeV", "#geq 2j"]

    return ["H_{T} > 200 GeV","M_{T2} > 200 GeV", "#geq 2j"]

def Rebin(h_bkg_vec, h_data, r):
    for h in h_bkg_vec:
        h.Rebin(r)
    h_data.Rebin(r)

