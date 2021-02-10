//  (C) Copyright Jessica Hamilton 2014.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Haiku specific config options:

#define BOOST_PLATFORM "Haiku"

#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_STDINT_H

#ifndef BOOST_DISABLE_THREADS
#  define BOOST_HAS_THREADS
#endif

#define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_VARIADIC_MACROS

//
// thread API's not auto detected:
//
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>

/* haiku.hpp
vZOQMZLypoKDwZOidMfbFL9ZbkFN/b3Pnj/2PvljP55Znuk9NhVXlHtk3mMi19MAPnvj65E1JQp/ASQ8hE3bZd+uLa0e2VSVqJWWmZ6Y1vA6uAzCmyAJzQbQIC5UKwg7Go3AG0chrrxP0/3Cgo06csDe6+/Di2drnsTGxrb+AVBLAwQKAAAACAAtZ0pS6CAWX6cEAABDCgAAOwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX1BSRVRSQU5TRkVSX1RJTUVfVC4zVVQFAAG2SCRgrVZtb5tIEP7OrxhxysmOCE5aqddrk+qoY19QHGMZ0pwlSwjDYra3Zunu4iS69L/f7AJOcrmk+VAse2F3Zp55eWawu7Rh/6ddlqvNwQ+v2HxjvHDtlGaCfyWp+n+FOL6D5oOKS1xfATWAe627uA+v0rqDntGKW6xjfR/Hr4Bbaif1z0ArL2N9izuNZqs/5NWtoOtCQW/YhzeHR+/hQC+/O3CalJQwCBUpV0SsHTjOzM4fRXJz40ryyQGiIGHuI4NRQSVInqvrRBDAe0ZTUkqSQSIhIzIVdIUPtARVEMgpIzAMZgt/+qcD1wVNi9bOLa9BFrxmGRTJloAgKaHbxkyVCAU8RwtoP6NSoc1a
*/