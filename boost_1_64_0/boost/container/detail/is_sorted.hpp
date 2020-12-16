//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2016-2016. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_SORTED_HPP
#define BOOST_CONTAINER_DETAIL_IS_SORTED_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace container {
namespace dtl {

template <class ForwardIterator, class Pred>
bool is_sorted (ForwardIterator first, ForwardIterator last, Pred pred)
{
   if(first != last){
      ForwardIterator next = first;
      while (++next != last){
         if(pred(*next, *first))
            return false;
         ++first;
      }
   }
   return true;
}

template <class ForwardIterator, class Pred>
bool is_sorted_and_unique (ForwardIterator first, ForwardIterator last, Pred pred)
{
   if(first != last){
      ForwardIterator next = first;
      while (++next != last){
         if(!pred(*first, *next))
            return false;
         ++first;
      }
   }
   return true;
}

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_SORTED_HPP

/* is_sorted.hpp
swn/5+NO4GLO3ziA/1RquqeaalQYhEESQlbLOJbcuXPnDmFcyQo5N8cy7hDGPa41/EOuhBDrGNeKHO1fS6wj1xqE/1P5tM98X3/Z9bK89/l+n+f7/O7fjF/ifGGRZHzNWpzM8oPFkvEaMtp2uwTTkSn4eh7VzIcZyPyYTU783RpmEuxSjUwdzEwm5/27m/IAJt9qudYX+za9AAsi4/Xl9ckvBwsn4zX4Phq7DhZF5s7sROJvd2DxZC7Mtky7lgXTCXGpi+84wAxCXG7/9xGwFKGG9XPGzIZlkjkx+xBd/RdYLhlf67nb3R7BpG2WtT8PXdMZpiLjuai0vTJgQWS8Dxfm2f2E+/AIMvU3s7IaJ72cMVsHSyDDtVuBLR6Q3AimI3NmcaudU6rA9GQOzEzbDk2C7SYrzcY0nKxsgiUL800MSTLCUsgUbMzrU11vw0xkrszW7pOdg+WyPK3JzG2vnoWZBbPJfdAYJttuaZ3vn+8MU5LJmO27WLosTE3mwyyrUqcLRaaVwsjwOXgbq/qS3bFfc/CMLJ5M9+15ZGmrQKnZpNvesCBD8fGs0A5+vOAK05D5MfsY69IeFkXmwOyA7+YPsFhhzC8Ldv0KSyBTMDuStjYGphfinJJjFDAjWW1mOXXeOMPyyKryXH5ymQRT7aBtkNnJ9XFHYeFkPG6r87xfYfFk9Zi5N6n5HpZGFsxs3/FzZ2HSztJSp0IrWutR/f44DYsi43FVXperADOQuTAz6h/HwFLInJhlzOoYAMsgc2VW3tBkNSybjK9nzOVJ1WF5QtyKpQ+dYbJddHxh1i3xUADMnwzP1gqs9dFTV2FqMj6m7ZSG1WEaMjkz3YpPrWARZM7MHk2wKguLInNk1jv7QiQsloyv2Y+1LrjBEshsWZ4tZ8dNgumEMaUzq2vC9GQOzEYeXNQDZiSTMWt+7epgvO9II8P3V2ytakrH7NxmwsxkVZnVX6N/B1PvpmsiZknPfDfAwgQb52J1EBZF5s8seZLXJFgiWUVm45OzZsHSyDyZ+dwceQCWTVaDmePnpQkw5Z7SUhVm7xZV0cPCyBTMSvnmlIJFklViFrHychZMR1aB2dNPWddgKULcO49+qbBcsjLMjhr2nofJfit+zlc0X7f7+XiPICfDMdKObN9tp/awMDL0VkZmer75JSyCTM7sZL+1+TAtmQOzhnY2EixeGHPu4CpzYToyd2YH7j2KgRnIvJmdCvpdCUtn9RWa/uknmInMkcW9z7pSBpZN5sJsb9eeT2F5ZG7Mpi4OfQeT7bW0in5tDsJUZApmtxqtqQgLEayG5jdHWDiZC4+TDi6CRZLVYlb92t8ZsEQyZ2Zrts8/DzOQ8fVcuXfhaVgaGe9fVkz9TFimkMveGod/K7IoKZflYm8VLR0s3TEfpjLSNTSzww077oOFCfa3YcMBnMO1ZHj/50Dn8K3lFs/CeyADGXJxtBog3RtxqjsshcyZmdRVkQrLICvDbOThsS9guWRKZp6TmrjCZPvoeM2sdR357zAVGZ/Po8baLFgQmRuzjf+kfYKFkcmYPbk5fQUsgkzBrGx6mTowLZkHs+e7B9WHJZB5MjN0WaqBGYQxXzm1PQJLE+I2BFZeAcsWareTK1bBzGS8D5UuTzTDZPtpH2NWJWNYFExJxuN6RGWNgqnJVMwGVTunhoWTyZl9Xt4hCRYl2MghpYNh8WRufK0r32sDSxQsuf1LT5hRsH2jdxbHZQhWdcOf/4VlC/ZqibI4ziyYXpP4C0z+H8u1vris4huYmkzJ7OfQMdVgYWS+zK41nZIOiyLDdZ2TVYw0Jir2OCyRDMfIAuv+fOUjmJ7Mlpm7eYQRZiBzZGPO/32fJyw=
*/