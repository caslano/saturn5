#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP
#define BOOST_INTERPROCESS_DETAIL_SWAP_HPP
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost { namespace interprocess {

template<class T>
void simple_swap(T&x, T&y)
{  T tmp(x); x = y; y = tmp;  }

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP

/* simple_swap.hpp
8WSAc4zR4R3fNQa/61tN/q+H2GtpeZDttfKOW4nHb+1pXUHPtxpRcOtg+PDm/pXWH/X48DLx3mYkgK+PEavTQfJEr1WcN1bxpbqtU1p3rz5EcT2KVuM1uoKmgvR3SHoN8JjsPzkWxv4hNXcYOfaX7z1Bmckat6xNj9Fre3R36Bj72t+Plfzrj7WvZadWes4Yq/lt+5NGcibOl/3efuBR9S0B8S+12ixZ37PyCnNLSh3tNmgPe4HCnPIEv915hp5zPPvB8aPZ0lp3XT6Bv4/RbVnep9e7nfuaxO7yJ+L7myfYpp6i5w66rdvjorJ1tFmxWb1NfEc9Wl5msw1M2pxvHI2Xlp6h16Plg6EQO+OLY3nv9LNGTCXdScfXjvI9ztrvds0ESnuV3xeJu7RxHc+O8SrcfH62yvOiEHse9rJWskFOozCJLt/hZ9vWVBYTXweT5j+QZ+OHBb87qthB85+hkLlwYz3rqVp9dzSZyjOyWtvRXOJpqG1HnA7M84I61k016liKf1uQf+l5VdpfgnnsPdz6tqpE5XEHwvYYHrQzLahVHhPH6zxWZWe6lvL4Z8iy2x35zB8eTPeQsPK50eL/tFr+BOE/HszXsicpX+HoyMG6mUPtbLTt/Ukj5P3LbgtblyV9VvBxhbWYswb3u15CZRjricQa0SpofS9hbJhh3kdyuk3Yezb8sdx3jJyiwlx65j5Jleq+p4PlN0klfPclOqxIDrdvwcRN5r/SM1kmnxlr39+RPM7+PH6cXfe9Z5xdD/lQnh8N6sLj7fz9x9v3ILw23s7ffIKdf+MEzR86RrQfyyV4DJ7NFL/JY0TF5ZX0GpXfvBwMEVXvsb6TwjxtOvUZjs+pz+i5+kMSNrifZwM9X+TUd3RcWrbqtXCqH9e9qxJvzytU2JGIj8ervRTX75Dmm0ybTNbzYuHpZb5ndLTkcsZE3us4Vu1jHIlyHMPfrnkHRV0SiPE2UfsYAxHeiECcN0HtrffGB+pGx0QEmnn78GPUCGJp6PXQ9sZ4ryeqTdQQ9LKLWpO+4tjjqPuS+/wd/pS3nUhlF0c67XNzrVP5KUysSWOdVR4bzIFwq25OnjTaMKZmBOXog2HPyYPypjelK47ljcS3KiMo766rSt7Y+PdY/INrlI+K/4ykF6yepQPDSV972/vajAm+rwO9z+8y7iiSPWciA0G1kIEJwTU1qpdMjDaxuM+xM3//Gqatuzb6KckzvfZNsuLzy+3z8OQr7M8rrrDLlu+ucLflbRnPCbwapPwXgYaA58RELVv45oWSvPlVrWtLO/2RwkxB3FjdAzlljMRL+Q/up0Skcu6iU47Y+QeRPCvPk9MLXeZJmj/B2lednZWfPyMLd0bkZJVlOW1uOkyV9gVzEs1pEH9b514b6dcDiKcl0uyptBau+/HlxBNH3/OlQKYfGhfeGQbUVmVv35egv4K2h9lWg3rRefTuyLD3g4WurySE7gOm+rLvBR5EbVjXS+PQsy/s5W/7jnrvFNnH6+G6ywDejrjWTqrU9pT1JTs/L7eQpu5h2YwoDqnT9sSHSFzbmJ13LY+Z+MC20Nm+KvHeSrzFlKRgW9lF/sVmXWhDwf0Nd0yhtXWUfl1n+6sU520cJwpZ193z5O/XewEovljnnjCKS/eXX3FcRWWzcy1ba2IIf6Lmr7J/JYXwJxF/zf0rOSRMsoRx9i/9be0j5D/MTEEe8zAOrjSWWWPjnZRXryXz9xBvG4+9H+qyepz461p7S3Inq+c0lJZHfyNGPAONxta8NKRx0Yf6Wqb9MJn3mPQD/xbES3FQuiRPsm/6Z+ar1v7yEtejta9hxyT+/qoh3Bz7vuX9p7jsTOd7YdeMDfKXGgk=
*/