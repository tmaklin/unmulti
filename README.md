# unmulti - split a multifasta file into many fasta files
Note: work-in-progress!

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

### Accepted flags/parameters
unmulti accepts the following flags/parameters:

```
-f    Input multifasta.
-o    Output directory (default: working directory)
```

## License
The source code from this project is subject to the terms of the MIT
license. A copy of the MIT license is supplied with the project, or
can be obtained at
[https://opensource.org/licenses/MIT](https://opensource.org/licenses/MIT).
