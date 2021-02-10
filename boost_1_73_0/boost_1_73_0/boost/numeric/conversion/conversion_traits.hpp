//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/conversion_traits.hpp"
#include "boost/detail/workaround.hpp"
#include "boost/config.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct conversion_traits 
    : convdetail::get_conversion_traits<T,S>::type 
{
} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* conversion_traits.hpp
VVQFAAG2SCRg7Vdtb9s2EP6uX3H1kME2lChpv6xxO8zLS2vUswNHQREgAEFLlMWBEgWSSuIt/e+7kyW/tEntoQGGolNgkz7e+z13VILu8z0edGHrw6oPwwfXSuLC6D9F5B7nZuwBFn8odYPrNiMBrEQeWAe2izxAuxJhtZU3tGdsm6Eb8o2+ApK8YbRFCoqR5Iku5kbOUgftkw4cvX79C+zDy8OXhz6c8lwKBZdO5FNhZj68iSvKbym/vz+w4lcfhAOuDmpVYSotWJ24O24E4F7JSORWxMAtxMJGRk7xh8zBpQISqQScjC+uB6N3PtylMkpJyVyXYFNdqhhSfivAiEjI24WOghsHOkFxVB5L61Bh6aTOD9C2ACdMZkkHmefKauC3XCo+RUPcQepcYY+DICqNQu+DWEc2iJrwD1KXLSO5RicyPgddOHAaSit8IE4fMh3LhFZMCBKLcqqkTf2VN2gqjwNtwAqlSBfKSWEXbgu4rNPjExsU6LF0tFidWzJ1l+psgxHzSFqS0uRoCPOATLHGNPtQ5rEwFXMVeWOizmmV4CdLs/I3Bp2jM9DqX8LgsgVTbqX14eMgfD++CuFjfzLpj8JrGJ9Df3RNyj4MRqdYeonGDIj7wgiLxg3IrFBSxLXN53sC7yeZR6qM
*/