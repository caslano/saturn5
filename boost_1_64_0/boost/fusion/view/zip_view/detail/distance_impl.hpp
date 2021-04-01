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
rTqT+ghR2pSbpWSA0OMMldKjLhB9UTpr7Vv9jo3OKm5uVjVh4EN6fPStzvJxELJdweefz/fGh3vDo9hJ3QnI6W3gBIvlkWXLpivA9HDGWzXK19hUeb+YddZzPuLZrqzci2JXcAXBdRiKqL+oGKGmqmDA+h5XzFW7WWIHGrtVJhv5E125wS+ZWXMWlajk9E2ZIlu6T6FeTC9LsCVOp7hTv250grzUX3QaX4fNnwVblH9LBkA1VJOr41w1Tic4/h6J0iy0taOoIu/RpguHR0RavPM/ztmHLvYRk48xEvx08NNodJcmTmdkPFuFUkrrxR6YBBwYPnk5owvkRWiV3+YX7BI+ePHO5ifxC5DZumdz0aG/4L69Obw9E3gTpOTFBM1WIDE2qwoYsze7sG45IoyZOxkUbxJVsxBP2JArXNn3rcTXZh0RQ7JkVnEqy1nu2wpemj6wHyKaJxznEIMn9dGoURPAU1UtVPGEVB3klp+dwoyQS6AOOVlu5AQON1VSCXD9qaJMdMo92hWeWX7xVwTOcP/hWypH0DEEQjJD7vQn6khsr4UoZ6ZcE8ATvQ==
*/