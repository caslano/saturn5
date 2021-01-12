/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09272006_0719)
#define BOOST_FUSION_BEGIN_IMPL_09272006_0719

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef boost_tuple_iterator<Sequence> type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
3RHMsN4K6toBc73elEx5cr3xXG+YuGkS8ih7zPqe4ImOnTEs/Y/4mvvOtm/xt7U+QBrid7Qe+4Xcc2vxdyL+niD+ZuGv3gf1Dk1tUyZ1Ejvf+7uwauhE+2L7XV+iLefQPifnRlOm/ZZ1oyX2fN8O8Xsqfo+Uc9TAY2Noph+kv4S1v5rJeWJOlr6Po7tRVvSkdHPebyN5X6RHjqdS2pKjRrzjmiS7xraPSRfRernJR07N3Ly7
*/