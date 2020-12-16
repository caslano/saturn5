
#ifndef BOOST_MPL_SET_C_HPP_INCLUDED
#define BOOST_MPL_SET_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/set.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_SET_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(set,BOOST_MPL_LIMIT_SET_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_SET_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(set,BOOST_MPL_LIMIT_SET_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/set/AUX778076_SET_C_HEADER)
#   undef AUX778076_SET_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/set.hpp>

#   define AUX778076_SEQUENCE_NAME set_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_SET_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(set,n),_c)
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_SET_C_HPP_INCLUDED

/* set_c.hpp
TjgGmdSB6flMo8puZd1JeOVV+FI8d71fLfueASywXMB4DQJegG2ckUo84RyS0tXMa5Mzry/PvEox8z4+GVCkTiEwRLpXnpLGdPf3TuP/UhcHegJgYIg5nalczdO8gJ9SII0vZWl88HlgWp2ewtrogT1I8jukBx1tBKkdl/er+A95YvzGKYunhPl5IDFmHetbb7+mY30r5LP76MyJIRW55/WEHZYvHYJ50ynYeeXx/WsrGYjqKZnTwTnzHRYNH4p4OII1dXSbY2vRpGZv+HksOa061PTRXnUzD+KU+CAuVPjUKfnvVIQ3c1QPZFQeQmPgSedzSp84hcLpnAv3iPrRuFYyMwHz2IzDd3Eudrl2eUnj7CJknNUqVPdLnXts0/FCgoTpntjkem4qN+s4FY0QHShMav11QIKePWIMXctSV2Hu18/Sfwq7eOYsz/CoIIxhCSwbaj4Wo8A+IaZDBZztrZrVimY940GzIh8Yg4UQuVLxFeHJwcu0cbhKUFxpCSfoW2GFakzFuenJ3YQKY+v2LvkohhQG5ihSAMZCT+5ZGixluXZMvHsiWxEVuasPMY610G3jchR+agoLFm9Hfpik7Im6RFHp7lk9bG8tc/KN4zqAe4+E+5xxgpXaqinwXPQh9dhszteUSdSjlc3d0SHGWFUSs/T7U1I8iv1Wfvo8OTzDxg962PlBhJ1AEabWtUwxgh48BV2cpUAIkZg6T2TLcWzlDGldu71I29PspbW/wx0WDUZRT294oZamxLCOWZZWeQXPQPXaT9uJeqg4UXj7O4qvPC2EdF2YGkXnp6zN1zGSLAaj7QdVlJz8piNpAJsMGtnECFbPiUbuwpSRez4eueMZOW10Kqg35K+bap7ECSg3uOlawkjAVRPw6ay4kIRVcEYGoyMY2LG1gTm0CZFz/rRopCekjPSz8UiPJ7JCeOh/q8Am6KkY6/8Ftv37Fv7vNRXTw4lNvd2/9tEjLL/KjKZH0hFag93ijhtu+UeFKCEwGJM5UGAug4DlsbxQZ4pyYvnzBJ3E7DaMoz7BFxEyDrs40rgjcAbNls3ByYiaQeVGCrDDJHfxrN3upKsHFeyNyLyR5M+a6o0iczeR+eiozG6V+U1kfhNbijdF5g/Q1EbFEBvBEBtJKVQ0yVN9KOGIBaFxg+smkQXvHus98hbRYNgfFrM+WPEKbtFzidA7E3u2qx7EAj2IeitDdCtrrvjm5qNtHTeV0lTxlvWunqJ7h7LjIdFuOi/qRPnnSIH2NSgYXuPL+uiUx7va767dRIDELhFrBOxVcQ8T8nhXeyhi0EDKcbmYFviWLkwVLvwineWURgKTXtpIa4wN6jR3e83X2ZXdmkZRqcgJGkW0MHAa9/KkVwDpoQuBnOWGXe3QdITZJTY86RWvwCvTxFexq9oKeWEhPYNlmHI4uOXBimaQJ3ZtFPSo9nUV2aWCXp01rVlVPxChWyw9V1vkBAKI4EeaBzWjt5pp+1ZU4ZnnjJzVYcWReykn4iydI5Rqa9R+ew1Xv4bCxWAP2LzYWeew6YqaQTTNTWeD37QJRY5ORI1V2Qr5ygGByyVlbqUDz1PVHTrEgzLZYLbUpCTBYF2LCUN95m7Zs+QGrgEEkWrmM4RIr6b6vRhVCvM9VOkEIhfCFKaaP4CPE/xW8MJpgOcK3ABYlBlW2G+dAnCBefiKuumg80X5tRpf4YX2yCkpxjf6X/9pfcrYcwS/3ap5Ktiu0MaaJYPsrDVEVKcuKPjQKbcQmxHfGmEpmplV2Wi6uahiszdcinLN+q6CHSomTgPmWsfq2bai0sbqwyDONdSMWUoxpEHgDSHX4jLz+/9M51Bkppgbr4MyG8OuHzDXv+ZIi3k=
*/