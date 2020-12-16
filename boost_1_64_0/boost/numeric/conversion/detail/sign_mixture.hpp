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
xjGD2QtzGRAeyHkLk23ZVTuwNMdTscKjnJZyb6M8r96xbkZ8/6I8z/z5+8bMa1hBaWbaGpc4S8uXUbDosQnWrLswJ2G1Pv5vOdcxmKuwaRuazuLeBuYg7MzBl6x1GTBnec/7k8oxd2HuwjZ1vTyaYz07ZzvT3kemsBYo5pxv6nSOJ0z24VulBV24n4DZC9t/qvW/zEGYXj5vfFQP1gKY7F/LlNIhXMcUC2429gvHU3nepYE/GKNliq0eVY+1PFXp36Saw1NZQ2B2wu4OmMF5dEFpS60x/yzmfkKxXgPWGnGuKG2pfjKqN+vEnJzj0tPHIYpxgFkJc3hzrQJzHibjXm1z22+sEzAXYV0LVDrE9QEm+7fzm8k1xgEmYzs3KaoF81oxm4WZb3jWhjnKdnbZ4sGzNsxT2LJmdvzZmDMwOWbd5t2JZE1Wnmc+/ZQHxxNWwGAjYVn39w3iuMzVbATsXJ6UT+z7XO2eibADI5e05pr65zphu+rvSmcuCRsOS6oSvYg5AStosGGw31W712Rs5xnpbhvW26EwD68LHE/9fK5/2fatQzsfziOYmzCLBBeeb2NhNsIqdo3fzT4o18Xp263jd0QwT2FdupXqwBjBHIU9PXDBlPNhvtb3IbCWC9dq/9YirJjx3/4Nhl0rHZmbc3MR9z3ZdiL3q5nc68OchenmNlrFtsCC5XVuLQozJ2C2wi45jk5hW2A2whxNH7Im6xYjz4SN+d2b5z8XmLmwIWdO7+P8U8zJs5Y7v9NXbGPHh1mskYpZ7dzNcQlRbFrzMh+45ig2/XDiMuaEYiFOt3lGaAR7aFjDB+G/6Tf6WXOsl3L9y7ZSQU6M7TyYpbCiCZ0yuN9VLHeePVtYP2FWwg5GmJfnmQtWSNilKmExjBFMb7ABsPPnczGXTJchJ4QFH5+xgXGAuQobFTviB8+3MDdhkywqsr5EwmyFPQ6byzW1A8xe2LnfuW7xDAuzE2ZTIuUyz7CKZTwZ8JpjrfRhut3hdsxrmINsS+2SXpxjMEdhYwp6GPF9j/K8pLPNtd9xh+mFNTDpo/1tEcXKfknnfLddnrMtbkcj/bjXV6xt5YeXmLswK2G3bv3PimuOcl3hI8+cGAeYjIOHq2sU4wBzEZbnRks9136YjNHAjnHav5UJk/17WfBpCOu18ry5XzLvM3eV55Ud3v8G37/AnKXFVHRg7VGs7tVLgzjWyvMGt9lnyjVgBX6WUdjZ+ODhzF2YqeHs2x+24vAzjkuFFVwfsi1g+3bWz3hhfWEt3Jr257yFFTJYH1gh00rM3QxhvWHph3rwzKVfqf09iATYRN+Ax8zrlazJ2dY7f/hijhnMSVhm2zzJHDOYi7CRUcU6c8xgemGxk7/GMj9Xaf2Lh808u6YN82yVdl13mF9N/zzMM5iNMLPl822YZzA7YX1c1h/gfIe5CtMVO1Wc65hynV/QupHMM8WqljmjnVNhlsLaVOkxgzUSZi1sZ9Z77ecjYU7Cni7oxnzJVK67deWNK7+TgtkLu5IypC3PY0r/5kXcsue5ajXmtGznvoPbuMYp1rDjEp59i8EchU1fE/6CaxXMSZrlxFP8jla5Z/HuDRn3LjDZv6UxJcYzRjAHYc3CrmbynbFipQKGMOcXKe280/3zPMYIJvOl2NA81qzJMBnbma0jK3HPp/TB1s6WZ8rbyj17XLHcxhgpZpRlM5kxgumFlayXdZtzMxm1R1jiwBtdud+FyXY+G5+wg/UFJp83x6voBb4vUK7zGNJvH/fJMFc5nlfLdWEcYHI8HdI3v2QcYDIOec8+TGEclOf1q9Z/NNdGmLuwoVPi23M+KH0f3v1ZCc4HpZ2bIyo34HjC5Pw7HNU=
*/