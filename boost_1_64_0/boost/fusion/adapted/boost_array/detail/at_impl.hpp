/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_27122005_1241)
#define BOOST_FUSION_AT_IMPL_27122005_1241

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<boost_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
JkIOWFOsOzYhssTEHWgXGHeNngl9ucxS13DjnKDePVy7WCpb41CE5vbYX3ncyWdG/gehDHCZU75Zd3RynQxr7bknHWgtCtGLmbmoEtv3jl5YkTfcVonGYL7+XztwvZzt0TVHo9icBdmyBlZWEZXgyyb75RroX249NNEj6N44n6ki6FsWXSPqbYnm+zK8TIAXyZ8PwlHvNuoBgqdrh/L5DvEa/SUcVzGzxKnczZFHXLSlWhXggoibJL1X8bk8Gz8Q5WQXJzaRbXiGWghBJuCyGFclRx8AMpvHzeMA5WMDAb8DFpa4qIFS1qzk+u2Nw/8ainDfwScAum2LQpqQahFUOZ/TZjBJMvZI1x82bDDF4wuJ+16mJkHGgwV7rr8/UwoEcx560ITQ0UfEbuzJEd4uJsXa/IoDCWiq+P9C8kolU2CYFZL2RsUQ6S/IaBp+wnSqdSJSuJ9AYJBRsrLP5pY3JHrloXel4cTQSOLJw6OG1UPvx8qsh/+ubgWyy3krDBI9SZL/ukl86iiOPRrQtxoppM17LiPFC0wlQ3Yx5ateFb3fJXliaweGHhzexQ==
*/