//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP
#define BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

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
namespace dtl {

template<class T>
struct value_init
{
   value_init()
      : m_t()
   {}

   operator T &() { return m_t; }

   T &get() { return m_t; }

   T m_t;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

/* value_init.hpp
wm8rFwq8Nnx8nOuTfVdNYQD0tyAzeyckBBLLFOxmK7q8ElAIweHhoVv3X+3tq8teZS4OYG5ua+7qYqAq3DGkLz33byjGZY22R6MhUobkAUV2BgghONjf43gcAZGN95aEoaQZGUlgMIhoNkJkkJGlWM7vsNx1Bu/ecWnHeiqz2EfaOSKga+qpPltWrkpoXD3BfJ1aoZQ0O9/ExgPgQoKTtKwG1B2RWBf6W7r1ngsqn8njyrXxoYtY9oIszpcPBb1bOKx+R6ttaF+S9MR+7W0QokAS0wh0ieFV4wCcEbBmXmvg5WXvlqsAtYifX99d7l+3ou/klv1TvEP+kbzBWC4AMBlPGGxve8zbIImUklt7ewyPzTHZTgIIA0kYCjrtkK1Bg34v4miUMM0Ues7AJhdM2AoC5lb7RQKyZuFszct6s3NuhtdJFv4yZcs1PAlGa0gzxSwWTKaCyVQzmWlmqaadCSIFypcC/C75tAlyUb7W81jztsvsByXJwq/fL+++uaB2YVBJUKLof0l1qKu7wv11VkgBzhMQiZRWK5pzAVbnc5Ikc54BC68teHWg6gb0bkrveRfwf5l1/1yDfWoLer+eXWDuY9bAdDplC0CIfAwFEAaSt9++wcFRA9kQhKG0gUDmuikEW1sNdrYb3D6YkSSaNHWNuVnqXy8y2inKyOkQsorIlCWEuTprEH3lMw3CbSpS9MkIQ4osg1ksOZ4o
*/