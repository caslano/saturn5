#ifndef BOOST_METAPARSE_V1_IMPL_FWD_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_FWD_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/deque.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl;
      }
    }
  }
}

#endif


/* iterate_impl.hpp
/bxig77zPP68fuPUG6FNSc27QqpsIv13do70le/B345qB+VOiDFB5kgTUnmvgc22o3NWyS6J9kbSzEVUmxsP4sh5wI1ZgEkNaMMhHS41TKn7yZXsbFXL88KZ8RDJjtcgbovzwurGyKd2L6jdEIG2l+nYrbL5R8rJtkaSjjWG+LuM1BULPQHXYFXzvCnzb478iYHQ+ZWljapy7zyYn4Px7a79wEj+A23SR2bKf+9vofNc41ubztmovc7sotZblPynXlTbmxfEDgWCDk2hNQ91Tr0m1Lijq3SxFYpXaJDLxKn/lLqSofHVZDggT2pDK/n/AhDoVoz8pzGQONXW+XEQgU61g/j9A+3PGsZMDbeJh+afjkAruYUbOJAauBEu/SYBUjUZ6uQFlOwPcZXOkKRXMWZ8zQEWlxVPyQMicI4n/GRLTVwO8Zj8ZDs3I7tb+1BWTkDu02QbbkYF/8uAW/kg+XwC4kgt09E9EajxNMUHLQGv3MmGVNb6PeFA/6lsZG4aardJ9/PmsEpUa2YCl95BcssMrLlshp4Sze85dbP7AoIUqGrhQGsJTzRfGtvC7z4HQa7Kul8qTLlcEZMSrZBl7Tr5J3V0vAilbsxd3RemaT+QW314IAgfnZd3+tGapfa1jJaU2W+DQXVLGEySoeSrfu4yEZBak9ZyyN4dVY5qVTRGdbsgrq3uFesfwHnQDObG0p2oVWwpjQdvUjw5jQmX9BsSDNFWmiYj/2yE7I1TgGSdLjVvsbqH7ZD9J6fdoUvW6KvATU4dY3d+Y2F7agRTApwZjy6K1x6i8Xl7NZ/FJUokjxXSGCd+i5W9JsR4Hamjle0r8GAIjc/8oPiRAbqJIjashHNxO/k3FqBCWW+y0x+TKuzsyXis0P33iPxNd2jyXQ3NF8WAOr5kfexU8NnuINhOYdAVXILmLcW+ehfNZ/lutm1V/HyD9qsFyOLvA92M4ejxOVj7wTbqBjyEyz4FQOfkp42l3orXztd9K9uF8WhOjertZd+vA5TtSl3r03CerH7uIU/vpkikitHiXHnYhPHQzOn7CGwb3Sq9run8UGSlreL2Le0V/x2m+6/61GESiANtZT+HwXnFJXP4mSm+NZCxNFaH/TgJg8bVZb/IoesVh+YJI2Bgopuwd3VS3xRKPrEPYt/6Os9d4HLVhcbraM+2eUuXNPqBbuPnu8t/4Kb9GbBTA3rYiLpfFUOb+IoxP6IJMlKGV6/vind/glW/Z9B9aqn5PEHnxy7FLzvZoq8JxOF7QVRNl/9P3rz+exSf/qL75TKyR3aStXoG5yFdIHHYq/u0nSXzpSe9m9+W2dS1vCPy2SB4gdOo+lIO58bGssflcly6iWpN/Kn24T6axwkUXwb7NYGAWZZIUCMM9oW1cJIV2MyzAFWLaOfqmQ1J7DOyfbMhuSz76s5x+SdLyx82Rvet9+iRVJOySooMjM3S+SEP8/wsiGdPg2lzc0jcXVHmXSfx2wpx9lrZGzt1P+8Dq2qjNL5dFZ9Ok72mgFu7Y4ovaAlt7A0iNVzr7bgZ81mzfe85sPc3M6p+pwCnIsmumgW21lWNb030rW+q+9ETc+lrjHyLYWBUmbKzLbQf6Mx7+4m6izvIfklh6qXrDFhiT+PZA8HmfEgXb/Eg1USRuPpa3fbtYWD1UPGUWBrapkMpt25je/TW5Z5snxmjSA1T6C3yp+K/q8Gur05dZzFdKvdYptqt2ITU1snm8Fun87IV/be8GnRRoWDdqtDk7Lu0sdgge8idvjI2BRteUv5xXfDbyAa5o328mO4zD32cFK/QfesN4EQt+Tu1lR6Qr6DhMt3fbpLNI5v62htaiz9E9pD2yeHyC/ispV2vUbo=
*/