
#include <iostream>
#include <cstdlib>
#include "easylogging++.h"
#include "Settings.hpp"
#include "SettingsParser.hpp"

namespace po = boost::program_options;

// Constructor
SettingsParser::SettingsParser()
{
  setup();
}

// Destructor
SettingsParser::~SettingsParser()
{
}

/*
  wrapper method
  parse command line argument, read and parse yaml file
  @public
 */
void SettingsParser::parse(int argc, char* argv[]) {
  std::string config_file_path = parse_cmd(argc, argv);
  parse_yaml(config_file_path);
}

/*
  return setting data structure
  @public
 */
Setting SettingsParser::get() {
  return s;
}

/*
  define allowed command line options
  @protected
 */
void SettingsParser::setup() {
  desc.add_options()
    ("help,h", "show help message")
    ("config,c", po::value<std::string>(), "configuration file")
    ;
}

/*
  parse command line arguements and extract yaml file's location
  @protected
*/
std::string SettingsParser::parse_cmd(int argc, char* argv[]) {
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("config")) {
    return vm["config"].as<std::string>();
  }
  else if (vm.count("help")) {
    show_help_message();
    exit(EXIT_SUCCESS);
  }
  else {
    show_help_message();
    exit(EXIT_SUCCESS);
  }

}
/*
  parse command line arguements and extract yaml file's location
  @protected
*/
void SettingsParser::parse_yaml(std::string yaml_path) {
  LOG(INFO) << "Loading config file: " << yaml_path;

  YAML::Node doc;
  try {
    doc = YAML::LoadFile(yaml_path);
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
  
}
/*
  show help message
  @protected
*/
void SettingsParser::show_help_message() {
  desc.print(std::cout);
}