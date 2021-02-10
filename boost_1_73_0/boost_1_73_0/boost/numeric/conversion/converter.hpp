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
BbScsFiqlrdGykQWi2k5q8gBxooscHI1GQ5G52N2PhiehYM/zgDVeDLHeuJxO0q5gS7ydLy/Pai4oUvA8KEbl4WAtzC6Gg57eKZ0Pqty6WQmiEBKMGRkIbEzNv7Q85A8U3rKFZO5dG06YO+G49/7Q9YfDjsVg+B2vjgmQwta465LEaB8aYYqVBiNuFBzIBHJlfxrUSoSZktdmOwqMqhdWp3OUFOe6PYiqi/y4cPPjbVOFVXSRg0doHQAJIXBMJO2dQgx40Nrzx7vxY9o70CCLYae3SEcEOtYEORr79nOTd7yvc0RSbYZ83GHvlQ7NOmvaUVMojltKlcqtzCvGhFPRWOREjwvCyJ/Wni8zNeLt7B/tMX5VXIxb7XbPcIvznQMYP8IsB0o83sq3sn5jfzBBibO+8h9ygajQfjVKBpYWOFw1qzVanwRMlx8IIz2vsq2quhRjbTPoYA4SrTJGtz962I38v9ZsXfsFEvXUYLDsL41JHYuTrb3YXhBxnVpIvF/wzQN8+pw14bBi4Uuz2UOKek4frXBNLsetDa8bi076tXhM3YUFZFNzsKryQgb62wyGU+eAzJPDle8BVK8otUaYOqL4RGejc56QXw742Klo0HGDpn6tonzFPDJ7x8B+N/nTfGtgEajYu114bOD
*/