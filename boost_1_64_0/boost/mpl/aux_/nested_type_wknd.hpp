
#ifndef BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x530)) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))

namespace boost { namespace mpl { namespace aux {
template< typename T > struct nested_type_wknd
    : T::type
{
};
}}}

#if BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    aux::nested_type_wknd<T> \
/**/
#else
#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    ::boost::mpl::aux::nested_type_wknd<T> \
/**/
#endif

#else // !BOOST_MPL_CFG_GCC et al.

#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) T::type

#endif 

#endif // BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

/* nested_type_wknd.hpp
5thIaAGra1p1xYe/H+mosw+90qsDSP99/ZVvDgTl6PqErXZcw7rXxhxTTkxTS3n9V4SJ4MNLrNdIExfaIuiz7rFUeCcR3e2LujLe67jznJ7ABXWMKnwaVzdhyAeNlVj1GmTd/GeY2oTOCT5urVDGnFLv4XU0DoYmLKeZTbZzK156T9u3wyLbZKf8J5lH5wudd+BCQJ3TeDqdzoYbNGjiruZdv/BDUbJsHfdgTDkV004kBI/bqxUHgDggYHCE5hW/qz0xEYNl2/5gAJ58xfESmkI1h53KuiYRtiYC9InhHysGFjb+iJxEXgQbOLCegFpLmUkhh28gaThp7oEFlCSzpxAIaSu6AV1GxDE8gIp8c47DcbnHjWd8JnUu0WqVKYCiGDQCKYGKkoJleRP8zuot4djXzlBo8+pQ45CwdqKXuQ/Vw26cxRe6fKAPcWpqYnrXe+qoTNxA4x7QD23YAEXpnvu5STLgAyuskYaPeyV7M7pmcBcjTuAZ3cyoWUjTrUoxTawI2An+HJb67oJfSB3KaSrf2YtzvHCxEW1s6nBZ5UNnNgtTT0jUOQL5Fw==
*/