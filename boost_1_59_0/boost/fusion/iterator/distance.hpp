/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0721)
#define FUSION_DISTANCE_09172005_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/distance.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct distance_impl
        {
            // default implementation
            template <typename First, typename Last>
            struct apply : distance_detail::linear_distance<First, Last> 
            {};
        };

        template <>
        struct distance_impl<iterator_facade_tag>
        {
            template <typename First, typename Last>
            struct apply : First::template distance<First, Last> {};
        };

        template <>
        struct distance_impl<boost_array_iterator_tag>;

        template <>
        struct distance_impl<mpl_iterator_tag>;

        template <>
        struct distance_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename First, typename Last>
        struct distance
          : extension::distance_impl<typename detail::tag_of<First>::type>::
                template apply<First, Last>
        {
            typedef typename extension::distance_impl<typename detail::tag_of<First>::type>:: 
            template apply<First, Last>::type distance_application;
            BOOST_STATIC_CONSTANT(int, value = distance_application::value);
        };
    }
        
    template <typename First, typename Last>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::distance<First, Last>::type
    distance(First const& a, Last const& b)
    {
        return result_of::distance<First, Last>::call(a,b);
    }
}}

#endif

/* distance.hpp
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
*/