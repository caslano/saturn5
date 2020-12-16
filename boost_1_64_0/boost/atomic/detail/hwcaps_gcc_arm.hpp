/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_arm.hpp
 *
 * This header defines hardware capabilities macros for ARM
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__) && defined(__arm__) && (BOOST_ATOMIC_DETAIL_ARM_ARCH+0) >= 6

#if BOOST_ATOMIC_DETAIL_ARM_ARCH > 6
// ARMv7 and later have dmb instruction
#define BOOST_ATOMIC_DETAIL_ARM_HAS_DMB 1
#endif

#if defined(__ARM_FEATURE_LDREX)

#if (__ARM_FEATURE_LDREX & 1)
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB 1
#endif
#if (__ARM_FEATURE_LDREX & 2)
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH 1
#endif
#if (__ARM_FEATURE_LDREX & 8)
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD 1
#endif

#else // defined(__ARM_FEATURE_LDREX)

#if !(defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6Z__))

// ARMv6k and ARMv7 have 8 and 16-bit ldrex/strex variants, but at least GCC 4.7 fails to compile them. GCC 4.9 is known to work.
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXB_STREXB 1
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXH_STREXH 1
#endif

#if !(((defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6ZK__)) && defined(__thumb__)) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7M__))
// ARMv6k and ARMv7 except ARMv7-M have 64-bit ldrex/strex variants.
// Unfortunately, GCC (at least 4.7.3 on Ubuntu) does not allocate register pairs properly when targeting ARMv6k Thumb,
// which is required for ldrexd/strexd instructions, so we disable 64-bit support. When targeting ARMv6k ARM
// or ARMv7 (both ARM and Thumb 2) it works as expected.
#define BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD 1
#endif

#endif // !(defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6Z__))

#endif // defined(__ARM_FEATURE_LDREX)

#endif // defined(__GNUC__) && defined(__arm__) && (BOOST_ATOMIC_DETAIL_ARM_ARCH+0) >= 6

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_ARM_HPP_INCLUDED_

/* hwcaps_gcc_arm.hpp
Wu8yz6fKdeLVL8RHjn4XeS+MNU287yLki+Svfd9mZbtv32aXNQurWweOE55rrnO0y2/NOr5TGKzsN054nsew1ptd/uOE71XuRKX/Rpqpz7eOZZzw3bv8xgnj33+c8GSutaV1eCerHSdMmiz5QLwcI16bzbvaBNo8H5urA2xeIDayRqd6/im3b61Gm80fhbD5A5vN1Q42e+pgM2nCvgVh2VzZNtDmAmxO3u1doye8ckbffzw4bq/NzzjYfA7ntc3i327zljrY7FTOz7jYvD0m0OaF5vuUtjm8cvbYbL4lhM032Wz2ONj8SB1slnJ2s/n/eo2Qb2stkO+rPv5+4xpNi81qdmfXPrN3FPW5YJvbGIK6j2n4T1s7xHmNELcxCnVfO8SyT7F6z8tB723Zp7jM26Yk7VmF/NEW3iD65itON5hgmatwMUyEObAjLIGdYBnsAn8Ck+GzsBvcDbvDA7AHPAh7wjdgL/gWTIFHYG94ApZ42yrgAUlXNFyMGLL/biIcALvAs+GZ8DuwL0yDGXAgzIKD4IVwCFwseqvgUEl3Btwux0/AffrbXrUtqPgT+HunxL9d9m9+EibBp2Bn+BYcCJ+B2fBZOB/ugAtN/7AIvgivgq/Ae+DP4b1wN/wp3AMrxd8uuB9WwwPwj/BV+Ck8CE/B12GHKJ5RsCt8Ew6Bb4k9yfr7kG9gsccs13ho/rIk/ybANDjJ9A8nw1kwG3rgFHgDnA/XwwVwM1wEn4bLJP3fhb+AK2ANXAk/g6tgY+K8EraGV8E4uAb2hFfDfvBaOAyW8m84vA6OgAvhKJgPp8O1cDa8Hs6HK+B34c1wJbwFXgVvhdfC2+ANcD1cBzfAMihz4MkHeU+Xd32uFb+xOUdUkrh+YCP4DmwNfw07wKOwE3wX6utLwit3uL7uQK8d3Cj16DEph7thqrjPgvfC4fB+qccPSv16CM6BD8PL4RZ4DXwE3ggfhfdIOPeLW+YqyXshz3BJl3Wu0vsyV+kPsDf8QK5/3Np/dRD/fxL/H4v/Y+Ift/bP+4qr/yPi/23x/474x639e4L4/434/634r4Hp4vY0NkLOp2cefZ3GU/2nzJd3mivPGKyvbb4847RCzpkPNV9exm+FNU++IXPk6zI/nnFfzIv/758TH+7YsfrOhy8pYr44UokcQU4iMcXMc0cmIoXIuuLI+LPIL/KL/L7p/v+ieXMXmgMAGt7//7MUQ6/JvlnemZdI28c8pIk5P6BStX1Iu8e0kePGjhp5Qe58ZgkUF6TlejIWLV2g2jWuaqfaNTIs7SDiN0GvWbxSuWcYQ2XN4s1q3WTMMQy95vA1Smc830LN9LyAwaRzdgzry0sbSFoYfWmkh/YOlR6/tedvaBRo5yXYeTy4nWR/hkpzfqLdTvza7Gz2XGg72zx3euwkPY52Zso+++lIW2nL+tL8gHzO3c7c+QXLi6Vd63eqXatkSNq5vnaqO5XfJLHbG1acbqd6jvQPDLPPIw0SB2lXcfil/ZRD2nNwVAVJO1hsSNqbqnUm1AGd9jdsaa+ypX1HHdNOHKSdOCTfL/SOo5G++w9kfbDXkcamIc8HSbuqXrkFS9XFbl0X2TOvIHfponxff4CEk6rcCThTlftpS/+MZ25RkV4XWfRTlHsi7hTlft4aB/q+fo1E2EPpvKLchTqMHrq/lH6VuYuLfXmbrM5PU+4pWj9Z4vDqqzg4Njb2oijSrW2JUmsne1T8em9Dttb06abZdEtwWu853IO0boZNt1TWmT4Yyx8qP+cv8hT6+v2GKN3v2K9Tff4hdb6XHqvzunK31/cCg/it65kUqfPzje7UK/a1RIt63oFvzF6113alXOMXyDrdme51zbY=
*/