// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PFR_DETAIL_CORE17_HPP
#define BOOST_PFR_DETAIL_CORE17_HPP

#include <boost/pfr/detail/core17_generated.hpp>
#include <boost/pfr/detail/fields_count.hpp>
#include <boost/pfr/detail/for_each_field_impl.hpp>
#include <boost/pfr/detail/rvalue_t.hpp>

namespace boost { namespace pfr { namespace detail {

#ifndef _MSC_VER // MSVC fails to compile the following code, but compiles the structured bindings in core17_generated.hpp
struct do_not_define_std_tuple_size_for_me {
    bool test1 = true;
};

template <class T>
constexpr bool do_structured_bindings_work() noexcept { // ******************************************* IN CASE OF ERROR READ THE FOLLOWING LINES IN boost/pfr/detail/core17.hpp FILE:
    T val{};
    const auto& [a] = val; // ******************************************* IN CASE OF ERROR READ THE FOLLOWING LINES IN boost/pfr/detail/core17.hpp FILE:

    /****************************************************************************
    *
    * It looks like your compiler or Standard Library can not handle C++17
    * structured bindings.
    *
    * Workaround: Define BOOST_PFR_USE_CPP17 to 0
    * It will disable the C++17 features for Boost.PFR library.
    *
    * Sorry for the inconvenience caused.
    *
    ****************************************************************************/

    return a;
}

static_assert(
    do_structured_bindings_work<do_not_define_std_tuple_size_for_me>(),
    "====================> Boost.PFR: Your compiler can not handle C++17 structured bindings. Read the above comments for workarounds."
);
#endif // #ifndef _MSC_VER

template <class T>
constexpr auto tie_as_tuple(T& val) noexcept {
  static_assert(
    !std::is_union<T>::value,
    "====================> Boost.PFR: For safety reasons it is forbidden to reflect unions. See `Reflection of unions` section in the docs for more info."
  );
  typedef size_t_<boost::pfr::detail::fields_count<T>()> fields_count_tag;
  return boost::pfr::detail::tie_as_tuple(val, fields_count_tag{});
}

template <class T, class F, std::size_t... I>
void for_each_field_dispatcher(T& t, F&& f, std::index_sequence<I...>) {
    static_assert(
        !std::is_union<T>::value,
        "====================> Boost.PFR: For safety reasons it is forbidden to reflect unions. See `Reflection of unions` section in the docs for more info."
    );
    std::forward<F>(f)(
        detail::tie_as_tuple(t)
    );
}

}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_CORE17_HPP

/* core17.hpp
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
*/