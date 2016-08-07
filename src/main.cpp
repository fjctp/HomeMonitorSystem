#include <csignal>
#include "easylogging++.h"

#include "Settings.hpp"
#include "SettingsParser.hpp"
#include "Nest.hpp"

using namespace std;

INITIALIZE_EASYLOGGINGPP

void signal_handler(int parameter) {

}

void el_setup() {
  el::Configurations defaultConf;

  // global
  defaultConf.setGlobally(
    el::ConfigurationType::Format, "%datetime [%level] %msg");

  // debug
  defaultConf.set(el::Level::Debug,
    el::ConfigurationType::Format, "%datetime (%thread) [%level] %msg");

  // debug
  defaultConf.set(el::Level::Warning,
    el::ConfigurationType::Format, "%datetime (%thread) [%level] %msg");

  el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
  el::Loggers::reconfigureLogger("default", defaultConf);
}

int main(int argc, char* argv[])
{
  el_setup();

  SettingsParser sp;
  sp.parse(argc, argv);
  Setting sc = sp.get();
  
  LOG(INFO) << "system started";
  //LOG(INFO) << sc; // TODO: print settings

  Nest nest;
  nest.start(sc);

  return EXIT_SUCCESS;
}