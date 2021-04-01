
#ifndef BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

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
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::half_open_range_tag >
    : size_impl< aux::half_open_range_tag >
{
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
Pqc1Uy7xGb7/4n2m638ufr59Txczo37ANc6qyMoDkdGvsAMdm7x4gu5G3h7B4esZD/HgUpAlJGEigofkCUYXveBRK8U+FMIDicIlO/NPWCBLdTMXSz2LUOmC1ro8XTmmAEPBbyUnwVq3aq869Za1AFZqzi0zzWkrgvRM4hL4B6L+fpMwd+z7lvN8JXdKdZd02PneD1aLFMqxmuX3WJqqpkAxh+UmSs0FRIA4CtFi1vuqakd0tBn/ojv0flFbxBCHlYdS/raVEm/uM+KyTjk4zPsboj7TDOT4+6w/cDvgKm5SFcB8Lvt9x1uF4keo6Lu0EdF1OTrOu9kT3+SsXhmJNVV2dcPGhbzebeJvGB5e+fhLHyXlGaEnjR5lcqSyB+wWBuH4UGoGEIGJ1vr/EV/GusslguZXs9WhInRgNSzYCMUNJinJVfFHV8EIJZRHTztl5Qdbd3PS0dxm5Rphe0uj+6Ogr0X+rJhhXTODdzf18XLSMGkYFodPqDLHVrReJm+34usdx7yEhZrJKiv1AeXEILGwFquimA7S8NczVqHjhLvbnIqCr1vNI8ahYA==
*/