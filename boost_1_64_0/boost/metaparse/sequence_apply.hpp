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
yeFlylYnXPHjaeuc7EhMICuSvfk+U1YtdVrrGPqIznn5eM2DIcyEMIkz+6Bm0ZBJp9LZD1+6gYPbQl18oOxHeNZMM2DBOnJ9DcUg2/dkHFEi96tHMiVt/KJjr4fCb0PmYc0f7Z7THx+qGP09BKMDtJDrOWKy5+7wG+1rF/juClRp9zMUgOCfw05326tPvE9n4wxE/adUwXr9JI7YKcAhRwLt9sJq6TRfM4xJlcgsMitWK6rxhbP2TqwT+WKdKUI1Is6JB6NC/pxQT5tkyy6NOsIAVRAyedBM+ujDKShDjXy14CAJFEN0Y8i+xlUqrwfb5wBTbBVNmkqWK1vy/9SDge97Fq1UbHwGmzcZdRW+GZhfcebPp054qgjjatdJ8nViP9OYmgRQKbQCl1LBGBFA/yzSyWWuWIPGPNt3RcOTuHbRnAzymERMupJwGtTKNMOQrCDOc66AIXgSbsNYpSmX+P9Q/Hw0bNTwYOEdfdiRjOwhiBXaCX5vbk4cnneoNGbdT6mQ/v2Okx/cdLzPLNWuKjs2MkqJr5ovv/mP4/CVPTnIUMnCK6wODXU35g==
*/