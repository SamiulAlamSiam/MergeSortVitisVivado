/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void mergeSort(signed int *llvm_cbe_arr, signed int llvm_cbe_n);
void group3(signed int *llvm_cbe_array, signed int llvm_cbe_array_size, signed int *llvm_cbe_output);


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

void mergeSort(signed int *llvm_cbe_arr, signed int llvm_cbe_n) {
  static  unsigned long long aesl_llvm_cbe_temp_count = 0;
  signed int llvm_cbe_temp[30];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge33_count = 0;
  unsigned int llvm_cbe_storemerge33;
  unsigned int llvm_cbe_storemerge33__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa29_count = 0;
  unsigned int llvm_cbe__2e_lcssa29;
  unsigned int llvm_cbe__2e_lcssa29__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa28_count = 0;
  unsigned int llvm_cbe__2e_lcssa28;
  unsigned int llvm_cbe__2e_lcssa28__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  unsigned int llvm_cbe_tmp__5;
  unsigned int llvm_cbe_tmp__5__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  unsigned int llvm_cbe_tmp__6;
  unsigned int llvm_cbe_tmp__6__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  unsigned int llvm_cbe_tmp__7;
  unsigned int llvm_cbe_tmp__7__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  unsigned int llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e__count = 0;
  unsigned int llvm_cbe__2e_;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond20_count = 0;
  bool llvm_cbe_or_2e_cond20;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge25_2e_lcssa_count = 0;
  unsigned int llvm_cbe_storemerge25_2e_lcssa;
  unsigned int llvm_cbe_storemerge25_2e_lcssa__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa19_count = 0;
  unsigned int llvm_cbe__2e_lcssa19;
  unsigned int llvm_cbe__2e_lcssa19__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa18_count = 0;
  unsigned int llvm_cbe__2e_lcssa18;
  unsigned int llvm_cbe__2e_lcssa18__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge2521_count = 0;
  unsigned int llvm_cbe_storemerge2521;
  unsigned int llvm_cbe_storemerge2521__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  unsigned int llvm_cbe_tmp__11;
  unsigned int llvm_cbe_tmp__11__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  unsigned int llvm_cbe_tmp__12;
  unsigned int llvm_cbe_tmp__12__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  unsigned long long llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  signed int *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  unsigned long long llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  signed int *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  unsigned long long llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  signed int *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  unsigned int llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  unsigned long long llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  signed int *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_be17_count = 0;
  unsigned int llvm_cbe__2e_be17;
  unsigned int llvm_cbe__2e_be17__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_storemerge25_2e_be_count = 0;
  unsigned int llvm_cbe_storemerge25_2e_be;
  unsigned int llvm_cbe_storemerge25_2e_be__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_be_count = 0;
  unsigned int llvm_cbe__2e_be;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_or_2e_cond_count = 0;
  bool llvm_cbe_or_2e_cond;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa13_count = 0;
  unsigned int llvm_cbe__2e_lcssa13;
  unsigned int llvm_cbe__2e_lcssa13__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge2314_count = 0;
  unsigned int llvm_cbe_storemerge2314;
  unsigned int llvm_cbe_storemerge2314__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  unsigned int llvm_cbe_tmp__25;
  unsigned int llvm_cbe_tmp__25__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned int llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  unsigned long long llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  signed int *llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  unsigned long long llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  signed int *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  unsigned int llvm_cbe_tmp__33;
  unsigned int llvm_cbe_tmp__33__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  unsigned int llvm_cbe_tmp__34;
  unsigned int llvm_cbe_tmp__34__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  unsigned long long llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  signed int *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  unsigned long long llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  signed int *llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa_count = 0;
  unsigned int llvm_cbe__2e_lcssa;
  unsigned int llvm_cbe__2e_lcssa__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge18_count = 0;
  unsigned int llvm_cbe_storemerge18;
  unsigned int llvm_cbe_storemerge18__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  unsigned int llvm_cbe_tmp__44;
  unsigned int llvm_cbe_tmp__44__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  unsigned long long llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  signed int *llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  unsigned long long llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  signed int *llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond36_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge26_count = 0;
  unsigned int llvm_cbe_storemerge26;
  unsigned int llvm_cbe_storemerge26__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  unsigned long long llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  signed int *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  signed int *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  unsigned int llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  unsigned int llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @mergeSort\n");
  if ((((signed int )llvm_cbe_n) > ((signed int )1u))) {
    goto llvm_cbe__2e_preheader27_2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge35;
  }

llvm_cbe__2e_preheader27_2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = add nsw i32 %%n, -1, !dbg !5 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_26_count);
  llvm_cbe_tmp__1 = (unsigned int )((unsigned int )(llvm_cbe_n&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__1&4294967295ull)));
  llvm_cbe_storemerge33__PHI_TEMPORARY = (unsigned int )1u;   /* for PHI node */
  goto llvm_cbe__2e_preheader27;

  do {     /* Syntactic loop '.preheader27' to make GCC happy */
llvm_cbe__2e_preheader27:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge33 = phi i32 [ 1, %%.preheader27.lr.ph ], [ %%75, %%._crit_edge  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_storemerge33_count);
  llvm_cbe_storemerge33 = (unsigned int )llvm_cbe_storemerge33__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge33 = 0x%X",llvm_cbe_storemerge33);
printf("\n = 0x%X",1u);
printf("\n = 0x%X",llvm_cbe_tmp__57);
}
  if ((((signed int )llvm_cbe_storemerge33) < ((signed int )llvm_cbe_n))) {
    goto llvm_cbe__2e_lr_2e_ph30;
  } else {
    llvm_cbe__2e_lcssa29__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    llvm_cbe__2e_lcssa28__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_preheader7;
  }

llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = shl nsw i32 %%storemerge33, 1, !dbg !6 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_236_count);
  llvm_cbe_tmp__57 = (unsigned int )llvm_cbe_storemerge33 << 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
  if ((((signed int )llvm_cbe_tmp__57) < ((signed int )llvm_cbe_n))) {
    llvm_cbe_storemerge33__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__57;   /* for PHI node */
    goto llvm_cbe__2e_preheader27;
  } else {
    goto llvm_cbe__2e__crit_edge35;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge26 = phi i32 [ %%74, %%.lr.ph ], [ 0, %%.preheader  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_storemerge26_count);
  llvm_cbe_storemerge26 = (unsigned int )llvm_cbe_storemerge26__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge26 = 0x%X",llvm_cbe_storemerge26);
printf("\n = 0x%X",llvm_cbe_tmp__56);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = sext i32 %%storemerge26 to i64, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_217_count);
  llvm_cbe_tmp__52 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge26);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = getelementptr inbounds [30 x i32]* %%temp, i64 0, i64 %%70, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_218_count);
  llvm_cbe_tmp__53 = (signed int *)(&llvm_cbe_temp[(((signed long long )llvm_cbe_tmp__52))
#ifdef AESL_BC_SIM
 % 30
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__52));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__52) < 30)) fprintf(stderr, "%s:%d: warning: Read access out of array 'temp' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = load i32* %%71, align 4, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_219_count);
  llvm_cbe_tmp__54 = (unsigned int )*llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = getelementptr inbounds i32* %%arr, i64 %%70, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_220_count);
  llvm_cbe_tmp__55 = (signed int *)(&llvm_cbe_arr[(((signed long long )llvm_cbe_tmp__52))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%72, i32* %%73, align 4, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_221_count);
  *llvm_cbe_tmp__55 = llvm_cbe_tmp__54;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = add nsw i32 %%storemerge26, 1, !dbg !7 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_222_count);
  llvm_cbe_tmp__56 = (unsigned int )((unsigned int )(llvm_cbe_storemerge26&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__56&4294967295ull)));
  if (((llvm_cbe_tmp__56&4294967295U) == (llvm_cbe_n&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge26__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__56;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e_preheader:
  llvm_cbe_storemerge26__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_lr_2e_ph;

llvm_cbe__2e_preheader7:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa29 = phi i32 [ 0, %%.preheader27 ], [ %%.lcssa, %%._crit_edge12  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_lcssa29_count);
  llvm_cbe__2e_lcssa29 = (unsigned int )llvm_cbe__2e_lcssa29__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa29 = 0x%X",llvm_cbe__2e_lcssa29);
printf("\n = 0x%X",0u);
printf("\n.lcssa = 0x%X",llvm_cbe__2e_lcssa);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa28 = phi i32 [ 0, %%.preheader27 ], [ %%58, %%._crit_edge12  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_lcssa28_count);
  llvm_cbe__2e_lcssa28 = (unsigned int )llvm_cbe__2e_lcssa28__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa28 = 0x%X",llvm_cbe__2e_lcssa28);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__42);
}
  if ((((signed int )llvm_cbe__2e_lcssa29) < ((signed int )llvm_cbe_n))) {
    goto llvm_cbe__2e_lr_2e_ph9;
  } else {
    goto llvm_cbe__2e_preheader;
  }

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__58:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = phi i32 [ %%storemerge33, %%.lr.ph30 ], [ %%59, %%._crit_edge12  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_38_count);
  llvm_cbe_tmp__5 = (unsigned int )llvm_cbe_tmp__5__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__5);
printf("\nstoremerge33 = 0x%X",llvm_cbe_storemerge33);
printf("\n = 0x%X",llvm_cbe_tmp__43);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = phi i32 [ 0, %%.lr.ph30 ], [ %%.lcssa, %%._crit_edge12  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__6 = (unsigned int )llvm_cbe_tmp__6__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__6);
printf("\n = 0x%X",0u);
printf("\n.lcssa = 0x%X",llvm_cbe__2e_lcssa);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = phi i32 [ 0, %%.lr.ph30 ], [ %%58, %%._crit_edge12  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__7 = (unsigned int )llvm_cbe_tmp__7__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__7);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__42);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = add nsw i32 %%9, -1, !dbg !6 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__8 = (unsigned int )((unsigned int )(llvm_cbe_tmp__5&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__8&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = add i32 %%11, %%storemerge33, !dbg !6 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__9 = (unsigned int )((unsigned int )(llvm_cbe_tmp__7&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge33&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__9&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = add i32 %%4, %%13, !dbg !6 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__10 = (unsigned int )((unsigned int )(llvm_cbe_tmp__2&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__9&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__10&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%. = select i1 %%15, i32 %%14, i32 %%2, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e__count);
  llvm_cbe__2e_ = (unsigned int )(((((signed int )llvm_cbe_tmp__10) < ((signed int )llvm_cbe_n))) ? ((unsigned int )llvm_cbe_tmp__10) : ((unsigned int )llvm_cbe_tmp__1));
if (AESL_DEBUG_TRACE)
printf("\n. = 0x%X\n", llvm_cbe__2e_);
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond20 = and i1 %%16, %%1 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_or_2e_cond20_count);
  llvm_cbe_or_2e_cond20 = (bool )(((((signed int )llvm_cbe_tmp__7) <= ((signed int )llvm_cbe_tmp__8)) & (((signed int )llvm_cbe_tmp__9) <= ((signed int )llvm_cbe__2e_)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond20 = 0x%X\n", llvm_cbe_or_2e_cond20);
  if (llvm_cbe_or_2e_cond20) {
    llvm_cbe_storemerge2521__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__7;   /* for PHI node */
    llvm_cbe_tmp__11__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__9;   /* for PHI node */
    llvm_cbe_tmp__12__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__6;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph23;
  } else {
    llvm_cbe_storemerge25_2e_lcssa__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__7;   /* for PHI node */
    llvm_cbe__2e_lcssa19__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__9;   /* for PHI node */
    llvm_cbe__2e_lcssa18__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__6;   /* for PHI node */
    goto llvm_cbe__2e_critedge_2e_preheader;
  }

llvm_cbe__2e__crit_edge12:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa = phi i32 [ %%.lcssa13, %%.preheader10 ], [ %%54, %%.lr.ph11  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_lcssa_count);
  llvm_cbe__2e_lcssa = (unsigned int )llvm_cbe__2e_lcssa__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa = 0x%X",llvm_cbe__2e_lcssa);
printf("\n.lcssa13 = 0x%X",llvm_cbe__2e_lcssa13);
printf("\n = 0x%X",llvm_cbe_tmp__39);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = add nsw i32 %%., 1, !dbg !7 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_172_count);
  llvm_cbe_tmp__42 = (unsigned int )((unsigned int )(llvm_cbe__2e_&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__42&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = add nsw i32 %%58, %%storemerge33, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_173_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(llvm_cbe_tmp__42&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge33&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__43) < ((signed int )llvm_cbe_n))) {
    llvm_cbe_tmp__5__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__43;   /* for PHI node */
    llvm_cbe_tmp__6__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa;   /* for PHI node */
    llvm_cbe_tmp__7__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__42;   /* for PHI node */
    goto llvm_cbe_tmp__58;
  } else {
    llvm_cbe__2e_lcssa29__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa;   /* for PHI node */
    llvm_cbe__2e_lcssa28__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__42;   /* for PHI node */
    goto llvm_cbe__2e_preheader7;
  }

llvm_cbe__2e_preheader10:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa13 = phi i32 [ %%.lcssa18, %%.critedge.preheader ], [ %%44, %%.critedge  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_lcssa13_count);
  llvm_cbe__2e_lcssa13 = (unsigned int )llvm_cbe__2e_lcssa13__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa13 = 0x%X",llvm_cbe__2e_lcssa13);
printf("\n.lcssa18 = 0x%X",llvm_cbe__2e_lcssa18);
printf("\n = 0x%X",llvm_cbe_tmp__30);
}
  if ((((signed int )llvm_cbe__2e_lcssa19) > ((signed int )llvm_cbe__2e_))) {
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa13;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge12;
  } else {
    llvm_cbe_tmp__33__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa19;   /* for PHI node */
    llvm_cbe_tmp__34__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa13;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph11;
  }

llvm_cbe__2e_critedge_2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge25.lcssa = phi i32 [ %%11, %%8 ], [ %%storemerge25.be, %%.backedge  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_storemerge25_2e_lcssa_count);
  llvm_cbe_storemerge25_2e_lcssa = (unsigned int )llvm_cbe_storemerge25_2e_lcssa__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge25.lcssa = 0x%X",llvm_cbe_storemerge25_2e_lcssa);
printf("\n = 0x%X",llvm_cbe_tmp__7);
printf("\nstoremerge25.be = 0x%X",llvm_cbe_storemerge25_2e_be);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa19 = phi i32 [ %%13, %%8 ], [ %%.be17, %%.backedge  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_lcssa19_count);
  llvm_cbe__2e_lcssa19 = (unsigned int )llvm_cbe__2e_lcssa19__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa19 = 0x%X",llvm_cbe__2e_lcssa19);
printf("\n = 0x%X",llvm_cbe_tmp__9);
printf("\n.be17 = 0x%X",llvm_cbe__2e_be17);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa18 = phi i32 [ %%10, %%8 ], [ %%.be, %%.backedge  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_lcssa18_count);
  llvm_cbe__2e_lcssa18 = (unsigned int )llvm_cbe__2e_lcssa18__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa18 = 0x%X",llvm_cbe__2e_lcssa18);
printf("\n = 0x%X",llvm_cbe_tmp__6);
printf("\n.be = 0x%X",llvm_cbe__2e_be);
}
  if ((((signed int )llvm_cbe_storemerge25_2e_lcssa) > ((signed int )llvm_cbe_tmp__8))) {
    llvm_cbe__2e_lcssa13__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa18;   /* for PHI node */
    goto llvm_cbe__2e_preheader10;
  } else {
    llvm_cbe_storemerge2314__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge25_2e_lcssa;   /* for PHI node */
    llvm_cbe_tmp__25__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa18;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  }

  do {     /* Syntactic loop '.lr.ph23' to make GCC happy */
llvm_cbe__2e_lr_2e_ph23:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2521 = phi i32 [ %%storemerge25.be, %%.backedge ], [ %%11, %%8  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_storemerge2521_count);
  llvm_cbe_storemerge2521 = (unsigned int )llvm_cbe_storemerge2521__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge2521 = 0x%X",llvm_cbe_storemerge2521);
printf("\nstoremerge25.be = 0x%X",llvm_cbe_storemerge25_2e_be);
printf("\n = 0x%X",llvm_cbe_tmp__7);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = phi i32 [ %%.be17, %%.backedge ], [ %%13, %%8  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__11 = (unsigned int )llvm_cbe_tmp__11__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__11);
printf("\n.be17 = 0x%X",llvm_cbe__2e_be17);
printf("\n = 0x%X",llvm_cbe_tmp__9);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = phi i32 [ %%.be, %%.backedge ], [ %%10, %%8  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__12 = (unsigned int )llvm_cbe_tmp__12__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__12);
printf("\n.be = 0x%X",llvm_cbe__2e_be);
printf("\n = 0x%X",llvm_cbe_tmp__6);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = sext i32 %%storemerge2521 to i64, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__13 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge2521);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds i32* %%arr, i64 %%21, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__14 = (signed int *)(&llvm_cbe_arr[(((signed long long )llvm_cbe_tmp__13))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__13));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load i32* %%22, align 4, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_77_count);
  llvm_cbe_tmp__15 = (unsigned int )*llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = sext i32 %%19 to i64, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__16 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds i32* %%arr, i64 %%24, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__17 = (signed int *)(&llvm_cbe_arr[(((signed long long )llvm_cbe_tmp__16))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__16));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = load i32* %%25, align 4, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_80_count);
  llvm_cbe_tmp__18 = (unsigned int )*llvm_cbe_tmp__17;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
  if ((((signed int )llvm_cbe_tmp__15) > ((signed int )llvm_cbe_tmp__18))) {
    goto llvm_cbe_tmp__59;
  } else {
    goto llvm_cbe_tmp__60;
  }

llvm_cbe__2e_backedge:
if (AESL_DEBUG_TRACE)
printf("\n  %%.be17 = phi i32 [ %%33, %%32 ], [ %%19, %%28  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_be17_count);
  llvm_cbe__2e_be17 = (unsigned int )llvm_cbe__2e_be17__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.be17 = 0x%X",llvm_cbe__2e_be17);
printf("\n = 0x%X",llvm_cbe_tmp__22);
printf("\n = 0x%X",llvm_cbe_tmp__11);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge25.be = phi i32 [ %%storemerge2521, %%32 ], [ %%29, %%28  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_storemerge25_2e_be_count);
  llvm_cbe_storemerge25_2e_be = (unsigned int )llvm_cbe_storemerge25_2e_be__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge25.be = 0x%X",llvm_cbe_storemerge25_2e_be);
printf("\nstoremerge2521 = 0x%X",llvm_cbe_storemerge2521);
printf("\n = 0x%X",llvm_cbe_tmp__19);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.be = add nsw i32 %%20, 1, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe__2e_be_count);
  llvm_cbe__2e_be = (unsigned int )((unsigned int )(llvm_cbe_tmp__12&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n.be = 0x%X\n", ((unsigned int )(llvm_cbe__2e_be&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%or.cond = and i1 %%36, %%3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_or_2e_cond_count);
  llvm_cbe_or_2e_cond = (bool )(((((signed int )llvm_cbe_storemerge25_2e_be) <= ((signed int )llvm_cbe_tmp__8)) & (((signed int )llvm_cbe__2e_be17) <= ((signed int )llvm_cbe__2e_)))&1);
if (AESL_DEBUG_TRACE)
printf("\nor.cond = 0x%X\n", llvm_cbe_or_2e_cond);
  if (llvm_cbe_or_2e_cond) {
    llvm_cbe_storemerge2521__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge25_2e_be;   /* for PHI node */
    llvm_cbe_tmp__11__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_be17;   /* for PHI node */
    llvm_cbe_tmp__12__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_be;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph23;
  } else {
    llvm_cbe_storemerge25_2e_lcssa__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge25_2e_be;   /* for PHI node */
    llvm_cbe__2e_lcssa19__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_be17;   /* for PHI node */
    llvm_cbe__2e_lcssa18__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_be;   /* for PHI node */
    goto llvm_cbe__2e_critedge_2e_preheader;
  }

llvm_cbe_tmp__60:
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = add nsw i32 %%storemerge2521, 1, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2521&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = sext i32 %%20 to i64, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__20 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = getelementptr inbounds [30 x i32]* %%temp, i64 0, i64 %%30, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__21 = (signed int *)(&llvm_cbe_temp[(((signed long long )llvm_cbe_tmp__20))
#ifdef AESL_BC_SIM
 % 30
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__20));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__20) < 30 && "Write access out of array 'temp' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%23, i32* %%31, align 4, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_98_count);
  *llvm_cbe_tmp__21 = llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__15);
  llvm_cbe__2e_be17__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__11;   /* for PHI node */
  llvm_cbe_storemerge25_2e_be__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__19;   /* for PHI node */
  goto llvm_cbe__2e_backedge;

llvm_cbe_tmp__59:
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = add nsw i32 %%19, 1, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__22 = (unsigned int )((unsigned int )(llvm_cbe_tmp__11&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__22&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = sext i32 %%20 to i64, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__23 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = getelementptr inbounds [30 x i32]* %%temp, i64 0, i64 %%34, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__24 = (signed int *)(&llvm_cbe_temp[(((signed long long )llvm_cbe_tmp__23))
#ifdef AESL_BC_SIM
 % 30
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__23));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__23) < 30 && "Write access out of array 'temp' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%26, i32* %%35, align 4, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_109_count);
  *llvm_cbe_tmp__24 = llvm_cbe_tmp__18;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
  llvm_cbe__2e_be17__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__22;   /* for PHI node */
  llvm_cbe_storemerge25_2e_be__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge2521;   /* for PHI node */
  goto llvm_cbe__2e_backedge;

  } while (1); /* end of syntactic loop '.lr.ph23' */
  do {     /* Syntactic loop '.critedge' to make GCC happy */
llvm_cbe__2e_critedge:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2314 = phi i32 [ %%40, %%.critedge ], [ %%storemerge25.lcssa, %%.critedge.preheader  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_storemerge2314_count);
  llvm_cbe_storemerge2314 = (unsigned int )llvm_cbe_storemerge2314__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge2314 = 0x%X",llvm_cbe_storemerge2314);
printf("\n = 0x%X",llvm_cbe_tmp__26);
printf("\nstoremerge25.lcssa = 0x%X",llvm_cbe_storemerge25_2e_lcssa);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = phi i32 [ %%44, %%.critedge ], [ %%.lcssa18, %%.critedge.preheader  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__25 = (unsigned int )llvm_cbe_tmp__25__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__25);
printf("\n = 0x%X",llvm_cbe_tmp__30);
printf("\n.lcssa18 = 0x%X",llvm_cbe__2e_lcssa18);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = add nsw i32 %%storemerge2314, 1, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__26 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2314&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__26&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = sext i32 %%storemerge2314 to i64, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__27 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge2314);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = getelementptr inbounds i32* %%arr, i64 %%41, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__28 = (signed int *)(&llvm_cbe_arr[(((signed long long )llvm_cbe_tmp__27))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__27));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = load i32* %%42, align 4, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__29 = (unsigned int )*llvm_cbe_tmp__28;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = add nsw i32 %%39, 1, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__30 = (unsigned int )((unsigned int )(llvm_cbe_tmp__25&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__30&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = sext i32 %%39 to i64, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__31 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = getelementptr inbounds [30 x i32]* %%temp, i64 0, i64 %%45, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__32 = (signed int *)(&llvm_cbe_temp[(((signed long long )llvm_cbe_tmp__31))
#ifdef AESL_BC_SIM
 % 30
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__31));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__31) < 30 && "Write access out of array 'temp' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%43, i32* %%46, align 4, !dbg !3 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_144_count);
  *llvm_cbe_tmp__32 = llvm_cbe_tmp__29;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
  if ((((signed int )llvm_cbe_tmp__26) > ((signed int )llvm_cbe_tmp__8))) {
    llvm_cbe__2e_lcssa13__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    goto llvm_cbe__2e_preheader10;
  } else {
    llvm_cbe_storemerge2314__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__26;   /* for PHI node */
    llvm_cbe_tmp__25__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__30;   /* for PHI node */
    goto llvm_cbe__2e_critedge;
  }

  } while (1); /* end of syntactic loop '.critedge' */
  do {     /* Syntactic loop '.lr.ph11' to make GCC happy */
llvm_cbe__2e_lr_2e_ph11:
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = phi i32 [ %%50, %%.lr.ph11 ], [ %%.lcssa19, %%.preheader10  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_147_count);
  llvm_cbe_tmp__33 = (unsigned int )llvm_cbe_tmp__33__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__33);
printf("\n = 0x%X",llvm_cbe_tmp__35);
printf("\n.lcssa19 = 0x%X",llvm_cbe__2e_lcssa19);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = phi i32 [ %%54, %%.lr.ph11 ], [ %%.lcssa13, %%.preheader10  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_148_count);
  llvm_cbe_tmp__34 = (unsigned int )llvm_cbe_tmp__34__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__34);
printf("\n = 0x%X",llvm_cbe_tmp__39);
printf("\n.lcssa13 = 0x%X",llvm_cbe__2e_lcssa13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = add nsw i32 %%48, 1, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(llvm_cbe_tmp__33&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__35&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = sext i32 %%48 to i64, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_156_count);
  llvm_cbe_tmp__36 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = getelementptr inbounds i32* %%arr, i64 %%51, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_157_count);
  llvm_cbe_tmp__37 = (signed int *)(&llvm_cbe_arr[(((signed long long )llvm_cbe_tmp__36))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__36));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = load i32* %%52, align 4, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_158_count);
  llvm_cbe_tmp__38 = (unsigned int )*llvm_cbe_tmp__37;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = add nsw i32 %%49, 1, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__39 = (unsigned int )((unsigned int )(llvm_cbe_tmp__34&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__39&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = sext i32 %%49 to i64, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_167_count);
  llvm_cbe_tmp__40 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = getelementptr inbounds [30 x i32]* %%temp, i64 0, i64 %%55, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_168_count);
  llvm_cbe_tmp__41 = (signed int *)(&llvm_cbe_temp[(((signed long long )llvm_cbe_tmp__40))
#ifdef AESL_BC_SIM
 % 30
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__40));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__40) < 30 && "Write access out of array 'temp' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%53, i32* %%56, align 4, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_169_count);
  *llvm_cbe_tmp__41 = llvm_cbe_tmp__38;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__38);
  if ((((signed int )llvm_cbe_tmp__35) > ((signed int )llvm_cbe__2e_))) {
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__39;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge12;
  } else {
    llvm_cbe_tmp__33__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__35;   /* for PHI node */
    llvm_cbe_tmp__34__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__39;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph11;
  }

  } while (1); /* end of syntactic loop '.lr.ph11' */
  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph30:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = add i32 %%storemerge33, -1, !dbg !6 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__2 = (unsigned int )((unsigned int )(llvm_cbe_storemerge33&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__2&4294967295ull)));
  llvm_cbe_tmp__5__PHI_TEMPORARY = (unsigned int )llvm_cbe_storemerge33;   /* for PHI node */
  llvm_cbe_tmp__6__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  llvm_cbe_tmp__7__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__58;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__61:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge18 = phi i32 [ %%.lcssa28, %%.lr.ph9 ], [ %%69, %%61  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_storemerge18_count);
  llvm_cbe_storemerge18 = (unsigned int )llvm_cbe_storemerge18__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge18 = 0x%X",llvm_cbe_storemerge18);
printf("\n.lcssa28 = 0x%X",llvm_cbe__2e_lcssa28);
printf("\n = 0x%X",llvm_cbe_tmp__51);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = phi i32 [ %%.lcssa29, %%.lr.ph9 ], [ %%66, %%61  for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__44 = (unsigned int )llvm_cbe_tmp__44__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%X",llvm_cbe_tmp__44);
printf("\n.lcssa29 = 0x%X",llvm_cbe__2e_lcssa29);
printf("\n = 0x%X",llvm_cbe_tmp__48);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = sext i32 %%storemerge18 to i64, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_189_count);
  llvm_cbe_tmp__45 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge18);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__45);
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = getelementptr inbounds i32* %%arr, i64 %%63, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_190_count);
  llvm_cbe_tmp__46 = (signed int *)(&llvm_cbe_arr[(((signed long long )llvm_cbe_tmp__45))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__45));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = load i32* %%64, align 4, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_191_count);
  llvm_cbe_tmp__47 = (unsigned int )*llvm_cbe_tmp__46;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = add nsw i32 %%62, 1, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__48 = (unsigned int )((unsigned int )(llvm_cbe_tmp__44&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__48&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = sext i32 %%62 to i64, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_200_count);
  llvm_cbe_tmp__49 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = getelementptr inbounds [30 x i32]* %%temp, i64 0, i64 %%67, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_201_count);
  llvm_cbe_tmp__50 = (signed int *)(&llvm_cbe_temp[(((signed long long )llvm_cbe_tmp__49))
#ifdef AESL_BC_SIM
 % 30
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__49));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__49) < 30 && "Write access out of array 'temp' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%65, i32* %%68, align 4, !dbg !4 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_202_count);
  *llvm_cbe_tmp__50 = llvm_cbe_tmp__47;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = add nsw i32 %%storemerge18, 1, !dbg !7 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_203_count);
  llvm_cbe_tmp__51 = (unsigned int )((unsigned int )(llvm_cbe_storemerge18&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__51&4294967295ull)));
  if (((llvm_cbe_tmp__51&4294967295U) == (llvm_cbe_tmp__4&4294967295U))) {
    goto llvm_cbe__2e_preheader;
  } else {
    llvm_cbe_storemerge18__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__51;   /* for PHI node */
    llvm_cbe_tmp__44__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__48;   /* for PHI node */
    goto llvm_cbe_tmp__61;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_lr_2e_ph9:
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add i32 %%.lcssa28, %%n, !dbg !5 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__3 = (unsigned int )((unsigned int )(llvm_cbe__2e_lcssa28&4294967295ull)) + ((unsigned int )(llvm_cbe_n&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__3&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sub i32 %%6, %%.lcssa29, !dbg !5 for 0x%I64xth hint within @mergeSort  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__4 = (unsigned int )((unsigned int )(llvm_cbe_tmp__3&4294967295ull)) - ((unsigned int )(llvm_cbe__2e_lcssa29&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__4&4294967295ull)));
  llvm_cbe_storemerge18__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa28;   /* for PHI node */
  llvm_cbe_tmp__44__PHI_TEMPORARY = (unsigned int )llvm_cbe__2e_lcssa29;   /* for PHI node */
  goto llvm_cbe_tmp__61;

  } while (1); /* end of syntactic loop '.preheader27' */
llvm_cbe__2e__crit_edge35:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @mergeSort}\n");
  return;
}


void group3(signed int *llvm_cbe_array, signed int llvm_cbe_array_size, signed int *llvm_cbe_output) {
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  unsigned long long llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  signed int *llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  signed int *llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  unsigned int llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @group3\n");
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @mergeSort(i32* %%array, i32 %%array_size), !dbg !3 for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_254_count);
   /*tail*/ mergeSort((signed int *)llvm_cbe_array, llvm_cbe_array_size);
if (AESL_DEBUG_TRACE) {
printf("\nArgument array_size = 0x%X",llvm_cbe_array_size);
}
  if ((((signed int )llvm_cbe_array_size) > ((signed int )0u))) {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ %%6, %%.lr.ph ], [ 0, %%0  for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",llvm_cbe_tmp__66);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sext i32 %%storemerge1 to i64, !dbg !3 for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_262_count);
  llvm_cbe_tmp__62 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds i32* %%array, i64 %%2, !dbg !3 for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_263_count);
  llvm_cbe_tmp__63 = (signed int *)(&llvm_cbe_array[(((signed long long )llvm_cbe_tmp__62))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__62));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load i32* %%3, align 4, !dbg !3 for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_264_count);
  llvm_cbe_tmp__64 = (unsigned int )*llvm_cbe_tmp__63;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds i32* %%output, i64 %%2, !dbg !3 for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_265_count);
  llvm_cbe_tmp__65 = (signed int *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__62))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__62));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%4, i32* %%5, align 4, !dbg !3 for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_266_count);
  *llvm_cbe_tmp__65 = llvm_cbe_tmp__64;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__64);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add nsw i32 %%storemerge1, 1, !dbg !4 for 0x%I64xth hint within @group3  --> \n", ++aesl_llvm_cbe_267_count);
  llvm_cbe_tmp__66 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__66&4294967295ull)));
  if (((llvm_cbe_tmp__66&4294967295U) == (llvm_cbe_array_size&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__66;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @group3}\n");
  return;
}

