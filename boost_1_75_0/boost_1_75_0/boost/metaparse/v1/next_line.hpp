#ifndef BOOST_METAPARSE_V1_NEXT_LINE_HPP
#define BOOST_METAPARSE_V1_NEXT_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_line.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_line :
        next_line_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_line.hpp
o1hVputTXYG/eApnsxGgbIdU3XlrMohciOWBPuXZRBeuuzaTb8gMPd8AQDgUDRd7hzAjxPnUH7wB31zMlGkkyj5rM2bKCCLI1sZNZ0SQrn6aHvTFCIyso55AQYkRWRJTCuJ4tk99H1FHA/5qxoogGmcBxIgFJrYAleZjfM7QCDwTk45wHDGIJDPeGygolbAy7F1TAM96GSF2LMMvYFhmGr2tEs3ivsq04A12wjTEl2Aqc5TC8QFEEPavkUpo9PTB8wzgHBk+fZ45fLobhU+jyYGdFd7NtyIVgmj1t7F/DZxzZmlD/s19SCjWxUuTCkqxs9lDjU+ZNigeca9n84dI2chsM9QQyu6WVxoMYPs7ePlMqIFiQbxPFxcy2yyI90PlqyhQM0+oHXRzgwXzvmckhrTW8tt81Z55m0RwbwZVOjr/y2OYlYRwshkAf0+5R7VG7tFuip2GXD9zSDWW1jHB3y8z4O9RLCRbWRgAPruzmq9L7URXeHMt5s8xMbGAB2lLHPyHIyh4OZeTmzWNSIrdvCqqsDw1iOjXBuNcmzjXFhIg34WdqzRGUDhEBZxHGwaNESHjQzFuKmjJdLvXL4Pwmilzvaq/mhG8JpynRv4AVHgQ6ZsrIP8RCuGxfXIgY4NIQuyxFpNqj679/KZ/Enx7GeYnlE0l+Hb23BcDsdB5NbYdP1TNP3Qf8ixIESX09koDvb1iBaG3Y+R/F93Z
*/