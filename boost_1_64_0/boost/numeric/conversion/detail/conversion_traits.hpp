//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_CONVERSION_TRAITS_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_CONVERSION_TRAITS_FLC_12NOV2002_HPP

#include "boost/type_traits/is_arithmetic.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/remove_cv.hpp"

#include "boost/numeric/conversion/detail/meta.hpp"
#include "boost/numeric/conversion/detail/int_float_mixture.hpp"
#include "boost/numeric/conversion/detail/sign_mixture.hpp"
#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"
#include "boost/numeric/conversion/detail/is_subranged.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  //-------------------------------------------------------------------
  // Implementation of the Conversion Traits for T != S
  //
  // This is a VISIBLE base class of the user-level conversion_traits<> class.
  //-------------------------------------------------------------------
  template<class T,class S>
  struct non_trivial_traits_impl
  {
    typedef typename get_int_float_mixture   <T,S>::type int_float_mixture ;
    typedef typename get_sign_mixture        <T,S>::type sign_mixture ;
    typedef typename get_udt_builtin_mixture <T,S>::type udt_builtin_mixture ;

    typedef typename get_is_subranged<T,S>::type subranged ;

    typedef mpl::false_ trivial ;

    typedef T target_type ;
    typedef S source_type ;
    typedef T result_type ;

    typedef typename mpl::if_< is_arithmetic<S>, S, S const&>::type argument_type ;

    typedef typename mpl::if_<subranged,S,T>::type supertype ;
    typedef typename mpl::if_<subranged,T,S>::type subtype   ;
  } ;

  //-------------------------------------------------------------------
  // Implementation of the Conversion Traits for T == S
  //
  // This is a VISIBLE base class of the user-level conversion_traits<> class.
  //-------------------------------------------------------------------
  template<class N>
  struct trivial_traits_impl
  {
    typedef typename get_int_float_mixture  <N,N>::type int_float_mixture ;
    typedef typename get_sign_mixture       <N,N>::type sign_mixture ;
    typedef typename get_udt_builtin_mixture<N,N>::type udt_builtin_mixture ;

    typedef mpl::false_ subranged ;
    typedef mpl::true_  trivial ;

    typedef N        target_type ;
    typedef N        source_type ;
    typedef N const& result_type ;
    typedef N const& argument_type ;

    typedef N supertype ;
    typedef N subtype  ;

  } ;

  //-------------------------------------------------------------------
  // Top level implementation selector.
  //-------------------------------------------------------------------
  template<class T, class S>
  struct get_conversion_traits
  {
    typedef typename remove_cv<T>::type target_type ;
    typedef typename remove_cv<S>::type source_type ;

    typedef typename is_same<target_type,source_type>::type is_trivial ;

    typedef trivial_traits_impl    <target_type>             trivial_imp ;
    typedef non_trivial_traits_impl<target_type,source_type> non_trivial_imp ;

    typedef typename mpl::if_<is_trivial,trivial_imp,non_trivial_imp>::type type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* conversion_traits.hpp
aFbmz5oa3XMBcwIWZuhDaXxQ8LfXN9aJGMYWhrZUTmIfUhX7t8i4dvyeBGYn7J/KMz9wPwgLFuYfVYht+QJzNFgpY9y/47BlPFO2xnwQ1rpy+FLOFVhBYdXP2cxjnYAZGyzkz7mqdM27jBEsWFiRFXZlDIYc0MasJD7Y+zBgLvsurIQx2nX7ozXzBbbdMJ7F8UExv1EdGL827EO2FUieX4t5DbMQNmpfYFfmNcxDWNhdm4J8HsxSWMVD77TvtWHmwmL9PDtzrGG2wvZdmz2H+7NY1CnZlpb5ONYesFaG/hXDB007zxrDc2Mscz7bNrT2a8b6AjMX1tmiVzjrLsxdmEOVg8+ZS7FafhZV8tOyLZ+XbedH92f89IrVLtYtD/sAsxK2bGfDkpwrsCBh5h8+uHGuwFINZ+0if9oyznwh95jtGAcY+j6tANeqUJiNsIMTej5iDsKsha080LkQ95iKeRV5wfcMsTBTYaMuvHTguQNmK+xz9Qf7uP7BgoWFhLbkWK+FJRr6Vxgf3LKfu4rzqD1zIttKXGmxhu2EWQv7eWTGcbYT5iks9OUT7gsSlevGukcwrycrz0tLq8e1ahGssLCWVWsy7hmw0YY+BOODGR3Laj+b1oExyrYFp962Zd2FmQnb09JlNdsCsxGWvn3LM7YF5iLsaL/N1Zm7HbQYFfqT1zsDk7nGwSwMFvRn3t42usZaADMXdnDj6rmsBTAXYf6nl/K7kExYkLD2c0K5t3HpiJwQlrVwvhlzHiaf5xq35hLzGqY3WEF88Ml+MN/vVoFZCrvy80JDnplhPsJGVX/AuRIP8xVmVanqBJ6BYB7C3m/83op1F+YlbOFnf+5pLyht8TryfDbHpaOW1wWMEefb4UtY5ztxPmTb+JSkVD4PZimsZOfe9VnLYRbCXMeE2HGNg5kL21nQjfvyM+J5+fFBhYY+fCen66xZPnxw1uM915UQYXnxQb4G8ed4fuis/a5JID5wHHGuL3OX1/21OsOGWjLPYNbCoscmZrGdMGdh15NmMF8ewvyEDRy0nc+z7IKcF2aWNsiYazjMXNitQ61MmJ8wV2FG9ftov0sDcxDWNarIYdYlmKWwGo2bcq/RCGYrzGnzIM6xWKUtvgN0fTieMBNhD8MG8hzXQ7mn9bfzmcwl5Z6rIldNZX2BmQkr+/VVXcZI6cP8i265uDbCXIQ1Cp/JnEhVnmfbyHYu60sXLe558MG1rV0v86wG8zH5my8B+GDMi4F6rgE9GIdsi8w8MZ15DXMQ5m6xjn3IUGxdSsIEPg/mLKxJYnHubUx76nR2woqbh3swJ2CyLeaXeiUwJ2Dynu+flIrimqpcl9L95EiujTDZztk2mxy4PsCsheXZ7X+a8YPZCpu0+cNi1iyYlbAMj6Pcsy+D2QtrddPtM+OntCXi9sjvHGvleVeMfms//wnTC9uUXJrnqqfKeHr0Gz2Zez6lLWWShpfmvO2V09K+hW/nfgnmLuxWUsOvrEswJ2FG7512cg2Ayba4NrLiWtVKuW7R4jc9uEdRrrtx/nULxgEm+142JDiUc0Uxu8kl1vMso1jtWbvWsA7Cgg2WGx9cuvSV5/4PMAdhGSU3bOOYxWn7An988Gyx+QiOGazvH9P9tfoRiT94ZlauCx83n3NlO8xW2LXGh2szJ2DWwnJNWDaK659i9jpXrjm3YaGGtuT6k7shltyf+cdzHcu21PB/uF8qALMUdnBy1/uMOyzIYH5/1pU2TUezfsIyDc/zxQdR/3un7T8TWLOy7XBQsvb9LcxC2MUXdYsz7sp1GxuW0bN+Ktftn3CzLeemYqGLTE5w7wazFHbXJOUj66ByXdOvM7Tzn3Ld1k4VVnM=
*/