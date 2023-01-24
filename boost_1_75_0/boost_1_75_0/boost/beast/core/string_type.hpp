//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_TYPE_HPP
#define BOOST_BEAST_STRING_TYPE_HPP

#include <boost/beast/core/detail/config.hpp>

#if defined(BOOST_BEAST_USE_STD_STRING_VIEW)
#include <string_view>
#else
#include <boost/utility/string_view.hpp>
#endif

namespace boost {
namespace beast {

#if BOOST_BEAST_DOXYGEN || ! defined(BOOST_BEAST_USE_STD_STRING_VIEW)
/// The type of string view used by the library
using string_view = boost::string_view;

/// The type of `basic_string_view` used by the library
template<class CharT, class Traits>
using basic_string_view =
    boost::basic_string_view<CharT, Traits>;

#else
using string_view = std::string_view;

template<class CharT, class Traits>
using basic_string_view =
    std::basic_string_view<CharT, Traits>;

#endif

} // beast
} // boost

#endif

/* string_type.hpp
gyD0NYr7DtAfTiywqkr1vuImyMN3ZetQD56Tds1EhU65doPzWtoPD3tEr2dKgJ3ZVZQyw6N07KqSHJJAo1EF/ODgFqOa9QzYaGXeeciL/c/Z32pXaUE3e50x7IV2Hx/QrLZsXctDdm1klyxuMCdD7psMH9T+yDlemP57+fecMM23FsjhiY7BEiz7CgFZos0SneNHE2dyE5Rwq9el4yVqJ0muq+40u75skVl/HBmtxxlf3XEal1sh7HY5kJeMZQUP7Vun1qX778KNZyoDDbh3pCekI1i4nIB++plrc2V38fB1ApIz/MlRHBU1Seki2u3sE9qBvL7VzmwtZbc2rxdEZB9Rqk+6lb5cLmOMBo9I1xw8mL6Had7v/uqLXt6tDCsCpBAI5U534FrZYmH+9uXlRe2GZ13L9QWWpHK7n9nK54UBXLTafms3PO9k6KsoGvZ0vQKEn2wkccoAfl+NFic7Ar5wvhVZ7jPWI9t04OAAfBey6+fwc/vWxzdEyQzY9qugQQUM+ITzfEm0jmEe2lISzXGrZTktWAV7P6xBcu4ZqP8R9XQ4xxcVkjynHRbU7CsemUxEq9+93cpqxNohCmW8wlZMK/RUfLKnMHVCl9EkzzOkjLMnej+qYCkM62Iqhjv+otvUO2pPTC8haclPL2p2hFRPqCoTXX4VyCgp9T3KQML8O+PuYo2SP6NzD6mZU6W4aogh2SKdhrRO0dZu
*/