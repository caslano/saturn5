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
OZOyHwTK0t5KOqriFpreryMmGuxQh+G9gh+E1Kvd7Pvw3CZLEbWlGWmOV3gFqsl5pB2/MJHukba1uwKPtWGW1U+jzZqwfo/4zzL876NaMQ0Q/8wVOzPrC3REKDf0CP+roE4zUeAL20dnsL5PBDmtFA7YX9vADJE3J+0/sXFY0y3TK3QTKvLrn4UM94/un9gAxywsibJUOW42cGhtoe1uQmxVCJHguD5yosmCX+MVpfXFap1LYgo86U91Xt386EBJOi0R4+J2R3TJQVuTXszKXJbrG0i1lFmgsx1jxlyOVlLMT873pQmWtaGFau7BHOYjX60ZvZ3Tf13aFCGQerP5bV4XEUC/vDeHz3jeNz62uof51mySnoqzfXBxDtzunQZw9WY+kqBB/T85YByDOSmlK5mHmIx2QPZD9gwfoCCwEYVZWzI4PjkKwKlhpUWl7sD+2NSl5X100RHTC2SvErw1EwSv+27fF86ZsR2CR4J9hQOBfqjnboBrNBViszPth/xZShe9IBw3819axbCTgo8La7xFAtOiiY+rRH2H3lS2VJ2uxz7fUNmoxD7TbQ==
*/