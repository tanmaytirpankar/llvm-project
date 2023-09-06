Alives output:


----------------------------------------
define half @src(half %arg0, half %arg1, half %arg2) {
%0:
%x = fdiv half %arg0, %arg1
%y = fdiv half %x, %arg2
ret half %y
}
=>
define half @tgt(half %arg0, half %arg1, half %arg2) {
%0:
%x = fmul half %arg1, %arg2
%y = fdiv half %arg0, %x
ret half %y
}
Transformation doesn't verify!

ERROR: Value mismatch

Example:
half %arg0 = #x0036 (0.000003218650?)
half %arg1 = #xbe82 (-1.626953125)
half %arg2 = #x0029 (0.000002443790?)

Source:
half %x = #x8021 (-0.000001966953?)
half %y = #xba70 (-0.8046875)

Target:
half %x = #x8043 (-0.000003993511?)
half %y = #xba73 (-0.80615234375)
Source value: #xba70 (-0.8046875)
Target value: #xba73 (-0.80615234375)

Description:

Additional Notes:
This test was run with --disable-undef-input on Alive. Times out for float
Times out even for half without --disable-undef-input

Symengine simplifies the source expression to the target expression. So no error difference.