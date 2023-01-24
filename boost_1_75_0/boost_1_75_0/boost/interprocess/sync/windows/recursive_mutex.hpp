//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/mutex.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

//Windows mutex is already recursive
class windows_recursive_mutex
   : public windows_mutex
{
   windows_recursive_mutex(const windows_recursive_mutex &);
   windows_recursive_mutex &operator=(const windows_recursive_mutex &);
   public:
   windows_recursive_mutex() : windows_mutex() {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

/* recursive_mutex.hpp
IaS/Bvv6vOND79oGA6DBeJ/AMDHKv3STB9gZw3r2uAthMB9459zJPhB27Z3z40Yo8IlvENq93CjqfjTnjXqv8dTX4B59deT7hhoHCx62N/REewP8vIUfCS6/ih5gRzZhvQkWi9REhXazdcjv7sjY9ei83cOC/dhQAK+AxzRBBAUwB9TABggVQ/kHRkttT4Xf/8+q9P8e887xj1nd0szC0fI/MVrW8+8Y3Ux3hruWUXhzoK9sIdTucKGfkTaOY0s1Seowphv3saTjVr8zg7fWKz1QSjtsyMgxLyUlcf9DNNCvC95BnhrD9dORWkoFq2OxuJzCR3k5BThQRgac3LP+F+opseSuzgyd5vLbQNb3rLt8f/BsXvZd1opAy+ubDmH3W+8dc6+0BpCNqZjvloB7TnsUP05ToejHjvPhnW8NP+wMwpwehL34V6f4Rf6M/Zmxbkxd7Fq4WVRthJqQpbh63V+5xZcrpzArwW+44nket2rEV18SlbbQrRQVqlobj5/Jfze0y6eJMdR0nbfi9LkNPVCNGptiH85ENtemdTJKDIWE7PagqpOHS6mp4VV+ut0jeXL+dFEiApa32B5QS33Ghgl54Xg4eQKeGgyt/X/RJLomPgv+VofmLck3P105Bc+AjkWucrlgemfBFI11RbDLrdLeH49JRiq+gNkBlLb5wiuSlr0+JJ8BjsjgV+QdHvcDMft3386mxX1Ylnfg
*/