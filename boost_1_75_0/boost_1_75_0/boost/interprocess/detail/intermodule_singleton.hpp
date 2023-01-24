//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_INTERMODULE_SINGLETON_HPP
#define BOOST_INTERPROCESS_INTERMODULE_SINGLETON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#ifdef BOOST_INTERPROCESS_WINDOWS
   #include <boost/interprocess/detail/windows_intermodule_singleton.hpp>
#else
   #include <boost/interprocess/detail/portable_intermodule_singleton.hpp>
#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

//Now this class is a singleton, initializing the singleton in
//the first get() function call if LazyInit is false. If true
//then the singleton will be initialized when loading the module.
template<typename C, bool LazyInit = true, bool Phoenix = false>
class intermodule_singleton
   #ifdef BOOST_INTERPROCESS_WINDOWS
   : public windows_intermodule_singleton<C, LazyInit, Phoenix>
   #else
   : public portable_intermodule_singleton<C, LazyInit, Phoenix>
   #endif
{};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif

/* intermodule_singleton.hpp
vyC9XkTMHo/m/aa+WGCtmeTbCoO4ZKmvsOssYEfYWohIIQJyOkKCBD8LijPI549U+KyPwHOQmTHyXnUGeh3W8O7pS5+jUxAnWRCrhlQIP5NTVxV8qaki7+Z6bbB5bxW2l4AB1qwjwaUHRyLQiTxRBBmriamvzpZtZ0D/hZQc5uriikkK53y9ygzpNePY2JMR1AyQ5AyCeSOPA/3tv5gALrnyv9/5uGBrkLjxzungmwSxljs8ffSEyo2BquQMxx1Y9rpfiA7sU7AVZ/z5pPX0ao9B9EPWRYeinPp0Gn5/uv+YTm7i9q/gpWezF8roKDQkjtfYDHNUWBrxO29Jzv0E4jTUVao0r7wWDcLY3loO/4ZSmBzerpk7aNuqyII78FUfwFUav/FnYyEzeRU+tyJHhSGVV+YVhjK4OS6eE7xJDz89Jl42vku3s2vVZ7+pUsITGJl7N1c9qNSN6rv34y7ooMkpLTIoe8lU7eCr2o1SaiUcG4RPA3/qxl7/7gN43/pNdZqDCbD1Fqyf8jBrQrZYsC5OWEoUuL33Cl9UZN5wwFqjJGVm7ImEnmSl3mK7gIuQcM+Vgr0vkGvMgL7Q1ZHNe4QxnzlF4I9AZjHRAI4J14UcEfNLEMZweXAaOYDnq+wpMbs2RSLnA8tv6uLXsgQ2eX3z+nL590OlviBxg+5gQLmPh+JGR9fdzXXHIkmEyDkdq+82mlACUo05e6Ef
*/