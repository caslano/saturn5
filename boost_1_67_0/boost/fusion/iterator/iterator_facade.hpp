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