#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "DeTiNPlugin.h"

void DeTiNPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }
}

void DeTiNPlugin::run() {
   
}

void DeTiNPlugin::output(std::string file) {
   std::string command = "export OLDPATH=${PYTHONPATH}; export PYTHONPATH=${PYTHON2_DIST_PACKAGES}:${PYTHON2_SITE_PACKAGES}:${PYTHONPATH}; python2 plugins/DeTiN/deTiN/deTiN/deTiN.py ";
//python2 deTiN/deTiN.py --mutation_data_path example_data/HCC_10_90.call_stats.pon_removed.txt --cn_data_path example_data/HCC-1143_100_T-sim-final.acs.seg --tumor_het_data example_data/HCC_10_90.tumor.hets.tsv --normal_het_data example_data/HCC_10_90.normal.hets.tsv --exac_data_path example_data/exac.pickle_high_af --output_name 10_percent_TiN_simulation --indel_data_path example_data/MuTect2.call_stats.txt --indel_data_type MuTect2 --output_dir example_data/

 command += " --mutation_data_path "+PluginManager::addPrefix(parameters["mutation_data_path"]);
 command += " --tumor_het_data "+PluginManager::addPrefix(parameters["tumor_het_data"]);
 command += " --normal_het_data "+PluginManager::addPrefix(parameters["normal_het_data"]);
 command += " --cn_data_path "+PluginManager::addPrefix(parameters["cn_data_path"]);
 command += " --exac_data_path "+PluginManager::addPrefix(parameters["exac_data_path"]);
 command += " --output_name "+PluginManager::addPrefix(parameters["output_name"]);
 command += " --indel_data_path "+PluginManager::addPrefix(parameters["indel_data_path"]);
 command += " --indel_data_type "+parameters["indel_data_type"];
 command += " --output_dir "+file;
 //; export PYTHONPATH=OLDPATH"; 
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<DeTiNPlugin> DeTiNPluginProxy = PluginProxy<DeTiNPlugin>("DeTiN", PluginManager::getInstance());
