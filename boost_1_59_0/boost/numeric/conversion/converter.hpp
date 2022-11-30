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
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
*/