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
ctpMZh/uTGzheXFfuLj3Anq89+l+OmJP7Pzx6P8e/MBv6nGZp38LF6W7tef9Jvg/6PVX+L1rksei6vKb1xO7u/wmutTFk7N8i3973q6J/oqw4T+PsedfPfwTSqAb9jxJs9s8ulmVonvSE0+++eZrsS+eHj590henfhKFsZiVYXId5jd98W1AJf++8t+/PyjC530RlsKPD+RQ81VUiCJdlu/8PBTwdxwtwqQIA+EXIgiLRR5dw4coEeUqFMsoDsXJ5PLNaPyiL96tosUKB7lNN6JYpZs4ECv/11Dk4SKMfuUxMj8vRbqE7jB4EBUlDLgpozQ5gLlDUYb5usAxcHo/LlLh/+pHsX8NE/mlWJVlVhw9frzY5DFA/zhIF8XjhVr+wapc65W8ASDW/q1Is1KUqdgUYV9gy75Yp0G0xN+AECjMNtdxVKz6FTQwVRI8TnNRhHGMY0G/KCwY7FDMJHr62ExkAHFU4q8iTQqc6t0qXVsNAY84ynKTJzAR4AEaBSmguS82SRDm1JhWrqaQOCUEt5KmgjcQaQLAiPuDmRjN7otrv4iKvvhhNH85uZqLHwbT6WA8fyMmZ2IwfoODvRqNT4H0EUyWi/B9locFTJ6LaJ3FURjIOeF/n+7ncafzGHj1ZDY6FYPLkXiX+xli
*/