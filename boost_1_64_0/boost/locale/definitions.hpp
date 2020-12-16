//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED
#define BOOST_LOCALE_DEFINITIONS_HPP_INCLUDED

#include <boost/config.hpp>

// Support older ICU versions
#ifndef BOOST_SYMBOL_VISIBLE
# define BOOST_SYMBOL_VISIBLE
#endif

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#   ifdef BOOST_LOCALE_SOURCE
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_IMPORT
#   endif  // BOOST_LOCALE_SOURCE
#endif  // DYN_LINK

#ifndef BOOST_LOCALE_DECL
#   define BOOST_LOCALE_DECL
#endif

#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* definitions.hpp
0XMG+cxie8pme8phe8ple8qnflcGnsoY8NMYA34601UyVvyBfN4onlPuctOmEhM6JZbRJEvM7Urqqwo4gzG/NwCuoU/IGfTFWcf2PYP5d4fsF2kLea0lNv4s5t/E/H3Ao4APBt6IvjiLGat9M/7enOkmM7Z6Oe9Poy9FL39X0HdiHX/PoM/DRv72AV8CPJu+QNuBO4HPoE/Qc0Q6yrEe7eXUfs6tzDXupBx3qePTAfbj9hsu9osct99iuyih7ZbaP6m+GxeS7m6OF/cBDwG+l/3Vfeq4c4B9e17EfB5le35MHXei0D1Ium7SPaSOOwfY96uvkO5V8rlEoeuJQvcC6V4k3UsKXW8Uuh7SvUu69xQ6wxtlfkO6pynfMwqdJwrdaqQrJN3q6jgVhW5z0o0j3RakGydoSVeqGVd3Qjo38M7Ao4AnAm8HPEkpt4P0OZpyd2e5ewBnA5ep7SYKv+eQ7lzyO0dtN1HobiLdzaTrUttNFLrrSXcD6Rao7SYK3W2ku510d6jtJgrdVaS7mnTXqO2mwp7ufNJdQLq5aruJQncR6S4m3Ty13UShO5V0p5HudHV+E4XuTNKdRboO9XshCl0n6S4n3RWkmwAoI906pBsM2Jp0W5NuG+BM4O2Ac4FLgFcF3h54beDxSrtvZ34jNO1+P+a3P9/rA4A9wF6FvjMK/VGkP5r07aQ/RqHvjkJ/KOkPI/3hpD9Coe+JQn886U8g/YmkP0mhNyrt6VtJ7yd9G+kPVugLo9BXkr6K9NWkr1HoS6LQ15F+Bulnkr5eoa+IQj+Z9FNIP5X0e6n1H4V+H9KXk34a6aer9R+FvpH0TaRvJr1P7ccq7d+DUaRfn+/BBqQrAwRIV0Q68Xw86YpItxHH7WLgdYDHsP8eC7w+8CbAG/I3+eFanG5+Ccx81+b8ch3gIwYZjnwde+6O9HNM38YWv8ZRfRrDl7FzP8Y9+H0y8OIzBxnLAHO3jvRdXAC8NYC+ivV+ii0+iru/xIGVswaF+SiuABTiHnwUY5Jq75d4PEDni3g8aMvoi3gefu+H3wuAo/kgXv4A5AT2A+h7mH6HTX/D9DWMZ8gvafvovobpY5j+hRWfwivgT9jOf/CbgAXgJZV+gxWfwfQXHOknuBswgb6BewC3P5VivAlIfTrFGA0oB7QDFgDeBPwCWAuLiJMAfsBcwH2AZYDMZ1OM8YAGwBzAfYClgNTn4DsYUAaYDZgH6Ab0AFKfTzGKAWWABsAcQBdgMeAHQEEAeQJmAk4HLAA8AVgGSH0BPosB+wHaAfMBTwCWAzwvphglgAbAHMDtgB5A6kuQC1AG8APmAu4DLAfkLgYNoAJwxOKEf+PE9e+6/iL/f9jP67//P8T5l7HPS4Lx/1twH9u//hYkkr4BVyowzH3G8YM5V3YHx9FGYD8GW88Uc09sh0NxVGNq866IwaiexeQ+Gba4FiL25z4yfak7nfHvN5K/D9Dvm03Rx99GXjL2+L7y+XbuUFzssfL3uu6zoYPdXItoZ49IlnuJ+2vo/aBMsZ4HbK1s8AfLuB1ljJPPq9yh/chR8veGrmxE6w/FnqucKv3GaM4Q6vKnbx/k34X8vfL5Vu6QL4Gd5e+5iCeTqTlnqOan2qo1aOLj6tJWN7c1+bUx/tW0hUmM/0ldd4LPXeXzPdwhG8Dt5O+R5lmGb6QO8oxs6ny41Hk7dFBojDOyZZkFSpkF2jJx5JllzkeZ1fL55maZk+XvIrPMPFEG8s9gmVvI31ONNJZXqJRXqJQ3lGdsDOVM9Tvy2Y0u5dyvUIDpa+I4+TzNvZOxknImut7cp14u5Z+NNb3hJn/HyHuzItqhUoYUOIPvwhlB/txb4A7PnEo=
*/