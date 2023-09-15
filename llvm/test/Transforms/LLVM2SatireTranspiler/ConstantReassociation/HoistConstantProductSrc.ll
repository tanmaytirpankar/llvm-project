@function = constant [5 x i8] c"func\00", align 1
@arg0 = constant [2 x half] [half -10000.0, half -0.5]
@b = constant ptr null

define half @func(half %arg0) {
  %a = fdiv half 2.5, %arg0
  %b = fmul half %a, 3.5
  ret half %b
}