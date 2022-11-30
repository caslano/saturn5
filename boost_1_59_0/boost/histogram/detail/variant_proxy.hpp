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
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
*/