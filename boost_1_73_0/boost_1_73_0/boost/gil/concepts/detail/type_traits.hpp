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
Cdw1k/M+Ri8PWe/D2bSBm2gNclPB40mIKMT6UXHU6EI7cHL6kVg+LUFBkCeS662c81YI667QLVyXBY9fclyoijwr28pU99wY+jmZAjSxIFdiAn3d7AnljtFNvK735nr3RjMJhGQs72XMnE9zuDcRzBK3CrUQXCBqcwQQlm6ZrKM2f7gTy0K5E9TWGb8XCqMQGxT00SD7jrUrAwTXSDM9hYbW36KWZ70xbMBxNc3VtmwzZ/4PkiONDkfSdKjpkzeNIjccGXBWBoA2y9DhRnKaKdmOdK0k+99JoVeuGnaTo+MdUEGp94HuCVchcGaGQ3BHiKXzzjoJqidoK+Esy+AjBjvS7LMc6s5wK8h32NFwYfrD6ALsM42lxYAH2BJkO3WjJM7DtgxdFhIaxq/HMvzs4QOybwJlMCpUFNPxOSIWQG2McmYgISe3MtPjECqAUhRRLEKHcZ7Gi85ivLC0o9uDHnBQlnC2FpG+WVuSPoBqHsS8hbhDtXanhhiAiwwmKVgduFO1NhYr7IfNhB1w8T8IC9dUVeTIqordLy24SWXhUkdjUf0p9mpInfCO2BQOTbPTvYNBGcvqAczGivJQC5/vVShPxDGsS8DO7YXPhhg8ah+/Wh+MYnKmP54x9bqz41oT0Fk4Yy6BmwByWyp2
*/