// unmulti: Split a multifasta file into many fasta files containing a single sequence. 
// https://github.com/tmaklin/unmulti
//
// MIT License
//
// Copyright (c) 2022 Tommi Mäklin (tommi@maklin.fi)
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "unmulti.hpp"

#include <string>
#include <algorithm>
#include <iostream>
#include <exception>
#include <cstdint>

#include "cxxargs.hpp"
#include "cxxio.hpp"

#include "version.h"

namespace unmulti {
bool CmdOptionPresent(char **begin, char **end, const std::string &option) {
  return (std::find(begin, end, option) != end);
}

void parse_args(int argc, char* argv[], cxxargs::Arguments &args) {
    args.add_short_argument<std::string>('f', "Input multifasta.");
    args.add_short_argument<std::string>('o', "Output directory (default: working directory)", ".");

    if (!CmdOptionPresent(argv, argv+argc, "--help")) {
	args.parse(argc, argv);
    }
}
}

int main(int argc, char* argv[]) {
    cxxargs::Arguments args("unmulti-" + std::string(UNMULTI_BUILD_VERSION), "Usage: unmulti -f <input multifasta>");

    // Parse input arguments.
    try {
	unmulti::parse_args(argc, argv, args);

	if (unmulti::CmdOptionPresent(argv, argv+argc, "--help")) {
	    std::cerr << "\n" + args.help() << '\n' << '\n';
	    return 0;
	}
    } catch (std::exception &e) {
	std::cerr << "Parsing arguments failed:\n"
		  << std::string("\t") + std::string(e.what()) + "\n"
		  << "\trun unmulti with the --help option for usage instructions.\n";
	return 1;
    }

    // Check input and output files.
    cxxio::In in;
    try {
	// Input multifasta exists
	in.open(args.value<std::string>('f'));

	// Output directory exists
	cxxio::directory_exists(args.value<std::string>('o'));
    } catch (std::exception &e) {
	std::cerr << "I/O error:\n"
		  << std::string("\t") + std::string(e.what()) + "\n"
		  << "\trun unmulti with the --help option for usage instructions.\n";
	return 1;
    }

    // Process the input
    std::string line;
    uint32_t seq_number = 0;
    cxxio::Out out;
    while(std::getline(in.stream(), line)) {
	if (line.at(0) == '>') {
	    if (seq_number > 0) {
		out.close(); // Flush only if something has been written.
	    }
	    out.open(args.value<std::string>('o') + '/' + std::to_string(seq_number) + ".fasta");
	    ++seq_number;
	}
	out.stream() << line << '\n';
    }
    in.close();
    out.close();

    return 0;
}
