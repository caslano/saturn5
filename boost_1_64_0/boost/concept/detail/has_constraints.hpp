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
jWmukNE90mFmmiULxs0zn1alYIQoNsAEAHjblGUfGeS/Kiy1yy0w+V8pAijgbNj7vgVb/fUnlqtDRUg+frtBLFZLwHqjnMkRWiDbDFlxRVahGj8/egQt2OnUZ4QkKKxbVU3PcdMZaKJrwX53lh/tlyTH2WoT3ek23LZmA/3bwpSpmvST1lSi+oA/F6nY2dzvXtVL/RM4HoJeNxuVR1nnmG/blBKJ1IVCpcBaNUJ0qhUz9AEHCYS94AMmCsUHXuz3r6qOkbsfn4Hb3OnFrO4y8wwYUlUBx1x6LSkspy8md7WNTIL1kQAbVnf55BpYdTClY7ZipNzEYG+NR768m/4vU92s3WKpKV80xeRXo2vCbPl7l+fszf7V8kbmv+SfAaxJisxrA4WfNbM+uCZ0mzUPeTBM16db6ZTd1jKlzaLEp/ztM3p//v9U6R/qAl0fsO/YWTWgVsakELra+Mp+PPR6dvBru1mg7pnx3ZnRNImQbSfx258UMGlJgJYrdRsw65nfwDpg9sitHwV81kNTka1JLjucUd7gjetzfgDjPdeJkj7DbldjHuvILkFneg==
*/