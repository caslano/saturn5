//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct udt_builtin_mixture
  : convdetail::get_udt_builtin_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                         ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                       >::type {} ;

} } // namespace boost::numeric

#endif



/* udt_builtin_mixture.hpp
PSf8iQCwWZ4x0uZXrwb2seWnDwBWahYr82unAZ+z5ZdmAH3GvEu+z/49ORM4mvCc8Jft7yOr1E96FpCyyubidTYvCV8pef+pUS7/e5L/ve38JQ8G7tes8tvcVf7oocAw4VMVfpakidrpY3HgHbvuhyrpPzuQfjZwu80iVXhBeJct27D5zpPlf5Z8254MOz2jsn4iwg+x/x6p0r5J4cfY8oNV6icvPEDkF4T7CS8Kn+b0r0oe
*/