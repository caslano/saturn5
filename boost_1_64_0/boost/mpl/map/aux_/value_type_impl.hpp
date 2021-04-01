
#ifndef BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct value_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : second<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
UJfkp/PeBWyr2X7wwQjq9s4YlQkKKmxNepId/km+E9KXUd0KfMtpoaU1rykTutoc4Z15eP28RlnmHG36HrpkGqLN4betsTKcZcvGGGQLnhYpqDQtYpWNF4rQw74jdK7kEc6NOdPShQvAaiuS+vKdDYtML53nQ/fq44BPjur81wWffG33Yfa1f6CGo9B2F9hIbLklj17lkhQaHcG5eKA/u032z9/DCF4f0rrFdY90Ip5GmMXMKwYcJ5Z7zF7cItmUmuZmYiLmgf/NRUyw8i72+7mxHZ+vnhDqJ+iUGshbpC1bHzWKEFWt9uWUQMHLx/RPsKPMOaNjkLwSv/b6tAdHlY0Ppt+FHGAOJFXqGs7RR4t/XoRmz4OWe2U5HgyJPQKSlYo5un7EToh2eOf9ePY8fmwK5kAEWZfu0HrVdlq5fhRcDNDe7Iv7CnXYxHPA+muVPoQyZNXyCuW2N+4zv/V1Dnh7rCxWtvCEFvgkmP/OVjUmuK4r+E8sBImRxFSiCa3easoT80eQaFfnLdlX/j5KnT1QYN4zTFqUsimupGRIAS4GvArqpGW5eMXXtA==
*/