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
Tj8V3Ia6Ppldu1mHr3rKgLQKcXZ30loApZFIX5sfOF+jm0myIoXYRwq8X7yijVqnUTvrsjQY8JQCh/dPlQE7jTd5R0hERnnjvklThXBB+BpwngIkiV7RkV0i1qW0ULmKrwK6EL5c0N9uQmAFC4k05NbXcHTiy+t5fF1iD1f6kMl5t3+e7UieNDhsyPkdsoOUf+bOeZRRwlR8XRIjb6koKj52OxSmeREqPk0PoiPdwlby/lbpFxpvqy72rUb6OrP/fgvG0B9hovnM1O0I/IkKsNoZXrS8NyeNRs07PajvvhedtC6Yo9P1IIPHK6KDE1SIWyavDvkPAf/qndKGr9fL5N3hIaLbOU9KMj+IV7eHs3iaHBLuE80iso3fjg91HRmCUlcwD+7W96JXL3W+aeGu+lwos5VdxfSQfxyNR9XEEi3KSeVbySykIaUEshRWxcCOrcgVBseUtdqJG+2GJFpvdUUeH7lPpQZScdkdW8EnPDah9U8P7suwM94u8Ov4yH18DZTK4VluEWn2aRy9zydSSJEjEdwX0xfi5jsfPld5+h3raBH9ERKK+j2kw1dnaQ7j6WaxUTm7/oNbik7p/YsXf4huFrNQ5XyCYbnb7vgjfKvikdLKfAkboFhNixD66000n2nt3VyFujt/ODHD
*/