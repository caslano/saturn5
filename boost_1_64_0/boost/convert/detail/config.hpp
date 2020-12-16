// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_FORWARD_HPP
#define BOOST_CONVERT_FORWARD_HPP

#include <boost/config.hpp>
#include <boost/version.hpp>
#include <boost/optional.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#undef BOOST_CONVERT_CXX11
#else
#define BOOST_CONVERT_CXX11
#endif

// Intel 12.0 and lower have broken SFINAE
#if defined(BOOST_INTEL) && (BOOST_INTEL <= 1200)
#   define BOOST_CONVERT_IS_NOT_SUPPORTED
#endif

// No C++11 support
#if defined(BOOST_GCC_VERSION) && (BOOST_GCC_VERSION <= 40600)
#   define BOOST_CONVERT_IS_NOT_SUPPORTED
#endif

// MSVC-11 and lower have broken SFINAE
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1800)
#   define BOOST_CONVERT_IS_NOT_SUPPORTED
#endif

#if defined(_MSC_VER)

//MSVC++ 7.0  _MSC_VER == 1300
//MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)
//MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
//MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
//MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
//MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
//MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
//MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
//MSVC++ 15.0 _MSC_VER == 1910 (Visual Studio 2017)

#   pragma warning(disable: 4244)
#   pragma warning(disable: 4224)
#   pragma warning(disable: 4996)
#   pragma warning(disable: 4180) // qualifier applied to function type has no meaning
#   pragma warning(disable: 4100) // unreferenced formal parameter
#   pragma warning(disable: 4146) // unary minus operator applied to unsigned type

#if _MSC_VER < 1900 /* MSVC-14 defines real snprintf()... just about time! */
#   define snprintf _snprintf
#endif

#endif

#endif // BOOST_CONVERT_FORWARD_HPP

/* config.hpp
L/nJYnL+cL07VsF5g5FbCbbD/XMXm/geJHCkJ3ZM3HuVeGTKPPwx9pQ4H75xHCwoRC+b42eJ0WrHECs8IXCJfX4BNveGOxMr5V8n7/IdeD6BtXD2tTaBy+BZ9mpktJ0cTSL2VBl/C4cjh8n314MjyCClBfaG/1t7Djt8gc+6LOIMf2edbVnTbs4aP7t4MtxtOGOhczVfpX0k8sR/V+KstozFF75P3m4nuRByOQ/hl95pyk9HMAqM2I8ftcfD8cqTW57vD6dTzysaDOwJTy3eBRahI/Fb8W1ZxOSz4Hyf4zvh7et4h/fOBPCVftHkTqqhC2OEX54E53sYmz0KFgyBm+eSy26AL/jDRuxHrL8P3wGXXn6JOGkMf8NzajP+lXPq+6ueYNno3fBtF3HDIX/IN7YNR6p7BzGb+I5w7H17f+7NycslnBcxCG+T/cGeL4ilsDWWxmeWyCeC+65d7Bm8Xl2bvTTgbMhhDo1hv+jwZHz6qr3ICrwaQl4pgHM6P5LYsRQ+hi3lEJvNxCf+tZjYYRz4+hg5/Wr45hnYfSP6NsIHZJLLQP5NZyGLeuBZO/qxvyqTwZEMZDiGtyCvEkNsa+dHWADwgyG9wJzfyvGdh9evl6Po+vUA/h+d26r+9PLDH30IFbLha2wBtUtsjM/PGeCjJf81nmrshXH4U5ThGO4aZTt/7qwoQ4VpU1RQkp/hFmWhtvK1EYW/H209fy7YnC636ORwF9ta9wxLNX7t1Yv/yijfKVyDedF68W//GgH0rcpvlCMto7y8Vl7T5oe1EfvVYL0VuFeuIdZcibbiD3jK76J9Ja09a+JWEqcs//kba6pSw5j7NmlNxdqaGrCOCsY6kBdttH9XM62pgu12fvfVnrXzb+zH0r4GvzehfcUbjF/sNUdFcozgCX0q3WAO+nBe1rkq2YL4XeyrRNuXOP9gyujLQDbl9wDtdxqY6oEKISuy7eBoBXlceJt2DvUN2dGOE7K0u1NrR0xCOzAQffPoFivOc7hd6ZK+sSTK8nLypTJ2QVl2QUmRzSirqrTLcI6SymooZQWmvkGibJTLKfetI8pGmPveobQzlWEvlOW4M9Cis03Qs8rofiNJ95tRr+hXcZ6uV4WSTjcReybvK/7dVNv/7cjJX/Tld34UWTEXf+DMmqya6zJlDIt8W2h9OA/+8PkGrU9LqU95ad5Wlnnvq8GPZd7W2hhttLYeTKilnlGpfEaE7ZwHZfkUss/WGia0k+TCOeTkudyFNBDS8fyCjGjv017dxc704R5rVX6RbJV9Szig7buDtuaO5v3Rjh/L/jppbTtrbaN8rsHhSC8qduQWpDtzXY7Cgpz8YleRW1mQzxpWJ8Z8QBuzniYz1scfR2KuM92VXZCb4SoCY5nPj4V0M2SEDB05BWklmcoE6j8ZEYz1KU+HR4b3d1A6SL/Tq8d/3k+Gs9jpvRdRqu2j59+QTV5JbnFO2qhi03DeFYyo6n+YRZ96KXti7pz8zALNzsJrCFnkpXnKorT9R8j7/y/OxupHqlr8iF3TiWDJbqp4+yBwGN9q0ie4DL8H06acaXwrZpcjduAeMSCgpj/7JPpIiIuOC+ttd0TFhvVOdkTHJsTHDrSJOn9rXfvQ8OiUJPuDqdFJ9kjbWdowmld/R2x0eFJYkjpGJWt9ckpSQnzv+LA4e3J073iGOcc45E6t7eLDUqL72R32+JSkgYkJ0fEp2nzjbd5rTkkKi+gbaQ9P7R0ZlhJm09rdYP2JSfYoexIb0PeY5OhnT0qOToh3xIXFiN9Cmct3ndKnvLk8Op5yba+UR9pj7Sn2SIfYoiPWHt87pQ97NOr7pYSFx9p7hyWaWqhnoW06ZWCinfk=
*/