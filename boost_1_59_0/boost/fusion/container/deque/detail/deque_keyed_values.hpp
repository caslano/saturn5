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
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
*/