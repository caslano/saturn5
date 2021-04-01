
#ifndef BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct O1_size_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : Vector::size
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct O1_size_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : mpl::long_<N>
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
30tvppW7Qfmo/rkrVdKK4t3MKg0XFdqgxs0Tt7u6dUQgfOUCx6jQyU5K/rM1L4TfVnLB8Lvd0uIPJTUcJM583TtVNQp6KQhAaC7Zps4uCi8dgVTYgyv8Uvsyw4p0ZPM18KrBGgTaG1M7Jywc1Mynx95gxF7WYAqP2HcdnPoa4AlWvwQy0+frFUttOiNlIVrmO9nJ/BdmJjrBspfwlZBEdAreymEiPFJnukm/me2yKKRRrlZKHrxDUPLzypUEqM33/dambrXMTU/5aKpgSb/i0G9dYG5jsYAMAox2phTe7qtyBhpEgjmIRUPLPPgLerwgnwu3hNYJcfh1YWiMb4b+6E3Q23BhnTFPHqOipKd0W8BY929xE+lOBdXMjeZTQxLS3Gk1itRC/XexE/SASb+7VAg1Irq1ev21+jbhXAjShp0uFZBr1FCsnThKwbEQxhCTs1gHsQP4ZDkdASJuMISFwIRdAJR2WIaVWri60dp0rinfPisbn304e4LCx/C+7ka7GMEIajPgbMT7BiCeKuGcvg3evcGmReYjw2ckY7Jw3q4SnxZoznHBRACbfg==
*/