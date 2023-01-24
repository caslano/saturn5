#ifndef BOOST_METAPARSE_V1_SPACE_HPP
#define BOOST_METAPARSE_V1_SPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/whitespace_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/metaparse/v1/util/is_whitespace.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<one_char, util::is_whitespace<>, error::whitespace_expected>
        space;
    }
  }
}

#endif



/* space.hpp
CpnTTqw/eCnbiTEUIFmxGWJFTCwCCSFcOhhzwBT+Fecn1aL/hu7atx67Jn8X2e11hE4iI8TryVeluimkBb2PFamfUZ1oomZvUs7b2SuYmK0AYram3lTaI8ezQuZoU3zEzKyzghrAi8o21FcuthnKze6lJR4hHpzqit6YeVRfTu4ylPoYUzP3HkDx79UtRkCmA9nmOIiD0XGcWg9GB4yxET/2vmBk3BTJLCocYwGbR7mcDzb9wgF8UjX0Xena/YV4Xj/TavR9/gFLYslRLG2Wd6IQnuQ8Uepeod/6oUDIMcfRb6GYLZsBYN2sQB82WDnEZSCxYoYffolhDgIpJ2PTBGGpTE+xGLagkm6O1fU4ag8H0n05kvwAZz8vk1qQIrgfjYeAD0GGrPpRm1RXR2zm7JX8yMqktGudVpEI6EYKSV5JA/gHv7CccQRYDFfRS8lZ9pYbSLI8wWq4XIQkz15uqLVvNUOSn08yWyjYQeHs56Xa7cbqHJAAM4KAGUEl/DzG7PY2USSQhCJFv40iFG+fiCLL4yiyZH83FPnDuGQUGbCfUCSBjVtp6GFWxs+r541rz3fXpbY9Scwjj47NhMbIqn4fe/YEd0piL5zgzpS24K9GWNCdF4lT8NBa4xR8xCMufWFeqvUw+VnhF/Kf+FwuPuvFZ434rBKfleKzwt8jB0J3J4jO/xgs2RjSdG6A0wLIlJeSJGH+J3QJQQlR
*/