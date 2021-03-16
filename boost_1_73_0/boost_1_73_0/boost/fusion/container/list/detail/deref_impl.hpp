/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07172005_0831)
#define FUSION_DEREF_IMPL_07172005_0831

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type value_type;

                typedef typename mpl::eval_if<
                    is_const<cons_type>
                  , add_reference<typename add_const<value_type>::type>
                  , add_reference<value_type> >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.cons.car;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
NWy6U6vhRr3Kn3f77qTleREt5vnBFJnRd1u1GQt2CMYCjzpraCwYm7HHXGK2yiO2V7HV2+P406z1FIMe+ZFiL9GeHmi0bORFux26U0QUfbPl1QJyZ2XUuBbBpRP38RPTMsc1iGt4FjlSBArV3E0wCwOa94IqK3J3EE8EsAfvG+wWfDyH0y9CSyRshKE2ISyV2sKb8L1JJ0LMVJJOl22rI5KBVTf0ybU0f7FTb0zRFgEP7r1GYzLw7XE/TKMmYzo=
*/