#ifndef BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP
#define BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T, class NotErrorCase>
      struct unless_error :
        boost::mpl::eval_if<typename is_error<T>::type, T, NotErrorCase>
      {};
    }
  }
}

#endif


/* unless_error.hpp
SY01/K3s/Xz5+UQ9XIc8kspEyp/Dbgx0n0jUG3XII6lxSCV6vocWX/YEUTF1ySOpiwwvjayJt1xMVI+65JHUeMOf8jfb7hxG1My65JHUBMMzXPjdvm+JWl2XPJKaiJQ/tvlwrN0j8KltdckjqUlItfF8tW8awdZSfqpLHklNNryNyhi8fhlRneqRR1JTDH/Kj7bsFyIqsx55JDUVqRTP935KTTaev7weeSQ1zfD28L+3tm1B1BP1yCOp6YaXxrQ=
*/