
#ifndef BOOST_MPL_RATIONAL_C_HPP_INCLUDED
#define BOOST_MPL_RATIONAL_C_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<
      typename IntegerType
    , IntegerType N
    , IntegerType D = 1
    >
struct rational_c
{
    BOOST_STATIC_CONSTANT(IntegerType, numerator = N);
    BOOST_STATIC_CONSTANT(IntegerType, denominator = D);
    
    typedef rational_c<IntegerType,N,D> type;
    rational_c() {}
};

}}

#endif // BOOST_MPL_RATIONAL_C_HPP_INCLUDED

/* rational_c.hpp
9lUpt1ldcic2qPk4vY/KOvVoyWuzrN2OChvkcpuOEYlTdcJvAJ2xFkdqSR8o/tYZ0tRyQ/qHQVJJHRZw20mZPeCYzrBu9q5e/HEP9eZHI1h/XIICV4oL6v8myIRnvdUab5GS80ce9tNWT2A1eb8ZM2tVtYjobLPL/gErz5a1R50xYa6BG8HzQsCTouZcbbgkk/229HNc0eFga9+AkdfoCF4WFWQTCpxmbjg9XmegNRD0z8wZ/Edp0Cwzspd1TynjH81nlUQrk+51mUQWe7oqFbA/Ouiz6u4G53YIbxPK9/5AWK2BinDvLoYoo08gUIbfhja9KSETiCNpCQgvIHEirFRcVnoWcaBn89yN4W/SV/fcBBPPgSxbJWLxf/GVPK4pQ2C0Sg260csdIv3xFb6kk4AHioMEzGt6cl396eJLG6a08JuWuKNSRuiX7puINThyg8TGnYlDZMucIcD1s8sEM954UIVmcXtYswz2kgagKaGkUzLyN6nGzGsEYJMqp8wmEyRwQU3AgT2S7yP+JOPntBcLbFkhHasjNIVCk8Nri5Zr/an6rTXjADdqFQ==
*/