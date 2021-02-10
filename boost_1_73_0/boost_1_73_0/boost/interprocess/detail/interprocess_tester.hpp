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
c9hoTjWYYU5NZ0iWdUA6TgaV880Sbyk0QiZOQKWNYs5HwpeRWPIk5E4rvcBIRYkbfREEwJTQrqjcGMchgPRYwiT8DPWn786DvHgXXNFBxMyDF9+/xmRElOloNKUBcDNT0K2BnkaxymFHo1hnHe7RDaGfXkyzEngoz3NI+W92cHqS++GGvsXMFjaD7NBV8Gdyuv8LHVaY9ji5JD6XWLtrAG3aDdAUlyyCfakW+CF3la5mehxgl2Zv7vbNvOsbW9Q5FrB9ivWWkrcRfZpouxrd0K6t8f/AZ+RbAMazMYWwpns8+gdQSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAABIACQBjdXJsLW1hc3Rlci9wbGFuOS9VVAUAAbZIJGBQSwMECgAAAAgALWdKUjp9XmEeAgAAnAQAABgACQBjdXJsLW1hc3Rlci9wbGFuOS9SRUFETUVVVAUAAbZIJGCtU99r2zAQftdfcS+DDVp5YwyWwB6y34WsBNI+F1m+xCKypEmnphn943dybKfpYDCYwbbupPvu03d3q4gRf2YTsUNH4sPZI25ak6DxOpdNaDDpaGpM0Po9kAftu2AsXkCdjW1AuQaMS6SsBZ2j7R3W1GUtNtF3kHyOmuNzMm4L3U7CjR+CDV3AwWfYG44eKJUc
*/