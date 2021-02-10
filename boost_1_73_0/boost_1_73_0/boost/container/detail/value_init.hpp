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
/JcJTBqxpS6Ao+DNUXCAC/SWt0NjRK65oYLjD3tLo/v0BOLwdOE9HWPzCmttsF9uQA4tzg6VoFBSopiIsaYMtJCX2I210sY6Ti/iZJVGqfeTkEUzlByOCYrr0fqd54IWCj98B3Fqv8F+jQ3UYB89ic+HRslLgrf3u438YZHO19GKPnorhrVibgfCFLIUBcMe3lTv0WBTrdyIUX5jbteiaWDLaSbscFKv4VbRDq3HWjVIO6paEF4muRp0Q3PE5ZOUwJS5+5YLglJzT7OWU4Dxg6TXn6FT/T2Ujol+L4CP2GucFTVIfo1ItcYILgAZ+t5dyS1yi4TZrQ94YOjIgFJpBE0j5bu99TZV9CS10zd7lqLzmstH1jhSPQHipe8ycZj0PXeIoaQ0kSzRIJpHSLa8UC1qxb1+BRBVO0BW0WqxjGKcbReewnFJWzHcTq6mv6W0OtHxRkgcdasMnqUTjQrWWYHEcgkTeB4VuuQVw8I91B+uWDNYlTggqbEJ4kwDnKhrfsV7Hyqkf8uKf1BNSu0h+o4ZsRWNMCiTSKShTIXV0QPUNmTquWwOHXypjIdkGeTSuF57FD+S2nBWkuOHuiqJvXb4mE5SWEeDd08DLo/5kg5ipe+rZk8O29iUVNerm9vHXesE29wV230XlLPU
*/