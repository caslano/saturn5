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
ogbJCjhlKkv3a2Evpt90FN0HKAlj34EDopQEHRXKVSXbAQ1OZ2FAh/i1/7KfXes4I0lHNy9Qbo0UrkfSh/Py0Pk9esnbkjM0SAM/GpaM05OGetnH6e4tCuuR2Dq7gwq1tpIK82PCs5St6BxzisFniJNJRMFnp6i0k/o7TjK/c2IdeyE4Ojca9jkG5798LKVRPExYVea217nns79mh58fP/ANJkZeRyNzNHilquMfM7ja/KsREZ6s+tgH4IryPC73SnhaoRnOLKxErkrF3WiDq7LOIvx+leQtRTNpD6XmhltdYzh1i/eWGWmddpyjy5twDhXkcHXtrG1B1Ium+1HR1qMsftvpArdcwFDcsKNUF8HBjfnlBoJT9Sm8wS/T/Ql8zTtxokjZlSAU8Z8Oysm2jNecHinlp+Q6eOCO3rDcMUzFFh0G18of+M2Di6l4Tv/L1XZ/7A48jw5OIuE2H4elmhgc3Ioc4XnAzyPV5BZsqyL/H+QCmJDVRaFmuyB+ZZmQiAsTepGzVbGa7jSv3qL1B+sMJ98NaOCNuuRcggiuczlWCTZc4hKphI7MBA==
*/