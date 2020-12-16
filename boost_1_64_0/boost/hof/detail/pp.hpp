/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    pp.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_PP_H
#define BOOST_HOF_GUARD_PP_H

#define BOOST_HOF_PP_CAT(x, y) BOOST_HOF_PP_PRIMITIVE_CAT(x, y)
#define BOOST_HOF_PP_PRIMITIVE_CAT(x, y) x ## y

#define BOOST_HOF_PP_SEQ_ITERATE(...) BOOST_HOF_PP_PRIMITIVE_SEQ_ITERATE(__VA_ARGS__)
#define BOOST_HOF_PP_PRIMITIVE_SEQ_ITERATE(...) __VA_ARGS__ ## _END

// 
// BOOST_HOF_PP_NARGS returns the number of args in __VA_ARGS__
// 
#define BOOST_HOF_PP_NARGS(...) \
         BOOST_HOF_PP_DETAIL_NARG((__VA_ARGS__,BOOST_HOF_PP_DETAIL_RSEQ_N()))

#define BOOST_HOF_PP_DETAIL_NARG(args) \
        BOOST_HOF_PP_DETAIL_ARG_N args

#define BOOST_HOF_PP_DETAIL_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define BOOST_HOF_PP_DETAIL_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0 


//
// BOOST_HOF_PP_IS_PAREN is used to detect if the first token is a parenthesis.
// It expands to 1 if it is, otherwise it expands to 0.
//
#define BOOST_HOF_PP_IS_PAREN(x) BOOST_HOF_PP_IS_PAREN_CHECK(BOOST_HOF_PP_IS_PAREN_PROBE x)
#define BOOST_HOF_PP_IS_PAREN_CHECK(...) BOOST_HOF_PP_IS_PAREN_CHECK_N(__VA_ARGS__,0)
#define BOOST_HOF_PP_IS_PAREN_PROBE(...) ~, 1,
#ifndef _MSC_VER
#define BOOST_HOF_PP_IS_PAREN_CHECK_N(x, n, ...) n
#else
// MSVC workarounds
#define BOOST_HOF_PP_IS_PAREN_CHECK_RES(x) x
#define BOOST_HOF_PP_IS_PAREN_CHECK_II(x, n, ...) n
#define BOOST_HOF_PP_IS_PAREN_CHECK_I(x) BOOST_HOF_PP_IS_PAREN_CHECK_RES(BOOST_HOF_PP_IS_PAREN_CHECK_II x)
#define BOOST_HOF_PP_IS_PAREN_CHECK_N(...) BOOST_HOF_PP_IS_PAREN_CHECK_I((__VA_ARGS__))
#endif

//
// BOOST_HOF_PP_IS_1 is used to detect if the first token is a 1.
// It expands to 1 if it is, otherwise it expands to 0.
//
#define BOOST_HOF_PP_IS_1(x) BOOST_HOF_PP_IS_PAREN(BOOST_HOF_PP_CAT(BOOST_HOF_PP_IS_1_PROBE_, x))
#define BOOST_HOF_PP_IS_1_PROBE_1 ()

#define BOOST_HOF_PP_ARGS_IS_SINGLE(...) BOOST_HOF_PP_IS_1(BOOST_HOF_PP_NARGS(__VA_ARGS__))

#define BOOST_HOF_PP_EMPTY(...)
#define BOOST_HOF_PP_DEFER(...) __VA_ARGS__ BOOST_HOF_PP_EMPTY()
#define BOOST_HOF_PP_OBSTRUCT(...) __VA_ARGS__ BOOST_HOF_PP_DEFER(BOOST_HOF_PP_EMPTY)()
#define BOOST_HOF_PP_EXPAND(...) __VA_ARGS__

#define BOOST_HOF_PP_IIF(c) BOOST_HOF_PP_PRIMITIVE_CAT(BOOST_HOF_PP_IIF_, c)
#define BOOST_HOF_PP_IIF_0(t, ...) __VA_ARGS__
#define BOOST_HOF_PP_IIF_1(t, ...) t

#define BOOST_HOF_PP_WALL(...) __VA_ARGS__

#define BOOST_HOF_PP_RAIL_IIF(c) BOOST_HOF_PP_PRIMITIVE_CAT(BOOST_HOF_PP_RAIL_IIF_, c)
#define BOOST_HOF_PP_RAIL_IIF_0(t, ...) __VA_ARGS__
#define BOOST_HOF_PP_RAIL_IIF_1(t, ...) t

#define BOOST_HOF_PP_RAIL(macro) \
    BOOST_HOF_PP_RAIL_IIF(BOOST_HOF_PP_IS_PAREN(BOOST_HOF_PP_WALL(())))( \
        BOOST_HOF_PP_RAIL_ID BOOST_HOF_PP_OBSTRUCT()()(macro), \
        macro BOOST_HOF_PP_OBSTRUCT() \
    )

#define BOOST_HOF_PP_RAIL_ID() BOOST_HOF_PP_RAIL

#endif

/* pp.hpp
Zud/nFZDZu7o+A+9K+0T29k+cQPbJ36X7BN/8pk+doN9THJaDSlUhD75XB+8YTyZ4kir2cMRp2CcbDzZKU6reZQjonrqhvFkqzithgSKWGGahNOp10xK+9ih4DqSIPsHKUoCBmMjYQi04v0QfBlqPtpXKfcmCaOiizVuYJUXks1FTM55ms1c0IxL1Rj1p2h2lcB35YMcL1lrjf8M5yfNPspfRfRSjI0OGjI2Uupb9/voWvZvnWoxNOmmv34aV+iEPXg+xeTKlAGG2fuBhRd1dUeuhkZYcAwld6IZiNpXpJFQf9WowcHkdS/awD841uhQpepfRZGdVRd3hepqQy2qiLgpyWlUWN6/K11fbrSaXXe1fUNKESM4J+UdytSy4IfvmZbMVpXihosOVTfcdF+p+H6uEoFxjXYFB6PIMMjkKWOacFAv3dgV0H+vOJ/t3mYaj4/OpR7x6FB11T1WKi4sYFBlSOQ7OBo/9XbHGu26xnrVx/QFxxqzgnMZy0rpwpb/BfqwbZipfF9xOcI/xm70igmYceQsZEcC1IcpAcRuYfu8A8iLFHOaSsWXYsf4qj3/eqcXcZ/jAAvNH8vANkjp18Ns0Vm/KP+VFeeXbGDjOOzbR29HZruTp0zI379SzM3fD+rox+ED+a/okoRFpqTJCnmXcHK+I+imDb4n3gZ58hhH8LC0Qe6xj5lgDx6UNsg9jjETHMFd0ga5J2nMhKTgj9tkU6UZPcodPp6PEch+SXYCe6bH5s0IN9alD8nZe8X0qjGFet+qAnehngmM+4OaYwFb2qTjvhJM5p+AO2LPXwO1Z6DAcPXp7J1zqNhbPEMMQq+krOIr18xtDYFAwZdtCIdfJABnMAMwvF/Pzj+1ImNDl+qfxeD7CcF3fP6+lSJ/H8D7y/CJ/FN6sjw70PuhVDznNxtS8zb0AHXkT2Ne0DPqxj9XcN7KpKqGrLoJ8teerDEvBF/0hD6wB3/eViO10noLEX7ZrgCLHIQ+ta9oB3vpejq2JxJECm5O5aite2kJrfZsJR+dTosZa4HwptKSnIYr/LAhVzfennPICzm1qxghyWw9edeQf7jo/aiU7PD5yWFJ3rHSWjp5ew2Nua9cT3z5zVC8z+5GW/Gnbnmd8mUdvJ5v6TK6pWdjtnvJ+/k6w4KGE5W56fZ4FlXgxvCJd/n9ydf0JYnX9KSc2DWtA81/rpu6pReWBHJLxfrcWJdqlwIk7IMBSE/+IHWGDQeP4fc5hoixXWHk6V5x//GoUdcocAk6DFJcgldoKqRq2OwEHGACZFz4heITR5FbQv8cJTVa96H3IbvJCkLC3c/GetqbnGU9zS/G9DO9EIH4HVDE71WgYySfx130i1VSDrc1BO3m7W1LS2jvhb5me1Zi+9czjPbat749aZ/5OQyizpntJVQh7kubVWKIEP3FxiSH0Amnzp7n3I3s+GDdSSI7rhxHrrzXfcK/88hNz7pP+ffF68B94l8X0JWz3kWF1s9yrPfa109JkhtVWhpotf1d6WrB4w6dcEuNb+mQPdgvPD2dFJw6RT2keGscp/kHgkcQYYRCJ52Vl4ZOpK7dT164qwo62ILPzEjaB/+Ap9Q6/FHI43Ya2YsJc6bkEwhLhH8Tkh1tOqpZ2UvM7xv/HsokY3BQ3KSzZ0CxlpvT1Q1UYIyXsAblhSeKD/7mUlhc51IS4256bGTi+XAlc46yGuVTkSRqSHEjE7JCh1CCDlCV80IjJ59sUbf+e8JkQieS1r4VzIBBk7Hxef+WLfMS+kO+2vrmH9cz4zO8YWRA2reQdg+wgWulp8QSsXIZcCE3K1x765x5tHYDiAKsh2Hp0CMp/zU9P7wn562cBl5fSfgz3p0=
*/