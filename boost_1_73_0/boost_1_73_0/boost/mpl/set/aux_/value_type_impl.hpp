
#ifndef BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct value_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
4371KKiCKViUPJ/AnP0SPGenmJWsBwifwG2wZ78KftvpgZBHTTf3+z0AYcPrUkCRFFS6M+nQlSucrtykdNHYc5aworppjF4Wd5FNwYEftDsnub9lQVWXTAr1H8exLRCxsN4BWjaHisu4TzfUiyBn1yfxh0RhUFexTJHQoEp4IcOUaxzUKc/zoIiuOSeK8u3lzSGWPfnWQdhva6I8/hjDfg1ryWYiGC1ZJVPej0nzxv5S14aVybaBXckw2FashDIx7F4vjAMBQ8YK+EXEvPoC9OMlVkIcSl5xyrMpeJ7Zs95/H1gP/K/ovxXdSW49J2so76cHVu8W6bT22UpdufdX+fx7/gtQSwMECgAAAAgALWdKUpKXSS7NAQAAZwMAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4N1VUBQABtkgkYK1TwWrbQBC9L/gfBpkcZVmGNsEohhKSJjTUJnF7MT6srZG0VN4RuyMb/X1nJTu+5FQKQjur2Xkz771Vxuh5rz0uVGZsQbL8we5ELvcL9bxer/oXfH9cq7Km3c7YUm224LQtUT19e3n99faosuRakyUDzFiN4R3dEV3sTY4qc9jUneRzzTodsJN0ksJsOoXlj5F6aq3t4gp1PocOvTwj9UCW0XL8
*/