#include <iostream>
#include <cstdlib>
#include "easylogging++.h"
#include "Settings.hpp"
#include "OptionsParser.hpp"

namespace po = boost::program_options;

// Constructor
OptionsParser::OptionsParser()
{
  setup();
}

// Destructor
OptionsParser::~OptionsParser()
{
}

/*
  wrapper method
  parse command line argument, read and parse yaml file
  @public
 */
Options OptionsParser::parse(int argc, char* argv[]) {
  Options opts;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  // config
  if (vm.count("config")) {
    opts.path2yaml = vm["config"].as<std::string>();
  }
  else {
    show_help_message();
    exit(EXIT_SUCCESS);
  }

  // log
  if (vm.count("log"))
    opts.path2log = vm["log"].as<std::string>();
  else
    opts.path2log = "./Nest.log";

  // help
  if (vm.count("help")) {
    show_help_message();
    exit(EXIT_SUCCESS);
  }

  return opts;
}

/*
  define allowed command line options
  @protected
 */
void OptionsParser::setup() {
  desc.add_options()
    ("help,h", "show help message")
    ("config,c", po::value<std::string>(), "configuration file")
    ("log,l", po::value<std::string>(), "log file")
    ;
}

/*
  show help message
  @protected
*/
void OptionsParser::show_help_message() {
  desc.print(std::cout);
}