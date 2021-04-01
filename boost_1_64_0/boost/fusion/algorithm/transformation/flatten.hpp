/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED
#define BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED


#include <boost/fusion/view/flatten_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace fusion { namespace result_of
{
    template<typename Sequence>
    struct flatten
    {
        typedef flatten_view<Sequence> type;
    };
}}}

namespace boost { namespace fusion
{
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence>::type
    flatten(Sequence& view)
    {
        return flatten_view<Sequence>(view);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence const>::type
    flatten(Sequence const& view)
    {
        return flatten_view<Sequence const>(view);
    }
}}


#endif


/* flatten.hpp
bGJB0UUtUJwimjUHGdvUvaawAGeWdWvVHi5nxJXEq98S9iHZqQqXOimnm3bb4peHLKaQc9hbkW60jHa0JEAviwteC3hL6J+yptJ3fJsShRtAZRriCJAHzjezD8q/wsRp3DLYPFrCPCRiYvf1cWQUvlDGgRyhJi4YQruCnDn5TsgrI+HWbYfa4TBGETEtZxzHzRJ5gt/3vRMqCnfzS2NGqm6U5VyRq6P6J0weOD+jCtDCX2ZPsycLzXMOOunSJ297jS25G0LGT8vPQi81b9ZNZUhrJ5p5QIFbkyZ7BM2Ct24P9VfDEuaCU/olUtNJNC35hytt1YvV/KNhISdKT8z3DE2hJXz1jmYCPDzfc9aXrYWzLoRGvrjDaGHv6QXctnKiv+2dgeyYRPc/NMgq7ApOFm/vLsmRiX1n5TBr5T4yE3EPDaPy/3SZMnAWRVoGC7ugLt4GU1+6k5mq1gX2hKvm6N0Pj1gqKYo+Bt9TY3i4Aba9xet/SQ9t37k2LmJD5dW4KWDEmY/UlRwXzg3Uudw1Cv0+xhuDQjwPWtElSDWd8zt/BmZhG3mv4DzfEg==
*/