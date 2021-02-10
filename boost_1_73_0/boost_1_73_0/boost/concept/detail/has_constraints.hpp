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
kzXCEQWVUp18Ph7nvahxJ+OC53Kcb6jwK9Xc2dU5VtOQa+CdAsWhl9QDvd6Dhhes1HekCAe7fl0zWXk3ZSFgW4y5AEnrekiHoYxKuwUKycCWp1dCh9UzpW+St1KjXVW8ubUQaR0Slb1oEQ5pwXUFR+I96NuCCrPeELFBGVg2lH/jyG5qL4C3WBW4QQJh4sKaSCY9eBemJ/FZCu+C5TKI0nOIjyGIzod8b8LoCLXBEFUA/dAJKrEKAazpakaLW+Df1emOn57A9Gw5D6PjOJvG0VGYhnGUnUWnsxQOwJ1AQjuU9+SxC27N1vr84Yl/eOjv44B+yyiR19kFVawtuT5uVJXExMkJRMHpzPlq9tUeYBTYsBYPocE3xRqKh90WTOchtWbhYP8QTtJ0gYqWHSbXh4HZk/MoXiRh4vzI2rzuCwovdT1WotUrxyDnHMfvlTnSU7BboXpqFNHXSvSg5u0F7JrSdl4Y1KNZMl2GC73IWRA8JgIdZ63SAkLP2Ah8GtxnhNT2DfYDmACzwtruDzrBL1lh3O3oGTz5S8Z7ieH/9FQqFFbR/qLQSSqvYCQphVUZ6nrjRZql4elsW/LoYGdVLnZ8CGoiPYcNZhdUoeJ1mRPTId63/Apn0NIaTyArWIaeGJD0kRREEd1vbKz2
*/