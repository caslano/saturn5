// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_ASSERT_DWA2006430_HPP
# define BOOST_CONCEPT_ASSERT_DWA2006430_HPP

# include <boost/config.hpp>
# include <boost/config/workaround.hpp>

// The old protocol used a constraints() member function in concept
// checking classes.  If the compiler supports SFINAE, we can detect
// that function and seamlessly support the old concept checking
// classes.  In this release, backward compatibility with the old
// concept checking classes is enabled by default, where available.
// The old protocol is deprecated, though, and backward compatibility
// will no longer be the default in the next release.

# if !defined(BOOST_NO_OLD_CONCEPT_SUPPORT)                                         \
    && !defined(BOOST_NO_SFINAE)                                                    \
                                                                                    \
    && !(BOOST_WORKAROUND(__GNUC__, == 3) && BOOST_WORKAROUND(__GNUC_MINOR__, < 4))

// Note: gcc-2.96 through 3.3.x have some SFINAE, but no ability to
// check for the presence of particularmember functions.

#  define BOOST_OLD_CONCEPT_SUPPORT

# endif

# ifdef BOOST_MSVC
#  include <boost/concept/detail/msvc.hpp>
# elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  include <boost/concept/detail/borland.hpp>
# else 
#  include <boost/concept/detail/general.hpp>
# endif

  // Usage, in class or function context:
  //
  //     BOOST_CONCEPT_ASSERT((UnaryFunctionConcept<F,bool,int>));
  //
# define BOOST_CONCEPT_ASSERT(ModelInParens) \
    BOOST_CONCEPT_ASSERT_FN(void(*)ModelInParens)

#endif // BOOST_CONCEPT_ASSERT_DWA2006430_HPP

/* assert.hpp
XnzYuj1ea4oPWp1DJV6IlaHyLDB7fgDGFZB5LLPe32r/VV8/nVBEUVlmeySoYipptZTOeI1N8MW7LYllZ1ZdzQTkka/JGbT/s8DQLsLaP0EraE7F4RTR3jvLB8wH5waZF0yPalnhWN/MBeTyKZdMsHlM/iURLF/2B287qARIxvcVayRAi3Wu9romnXIuiazXhUs4tIqbmowhceifXjedRzz0pg16nT+U1409igqGTh7p4YxOVCnva5hdIUAxua11asgylzMKk1ubgb0zIYxoyKhP45Rle+NpBa77HlFbEybob3WjjUypcSg2d7Nlvhm1N2mXpSQ64sr+vUlWH3InESrJeM54tygd9piPaOMndG6dxBp5+kNsYiE53nWiRm5p2NYQBGwqnu0AABhH3c+c61aBxgtbbowus2n5M0kNGHXe//xANZzmC7FNMxNXJG0ECmIyd/M0y9kyveiiNIhdLTx/v3IuPFDjTInXrZcdGhJHw+9/NYuxWtB7IuZ2YMhWRH2c2jcRCjzVHlxELKjKB7t1c7NTmzuUFg/tAeKwGH82kRKQzIZw43qWYQ==
*/