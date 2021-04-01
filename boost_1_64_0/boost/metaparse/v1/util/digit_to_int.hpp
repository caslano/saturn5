#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/digit_to_int_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class D = boost::mpl::na>
        struct digit_to_int : digit_to_int_c<D::type::value> {};

        template <>
        struct digit_to_int<boost::mpl::na>
        {
          typedef digit_to_int type;
          
          template <class D = boost::mpl::na>
          struct apply : digit_to_int<D> {};
        };
      }
    }
  }
}

#endif


/* digit_to_int.hpp
pJBOw9uIyplj779SDrk5OV/kmGoBiCZAIC2ZBXq2TKuC+18foGkQssa06rwxBiFcxD30a9NtWBEw1LFfD7vYoW1QwUwXCtt2oNQKB3wVQ7RBPZhKOfuKUg6mwDCFSXkT0bRxLdZU7GJWw05slDnRuIWQCRTfuvW7CME+dgz2rLThDc8z9hswujZA2rJIrGyCnrbeYonSQCFtgMpaxCFyBctJYEjjh2V5DrOeYOmeLuOAjymHZrx73OTrSVNaRe/u+tSunsW6LnLqA0df34Xril3sb57KP8AtESBxzzfiYpwahjccOD9uiVt2FLJ5YTceyWYCgpTwjFxVSY5Q7KluwtNu3DrDmBPOL9yY+1fVIEmyWQwtmom3S3xA3c7JBsog2ezW5ZeoMT/QYtlNlUik3DY0ljeSphCo1xJvRSkg1baoGCEy9MtdrYiFvqSHRY/rnfbGQwlJupn96yUOBklhK+hofxRJvJyhxoJjhslswl4Oj0s48JXd1rweIOiVz1V2xzoWIMYWUI+1blL1kCuJ695bSUA8YWFPZGhPp3k2AKNm08npRH5M+S1dYQ==
*/