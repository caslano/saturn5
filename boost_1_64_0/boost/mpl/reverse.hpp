
#ifndef BOOST_MPL_REVERSE_HPP_INCLUDED
#define BOOST_MPL_REVERSE_HPP_INCLUDED

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

#include <boost/mpl/copy.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)
    >
struct reverse
    : reverse_copy<
          Sequence
        , Inserter
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, reverse)

}}

#endif // BOOST_MPL_REVERSE_HPP_INCLUDED

/* reverse.hpp
k5HlwshLxon7P2idU18mRC98XcS9T1hI0/v0xKFY4HSD5mCj+cTUcPKXqxemq1KlYmPoVNzRPeGO+eQsgWnbnj22suoEoXtnsjnb7Hvn63qplCYUQdG7PPWQHMEMQFiW7u2V8bYl/WybvTc2kBuJCPK3zwEjVhmAGc02JTataAimIXeBMjoC1hoEWDqjrUdEhSicVOu5Md1OMIlwx2p8DSDHn3TU31lYE97JuODnnzp/0AMLNgauEsu7OwvTYW6iRnMdjZ+ZxQd1kMoMnRKnSfkcc55Lzvb4Ql9LdSTY9VDTFoLyW5upUNrxUK5RWiSduH2391Ro1hBqc31wHDZ0fQDlnOOhNDi6nnqfsCKghOGfYyVMiEYgvivfiEDNH5PU7YkN1i/Pga8WLd277qamWt7/0iGpCKijvVCNHX5OoR46cYP9m1WRo/BIHV44TVusiybDBoP9pPEsXlOEm3vyouNPovEa57gLuaxuaop4V57sqkdHEmJAIFacl1RPQmJbyoCiK3OtqTmX5mjabj2I3p2QIsrLh/qlc1mR2WO7qTOCr6m4x2+rdBfhNg==
*/