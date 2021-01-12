#ifndef BOOST_METAPARSE_V1_IS_ERROR_HPP
#define BOOST_METAPARSE_V1_IS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_tag.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T = boost::mpl::na>
      struct is_error :
        boost::is_same<
          fail_tag,
          typename boost::mpl::tag<typename T::type>::type
        >
      {};

      template <>
      struct is_error<boost::mpl::na>
      {
        typedef is_error type;

        template <class T = boost::mpl::na>
        struct apply : is_error<T> {};
      };
    }
  }
}

#endif


/* is_error.hpp
EezJY3gBGzCV57EP/8S+HMf+nMABvJlDOIdDmXgOYPA9xIjk5wAG19ZV4njW4g3MpnUhaLfgXJ5LRXK7jdjX+3kZT+YVbMOR7MZRvJ5jOZlXcSqv5gxew/t5HR/i9VzI8dzGWSLvnJmdg+VWTphG0K+Ta/o5hU14J8/lXezOu9mb0ziAMzieM3kL7+UdvI8PcC4X8RE+w0V8lo/xCz7BH/gkiyrPMyzOJcwvb3B+yQ57KO8Z
*/