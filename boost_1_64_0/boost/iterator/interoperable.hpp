// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_INTEROPERABLE_23022003THW_HPP
# define BOOST_INTEROPERABLE_23022003THW_HPP

# include <boost/mpl/bool.hpp>
# include <boost/mpl/or.hpp>

# include <boost/type_traits/is_convertible.hpp>

# include <boost/iterator/detail/config_def.hpp> // must appear last

namespace boost {
namespace iterators {

  //
  // Meta function that determines whether two
  // iterator types are considered interoperable.
  //
  // Two iterator types A,B are considered interoperable if either
  // A is convertible to B or vice versa.
  // This interoperability definition is in sync with the
  // standards requirements on constant/mutable container
  // iterators (23.1 [lib.container.requirements]).
  //
  // For compilers that don't support is_convertible
  // is_interoperable gives false positives. See comments
  // on operator implementation for consequences.
  //
  template <typename A, typename B>
  struct is_interoperable
# ifdef BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
    : mpl::true_
# else
    : mpl::or_<
          is_convertible< A, B >
        , is_convertible< B, A > >
# endif
  {
  };

} // namespace iterators

using iterators::is_interoperable;

} // namespace boost

# include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_INTEROPERABLE_23022003THW_HPP

/* interoperable.hpp
J42a6t5pbqHqeoy515P322Y/tzHZ/3rhKeC0vR7nQyFfB3hw788P8Oxheoe37YIol6e/UnnHMW9TNtVd/csaD95Uu7KWFJdI58zyoj1PWF7koef879Fz/qrZ7Z+X5De+5QdfP5TFUz89v6uuGWdc02yj1d38691TjXFs643PA0HWOY118HnG2tVX8+o5+Qa0p64v46JO8Nyt6O5bVxDqmmFX10XZBQvzgtPHDF1Xo2+wr6vm1X1KA+pq6K7PXCuuZ/jgqnQ03JdUIF9PHzZ2IL51cte1V2cPnPb9sEufSV322heBfVvZ+5I6db6e7H1eBfbNZe8rLLDPLnvfXw33bWX4pBKbgXTxz+F+9uymbcZlxu/rjd83GL+XGr8X87cTdI3xu8L4vcr4vdL4fbnx+zrj99XG76uM31cavxey/GNAy/hbKa97zTftAGm/mO6z5vs5nAaIL6mh9O0xHPga8Hzg68BZjJ8NfBtYDqzl2uDtwKuA7wJXMH4t8H3gLcBdwE30bfUmfYwouX8C3Md89wN/D/yKvkeaONy+R5o53OdVPTZquzDIDZTO/VfvZD2yHO565ACbAOcCm3Mtu4vheIbbcm17F4a7MtyTa92VHOYDRwALgBOAhcBMYBF9fhTTV0UpcBFwAX1VIMy1+7RRAg5i2Fy7Hwe+pvQR04I+YtrQR0wn+ojpB2zP/Cq1XQ1ky/yagcqZ32DwRQOHM79hKj+GB9KnSBp9iIymb5EJDC8AngNcrvIFVgPHAZ8Cngt8BzhR+5Ch/QZtTNJ9fLCgC5By3ANszTWyiSodsAPXyvZWaYED6HNnGH3uTKTPnfOA0BmR96PAHGAN16Y/Tt9ovwJeRr415LuZPtZu5fVup4+1aoa5Fph2EHiusfzmWuCRvB9GAVX8aGCMkgfXdI+hb5lzLPpeYX3Sed+M43VmOGgLQLsHdZ0eoAkOvovzOlO4dn0qUPb7Zv7nAzsDL+Ba8Zm8zmXAPsDZXJs7h/K7UF2f4dEMTwdeRJ87mcD5Un+3765s4NXASyi3fPouuBT4MH0YPMZ8VJuX0udcGXAbw28z/B6wHPg+fRjsAS7ifb6Y93cF8C/AJcBDrMfnwEKgElIR0AUsVvV3uM+3Bl4MTAHmqHqreMq3Sn9TxjdutmNz0LVsR1xL5HoQGAs8RLmGO9z6eBjhXvQ1dAbwS8rxb8CRwK/Y7x0HLqLvoOuBFn3QhNN3RRjwVobp84DfIjHHznKZPg+c4KMNuehVDMvT3FirXcn0A5jeXKudyvR9ganAfsDeDPdn2FOOWubT3qYc3ZjPaewnU4DtgKczfZL+HkWf+j5rvZ3mGvwg+ZIMvnQfvhbGdVODzC8tSL6MIPmyguQrCZKvMki+qiD5qoPgSwXVkK815Wz6zJjNdp/D5+GFht7VMl2yjd5NYbqpwCjgdKa/gM/RGcxnnp63wb3OfEwfCFeinA76zIihzwwXfWL0AF7L/usG4Bj6CClheAHDixj29OfVvN4km/58DfgUrgW2B/6Mvl5upa+X9cDB9AFxNuPTGT+R8VrPPwgs/2hTz4PkSw2SLy1IvoyT8G1DxJ2zsfYdtAt0BBTI14LpZ8H0sbAbRL8K9KXg70fhgMIM+Bfw8ZGwDhRr+EM4gHDuFHu/Bykg+joQHwcR9GngnIO19z6+DOjDwNd/gfZbMGS64afA3keB9kmwHujcFWHnh0D7IEhFGdJn4nrALFAlqBq0DbQfZF0IfwKg0aA5oCtAd4K2gupAzosirRTQBFA5aD1oM2gvyMqEnwFQOqgAtBK0AbQddBAUmxVpDcwK+RIIHaEjdISO0BE6QkfoCB3BHxGguT/h+v9MLOHPk2X/P24=
*/