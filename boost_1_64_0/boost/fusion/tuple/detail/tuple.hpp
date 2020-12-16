/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TUPLE_10032005_0810)
#define FUSION_TUPLE_10032005_0810

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/detail/tuple_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/io.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/config/no_tr1/utility.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/tuple.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/tuple" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename T)>
    struct tuple : vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)>
    {
        typedef vector<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)>
        base_type;

        BOOST_FUSION_GPU_ENABLED tuple()
            : base_type() {}

        BOOST_FUSION_GPU_ENABLED tuple(tuple const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}

        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2> const& rhs)
            : base_type(rhs) {}

        #include <boost/fusion/tuple/detail/tuple_expand.hpp>

        template <typename T>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(static_cast<base_type const&>(rhs));
            return *this;
        }

        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(std::pair<U1, U2> const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }
    };

    template <typename Tuple>
    struct tuple_size : result_of::size<Tuple> {};

    template <int N, typename Tuple>
    struct tuple_element : result_of::value_at_c<Tuple, N> {};

    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Tuple>
          , result_of::at_c<Tuple, N>
        >::type
    get(Tuple& tup)
    {
        return at_c<N>(tup);
    }

    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple const, N>::type
    get(Tuple const& tup)
    {
        return at_c<N>(tup);
    }
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* tuple.hpp
3awzT68x5fSumD7oPD5rjkH3trGDDSrvS/s7MVQerrHZ2HZdTO9nY9p1ceUAxdh1sXf/Nn1rAA1xPEDMpRamXV+vPIBi7Pr6zAdKOhD6F+ScRJYsmad97iDS18EzazrWyz88SNMhhTVZln/vaVD+55ax/E3/+EFtD6yXWuVb3zm0K6ZqNeb8YYpirfKt70zowhB56Nuu7jGwUKzblo3P1v3Fvt1w3XLft9/Cox1ELpx1aePa9tL8/ECTti0r/fX9ShTTrt9YnnDnicTWIDhohHNCdU8HpcG6hjpF0DPXSjTmxHMV+5MNO9+PNlT94jG0FPMJ7qlq49BaMmexcYhCe+f2SAwQt6zsq/vOg7KOLq+TvvNh8I3zbNe+832o0/Zdcm5g09t1+4VTu2Lkr8+dwzTK550p1irb+rx6F6ZbXrqfYtEvIUae+7MxbZ/yA4JBn4J1YPu+QJd14LlzcrEQvz/6fvhd1g1Sh9+L8qTTaI8TxJSNwXTKuoNzqfdoTPWOVn8JdkqXYEI3fOMAcc+caOPU9EE+cmrkxZfaOGMtBfevbIyei6C+X++KgY5+o7HLm9oVJ4sJfcQv7h03XFqD1K4YfdZ0G78zBoSZ1g7MG+t0PNbI33cb6w/SeazVY/hrz4AxmFq3BgJUGLWKVrez7wCt/rptjwXehXMQNcocD4y53w1jfrc1UMbgGvlVpUt+e0N/eWe8vbkOadbziaeAH61sUUxSgLbzPkD7gaKBRCRWY5wDQLt+AdfOJQH1HVVr6svAgkU3OLdzAdPyQqgr78T6Kd+tq6oK7he26JikZm9v0sBIbsMvvnnKoMGyq8x/lcfqISqUAfcwNbja0mYeZdBQO9YB0L/HoI8rHXUy0Y4X7rUx3XZcN3C6Ism6sCPro3+6nxZ5KHFyLvuXx1ffXje4qz9ehkdud9YG2kf//VBFW6499yPrb8ugbbvfUDT+EOxzZx6flRNlJd/wMe+YUJRgCCcxe8b6RzmBtAjaD/Jcbb6/ZFQtEKIvW52UtPWV5dn+uc2Vu0B3o+ftkgc61QeAPStPk/bMS3MI5jJg5nvNeuK1qYfDeiLcqFDPC0DdUh+iSwZboNPge5vkq5Kgv4Os+ntlPtr/B/y+uAVNS75Bg7SVSU3DpIEtuCcDtG5bZJruq/J4rpWmt4K8OSNNB3/7MJWmuVuk6S2Sr5Wm+rudJvzelaaa1p0moHXagvOlcsecLyUscEqn4OFtz5fWYATN6nHE659B9tvywvPV923y3TktenR88eYJg6vaDkL6hyYoXW9APAHHeV30/tLWBWNdyMLUW0BIhyPkhG77oWsWnW4BGeu00xSnt4Aei+stlC4nP9QX2XTc/gEM+iKKwe0ftBfuiqEYa/sHZV1p4ba36lgBbPPefomRUX/yRQ9jDqS+V5kN102pPUIcD99H0gaXRvBIZOWjnlKfz5XfIfO2Nnov1XFbW1M07jwoROklDsO0n5zf9d+jXg5/VsFK1YlVlHuZyM2YyD1eRGGo5G7AJP+25KLY3im9/mrJ5ambZ7nvSrnVgKqSfmuJPUfbet3KA9/LYxGKXMmssnF88rZzoGnb/7LkFkFUxMKNDLm6Sxzfi7zn6rQfGVN5ScJ56fhCydNVZHx7VuJ9LJZMl7thmEScyEQrO2Vh2YwsWVGZh15QVvmoZvpyLDO+HfNQ5mdtmWmQBElYm7c+ugORWDev2Wl2/CjLi0IKrX3GrasmCm7k3rDk+m5e5Dn3pVzIwtHa0vLgDsSi3IPbVj3KoiiPg1TKrf31Hdmr83bBkhs4heC+l9ZttBZ9e0K1rWctmWEmAsFL1T7RV962pU1bep8lN01yv+BuSeT214djrAs=
*/