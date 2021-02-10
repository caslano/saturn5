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
RVJEQVRBLjNVVAUAAbZIJGCtVGFvm0gQ/c6vGHFSlVgUmmt1bdqoOmo7DToClsFtLVlCa3Yd9g7vInaxYyk/vrMLvlxyqZoPxcILw87Mmzdv1l+5MPpll+ObcPDTq7B3gReuR6dZK/9mpX7aoSjuoP+h4wrXZ6QK4N7rrjiFZ3ndwYn1KoZcF+a5KJ6RbmVAmr/AOK8K84iW3nPwH8vm0PKbSsPJ+BTOzs/fwUv4/dXZuQcTIjirIdNMrFl748EFtZY/K3J76yv20QOmgdT+g4B5xRUoudF70jLA55qXTChGgSigTJUtX+MLF6ArBhteMxins2WUfPZgX/GyGuIcZAeqkl1NoSI7Bi0rGd/1YRrSapAbjIDxKVcaY3aaS+FjegaatVs1hDEgSK0kkB3hNVljOqKh0rpR74Og7NoaKwmoLFVQHqnwK719VNUS0WzJAWSjQUvoFPPA7PdgKynfmBUpQmPTrWuuKu8eFiYUNJAtKFbXQzh05Uz1JTDIBrY8sxMaRM+1WZQUymTbV3L7YCPSOgTadK3AdEgL7qMSifegE5S1dr8l4phlYNlS/pOW3WOnIAWiAjfMIMpcWBPFlQdfo/wqXeTwNZzPwyRfQnoJYbIc4v0VJRPUBsesLbDbpmUKUbTAt03NGX2Q
*/