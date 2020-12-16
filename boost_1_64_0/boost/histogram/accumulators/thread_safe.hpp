// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_THREAD_SAFE_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_THREAD_SAFE_HPP

#include <atomic>
#include <boost/core/nvp.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace accumulators {

/** Thread-safe adaptor for builtin integral and floating point numbers.

  This adaptor uses std::atomic to make concurrent increments and additions safe for the
  stored value.

  On common computing platforms, the adapted integer has the same size and
  alignment as underlying type. The atomicity is implemented with a special CPU
  instruction. On exotic platforms the size of the adapted number may be larger and/or the
  type may have different alignment, which means it cannot be tightly packed into arrays.

  @tparam T type to adapt, must be supported by std::atomic.
 */
template <class T>
class thread_safe : public std::atomic<T> {
public:
  using value_type = T;
  using super_t = std::atomic<T>;

  thread_safe() noexcept : super_t(static_cast<T>(0)) {}
  // non-atomic copy and assign is allowed, because storage is locked in this case
  thread_safe(const thread_safe& o) noexcept : super_t(o.load()) {}
  thread_safe& operator=(const thread_safe& o) noexcept {
    super_t::store(o.load());
    return *this;
  }

  thread_safe(value_type arg) : super_t(arg) {}
  thread_safe& operator=(value_type arg) {
    super_t::store(arg);
    return *this;
  }

  thread_safe& operator+=(const thread_safe& arg) {
    operator+=(arg.load());
    return *this;
  }
  thread_safe& operator+=(value_type arg) {
    super_t::fetch_add(arg, std::memory_order_relaxed);
    return *this;
  }
  thread_safe& operator++() {
    operator+=(static_cast<value_type>(1));
    return *this;
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    auto value = super_t::load();
    ar& make_nvp("value", value);
    super_t::store(value);
  }
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#endif

/* thread_safe.hpp
p9nLwO5HIwpmB9coon8etqnnjWIu8e5sHhG2TEvli4FrUj4EUlUYw339Wjlc9W9GAVDia9HWkPmSEp8w/G+or+o5sD5+7xTfQq1F6AzV+ra610jziDWzpcdtnfNEG2vRxhdwYP6UH6+pvTsE4o6pHXB1xLU43Z6cEzlhMC5W5h7YcIxY+XJSt1e64Djzvqxt2tGXzmnnHA9Da2yB/t/Ddb/E6LRW0d5o7lKZHLrBTDDIa173AubHeQIaY7O/NCcsjdfYwIYYH4pP8I2HNHd4qBIbu+PhlpP7qE68nxddrT+ZSsyynIEC5N2opqm6zp5/28JHdZ5lhjIaPMsL2gcP59/wcZv8+efLv79tfmeH+cvKWZ6Qs88jPh6un2cc1WyNDHPgcrE2KxK5Wd5Z4QrdmZEd2t+Fnlyod4sfTjDOQ5nqUwkSM0l2uQR4PWMeI6NbfHsVZ9LqudCWo0NIsJUfnGVzP0i/g5cHb1DEetCsiNZa26u7PHOL8ujCEJjGNXLQY7Axn52L2WpHpSJ8VSt9q8qwIQrPDzvxTwisQBm55zMhAMwiuw8Xvf2Rc0gkVejKGsftg80ocdkSktoNyMV3qz/LkklU0hG40Ex3VpRUEwn8U6GvnYlsEtBV5DQixOiYj+REV3gPJ/i7bJg8ym8pbm7eACq2viHRVMypL0ugp9B+hfzF5mIjzv8B5SzXTuKqVCSuS1Gu1X+Y1DCjG6ymoqgkXw96v7XIXNRaPucQMjoKD8vBNNvlvzmHmhNywhvQRdReTqaosD595WbDXreA73BgWAwlFx2diglGQiw0IHTHcZLJNOJdmdSEyFXCRpxJN/6FJoCYQ2fzATGMmIV/64f4DRZFaPnO+tiwHWHdX86bi4EfoP38GFNmcBnvDJfS9ZFG5E+QfpRsCCulLmG/2ThKJYPHWAiukDx8aChUBsK375k0hTRSg4jEvcJEzv6HzLm9nSGF/6H7qyH7dM3+17Oh3s47NyVMMPv7VdWCHykwT5hi9ncPbEsASwIBOLjJ5i7MjjBFPAeKmBhaZM57c90WkCvSIZLNFU2zZloIcZ+mPGu6vbeTOgPz3S/I64jWjZd0nYVe6OHf0bUa8PtRhdytNp7KwOBXX4xTDNwGTg9M5B6ZYNTcF+uj+QrEoZcYOPeSIY7+F5EhV2guAGzPaFQyLORM10XPAYktawxQJwHU+J+KqUPNBp24GpTCJp4u0+nEZxizPv+LPqn/byFbczHiQsqzLXH9n9ph/w+sNvqfaHT+A1Nr569B582fo/OR/g/6xP6fo/5PJ/i37X9hh/2/MNL/rgR/E4/AHgV+FSOYPOdzjEDq9yoWsjzJbkjqbfVaCZ2PrVodBQJrwBG+q3Wj/iJ2KMmbSM5Uakh+xJpVsYhio2Jl5bwen7JE1uNRom0vnQuN+MN3l0Ch5hK3yFv08QtsF60u3LrtpRWCmEUtLn6Aku/bf8anKLdOpO7euCCa384lpmkaZDc2jMdu0h+TmRlcJk8+c6FAT6w+VGlpsJiIh25KIB4Z7HnVm/QLNy5Nbv/VHnF4NO+mtIUBDnNd4lcj5aauYFO/gKi2uKA1xpeDapPLcRVjcwlTcbboarXn0hr0V7RyQck/5pPZxHptNrnvyAmThzi2gXjOcfsEdALs3iH9PZrUfJjjkhEy+S/w26r2OWpOmWkfqw/sXw+QpsKL77GJ+mzhLhztrMjZnJB8tGrf2q9DdTua7SbMq2ZAROUQt4yl4wON+3fICrOFissjhR9AzJ+pH95Ej0c8Ws7joITbqFb0gWpuuha1UaDuYGITmZIAYpkm3wrDy13gnGtF1hM6jU9DD/t60cVXx0VamSC7mNbcO3DY1dw=
*/