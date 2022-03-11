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