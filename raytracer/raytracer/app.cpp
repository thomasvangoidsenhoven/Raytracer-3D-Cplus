#ifndef TEST_BUILD

#include "easylogging++.h"
#include "version.h"
#include "command-line-parser.h"
#include "logging.h"
#include "demos/demos.h"
#include "pipeline/pipelines.h"
#include "util/beep.h"
#include "scripting/scripting.h"
#include "performance/performance.h"
#include <assert.h>
//#include <iostream>
#include "json/json.hpp"
using json = nlohmann::json;
using namespace raytracer;

namespace
{
    void render_script(const std::string& filename)
    {
        TIMED_SCOPE(timer, "Rendering script");

#       ifdef EXCLUDE_SCRIPTING
        LOG(ERROR) << "Cannot run script - scripting was excluded";
        abort();
#       endif

        if (filename != "-")
        {
            LOG(INFO) << "Rendering " << filename;

            raytracer::scripting::run_script(filename);
        }
        else
        {
            LOG(INFO) << "Rendering script from STDIN";

            std::string script;

            while (!std::cin.eof())
            {
                std::string line;
                std::getline(std::cin, line);
                script += line + "\n";
            }

            raytracer::scripting::run(script);
        }
    }

    void quiet()
    {
        logging::quiet();
    }

    void show_version()
    {
        LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
    }

    void emit_beep()
    {
        ::beep();
    }

    void print_statistics()
    {
        performance::print_statistics(std::cerr);
    }

    void enable_3dstudio_output()
    {
        logging::enable("studio");

        LOG(INFO) << "Activated 3d studio mode";
    }
}

/// <summary>
/// Processes the command line arguments.
/// The command line arguments form a series of commands to be executed in order by the ray tracer.
/// For example, using "-s a.chai -s b.chai --beep" tells
/// the ray tracer to render a.chai, then b.chai, and finally emit a beep (so that you know it's done working.)
/// </summary>
void process_command_line_arguments(int argc, char** argv)
{
    CommandLineParser parser;

    parser.register_processor("-s", render_script);
    parser.register_processor("--quiet", quiet);
    parser.register_processor("--version", show_version);
    parser.register_processor("--beep", emit_beep);
    parser.register_processor("--statistics", print_statistics);
    parser.register_processor("--studio", enable_3dstudio_output);

    parser.process(argc, argv);
	
	//testing shenanigans
	
	// deserialize from standard input
	//std::cout << "give json plox" << std::endl;
	//json j;
	//std::cin >> j;

	// serialize to standard output
	//auto output = j["name"];
	//LOG(INFO) << "name is: " << output;

	//std::cin.get();
	
    LOG(INFO) << "Terminated successfully";
	//std::cin.get();
}

int main(int argc, char** argv)
{
    TIMED_FUNC(timer);

    logging::configure();
    
    process_command_line_arguments(argc, argv);

    // Renders a basic sample and writes it to a file named "test.wif". You may have to look around a bit to find it, but it will definitely be somewhere in the project's directory structure. You can use an absolute path to avoid having to look for it.
	//demos::test_sample(pipeline::wif("test.wif"));
}

#endif
