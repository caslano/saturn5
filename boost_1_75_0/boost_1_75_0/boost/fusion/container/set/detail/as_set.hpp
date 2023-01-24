/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AS_SET_11062014_2121
#define FUSION_AS_SET_11062014_2121

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/as_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size
            , typename = typename detail::make_index_sequence<size>::type>
    struct as_set;

    template <int size, std::size_t ...Indices>
    struct as_set<size, detail::index_sequence<Indices...> >
    {
        template <typename I>
        struct apply
        {
            typedef set<
                typename result_of::value_of<
                    typename result_of::advance_c<I, Indices>::type
                >::type...
            > type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            return result(*advance_c<Indices>(i)...);
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#endif
#endif


/* as_set.hpp
GmuUjNjCXaDGuhSAok8ebeFzaQuvtG/h+XMkPAydQ0t+JpencKmtvY0WFgNwfv2XWv4i0GoH9+QH94NuW4x5RaVGp7x/r0YTP0Uw8N1UhIEvZiAMDNwtaeKz71M08bhKRRNfeB3RKRYMPHe/ByMBlLnxfvCAX+69JGcTRMoyg2iQTIwOwOTsSIrEnGmmp/8eqm4s64m4Ks5tXKBUCi4AmUhbNyq6MVELL1ATAo8LHkTq/bwyaC/gthaFIwhk68i6jg5bsSh1w6JE2tTQ9I2n5LK89BTHFX/KflamyLOSMfHyP9VSVBQEf0Fk/AOR8bRJGjJm36Mh4yJaiNFBXIj6R3Ahnv9JIuPiexUytkxUyLj2mnBk7DX5EMj4iETGGQ52G5zZIeq14nJHR9ibHNEQ0lLwAF24yyB8D8PMTx62MLOiksxrSxkr9SwfdBjH84tKMaLrukNEdC0fbaWeq+tDz1Ak1j8mqbeoEK88WbsmdYjKPMRPoUVrf+7qlYiuWn4XNGHFra0LyVwuDMbWEi0oYKxfri1SNoBZRhiYjXhSglmO+nXmk4z/XG55hsoPnokW14GAb8f+LpJQA9zLRRsXsG1pMFQ8h7kGmbPAIQrHHnn/I5rM5mAP6NVQTTa7YOgizusJGuxW302wGwDY/YRgd24t0XXTEXZ/+IFgN2C2VxDsivk8cYLcSM2EYpcl7WaOBRbliolEztVKcm4T
*/