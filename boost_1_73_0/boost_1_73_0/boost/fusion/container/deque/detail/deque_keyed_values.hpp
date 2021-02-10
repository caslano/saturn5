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
fA8n8cOCvruLlthtp2B10R9ekkw1/si5DdXP4Z7+UbFlutgsAmeU+4P1c2jDQiUhjrm0Hw7Gw8IzPFDFlPPfq5plozwM53P90AEL4VXqdeZ5czgUXbR5YorK5z83YiE/EY/gWvERDc7xVA/JMVyOo3M8V8lu8sMorJ7fazsn0Mj2JjkWXB11EeAvvrzadeLk7OCopoOQdT59oZlzUyDbBrWdgww4WOMkAw2NFhXsqhNBYok8EGGzmwVo9sEAzMQgcdqDpzvK3Gz42WMh/b1WE4lFKRK7ikQC4KgC0hKhM+ySo7IVU/Ohihng886mHj0KWj9DSlSrdyz2gVJgAs12e9L/lDmfMG5tpigYW2h56V/2aT3NSRaT1QV11OHaSHPkHpO8oqhmWuyJCdlk/KXT8uV7nNs07k3EofVDpHLB4S2gFwD1rqBJsgciWg3jeA3jmUCTtFZY6S2nY82CHX/N9NQWY2qwIuSAXfW4goS2kGBIC8I2LkWhp4hRAaEKH3d6iJ7CEbFHwr63pntVNV2Xi/J2aGLhahWvdreYmDovsHEyBml0DRaAeW1m7RhbERiPy95s+AlLrr9pvOTgDFmkg+JExdqqzo1apWiOtKvzfAAk9EP0/6sVEjMChX+/n8MSRV56JFL7ZA1BA7zQ
*/