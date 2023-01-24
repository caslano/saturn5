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
wOtCiNtCiOOHH374rp/6uy6cXAJYKvKfs7i/iDGft7hf146GVKXc+Nbz7D7/fF4+R3yvTjOJC66fEwohCC/s0LAxAI77g7EB7B/sMZ4GoAPuHCjQVikReQAyIEBkNt3mk4FNN3YIpU3fYiUhkxzOBIwEaGXeQyQgYgI5JgyOaQVD2o1Dtjp77PS/xk5vxnY/46FLggcutRn021zYGTAYdHnyyffTbLVoNjvWkyBz4gBweHhYiq84yVJooJZAnEQ12dreDoQQTnrYwkoQ7u/23t7nbAGkEFprHQMzpfX1b37jG7tZlu099vjjXxZCvGjtEdeEEIcPPPDAPeX2PJkEsBD5T4n4C+qo3p4V8cv9WtyO379MZ7x4+zsMvvdSCfHJr6sqQHl3HJe/+dCDRFGEsgt6XLCPDCSHBwdMZ2DsjWdlGk6CUBQOmtPUAbl64dKEAGFtw7kdogGiBUgyTHDbLJMcTgTXY0VjmNBpxgy6CRf3Jmy9OaLfHtNtHdFrjWg3v0Mrium1Z/R7gm47ZDDo0uu06HRaPP7E++l222CNk4GUNiiK/DsfHR3N2R2gnlgsUh1OqmI42N7Z8d2fQgjRtH8DIcTTALu3bv2szZMCqdJ69zvf/vauUmo/TdPdpz7wgX9ticObQojrQojpYDB4V9WM9QjAAmSrPjyduL8G4vs3i4jLSnF/BeJ7aVorXtz7NldvP8cnacyL+yaT
*/