//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/detail/bad_weak_ptr.hpp
//
// (C) Copyright Peter Dimov and Multi Media Ltd. 2001, 2002, 2003
// (C) Copyright Ion Gaztanaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <exception>
#endif

namespace boost{
namespace interprocess{

class bad_weak_ptr
   :  public std::exception
{
   public:

   virtual char const * what() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return "boost::interprocess::bad_weak_ptr"; }
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

/* bad_weak_ptr.hpp
q3XUd1MCjnsadO7kVcJKfL4GogoKFBjXQgVsH0bdjUilR685ApnBfCw/1sr3DEtu117ocfpD8jomuEVfHi7via+vBl++/wA8wp+NAGiowX24tSMqtPEvhYwlOA9YLzp+PNkUP51k3WkZy6wNzW/PNvCbppnyV4JFwe9McwFDtb8FPg9AAezxYyas52Zs0S2y9Z9X2I8Za1h/kbum3dCwzNPo7MezXjKmjCzsblavFwIkBx5fF8bnGSsp+FjmPNAQim2i2It5hZAT/xXBjWm2RBwqVDEKVRuEC175v05t/txMU0wHPwp5rzptQQ7ZukDPzmfck1zCz/KfeS5+v9cCJ3SHTNVyjNpz442mWOkxvruVFxeo9zAXYqol5isLL+v6dY1g0GHU5ttOM/zFX6/ljmbQH1CvexiEOCYyLtCpU9bjNlNBJIFXo++CvNRX4j0QXGMt3/SBmtgkZknQ/JOpa/j9aUKupNyJBpbb/Ru/mTzPDQ3j5CxFE56a96UGOMMKW/bl39joS99pjcErDe6lij7+kqfV3D4b0rarWEld+1DDWGo9txOToFDF+l0v+IyiK6lLZlZLDcgtZKV6rnhpTHivWX8VRp8zzNxLHiUXYJoKVbZScA6Wbo4xLlBpjIlsJfHgycNSs9rqeO8slcpZLy2zBZTK+tZ9qBDvL+PDYihjQTwGSTnwZUjkcnHeKLu/mt0UkfC+kJomMdWT
*/