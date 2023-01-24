/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };

    template <>
    struct begin_impl<assoc_struct_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    struct_iterator_tag
                  , assoc_struct_category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
AbT8pBPJRPQBAV667VYtQSJYghy95FWN3dNeI5OAW999g3OxtB9KaUUg5wp5j+CykXLkPWrtICmZV8zkLJ/uCjALiUHjksz/N12ZDin+1yP+li1w1980CN3+N7bErX9HB+eh4qYIH9B4bppLdpGtCMxNk1M3N02uq6HcNC2GNDk3zbyd+v9zbprz327IrmQek83S1/wr5Rg10G4alredtvQ1oH1+6V+vLTXbJ3xnPe0DskJLFL9e/LrVJP1ylWY5dqdslmcDmgVX+9AsMWazTNvxPzRLkKyEvdVQs1x7VDbGFUepMTbwgF5//gYCuA7fnmXOgg1Nzd/gyvDWIHoC/OexDkje2C5PHGFJP3sTLekreUk/AUOB7A89iUP3DX1w6I7oQ0t6KGS02kJL+kqklradl/T47IIFdozJJMdnShOB9v973dzBR9+ezS52OktPnpCtl0DCH9TkvTJl0L4wiu4k1/Bm8ngC5hGjeUKb5q2Gox3osoWitNuXWQ3YZfddQIdtefA67Ne6fQNz4H08T8IDhtDPyQVoETq8n4DS2TC3zhM8FDjICeeL73RO8V0znHnZZfGyi3j5cUyc5MUoqXyyB3zjLrnGka/winTimRDwwkkQf0B/6yXRgPznAB+IXbylkW3V4gemchR+Lrb42RdK/FRb/FQTPzfUw0+1yk91I/yUhBI/XArqt2rBU+NchZ+Xtpv8DGR+Ki1+
*/