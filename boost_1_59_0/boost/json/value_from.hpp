//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_VALUE_FROM_HPP
#define BOOST_JSON_VALUE_FROM_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/value.hpp>
#include <boost/json/detail/value_from.hpp>

BOOST_JSON_NS_BEGIN

/** Customization point tag.

    This tag type is used by the function
    @ref value_from to select overloads
    of `tag_invoke`.

    @note This type is empty; it has no members.

    @see @ref value_from, @ref value_to, @ref value_to_tag,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1895r0.pdf">
        tag_invoke: A general pattern for supporting customisable functions</a>
*/
#ifndef BOOST_JSON_DOCS
struct value_from_tag;
#else
// VFALCO Doc toolchain doesn't like
// forward declared ordinary classes.
struct value_from_tag {};
#endif

/** Convert an object of type `T` to @ref value.

    This function attempts to convert an object
    of type `T` to @ref value using

    @li one of @ref value's constructors,

    @li a library-provided generic conversion, or

    @li a user-provided overload of `tag_invoke`.

    In all cases, the conversion is done by calling
    an overload of `tag_invoke` found by argument-dependent
    lookup. Its signature should be similar to:

    @code
    void tag_invoke( value_from_tag, value&, T );
    @endcode

    A @ref value constructed
    with the @ref storage_ptr passed to @ref value_from is
    passed as the second argument to ensure that the memory
    resource is correctly propagated.

    @par Exception Safety
    Strong guarantee.

    @tparam T The type of the object to convert.

    @returns `t` converted to @ref value.

    @param t The object to convert.

    @param sp A storage pointer referring to the memory resource
    to use for the returned @ref value. The default argument for this
    parameter is `{}`.

    @see @ref value_from_tag, @ref value_to,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1895r0.pdf">
        tag_invoke: A general pattern for supporting customisable functions</a>
*/
template<class T>
value
value_from(
    T&& t,
    storage_ptr sp = {})
{
    return detail::value_from_impl(
        std::forward<T>(t), std::move(sp));
}

/** Convert an object of type `T` to @ref value.

    This function attempts to convert an object
    of type `T` to @ref value using

    @li one of @ref value's constructors,

    @li a library-provided generic conversion, or

    @li a user-provided overload of `tag_invoke`.

    In all cases, the conversion is done by calling
    an overload of `tag_invoke` found by argument-dependent
    lookup. Its signature should be similar to:

    @code
    void tag_invoke( value_from_tag, value&, T );
    @endcode

    @par Exception Safety
    Strong guarantee.

    @tparam T The type of the object to convert.

    @param t The object to convert.

    @param jv @ref value out parameter.

    @see @ref value_from_tag, @ref value_to,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1895r0.pdf">
        tag_invoke: A general pattern for supporting customisable functions</a>
*/
template<class T>
void
value_from(
    T&& t,
    value& jv)
{
    jv = detail::value_from_impl(
        std::forward<T>(t), jv.storage());
}

/** Determine if `T` can be converted to @ref value.

    If `T` can be converted to @ref value via a
    call to @ref value_from, the static data member `value`
    is defined as `true`. Otherwise, `value` is
    defined as `false`.

    @see @ref value_from
*/
#ifdef BOOST_JSON_DOCS
template<class T>
using has_value_from = __see_below__;
#else
template<class T, class>
struct has_value_from : std::false_type { };

template<class T>
struct has_value_from<T, detail::void_t<
    decltype(detail::value_from_impl(std::declval<T&&>(),
        std::declval<storage_ptr>()))>>
    : std::true_type { };
#endif

BOOST_JSON_NS_END

#endif

/* value_from.hpp
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
*/