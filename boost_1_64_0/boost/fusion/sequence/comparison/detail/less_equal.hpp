/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_1141)
#define FUSION_LESS_EQUAL_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less_equal
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) <= extension::as_const(*b)
                && (!(extension::as_const(*b) <= extension::as_const(*a)) || 
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

/* less_equal.hpp
viIttlKCHbWvKRc46FlwcmK0HIzHjrPAXYaOiUHdCHUcbHKu7XdQ7eoNP2Asv/7NGqdCi8IogrwsNr0oKgTO3RUUJzDINgWwwnim+f2Oc5G1KcVF/70P4WkG83bXFc3LloMz8frP1XU6Bnoo24FlZI2QFHytDysHEkAg63fhKJczBztqnFCz0peUoVv+H1GjZlOMBPokdEpX+pLo+1+P4Vir9k8SRVOCr47l/6dCz21kjWU+BZpjv0zZuBbmljT8/caZ9zlck24Hm6UmeszcO0NTdslf7txZ6P3c1/HEDd4kIVGdiA8k3NLustfyjTiykTg0V/p1YrNi9sJ+/GXwKcDOP+T0EvE3LsWzZu3tXPJfIU+MT869CJTUC/LmK57OxiPEsqJ/+QPTLAdHleGJS8F9/pa6qBtMxYUoPyLMxudgC7+XhjiKPH99LL/OKHhILzsRuJmYPw9ox3SjUxWYPPgEwt2rnOBbRtC+Q4eR1COklluKvqE1UdQcjBkTydQi6TO02dqWeNoUhv/pbXGwrmZsrNLBRWLDnEgJ5LPIA5n8uMchAM0T1TVcLw==
*/