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