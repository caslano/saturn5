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
+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
*/