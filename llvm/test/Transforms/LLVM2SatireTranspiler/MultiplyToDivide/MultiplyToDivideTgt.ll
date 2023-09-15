@function = constant [5 x i8] c"func\00", align 1
@arg0 = constant [2 x double] [double 3.0, double 100.0]
@arg1 = constant [2 x double] [double 0.2, double 10.0]
@arg2 = constant [2 x double] [double 2.0, double 50.0]
@y = constant ptr null

define half @func(half %arg0, half %arg1, half %arg2) {
  %x = fmul half %arg1, %arg2
  %y = fdiv half %arg0, %x
  ret half %y
}