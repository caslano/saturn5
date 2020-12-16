
#ifndef BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_REPEAT(n,f,param) \
    BOOST_PP_CAT(BOOST_MPL_PP_REPEAT_,n)(f,param) \
    /**/
    
#   define BOOST_MPL_PP_REPEAT_0(f,p)
#   define BOOST_MPL_PP_REPEAT_1(f,p) f(0,0,p)
#   define BOOST_MPL_PP_REPEAT_2(f,p) f(0,0,p) f(0,1,p)
#   define BOOST_MPL_PP_REPEAT_3(f,p) f(0,0,p) f(0,1,p) f(0,2,p)
#   define BOOST_MPL_PP_REPEAT_4(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p)
#   define BOOST_MPL_PP_REPEAT_5(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p)
#   define BOOST_MPL_PP_REPEAT_6(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p)
#   define BOOST_MPL_PP_REPEAT_7(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p)
#   define BOOST_MPL_PP_REPEAT_8(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p)
#   define BOOST_MPL_PP_REPEAT_9(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p) f(0,8,p)
#   define BOOST_MPL_PP_REPEAT_10(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p) f(0,8,p) f(0,9,p)

#else 

#   include <boost/preprocessor/repeat.hpp>

#   define BOOST_MPL_PP_REPEAT(n,f,param) \
    BOOST_PP_REPEAT(n,f,param) \
    /**/

#endif 

#define BOOST_MPL_PP_REPEAT_IDENTITY_FUNC(unused1, unused2, x) x

#endif // BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED

/* repeat.hpp
jaPxYxyLn+Eb+AWOw68wiX/f45t4DcfjbZyA93EyPsYpWIx1mIouOA1L4nQsjzOwKc7EljgLW+NbOAhn41CcjwtxIS7FRbgaF+N+XIKf4VI8isvwK1yOp3EFnsM1eAPX4h1cjwXJ73exCr6HtXAD1sGN6IWb0Ac3oz9uwT64FfvhNgzG7TgYP8Ak3Inj8UOcgsn4Fu7FdfgxbsJ9uBv346d4AA/jwcy+J7jmtNyHyyHpi+UwlsXPZT7f3HINKNeGzGc4//aSenVM6tWX6IwnsDR+jRXx7+iNp7ApnsF2eBbPy/eSr+P3+A88j/Ys+4KU70VshD+gL17CVpiCHfBH7IY/oT/+jOGYilH4C8bjVRyN13Aa/opv4XVcijdxI97CZLyNRzANT+AdPIX38Qo+wOv4Gz7Fh5ibDEzHYvgIS+JjLIf/wFfxD/RBXS7qqx1gP8yNQZgHIzAvxmA+1KMDzsT8OBcL4jZ0xM+wEB7GwvgtFsHvsBgqJ5+vYF50RgcsjoWxBBZHF3TBklgbS2FdLI1eWAZfw3LYDMtjJ3TD7lgBA7ESDsVXMRqrIPWI9Ms1qly7phDKSdseZUiVdjGX0Rmvohtew/r4KzbCG9gNb2IvvIMJeBdH4T2ch/dxET7AFfgbbsOHuAvTcTc+wq/wMZ5EXW7KVQHzKtsIOqI9FsY86Ix5sRbmwzrogO5YAD2xIPpgYWyFTtgWiyL5QcGbrkHZF0l+lFXSLfnRUvKjLTpje2yNHWX9O+Fg7IyR2AXfRD+cjN1kvbvjGuyJBzEAD2Nv/A774Hnsi7exH97HQFTWayC6Yxh2wsEYjuEYjREYi0NwOA7F0RiJYzEKJ2IszsE4nI/xaGyXLNeSOFH2S+p2ydUlH2qiM9bBWlgX62A9bIf1MRQb4BBsiJHojXHog3p8DYdjYxyLvpiEzZD0sF5yTSfXekp6ahjzxTDM5XeFcQFWw4XYEhdjP1yCIbgM38DluARX4Cpcie/iKtyFq3E3rse/4QY8hFvwHG7F73EbpuMOVBL3AebFXVgId2Nx3IOV8RB2wcMYg5/jSDyCSXgUJ+EXOAW/xGl4HGfgCXwXT+ERPI0n8Qyew7N4Eb/Bn/AcpuL3mI7n8QlewELKfhyL4SV0wRTJb9Ii12fsOyS/a/N/PSpD8dzSvhidsSSWxVJYHUujN5bBNlgWe2I57IflMQgrYAJWxFFYGefhq7gIq+GHWB33Yg08hTXxW6yFF7E23sY6eB/r4m/ojgVIswcWQU+sivWwFjZEX/TGVuiDvbAR9sMmOBqb49vYAndgS9yPrfAAtsYvsQ3+jG3xMrbDp9ge/8AOqBxHO2F+7IxO2BXLYHcsj/5oaI+vk2s2/Ey2w6K4QLbDkdJ+MxGr4iisi6OxKY7BFjgWe+Eb2BfH4SBMwsn4Js7A8bgMJ+AanIS7cTLuxSm4D2fhJ/gWckx4ZtvElHn0gU5wnl9A500IIIyZX+B/uo+sF227uJx8ya79otvkAla3Ydw8v0CO2zEeZJ4LBN0C5iW0JUQSFhMOEVIJjgttbRltg23IyfAX9P8fHRGv/9P9/yvP+P9Q3i0+rJxqG5YZGBvo4eOpMz6/n8ffvD/X/C0wfhjncIZ5c3lzjmb2d09PL5k3N39brf2bal57/n7O/O/1G8i8UZzkjTyi+Ztq3jzMm2z293repnjz8rcNRzV/U82bj787fKH+e31PD5nXgb8N1P5N5lXaK6whPzoa/x4cMZg3otVZpvpNqvY3svrq36RrfyOrqf6N4zHNb2R11L9xy+Y3skqG9hGHiusyniunyX2CAgQ7ggPBkXU+2T+zzYHeXRai3Jc3rNjz7xern13722UfR4o=
*/