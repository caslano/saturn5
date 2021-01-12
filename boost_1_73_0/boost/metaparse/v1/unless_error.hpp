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
HncM7VNU5Y2syz+wMW9iC97MQ7mAx/FWnszbOJy3czTv4O94J2fzLs7jIt7Gu/kA7+GjvI/LeD9f5wNczwf5FR/ij3yEBeeDR7knH2ddLua+XMKWfIrd+DSP41IO5DNM47Mcw+d4Op/n2XyRl/OPvI4v8T4u4yN8mU9xOZfxFf6Vr3I1X+PH/Au/5EpWsp++zmp8g3vzTTbmKjbn39iBb7EzV7M732Fvvsccvs+J/JCTubao
*/