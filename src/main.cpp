#define ELPP_NO_DEFAULT_LOG_FILE

#include <csignal>
#include <string>
#include "easylogging++.h"

#include "OptionsParser.hpp"
#include "Settings.hpp"
#include "Nest.hpp"

using namespace std;

INITIALIZE_EASYLOGGINGPP

void signal_handler(int parameter) {

}

inline void el_setup(string path2logfile);
inline Setting parseConfigFile(string path2yaml);

int main(int argc, char* argv[])
{

  OptionsParser sp;
  Options opts = sp.parse(argc, argv);

  el_setup(opts.path2log);
  Setting sc = parseConfigFile(opts.path2yaml);
  
  LOG(INFO) << "system started";
  //LOG(INFO) << sc; // TODO: print settings

  Nest nest;
  nest.start(sc);

  return EXIT_SUCCESS;
}

/****************************************************/

inline void el_setup(const string path2logfile) {
  el::Configurations defaultConf;

  // global
  defaultConf.setGlobally(
    el::ConfigurationType::Format, "%datetime [%level] %msg");
  defaultConf.setGlobally(
    el::ConfigurationType::Filename, path2logfile);
  defaultConf.setGlobally(
    el::ConfigurationType::ToFile, "true");
  defaultConf.setGlobally(
    el::ConfigurationType::MaxLogFileSize, "200000000"); // ~200MB

                                                         // debug
  defaultConf.set(el::Level::Debug,
    el::ConfigurationType::Format, "%datetime (%thread) [%level] %msg");

  // debug
  defaultConf.set(el::Level::Warning,
    el::ConfigurationType::Format, "%datetime (%thread) [%level] %msg");

  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
  el::Loggers::reconfigureLogger("default", defaultConf);
}


/*
  parse command line arguements and extract yaml file's location
*/
inline Setting parseConfigFile(const string path2yaml) {
    LOG(INFO) << "Loading config file: " << path2yaml;
    Setting s;

    YAML::Node doc;
    try {
      doc = YAML::LoadFile(path2yaml);
    }
    catch (const YAML::Exception& e) {
      std::cerr << e.what() << "\n";
      exit(EXIT_FAILURE);
    }

    try {
      doc >> s;
    }
    catch (YAML::Exception& e) {
      std::cerr << e.what() << "\n";
      exit(EXIT_FAILURE);
    }

    return s;
}
