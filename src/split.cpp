#include "split.hpp"

namespace unmulti {
std::vector<std::pair<uint32_t, std::string>> Split(const std::string &outdir, const bool compress, cxxio::In &in) {
    // Process the input
    std::string line;
    uint32_t seq_number = 0;
    std::vector<std::pair<uint32_t, std::string>> seq_names;
    cxxio::Out out;
    while(std::getline(in.stream(), line)) {
	if (!line.empty()) {
	    if (line.at(0) == '>') {
		if (seq_number > 0) {
		    out.close(); // Flush only if something has been written.
		}
		std::string outfile = outdir + '/' + std::to_string(seq_number) + ".fasta" + (compress ? ".gz" : "");
		if (compress) {
		    out.open_compressed(outfile);
		} else {
		    out.open(outfile);
		}
		seq_names.emplace_back(std::make_pair(seq_number, line.substr(1)));
		++seq_number;
	    }
	    out.stream() << line << '\n';
	}
    }
    in.close();
    out.close();
    return seq_names;
}

void FileToSeq(const std::string &outfile, const std::vector<std::pair<uint32_t, std::string>> &seq_names) {
    cxxio::Out out;
    uint32_t n_seqs = seq_names.size();
    out.open(outfile);
    for (uint32_t i = 0; i < n_seqs; ++i) {
	out << seq_names[i].first << '\t' << seq_names[i].second << (i == n_seqs - 1 ? "" : "\n");
    }
    out.stream() << std::endl;
    out.close();
}
}
