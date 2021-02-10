// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_VARIANT_PROXY_HPP
#define BOOST_HISTOGRAM_DETAIL_VARIANT_PROXY_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/traits.hpp> // variant_access
#include <boost/histogram/detail/static_if.hpp>
#include <boost/mp11/algorithm.hpp> // mp_with_index, mp_find, mp_at
#include <boost/mp11/list.hpp>      // mp_size
#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
namespace histogram {
namespace detail {

// This is a workaround to remain backward compatible in the serialization format. The
// proxy uses only the public interface of axis::variant for serialization and works
// independently of the underlying variant implementation.
template <class Variant>
struct variant_proxy {
  Variant& variant;

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    detail::static_if_c<Archive::is_loading::value>(
        [this](auto& ar) { // loading
          int which = 0;
          ar >> make_nvp("which", which);
          constexpr unsigned N = mp11::mp_size<Variant>::value;
          if (which < 0 || static_cast<unsigned>(which) >= N)
            // throw if which >= N, can happen if type was removed from variant
            BOOST_THROW_EXCEPTION(
                std::runtime_error("variant has fewer types than stored version"));
          mp11::mp_with_index<N>(static_cast<unsigned>(which), [&ar, this](auto i) {
            using T = mp11::mp_at_c<Variant, i>;
            T value;
            ar >> make_nvp("value", value);
            this->variant = std::move(value);
            T* new_address = variant_access::template get_if<T>(&this->variant);
            ar.reset_object_address(new_address, &value);
          });
        },
        [this](auto& ar) { // saving
          visit(
              [&ar](const auto& value) {
                using T = std::decay_t<decltype(value)>;
                const int which = static_cast<int>(mp11::mp_find<Variant, T>::value);
                ar << make_nvp("which", which);
                ar << make_nvp("value", value);
              },
              this->variant);
        },
        ar);
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* variant_proxy.hpp
LZaM5bgxmaz7kOo8GBCPEJ/jRQeuTJ9YlUsvKTM5GV+b5jjOEr0hX4HF61oV8Q+NPXG1fdg+42obP8vFp/C7nH5/X0Yb9lQdyUz3cswMakLBE5y6Cp7ANKHgCRRdwct9UzBos1n8bYOul6TvvV5jwwFY4Gq2lEs44cPC4Iyer46GOrCAi9OXbcN2AyO1RkloiYtxyTfl620k9nEc9QqjpYybbUK49GyxqQBslKlBzzUNnqDnNiKeOby6vM2TBkf9lE9hlTH5Kdw+rucNM3Jk+ldOvyn5TND4NUy923pO6h2c7ahjSbNvggWW8tBUx5PsLI6buJkmtjVQT6pASoTlQT2TmUU1Lr+QLy7h6PGtU4E1Gpl9uFuDcMGDVLAlD8z+YMZsAxcK5EHBBQp3UdS5zqmDIl+RapMWC7UU8Kj3tbZOcDxSBdJ8hRZh/Hl1CYoLrGzcd4Dke6t0DHFAp7BTgtfAxVo5QK9HJVAc6wSP3mMdBYzD70TIDgoJpzGIgOelgMRhaYkTZ4zYt5Q9W8j1onnBIU86HRzQJw/0OQ5ojYijUrhZVACkjYpegjh2KNcSnghXiQqANBLPSxC9EW1YiiW2BUASiXoZIiRukxwk5YAjEuB5FSBF/YT7QkVEigLqlZAUxE4lImWoz6u7
*/