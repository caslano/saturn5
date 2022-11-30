/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_FACADE_09252006_1011)
#define FUSION_ITERATOR_FACADE_09252006_1011

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/iterator/detail/advance.hpp>
#include <boost/fusion/iterator/detail/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    template <typename Derived, typename Category>
    struct iterator_facade : iterator_base<Derived>
    {
        typedef iterator_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;

        // default implementation
        template <typename I1, typename I2>
        struct equal_to // default implementation
            : is_same<
                typename I1::derived_type
              , typename I2::derived_type
            >
        {};

        // default implementation
        template <typename Iterator, typename N>
        struct advance :
            mpl::if_c<
                (N::value > 0)
              , advance_detail::forward<Iterator, N::value>
              , advance_detail::backward<Iterator, N::value>
            >::type
        {
            BOOST_MPL_ASSERT_NOT((traits::is_random_access<Iterator>));
        };

        // default implementation
        template <typename First, typename Last>
        struct distance :
            distance_detail::linear_distance<First, Last>
        {};
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Derived, typename Category>
    struct iterator_traits< ::boost::fusion::iterator_facade<Derived, Category> >
    { };
}
#endif

#endif

/* iterator_facade.hpp
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
*/