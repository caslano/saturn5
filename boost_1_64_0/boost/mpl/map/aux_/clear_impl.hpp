
#ifndef BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef map0<> type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
3bUpt6jtHHc7uvVb5WNs2mwfZcxy0zIze1yfiBRMDW/MGBqMu/bJcllKF/FzdIzuK/YmEx9S2iGQ+NEhwYOKAEx3GpW38LOr1AbdghnIHqVnGygKYihBIjtiXY52i7AXbMArWOVY1wwQqs2fd08nLb/9/lyDEILGzyKKXAnCGShBjUsDTJfiBHHspsuZ81DYTgrH/cJELpvc3ohNrX9Oz24np6gUEPrfIhh9pogPP474QFzM85KVQnHTc+Ee1zFafkNnxA1OENzH9rgA9X6k04LLChvdXiiYEQ3xdQkvVRqWXHA/WfPnAMnpAYlI+Er8Ae4V5YunHV1ngT4GDh/pADjsW9n7DLqFFr1+d+t1+Xj+g1D4J2YSeUUgf6UxxJTDXu8X+tN3dRdl8lWLEj1elxSypHa61g6Dp5x28cm3oKRc9rNfSl/OysLZt77us269LjHlUo6+QC4BE6kpQoIFbBmHFqAbrLwnsFF7YuNF3R4QcAJbFwxJNKzfRBsFNnGWjyMTzt3hoxPMXzefn22QGi3MviuhpAi4P6n7YVsEsNlAXmmCHnyLkcCNuQ==
*/