#ifndef BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_container_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_container_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_container_new_t)
{}

#endif   //BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
TcE1P/3yixZMi/SrCrAp6H5cq5QghEmZjqpRf1SlM3PQKrp+eBgch9+u4rg2fvGHJ44d/EGhXj8JBqZhNrTis6FvJ1Y/7yXUor5kLMDgxTGFfxqymu5YgrAV+nQ/24jS47FDQMAHAEWzXa9UTSfVsudrdr7TgPRVTZtrVtN0aEo5AlrSdHLA6epWP+XhV6OY0M01s7lp1ltts+ZtNvxe5p2L8+U3hF0L7EFSCzQeXva2Jf6TL7ZBoR2MTzLpc0w=
*/