# unmulti - extract individual sequeunces from a fasta file
unmulti is a tool for splitting fasta files containing several
sequences into many files containing just one sequence, or for
extracting a list of sequences from the same file. The tool supports
input compression in .gz, .bz2, or .xz formats, and output
compression in .gz format.

## Installation
### Compiling from source
#### Requirements
- c++11 compliant compiler.
- cmake v2.8.2 or newer.
- git.
- Internet access.

### How-to
Clone the repository, enter the directory and run

```
mkdir build
cd build
cmake ..
make
```

this will download the necessary dependencies and compile the unmulti executable in build/bin/.

## Usage
```
unmulti -f <input multifasta> -o <output directory (default: working directory)
```

### Example
#### Split a multifasta
Running unmulti on an input file `in.fasta` with the following contents

```
>seq_1
AAACGT
>seq_2
GGGTAC
```

will produce files `0.fasta` and `1.fasta` in the output directory with contents

```
>seq_1
AAACGT
```

and

```
>seq_2
GGGTAC
```

#### Extract specific sequence(s)
Running `unmulti -f in.fasta --extract seq_2` on the example input
above will extract only the sequence starting at `>seq_2`. Multiple
sequences can be supplied by delimiting them with `,`. Running
`unmulti -f in.fasta --extract seq_2,seq_1` will extract both
sequences from the example input.

#### Other options
The input file can be supplied compressed in the zlib/libbz2/liblzma
format depending on what was supported on the machine that unmulti was
compiled on. Adding the `--compress` toggle will compress the output
files using zlib.

Adding the `-t number_to_sequence.tsv` argument will write a table
linking the output filenames to their sequence names to the supplied
argument. In the example above, running `unmulti -f in.fasta -t
number_to_sequence.tsv` would produce the following file

```
0	seq_1
1	seq_2
```

If your sequeunces begin with some other character than '>', the
`--seq-start` option can be used to change the character. For example, running
`unmulti -f in.fasta --seq-start @` would make unmulti compatible with
a file in the following format

```
@read_1
CGCCTAC
+
GGFGGCD
@read_2
TGAGCCA
+
FFGFG=G
```

### Accepted flags/parameters
unmulti accepts the following flags/parameters:

```
-f            Input multifasta.
-o            Output directory (default: working directory)
-t            Write a table linking the output filenames to sequence names to the argument filename.
--compress    Compress the output files with zlib (default: false)
--extract     Extract only the named sequence(s). Multiple sequences should be delimited by ','.
--seq-start   Sequence begin character (default: '>')
```

## License
The source code from this project is subject to the terms of the MIT
license. A copy of the MIT license is supplied with the project, or
can be obtained at
[https://opensource.org/licenses/MIT](https://opensource.org/licenses/MIT).
