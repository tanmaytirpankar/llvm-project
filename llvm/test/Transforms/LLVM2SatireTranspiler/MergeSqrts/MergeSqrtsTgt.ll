@function = constant [5 x i8] c"func\00", align 1
@arg0 = constant [2 x double] [double 1.0, double 90.0]
@arg1 = constant [2 x double] [double 45.0, double 180.0]
@s = constant ptr null

declare double @sqrt(double noundef)

define double @func(double %arg0, double %arg1) {
  %m = fmul double %arg0, %arg1
  %s = call double @sqrt(double noundef %m)
  
  ret double %s
}