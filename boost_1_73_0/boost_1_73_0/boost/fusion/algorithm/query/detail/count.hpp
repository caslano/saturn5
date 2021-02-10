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
mnY/4miW+9Q8ktZ6UXFHayZAZhTMcQ8Tg7mY8h1E3M734DakkU/jVYBHyUGRIRmNm+NOi2ZqrS2/8L/SBHsYX8k1Unm2FfXfKd2m2XxOHCfhC2OkviyqmhNXiua7GGjVbuG9ayqAriFb3aM578GWn6lh8GeK5M8rkYeml1m+j5122+/xivW7o133utu/q6YKVcq2yeAxn6ApYxqTi4nCJJxEeeJp3MpdAOX0I3t12+9yd7dBW3AC/jg7jvc5ppebTM6bba/T+9zsEjmXR7lDQYz4tnD26+YiVi1cCyFNwAk73ioemDZ3cy+8FzEc1PyGeLMFJAemcnQRj0ZdkrHo08WMiZf+nj/8d0JoPrSj7nmThtdr013a870/eUe14qv+wO8B3J+8uuPth97VuDuilw3HS/qO3hy7gJ6P+l1/7J/Q+5MaM/5fSPb+86hPjQ4w4mJPo0+dMTU/dYAb9LvNoQzyzPH6S797IW9fO96OWh+bvZ6P129cr3164I9JPh0N+kOM4K2jVfOrLEP9qIbJLIghXEGknym27vXB2fHBkXNil+d+W33sWuFLf0To1/uE965FPvf11OuulR5ejRTwkxf/oXAqmSvceM/YFMwj4t4SRigtkU7nMUQ2sHyEWsF9KHeghdpWH0ROhj7G
*/