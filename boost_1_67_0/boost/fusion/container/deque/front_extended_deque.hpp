/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FRONT_EXTENDED_DEQUE_26112006_2209)
#define BOOST_FUSION_FRONT_EXTENDED_DEQUE_26112006_2209

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

namespace boost { namespace fusion
{
    template <typename Deque, typename T>
    struct front_extended_deque
      : detail::keyed_element<typename Deque::next_down, T, Deque>
      , sequence_base<front_extended_deque<Deque, T> >
    {
        typedef detail::keyed_element<typename Deque::next_down, T, Deque> base;
        typedef mpl::int_<(Deque::next_down::value - 1)> next_down;
        typedef typename Deque::next_up next_up;
        typedef mpl::int_<(result_of::size<Deque>::value + 1)> size;

        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        front_extended_deque(Deque const& deque, Arg const& val)
          : base(val, deque)
        {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        front_extended_deque(Deque const& deque, Arg& val)
          : base(val, deque)
        {}
#else
        template <typename Arg>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        front_extended_deque(Deque const& deque, Arg&& val)
          : base(BOOST_FUSION_FWD_ELEM(Arg, val), deque)
        {}
#endif
    };
}}

#endif

/* front_extended_deque.hpp
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
*/