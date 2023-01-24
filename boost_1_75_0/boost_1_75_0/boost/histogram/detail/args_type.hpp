// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ARGS_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_ARGS_TYPE_HPP

#include <tuple>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
struct args_type_impl {
  using T::ERROR_this_should_never_be_instantiated_please_write_an_issue;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T::*)(Ts...)> {
  using type = std::tuple<Ts...>;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T ::*)(Ts...) const> {
  using type = std::tuple<Ts...>;
};

template <class R, class... Ts>
struct args_type_impl<R (*)(Ts...)> {
  using type = std::tuple<Ts...>;
};

#if __cpp_noexcept_function_type >= 201510
template <class R, class T, class... Ts>
struct args_type_impl<R (T::*)(Ts...) noexcept> {
  using type = std::tuple<Ts...>;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T ::*)(Ts...) const noexcept> {
  using type = std::tuple<Ts...>;
};

template <class R, class... Ts>
struct args_type_impl<R (*)(Ts...) noexcept> {
  using type = std::tuple<Ts...>;
};
#endif

template <class FunctionPointer>
using args_type = typename args_type_impl<FunctionPointer>::type;

template <class T, std::size_t N = 0>
using arg_type = std::tuple_element_t<N, args_type<T>>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* args_type.hpp
n6hWrVvDjwjdocOLEXXSfQ+qvoPObclQ2Xy6CRAkium7+cJP/D32svyVwQCPL3yzht9UxjcAVBjp0+C/JpPWFn6LqZEQs5F1FvtK9/LTU0jl486Ctb7UZRnwktA7O3ZajlCVy+S9zBFjBXAii7x1t/N3xPaqN/7GQP4dL3l/c2v+3WxCAMHFFPvXohr8FZm1H69NJo05TQalX6tQEhJr9E5EO8scawaOrK5dxQ+Gst4LnR5bbzR9jzVZGf789N6ca6Q4O7G+mcVA/akv2+cPqtCk7uf4FPkHVWAb727I7HddE6zAP7DEWjBlWZAVXrASfvI+V+buNVsKax5rz2FyrqssYHJuqvzWeTj36jSEbomzX3Q5PNEKT9f+27pj0ORy3qGnCoFQfNamGxazA5+BvN9moz3jHe34hY9Q7kvWpcdW7EqfU9dwQ605PAG56gLEC453sy4VPxxlrGbQM4Ve4brvgCNKYI79rbOK1PjBABdiSZwbMKN1qHw/tPTFVNF7QEkivY2EqJlpg1cueN79h2EwjFhsNtoJlvxVw1GR96eo1drEI9YSCU9bFFDBKe+5SK9oHCsUVfvEsY65zpM7v3p4Zs3g3+I1k2MKGpvKiVhrP1wHH4DJG3IKEkXIKfYe2UcgZpmBsjjG5lngz/TlxTgzYYfi8XbFOLO/f+47YWycHR5QE65uzAweqmYKUBQPqv62GlfOQZjfeGs5
*/