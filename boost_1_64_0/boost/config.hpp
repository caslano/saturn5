//  Boost config.hpp configuration header file  ------------------------------//

//  (C) Copyright John Maddock 2002.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.boost.org/libs/config
//
//  CAUTION: This file is intended to be completely stable -
//           DO NOT MODIFY THIS FILE!
//

#ifndef BOOST_CONFIG_HPP
#define BOOST_CONFIG_HPP

// if we don't have a user config, then use the default location:
#if !defined(BOOST_USER_CONFIG) && !defined(BOOST_NO_USER_CONFIG)
#  define BOOST_USER_CONFIG <boost/config/user.hpp>
#if 0
// For dependency trackers:
#  include <boost/config/user.hpp>
#endif
#endif
// include it first:
#ifdef BOOST_USER_CONFIG
#  include BOOST_USER_CONFIG
#endif

// if we don't have a compiler config set, try and find one:
#if !defined(BOOST_COMPILER_CONFIG) && !defined(BOOST_NO_COMPILER_CONFIG) && !defined(BOOST_NO_CONFIG)
#  include <boost/config/detail/select_compiler_config.hpp>
#endif
// if we have a compiler config, include it now:
#ifdef BOOST_COMPILER_CONFIG
#  include BOOST_COMPILER_CONFIG
#endif

// if we don't have a std library config set, try and find one:
#if !defined(BOOST_STDLIB_CONFIG) && !defined(BOOST_NO_STDLIB_CONFIG) && !defined(BOOST_NO_CONFIG) && defined(__cplusplus)
#  include <boost/config/detail/select_stdlib_config.hpp>
#endif
// if we have a std library config, include it now:
#ifdef BOOST_STDLIB_CONFIG
#  include BOOST_STDLIB_CONFIG
#endif

// if we don't have a platform config set, try and find one:
#if !defined(BOOST_PLATFORM_CONFIG) && !defined(BOOST_NO_PLATFORM_CONFIG) && !defined(BOOST_NO_CONFIG)
#  include <boost/config/detail/select_platform_config.hpp>
#endif
// if we have a platform config, include it now:
#ifdef BOOST_PLATFORM_CONFIG
#  include BOOST_PLATFORM_CONFIG
#endif

// get config suffix code:
#include <boost/config/detail/suffix.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif  // BOOST_CONFIG_HPP

/* config.hpp
gWkn7HWiOM3tMY6fJ1mwo/azlz8pysOikMbRbnVl6JA1MAJUKHQoPnie1uO3cgnuiGK2ag2/WlFOIxkbf34R6OJYzX23gA5sQZy0Ik5mxCXMM4+1bm76PFQ4jWOA9Cd8KSucxwq3i6lwvcOsZ6ag7N+jK2L9f/5gjLxKzo7uoYuTg3C+uczJCZMErlnMgYtuPYEFU/CfzQc83WIijrumMS32irIs3bik7KBQGe1Tv6DSqLP2cYk52F3FDwMu8gthMRwnGaTAFFJnxgami5vJyIB6yICSdi9ZIZaBaxVwoOA8yXOO8qrXGbeUXdrZFZovRIWnJBfg+5spKiT+LDpvLgeNykQEmd8l1CG9HaNDWkrZ4bOAMDiX3MHWiL2c7LK/tTjNRTC0Xumc994yOuc9w7zGUWUbvs7pwXVkoG+HGaNenlzWq6R+lHKgTq+sPBSnVnGz8aabq26QN5f1rVXUeBosFOPOMsW4tExpdWvZzyHr5WXnQKWrN99aVlOUI9iMA71qhjrIT3Bora5TThnPdzI/Q/59oqnl/WVL0bHHhhfDqI8JH9e5ocUwEowT0Ah6od0ELOjD08uaULfYrvnrX6NdUx0dThlan8lybm70M3l0v166ZLUbJ4nh9KyKocBrM8R8i8V6dQzWO07DYhAbmRsTCQKWXrJmzqtZFdiI8ZsKvTYWsJMBeAo29xj0LI3uQtJN79PHpApJbStvfMPOJ/VreOO1dS0oElYxRcf+eJ9aMdS1PN24663FeV50oqrLLDqIG99GUMrXQamSbF5gmPmhcePbFLt5v5u8RCjS2csvW+hQf3fkxze4XQVvz13N2+AAFhlweagp0TXfDlwEcpBFm0L+bIbfOOPA43p1RhsDY5wyt2YvU/YTKOON4ASZUeyVb55I7gjUK2nmObzbra283qgn3kcmRobwvSPvdssVd7utFKXMnQHZ4+snYQwtXI0pWj0kzaIUHf4x/QARCDVjrTsSYeaXq44qJRLilYHG1rmUiUvlpn6fupZKCTf+ZLjJKWtn3UUKxZrIi9lQMa+KKsor2dSHTJPASHFJTlQieRhZApk2FhTGhMqqINypvEznO/wM+eeR1vLP53NO8D62nzOpeR9b1+96H1vklqZj3cd237zofWxd/7PuY5v2cJNxH1vX73wfW6JrQVubeR9b75HfdB9b3Dfcx7Yl9j62SuOutRUt72P7kzUG5mEDZvG33McWtMob2DJ+zFvCbjK+vPy652p8sZM8LNj0wcZ9bI5njfvYMEX7g+jcoLgKKsPDTuI6tnjXgg6tr2Mzb1JLjrlJrY7rtbhMzVVShddvvCLNdc9fEAzDlGDYCuzVcj+ceVka6N1ChLe+MG3WN1yYxqaYOYFvbIY5Y82L0uJbXpSWcOyL0pwzS3lRWkqLi9LeXibGdmK0avW2E7sVbtGjy6yWZfi/Av9X4v8q/F+37L/zDrUCdRPshyVb5lB6ErsXZ7hcyzeLPg3tmaOEOyK0Mn1XbkVwWOiQbZYDy3A1ek2xoicr0ityi7CRFkRcr0aq0J5eDK3cEx/aNThx09xDpNLT4ssOM164R5n49ubuCvpDh+wzlynERTzBMr7axOtS8QqMwINXnzW0xxXaPbhyT1Ll7vjE2sTNcw9ZnBbL1CfL7DFIG3P3BmeEDjlcC65ChlHErpJr+EmM8tNvfNrl5yUmcHN+ttCehMpdSSLLjombkKmAR6zMnF5FrnnpSFjmiCnA4dxGV8kDbLlDca4FW5paFOKtphaFqGlqUYgy49MhP5820yJLFItlsmMPauWujqJMqdEy2QCAkiZuEoljCpiGAoaApSwupoBNuYddJctEATHhL2hZwIEtC3g=
*/