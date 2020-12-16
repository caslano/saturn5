///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATION_TYPE_HPP
#define BOOST_CONTAINER_ALLOCATION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
enum allocation_type_v
{
   // constants for allocation commands
   allocate_new_v   = 0x01,
   expand_fwd_v     = 0x02,
   expand_bwd_v     = 0x04,
//   expand_both    = expand_fwd | expand_bwd,
//   expand_or_new  = allocate_new | expand_both,
   shrink_in_place_v = 0x08,
   nothrow_allocation_v = 0x10,
   zero_memory_v = 0x20,
   try_shrink_in_place_v = 0x40
};

typedef unsigned int allocation_type;
#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
static const allocation_type allocate_new       = (allocation_type)allocate_new_v;
static const allocation_type expand_fwd         = (allocation_type)expand_fwd_v;
static const allocation_type expand_bwd         = (allocation_type)expand_bwd_v;
static const allocation_type shrink_in_place    = (allocation_type)shrink_in_place_v;
static const allocation_type try_shrink_in_place= (allocation_type)try_shrink_in_place_v;
static const allocation_type nothrow_allocation = (allocation_type)nothrow_allocation_v;
static const allocation_type zero_memory        = (allocation_type)zero_memory_v;

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_ALLOCATION_TYPE_HPP

/* allocation_type.hpp
R1/NgG2V7EyFzVdh/0jmnf/dADso2SnnMHPYCclqv/wlDnZestwPUw/ArkoWbOer9OWOZENDW52APZLs8luHtrAXkq26m+QAK5Tm97T1nsgiE0J7oeSeyNREiPotk01gOjI7Zp+fHt8BCyRzYNblbH57mF6Km75PfxWWQKZidufoax9YshTXtFmd+rB0Mhdmy8696QYzSHF7A3emw/LJ1Mzs6u2/D1NdNI67ZHP7OMybjOdZ9eThAJiOzIaZpnnwN5i/tOYA870HYWFS3P0ov5WwWDJrZq0fqhvBEqQ1+ydWnQlLJuNz6OU+d63SMzJ7ZttS1itrZkt2s4fjJ1iutJ/dzBGpMJFtbEPjbgXD1JI1fW75B0xLxvPs9u/eOjA/Mmdmv/c7dwMWRubE7PH9Qx9gCWR8tjsuLFXyTJHsS8Hd/2CZZB7Mdi6ZsA+WL8VNuXVSiVNdMhWuzHJauzRW6pNsw4PdR2H+ZJbMPuYdLgsLIlMxO9ewVltYLJktsxujW7aAJZI5Mgvo9ehfpXYyZ2bHLjybpNROVolZ591xqUrtZN7MwpL+soNpLpuKCsxmWeX7wPzIXJip971vBQuTbNdOm9KwBDIfZpVvXJoOy5Dsc/73GbBCshrMxOCBFWDaK8b73ap1VMnTX7LU61E5MD2ZMzPPmgEfYIlkHszE5SHOsHQpbsfKW3/CDGTuzK71CBwPE1dNhYbZkvsNzsG8ydx4XMSk8jA/slrMGr++XAYWL6050ORfpZ8pWBMW9doelimtKXwSkmHimvGaD6rOvqDkScbXvHPZf6GSJxlfc2KvcWlKnmTOzMacz3gBS5bs1sQuC2AZZLyf159arYPlklVj1qNLnd4w9XVT4cnsSvt+KTAdmSuzoP0lz5UgMjWz6NhN85QaJLsZ0z9TqYGsIrMEqxeVlV6T1WT26PLYSjBxw9iavg/0gvmSVWfW81D/TjA9mS2zy3GfDsMSyHjPht2NbQZLI7Nh1u+mmzssg4zXZ9J+4ldYDll5ZrEdv+TChMH4uhTn9K42TE3Ge13n5Z6mSn1kPE+7r3cuw4LIKjBzWvRWrdRH5sHse02bF0p9ZNbMyjS9+0qpj8yNWcg19V9KfWS8Pu8aB4Nh4qZxLqnqf2fCvMn43L0OHXaG+ZPxftbaFVofpifj+9kWPlgKS5Ss5wmPFKU+Mjtmy+rr82CZZFbMPoZOuQAzkDkyi6mvbwjLJ7PkNQx5VHLNumV8z3DE/IY3TE2mYnYg4VMWTEvG53Dm456NMJ0U94/WfBYsULLHD3Z5wfRk1ZmJv++uhqWQ8V4PixihVfpCxvu5MDkiHJYr2cWz1abCzG4bX5figlf1gnmT8foeHWw/FuYr2e6kll9hfmQ2zLZHm75WapfiwvcfnwcLI6vCrFbPldtgSWSVmc3uHXNQqZ2M9yys3EsXmLhj3Os/LthFwdRkvJ9icdghpT4yJ2alLF5YKDVI9l/ju4GwWDJeX/mZ5brAEsgcmL0Jc0mAJUvWZ/CDLFg6Ge/LLL3jLmW2ZLwvy5e2nabUd9e4Lz3qfTwL8yfzZrb42cGdsHgpbktMizFKLmQuzE4ldPgCM5CpmEX/Objk/QqZFbOuVa07wMS/xnNY0fN9Z5iGzI7Z40Yxg2C+ZLxngz+Ghiv1SXHLwzKawMLIeJ5d6m9qrdRO5sxMM7q7ByxZshPNa/nBMiTL2dPOBpYj7edu9y4XVijVMLzO7N4w1T3jNVPtw+JhWjJHZjP6jnSF+Ulx6y7GdFBqJ1Px+UXFdlFqJ7Nm1rHLZE9YIhnvZ7MtU57BUshsma3Xv8iHZUg2b2pLZUYGaU16h2AJy5dyWdSz8TuYyDG+ltv/mXE=
*/