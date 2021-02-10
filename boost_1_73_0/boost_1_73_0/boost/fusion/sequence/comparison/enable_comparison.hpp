/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ENABLE_COMPARISON_09232005_1958)
#define FUSION_ENABLE_COMPARISON_09232005_1958

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion { namespace traits
{
    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_equality
        : mpl::and_<traits::is_sequence<Seq1>, traits::is_sequence<Seq2> >
    {};

    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_comparison
        : mpl::and_<
            traits::is_sequence<Seq1>, traits::is_sequence<Seq2>
          , mpl::equal_to<result_of::size<Seq1>, result_of::size<Seq2> >
        >
    {};
}}}

#endif

/* enable_comparison.hpp
14s6ofccUcboNoWHKe4AeFjxCJjWwkOkyfFMrvhWJ5cNAxXfYqxhNQZ/GH1qzaNw7vStjPEWPxUo2FBW2EJdVFaVCtDwJxA5y0TXUCVnj86niQHUupW4pfYBiZxzx+t3nhuNjfwYcmgw0xcU6fA1N0F9ZfOoKZSnWIdh2pbZQ8K3Og8tTGBEyZOlDGcym6iEk6v2X4OP4/F18LHbvugOjYJnJHK5QQxhYyRIxTUJ30Lhu7RqmgH7BdzDRhhKbbDwnho/iDC/6vgVTW2amXKM6u6vMCj035zVdjL5h5VO+o0f1Zum6W0k3SpIPbDF+SFVs5UJVg8w9AUiDcO2OqR+rxsY6iSZrWgxxuOfEEk7jk3OkYFZz6KEJn/krSNzeQc9wj/eSo7fYilDrDqz+wBlkJ47NdK26gqYBrJxdFd5bK28ygVoaiwlxQaAzRcs+l9YluAls0LgkdHB0dtoJy23EOdqfjaA8FFgZt06bN1yKo22LqwML8rHLYCy2OWCDNVO28EwIrc0f+0MgS7joM8la6HMJJZwybZBql5vgVZ33g6xbrEb1Kp1PeRAOENpL7yjQscb8Xy0YooQo/K1cbwjzBiQbzgiwg2RZygxyd4okQkXkaZgGothQ4KexEdbSZmuMHXQ7X/o9bs/O5cg
*/