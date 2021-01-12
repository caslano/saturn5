
#ifndef BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct value_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
3lzTtCNsHaDN9+nHZHHY85Ww+8pt2XzVYYGkOY+w6gfqCUmmSgUbKRDT6hTs08RMVQp2sRhjiWD3LsXYvPj76CwTy1ah4N8kHlWhxF1vIy5VqFhnOzGtQsHeSEyrz9hF7XCYE694R3LmbUpf2drraawDR4rATd3Wk8gsidFXvVIgnjdLQlsbiKPkOFArH5wcPzS8VFvGs4nE+B15VdnhjdoM7CDBxrPIt7c5+ZnV1aXDeD2p
*/