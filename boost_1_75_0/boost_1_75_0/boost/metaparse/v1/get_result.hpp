#ifndef BOOST_METAPARSE_V1_GET_RESULT_HPP
#define BOOST_METAPARSE_V1_GET_RESULT_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_result_impl;

      template <class T>
      struct get_result :
        get_result_impl<typename T::type::tag>::template apply<typename T::type>
      {};
    }
  }
}

#endif


/* get_result.hpp
j1ru6G66w1G8iIJ66pByvqcqayBOzYmkuPt8Hrybz3aR3dcahb7ipVDTm9+GNnsHbanwGjztUo9g7tLwSIWXOQ1NSlxayuXcZO3xL47rpVDiy+cJ+lq0i6qOAxssaEtXo9N5LRETYjTTy0aIYi1e1dcmrPtfcTnyB0Z8jZAHxGiucCMg3jCpuNaQA635349KwT4FP/76VvbxNNaFbGh/0ddAEeg4aNEcGpjjF3cU5Zb8qEznXg4So3rYI5ZkwbNpgZxlVe5SnupWalmOrX5TRneFW/23V81pc+mMUB9KAbtsZ+GAjblJ9f5iNoTcFMj7RXaLb6SmwiMv+ymxe/BB1qjAA2yZgWyZAljYGeYRdMOiEMP3JhIGDIcor5dNdQ1hCIpehfUSxNJ5sAdo9x8ETf5tPIFj9KrNVAqnK2VwtBsF2172+EQYCTUIqwbrvx+g1Ynmn3lbEu2hWTyL2028XZXHy04sxEmnXFB3KY8PXOZRY18CEEug9mKKO/EG3aUh8YGVXoTIROjND/+CaBI5c82VM7JFmKCj5AkbljHIZnR2UiEzezBzriU/d7IYoJFbGH15VX+bR/XNlZEqEx7mlawbx9to/eXy9ZfL1t+4vwpwMEfJRbi3dMO6DYjqhTkkdD+H+OxoYUTZaGaz5MzmGjP75ishM7ukyTqzV72CM4uNxrSVuWF5v5GYESPLKJGhniBWRzRt6eDK5Y1f
*/