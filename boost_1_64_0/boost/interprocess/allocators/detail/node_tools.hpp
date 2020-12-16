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
cJFPqd3f4McXYiwSGYXmZI56a8+BYGbhoy/W9qM35lItfkePKUP2qL7eQn8avDtan0qneFvPoYZe1m/p+Y0ScNtK4N0n8WUyjTFwzDnsy73GIZDu93jvRc2S5mNmfbOZ2dkcaI40J6MXzUWv3meeBOveMiOtOKuU5aJ3PQWfeC5gYTOtzehIx0l03KAaRbECdNujhj5tP8N+e9V+HUV3C0j3nH2NzE4BJ9oR4RONnQ74jyPRnCY6q2Gg+8C2l52fnd+cgu7juDQN3Nb4sJko3xPg7++72fDQC/gCfwXjVoGLesxyZ6rEMG8UrONdEk4H2JXXvJveXS/Zr+HbfjNYx0DwWBY4obCwKh9YQmkGhhyojFQmKzOUucpOkhdnlG9goXnI0VUbqE+pvdXncC6m0IM2q9kgx1zWZH4tipWow0dbwOcHamO0V7XXtQ3aFhDaOe0a+7iAHg0rNOgrHfR+uAFj9Yn6arjGPv0kY/8zVakgaQ6J7tmasX/OeIG+s5yszXb26gWU8r8aD4wqKHSe2YKxf4bqPspcFKjZB1CgvjF/gClWsKqibDRm7PvBgIdb86ifG+Fyx9mL10GFJeH6kp3K2Pew+9vPkgr5C3rMPvuk/Y39A7UukVqnOg2odr2dDGcofeEd8iLZzhG6w1XnR6ek+xgIz3NbuE+DKAZRC+e674KA9tEzLrnfunFUwxqe4TVmb3Xz+npTwlo6/OJjKvV5MGGUH+9XopukBtyiu/8qjO8d/31/u3/EPwW6KBCKDpUNpYRs8lRtcFvG4vzOhe99iCJ2NHQ6T3/Opt/wKCiWEquKKrvxCbG9+ALu4EyUx3U4hAdhfX8VH4jxcL46UqrURGqFizlKeh3Pf6W0Xdoj5Ui3SYAUIV2QInsgwOZyaeuC0wX9uDdq0iBW1TA3yx2NYzzhEUd6fWhLUBc+C30RuonHUZgIVlg7bCdOEGvKr6qv46e8r24P5/9gE2Ee4WhPaF2CjMxoWEQOyOw7tNci9OxEvVfgCU3W34Kvb9C3sPeijDKsAIsu3hpEvwiW+aFxwDhjXEMtvWuk0tXbmf3RBv5kToNhfml+jbITwW6rYdW1dOsl9tosawns4xPrU+ukVZ76quAbtbX7ss+GoTB/jJN12b4FAoh1ijud0c6H4HrMwOFfCXq/h/sZ71YKdtYTeKBz4YxrUBuOhmeWfeWDaNoyp8O9iSQGZzOb12DwkSSuavkKuyl8D2lb5iVHctTtRlPzD7+mi9WdStAf/TvTGmZloTGMhTtMslKchP/larBjV3nCjbw+1lyMlDR44lBpsXRVqqZsVHaTeDlLX08EG9VhR0ZrpWFuilYPD7irlqFNJ3HX2fiLvRAeUIXd/gf/cv/OgdL8tuz/LnSyCMHlMzrCTxeIu0GcK+Gel6VGcMeDygh1Dvvb0XZTPw326FCjCcpZlK3y7T8Gr0YE37mUWAwct1Uuq1aGXbZSB6uT1eXgnctUZIk+vlRbiwN+ifpbjcpb0bDMXma61cMaYo1DA6gfeNG77Bb40Pwy7oVtyOOSeIs1vBv9sbnyjbpb26AXtG5Z9ezteAPHnOZou6956X43evFWtJJf/Bh2Tig0OPReeI+IEUJ/HsOlpfJO+QdcsBZoayXUumhp3UgzHUa9aqVXecSBWmgsZb2tMtYaG0Fh2wwNljfVzEGhT7JCzNvMsE7hxAYIp7g/Bp1mj98J/SXvc66KLaX2Um/21ifwkdqywZ6KhJErdLJhSrraV62up1L1JsMtBhkzqGnxZg3zO/uQ09CdR/047g7yNvofkaTM5vfu9w/5R/3X6cRvkwr6OcB2EUILHnFidTHEbpekeugFu/is69J0+SM+qzY=
*/