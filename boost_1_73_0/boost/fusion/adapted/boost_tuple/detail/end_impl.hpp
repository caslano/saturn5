/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09272006_0721)
#define BOOST_FUSION_END_IMPL_09272006_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace tuples
{
    struct null_type;
}}
    
namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef 
                    boost_tuple_iterator<
                        typename mpl::if_<
                            is_const<Sequence>
                          , tuples::null_type const
                          , tuples::null_type
                        >::type
                    > 
                type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
ne+ed8RtI+PXD2ImTznnjV+Z9i28T160Gh7oGhKnJRnmGqRIzfeczibdal8/ljdXyPVOqut6tcu6Kjb+cqXxSHH7rKTDWOIvQ/s7tI7siru6++JnZxh6jknffYB6WTr1Mj8k3aX8HutRF8sbb+piXv3JUn+ZLPfBfKDs2mNnG4+15BeyEfgjMjWHmBA/F8cP39Q5frNQ7O+zPscX3Tdb/QjZT3JXpq5i9Had8/1ukvPbvPqM
*/