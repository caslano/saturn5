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
I2bHJiFmP0gQ29G1G5Tt6J+blO3orhWkXlEdZjps1brCopSSkzTGaipNEStVL/hRvL0G7svlG1HGmM3jH9QsCR2DDFxvo5FnaAUz8aYC3lSgiu5XAqkpnzflY1MOlofmS9ECVexfIMT+fOiwJ1DVy/AO5aKDHcNteIcytYOiFSrji+eiQJ1WSKhqdcLYDFzt0NxOcUqpK9uiBJGU396gUHp8rEGrw4HEYlDRWsKyvNXykkfCcLBkNphl47tsADD5JlnWH2kPPx/ulGDZAOwdqqzEwzA0AIp66iidxtMolwIIpAIFpPc4SI8KkJSBCJ7ubvBEc3jWBHBIEAblpu786QXae97Jo3vmeL6nB78nX3vP0/yeUZ7vuRPv4UY/zW0p/LZbPd92F7+t3O22IH7bVaPH25L4bWVut33HkfGd59uS+W0z3W57ld1GK9YirQ19e1VDDfkHVVoNuaYguMtczpvKeFO52lTIm8p50wK16UHeJIwuIgq3T1WUmFFcKmcXb+UXCxRVHeQ/5xftWtfqkYprNa5buZ7N6sv4olVaStwRnYyKtgInc2OQHx8V69WKo7QmvcGPr/Cjkx9L+XEaPxby4xP8+MhRXK9G02EYHbLpkEGHPnRIoUN3OtxKhxuPhhsa5i1FP7pxhyGzs4T+azNK69mOWYJJQzlMB1mll0AykYcPA0Rji1UqRrezrpusm+oDres+eJ/+WU0f
*/