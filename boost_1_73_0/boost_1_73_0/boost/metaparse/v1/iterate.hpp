#ifndef BOOST_METAPARSE_V1_ITERATE_HPP
#define BOOST_METAPARSE_V1_ITERATE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/iterate_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class N>
      struct iterate : iterate_c<P, N::type::value> {};
    }
  }
}

#endif


/* iterate.hpp
rbHi5Qt50TYnlmerWL6pyvOl/ANQSwMECgAAAAgALWdKUmAJP6tdAQAAQQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjZVVAUAAbZIJGBVkstugzAQRfeW+IdRqixbq110EVmoVUJVVqFAErU7BwZh1dgIO0nz950YlLTi5de994yN8Oh8JR3GTCjTWPp84/lkh9rF7K3MWJIVW5YnZR5euyTNV2sm+G2R4KPuDgocjjjcO1UjEwP2+kyztfQyZr5VDuhulEaorPFovCPpOCtcUFZdHf9P+TMu+ORIQUutSD8FVaFzNYlZ4/urNGYgjOww1AK1PRltZQ0n5VvoDtqrnnguxgodSA/WVAjKQCgYBB+1ICrbddLUwXzB+fx9XZRptpiTa7bOS77XUtPD9SFc/PHpmRiuKmpOlES/xUE1Z7iUDrLxOIBvES7nAK10sEc0MHOt9TMmjmEtGfSD9bayOmabIslBGmvOnT24iGWvRQGE9YI/sqNyHiiVRneriC13K5jIxs6EF4VTjVj5mSWQRqxIvxIg5Cjs/tj62KRlROC3YMGvNPz21/wCUEsDBAoAAAAIAC1nSlLYR3I+PgEAABECAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90
*/