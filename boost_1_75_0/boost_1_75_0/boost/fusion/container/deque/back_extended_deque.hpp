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
lCFzHOgAb4Gs3Vhy4ov1lCmpN9SBlbZnBVZhKl0sx7BLjloN9Zud5t39YsgZ4XfGrUqrCsPYYmWvXYAT2Tw2jTfupMZIHmNZS5KsOSCDt7+ntgPmanOovVt33u5Q2+Hb1CZR+999efujajt8mVoSbsx9uvH2DLUdUFRbT9uzwTfx9pvUdvjItTXUPvYG3h5G7e2VlRj8c7DoEWDohgBuYGO3LO3Abzl4DG+5AfvmOV6lyL8BqEtCiy3cCfm5656FfLKJ/LaldFtHvM3x6nrtXSv5XZvgrr7srn3i/R49JpCPzmt1rVlj5zt4YyY1juVOXziyvDw4gjhjvAzZ5wQ7rTrCaX0Z371HM7n+iDvJgu9MHZSGVydZ7VE4d5rbtxHv/zOhVGIrBQXX1ZUrK0aqZsXIVjk+JZ6XxGwIFTkGa+93uVyUNE36GbkGsJCgI5zP0swKPqKdpqW81LumDCwWdRdVZe1a1cIWbRXYoUuJDQMivbDh6ecFG7axX6COaXGVjg/z8yB+fuUK8syLl+j0LLHQ3+nqz3T4gTfuYacNbFJsY0k89af7FZ5KPlaK98MOxlN3AEIu15A2JlfVxuSiSXkcrp5kx42XDTKqdLkaTYJcVMSDEI/EUDBdGqSZg0/CPvFrRDmEa3nDt2EGz1VXymtA5sTqyFj6hJKjYnbuNK/FT5zmi+1juOZpdwBKDNGcFJjEUK2WeEjgAkMA
*/