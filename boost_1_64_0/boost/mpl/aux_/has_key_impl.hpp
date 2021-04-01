
#ifndef BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy 

template< typename Tag > struct has_key_impl
{
    template< typename AssociativeSequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,has_key_impl)

}}

#endif // BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
iwo5oiXQ2X3KkPv3HsTqSrVOZvpTEONU6vMiN7AWDilE/kxtTI+GHEIajJ5Z1LxFWrT2SRk+tvYBazCtmECtT3eN/A2zPhpN/IXqzdtqppLaaVjX7+SuhGIf+OX5nBkTn7wcE9Li9XyQ4tKOf84+cYj/UsQEmfYHMDKw2XI4/bOk2WFEA2l9/N9V6ZzdT4EmaYcV29lyAsW+EIdJhDCEEimSksLUZx+ndXybIcMdcPQsahf61nxJE6vt+lQ/6ZEjKe9Pps92IJb1qV2YMyeEUocDp/MjgTQz4I2AW35BI9nwC82DAJbrl1+6EaIAtrzns4RmlokRvMQNeujByRIxoTUqdFkeIQtZgwmQ4vOBtwApVPWSV0yRqzA1zuALzIA/rVIS4ShEe2QX4I2uM9WsWJBGH6c4pYH0c/VKvFr4O6fSfeWSxJVqfI31n0KwP9oj8NgWGzaFsWkdnnQhvZdB8IBZZdBXTenh584pN6H2OIjfAJRnhJkHF/Fj8asNqFdW+KQunEgoTcW6rnXk3eDT5zBe/hdw7OjltxMCKbfMlXq5LuqIaA9HfO1clA==
*/