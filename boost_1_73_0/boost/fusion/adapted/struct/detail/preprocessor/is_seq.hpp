/*=============================================================================
    BOOST_PP_VARIADICS version of BOOST_PP_IS_SEQ inspired from 
    boost/mpl/aux_/preprocessor/is_seq.hpp, original copyrights goes to :

    Copyright Paul Mensonides 2003
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_PP_IS_SEQ(seq) BOOST_PP_CAT(BOOST_FUSION_PP_IS_SEQ_,       \
    BOOST_FUSION_PP_IS_SEQ_0 seq BOOST_PP_RPAREN())

#define BOOST_FUSION_PP_IS_SEQ_0(...)                                           \
    BOOST_FUSION_PP_IS_SEQ_1(__VA_ARGS__

#define BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(...)                                    \
    0

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_0                         \
    BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_1(...)                    \
    1

#endif // BOOST_PP_VARIADICS

#endif

/* is_seq.hpp
iz8beppqPy7olmX89JjYiVW1bW0RdbyVqntxxE18Q9jZ+9QqLO4Ym0j+D9XTAyWvTSGGo0weeEr0aoftw59hxnvj5VlXYqiWef820Uu2dD5Txher5M7bENfob8TcIfhOaPwBdS/1v7Gfx9Fz65MfLaVPfofED+fxpBSrFx8uqV5DePTO7BL9w+1tLPnjM2BpFy+ENpF44CtT3xbQaZ9ZlEtNzV9pe6k3HJHyY/LFEbF/ozMO
*/