///////////////////////////////////////////////////////////////////////////////
/// \file local.hpp
/// Contains macros to ease the generation of repetitious code constructs
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_LOCAL_MACRO
# error "local iteration target macro is not defined"
#endif

#ifndef BOOST_PROTO_LOCAL_LIMITS
# define BOOST_PROTO_LOCAL_LIMITS (1, BOOST_PROTO_MAX_ARITY)
#endif

#ifndef BOOST_PROTO_LOCAL_typename_A
# define BOOST_PROTO_LOCAL_typename_A BOOST_PROTO_typename_A
#endif

#ifndef BOOST_PROTO_LOCAL_A
# define BOOST_PROTO_LOCAL_A BOOST_PROTO_A_const_ref
#endif

#ifndef BOOST_PROTO_LOCAL_A_a
# define BOOST_PROTO_LOCAL_A_a BOOST_PROTO_A_const_ref_a
#endif

#ifndef BOOST_PROTO_LOCAL_a
# define BOOST_PROTO_LOCAL_a BOOST_PROTO_ref_a
#endif

#define BOOST_PP_LOCAL_LIMITS BOOST_PROTO_LOCAL_LIMITS

#define BOOST_PP_LOCAL_MACRO(N)       \
  BOOST_PROTO_LOCAL_MACRO(            \
      N                               \
    , BOOST_PROTO_LOCAL_typename_A    \
    , BOOST_PROTO_LOCAL_A             \
    , BOOST_PROTO_LOCAL_A_a           \
    , BOOST_PROTO_LOCAL_a             \
  )                                   \
  /**/

#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_PROTO_LOCAL_MACRO
#undef BOOST_PROTO_LOCAL_LIMITS
#undef BOOST_PROTO_LOCAL_typename_A
#undef BOOST_PROTO_LOCAL_A
#undef BOOST_PROTO_LOCAL_A_a
#undef BOOST_PROTO_LOCAL_a

/* local.hpp
HIOFuF9OMQoePLKwzn95Q/mcz5NMVNy2tmGwEMdvKU9FLJ5tRFJmeaqYdFBwqed8Gs3bFdT7g90F7N+j3vn6BZTXBWGlVkYJyHd3ctz5h90tcMxSvEhYY1Kd1XXDcgf/HzPHOn+Y8jpXVaXMbdnm7STr8/N2iEse5SuYUA2vhJFsE7QRd/5bzlCHkO8Po7ZuGs2l1XByhyWp19a/iPLNmS7yKuN5AWsk2tC5E8nxPgh5V/Esgi9Fh1G+K4+k+aYZqExzzqbTQbcghVhDFCsKxpOqbHRWe/tr9Drl44/DZtHZFwCvjs/jKB+Zsqo0Oa9NscBHGu/qI/ABPcaur2aUzzmthcxyyY6cyOC6EC8gnAkollsm6tSarC7ZhofjLuVPJ3MvNeMD3BJwN2B413wf5beey0Y7Xv7lNvJL9uGorg0TWVIJ3lQs2dlpM30ypEH/Phd94b0Eel1y2OVmR9THyp8jfoKllpdJklqmXuBk+j62uBupMLfDQevoyGmke4O3Vt8yxbeCR8VnjIoXVVNoxcTEDburxyHuA3FJBcZbzzvjykXsGHcpH1GyWom6MW773508f4rNOp05i7MpOgCCKeGPq0Sm/zbK50JZ5fDIlDJvcrsT4lEOg60YxfOalblqslJq5o2HYJJdnr/7uDje4yMciXNGDMfRlymf85muKy55CXPeTdne3Ptm1GYZS1We6SxLvS3X6L92AuhyhlhflFfFTKOSqk5SyBhU1KZoXBneuh8dy0YyozOZlGU75NHjB0240sU3vydNe6EsGs2rNGmz2qW2lVjPh1C80szqrEkzoVnbcZDEX3iOjn01V2GmeqUF52Rvc8SIXu8h5dWwstBlppIMMvfKQZP9MUpzCjyDRvnnTOuaF0Vl3SkUFrKQDIOcwNIGI3y+YLTj/Bzu+b12y7k0suJFWwCRnFiG30RlyJhOLOdWJ/9PGdZwf1yN3xfTWlZKGmd3E3Q1FmyIdmgay2rwyF1UOVwYRFzkLs2MpjEM7PXSzComkl4SBw1vWzQNl4wbm7qMKja84qb+uB1YYnfoTMgXbeXfhWkxJr8ojU4r5m5ATggw2sEkmNeHV/v+4Qphm5TB1b3NyF6xaJnQ9w335ShtwlKeV8JUJSPqGXk3mBNsk+/F7ch1VZVNCWoe+25iwjNmOHIlIWZULy+u0lwKWzIY+rob+JhXOBPSdOclr/MqFRK6bAuGSHSu+yvFXqySqixMxUSCYNTbvjeuF9cD/GAwdsEqnf788aFrKLiHhfhzM6/zZU06AMv5FRKvPSc0kMLNl6cVTGs6Ouoxz5D2hWlL23qqe1zjXjk26Kq+ZLags729f9jpqr6C0JWzj1QbydbclcoWYl63FBPrJr+ZYC5tiS1Q051CPWYg/en03t7R4VARWj9dyT7+IOgxEjyA5obPW8GXy2K+UPhQv48u0rH9Blj2Ty4vU+CFeX2R4AJxpWunGz+X0uMKIeZ7S9sSkF2f/LjD+CdKiBQ/V0YN+oO0XkZDLM+k8h3shh7m2sXfv/tx7PNu35tHDw5JrH7kfaqHhfE4d0yCysoH451Ol/RBx8FuHBWKg6+d4ji2Owcv91R3/nKfrszWxtN8FyGP7z2XYkK7X0H6AeGxoZ5sy74voOPYrh1o2Pcv7NG8Yq0/5YEOCJbz2z0cdO3cw0Lg9YM+Jtj7t29EAffTRdzpZX4GfrkER/0MYP1/08c50RZc07A/f7/YPsBrLsj0AjxoRsT/8QR8d4yRkH0YW3+J8E+aR96cy7y8DvMQsXd+XtyX/snBOQV5weDytYHRkmDv+R+xlhdkHN1vGRYO59dWLmN7PqSPcWb5bujPYSsceT2qh4NBMQcdhXg=
*/