//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/int_float_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct int_float_mixture
  : convdetail::get_int_float_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                       ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                     >::type {} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
mlLmqQg6f53Lwn0GcI5gg212w9tD4UiPQYP3qn+cSL20vqAwn3ZAheF9e+Hgj0kNDGpdbjR6MmCGWbeWCsWHL3eZsLEKu1rxGdTXoefR5bAaQVkLv7+3S1grV2bRAPAh+RPXyTS2Lr/lTy/ZPmaAz2wsyDu5Q+RsjbkDrs3gVacZpqnN4UvW7CHPfWllYBZBebPT3B8c8M5mNjFSFijIb8eB3YrTDXtVrPAus1nxls0rdIm5ZY5gW9X6eeF6Fr6RP/5LE6vK6/lzRuI+XeA8bZVttDlvAErPU04jOKhfp/rhAY8uiULs544+iOlZJjwmVAjEAxPvqmUNeDAEQReKCHzyGMHorQMBE36kzaSCFVcvM8LkoHjxkayzAeJ0j/UmdQNi92q/lK1WnH/oEfib6F6g0oVVt3/+Yr5+l6qD/QiqJnM3Z/PYAGcJADsNs82mJvyPnS8zdu7CUcZ5XlADPzBGdyQFT3H10MEKg8Ef5NE/NjkkXTwThMIG1cIJDw99bsRd3tk7alM6iqWrWiKm/2OVbVEbecmPeB/a8y+YbpxkrlMGfFW3WflDKA==
*/