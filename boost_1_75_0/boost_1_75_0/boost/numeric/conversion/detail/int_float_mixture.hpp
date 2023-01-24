//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/config.hpp"
#include "boost/limits.hpp"

#include "boost/numeric/conversion/int_float_mixture_enum.hpp"
#include "boost/numeric/conversion/detail/meta.hpp"

#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  // Integral Constants for 'IntFloatMixture'
  typedef mpl::integral_c<int_float_mixture_enum, integral_to_integral> int2int_c ;
  typedef mpl::integral_c<int_float_mixture_enum, integral_to_float>    int2float_c ;
  typedef mpl::integral_c<int_float_mixture_enum, float_to_integral>    float2int_c ;
  typedef mpl::integral_c<int_float_mixture_enum, float_to_float>       float2float_c ;

  // Metafunction:
  //
  //   get_int_float_mixture<T,S>::type
  //
  // Selects the appropriate Int-Float Mixture Integral Constant for the combination T,S.
  //
  template<class T,class S>
  struct get_int_float_mixture
  {
    typedef mpl::bool_< ::std::numeric_limits<S>::is_integer > S_int ;
    typedef mpl::bool_< ::std::numeric_limits<T>::is_integer > T_int ;

    typedef typename
      for_both<S_int, T_int, int2int_c, int2float_c, float2int_c, float2float_c>::type
        type ;
  } ;

  // Metafunction:
  //
  //   for_int_float_mixture<Mixture,int_int,int_float,float_int,float_float>::type
  //
  // {Mixture} is one of the Integral Constants for Mixture, declared above.
  // {int_int,int_float,float_int,float_float} are aribtrary types. (not metafunctions)
  //
  // According to the value of 'IntFloatMixture', selects the corresponding type.
  //
  template<class IntFloatMixture, class Int2Int, class Int2Float, class Float2Int, class Float2Float>
  struct for_int_float_mixture
  {
    typedef typename
      ct_switch4<IntFloatMixture
                 ,int2int_c, int2float_c, float2int_c  // default
                 ,Int2Int  , Int2Float  , Float2Int  , Float2Float
                >::type
        type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
h7r0GIJsl/rmZIOgJ2BAfvgnLJIFi6D7MpjVILS4vDqctwHrH01mfrQU/VnxCeIcsA3k1UAxEofDC/35UYPAgpOu3a9pK9jlFXCpakXtmri2kW8GTZzUqA7aH+GvUskPkbtmFTEP/ab6MFIX0J0DeGwnIe+IWS416+SjCPhLyacGc9CV5GaKlZhXej1FGigUQgrzQss1+lkjdlA1NwV65FmAMiiXNn1ds/4JcUBZyR4Ca3jdz3rNMaz+iJEAcHMs3AzN0Kw1IQOLFUAB//1QtID/p6NhfclNmBk9LOC/OYMJ+AyNsqlP9UmUu/CsWXwE53MVgp4mjPFvXmarRJCw0PS7KTQdo8DUN29pD/td6PX8Ko4sYQ5fT9SFoVdGd4DVgskkkbuIDsEU+KIneC3iw70lzlyb7w504rejZa7IQ9EHOEJy7HesI49+dK9DgFGkEUVaGRD9deCk/RSGWB4FBePN7vymfBzui1VBbgqmYcEcGzwMvaqNLBjLyNy00UVbs874kUG5CKE86cdoKDeFdCiLlSepzyhIO27qBOki9aKbOKSt9OouBDbPl+zMHTPej3VCK7E+ttYgN8Hh5qg6ysozlQTaZoqVEyiPeKu/D5CstQHyWlcvPappLZdQod5dmvWtFtIdPhvA0EjN+mJL9HjTwuP1eWPG+rcbO4zVeiN0oC66kY/2jh8JL1rq4fylkVRhvhTk+qe0vAdX
*/