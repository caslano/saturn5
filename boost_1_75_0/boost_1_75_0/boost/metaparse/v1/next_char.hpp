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
giaHdcpVdhPMSFcT0ZH2m9K+9osxeq+8g9p/hoA8ozF7ppzbWMeZ9wYYr3l3G7qXWz2KQ/ajB7BZKRMo1Aqzfoh56FL50H2lCDhhPmrJ2ooHTaOGNQrVGhy4XTBwyWzgpp+FA/eRvd2BK7s6fOAmXNPhwGHjLhtiN6fZ06SbBi65fbMJKjvZbxsDJ0BYaPDGfaAoYXSWfpeZztqQJYfR2aLBZ0Rne4jOHngghM5gLJHIuvjUKu2arjhcZe0P18yrwofr8qtPT2cnr/zf6Wzo6vbobOD7hu8T4j2xOuohtBX/ihWe5pFrr6T9eLDIIVAJfgHtWUGxfWDMXaq2YAYair+mYKFfPsWAAIy+QFn8Kyj+BNrB3TUQK4d/z10PLnLFn8hN1d5g7CW/Ew6n9JKXDraUaZknxiRVapCpXCHC2ZoKVroJHE/1rombhX9uhgRTLTyQ7Pov+hw32NTn10P6/Mz9Rp8TtUNb0Je7lN73NMXE4Zxt1355EODd9LzrMR0ZkO9pNN6t1fV5p0Ch8g/wqAt4U/hg9D4UMhiFV1oGI++KDgdjvY0bL7OmBmJoRNQZsF3mEcgg2QgAdzc7xhPIZSOUn+gNpCagTJPog0j0o56gJ0HrTZ1acNpBamIN+Ri/SCPlfzh0GGC0fmALyDOpBRINb+H9FxOvbv3wMvTz6QjpxLq6jL2yLDIvQd6IAGQBdH6OX6MoaQs/hXVE
*/