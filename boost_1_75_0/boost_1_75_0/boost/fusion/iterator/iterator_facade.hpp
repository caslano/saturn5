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
K9qIqa1ncL9LfzOYGoH7teHWVIwu+copWBd+HN0dJBDBlzfxJBq5ZahL+UhWLpQV9kK8jIcstOefuIFYicGNH2sWzmN/Bx6zJZM0PEHgyGt6jorc3CG598jWC6632TprW3pHqgnPBlheyScG7kdVRPUf6f70JJSPf4YTwJ9vGC+WlYUK5gXvR8cduF1Ft0fGbs+l2z68Hb1RqpE02635LEn/m7GnLAi6G7FpC/BBG9+r/iWrSIK56OMAd/1U7dHRolrU5RoeFahWkSODJ/uUb3y5570HO1wo2T8yE9l8jTm/TaoBgSSdKg4klxXmB63uDR0ugqfXbINHks8r7Bq4blBNUVaYwmDewkmb06OGyW+NmTOtO/ZNqF6Mil1gqnkm3QHKHXFZKcSNdA5JN1h07LstnBY+go9otj7Ql/zaMgfVELgV8xT9NDV2+6sb2ErhxIfhpVuswrOyVLM13UCPFgK3D/QV12a/SKabQOaLmZgDcZ8613IKTmnBALVi3wjEwPFUaYGJQIDAdXJkKlJ1yCKk6tob9MEK9jJ8XsdMCcKJbvAUObKOlO6OJulRdOVF7UBkcTfeooafo60J53BCbBM53XnDq1CljF8GU9BVMch84Ruib/PaHCsn8DZaGTGfhdN/MY4grN6F3eGCT3k5G7HF84/70Z3uqSSh0Ubf87LCAVLVXPji3vAN2rkrDTVcGDkEmsbxTznaViqF
*/