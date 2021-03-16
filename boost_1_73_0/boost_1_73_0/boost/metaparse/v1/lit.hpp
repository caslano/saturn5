#ifndef BOOST_METAPARSE_V1_LIT_HPP
#define BOOST_METAPARSE_V1_LIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct lit : lit_c<C::type::value> {};
    }
  }
}

#endif


/* lit.hpp
SdsXZZY/riQbnKnQvsjYVJTyV8mZ4MGXhVgJCTc8h4IS7nNXxuYYnNB2wFgBTlkAVY/bXMNW1Rd+i6maUq8WviPfbidPZfBAcBQKo0juhblDrn3Dw+7SIIrs8AAEvw4Xv8uXFarnxp4gB4Z2/mnJWFpk8w47S+xTKszJ84fBYS8Nw6BQCvOgktgnkGXHY8TaBsOu6rlepzrWG8KFERgywxSmWObF/HAwCz8bJyhoKMrs0LQkBM8uL/zFw7n5xe4=
*/