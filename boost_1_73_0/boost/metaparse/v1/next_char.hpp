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
6cQ67MJG7Moe7MYB/CMz2Z1D2YPZ7MkxvJCT+WfexSs5i2P5EK/ik7yGn3Acv+G13F9ZrmNxXs/GHM9OnMA03sjhnMiJvIlVrEeT2Jg383lO5oe8hYPsE25lFu/mTE7jPE7nY5zBpbyHX3Amf+S9LF3UdsEynMWanM1WvJ+9OYeXci6ncB4X8UG+xPncyAX8gQ+xov3MQjbhIzyTiziYj3IsF3MmH+ejfIIv8Em+wiV8k88y
*/