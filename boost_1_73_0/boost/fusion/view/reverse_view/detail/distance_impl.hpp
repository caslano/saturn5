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
lzR0NdHo9THJXu33+iuHzBpw9TMyr1DcsVUorAf/P/5S+SHs5yW2LlKdZu8ofgOY6aBi64Llxofezd/Oa5O+a+MzUpiebkQY5e9tT8PzNYh1Y8KsrvWR8+X1w/01yND53jlGdOi5BfD13EuuTzIOrwywNiX5Z29maFRklscb35bo69jAgPaONFZMMi6+qZShqxIydPpMFzDYgcIc2jiMXDJ93YrJQDFP4E/EGa4PmY1+genr
*/