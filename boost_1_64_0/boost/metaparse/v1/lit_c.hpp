#ifndef BOOST_METAPARSE_V1_LIT_C_HPP
#define BOOST_METAPARSE_V1_LIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/literal_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>
#include <boost/metaparse/v1/impl/is_char_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C>
      struct lit_c :
        accept_when<
          change_error_message<one_char, error::literal_expected<C> >,
          impl::is_char_c<C>,
          error::literal_expected<C>
        >
      {};
    }
  }
}

#endif


/* lit_c.hpp
5upNw3Z7f5jOMATfrCDjPQTYZSWRHWzUCFtKJgBJMaVag17I9U/hkEoqfqfrr9T4KZ9Dze2JrMqx42QJI4MzJos5waG5srD+UytWHEmOZsA/eU4WOhsJHa54Yc+II6yQcDABrfePtMQ848A+/3DPpTTzUgM4g+g0nDv5jx14wWIgoKLukmkfbNgl2oao4G5vNkmwFYu3B9PHXU7X0KV2mUk0oJVH5v53FYfbSvo7PKSIjFafr5puM5LcU1R0B8RrB63iyWBZb84k8tKBcPgG6CfXDsPA/Otl54ydEKxBgJTRUoenRlXkA7Nu05jx3ue7SiNXMTHgbPPw2o9WYGvtE+o3+bVBd797EwQhMPm2u3Nm7xrTsHDQMolHjmZqqVxhZXwHKb5RjoVnQfrdqPayxrKLJAlq85OBWty2m/78F/XtrUzgqeF4AHcn2jWgpZWEgyLZEFn31ZZZt21nxBr7KuzzzdbpHxJHY8ntbcAXXyizY8ns7VBT7LJ7FiarA8gwlEQG6XobTPZByJRdttkfDIVjjtAlnZ3i946LfW1Jcw3LsJqiXHrWe1Pzkw==
*/