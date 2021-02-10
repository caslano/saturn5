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
mgKltbdE7KIMLFvKv9Oyfe4FiIaygpGfQJCMYMUUVy6cB+lJdJbCub9Y+GF6AdE78MOLAe99EL4lbXCKKgGvW4mKspDA123NsbgT/KdOuuOlJzA9W8yD8F2U+XE8jcJwNk2zNDidwWMYPXoGfndp9P37CEY1XxkBwFPvyRPvIR2Ybxkytc0uUfOmFKbfJCtFyMkJhP7pzPkm/PIBkFfPO18jtUHzum9bMp8k5F9Re1XFPlqOc0FsIDFsoZOLMIqTIHF+4U1edwXCS5NML9DqtWPD5oLO7+U4Nj/BoQGvSULfyo8UKToj/0OTXXvwwsZ9O0umiyBOgyh0YkZtYtAK3mgjIJqZnQ89D/N3W59rRlhhLqgmejZjIT5CKXupOkqbGb3PAdk3tFMney4I2xhIXAualUooDRv2BT+eY/VpOaX72hiQVrGBK5RbaJDJHcayDG7LjxezlLSZvJstbP3jxwfLMnb61PE6R5rkkkSZM0WTqLq8MpvlJE1jaHmLNW94c0mjh7KvmVSsJWtUaagxueSscVZIK61mW5qTorOlbBjXylBDAGgDWOce0a4CqkDSADrnFZXAqO6CS/OWodpKUddig4W7V5ElFBllJ/FTh8rasaKwE08KoPwIK8Fhyxk/U20Cgti54rjZbVri
*/