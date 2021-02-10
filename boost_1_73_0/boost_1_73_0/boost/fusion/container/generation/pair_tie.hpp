/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined (BOOST_FUSION_PAIR_TIE_20060812_2058)
#define BOOST_FUSION_PAIR_TIE_20060812_2058

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion {

    template<typename Key, typename T>
    struct pair;

    namespace result_of
    {
        template<typename Key, typename T>
        struct pair_tie
        {
            typedef fusion::pair<Key, T&> type;
        };
    }

    template<typename Key, typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename disable_if<is_const<T>, typename result_of::pair_tie<Key, T>::type>::type
    pair_tie(T& t)
    {
        return typename result_of::pair_tie<Key, T>::type(t);
    }

    template<typename Key, typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::pair_tie<Key, T const>::type
    pair_tie(T const& t)
    {
        return typename result_of::pair_tie<Key, T const>::type(t);
    }
}}

#endif

/* pair_tie.hpp
nI2sa9jVLux6ZH8YOO64DjM5+FLCaCW/azyxbklwyrdVG6hUroNI0trIWr3a6Eqs2qCRpj6ZVNihG9/UR0oJakOrcOujf3qu0+tS5CyKypPjdevqsnW2JcMQzwSUYbtvmARd59qe9Etv4OT8/fuz5kbFnGsspnggTVmRYPGVeKigeHjEEW2dCDOxx3XerIgY9gJ4KokppLJGs8BRxTUF880vURbvbZo502GM1QrHv4dpFdiqyCkkmfP92FaBlavChHbRfEKkigPL6Xc4MhdKiXR2SFU3qArWtvWXTaNqksgFKpq+UEVGcmDinwqB1lZg+0HPNwSvmmvbSJRw6h8iid7zfwqehijlvgg931Qwsw8MyWVzzZCaoz//KWNKLWQelb6hP3s069JqKK42fhANnTIRp/1KR+0Me6ZD8x13Pf/1/nx0v5qvDs23h0PH7ZqNZRjeNLfmsyzDoxAYrYg5KL3Efsi0Uns0HyaO72+n5G1zW88ZC5dAB/CLkmRW8CczHNgTbCBGvXHp0PnZRlbbZJjPM70EVuhY5gK/LWKefu9SXy1Lhb3Q36lcYCNI3cKqJmKLU+Ae7aDHpHDp2zvqCExjRsP4PmlCmHOmcXkwSPmihGH3mUaJ6eaqzUA/Z1KkmpouCUJTowODQmm4
*/