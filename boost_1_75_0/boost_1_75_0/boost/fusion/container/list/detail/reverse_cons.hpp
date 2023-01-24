/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_REVERSE_CONS_HPP_INCLUDED)
#define BOOST_FUSION_REVERSE_CONS_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>

namespace boost { namespace fusion { namespace detail
{
    ////////////////////////////////////////////////////////////////////////////
    template<typename Cons, typename State = nil_>
    struct reverse_cons;

    template<typename Car, typename Cdr, typename State>
    struct reverse_cons<cons<Car, Cdr>, State>
    {
        typedef reverse_cons<Cdr, cons<Car, State> > impl;
        typedef typename impl::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(cons<Car, Cdr> const &cons, State const &state = State())
        {
            typedef fusion::cons<Car, State> cdr_type;
            return impl::call(cons.cdr, cdr_type(cons.car, state));
        }
    };

    template<typename State>
    struct reverse_cons<nil_, State>
    {
        typedef State type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static State const &call(nil_ const &, State const &state = State())
        {
            return state;
        }
    };
}}}

#endif

/* reverse_cons.hpp
FwujlrrDwvR2TrBw5n+AhQA3WDhDsfB5P3dYCHCFhTfbNgQL2j/qx0Jcd4yFXt2dY+H6EpdYaNXWGRZg3dMS0d8eC6fbNAQLL5xxhoXFT9SLhaQl7rDwchsnWLD8D7AQ6AYLFoqFD+PcYSHQFRZeb90QLHifrh8L0Y9jLHR73DkWrItdYsG/tTMswPqhpX28PRYOhTQEC0NPOcPC/MfqxULcYndYGBPiBAvV/wMsNHWDhWqKhbf6uMNCU1dYmBLcECzU/l4/FrpEYSw8EOXEJzvzljse323lhMeF/wMeB7nhcSHl8cN6dzwOcsXj5q0awuN3TtTP47JumMc7ujnXt2kFLvXtfV19+jYW9UjZ6dKcfFVdkueRTUK+VV5SvoZp4DO6hmjgoePONNCnmxN8FC9yh49TLR3wYYz5AWjEcq9opNw1XO5fOsp9NgDQT9lApxaY1ETZrvoD2Q7kCg8aV3jwbNkQPMw9Vj8eCrtiPHzb1Q4PaoSHEAUPL77pEg9vtKB4CIg6CO8fREadqPLBwgZc9JPnwWp/vi9kHd6iIZI/dpRIPkl495hIPoBQSWjUYhrxJDcR/w4zF38cpjPqBMpXgQitgNb/aO4g/LiY7VpF+N/UFb7RPOUMUNiTAABezKlX/louf9lR/s/G5W/X2sv3PtRhQ80pRbZadNuWREQ7zEG0nZs3RLSfH4GJScQvgzwy3CBnRoqzkkcf
*/