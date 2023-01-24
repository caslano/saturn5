#ifndef BOOST_METAPARSE_V1_FAIL_HPP
#define BOOST_METAPARSE_V1_FAIL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/reject.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg>
      struct fail
      {
        typedef fail type;
        
        template <class S, class Pos>
        struct apply : reject<Msg, Pos> {};
      };
    }
  }
}

#endif


/* fail.hpp
vuZpUBhhD54Vnf0oReyxj236RL8o4HXda6Gv2iq/ix/YFI6PM/hmKAyOBQBGIxR3WpuDYrYGxesgidrtx6rj18HWJGSBL5j2VRQcZ+ngaNHB7Oexxr6gUPsBA2zSbzbYzQTM6EPpGwfsUb8Rag4aIQaxnVrfoyfjVG2FyrAyked4xl4f0I5HuOEjhX1eP7CJQLIkxWhcDVvt0WupkPN0HprPPqQjBlT6L3NL4Dxi2OBm+7vKvfm4FaTWCe5Bm+9zuKUrK6Kr5uxjvAQkzVIuaR68Bl2DMEkMjsTd8u0NqkxZc4PeFzhdDYJMAQuh5Jng3AAY6QlWKhvbiWX9AKEi1z/HiUyWCSadRQFs+zGGHuRHJgiMg/DuEM8hI03JI81grGV8gnvQ+CQmXoTO0cwDwREJCZGOFILKRspPII3JHUMQ15vyRk/w3vxPnB1NFufYmc1RkoPHFHvJdQrNiHM0xlMoes7o/8wC/6dFxfd0XtyWgSAaqzd9CVgdPGYOzJbGJpfstM9fgus7CwRjdHjukOtO0jsxOXIkz4NFG0UaTpvtrvHs/8RluZzIvm4ihUnCKIOOJEXy1CAm97pruWZ+qZYW112kdcFAY2ggfwHupjJ1iNFNpn+yFjkU30qjIa+anSnZCxlfgOqMMJ+zh0xt6YBBb+UQM88DWSCfwtMId56+TkWj0ut0MrUAZ9CsgRN9yV9SQ6PgBSbVqVyz
*/