/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_IS_FUNCTION_HPP
#define BOOST_MULTI_INDEX_DETAIL_IS_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)||\
    BOOST_WORKAROUND(_LIBCPP_VERSION,<30700)||\
    BOOST_WORKAROUND(BOOST_LIBSTDCXX_VERSION,<40802)
/* libc++: std::is_function<void() const> fails,
 * https://bugs.llvm.org/show_bug.cgi?id=20084
 *
 * libstdc++-v3: std::is_function does not support ref-qualified function types,
 * https://github.com/gcc-mirror/gcc/commit/
 *   2fa630fb50ba29d8e891c52a75aaec261b07874e#
 *   diff-6547f965a8d66bf35a6388fcf404aaa3
 */

#include <boost/type_traits/is_function.hpp>

namespace boost{namespace multi_index{namespace detail{

template<typename T>
struct is_function:boost::is_function<T>{};

}}} /* namespace boost::multi_index::detail */

#else

#include <type_traits>

namespace boost{namespace multi_index{namespace detail{

template<typename T>
struct is_function:std::is_function<T>{};

}}} /* namespace boost::multi_index::detail */

#endif
#endif

/* is_function.hpp
u/u9p1paAmeNVN+qSxQOo//wBYd4ZyLuGgfkYeEQHzwcyjMVDnni75Nb76TGluL9iAqHHIVDz56+jBHxhCPt0GZh94tFGekxYiVrjBgOtYRDGY2VLfeNyPADh/ZQPOkcCWZizBuizecRFiujf8/6k29X1FXhuyxaG2YrLMp+86dvtHY6RwJZWDjEfytlmRhqyARqjgspPstixAHz/O4PDsJq7F4mkIkHi/xlaSzyDSxwZFgyiPpHltIrex7wp380RUPuoYiG7LXVp6XwPuGAbd1q2RsnIg2loGZwWpdYTTp6+qFfizr+2yuM/lnYfWNxKfSSHlGAvm6r7vCioq4B4UJaZ6ws/sJPf3Do8KNvdPTTN+DZUhhJMoFNP3rrjhW0BS0wlLAYQjLxky/jhLAEuUYCWZg4jOta8kwp21kC4vOiV3/ZTlHXlHEXZfMzFQ5LHvBFJqIdzrVsZGHj0PNoKVxPfQPxWPX1z59GGnqvzRfKhT4ztbp0iPYJh+aYeyCQB4+VBfllj5TCPJIHtENv3PZFj2rp2rBM2xyzlDxUr+kPDqGNnMNALIBxGHlfeu4stubOUXA3jQ9lK5A8fOQLDuKuTedKNvKw5KHnrlL0ZZY4lIi0+6pGrapaug7MyyW7zCCFw1x/cBBuoe41S2ZiyAQILPT6sxTj5W7++RFIw131I/T+C/WNect8mTMiwhHKORTIw5SJ3ktKYVOSieEi7dOiqx5RLV0PjsfG4xBZoGRixtpr+aFXNiXawq5xQB4WDvseVwo3kjxgp9hgzN5ktx0NIwiHRaugPoULMl/W4U3iiLRzfYqZGH0jf04plBIWaKOf8P1+ayvqGFiABBwnhpKNyieZiHU4t1tqHqxXzu0qhXbqG9jWlboGkR6xvvQN1f5ZSJsxyhccGqOppHONipkYOvaCZHoOXd2aQzeA22n9mUtzx2KfsPBjvcFMTPtMTSk8m62wwPGgc+UPNlPUsfDT6qRXDaMxcx1fsAglo87HTM2Dcdh3QinsT/1jJK43ln5K0WvHQW6B+vaYHid8wqHNee9AFp6+UVGK+/YShzVxl3PdFfdS1PHSn1Te35BF8rCuPzgIe7tz4wwzMdfi44RdgrDAGMQ7wLMHKOqG8kyJvvtCjhP+YeEHFFbfyP+ihMfLta3xsgyqNlLfWtYkmVjPHxzCYdc7wZKH7QvwSgnMojFiFO7vfbzdNqql5TACF+eoX+eTPPiAQ7xpTkNKOP87BYKZePxgXiiBIsJiHfH3rMtHHKWoFVAv1p86nt8qOKZs7X79JaqJgXTdY4FMPFjU9pbAA4TFunjuo+LSJkWdgDqV/FmSTf1jtD9y0R5yu//HPEx79jMlsDWNE+vhmdKNTpurWlrJ9uxcPV76hINr4yXzMMfLp0ogRDiMxnMUDQt3Uy3dCOqzSKfS8jDGHxzCoZTbOZSZePSJh0rgDOobYzAuwc+XVynqRJhL40RvLsmET1g0iRg07gcK5pLeF76nhHWr9S3damPoHULzaK7yJYOZju009d0N+OFQKJiDtQ69Na1LbGDpElWwdEWyTZA8zFjfsTxQDZ1D4OkT8xemMRhrYbAJBHPITpWt5KDbBzlIRGY5hQDLt3yoriqBbmo/agaPjP6UfMk2haqVSXfIozHBBxmIdzY6VauZhXdsPD0tB+MtOdgMA7motdYq1Bc2cI+DuLfe4bDIDOy939PSGGxoYbA51NIa66tM9K4W/09y3xeEfT3icDeDOVi2h8NKYAxhUIb6wumhw1Urt4D3V6UGk712vmvfEFHDpoRDB1OjfB4P55bABdT+cty/iD1Mrd4SPiP9uVv7EfrQD0KpVMKl2sgsPH1hbrwEygk=
*/