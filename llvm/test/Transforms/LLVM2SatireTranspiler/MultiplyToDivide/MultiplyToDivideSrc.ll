@func = constant [4 x i8] c"src\00", align 1
@arg0 = constant [2 x double] [double 3.0, double 100.0]
@arg1 = constant [2 x double] [double 0.2, double 10.0]
@arg2 = constant [2 x double] [double 2.0, double 50.0]
@y = constant ptr null

define half @src(half %arg0, half %arg1, half %arg2) {
  %x = fdiv half %arg0, %arg1
  %y = fdiv half %x, %arg2
  ret half %y
}