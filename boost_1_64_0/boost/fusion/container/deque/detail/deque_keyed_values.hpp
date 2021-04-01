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
DFiKQz8FeaPZUiKolydap+DuA9JR5FYOROnqCkHhciYzKTFzYiQ4fAKwIbAdP9ah/XTQhp7Sz3hU6Un9pTYwuoVuBnKD1arrXq+qPpjJfDHSYX0viS0Zf1kVgwSC8CILd1VVaDvqM9QqscvXj0qP4hY5El14Roy+aJp/MC2RRI+dI9gq939XmPIQALPgRStSLAhTGcZrVHkWMpTnTNv7O6DD6Tss0p2XFaH6MkWuykygqbD8bPodOSA88PFr2Wl84tW38W1lHw5cCPNQZlHmnjWqLpg7Jby7GNWY/uIapoHcBo7NQ7QEJc5zdjNraZgfLCecq3aV4l3uSkGTjcrYp/fJjoLFACVV4tLielcNA0SZGrfbE04VB5a1hVN8+bg7nZ4YqgAnBE8xnCufmxFanXA9brl7rExCq12TK00LcUx15DKRp6X5zEI4lrgXNVSAzWwVXF2XeasNBoL2zwPKJBP4iQFIz6nCbDSsMw1kV90AbGkPGYnE3t0hIj+68SM01ZF/XpNy4JomLKEW7W/yKSsT2wotwFcAeLtNqmBZTBzL0wx/3iWUNjg2/w==
*/