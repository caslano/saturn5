
#ifndef BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt 21/sep/04: portability macro for the sake of MSVC 6.x-7.0;
// resolves conflicts with 'boost::numeric_cast' function template.
// use it in your own code _only_ if you care about compatibility with
// these outdated compilers!
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570) )
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast_
#else
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast
#endif

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename SourceTag, typename TargetTag > struct BOOST_MPL_AUX_NUMERIC_CAST
{
    template< typename N > struct apply;
};

}}

#endif // BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast.hpp
gBVGLawfny3LPj+9eK2J0rwgg9fioe5+Et0XB8P76uu9EqK3UQsMxYsHxe739xtQSwMECgAAAAgALWdKUj55WsBsAgAAoAQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNzAyVVQFAAG2SCRgjVRdT9swFH23lP9wVcRLteAk62C1sk6Ij5UNaEUD2gNCMsnNh0jtKnYL+feznZSOfUi8xIlzfO6955wk1qh0yhVOSFyJXJrlCdtn2WRqQqZJMncXmJ4dn7o7GpGY7hAx7Q6RPbIHC2w22PiqypDEDa7q1gAyrjkImZaYPn0ZtKgGHS8ND0KIggBmPzxyyjUySNb4AYIxXMuNeRMGEI7YaMwM5ttV4pGOnoHt2Ffugeb8CT1yyc3OlcyqvMKs5wk/wve1sBUMT8TC4JXnLOEFg0EUBtEnP0uP/I/j0WE0Gn8eeOQ4TXGl/RsuClQMHltTzCMnUmgU2r9EUeiSwaHbEpjqSgoGaS0V7lBJu0Lb5YumpV7WHjlfC9H6JXLTmxGgtZSekc5KYyXspXIantSV5eg0TN2DgXTTTkip9cpdnA3bXYgFX2Iva+S8gudKl3C7KhqeITMI2kEgTuVyyUXWcTFK96ezRXIxZ/v2dDSf3SQ0PAoi8H0L
*/