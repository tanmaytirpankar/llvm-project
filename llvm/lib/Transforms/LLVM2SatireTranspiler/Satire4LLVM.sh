SAT_ROOT=/home/tanmay/Documents/Tools/SatirePlus

OPT=$HOME/Documents/Tools/llvm-project/build/bin/opt
OPT_PASSES=llvm2satire

# Run opt with llvm2satire pass if $1 is a .ll file
if [[ $1 == *.ll ]]; then
  $OPT $OPT_FLAGS -passes=$OPT_PASSES $1
fi

# Run Satire on the transpiled code
# Create Satire input file path with name
SATIRE_INPUT_NAME="$PWD/src.txt"

# Run Satire
$SAT_ROOT/src/seesaw.py --file $SATIRE_INPUT_NAME --gverbose --error_analysis