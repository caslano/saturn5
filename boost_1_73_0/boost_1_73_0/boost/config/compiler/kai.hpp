//  (C) Copyright John Maddock 2001. 
//  (C) Copyright David Abrahams 2002. 
//  (C) Copyright Aleksey Gurtovoy 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Kai C++ compiler setup:

#include <boost/config/compiler/common_edg.hpp>

#   if (__KCC_VERSION <= 4001) || !defined(BOOST_STRICT_CONFIG)
      // at least on Sun, the contents of <cwchar> is not in namespace std
#     define BOOST_NO_STDC_NAMESPACE
#   endif

// see also common_edg.hpp which needs a special check for __KCC
# if !defined(_EXCEPTIONS) && !defined(BOOST_NO_EXCEPTIONS)
#     define BOOST_NO_EXCEPTIONS
# endif

//
// last known and checked version is 4001:
#if (__KCC_VERSION > 4001)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif




/* kai.hpp
+PV8TA/YHxiFlqg4jB9NDz4Y4VM3W/LvQv0u6fdo3W8Buihgbw9Q1sUCuqOVynv2aBfGhsj38IdcLCrbgW/2X63297yBXaZfLTdnpg/eZ88fe6f+2I/nlpdl7Tft2D146x65cM3Fv0gPZFZkOIwDT/Hw8MA9MtbTUTybBvDZG89G1pQqXOPSJDhKwktMw1St3T6azbKpay5wHbefiFZxFlwG4XWQhGa4tVHFVUshOxqNwBtHIW6u0+nzioKNjMR+P2PF9sD6H1BLAwQKAAAACAAtZ0pS8PN9tQcEAAC9CAAANAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX0hFQURFUl9TSVpFLjNVVAUAAbZIJGCtVWFvm0gQ/c6vmON0JzuiuLn21GuTVkdtekFxgAPcnE+W0BqWsBVmEbskcZv+95tdsH1pIjUfimUvLDNvZt68WdsrE45+2GXYCg6+e6X6m+KF684pbPknmsnHHdL0DvoPOq5wfUKoCRy87tIxPMnrDkbaKx1inar7NH1CuJVKUv1MlPMqVbe403sO/lPebFt2VUoYTcdw/Pr1H/AMfnt+/MqCGakZrSCWtF7T9sqC01zv/FmS21tb0HcWUAmksu8BJiUTIHghb0hL
*/