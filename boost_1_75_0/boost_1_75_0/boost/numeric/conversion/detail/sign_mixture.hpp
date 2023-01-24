//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_SIGN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_SIGN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/config.hpp"
#include "boost/limits.hpp"

#include "boost/numeric/conversion/sign_mixture_enum.hpp"
#include "boost/numeric/conversion/detail/meta.hpp"

#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  // Integral Constants for 'SignMixture'
  typedef mpl::integral_c<sign_mixture_enum, unsigned_to_unsigned> unsig2unsig_c ;
  typedef mpl::integral_c<sign_mixture_enum, signed_to_signed>     sig2sig_c ;
  typedef mpl::integral_c<sign_mixture_enum, signed_to_unsigned>   sig2unsig_c ;
  typedef mpl::integral_c<sign_mixture_enum, unsigned_to_signed>   unsig2sig_c ;

  // Metafunction:
  //
  //   get_sign_mixture<T,S>::type
  //
  // Selects the appropriate SignMixture Integral Constant for the combination T,S.
  //
  template<class T,class S>
  struct get_sign_mixture
  {
    typedef mpl::bool_< ::std::numeric_limits<S>::is_signed > S_signed ;
    typedef mpl::bool_< ::std::numeric_limits<T>::is_signed > T_signed ;

    typedef typename
      for_both<S_signed, T_signed, sig2sig_c, sig2unsig_c, unsig2sig_c, unsig2unsig_c>::type
        type ;
  } ;

  // Metafunction:
  //
  //   for_sign_mixture<SignMixture,Sig2Sig,Sig2Unsig,Unsig2Sig,Unsig2Unsig>::type
  //
  // {SignMixture} is one of the Integral Constants for SignMixture, declared above.
  // {Sig2Sig,Sig2Unsig,Unsig2Sig,Unsig2Unsig} are aribtrary types. (not metafunctions)
  //
  // According to the value of 'SignMixture', selects the corresponding type.
  //
  template<class SignMixture, class Sig2Sig, class Sig2Unsig, class Unsig2Sig, class Unsig2Unsig>
  struct for_sign_mixture
  {
    typedef typename
      ct_switch4<SignMixture
                 , sig2sig_c, sig2unsig_c, unsig2sig_c  // default
                 , Sig2Sig  , Sig2Unsig  , Unsig2Sig  , Unsig2Unsig
                >::type
        type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* sign_mixture.hpp
SfSBwEFDOOUhYIAPf/Jyi/Dz9oOslr2yijNiK21MhnzHqOuFsCb1Q9FZRmfVqo9624H1ZvmvPmFn56kGsiIQjR91UNfWPY5P1RnQfIc6nf6f7I3RLWFA4Qp2qHLtwuXv64cqy9R8kNQ7cJw4kVcnFquAsUxqDYhv2RotAKqMpKELmDrTzo7VKI7E+4oRz1aBztbS9xlLsZPHB9A7Ofh2TuQ8ZpW99mrWq3nrJbx1DrbOwtYg7ljjoOPYr2nWRHrDP4H5glPKTZKHYOQeYpVQXkg0CpHvKFZPd4wVq3uPxZBkVVXbxZX1mtX6KVeYa9YkfmkH+XMPqmF9Fq5BWb2fmB6UM4dDE6WIr2VDLk9GFKVCuXkW53lObA7z02mdagVisO8//qUbS46h2l/+ETa6Q24Vb8CUGs2kU/kaGXvlQcCf3WS6eP0ArLay6GJJntWEqr9JESUY2+iLLkASuwAO0D7BhfthY+2n9349iDuXvTMA0DmUWOIMAuQkI6bbePcAY2JDknwKesr2zfYoC5uztzoCZ0zz8sPKlOQJ/hNSoM08L4cQ/Tl4yxFMGAtoKMwd4TS1ugP1cdgYc87ozZUxE5hsLvrfDaXABGF2OEecIO6q8ftgd4prXaqjptkCf484u1d7q476eoprpzfXfAO3vN923+0ITkc+whfnCsal425l5ZrcOQz8FDCnB6PzFBExfgTMa26r73LHugRm
*/