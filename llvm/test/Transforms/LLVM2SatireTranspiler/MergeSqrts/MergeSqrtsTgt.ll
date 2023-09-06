@func = constant [4 x i8] c"tgt\00", align 1
@arg0 = constant [2 x float] [float 1.0, float 90.0]
@arg1 = constant [2 x float] [float 45.0, float 180.0]
@s = constant ptr null

declare float @sqrtf(float noundef)

define float @tgt(float %arg0, float %arg1) {
  %m = fmul float %arg0, %arg1
  %s = call float @sqrtf(float noundef %m)
  
  ret float %s
}