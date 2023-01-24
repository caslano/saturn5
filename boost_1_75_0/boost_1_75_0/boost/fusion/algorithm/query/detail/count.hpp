/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_COUNT_09162005_0158)
#define FUSION_COUNT_09162005_0158

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/support/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion { namespace detail
{ 
    template <bool is_convertible>
    struct compare_convertible;

    // T1 is convertible to T2 or vice versa
    template <>
    struct compare_convertible<true>
    {
        template <typename T1, typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(T1 const& x, T2 const& y)
        {
            return x == y;
        }
    };

    // T1 is NOT convertible to T2 NOR vice versa
    template <>
    struct compare_convertible<false>
    {
        template <typename T1, typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(T1 const&, T2 const&)
        {
            return false;
        }
    };

    template <typename T1>
    struct count_compare
    {
        typedef typename detail::call_param<T1>::type param;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        count_compare(param in_x)
            : x(in_x) {}

        template <typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        bool
        operator()(T2 const& y) const
        {
            return
                compare_convertible<
                    mpl::or_<
                        is_convertible<T1, T2>
                      , is_convertible<T2, T1> 
                    >::value
                >::call(x, y);
        }

        param x;
    };
}}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* count.hpp
y2gSQfjHFujhvDZEE+dDcMzDkhfCMLjztMEltmdwl71NgyvF6/sTUGFG6ODS3paDK4ymwXl4cIKUsd+cEjo4jzY4jz64WXQpjKIjDw2OlHbixOAK9dvCv4FkEUd4lK0qH5DbxuFDzW0O1tlJDrbX3nYM9qrlNNin8QpqH+w8d+hgBy+Xgy2PosEaXXGsPY083xwL9cXBxcJ8cbgx2aVszQE2amBUK+uW75/jlAGBgva33rKa8n1nCT4nl5kgnJjjyMXiRhAz5g7WLOF98LPIyPEVZ0Km2uv5BKlRtdNMgmtyZr4Ftnp18VBRysmH0HBsqNiZn1Wc4b0f+uPOpdtbd670bQkVLeb7JzeyN++aW07KD0USAmzV91A/M+DELsj1DUfMmiS/CBUUYJu8zwXy/2pJgkm6m8j135yZ7evrVnbguO55WhvXpSI3GG3UjdCie2keGwyTa3DZwegh1NM6pjrk/SoqgRWy0lcZnLTb7qWT1qQ7Opd3FebPEtll19FP5dtv2tu/PyXefzudgbO20yV8KTzVqVsptXg7XvOPx8SbOPEqSrwSE92cOHQ7VncRPS7g1HO2Jpp0hykGKBTfW7nMDZ/CAY6OUkd/Skl/NOKBLA6bdHfF2iK1tzig0T48fZ287x0LymoUM/63s7TblhpMOcyWbUVwrVIIfK84QBrNdEoggwMCU5Ad0t0isB+g3OexVc1C8IglB2yC
*/