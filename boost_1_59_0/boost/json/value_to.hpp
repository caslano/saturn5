//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_VALUE_TO_HPP
#define BOOST_JSON_VALUE_TO_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/value.hpp>
#include <boost/json/detail/value_to.hpp>

BOOST_JSON_NS_BEGIN

/** Customization point tag type.

    This tag type is used by the function
    @ref value_to to select overloads
    of `tag_invoke`.

    @note This type is empty; it has no members.

    @see @ref value_from, @ref value_from_tag, @ref value_to,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1895r0.pdf">
        tag_invoke: A general pattern for supporting customisable functions</a>
*/
template<class T>
struct value_to_tag;

/** Convert a @ref value to an object of type `T`.

    This function attempts to convert a @ref value
    to `T` using

    @li one of @ref value's accessors, or

    @li a library-provided generic conversion, or

    @li a user-provided overload of `tag_invoke`.

    In all cases, the conversion is done by calling
    an overload of `tag_invoke` found by argument-dependent
    lookup. Its signature should be similar to:

    @code
    T tag_invoke( value_to_tag<T>, value );
    @endcode

    The object returned by the function call is
    returned by @ref value_to as the result of the
    conversion.

    @par Constraints
    @code
    ! std::is_reference< T >::value
    @endcode

    @par Exception Safety
    Strong guarantee.

    @tparam T The type to convert to.

    @returns `jv` converted to `T`.

    @param jv The @ref value to convert.

    @see @ref value_to_tag, @ref value_from,
    <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1895r0.pdf">
        tag_invoke: A general pattern for supporting customisable functions</a>
*/
template<class T>
T
value_to(const value& jv)
{
    BOOST_STATIC_ASSERT(! std::is_reference<T>::value);
    return detail::value_to_impl(
        value_to_tag<typename std::remove_cv<T>::type>(), jv);
}

/** Convert a @ref value to an object of type `T`.

    This overload is **deleted** and participates in overload resolution only
    when `U` is not @ref value. The overload exists to prevent unintented
    creation of temporary @ref value instances, e.g.

    @code
    auto flag = value_to<bool>(true);
    @endcode
*/
template<class T, class U
#ifndef BOOST_JSON_DOCS
    , class = typename std::enable_if<!std::is_same<U, value>::value>::type
#endif
>
T
value_to(U const& jv) = delete;

/** Determine a @ref value can be converted to `T`.

    If @ref value can be converted to `T` via a
    call to @ref value_to, the static data member `value`
    is defined as `true`. Otherwise, `value` is
    defined as `false`.

    @see @ref value_to
*/
#ifdef BOOST_JSON_DOCS
template<class T>
using has_value_to = __see_below__;
#else
template<class T, class>
struct has_value_to
    : std::false_type { };

template<class T>
struct has_value_to<T, detail::void_t<decltype(
    detail::value_to_impl(
        value_to_tag<detail::remove_cvref<T>>(),
        std::declval<const value&>())),
    typename std::enable_if<
        ! std::is_reference<T>::value>::type
    > > : std::true_type { };
#endif

BOOST_JSON_NS_END

#endif

/* value_to.hpp
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
*/