#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR30_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR30_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector30_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector30_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    // expand vector21 to vector30
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector30_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (21, 30)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector30_fwd.hpp
+TOLXetwzLW5fircNmbcsElJw90fat+faavhM73UHfswV/2dKHm+LHk2IzWUfHexbOgS0zyVMQsKivPyqs1Xv13RN3tv11NW5vvIozjfUu36q7Zrj7pdxjx3muT5Y+V70jxPe6Hd/zyX+sgzSgY87yL12YH0DMuW+8iz2JFzVXkaz0t2Z5HHPj0g5egk9w7akfYq1+rGckgxMrPyspx8Evzf/iW6sjSSssj501Afkbd474P9vDf0DpNyVPsd9R/27gQ+iuoO4PhyiFzBcKcYYcMZ7nBHiBDucAcIECGQhGRDQq4lCRBOIwIioAYFSy1qqiioVCNiReqRKioW1ChosVKLioqAGDWl0Wrtb3b/mWN3luyGgO2nO5++fs0yO+/Nm2tn5v/e81QG47pvbum+P+9l3kiTPLXduep8detFpbqv1x+Ufcs0D3ZnH+p2n4d9a0Mr931rv7Jvuecpu5b3ea402bd6q/uWsRyBrd33rQPKvmVaDuV86v05ap9JOWS/Ss53Kcfa1u7b4FYKFLjaUI6ZwyfOcGwCX/bvda3Mt0HjIPd1v43/iDTLU1l1H/bnda2qXvdy3F/bczyVedyU5zgo8/iuXy4+yte4MvP4MU/xTr7Hj/nafs88bsr3+KhfKk7MU1xWrqM/ubNPHNjWbs+PDRsVXeh0+jcFe6sXl1Vokfc3GCD9eLF4y1o5Kv5Wi3aG+DG2w0+wC36KI/EzjMEvcB5+iUvwLG7Hr7AIz+NO/BoP4zf4BX6Hdcj3H1gfL6j9OMk7G2xCsrvEXb3OfFfhISnfG+r3SBf53svyvVfkewdRjfOS711j8r0n5HtPYhMs1vc3dZHv7ZfvPSffO6D7XuFFvve0fG+ffO8Z3feK5XutTL53hPka4JvYEt/Sfa9Uvvcrk++9wHwN8UUMwpewsr+4MvneWJP+4u6X/uIewEFYhJH4II7Ah/T1u9Dz+r4j6/uurO9Rff0u9Fzu96Xcf5FyH0fpd0+eayv34u797q2R7b8Wr8N12AvXYzjeioNxA47B23AqbkTnGC/yDBuGyXGjH+NlvIwJNAk74VTsidNwEMbgMJyBM3AW2jEWN+BsLMQ5uA3j8AGMx6cxEf+I8/ElTMZP0YYXMAWvrSX98GEq9sQ07IcLcQBm4GDMknjH4xZ5Jo0/Sb0F4RFZrxxZr1xZrzzshYtxIC7BEbgUx2M+TsTlGIMrcB6uxBRcham4GhfiTZiHN+NGXIM7cS0+iuvwKbxV6mEjHsbb8SjegWfwTizHLViBd8n6FVjk+TM+K+sXgHmyfkls36aYgq0wFYdgGkZjOmZiBmZjFt6E2Xgb2nETLsLfYg7uwlzci4tl/zlpkefNuEX2H2X/PiblqE1omxXrYShejROxPk7HRjgXAzAZm+BavAbvxqa4C5vhS9gcj2NLPImt8GsMwoa1yBubYhvshNdif7wO52E7tKEV0zEEc7E9LscOeCt2xM3YCSXul+e9ar96TJfWr164RZ7fYohsP30/dY/Icb0Lm+FuDMZHsXIsrwT5/nCpd/1YXqfIJwQ/w274OfbHLzAST+N4/BKn4hnMxLO4GM/hSjyPt+HXst+W4bP4Db6K3+I7+B2exnI8h//EWpSrAoPxe+yHP+Ag/Akj8N9SH/kWeV4LL0p9NMaMyv64pR4aYRcMwN7YBEdjIE7HZrgMm+Md2AKfwJb4DLbCZzEIn8M2Up+ppDLJf7fk3xDjJP87Jf9CbINbsB3ehb3wbhyKW3EmbsNFeA9uxl/jQ7hdvR7Js1ScaXI9Wib5LZd8VuBgXIlTcZUsJ7yW+pyU56fO5XRU9iOJcWnHfCFoxa4Ygn2wvSyvk5S3M87DLpiEXdE=
*/