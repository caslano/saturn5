/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_20060124_2033)
#define FUSION_DISTANCE_IMPL_20060124_2033

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    struct random_access_iterator_tag;

    namespace detail
    {
        template<typename FoundIt, typename SearchIt>
        struct best_distance
        {
            typedef typename result_of::find_if<
                typename SearchIt::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;

            BOOST_MPL_ASSERT_NOT((is_same<typename finder::type, result_of::end<typename SearchIt::iterators> >));

            typedef typename result_of::distance<FoundIt, typename finder::type>::type type;
        };

        template<typename It1, typename It2>
        struct default_distance
            : result_of::distance<
            typename result_of::value_at_c<typename It1::iterators, 0>::type,
            typename result_of::value_at_c<typename It2::iterators, 0>::type>
        {};

        template<typename It1, typename It2>
        struct zip_view_iterator_distance
        {
            typedef typename result_of::find_if<
                typename It1::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;
                
            typedef typename mpl::eval_if<
                is_same<typename finder::type, typename result_of::end<typename It1::iterators>::type>,
                detail::default_distance<It1, It2> ,
                detail::best_distance<typename finder::type, It2> >::type type;               
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<zip_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : detail::zip_view_iterator_distance<It1, It2>::type
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename detail::zip_view_iterator_distance<It1, It2>::type
                call(It1 const& /*it1*/, It2 const& /*it2*/)
                {
                    return typename detail::zip_view_iterator_distance<It1, It2>::type();
                }                
            };
        };
    }
}}

#endif

/* distance_impl.hpp
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
*/