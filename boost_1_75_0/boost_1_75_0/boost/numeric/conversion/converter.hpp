//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_CONVERTER_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERTER_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/conversion_traits.hpp"
#include "boost/numeric/conversion/converter_policies.hpp"

#include "boost/numeric/conversion/detail/converter.hpp"

namespace boost { namespace numeric 
{

template<class T,
         class S,
         class Traits           = conversion_traits<T,S>,
         class OverflowHandler  = def_overflow_handler,
         class Float2IntRounder = Trunc< BOOST_DEDUCED_TYPENAME Traits::source_type>  ,
         class RawConverter     = raw_converter<Traits>,
         class UserRangeChecker = UseInternalRangeChecker
        >
struct converter : convdetail::get_converter_impl<Traits,
                                                  OverflowHandler,
                                                  Float2IntRounder,
                                                  RawConverter,
                                                  UserRangeChecker
                                                 >::type
{
  typedef Traits traits ;

  typedef typename Traits::argument_type argument_type ;
  typedef typename Traits::result_type   result_type   ;

  result_type operator() ( argument_type s ) const { return this->convert(s) ; }
} ;



template<class S,
         class OverflowHandler  = def_overflow_handler,
         class Float2IntRounder = Trunc<S>  ,
         class UserRangeChecker = UseInternalRangeChecker
        >
struct make_converter_from
{
  template<class T,
           class Traits       = conversion_traits<T,S>,
           class RawConverter = raw_converter<Traits>
          > 
  struct to
  {
    typedef converter<T,S,Traits,OverflowHandler,Float2IntRounder,RawConverter,UserRangeChecker> type ;
  } ;

} ;

} } // namespace boost::numeric

#endif



/* converter.hpp
rm+jGn/wgWZBz6TG6yxnRdQ6GVRz0yXv8Mr1GNBOCpMrQ2901ORE1KGkyblzWZeanF29dDtfeB1uMUSvQ0eD8+6RHQ3ODO8Dy+l/nGY4n2F+uWa9DPAksHFFLA5R7h/N+rehUTi0ZOT5aHr+vrQrHNJtQOZXhOix89wlsROwjDyrIyeQ2mtBNC0JJmDDn0ecDzL1XKqnUmLWUzL5S5aoetH62BJixrYAjcIxA5s34jwHdv15Daz8kS4G9k+xM/29XzOfY999nX72fbdS33efpJ/X/q8659r9cMYcA5+yDiO54awj6QCfP53XaAqruoDPYz06w2fymXPBp2Z4R9oZ+BixW/AN5AcCJUBcysTiyWWadUhaFNY/Ovx8xrqmMhZyHXNcrjkdGaJTXMudbGJcHvoP75jkMvfmQrESxZ7cF/G0Eqs+oGscvG9G7ou4h32X1T+iH7b1lEmHHbt/Yefa9CFRM6kehjO5pp5yAbFm8Q5xLRbz01Zgp0Sobgntir6/Qr8/KfTBf5OzbHWgY6pM5qlwOFkQ1tfHJSxR9yQTJ3Iqhf78lhItS/AKPQCrJX+EYVVGoCI36pwSUtxUrCEBUqzai7AI4MHiv3JoAGEwlLkQMzYe9sUgnLuJJrKdTWRFKIkcB8S1vvSsempuiH5l5GCjELoWaOCG34iDlBkUHxuEFJLOMH+3ADkvC/6hJK24srfyMCEqN6YMw5Zr
*/