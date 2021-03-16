/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ITERATOR_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ITERATOR_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<single_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : mpl::equal_to<typename It1::position, typename It2::position>
            {
                BOOST_MPL_ASSERT((is_same<typename add_const<typename It1::single_view_type>::type, 
                    typename add_const<typename It2::single_view_type>::type>));
            };
        };
    }
}}

#endif

/* equal_to_impl.hpp
2eJJfX1acM8RkPuruZaTUI+cRO75BeR2JWg5SfXIack9N0hOkpaTXI+cVlpOspbTmnvY+Zzt9/07yp7Qx7kN9xSQ/d5ay2lbj/Vpp61PWy2nfT1yUrjH+AE+L9prOR3qkZPKPe+C3O8dtJyO9chJA+v5bm1XRy2nUz1y0sE+Pp20nM71yOF708dJ1qezlpNRj5yuYF+fDC2nWz1yunPPepD7q5uWc1s9cm7nnoMg99dtWk6PeuT01HJ6aDm96pE=
*/