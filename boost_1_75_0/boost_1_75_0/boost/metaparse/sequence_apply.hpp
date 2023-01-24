#ifndef BOOST_METAPARSE_SEQUENCE_APPLY_HPP
#define BOOST_METAPARSE_SEQUENCE_APPLY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/sequence_apply.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
#ifdef BOOST_METAPARSE_USING
#  error BOOST_METAPARSE_USING already defined
#endif
#define BOOST_METAPARSE_USING(z, n, unused) \
    using BOOST_PP_CAT(v1::sequence_apply, n);

    BOOST_PP_REPEAT_FROM_TO(
      1,
      BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
      BOOST_METAPARSE_USING,
      ~
    )

#undef BOOST_METAPARSE_USING
  }
}

#endif


/* sequence_apply.hpp
AStQwBNzWKU9NXYtmUsfoRS5DCneGmI5sFIFW/Axbcuvkljra/W1/hBydLAS0ZOgPaDCYEOw+DUJgpMg8wxN863gsxnTYPeHBkliXe/mk6twmtX4whbQRFj3vbX+cCeAAGat8Nb5w96WWIKtITSRaNmlunr/YJOisCEFVNP+2wzpOU0Wf+SBn9n82glr6dAGsZYeuIsGfh+//nIvMoCGXzT7E7tU3/OLE6oJs0XeH9oNMEj3x4cOW4J+aGw6m4tnP2YEX2E3PnkUfBY8sY1q3NN5gOji5zv/0NREPhYbkiWaXTN5OoGUVnBd2vje9Y9Gfc+if++8U33v5NQ//L0Hy6K+N6RM+96G20/xvcgf/96bi6O+d8ti7XvXnOp7/dv8nht8dZhOG/fNxE4Sm8Cshs6+oY7v2K9gH4/8iS8SV87+Vqo+gcw/cZsmUlrSdB/X+NLlrRlyD6ZLpDvXYV4g9DQs5vk84OxW5lAihAgByc1hOfGo12cLsA3AnorE+VnV9Yk7T6iEf+CX95d8mh9T0VWyFjWMhmwOMRUgpsARJu5S9ixrdcmH0MYawNeANg6kNiZAG8Nd2V/deWtjyXmRvcEhuQhjASxnW3saLWe1kJI0IynZMzQ2fwLZdDbcERVbBsBJXy7nsWUFUwynhEaYkF54Tsh60FMElRWcHxooGU4PDRBLmqXrnFvQSOJGy0jmnaRZzjDIYeIRjg1x
*/