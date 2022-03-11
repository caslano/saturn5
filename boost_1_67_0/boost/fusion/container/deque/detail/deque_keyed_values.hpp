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