/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP
#define BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/recursive_lw_mutex.hpp>
#include <boost/flyweight/simple_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* simple locking policy based on native recursive mutexes */

namespace boost{

namespace flyweights{

struct simple_locking:locking_marker
{
  typedef detail::recursive_lightweight_mutex mutex_type;
  typedef mutex_type::scoped_lock             lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* simple_locking.hpp
ZbkCY9eqHzSJzGgbcJ5lfCfikU9b05yo2itWnGeSu32ZQx66ZakikaIlvLolpPZpkDiCL2QE9qRllRpVIFOqoIdTbGBDmXTkNpeeliB+waQ038CR5VJYRY2PMD2vVGp901VhYxuMVz+CirgWLj6vcRTVKpmDI1QOW1FelQAqylHzFiRfcBisATXb8MXhPEOVUF9Lmo4oSCYJcoLbCZAD2x0XeVGlcNQl+XI0hZUITxb5jWHuCXaIG+jIOlsIhVuCSxUDSAxkzqxcyXKDdrHYEExOsrTNhe07oTIgldVwJY5sbW3VeV2K2HYfMl02dPVQKRuCrCNAfQDkmG20jlqA7V2mEnYSKLDZsNCSa+v8psGuUUt5nFdwqfSy3PjUtx2gOVEwZKNtWQQDqy3nV8bhbCUtynCjN0mxkp6TPHok+iD0OxgXVf/MMIPPAh5tc1xrQniD5FH6RQpb8Qa0o+t+hWRdBrpD+TLaL0abd0BiXGp32joy52Ze5nYYQYHETmaafcclse/uVkamjARq4bGpHLlzx3mksNONfcMgkSAdmdnpAXgndjaaHKAXjGmAKJ8UF11suEnMDkgb1yqexSQHqxJmxOYaGYzri6RmRJ4JpG2mpfi8ZQIGlEC1XY8Qqql58PK8iU2JJSCAu6xH
*/