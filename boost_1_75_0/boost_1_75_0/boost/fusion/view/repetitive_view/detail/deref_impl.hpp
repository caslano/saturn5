/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::pos_type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return *i.pos;
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
AKVC0i0lUaV8xwdOP7i3IgHhebNfBPReWmTfj5UvRF/s+KZw6++5ZQqs/WJO5NRo85UGkk9zv4moQLq3mgRprDz7oK+9Ptf1yzPuz0GCrX4GmNtqsG5ZzI9R+C5Y/d4dlmFcuVSG0dkNCgsXNJB5lUJnltADIVtAOh0OoTCvk6ZKO6WP7/tLOgyUa+f72w7GVJ7P35b87Vjmtmkpvsf6lY4JYSqC7wHhHWRxYCo7MuQvyr9f2T5HZQDQWwe3yCBFHwL17QkwKnj73GFDt3Xm6INrZggwruvYlgmMRD/GFmIUn+6cCB/6cmPDkL2L447L76DcMNafL89yt/0j7cI+Iul/Fm1cFeavqxl6Jop2IbX7C6y6WC9ty3mHQMt8n5e5WPtAy+GKDwcDv4//eYd8sVHeM+qxmhGgZ4jvvAc2Id8NnPAzoeI/rV8SxuayksseJVNNNHv8469eUkm7V5C8cph//7UyIv+QpA4o74G30+MIUjWjtOngi2/v1D7M79aVvKltSLE2njeG/kcbj/aYv4E9UgLO0mQhkd0CnN6BYwA4VXWjbOZGRR/64j6P/Q3hm25XqoLVzm7ugCX3Z/ff8Ki7d3Ph+eBalIGnxDvKxCmMc1M29FGT1LafCjn+exHjp/yckUQOpe4Ty/cNa+UWY2IvQ1UTDIiAc9R90DOfCxou/pJGVxgL/9SmUcQIJsy9vPMktxmzfD+wNweg
*/