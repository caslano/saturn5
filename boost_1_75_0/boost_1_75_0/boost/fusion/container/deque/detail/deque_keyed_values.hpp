/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_CPP11_DEQUE_KEYED_VALUES_07042012_1901)
#define BOOST_FUSION_DEQUE_DETAIL_CPP11_DEQUE_KEYED_VALUES_07042012_1901

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<typename Key, typename Value, typename Rest>
    struct keyed_element;

    template <typename N, typename ...Elements>
    struct deque_keyed_values_impl;

    template <typename N, typename Head, typename ...Tail>
    struct deque_keyed_values_impl<N, Head, Tail...>
    {
        typedef mpl::int_<(N::value + 1)> next_index;
        typedef typename deque_keyed_values_impl<next_index, Tail...>::type tail;
        typedef keyed_element<N, Head, tail> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(
          typename detail::call_param<Head>::type head
        , typename detail::call_param<Tail>::type... tail)
        {
            return type(
                head
              , deque_keyed_values_impl<next_index, Tail...>::construct(tail...)
            );
        }
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Head_, typename ...Tail_>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(Head_&& head, Tail_&&... tail)
        {
            return type(
                BOOST_FUSION_FWD_ELEM(Head_, head)
              , deque_keyed_values_impl<next_index, Tail_...>::
                  forward_(BOOST_FUSION_FWD_ELEM(Tail_, tail)...)
            );
        }
#endif
    };

    struct nil_keyed_element;

    template <typename N>
    struct deque_keyed_values_impl<N>
    {
        typedef nil_keyed_element type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct() { return type(); }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_() { return type(); }
#endif
    };

    template <typename ...Elements>
    struct deque_keyed_values
      : deque_keyed_values_impl<mpl::int_<0>, Elements...> {};
}}}

#endif

/* deque_keyed_values.hpp
F/wKMP/fE54FP1XLv3OL4BEbt9AaPIavxcP4cSAc5ayddGbhV5P58Q5svZ233rDL2x6zR0ffMt7Qd/3eY/Z5V91jLlOlvhHvuu0xw9/1e4+5+x3NHnPfO/4IemkTvIszts0CqY9t9iDy7RzA95gedAhRHXzqEG57x7cOAdSqcu99eh3C2RX+8OZJj3vTIazYJF5n0SZP3xfgHhrnc+2bvKJhbgoG92Crcx7ZNg7KXfaEGxSQ7/YL5KrHvIH8d5W7bgyIcHV7HRGCbgw376purPptbWwJBmAmWDAAsynwHucS4cxr/hB7hmCm5WruqApZKRVJO4kyzhBNzX0bWURIhpOHvLFbCuAWilmB63v4dcU7rEJpOiCaynnT20rTMdG0jDeVK02yaILZD8i3T1fw+9NydWNzYnkjuEZ6H/IosRIcH9TWqiqvdCPqmW/+mphAx6/xtDUdWtAhig4hX3vRnZnbudH9YX39DwYjbPcV+rlAJWDrkDuwJfYUggXeI5IElgNYc0q5ueCx4otG2/WWigvILKDUa8sfwhWdf13bvOIp9rDC2zQGso7U7eXbyVYfp51Ny98CdPXTDrfjKAxnn1a3z1Ix1SiufkpXJ9at1/ZdTFfH1L3DaLYhwrcpxP3LeG/Ebd4g5mPEBkL5x1sQuyvp8CYdFm7xold9r41PHvPNm4rQtxP5MAl97AfUBaVdN+L8HaArTA4gbd4r
*/