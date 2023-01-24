#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of = repeated<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of.hpp
Y36Jto8fyzyzOxOWMVrItHxcQKkGbmDWL9pZo7p0pLJ5gcgmnfJ20en7MTlByIoD8H2ulV5N+wWPQMHpC92uYTUy6BrmzfRkBqNyFrI3QdWTqTl/oR7txMcAmZ9zkOkg7n7g1YuikzOLotOzLmVPZrSm3AlCcSA6WfMpG9D3XuslWSwiA4rQ2q3lWThZ3n61HS3DG/OuweYzsHlDX3AKcma2USmYlBnblnxw9m7WXXlzrMT/kSHa0BRo/7nmuPFoZOMp7B86lV79+RZOKQXHph3fH0k0bxE1mM8cUxJzoC2/puu/8U2HqJPeiOJou9PmI7peS6K37rr2Zuxwu9Kquy6Br/mbgGiogzJ112EaiYaDmC4rg+FoppVr0a7KtmLpCuAKP8ZTWE3P1aZk0+Gsuz7Cl6Jn/wZt1/Zc3aX/Fv+BbB5FVSMNvo9Q7Igc2aLLemO5r3BCSbhd3wJsRJVcdjigHIBDRVqVXgH8ZyVROKdXb5L1d2X3D4sAfvvn7wmU/RAbzE+BRP7DH+mpPvoWWd8GDy381pv7hd4I7aHeAVUu2FbH7ylxF079DCNtq+7qwqtoizgBu6HZcWbCF/jWmWhVkn5vtZhzVSfpRUprUNkcVHbKE1HQkZY8SFtpff6n5YWZGIDYkCJH9lnDhwLKJhQiczej5VrZQFlt1sP3YQ1Hdoym0xM4sOvgqenqoEmB3JbQuUW5IPRgnP+i
*/