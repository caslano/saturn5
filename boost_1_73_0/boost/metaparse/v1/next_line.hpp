#ifndef BOOST_METAPARSE_V1_NEXT_LINE_HPP
#define BOOST_METAPARSE_V1_NEXT_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_line.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_line :
        next_line_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_line.hpp
eDZbsJ/SBnt4NluHIurDjjyEZ7ESz2YVdmJtnsPWPJdteR67sAcv4gUcxhz/XcE/8c/8M6/ilXvRV9uLJuh30JPv61Xrm1U3rak8+e3nU7sOKfy9+X/192b7Ktc1WtHENLFYjDzw3//b8JP1rAPMEOFvuPeIhWKleS7LVez599o9/1Y7Qvzab7PJv8s2FeFvsJkiR+z5d9fC31wLX/+913/y/v/cZ6/mn/3/a+f+JwfH0W2C
*/