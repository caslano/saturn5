// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP
#define BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP

#include <boost/assert.hpp>
#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

constexpr auto invalid_index = ~static_cast<std::size_t>(0);

// integer with a persistent invalid state, similar to NaN
struct optional_index {
  std::size_t value;

  optional_index& operator=(std::size_t x) noexcept {
    value = x;
    return *this;
  }

  optional_index& operator+=(std::intptr_t x) noexcept {
    BOOST_ASSERT(x >= 0 || static_cast<std::size_t>(-x) <= value);
    if (value != invalid_index) { value += x; }
    return *this;
  }

  optional_index& operator+=(const optional_index& x) noexcept {
    if (value != invalid_index) return operator+=(x.value);
    value = invalid_index;
    return *this;
  }

  operator std::size_t() const noexcept { return value; }

  friend bool operator<=(std::size_t x, optional_index idx) noexcept {
    return x <= idx.value;
  }
};

constexpr inline bool is_valid(const std::size_t) noexcept { return true; }

inline bool is_valid(const optional_index x) noexcept { return x.value != invalid_index; }

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* optional_index.hpp
JwAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL09TNDAwL2Noa3N0cmluZ3MuY1VUBQABtkgkYK1VbW/bNhD+rl9xczDATjUrCfphXZJinuN1wto4sNxm2TIINElZ7CRSICknQdP/vjvabuIsXoKtCmJJ5N3zPPdGJbtf74pgF5688vCf44X34HFmzUfJ/ePWeX4Lyz/0usT7UyQJ3Lnc5j142uUWusElX7Ec0XOeP0V0SdroJyHPy5wecQXdyHNomhur5qWH7rAH+69efQ/fwcHewX4MJ0wrWUHmpZ5JO4/hSISVH0t2fd138nUM0gOr+iuoaakcOFP4K2Yl4HOluNROCmAOhHTcqhm+KA2+lFCoSsJwfHaRnr6J4apUvCSQG9OCK01bCSjZQoKVXKrFEqNh1oMp0B3BhXIeAVuvjO4jtwQvbe0Ig+hZ5QywBVMVmyER81B637gfkoS3tkL1iTDcJXwdfr/09ZdILlBEzW7ANB68gdbJGMgyhtoIVdAdE4KLTTurlCvjOzVIpUViLDhZVYSFfkq6pWwJ2So9MZlBg4qVp5sz2hHVVWnqDUPMI6EUrdVIhHlAI2EwzTG0WkgbjEPka4pVTkOCt5bmTq8Ao1EMdAYZpFkHZswpF8N5Ov1l/H4K54PJZHA6vYDx
*/