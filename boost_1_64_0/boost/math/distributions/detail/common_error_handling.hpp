// Copyright John Maddock 2006, 2007.
// Copyright Paul A. Bristow 2006, 2007, 2012.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP
#define BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
// using boost::math::isfinite;
// using boost::math::isnan;

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

namespace boost{ namespace math{ namespace detail
{

template <class RealType, class Policy>
inline bool check_probability(const char* function, RealType const& prob, RealType* result, const Policy& pol)
{
   if((prob < 0) || (prob > 1) || !(boost::math::isfinite)(prob))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Probability argument is %1%, but must be >= 0 and <= 1 !", prob, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_df(const char* function, RealType const& df, RealType* result, const Policy& pol)
{ //  df > 0 but NOT +infinity allowed.
   if((df <= 0) || !(boost::math::isfinite)(df))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Degrees of freedom argument is %1%, but must be > 0 !", df, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_df_gt0_to_inf(const char* function, RealType const& df, RealType* result, const Policy& pol)
{  // df > 0 or +infinity are allowed.
   if( (df <= 0) || (boost::math::isnan)(df) )
   { // is bad df <= 0 or NaN or -infinity.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Degrees of freedom argument is %1%, but must be > 0 !", df, pol);
      return false;
   }
   return true;
} // check_df_gt0_to_inf


template <class RealType, class Policy>
inline bool check_scale(
      const char* function,
      RealType scale,
      RealType* result,
      const Policy& pol)
{
   if((scale <= 0) || !(boost::math::isfinite)(scale))
   { // Assume scale == 0 is NOT valid for any distribution.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Scale parameter is %1%, but must be > 0 !", scale, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_location(
      const char* function,
      RealType location,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(location))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Location parameter is %1%, but must be finite!", location, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_x(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   // Note that this test catches both infinity and NaN.
   // Some distributions permit x to be infinite, so these must be tested 1st and return,
   // leaving this test to catch any NaNs.
   // See Normal, Logistic, Laplace and Cauchy for example.
   if(!(boost::math::isfinite)(x))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate x is %1%, but must be finite!", x, pol);
      return false;
   }
   return true;
} // bool check_x

template <class RealType, class Policy>
inline bool check_x_not_NaN(
  const char* function,
  RealType x,
  RealType* result,
  const Policy& pol)
{
  // Note that this test catches only NaN.
  // Some distributions permit x to be infinite, leaving this test to catch any NaNs.
  // See Normal, Logistic, Laplace and Cauchy for example.
  if ((boost::math::isnan)(x))
  {
    *result = policies::raise_domain_error<RealType>(
      function,
      "Random variate x is %1%, but must be finite or + or - infinity!", x, pol);
    return false;
  }
  return true;
} // bool check_x_not_NaN

template <class RealType, class Policy>
inline bool check_x_gt0(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   if(x <= 0)
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate x is %1%, but must be > 0!", x, pol);
      return false;
   }

   return true;
   // Note that this test catches both infinity and NaN.
   // Some special cases permit x to be infinite, so these must be tested 1st,
   // leaving this test to catch any NaNs.  See Normal and cauchy for example.
} // bool check_x_gt0

template <class RealType, class Policy>
inline bool check_positive_x(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(x) || (x < 0))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate x is %1%, but must be finite and >= 0!", x, pol);
      return false;
   }
   return true;
   // Note that this test catches both infinity and NaN.
   // Some special cases permit x to be infinite, so these must be tested 1st,
   // leaving this test to catch any NaNs.  see Normal and cauchy for example.
}

template <class RealType, class Policy>
inline bool check_non_centrality(
      const char* function,
      RealType ncp,
      RealType* result,
      const Policy& pol)
{
   if((ncp < 0) || !(boost::math::isfinite)(ncp))
   { // Assume scale == 0 is NOT valid for any distribution.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Non centrality parameter is %1%, but must be > 0 !", ncp, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_finite(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(x))
   { // Assume scale == 0 is NOT valid for any distribution.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Parameter is %1%, but must be finite !", x, pol);
      return false;
   }
   return true;
}

} // namespace detail
} // namespace math
} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#endif // BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP

/* common_error_handling.hpp
EPj5KuTvH7E1sL4CWwPxvSLLQXWJTmhrIL5X1WwNqJypvxknydZAeM97Y13muFz71KVqa6CHJV9qaMCbN6N7cZPIN7DllbjsNgYIK3kfLOd7WvOvYY1tAUahCDsCG6iXK+oxXogdgeZxbmJcTH1Pe89XOwJJKrtNZWtHx0WNiasbq3LcTyPtDVzb6Hh7A7VOkr2B4eGyrx+KbB/OxX2AG9uFsc5X9oyZqEouyinKzM+7KCc7+MAb+Ryh9+FDEu5dUuI6b+Owk0L6ND6ucpuTFmnvwlMv+UnyHFhS7HlOa9ybs2h8DbPrnhLer3vKYBMy4WtsiyyROHobHSm1IW3uu83l/K2ML9HmW7SOz35ycW+1raL5WS7Hg5xg/SfTftfGheo09oLYtNhO3Ezr1vU/J0ndtsKvNn5nJ4XsSfRStsW1s+jA2myW3CfXdrILFuXI8fDeZq+8/1nLtAfKlmPK1owpDZHAXwfvObh6uPNx2JtA+bXc3oTH2ITf1oStr2lY19s+jB5wAzk3yalDWQ6gvM+wjq0mDuuzxzF99kim7R7BybNHvUQpX8vzi5RpTIX3uqrYFyg2322W8UvTEnxWSOpjf1ZYq4axqHozZo8Pvl+EyjW7V16G6Vs6VtP+K35WWOkpjyMh/TRp45ay88pSHsaet/WZVGXNWLWiCvcubWO0qUgdPdLFsfnOtV7L2NSOKJ98vQJRGD3tsZTPxlD58PFfT/lU4VlqoyfPf25kxhFr+Wz05XllNfLc36eXyLUi+lUX7VdxCeZZzHAkbWRnKH/BLiVpHY6f62RM4diWL+RPpGOeEtGGiY/0SHzSPnd62qfRE/wHbF9UV7+vunpk60W/77e7X22W+UFU7YL6+584sOPBT0+e3tx3rQ9o16f79+lj/ifaxFAbhzJez4ZNA3LPNN8ivkD/vlz1B0vD8zs6B1amY1a+xtNWbQl0gGfAjnAC7ATnwc5wEewFL4Zd4WUwDa6D3eGdsAd8FPaEz6n853CSmfPgGnr9OriROEf10oLsB+Ngf9gEDoDN4EDYDp4GU+HpRk9P3+V13qPMp6d3k+rh3eKx6XEO3Agz1f8H8FZ4O8Rho4LzGn9K+N0SJmr8Lq6xuReVy5WpXG2LXFOP3EaVa1BJfNPMOxF5t+TrTi2vzVped2l53a3ldY+W1xbYD94LB8D7NP4e5l2Ea2r8HpsVxl5+S5gMWxm9RX2G17ZV5tNbLFR9yMWwOVwKW8NirbcSeKr6d1O5XqqveZr6j1H9zDNVX/McPc6Ay7TeLoU5qq+5XPUQL4U4tS2iz7P6PF7msy0yVPUrR8HucCwcAs/Q606EkyBO9CTz4HzVR10MF8BSmA+XwvPgD+FMuAnOgvfDDPg4zIQvwWz4JsyBb8Nc+CuN59dwNPxAj0N6v/r8ps+VZT693zVa3pfDRHglbAGvgr09tm2ugUP0eDgsg+Pgj+Ak9Z8Mr4Uz4Tp4vvqH2+1KTUezE/SDjSqXVIlcJ70fh/vLbFwA10LlkgKhrDeFGwNV+wb0/4veaMyOGt3R70p3tPQA9ilw23Fv4b7ExR+MddJw43HzcGtxO3B7cV/i4g/V6JbW/Gp+Nb//7V8t3KLvfP2fucJFedkhDYB/TgcguO6yNGjvdQbPtsxBZs7Jz5F5JPzbwnR55p2bXzCHBZmFmYsX6LmLCJPCQzN3wDn5GYRblJ1ZlO2ITkFxqmP2m6fpWnEWLjzv9w6Rzu5cPt87eco5Z5w1JmPKsOHjg7oFxOLdW0xG7fN+xKFzsWbeCTuci5ku9syjXisysZZ5GWv4zFJf+Fs1vGUui/D+b8pJAZmwWzSsZW3VEjY3P3PuYhP2ETlfx6qD4A0=
*/