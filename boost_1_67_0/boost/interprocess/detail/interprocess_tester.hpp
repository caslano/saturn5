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
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
*/