#ifndef BOOST_METAPARSE_V1_INT__HPP
#define BOOST_METAPARSE_V1_INT__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit_val.hpp>
#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/next_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef foldl1<digit_val, boost::mpl::int_<0>, impl::next_digit> int_;
    }
  }
}

#endif


/* int_.hpp
WjFJRsm95YoTu9rjXj1I0ZNxNF5trZ7vtqPadXSNUMzN14mZrHGp19Zb4/YBtEpS0PcsdJBUPNCHsyriVeoJMr+1P0/2mZomYQLzYCM5vNHsGRv9//gZ6SgEzSFE4DkYP678JSQQL1uTZ0VDEUV03TGxYUWnSo7zJ3jfdghCt94nR0YZE+JOITgjvkgbKgOqf5Aq/kfu2Gv40/j/ieF7zp++rETg5b1MHCXhPmkPQHwhSteNLroQ5oGiPzi6nMqDQh1QAo7PnYWV8mrF0WAksUD84FqzH4QxrTmSF5WbYz3u4+TKbXMLEHLg2t9hZ1z4FPDvfvbvZtfJk2NFy6/9yKqbaRvC5svnNuE1zkfzSY5LWnMzPtDhZbUnyUwoABOihOYE7hQBYh2rFNcP1jBd79tgWdgeZ0MAmeyL3M9cBIMAiEG18vMftbOi9jWCDkzRKvGhMUiYKtrqK6Pw5sSEQAyFHWsx69nPV2a+SJBQ0UGPae4U4f/Rlzk7W5x1Ks1RFLYga1GTK2/wDWSHHzNOhOMxtu1xVhlrgxs6esP49DaP3CCt3pybSFtdfA==
*/