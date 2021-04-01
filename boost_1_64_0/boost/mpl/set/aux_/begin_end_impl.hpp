
#ifndef BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/set/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : s_iter_get<Set,typename Set::item_>
    {
    };
};

template<>
struct end_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef s_iter< Set,set0<> > type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
IadJngNPckpk0GcOpZDdPgyFcFWUxXvTPofzdroNHwf14lkqqlQACADBSa9wSE7XGqebNAE3mNmLDkWWDmXSHD3+KDFDeVrn1l+dI+LZ+T/fzup2ldWXrPAoVx9pJwyXcixHeD+dJUpZesypDfwxmlIaOXITipzIGVkZo7d0FdZuf6SKxq3kGUOAWwDdDJOQrTjI6wXMT7ArNvbb2hjDRJOF+C+2v8reCs7U0YtuWKvT4nVpK1R9QKBss9iPUSD2L0iB4CMWsocOcqBj4HLQXZYOGK+9Tan549stxZ9q6K+Ry13UhyXRgd5Ct3qJTIN2xxwHq0DutCbwCwKq5/SGK4QXptw9e7QUakIdCPjNWK3zHnB+jEhWL4BvuXT65HJtUBGTLbjz9uwui49JsZMg3X88Dn015OqldOiumiOIyFSAkNgyiaqEf+YNJT5u9DcmkTJntVLxgTdNU5b/D3egPcvvHMJPT9U1/PAIVTFt9u8O/4vk0adaZO8sOeFbKYX13G+5mr0csKt0x1NTVwwWX2d7r7Sz2zHM3rH8oz9fQSSClmonJJh/zODZFg==
*/