
#ifndef BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::map_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
+Ul18EPwXvAIuBFsY3rgx0H1KfdPwAPgp+Ab4DGwjWOU6aBMX4K9we/AQvA4OI5lxfCeBVrgHDAArqZlDz4GdgSfBjPBPWAOyDbKBUMYn53AHDAPPBXESLXPAvPBc8HO4DCwKzgS7Ab+HOwOFoM9wHFgL3Ai2BssB/uA08G+oA2ezHyBp4DrwNPBR8EzmK+g/F6ejboQZ4Iouzgb/CIoPZZspC0GM3/g+cwfeAHYAI7kfcELwU1gBHwMLAR3gZc=
*/