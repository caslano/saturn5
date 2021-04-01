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
4GtOmfDTCeNucwFMKAdpHcfb42sASdu4tO5VVq8CCnrcY50VJz1T9KBqZw1PI9rdGbnZ/AtgwWEOW7uV/cNAqHIUCdcscyxdXCW49yjcjsNi9gqwASrkb6xYEdZCUoUUOxeFwYdLvH9jsHizkAJ/nLA7PlXpm+NM3jBIwXTS83WgFol8Fqyh3TU8updYlmbCu1iTN/Z8UlN6DdCuyVLWFAmhrektAy9Nq4upqappgbrB6fWxpOaFUKRVL1vfqPVWeeH0JP19veQPafLupEcYshoDH00+ffOT12HjH6pqkoG5Tky/d9sQrXsmcYQSu+45H9ZCqZDgdOCFuSSRmq17CniWyNXZ2dodZcXCiJoIOZzZ7kl4jgwlRL1h5bkgF1n98dBELeRNJ61EmayACHw+WarKJe8IFuCn8fpb1FhZmvFhcqiKne9nxYiWD+7embsBcCII/77igG446mBhRX6T4POLUW6GXjJgr7hjEgTdoHUdubq+LvRmF8cekw/wOA3b0sqWGp+OgfF1+Y7tMMQMuhhfXA4Q+6sAVO1utUuSOWLuKXYZNlmmWreOvA==
*/