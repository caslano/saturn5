//  Boost string_algo library config.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONFIG_HPP
#define BOOST_STRING_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_STRING_DEDUCED_TYPENAME
#   error "macro already defined!"
#endif

#define BOOST_STRING_TYPENAME BOOST_DEDUCED_TYPENAME

// Metrowerks workaround
#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) // 8.x
#pragma parse_func_templ off
#endif

#endif  // BOOST_STRING_CONFIG_HPP

/* config.hpp
mN9ZTVCKE6xR6CbdUvY5/5ne/r671gDgcUYCRzhGuje9pldNWIqkzfhHjChKoFgAp0uR/An2c7p0nHmogeU/C1aSE1FH6dmROs0gtQY6UliqZFVQ04h95yBIPYELFk+6gRjsT1V3JwrPKamTGIiD8acvvqAUYP1bMwQ3ZYu6Q8zp7cgB7Eh0koNnvoJ8CMRUQ1lufh9yWqrX7S8L1A+LkBncrTImtQSSjLGtvMT1vSntNeJNrRgabaRFUMciVRzCWsR3pqN0LuXlrIm0lgpffykMiNfuPdSAGZpr3CYIJQY/luuqi0r7H6oPsQa3NL5wgH1aWdIvaNy2qDpqtmQLnpm3x9vEogT7fwUiLKgYKPbOJnAU7JLXGTaaooRmFDZU9UtKOesdGxpGtqzzsAjuh3oLkEAjVOJZ2srMNCrSOfBlwyRmOGoe4bd0/LxrLlhXZYZr1t2hA/a2y4YpYUCTfJyW5e/HoeTcGXV6jSWNPKNfmux2i5kfKK5nSCi2c2VK3p+ZipkWnxcIaUWWBLim7GYBOJ61UrICdV7/EBQV6KMlEf1PPVKaqDPxkw==
*/