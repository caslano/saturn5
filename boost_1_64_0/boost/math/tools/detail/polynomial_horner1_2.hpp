//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_2.hpp
MWkR5nGWldr+q3MMjSxllltSZ4/kXNy4VLyB9ZZc5qzivK648DscF9JMK73nC22gxDZtqzSwgcyx4YMAg5nKuqpiwYbk8hvn0NCGWhOtW4Hzh35GNnwe6G8ayypsSLAhufnGOHSg/lAkdItZbdT40uvy/vomrKe/Bzi1lbY2lM7KgmOYV3+FeYUtrkUrBLj7WhM9qp/HHwh93BlrteXBlnQeF8+4cl6NWGUIaZXM3ioal/ddgX7CRGNIozobbGnDfXJei1osmLWkAjaQOTacAxgWt4RQbjob9kobELRBO1Upa01mw7i8XS6ziEnNqG4bpCk5PYpZ+MQHwvK2TmolOQZGXKG89wEOU0Y6yUJUio2IE/fgLsO80lo2vHZ1du8Ylne8t5bLnbO60kSa3i+3NwieE8P8akmtq5qq+G5UXubRBxXKiLo2zBkTDBmChYzeCf4AtIdRLTWWGNgzr+w/Cusv140iWnSxYJYXHwLL/tMwXdhUtsW1zmwZl/23gf7amLaxdfDpT/rTmFiWvVDcNq0GRsCyT/tQeb+rkKXCmbruHN4DUL7G3Y9xZaA9NcPMw7X5u2arj+2EksyJB8E3cwTjrcDOG9TjxF44ydwxl9FINdgJgmXeRx4e9DgxlkYucxqrFhtHKKrNjO9c3KeEurVomtZVPL6ZltsQ3xnLZXwtx6ZVxqGLforaX2WH+yQKYmDV0Io34G26UfqfAtKvrGGNQytmdAf6aYVuTmtVNSy+xZanP7bzXOZhykgulAgr9oPd0fz6+UX+tNQQWYlYZ/O0xzt/ucw5V0mjuDVo9qb8znQUP+ZNOT9mqGVGE4VnPqND3LYiOsOQT+/PZc9opg2xDKOj7eJ86gMFRm10XTeVAhixc4TjwqeBLEai1bVjhvSLjHIWdCrGCywwnZCq5i0BmKlRwnMmIFsjQkTtDWNh1j6KuTYtzpkeXK4BuaLamhBVmfVufLLYsIh+pEDWIVaLtq6MhvP3cZy1wyJu8irQIxAX2GIs7eyhsiEV462MuAbP5RUyFWHOcDIbKIzLYx2dj+fTucwiMVRUhFukax59J5biOAT1e2aCTWOyEExwbHwT0C1Y02rWMHTp4oWo+1S8h1DodrqSjNch7Ssh+W5lZTRnfH8us+SEqltrJDrcPtyZlOu5D+a8y7yuZcMlDTEcvIOwm07Lcy/xdODL7FxrBNbdw4UbB9uZY0U27n7UY+QyEouqZXXWtz9xtbcipuv7+RiybCtvuHQOkWpldSkbQKr4Bh/EIDXWLdU869cvH04LjB8/uHy7xBgq0YZ/yXcpDR4J4/cQo1GUc8xV6h9LO7pBIccwpjXacj7YwQguME48BGBwQa1Wpsn6yLEddwQYRFXYtG012BGm8RDjPjm/QZpzh0ktZxONIvrXgHEOYDhLDac16e2IU/hUbynEYNy1Sth6NtlI4b/gWzUAo5GYMSkGM9LFvFOPHsarnB/XyErmXMVYPmnA3pgiAlh6iwbgKWaV1Ub2NqUpfborV+ARhWtLLUmVrKs0y2UwsLjfC/AYEcIp7AYDw/Qe4r2/wJNK1NwKkiYUpX2w7/50Id8S3pi2VjD2GAnwsUHFM7pCtpbEMWNYnGj8F1uPPRTc7bWirSpTIwp9wJKtJx8K8UwrhQbPwM6zNPNpyOU1YryVzjoB3D5G9zoLTI2bSrG6io3tv9j4RGAj0w0VshHIZyu0cUjj5kOLN0gd1aoKjnGdmbZiLq7B4v1lgFFbJbmWTRhaYorAfeQX5fzLXDRMhmw4mHqb7Ppkv+zP3/NZMFdnWrOaSpmc9XxG9DIb0acnx3AIC21ly2ofY2T/6Bq/SbWb7cjFcQyWj2SkrlxV5a4=
*/