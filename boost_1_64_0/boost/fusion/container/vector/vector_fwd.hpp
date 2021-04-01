/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_FORWARD_11052014_1626
#define FUSION_VECTOR_FORWARD_11052014_1626

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/vector_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    struct vector;

#define FUSION_VECTOR_N_ALIASES(z, N, d)                                    \
    template <typename ...T>                                                \
    using BOOST_PP_CAT(vector, N) = vector<T...>;

    BOOST_PP_REPEAT(51, FUSION_VECTOR_N_ALIASES, ~)

#undef FUSION_VECTOR_N_ALIASES
}}

#endif
#endif


/* vector_fwd.hpp
zRqJEbeLRu93oFsfl51P+N8mhuiaSE9W2vHNqt8Z79LKflGLrbWN7Tkh4Lh3kqaXowGk5+eovnONFrVQGAP2Osf8Q61zdVQqXxC+Q+rQXibRXEocN/SoCNwFlUf0pgeUn8/K8g4RwAYtM8AL5TH/hTiNeLWKa7e8LViZhgvXLU05zO1nWI0B6RAovzjnoo5Fu5aIBM9qK7suAUwfTbczcYJ04TisxscalX9qNc6af+UU9HNxYTPR5FE08X96LnpKCE2d750cF0O73574T2ymtGG8MGDlGONZTKCtxolBxdz34LJCPmHEGw1OprmQib1Vfjh2Y06/XJAQ4+38+42W8QR4VwatbuSr9TrW7rXmE+XiSz7ycUJi7oh/1xVVA3M9jFDF0fTKYxXeAG2ryuCkWWy7Dedtw9eFTUTfgulLDD/MtwKmkT74LrZQe13T4XChs3SPaYXOYYzX0UcaKu+ih9RR7b4fqlFP1cOcBjojSD+l4iPNzy5OfaHDTg4d8/g1Wzu26pBK6lm9pHSczINZVziXx1lRulWFjetz1M49mxBGNp4EWwJMoJti8A==
*/