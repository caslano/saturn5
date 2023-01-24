//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_CONCEPTS_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// TODO: C++20: deprecate and replace with std::std_remove_cvref
template <typename T>
struct remove_const_and_reference
    : std::remove_const<typename std::remove_reference<T>::type>
{
};

}}} // namespace boost::gil::detail

#endif

/* type_traits.hpp
Al9vDEoRDNuWQiB6Q7W94PSUMs55plu4hphC/6ZZU06ztCftfkbIU6nqEu3o+19qDoPLxllpGEt0phO46SKj1CWb6a5abjvx5lFqP0Eyp75myx8fyR3Tw8oGaG/mB8p0tfHVEp32i8hK5fxHYuTJkx/WfO4dtFTWZlMH5ymAX9x+ytC++5ZQGKUF+OiW6CJbBeCQ3BXlCz4c5nGv+0OLs0ml6cnPbc/Kp1V6ZjXySFr9Xn+AQq2igIvFQu8np49Rbpz3xgCAL/ho1hKs9vND+Q5VjMmOGa/XOPea2S/Yh5RL8MWfvHaJK9y4dCXKh9/KU+lKhByuLtKrGNzdry1n1iba5dsKhRmY8HFO/zmmkZCrU+WBCr747RN6I+OSnZk0Fjf0SAG9gP/XlwsmlgL6+vJft2F68F7bn9TjnQlazuzS7nJG+5Ir5u1L6sM7hgmzEbl8YtmtRpncyFOkby062bJ/iCEnaBowE2i7OoPIG+VT82p/zJc5bSTptjV1Di7PoCZmJ5NwSts461TYuWlMcpClgJ/2P2vOCqj9iS1soGMg0CDpunpx/8VjqF7OeZI3nC+3jEELu2VHJ7TgPilWYkTNt0szEfgB2fxWvHqhocHW9do7qiH33ZL7b6QUi+kx+tSnCtZ0faLpTOb4vr22vaP9JClJP4+uNndX0Mom0RUYaotx3cu5Ri+t+7bD90pNL0X7Iw6ZpuDu5rsV
*/