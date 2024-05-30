# Endian-Converter
Simplest version of an endian converter. I made it in a couple hours dude.

## Usage:

This is a command line tool. All you have to do is run it like this:
```bash
# Swaps the 16bit endianness of inputFile.bin and puts the result into outputFile.bin
endianConv.exe 16 inputFile.bin outputFile.bin
# Same as above but 32bit
endianConv.exe 32 inputFile.bin outputFile.bin
```

If you somehow forget this, just run the program with no arguments

```bash
endianConv.exe
Usage: <exe> <stride: 16|32> <inputPath> <outputPath>
```

# Compiling:
I made a Makefile. All you have to do is run the one you want.
```bash
make release	# for release mode
make clean		# to clean
make debug		# for gdb stuff
```

of course, optionally you can use `-j4` or `-j8` because the compilation process takes 
ages, I know.

Alright thank you love you gnight :purple_heart: