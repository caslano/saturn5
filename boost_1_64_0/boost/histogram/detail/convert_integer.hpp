// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP
#define BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
using convert_integer =
    std::conditional_t<std::is_integral<std::decay_t<T>>::value, U, T>;

}
} // namespace histogram
} // namespace boost

#endif

/* convert_integer.hpp
d71+gIAG/nTGhBnixao+fYoidfN+HxY4syVIGEmxKt9PiXNsn3n64PLJ8Bxp/rHLOTZo1FsGOLD6jehLDjvZfrGw7psv3a/QcAhn4Zxxs4a5VINvjtAPetWiBD1Ex7Exwr+DWw2wKrDIaoeATOrVo+BCE3KHbmqCwdzC1h4FOW9wqPclKx7BMgyn0l98vKJi5z+Y33jObVvFfarIGvoe+KkchjjpOZJwoRFsW7kNDSxzZuhN8I4tf+K2ib+SW98Fm18avDkJTxYlm3WnSgRF53xR6hdi+bWhYnFQVi2BmWbu6Au4NvV2/0iVIb2wj5ALyxvYPi0ueYvkY5/hzNqQUtAJOTCed43xskqDR8lVsJ7S91rClnNBkiO1nwqXWSChGHp5MxuK8Z4lGrsR4R0eRnvQCyre/ecAKb0lM5S8t1HQ4YVghgucO4pyVnHo1N7KJo5S53Wcc3QqL1Cbu54hzzmQj1fnePxZ/Hk0kHNiu0SPigyJZkNFerEkxcR9mcOZD9ctKqCWdoRHeI/Qu2YmpcG+T8pFboyyoHDVAHdzRalFCyqbW+8f/ksk2g==
*/