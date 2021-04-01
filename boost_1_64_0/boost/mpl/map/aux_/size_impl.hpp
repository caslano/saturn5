
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
HCpoMD6GDU9OQXdNKu3xT5KQ6Gd0WUhiabaFZYZakPeVc42x8/YNloPTGB4tEyWU6hiLv8nifC8oHPZebdzEA3xk4YjKt5INHu7WccboAZaI1jWpm4KVv3fd9ay7kRoU8mgci/lR25GecM+c61neDWhpnAjt9tSer0M6kde703msew8uOKqxlSmRDiHXZiwoEaesWrSbetkAPBoo1P0+6g4gvM3uy8TL+xfr250Y0VfZuPCRF6aFV9d9kWI1jm8gGM5PJ5JySvgJD8YU+2Vaw/urzxfNcl8hRrNzRXn9khx4gqQxL1JMG7i6gDfLMYcnHADY+LRYbHkc5gN+FFzCFtkPMPZjp71kLNC6/0E7zg8ULgaTEk+VjfbMCLb+r2FkJRGjMsECoPp638ygSN/Y8oHMwYNgvXQ+osAyhgVF3Rc8AegMDFs2paSVIrg5Rr+DIuGQqBKSO71saBByY68150Oum0P3Z3MXopFIOMICXeuRIWWACTg6VQaWUlQKmVWiz92D0IoXfQ3YOIREc98GgLivqBNS12FAPeZHm5S3VFQQ5EY/pdv/LK1wjQ==
*/