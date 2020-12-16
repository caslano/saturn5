// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2016 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_FACTORY_SUPPORT_AJK_12FEB2016_HPP
#define BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_FACTORY_SUPPORT_AJK_12FEB2016_HPP

// Daniel Wallin discovered that bind/apply.hpp badly interacts with the apply<>
// member template of a factory as used in the optional<> implementation.
// He proposed this simple fix which is to move the call to apply<> outside
// namespace boost.
namespace boost_optional_detail
{
  template <class T, class Factory>
  inline void construct(Factory const& factory, void* address)
  {
    factory.BOOST_NESTED_TEMPLATE apply<T>(address);
  }
}

namespace boost
{
  class in_place_factory_base ;
  class typed_in_place_factory_base ;
}

#endif // header guard

/* optional_factory_support.hpp
fuR6DiG41kVoK7nfVPn1pDlXNZj0nWCmmkgaa7CrIyp3HK/j2khcia48sldGGpuRi+3Yp+r0Z7jKwlS0IycPqDRJP7Ra0r7LtHBdEM54/2YdTnd/FO2jt/2R7bojOM/aY7uTufsi1xOerJfod0u6obrGX3/oeo+wrnXvzpLX8t4NUVGHnYYMNffNoL8riZv2OOwgd9R0RHVCdUZ1QXVFdUN1R6WhdlF2PbQ5StYJe8JbUMp8tNj3kt+94a357NLkGTbS/Qz723l4aKGJrztrJtfre3WfkXde7upHEt37qVx9QKL7LHNuW9ZhF3OefdJGcatlVMlugkt2SZeWJ9f5Vi0PEiYBmvDWO2aBem9UaJGuJ7bEF8r7jq7ET5b+K2/JPnzZ33Xf6cAzwjXA9f6e40rttuS19nkR1v///CPN+n60VD9jsXDq0z4SU2T/oLp1X2kWWrXRxFJti7OPx1bme87ufOf34u1nHmkx6fTRuq8spyX6lPn8zWve/vJYauqcY7dMG7XsccYU8aHKvHlyxs93DhhR1T91RPSsrzM4UPa7pcw3vlOw0QJ/1z/aVyh44FSFz9jrNzFCmZd8Z1j02Ns7z/skcmFmucpp/2TNS5u/MfPNE39dvvfS9HtKF925tH8YcxdtvmnV8J67Qr77+MBjFf56eOXix3hnrOP9+eeoh7bUXD6/yavZkxPrfZ5COIWV+boZqbNbV+uUU2GW/e9jd5xiXNdYpz81dVOvr974vVjP92aW6LmuxHHalQ5nYunKybuKrnz2t+m7F59e8mNP9qhEKnPfY6NSys3+uVHSlaRCCc8P5b3UFr8y7757S7dP/3qq4w9b/7E66snyj9DmdH5zWnUvMaXS8qUvFmuyPPLcn4wT/VHKPOnlWUuvlu1zYNG0Ts8ufOGZk5xP0eZNfqlUsdfPsxZta9+v2MXwe+5in7eONzEmvePpHhfHVSm/asms6Vsvs5ctRJm/u+KLE60yRj0656cZQ3ekPEHaN/l0+ewI21ex6fLf6j0S8WTfXg+zn/KADv+JRze1mRfi/7PVsAZbx3/eYAj70HX9Ptl3Rp+LYcs3zd5S5NzJx1ccZq9WtDK/uDR5TfXD46/O+XHj3rkbSz/FXkWd38wz4xZezql44s37W5eo9kVDzg2Ga/f+lwqlD51YfcPDT+647c+Uk8Poj3S8u++d+EC1pXuGf1b0j22XK5Wpy16eQsr8lTf6fPvE2OIX/rp/fZsPyu5kbPWDNt/+Rd8yDw3eGrUg+qSd+PPmvay9hSnzGYVXHTo0Man3mQ2jnz9XuX99+jNdv6GXiv46rvvIgR9EVVyWuWJOAc4N63Lb2bzLpauN67/54NefHRtmD3udvkKnPytpyeU5PR7ut6DKbevi6kaep8/T8n/1o0MRD82ec1/7938eMqp/edaZH9Pm7boNS/qiz6VqkZklzt1V7wr5/VmNf2RNMp40X/CZs2ZFXL9/jzO/b1HrNvK7M78/Cvw284aDssZ7t/yuhnpefndFPSe/J6J2yO/lqGfl9xrUEvn9OWqZ/P4OdY/8TraZC8nv2vzeKb+b8zuykPl9F+oLMd+CeY783msTrvz+lt9H4sz4pQNleTTw26wtvcfv/ajC8rsF9r+g9vjMebGWYr4OuTgvYaajGov5MdQJl/tXXb+vuH7/5vr9q4TTAPWz+i1rQZflt+XTa2Q6/GibOOT3NNJcRuJ9Ioa9CPJ7J79Ly++T/K4kv//F71Lyu34s/an8LkZ4P8o3Kdf3Mc+Emy0TdxRqAEoPyen8ld1pGA3PwmT4DkyB78JqFmHCmvADWE/JDlR5exM2Fr2KbzAqR+LrJPFFonpJfH/gzm/ynx0=
*/