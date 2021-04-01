
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED
#define BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/function_types/is_callable_builtin.hpp>

namespace boost { namespace function_types { namespace detail {

// wrap first arguments in components, if callable builtin type
template<typename T>
struct to_sequence
{
  typedef typename
   mpl::eval_if
   < is_callable_builtin<T>
   , to_sequence< components<T> >
   , mpl::identity< T >
   >::type
  type;
};

// reduce template instantiations, if possible
template<typename T, typename U>
struct to_sequence< components<T,U> > 
{
  typedef typename components<T,U>::types type;
};

} } } // namespace ::boost::function_types::detail

#endif


/* to_sequence.hpp
xP8dh7y6wSUvyAe6UcFptoxAGBQ0D7N9/r2L+mo8ZuMM9LajWaqr+SVeaW/L/B5DAcK+4nc8JiDr5Yinr/du6hzvMKv0/fFc7nOCDSZUXbTGTirZb8ICHHU9B4xz+cwxi1qcCyEeKvrL5h1DMsshK2XHLQqRH3arYNICdE6Gu5C13zkTulR8BRSZEH8aXVHUxwwqMhwEvs4niKLXkHox654HJlz21mMx3/eXJ0KF0fQJreTGBSdGWizEZDMIAAp/zNceksrZWGlqUPetz87nLRva0m2/FD3hYgjVwTovtHiwiwPz2mlr2/BYdxhpkzKqaJz/ylqkIq9+F4ygc/Bd89UkC6+yyZC867/Qtv56Gr+3aLH/Frqxjw3gsoSI5Lp7cn8wk+87UiYibMzSxXRieTHDfx3ypMU7oWQWUuCV+vNW7IOmgJU1i4tJj0s0BbXZxQVkCVGX6zOKZQiPWrblo2jHIuLb2VoqO4HkSCP6wHcF/EqAFEaVqRzaCtomhrDmchLPnX6YC/TRHVHCVjvxLhtMW6K1CxFjnL0r9xA/HfJuZ40DKdiLriU8qQ==
*/