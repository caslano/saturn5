#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of1 = repeated1<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of1.hpp
R//30/7jzcPvfuDTf2/uvALQ5e9nlQj3XLnKVPo6KiyWrU2p1ejWFo5tS2Nr3To4dIfBoTuQ478y0RpM1FTwKZkS5c3g6bGCEzWj0R0e3RVHg8WJ6rIyYwtmHKu8VHNdbAZvFX6xBBpti6PBHGJZCGpGNyFDr5odvslQbDary9YgRFCgGDWDl42fJkTNhdFgauGTpegmFD9cmUML5hA/9YSawVuFz72h0aY4GswhfhpDNffF5nXxdGBq8bAxakaEQ7XjqtnimzTFZnRvV8HRrsLUh0cPxdHgvaN5X1m2Hixbh4m+w0zfYarvMNd3mOw7zPYdpvsO8323ifAdmHGPCb/HhN9jwu8x4feY8HtM+D0m/B4Tfr+J8AcwY4cJ32HCd5jwHSZ8hwnfYcJ3mPAdJnyHCd9hwneY8N0mwvcukF63ATP+gBl/wIw/YMYfMOMPxPhrb4s8tvTJGtiO/IoK0/vYXhrvX/n6Kv3q2uur6bfZXs2/lvf/UEsDBAoAAAAIAC1nSlJrX1GEiAIAAHsFAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMxVVQFAAG2SCRgnVRhT9swEP1uqf/hVIS0SUvTpBRoF6Kh0WmdBnS0wPYxxBcS4caR4zT03+/sNKVD
*/