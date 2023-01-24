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
kUvC26yRyLLwmP1cdNy+SCfWJdsbR5qWNg+0ZFpXtIw155rWNSaSufrmxGXxHPGUrk5knd1s3Pxixqcxloy53jStl7WlWmMtbe03t9Azj6YG+Y5bh/y0gtbvnfTAfg3rcYacU0/4f/8M3fx6CLTlhaEgbZkfsjeETAjojPsgVvL5asynm54SdAALS0E4QyHnyyG3OayTOs1RyW11KjmeUMnMPJV8A7LOWIntphdT5RYq3yiVeRV/ClW/4DplkMxu8HK3e9+d+A1NypDT8pxut1bZhfBl0d/TjHQ6ncQFu5aetbqeluvAjDzKKyXf+LxFN+FPYHw+qOjXS3aNZuZ0Jh1J6hN+/2+6Wc1whj4RhPOe84SJyf6QXGM7PlGhC7uGHjgPE1vKecU+JD/V4U/4Yn2/Szf/xN//nvf9w0N/HVa/0s6XtF6rVs2sO3rnExU2yuph+v5e+j7bF01ulpNoPutpPuuMX4bkZskMs44xT5XzqFw6bOi/h+okJHSvS0YOP+cyABcMe2T4ELXvW3Maa6qttfb5znp7TN9oPRpuswp6hHbNJqvzxPYeGq7gwx9027vPs4d+tEbN30F0b9PJRPdyM9K91+iVv3Tx9btU2XtGVN1PJeMIUr53NKQWVC/dTf/lobY/Zon23v0bIWf3b1dWb3ejw551L89o/KHg/uGYdYX7bL7lXv/VXL9b7V7rbIOxgciOlW0b3hbY
*/