// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP

# include <boost/type_traits/integral_constant.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts {

namespace detail
{ 

// Here we implement the metafunction that detects whether a
// constraints metafunction exists
  typedef char yes;
  typedef char (&no)[2];

  template <class Model, void (Model::*)()>
  struct wrap_constraints {};
    
#if BOOST_WORKAROUND(__SUNPRO_CC, <= 0x580) || defined(__CUDACC__)
  // Work around the following bogus error in Sun Studio 11, by
  // turning off the has_constraints function entirely:
  //    Error: complex expression not allowed in dependent template
  //    argument expression
  inline no has_constraints_(...);
#else
  template <class Model>
  inline yes has_constraints_(Model*, wrap_constraints<Model,&Model::constraints>* = 0);
  inline no has_constraints_(...);
#endif
}

// This would be called "detail::has_constraints," but it has a strong
// tendency to show up in error messages.
template <class Model>
struct not_satisfied
{
    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof( detail::has_constraints_((Model*)0) ) == sizeof(detail::yes) );
    typedef boost::integral_constant<bool, value> type;
};

}} // namespace boost::concepts::detail

#endif // BOOST_CONCEPT_DETAIL_HAS_CONSTRAINTS_DWA2006429_HPP

/* has_constraints.hpp
AhaGK2Ep+CqsAlfBunA1bAbXwHZwLewB18G74AiYDFNhFkyDo2E6HAvfgFMkfD5cD5fA1+Bq+Dp8E26AO+BGuA++CY/BTfA03AwvwK3we/g2tHFtfAcWhjthEXgAVoIHYXX4GWwKT8FY+AXsCM/AHvAc7AnP63XHpJ8Tfo14rzv2rp2qCnfCUPg+DId7YSm4D5aFNUivIjyEXh0egy3gx7Av/AzmwNNwKiwh6weVhAtgKbgI
*/