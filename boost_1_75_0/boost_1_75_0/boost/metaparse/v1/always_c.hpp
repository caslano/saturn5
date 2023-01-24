#ifndef BOOST_METAPARSE_V1_ALWAYS_C_HPP
#define BOOST_METAPARSE_V1_ALWAYS_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/always.hpp>
#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C, class Result>
      struct always_c : always<lit_c<C>, Result> {};
    }
  }
}

#endif


/* always_c.hpp
5Qa3cuFgdkqjn0Au3his9Q6DbQM+eUAXKPNlIh5r6mQ1cXrqlsa6kW7OnZk0jbG4QCLxhNuggXakLf2Y2EENTmDr206z7ZVgy5U0g6Xbyu2GPHphYHAWw9Qs+5MV8Jp0XdMqG1jY0926Nl11ktamKg9J7t+eVmshU5XSMoS1bcuVapXS1WhPOo4UAt2dmfSR53a0UgVkLEC8NhW2T/Z86p7gDlM/EwqEYD9esNCPPP2VAga1QohumJbNO1J6w4NfwujQWak5VNRYGpvOIDcVIDcCimddmJ3Z159C5U+fvcKC5swUBDJCsiP0345Mq4DACBqGbj2f3ZpRVm9FV9FOCgealj2gr73YjtSHeq1mD+g3LNCYLZXRQz/3tyBBsJlN0e953X7aFUvXSztkudWWTQ0Leo8HM+QTt73rJQwRHkeBDG7523VAflpBEd0dVIZEC3BvqzgyOlhxVmlazzadkVgXEaQDQ+fLoeFtGZQ1hWUFnNgWQiIB6469jibfUN4EenX9AHqRSoYw/3qCiMGhZXrZArmpGqwWGqgiD5jUBHtB5MmhfcH7qtbYmTAaGsKEjtYM+MOT7cX3wcIEZyYn2ovj+J+97SW3I6VeEJ1UrTh6d6CE6uJBeMeTPFAo7ywV+aTE7mEeeHa9CDxD35mxOyvhJLjb0B7+WSJfX3d0TXsMQoPFCG7Ck/GBcRCY8mkZLNYOxmd6yOFG7Eh0
*/