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
4Q24DrfgBtyBG3E33oBVuAkP4o36M+mlbULuH/o4zKHzuPGZ+bJe3wbWqzHEl0YwrjfaOMdPJ4mv/vW4d+76Wf33GNYr0+Orf70qQ3xbHfYj3LDeaT2++tcLD66LL9Z5DIa+Xpqb65XLev0bWK9a1utbz3rrCHI/kvuU2ufCVx3DJfdP6W7dDfvhIOyPMRiGcTgQE3AQZmM4LsYo3IXD8H4cgUqdGIVtcTRG4BgchrFIfph7TO4L4u3y+W+FKbUXiqzXAeOwJ07EATgJp2M8zsIEzMHLcSNOxXKcjltwBmrnG7nnh4tNzjcfy/nsr9gTT2I0foop+Bmm4d8wG7+Qel5BOC3xnpV42+FmiXeu7Mc8DMH52AdTMBxTcS6mYSam42rMwLWYifswC5/EbPwjLsYXcAl+hHn4Mebj37EQv0KL7H+1l9x/w+5y/JV8HZR8viRjB1/GXvhnHISv4DB8FcdgNU7C1zEBD+NcfAMX4xG8Co/ianwXN+FxfBjfw+fxfTyGH+A7WIPH8S94Ak/g58g+qfXoE+yIJ7Ezfir1mh2S+2qUmZzvO6vfB9rrZjmet2AUbsaJuAWn4a2YjL9FG96Gv8HbcSNux9vxTnwIK/CPeDd+hjvxH3gfNiETu+V8fz+G4h6cjA9gIj6ImViJS/AhXI+P4EZ8FO/Ex/D3uB/fwMcxnH17CidhFU7GZ1DmyJN7Ytq9sgqHOfK+kt9lZzAOv8bp+C3Owx8wF3/EEvwJ78CfsQK9qEevQROpVxfhWfTG5qTRDNtgc/THFhiCPjgHW+KV2ArLsA2uR1+8GdviY+iHT6I/voqXYDW2x6/wUmQbrwD0ww7oj4E4EDtiOAbhCAzGsdgFp2BXnI8hWILd8DrsjluwB/4WQ1E7b8o9Luhkct48K5+XH3Eo/hPVPi04Dy+i/PKwGZZjc7wbW2I1tsL38WL8Dlvjz+grvx/8pD61M/5ukvs4lSbnMZucb5bhZbgcF2AJrscVuBFX4h68UvaTz6Lc16Euyn4GqnMhaq+DMqftnzAIX8Ae+DJOwj9LPTqEVnwFV+Krst+vyeeoGrfh6/gcHsZP8A38At9Epd68hRF4DMfi2xiP7+ACfBfX4nHchu/hXfg+7sYafBA/RPm+kXsvfOZMvm/ay/m/Aw7HQIzFIEzCYLwKO+Ma7CrHMQTvx+64F3ugVp5yLwUnmZTnPTKG817sh7twCN6Po3EPxuNeTMQH0IYP4gqsxFvxIbwDH8b78RHcj/vwaXwUX8HH8B/4B/SVOY798EnsjgewH/4Rw7AKI/E5HI0HcRw+j0nN3BtLWpLD+CwCY0o940n/zeNJ9+d4/9vGlB7J8f7VxpWezPE+p7Gl/8/jShnv7XJsqVeu9wUdX+qX6/1fMcY0lHwmEGyErYQDhBOE1os5VxGSCaWECsJBwilC4BL+RkgkWAgbCXsJhwinCH553l7RhBRCGWEbYT/hOMEr3zNO9b/h9Sv1/y+25eZZte7/59f/X+m/n2Lov99HrgfaEpoRfAkvRirX8129tL7TY8ePnzVj7Pi5auNevpqAG3Nc+cr8Ud+obVPpdn3qt7lIM9FVmnl5ueebJtcGvFhH0mwjaVrM07RmZxYWZLkxr1h9ae6XNHdKm98OwsukWe6cplUvWzfmcpN+UJzD7fpBSX8niUba98NRa6tkori6JBzm8zPNJ8td5JPjcSHySTQu88nfnPLpI6fEcsnnBslnuLdZPuUYNqJfmXk+JRrTfMrfHPJZ6u1c1/5MPk9LPmU8AvXM2OXH/br2iOTTOAbilLfzZ+oQafo1c0xT67Dvzjx19aWX0sw5vVeUY2GSnnSQOaf0asu0dXPnY/8a6SU=
*/