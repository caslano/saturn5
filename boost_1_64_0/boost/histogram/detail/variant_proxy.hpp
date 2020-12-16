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
DmJN71V3Xbqpg7EBVpsNvBDRl4bhBHX2ewl1FlwUwMjdJEip15Jj4jPLx3rYm8RlgsZILSBeIWUUONENFGWCDNQJN9ijRpV6NIYoBB8E4wyXw9ecqUcMl0N6UFKPwOkwLNMJmt56A131xuHR6PlY+P80f+WIdYdeiEZT3BtVlI+qSpNEh7CQfi0cAaJpkScbltBBLCj7DbEBSCl7sbsVXsXaaHQgkgFlcQR4HXavdS/2eDCNdAQFKEd15GCus06JoGjRUTTw4qa+BVgBJ9gyCOGQAF6HXiAmuNtR7GFlU+SPwZnP3ArNylLeMAXBkreBgIsUYSQZkzSkapY4rnU3A8MjZBgSEcs4JWLdnPP04twvj+Och3AjzgGzJ489vnMZ7QzGmGG+gnBqkTi1GHzLEkegCu+6D6vgH/ACU7txyz4N3Fy9cHssAbf2OG4u8BBwCT/RSpL94y/6v/gwVUxIdrPSCBSBVitjhzrUCgUlHPfz1FizuxUFUP8UyCaw0HFKNMXabtmKDYzf7wm/tcCP5OsGb1m6LoLuxsZxTTAH3359qJ3wjDwZ7Ho4Cmxp/oPx3Mt4hvFq4DqRZ3GRfOximKHW0dRvxk/dqmz7y2BCEy9h6H4EHrgv2SIzPEGRLyJWwVNV6xAkNkasK8QQQbOA15Ge1UaTo402SuwS4Gx0kNoV3TNQlX5fm6ncwdH6YWpbdJ9CydXNtdG3BQpHDuDYDjWFUJTg3UHRYlLFAVAO5qldhkavRbeiCpxsc++jGkdkUcWa9w4mH1Wai1FIm3dBczJAeYJQ3CCV3FYi6GjCksn5d09kvJlQtd4jxuLVFxlvotcpnqCk6ii5+DEVoCHaZEM9WK8eBQmY79yrMB1MxKba6DtEwFFlMRAHb0y5tCcg4TYcGEB60O1DkIl7P8iQGgxnRNR5CHEXZVB3KEMSCRoLeqD9TAOIydbpgLJvI/ToUF+qkpEJ/UgI2SsIX8wZAt8Z4jxxVKwDtsT8I8R81A9A2AR8qTEerLYBeXVTZMK7UEdMXRGEA+Cyzv0sEEHczwPe3YzHXI67JVLlCQJ7xlOZZwbHqW6g19DT7gJhR6LttbPttUvbG5nQHwXCAgcjSZGqSBJRD5UMiCHHo70eSLO+MMqRCcfUTeT7E2e1KY8UH19ZjZLN6C12MQ0ZeNXRzkYPhVE2jPA8C+wzzU+qBnftiQZ5q7IJNWmLewY7TbJGp5BjJPOJnOa5FmQL6DfeMk/E7fWsIQbaUkOuVo4iPyO9JIkU/gRYZ3dj7SCsgTHwhr2eZ1Wqk6ga44MGmi3N4btksrlGkwU3bCMqCNlrkhQVDAlPAcOi+KRjAgyukwnvE+rXqZvA61zmtOcEODsMnFtJ0N3KYefqmIEPHtLeZpNUZmkomxPMOLjdjNbnMHEV1YtRro2Sq2cA6Eo+k03vE7JVElnJYdcJsLUb2JJdb5U2vYcdATlgNXB2AFulsduA0FR+Bzi7D+sCYIBIGKNxJ/3rRpuYnUlqQloJG9YnpOcQ0mI/4brh0AtKLkQIu25UPyJ9rYGzC5qp41sLS5+uzHNKq8dstnPTnWDlDUa3kmciScPdLF0gqPc5lp6QCaRDt8NBw9An1x7x2u5OPcoHE85FXA78A/A/jH2CeD7ZEcY9PNmMVy856eAFT+HJFgRM4QnxfGUHgmhyuEjRwpPpGMFSpQgCkSMEYbyGC5wInYpQDw8pTLPzqMKNjjBCwwUuDE0s/+k+Obsr7uZODcaSH8Rgc82z1H84kwGSc9e569z1f3utoiNCNds3E8dHt8iBUU2fUnvCQ4fb+v/mw6yanFOz+LTmmV0xzKjtlzNq9gqf9sv5PPflxDRY/Tx+TA8=
*/