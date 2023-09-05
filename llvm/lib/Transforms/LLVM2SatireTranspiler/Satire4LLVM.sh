SAT_ROOT=temp

OPT=$HOME/Documents/Tools/llvm-project/build/bin/opt
OPT_PASSES=llvm2satire

# Run opt with llvm2satire pass if $1 is a .ll file
if [[ $1 == *.ll ]]; then
  $OPT $OPT_FLAGS -passes=$OPT_PASSES $1
fi

# Run Satire on the transpiled code
