//  static_assert.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP
#define BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

#include <boost/chrono/config.hpp>

#ifndef BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static_assert(CND,MSG)
#elif defined(BOOST_CHRONO_USES_STATIC_ASSERT)
#include <boost/static_assert.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) BOOST_STATIC_ASSERT(CND)
#elif defined(BOOST_CHRONO_USES_MPL_ASSERT)
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)                                 \
    BOOST_MPL_ASSERT_MSG(boost::mpl::bool_< (CND) >::type::value, MSG, TYPES)
#else
//~ #elif defined(BOOST_CHRONO_USES_ARRAY_ASSERT)
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static char BOOST_JOIN(boost_chrono_test_,__LINE__)[(CND)?1:-1]
//~ #define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)
#endif

#endif // BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

/* static_assert.hpp
ghHf7xY+/iSKs43XbUXp7iIVd/QaMnmFJeUF2RMKcyb6ZGMN2XokS+9opXQ/7FNJut89tNNVRvd38z72LOLpCJvYjdjoX4HPG3fu2GhfjH8F7YNRPaA59pkNWoCeAfH+w1TNdwWtQs6+anuVs7XO9p1E2qOjveygcwSXMUN3wNUwzgGjXCo1u7ikOHuCHqmdXVBWVlLm1x5IG+3hk2vKabwRkfZl7OfUifYNDTugzEA9jc3NfN7byWY9M34K1LN8UsmUwvxsNFrZDNpzN/SczDr5ZJINHW+gtNWokwiq06CfAus0n9Kx5I/AQpS+fWincxIpWgPLOIeKt9gdZqvxvqhmtfA7VNV7MtJdXX14L6ssifsA7/NuYhvUq/6OmjgMBTdX2SC7vKIMjqb2bQU/L81o3xxU/71e4q1H+VOoFIhwvgv4d5SfWOt93ma0l073CNB1j4Wfb93vzng1cmJ+IF2prfKgr6+N7iFdc0UTfs46EF8vmYm+UwiYB7gNsBHwFLTl+nB56Ugbz3pRvvGM+/KTKd9N+cVTioCb8HjRlvL7yCzoXgFYBLgH8DvAbmGlciYZ92lI5Wi0h15KdW7CPqo2lJ8pR+Hf2YBbAQ8AngLsFYrKGeIrB9b1nZmJqtWZCgfZ1HMGsn7pM3pZ1BZmV1nV3+kDB7dtK5j2VjUtg/oEaM8ZtK6UXmSkO1J6jJHuYPTNe6iNc4U7YKwiO/N3L4GJBtsyLRMYdgKttEbfKOQXe/VlX6cuvwY5R85U940JZQUFgX0jxxiDFY0x7RHFJLkf+GTdhl1lLcbjwPrlBPhUjrGOcQCyPeu4z09H/EChDKPvThbGc+bjizvnN2vpOTJ0QBlBtuodwcw87nUFTEbH3fy3aj1Kp1SUg+yvS6mfLszbK+SYMMAvP9IY/4qNfv8V5UXQN2BOwSaHoOztKMOhRVmUw2yxR9mb63/YQ4855NvbRWVcFDzmGPfYSfnNA86SxZzHN2nZdlRn6qNnGZd28nbScp53zAXMgT2PnDbsiR+PnPygccmwJfhoHHDzc+8i3YvFWJ4zlNLYUDLFf84QTTwFojX6LNncKKe+MW6RTKEw5jF2kikR10B3spMhk8wyxtyE8j3Al5BMM+GGDTWkF7mrOnCH834Wqp911Adp6OZ71o3nn/Sl36sEui/ieZOr0i05fSY50PYZDkHXDLZ9MeAlDNJZfrafVja5oiC07Zkv2TjP9itKD6nud37n6gYY/I2MOIJySg/32Y/4C/3sV0z5zdjePvn6Ye29kvJbX1B7N6M01SPI3qQr2Rf1CLD3Qk7/jLTPt9pDnb/vMIzPNYwPNdw3h8P5OM/fNxnah3rhvmkczvc5bYVO/3pe7ssTnhi75P3VXS6e/cRzQ8J9izic7zacbzucDzucL/n8vwUd2hd+/t8iPlE916QxP1XS+95orttF98ex/zXTWEvReo7yLMDd/Pxj9SgNFwzwpcAZ7O/pAXwZ8FBKV/t79nF5Ni7P8PewH8v37jQrcCdg0sNYf6DMEHpsZbkngDuxn7ML+zm7sj+0O6eNd4fxXDyfygt8d9h69itvBo4D3gScAvwY8HDgLcCjOZ1NaZ+ePA9n+6YG6fkB6/kh+8E+Ao5if248+3OTgT/m8nYY81yaZ0PPwHfkzQAfnXsDHgA8j+1dyX7m+cBjgK9nP/O9wBOBVwNPY//sHOBFwNcDLwZezHw3M9+9nL6P049xegunXwBeAbyb6a8y3ffORZq/AfclOwe+c3EQf296MNf/SuBE4FHsb80Cbgw8hPvXVewvHcbtO5zfYTiS+9soo315ngYcF6J9gakd+gCbgfsC29gPS98HYr9vP2D6PozhL+Y=
*/