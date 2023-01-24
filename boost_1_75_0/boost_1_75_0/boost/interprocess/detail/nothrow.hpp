//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP
#define BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace std {   //no namespace versioning in clang+libc++

struct nothrow_t;

}  //namespace std {

namespace boost{ namespace interprocess {

template <int Dummy = 0>
struct nothrow
{
   static const std::nothrow_t &get()   {  return *pnothrow;  }
   static std::nothrow_t *pnothrow;
};

template <int Dummy>
std::nothrow_t *nothrow<Dummy>::pnothrow =
   reinterpret_cast<std::nothrow_t *>(0x1234);  //Avoid sanitizer warnings on references to null

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

/* nothrow.hpp
4H3C/07qd0WleVd+ZfN0U3dcJMWTyafbGHSTZ4Vp1kpmiJh7apNVbNhgDmUWlpq/d3hgUJBy0HYs3EnOm3ZwQczp3smjm1R2vF6c8THC7uEDI67Dadc5JfHu+Rmjtefzm9RelJ1MWWYL2zNvh5QMwpjH3vvDlotGq5EoQv5d0grW6dMKSfkiewlIbsCQZFpF5JxPS0RRZQRTZXQ1rCrSyQ42/3ymlZ/olMXPYJRqHB5q1LkI+Kg0B2qszSyxIMVsEhTJHJtS1Bi+kz6i+etba0xmvHe85eqCNE60HqiRMCuT57P2oESJgXWSqfPm0TcDXarclZcrRSI+c5rXqBuWbEIZoWW1G78m1WZYX9LUJ6pd95wi9Uq7y5BaPNPR9dHQ5Dz5+4D3tfzv0fq+BZuR4kuTq0CMVuESP2Omd5RH9qiC5EkgMPYF81JAINhujJ+WwMRZdjrhhgSc7mEzFpZdCjpXlVAqheOGGXFS/VInhz8s06SRpWEbXTyMyJmDQC6NyKSVJSf+l5IZMykW1vzR6ztcRb5daCXbWjFSV/dW84vPmPdqrqfRlqDudzbyxBp3dChAVbCX/lcSd80TMNOGb5KnR9QMPTifjxy39vWXnJv0r8kraHDN/gWra9ZWux6Scnpt7Z9xAhtzlsxo6TyprSvQ3jmF++Qe5Ar2L65ftu9+W6io0iomBMPt7/QIqXBemM8xOBJQvxmn2st3
*/