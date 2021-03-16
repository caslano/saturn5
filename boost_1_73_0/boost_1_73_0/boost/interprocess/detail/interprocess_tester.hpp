//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP
#define BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

class interprocess_tester
{
   public:
   template<class T>
   static void dont_close_on_destruction(T &t)
   {  t.dont_close_on_destruction(); }
};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP


/* interprocess_tester.hpp
rY4mHHXyUVjWmqbUlHTCmatTjVJgDp2fEhuYABIIpIO/hRYpkNYxGOXDOGc8Sn9EaaxsdjQt3UWYs+hIbgNu7RjUhiXp6N8GKXT0bosVavUShLF6tO7iRi7lClYx0zo2iq4IaY+QgeAF+httMUQZABjgfL/1mzkY69dIgCYxEeI/mSQBuUY/jaZ66BdzQyJVrXixMdKZ9yGKoVBqHPoZ0Xii64lSghy6g+gAoluIJhCFiQwiCpMYSvQpoucThcE=
*/