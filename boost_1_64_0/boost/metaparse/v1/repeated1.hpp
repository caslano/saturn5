#ifndef BOOST_METAPARSE_V1_REPEATED1_HPP
#define BOOST_METAPARSE_V1_REPEATED1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated1 :
        foldl1<P, boost::mpl::vector<>, impl::back_inserter>
      {};
    }
  }
}

#endif


/* repeated1.hpp
Pmanj32K93OS4v2cDxk7NLoX6+XhaKs4jYOrV3dudHU14M7ky6Kusf9FjNGRydDEJLIQnHu/AhnORBt8LJZ24pnjk/0jCTkOcAz2sVHcLsjv1aHkl9sY14p4ezyCcuEbQUnt+/jPZPw4fh028BUx7t404+4tM+7e5nFFMKZ5Be6tvQv8f8TYzz9hH+l0LDx3ErQcPtHQ7wEJuCvziImBNKpKl7/awHcgeKR77QVeB1pdCB7o/6Vhno8P14A4PjtSmR9tN44P4t7JwJEulA/RkfxebNqzU5WX94tC3jtXaXu/SxXL9GLIdFfKi1+bt5LqZmbO6NxveqgMnMzagN0UfewDqjRfu1Pa4eZX8TekuZhD5tCZYilkeMTEUF7+LVfCDYJ1wVTIbTyl52xXbnNC2oOgnSTaDaBdFNJbGET1zDH+cCfSWiTTu3p1NOaKCf9kl4dYuzPhXzahiqWzOThs4aLmJUubmpa01i9bGYpI5WTXL7xnSJpvtCVVQ6yNRkDbybS0So+nsio9nhKUBg8Ei9+7VLCeE3+WBp3LIb0D46s3sJfm+/1iTTbNfVpTxX1aa/q0rsrhjqxPa2L0ZS/Qk7ozD7QnjUhfNqzt7O/q6+3tag1fy8EYc2NoQRGPocmhjLe7Jlm+iILONS9qPBhG32Znx8wU0OtBO/YO20GrXsxb+1A6j+j2U3CSASrDNj98mzlU3CjW4zgb61G+3YNyRZgr9oRv51ShwyXBYPai/2An5tO4dubi+TiLRv/2Nfo3HWN/P2kngHes2U98HLgzgQu9JVw+Y5DfH2YB/xPA/0EQH3d2hpOn47+3L93TOpAecKHLIa/9CTbWwTb0d2bSrV7oDoZy4xxsdddguKYAfr7L60+3dUTo/2T8IgdLdfUOpKOKfLnZBCsJYb09VGowlWnt6+/tDt/lmonY+Z8U/ZIgXLM14gysQ5z+jCbadMK3aBk9uN64INjm0qPC9NLmpkOXLiPewrzRLg9XXKK8HcK8eWRQFsxtDHxensvzK+swvWOYXtDc3NRMdmqnUH9cf32qytUKAYTruwHH5GEzTCYxuq1RxdHuTw8MdlFE184e+zZVXhbWtlHCCvJdH2Vc3CBaGPGa5yAhr3G5Y325tSMNKv5zWyrjItjTo/OpgOvJC3qPbqUwG1hroe5UW08q3eXzuf65H7L+6ah/TlgOUhJjd16Y397b6yK64p2HyFbWO13crj2bE6xHHQeGtLDu5rYNZozOZgL/tl8fQbzVkPHL0R9O6sCfH+p/q/Cz96VmwrYsEDJJkg6jOqHDyIAO4wyF6nM/vk9kv4EfDLtCtgDrPvYVoTyUYRo57+RUsb9SPL7L0/5KS+S8B1tm97gFMWdDTVXChxSfbpkO/FBcjDexHmqp8riUDOefjCtG8lmt9jY9Syj4S2Yt5SPPeb8t6unMUNzw+lA5ke/8+zfUUyTyw9qOTg/2HequSmTLjHOwXto/9XYdkj6mhdZ06WAF1jcruP9cP9c3NbaQeWhtXjB3Pv52ecuam5aE/TkcQti/K+Lmkv8DXSe/lVV8ntJQlLsfeK5Iz0WfxXxxuCjn5sedCPZAkYcdKWBU3u/liz3sKDOHUVl1Hr0T4bajjpTBdfAW6BP9H9JNA3e1qNOP21HBcQXsq4U06uE0dBFzaby/7dGo449FOgZkN+VPdrTNWrCH8nktb2RIPPeB3jqhu+siPc+Dr7TgyX4XyIj16GcIti7PleXzjJ0IZz3q2IA6YCNI3pA5vgOsqpKy3zE4BuU+L9cPPFbRFl4/HAv84zw+5MmyeS/fldXyPIHlAzui5fMFV5bgOxs7Q/26HXuzc3BSlbVptqzHJ7mGNu0UtN8=
*/