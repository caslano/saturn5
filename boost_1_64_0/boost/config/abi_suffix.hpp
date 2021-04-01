//  abi_sufffix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

// This header should be #included AFTER code that was preceded by a #include
// <boost/config/abi_prefix.hpp>.

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# error Header boost/config/abi_suffix.hpp must only be used after boost/config/abi_prefix.hpp
#else
# undef BOOST_CONFIG_ABI_PREFIX_HPP
#endif

// the suffix header occurs after all of our code:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif



/* abi_suffix.hpp
/OON2m8kYeTILgHda3UgyS95N1Vswfxncg3lMR2F+9bvwKyvrIODyixCpSsbWewedxuswxJ+rNgKhusO52zKj8e0icQWvlJwUfXRwOUIWoEOINhSI0c7JoivDxRNZ8YhVRRt+AI7YV4/FlmgTJhfjwpwFlToW43VGbCvTRIHkXIqLAiKeFcISOsY/ANBQm7XKpBFGtU4r8eLBFuotxhfyR5pbqKMPf7VH2sqWausuUXlwBPfXrbGFh5mrqYg024hzVcDdoPvJKXQIkWpCzdiNXSGetNcVShQodj1dy191iKFyjHa6j5z640kIu645fwI+ZLl2UdWCuDDfdUNWLzLMQunKNmLAejU11vyBclrw8A5vapE92c0/CQ/9MUhtAzHiMOYzFpg/kVoE8qg9/Vp6V/O7PL7oGwbLclyvH/6memVuquCwCe72Os6Ni94+Tf7b25Bpig0c1V7euswhZ/IUEL+6zd9kyruPL4Md7qLeBhcLrmBNzYy8c+K1j0cKU4WgK5PqdcUmwYEjPl5V5BkPEfyUAZiMRpz1sJqjxLTHV6hE1N2FVCiKIwLJg==
*/