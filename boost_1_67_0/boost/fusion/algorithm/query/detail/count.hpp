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