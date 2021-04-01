/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP
#define BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
namespace detail {

class null_disposer
{
   public:
   template <class Pointer>
   void operator()(Pointer)
   {}
};

template<class NodeAlgorithms>
class init_disposer
{
   typedef typename NodeAlgorithms::node_ptr node_ptr;

   public:
   BOOST_INTRUSIVE_FORCEINLINE void operator()(const node_ptr & p)
   {  NodeAlgorithms::init(p);   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP

/* simple_disposers.hpp
ALoLSLuxtsykgGDlW/wehVpIyYrVDkZftHPRNLjxV8YlWIFr/KB9tk/zJxgAvvD0GUvstNyd/K0z0gEsgHdYc+tks7b5ssanPRirk9c1DbqVWXwDMpRLhhyPoZZXVu7phloYeosUWlNs2sRvAqwMGWPnbK62Omj3kcuEod3fWLXxhXq1ddmp6DQL9frtop7HgqV2R/tqGBeAGtQjMrm4nmlfy49w0rS31hGSLecmU/yyt9NXtGE7fQ3xKc9L2EO6php9hu1TyDxSbIoLMqM/4g9OWSOJfS7gIpCwxi/CecIadvJWxLpQvehJffrmOAGZ9NvJL+iYvaf4Du5FIytLpS3HVOd0WOf/Kegmgc9/pHEbgznKgXVjVJa0pBE7zMEhkl3kyvCzJWQZ9m7GRmmVDpy4UJAELBa3TqH6Bz7a9WdsVmwMxvSsqWupVUWNZa5K8sUgdZTJuKfbwOGBuDNK3SrS/ii6AnOCEB4B8hKNF+Wh0IXZA6DtfYwU6lAauOeqqFZEttXE36Wz8dxQ2jrDsK+CDV/g0eZy5dz4EnAIWUpwGlL6epm6K7eF/w==
*/