// Copyright 2018 Ulf Adams
//
// The contents of this file may be used under the terms of the Apache License,
// Version 2.0.
//
//    (See accompanying file LICENSE-Apache or copy at
//     http://www.apache.org/licenses/LICENSE-2.0)
//
// Alternatively, the contents of this file may be used under the terms of
// the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE-Boost or copy at
//     https://www.boost.org/LICENSE_1_0.txt)
//
// Unless required by applicable law or agreed to in writing, this software
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.

/*
    This is a derivative work
*/

#ifndef BOOST_JSON_DETAIL_RYU_DETAIL_DIGIT_TABLE_HPP
#define BOOST_JSON_DETAIL_RYU_DETAIL_DIGIT_TABLE_HPP

#include <boost/json/detail/config.hpp>

BOOST_JSON_NS_BEGIN
namespace detail {

namespace ryu {
namespace detail {

// A table of all two-digit numbers. This is used to speed up decimal digit
// generation by copying pairs of digits into the final output.
inline
char const
(&DIGIT_TABLE() noexcept)[200]
{
    static constexpr char arr[200] = {
      '0','0','0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9',
      '1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9',
      '2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9',
      '3','0','3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8','3','9',
      '4','0','4','1','4','2','4','3','4','4','4','5','4','6','4','7','4','8','4','9',
      '5','0','5','1','5','2','5','3','5','4','5','5','5','6','5','7','5','8','5','9',
      '6','0','6','1','6','2','6','3','6','4','6','5','6','6','6','7','6','8','6','9',
      '7','0','7','1','7','2','7','3','7','4','7','5','7','6','7','7','7','8','7','9',
      '8','0','8','1','8','2','8','3','8','4','8','5','8','6','8','7','8','8','8','9',
      '9','0','9','1','9','2','9','3','9','4','9','5','9','6','9','7','9','8','9','9' };
    return arr;
}

} // detail
} // ryu

} // detail
BOOST_JSON_NS_END

#endif

/* digit_table.hpp
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
*/