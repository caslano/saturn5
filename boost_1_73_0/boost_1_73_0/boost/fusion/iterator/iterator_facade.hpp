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
j5EoSFBmIsZRz98cohapGq43Ep/01EM34goMQT9CHC0if1KcWOGa4qrCzdE6kdEtMeKtjEAXqIrALjXQlIE71tABMM4AcD5zSJZMS/sCTvCQ5+a7YQhAQpgeNlPtOfNCsJlkwkR2p1NJM6y4nkilhhFJGkiQ4GOklb0sohCQVQRyr3HZpOikSySLl0aJnj9BCaCki5YADtRDqUGCHpRao9MrKclDssauB4Lk8EjsikP4p6XTrnh2zEoKSz6p4r3Dqwcnj/cfsxayYezukhyC+hnIr0Xp6HkVYVfLJB87Z6cgjA6ePqvg3+davirNVajzNGCE9yrTaTnfFpt0P9TOz503l2dnjQ41JXWwuwujPDhGFFAUgtkOcos6tx9nv4IhRA2+/dYBj020p6TRxLda7Vvv9Fun/k10wYPCyenUCWQO3uPPB48ZQKeGAP6J2OIHskjU58yrCECmBBASJO1/q5+2L1s9UQpmE3DvcFUDe0XoqygPDQRhjN4VyEQP38uroRuEay2Gvn6LVnfTFrWOacEKjJeokCgxeGWiTI4TlN84X0Gqnrgb8DrHssTKsCz+3rJ1ObZXS0AYeyxhpeuNIuJqsBGQl7kOMBhUKCttr9uj/oVme7QuplyTzKO5apYyn6YgS6bGa1F9Whbf
*/