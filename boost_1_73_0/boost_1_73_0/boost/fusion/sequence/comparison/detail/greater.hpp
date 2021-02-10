/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_1142)
#define FUSION_GREATER_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) > extension::as_const(*b) ||
                (!(extension::as_const(*b) > extension::as_const(*a)) && 
                 call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* greater.hpp
uJsyBZ2C5Sg5wTZOImk7/zgA1/2Pdzd+EPQnYYucYL2mvctHWye9PRAdxSmPv7Ta1k3M9wOBksKT1CRcwflBrj8v/rq0IdhUdew2ZXtrsKamwrHM8R7ylnz9oT6VdW07uzmjUB1VgLxsbA/NyjPND1NSEpHA1ZWlfn4OJ2SZZ2yh4dyWaxxGn4b+TeQPB35wgIJSJbL4xeBFNXGK913ghNjohSI9z0e+elWbHmj8ZNsj2bKSUxM4uhsOL50Hx6kVfaq2W0NUW6LZKqJ03zVCrTzyv095YctHNxKHTOLaC4wVYWpR5bwwtCEWhVR4Te2ZGkpNi+3aCjs4GvpB2B+Fk2n7J9mKpHWkRQ8hqRhu3aIP9r4McPgwQxNuieNgN3H3pPgxE+c7KgX/alo/DsKhs6zpYRvRC3UPrY2ETZ+RZaNy49g4OAe9QRsb1W2bovNJjbHndfTmPG6SM4p/2VZpLSUWnN6PAf6MznBM6BpGJP8d5H9KWANvNHgEfcYL/Mt1vgFQSwMECgAAAAgALWdKUtVxdw9VAgAA+QQAABgACQBjdXJsLW1hc3Rlci9saWIvZWFzeWlmLmhVVAUAAbZIJGCtVF1r2zAUfc+vOCwvbXDjrk/rVsayJG3DRlqSlC5QELJ1XWvYlpHkpIb+
*/