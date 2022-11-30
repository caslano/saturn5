/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_14122005_2104)
#define FUSION_DISTANCE_IMPL_14122005_2104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<reverse_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
            {
                typedef typename First::first_type first_type;
                typedef typename Last::first_type last_type;
                typedef typename result_of::distance<last_type, first_type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(last.first, first.first);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
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
*/