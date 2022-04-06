#include "extract.hpp"

#include <set>

namespace unmulti {
std::vector<std::pair<uint32_t, std::string>>Extract(const std::string &outdir, const std::vector<std::string> &outnames, const bool compress, cxxio::In &in) {
    // Hash the input names to check them quickly
    std::set<std::string> outseqs;
    for (auto val : outnames) {
	outseqs.insert(val);
    }

    // Process the input
    std::string line;
    uint32_t seq_number = 0;
    std::vector<std::pair<uint32_t, std::string>> seq_names;
    cxxio::Out out;
    bool is_in_outnames = false;
    while(std::getline(in.stream(), line)) {
	if (!line.empty()) {
	    if (line.at(0) == '>') {
		if (seq_number > 0) {
		    out.close(); // Flush only if something has been written.
		}

		const std::string &seq_name = line.substr(1);
		// Only start
		is_in_outnames = (outseqs.find(seq_name) != outseqs.end());

		if (is_in_outnames) {
		    std::string outfile = outdir + '/' + std::to_string(seq_number) + ".fasta" + (compress ? ".gz" : "");
		    if (compress) {
			out.open_compressed(outfile);
		    } else {
			out.open(outfile);
		    }
		    seq_names.emplace_back(std::make_pair(seq_number, line.substr(1)));
		}
		++seq_number;
	    }
	    if (is_in_outnames) {
		out.stream() << line << '\n';
	    }
	}
    }
    in.close();
    out.close();
    return seq_names;
}
}
