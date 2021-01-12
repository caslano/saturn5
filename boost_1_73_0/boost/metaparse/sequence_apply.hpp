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
0nDFDrvuL2MX+c3rs6aucRPy5b++4clTc7ILb1uc6C+upPlPyhkfbR+3WmJqlYzd51ZqJ22hHu+7oW1JTk5mXp1gZVqgz4x7Q7m2iG2DxsfKtV+HvHLVheDe1SXe3bLIv55rhb7ZBrFyMJKehYn0hB6URhXoz6PrbqznVakF1+O9ScPLk4aXJA0vSk20neiYGm+H0ErRxcYdmRjXPD6uamJcSnzc/nnjWraPj9vWOW9cu/i4
*/