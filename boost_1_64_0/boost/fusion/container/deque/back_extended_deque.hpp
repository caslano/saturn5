/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BACK_EXTENDED_DEQUE_26112006_2209)
#define BOOST_FUSION_BACK_EXTENDED_DEQUE_26112006_2209

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

namespace boost { namespace fusion
{
    template <typename Deque, typename T>
    struct back_extended_deque
      : detail::keyed_element<typename Deque::next_up, T, Deque>
      , sequence_base<back_extended_deque<Deque, T> >
    {
        typedef detail::keyed_element<typename Deque::next_up, T, Deque> base;
        typedef typename Deque::next_down next_down;
        typedef mpl::int_<(Deque::next_up::value + 1)> next_up;
        typedef mpl::int_<(result_of::size<Deque>::value + 1)> size;

        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg const& val)
          : base(val, deque)
        {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg& val)
          : base(val, deque)
        {}
#else
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg&& val)
          : base(BOOST_FUSION_FWD_ELEM(Arg, val), deque)
        {}
#endif
    };
}}

#endif

/* back_extended_deque.hpp
H6xowLyatNab452M3mlgtNocyYhDQV8a2e20ZmNDPDNQ/sq/QoZSYcubra/Y9a4TJcSEqN0p8ZtfTbf8knk2GSUS9oM8X2bhnpv2K99YFyvgFnw7B/Q/MZIBW+rsYsMaNE+HXXwgCEJOCM/XeEF7EFj5BeuCRt3qW3mKGrnEbBgWQHgoXDJr7C4452bxC7XTQ+qWe6VpQg8NsbhY4y4b6UeUhIP082vrk2f1l4r3cTs85Ae5bR/ksuaeX197uvqgcImAotoeb7+/hApKMsJvwXtF2HJkYZqDBwImXjy8zyANL2Xm268yDv/95gQPr30jtZG/aMHp3r4SCfNaXoaHXmlm44nXtX64rtFWAh8enX65GKWJqxn2heOVxcL1PlTnUZX6hQ9I4FKAzRPjZjkrRTH5F8wcf0hHfVh0PZg7es5RTdPkhGAnBOgV66j1ZdY9pQYip1kj/u57J2nzGN6zOc506tSLpYpsp+uEJuYzYzQgT6gztUvld+qmlTO3tm2siEmXNlYH73+AbSoxSaTjlwen0BeJl5HwSD8zflAgTmVcolLuBme3GVT7Bg==
*/