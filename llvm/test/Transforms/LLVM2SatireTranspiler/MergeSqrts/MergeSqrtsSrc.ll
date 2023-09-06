@func = constant [4 x i8] c"src\00", align 1
@arg0 = constant [2 x double] [double 1.0, double 90.0]
@arg1 = constant [2 x double] [double 45.0, double 180.0]
@r = constant ptr null

declare double @sqrt(double noundef)

define double @src(double %arg0, double %arg1) {
  %x = call double @sqrt(double %arg0)
  %y = call double @sqrt(double %arg1)
  %r = fmul double %x, %y
  ret double %r
}