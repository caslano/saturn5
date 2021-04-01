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
mKWI8GQi3jMPVVd/h4I3mwo32S/vTfHHEkLanisbAT6hwhEtXu6c4nz/XBxYecTPqOCY1EjSBDOub08DlLWspQBSul71/dxge1azrtTDwx3BHaqxoYIbm2a8WdnPzZqT6u/rPxO794AHWThW4RFqXEdDvIfwFscryqKbjZTqVRz3+u7zOCxv8VwSBJ0D/NNhoeLWH3KwNx+6l73fXZ9fBlfQEut6qEwYM6fnOpvDLiPTCdIAoqUE210wRQ40Dd0L9AGpV6tu0a1hJKjl3kcxoReeWfFaVFhbGFiRYWQ3s+qxsGuuhONiMW2C6QTHANmA4ibSrQOyqboGTokZxOZ/eFkKMySBo4m46qBF2GE9iQpDdmzem2X89cEE0z032sAFhR6kvGl18KMLoGlZMHoxkMiFT1TACVg2Z/ipiy66girC1SX8M7IVUPUPbTA24l+IW6uHimeFD4ZR6JNKRMuiQgYrF8OLOC+AK34nEHcTC+YxOZQC+lNXxsSeHTlUTYAcoISoUC3fR5c4ZPx92ZTaasAQrsad8wR+UBXcqHgAUC60SwfdbHfnmscqYg==
*/