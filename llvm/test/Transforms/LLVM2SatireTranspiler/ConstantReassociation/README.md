Alives output:

----------------------------------------
define half @src(half %0) {
%1:
  %2 = fdiv half 0x4100, %0
  %3 = fmul half %2, 0x4300
  ret half %3
}
=>
define half @tgt(half %0) {
%1:
  %2 = fmul half 0x4300, 0x4100
  %3 = fdiv half %2, %0
  ret half %3
}
Transformation doesn't verify!

ERROR: Value mismatch

Example:
half %0 = #xb803 (-0.50146484375)

Source:
half %2 = #xc4fc (-4.984375)
half %3 = #xcc5c (-17.4375)

Target:
half %2 = #x4860 (8.75)
half %3 = #xcc5d (-17.453125)
Source value: #xcc5c (-17.4375)
Target value: #xcc5d (-17.453125)

Description:


Additional Notes:
This test was run with --disable-undef-input on Alive. Times out for float
Times out even for half without --disable-undef-input

Very little difference in errors. Not noticable