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
RTElMg7U/hY9QS0hx65ipZ8CJn33k98K85O8+omtm1CeVTNNO96rx59r1EnR/ruE9yCTVAu3+6Uy8l58cMNQF91/s9nhyNWllL3VnQDlXeKAgP2Db3l7A6nzX1XoqDJmWL+p+8fpGuFA5fAsypTYVSbmCNHuHh6AOxol1AGkukGHn0keuk4NMXSanSeCkLNJyNCCCx8xl5w+++69Y9RyOlxEVWSEIneogvPG1+ETkhcZPy2cL6kzAiyYGWT3ENnhtPXzWxbuQhqgHqusgOyH3wXPxmhq+a1LLwEmWKKIr2ileMKFAbTBr/h4FuuFxjLuoPOV2ePIp2jszZs6CKd1P/W7LfjP5LsP59nfG3OMVRsaAyqTVjpK67o+Vzo0scdpNJ2JqcQsS+pU3ghTyiJLj2YV5x/Waa5jJRn/fg55C+rqgJnSFNCZBmieVg5dwqiXcABqQOMr3FKj+Oqe3uhXeUkTomimj6XCrHHki+/2UusxRbIh8yvFGk3W7/KCFlXw2Y/+YHfBeDlnI8sAyFJO6jhHFd1Gh0oyG4a1wPEd79rloAXv7zrUb8Wwww==
*/