//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  BeOS specific config options:

#define BOOST_PLATFORM "BeOS"

#define BOOST_NO_CWCHAR
#define BOOST_NO_CWCTYPE
#define BOOST_HAS_UNISTD_H

#define BOOST_HAS_BETHREADS

#ifndef BOOST_DISABLE_THREADS
#  define BOOST_HAS_THREADS
#endif

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>
 



/* beos.hpp
97gKhP3DoPDDh41tVZLkIlqEpA3lyW1upWhRGW/ziPsxSdcuwokdokXV0eQ+t9ffFvWLJPcNQ7oMpGvk5BtQBXDfUGunFVs1fcVuZZ9qWlj77qWnZzX8QitS5SNERbPZ4mUGK3GDt2UokTqg/h+pfiPi0SKpxXzfqUJl/+/cOuF5BeiqZIU8EnWO5a6FuDWjH/UatauNe3BW2/hZWVSZGmJzzcrkwcYIn8M7bv9QeiKsqrL/G6sD9NHznB+pz6M=
*/