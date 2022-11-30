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
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
*/