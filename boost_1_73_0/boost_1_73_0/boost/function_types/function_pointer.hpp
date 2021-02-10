
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_pointer
    {
      typedef typename function_types::function_type<Types,Tag>::type * type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* function_pointer.hpp
H9788MaHEyYFLyAyXM55de3Dp8ze+XfO7u4CzX/2gRtgRbClMM6FBq0WZsUqDnhdiJRLzTNgGjKu00rM8YeQYHIOC1Fw6I0nl4PRf3xY5SLNGz1rVYPOVV1kkLNbDhVPubh1akpWGVAL1ID6M6EN6qyNUDJA8xwMr5a6UUNOsEIrYLdMFGyO5piB3JhSf+x207oqMJJuplLdTVsogtwsd6K6RG+WbA2qNGAU1Jr7QOd9WKpMLOgbIcKbZT0vhM79B7fQoMy6qgLNi6JRh6KCaxcCh6hBy6eTUKL3wtCXVlKTtVWullsHEdZG0aKuJJpDWPBcphB4H2qZ8cqet0C0VhqULeTfoOzB9wyURK+gE0YwiDowZ1poHz4P4rPxLIbP4XQajuJLGJ9COLps9J0PRieYGwKtVsDvyopr9KICsSwLwbMt49+10r0gPoPebDocT+Ikis6S8/7l6WzUiwfjEbyDztsP8GstMb3f/tiBTiHmxD+8D969D97gDfqVcKbXieaGmMa/mFQa9UZnMAov+t4+5VevIWVFMWfpDSww1BupVhJypQ2mjUlzIa+hUNcitaqiy9F4Eg0iL5AL7+9CpkWdcfhE9l1K5j97Hpf1EqxLN7k2mLR/eGCDOz+L4jBOTgejfhKenCTxGK+H
*/