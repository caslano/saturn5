/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::deref<pos>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& s)
                {
                    return * fusion::advance<N>(s.first);
                }
            };
        };
    }
}}

#endif


/* at_impl.hpp
sHCJSNw7vt+v4s9gC/oaFiXu+5lHM9LrEWdtpMeszlRPcXM/tyTzHUlOFUlOJWnMEm6ucFuFe044CtOfXDCpYLLPp3NZNVtw1094vzCyZ2yEw9bRsbm/K+QiDV5nB1puOeSiNSXipWl2RiwqmFVUj36jE4J1pzNqv9O4Tn0p+Xweo+PbAui62S4YqdlK59saIIeTNQ1wkoLbB0zJqEPbId5d15NS1Awl2LqG6JPoi+3cW54N5xm1P8iH0BJ6VSY=
*/