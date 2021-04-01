
#ifndef BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct key_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
tVieacV/0DXA7HJ+g4pCYijdISH3LwbL2cqxJs7/OewHjacPXFcEWlmNMui70PU4JWEZ6beC/QUePubHtyOzLHpmSemMaItZokdmVfp9fX1ExVvrSHGN1QfTM5A3N0PUJOF72KZBAbXmAGL/IoCa+qDXmxNqGiw9RjKy0DK4JCMOuSL1H6pJg9SYbg2O9fzUNFK0gOiKwQW5oF+c20gKnnmXBiJ+Mr4um6Miiqd7/5FRAKqjPilDPXlbY7gUw6XVOXZOIAcAzCECWXB1FEn9cEUcH58f2+774WxwhJ/ZzJjH8FrRAY0sJ1r3NjqAgLbf6ItEIjrhbyDqV1g3g2iERtT2ijFcmTgxD6/WwiKoo4qmtb6/zcRQtNwLCLNW/+2U3rrW9azqAykVCZWzCZ+fkKEKlhCb4dxDgtYHE4hFqgezokpI45df6lgrY4PW2VXDWrIRQ8H8IaoH73Sy4qAn1J8s40EWVFpJNmDIsYaMtY5CwBbzfBZCdCOX6DY2U2jny2IXWvDNe9Q1ogbJ7NodysC+YWyZN1WlkjeHfhUvdgH5DMJFPpDNbYCdOQ==
*/