//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_NODE_TOOLS_HPP
#define BOOST_INTERPROCESS_DETAIL_NODE_TOOLS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/slist.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {


template<class VoidPointer>
struct node_slist
{
   //This hook will be used to chain the individual nodes
    typedef typename bi::make_slist_base_hook
      <bi::void_pointer<VoidPointer>, bi::link_mode<bi::normal_link> >::type slist_hook_t;

   //A node object will hold node_t when it's not allocated
   struct node_t
      :  public slist_hook_t
   {};

   typedef typename bi::make_slist
      <node_t, bi::linear<true>, bi::base_hook<slist_hook_t> >::type node_slist_t;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_NODE_TOOLS_HPP

/* node_tools.hpp
9cp4UD47/6Y4Ob2Hc3PxLnXSfGnNc5PMeVFTwtvGu3RgyxYf0bzE57kLTVVBGje0oprxpXBiGcetoAvYENwNuJFUms2kE4s7oUdHUFE3oYry0hHUonGMqSWVUkgnuOWOc+VE2X152Tsigy0ldQpX9WfSJRSGKXGD64BR3jvJVS0WpHa9f7a0S/EeoPM17a3K3arXh5nFb47zMne7hbc87lUr7sY6ZqKDl6XD3dGhZmXAu4n0VtQO709xRzre9h3cveD9p+S53a5bVhQPrgnp2DkpNL5HOLo4Lgcdrdma4ouPG/xE+vNt21wLpINdprEj3dK8ZR3zoMwfEXPzbta/NHesWX/m+ArXS6OCf1rSy7muybhbUg5lsMXmPY/Z7f5jaPdZDpjJpXIAu61XP9c193O61UKyd7O420pdnv0LUEsDBAoAAAAIAC1nSlI9wdhhJAgAABEWAAAyAAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvdm1zL3Bjc2lfcHJvZHVjdF9nbnZfY3VybC5jb21VVAUAAbZIJGCtWHtzm0gS/38/RZtyleQyIrbjy268qysTCdtkJaEF5E3W5aOQNJKIEbADOPG3v+4ZXnrY8V5OZSPE9OM3/R4OD+AqCNkFjHuO6Y1tqz/pud716Nbr
*/