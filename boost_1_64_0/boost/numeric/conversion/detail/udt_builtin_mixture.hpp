//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/type_traits/is_arithmetic.hpp"

#include "boost/numeric/conversion/udt_builtin_mixture_enum.hpp"
#include "boost/numeric/conversion/detail/meta.hpp"

#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  // Integral Constants for 'UdtMixture'
  typedef mpl::integral_c<udt_builtin_mixture_enum, builtin_to_builtin> builtin2builtin_c ;
  typedef mpl::integral_c<udt_builtin_mixture_enum, builtin_to_udt>     builtin2udt_c ;
  typedef mpl::integral_c<udt_builtin_mixture_enum, udt_to_builtin>     udt2builtin_c ;
  typedef mpl::integral_c<udt_builtin_mixture_enum, udt_to_udt>         udt2udt_c ;

  // Metafunction:
  //
  //   for_udt_mixture<UdtMixture,BuiltIn2BuiltIn,BuiltIn2Udt,Udt2BuiltIn,Udt2Udt>::type
  //
  // {UdtMixture} is one of the Integral Constants for UdMixture, declared above.
  // {BuiltIn2BuiltIn,BuiltIn2Udt,Udt2BuiltIn,Udt2Udt} are aribtrary types. (not metafunctions)
  //
  // According to the value of 'UdtMixture', selects the corresponding type.
  //
  template<class UdtMixture, class BuiltIn2BuiltIn, class BuiltIn2Udt, class Udt2BuiltIn, class Udt2Udt>
  struct for_udt_builtin_mixture
  {
    typedef typename
      ct_switch4<UdtMixture
                 , builtin2builtin_c, builtin2udt_c, udt2builtin_c // default
                 , BuiltIn2BuiltIn  , BuiltIn2Udt  , Udt2BuiltIn  , Udt2Udt
                >::type
        type ;
  } ;

  // Metafunction:
  //
  //   get_udt_mixture<T,S>::type
  //
  // Selects the appropriate UdtMixture Integral Constant for the combination T,S.
  //
  template<class T,class S>
  struct get_udt_builtin_mixture
  {
    typedef is_arithmetic<S> S_builtin ;
    typedef is_arithmetic<T> T_builtin ;

    typedef typename
      for_both<S_builtin, T_builtin, builtin2builtin_c, builtin2udt_c, udt2builtin_c, udt2udt_c>::type
        type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* udt_builtin_mixture.hpp
riVr8pqcfZhrd/EE9xqwXMIur6yt/bvqMDdhujlLpnBfDgsQdj8t9TnHBeYhbOog43jWa5itHLN9P8P48yiwfMIqfyszmGs/zEVYueJNC7DvSh/MP6f24pxei1ouzHjBzizGHRYobFmtRO3fAoX5CBsSW57767WwIIN1g/W9/moi58NarQ+dYR2Nvgezzq9DW4S5fyjFGlkFZizs+dKaYYwDzFqYW+HGnJuNYFbCHme+vc3aA7MQNnGqSWOuDzAvYYOP5G/LvsM8hW073m0k4wezF9Ys1wgTxg9mJ+y85aMWzGtYlYF/19uOsAl2Edq/AVvOmOPZAfaqUtmFnLewggZrD2tae9gCntFhRw1reDtY3sD+LnxfXp73zLaBrTL7cB2DmRisLexlE7MU9g/mKsypQzrnbRos3vC8P3ZrToIz21kBzxPXpRS9xX3yEJijsI8hwaW53sKshU2qPbMyawjMStiv5CFmzEFYmsnftsTCCp31mc8aWZX3zDarkVm1uKeFmQjrk+cuYxuqWGr8u3Xcnyn2tuqzVOYuzEnY/GMZfF4LmKWwkY9Wd2cOKu3sO6jDVu75FFuwLXIVx1Ox2AN+/qw9MGNhWa5NLnAPDfMUdq7h5RDWZKWd+Z3CV/P7DpiNMMus3Q2Z10pbOn5e8oNnGZi9sKWT92ewnsFshe197Mr97gelLTu+1OXPBemqGevMhbV6O0P7931hZsKW/WxahGuqct3pIfe4p/WAWQnrapGch/UTZids/ZPtjFEITMY9rkmf/3N133E9d20cwNPe/dp7SFI0jCSzECI8RsjKJrsQGbc7e5M9KuK2FTLLDMneKxRRdgihsp7r7un5/K7fdf/x9Mf7db7fc851neuc8w2PIb4Zk5kye1yjpAn2DjJzZpFHnF3xu3IyE2bNV/o9RPzIeBw6tK8/F2tFWF2zuQWILRmPw4PiHHucTck8mY1ZMlMP93eympXWj8yg4GAg5qWlcj4jyDSrPX6F7yHCqnTc9gVzJix/c/EfrDFhxm2GIX7Bwl6e6NAbcy3s6ri7mbgjCLvkvPsu9gdhHsV/crA2hWVbReqhtgrzed9iGs5Lwl5/m3kc61bYANMAzMtsYUOHNM9C3IXd/mLeGnc1YUl568xR58kCWlTUyP+979GRLcj5lepqtVi77z7jEjCfZO7Mdjf6/g5jELZ4slsv5JmwgY8cUbNyxfsCr69DHBSrVNv51uj+HLVVWPsOE96gRpLxZy5zmYFat1W0m526cTvqkmh3Uu3LRdSQ1ar241XgPeQnWR1myzNeYgyxZDWYhdacMB17lbAEE+fOuKOTeTHrfvcz6qfhGtV2u8oL1qEvZLzdAtd69TAvot3dhevdkRNkfAwG5rfUECPRrlGfHZPRl7Wq7+vb6MtUxIiMt7P3CtBCX8j4+743b9UJ+SLaHbB0D0NfxPsefrG0Rb6sE9b4pQnqhLDOGg9jESMyD2YTHxfWQ4yELRytF4kYCdueeqMx8mW9qo3q5zMU5wlhv1cMccLdV9ii53+X4zutsNVXm2LsF4UdXpyIuS4VVqP5g79wJtqgaicXlj3DGWWDyDNXvSicJ8j4Onqv9yMD5wJh1d+Y4ncvr4UZTI9FHbRJUFeLrrCgCtscE+aD/BSmr9lIgTEkYj+qsHEP+ldFLRcWWLPWMJwxhfUJ0huF37UKW5VcUA3zKcwhJVtd+c1f1cb0nzoB+7uwgtxhLqjXwl61PDIWsSWzrrQ+ZJOTyqvgvERmyGzSiH8u47wkrF5gMtppbqRziNKonp1LQxzIzJl1vFzcFt97RLvZGVGodcFkCma5Zz56IZdEu8ZNfLHGRpHZMlt/5XNn7HGi3dE=
*/