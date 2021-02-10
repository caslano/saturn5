#ifndef BOOST_METAPARSE_V1_NEXT_CHAR_HPP
#define BOOST_METAPARSE_V1_NEXT_CHAR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_char.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_char :
        next_char_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_char.hpp
oqf4FQNRmq6TWs2+EP2b2IRhFCXhXRQ/PtwnSQy1c+ct56uXLC92h+1qn73u8uJ5f8jeCr4O443XmVN9ORmPdzkiNdUASjoJsnJI4GqEyzNCLS28I2pY2Nq4BRP9yPoIJDJUGuV9Qx/4qxV8hvjtL74BUEsDBAoAAAAIAC1nSlI24flKOAEAAAMCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI3VVQFAAG2SCRgXZHBboMwDIbvkXgHq1OPLNouk6oIbWqZxqkMaKvtloIRaEBQkrHx9jOBtVJzie38v/0lERaNzaXBgIm6KxVtXzj+KF2YgL1mMYtf0iNLwixhvl/URp4b9LE3AxP8KhR89t5BinpA7Zu6QCY09s1Ip4W0MmCtWhbJ54rgi4KM26bGzi7G3CUkMK5dwErbk/o/A9HJFh0f3FCB4PMZiFy1rewKZ95wvn7bp1kUb9bkivdJxntpK24VL+sG+cPj020rwS8dKFyIiPSIui5HmK4AsrSowVYI0ztCJQ2cETtYmUrZFROD01KDXiurctUE7JCGCchOdWOrvo03PXAKhPiMv7LtG7ynqVQ97Ty2Pe1gopwjq+Z94nW2o8eyjziEyGNp9BkC3cFzXzVH74co8wj9OlrwCw+/
*/