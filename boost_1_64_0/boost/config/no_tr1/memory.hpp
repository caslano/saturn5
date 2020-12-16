//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <memory> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/memory is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_MEMORY
#  define BOOST_CONFIG_MEMORY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#  include <memory>

#  ifdef BOOST_CONFIG_NO_MEMORY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#endif

/* memory.hpp
xJukQUj7O0OiCDnoIxveqHkSc4a2gGrcHwZx7g/JKs/ELGRgGPm5JCSuRlvuufJ593WVr+L9UuiHZ0WJn4+HikhllC760CDYOtawkDgG58J5smFE/pgKvE0Ia3EulDHF+ssRym/SC2SZELbtpTokRuFcOF/5+o75u4fubQ592+C9oBw2O678pvb1GQj7nunEkLkT1Ne6E3Qod90zHCTphaBMCPvOh+ThLrx7fYFsyB/5DcYKHQKTAjgfeGoI4yBJMyVmQthy1K0hE6d9oWw4PTf/QJSeYE87/dOKxnz6dU2c2tNjIGz79b0hMRjnw0WyoefjXcK692DoeQjGS/lZ98n4YNrD4h/irjzMyimMv3eaZmnuNkuEEJLs07QNQvZQyk6GMc2dacZst7l3pinZS5YiJaKJhBZNGZQmhVQISWijUoiKkL3s55vzu+fO+3k8j3/Om8fcbzqn5/7O+XW+c97zroBwyU/TvJSHffIy9WyVu3Sh7t3P0xkSdlgotkMP0m5gRwuM/ylLt90XsnSFEvat3jMBwM+KGV46BHvDFarhyb1JqImY5WlshZjrVmJ7pDNEq/dMAHC5YWacgysZB5n7igOrdyoAcH2D4qAnOLjKiW+KBrJ1b4ZnQ6zeW6IsB9ZNni4UE7fSEF8PV7P1kL6v1oNdBRQQWKzKnLgudiDTxQY9I8HBVEkObOtigcDWwZz4OriGrYOAZ/G+WAfVpeEiu15zBoOthblxHvIYD37PbsgLQTl9bIXAvmAQzF3ieS99CJnpWvUsmPA7IpV8nvZe6BnkZKYKJ49lrcU4NjeGkR2b4mvhOrYWvJ6mffFODA3b5WBomNuoFnrpIszf8bf/Kee2NXqGaZ6OabF1IDb/yoIKu/ZaAHB77StxP6DrWSx0G099Mnw8EmVy76shhrurvDlhq44NgHDfo5Z66QbkVS5QDXM7Nc6AQ4NnSRB5A+TWAgZpVVJgGOYO8a6XxmM9DFINw6v6LdIzTfGUJ4CHBLn1oKzrVrVuAOB3iFVeegAcFHoUJ48djExEyZ7ovuDAsuYRAPwOoTi4BByEHD/AR/sO071JHu8JmG+mmP7VupYJADzO4lMvnQwOipz41ataI7dda8+ORPjXtxJcB+qv2ws/Mgg8xuDzOAfFjINEE2MwSZKDSFGB1btDCwSzDr7w0u2QFwer56yB8wboWbby7IKc1CgnJ4XtJlc3CNw2t91LheDAsTtU7B2xAolSzP3pLkkOlDBbWmxVz2gwWHz/Tq+p/VqqnmNGnwmNisfTKwt3aTkbZbg5DKLY7moABo/d3uM18co3OHmnvhrSg0BEfRrkxiRhHiy/FcDguZX+Uj5eWA9l6vlQ6bS20EZTO0Qn9lXSw2GSPNg+K/8r9sbvo3rYZMpVQ+2CgxGt/Rflwv81Vy4OKaJ+t3uVAAL3kfZRN3BQoRpK9v76gp7lnzS1k/5tpFcmZrkuP1QQtef4ia93yY3H+YyusVI1XDMwuQGZLWhNEs5KGd9Xx+dKfditespA3PeIE30mLq9KNRy9axS85H+nOi/hSiEiQ2OYdqtYMRB3LH83H7XFPhlWz80zL4QM9RttwN5wVYpI7DaGWWDtTmUA3OvhdB+FUZNliGo4Zsa6o3TvXorFT/RJIPLY58Dx184rVfFP1khwIRg9S39VoQv7Y7VqeGp9cjZu1LQyMWaVEOWg2GIyA4bB7lWX+GgB9oaIk/f4m1FL9Ex/pTUJ2CdJkoeiQmtCgwvBcHCpj3ZhT4iq56M5WfBg+YXqMOvVohxUCawFjcH8P6/wUX/wUOP4/PXOQZ6sn2lxCt4J0X0hYtGFg0Fwn56BPhqKd6LW8el5uaif7v2Jwoc=
*/