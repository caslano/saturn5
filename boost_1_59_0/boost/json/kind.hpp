//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_KIND_HPP
#define BOOST_JSON_KIND_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/string_view.hpp>
#include <iosfwd>

BOOST_JSON_NS_BEGIN

/** Constants for identifying the type of a value

    These values are returned from @ref value::kind
*/
// Order matters
enum class kind : unsigned char
{
    /// The null value.
    null,

    /// A `bool`.
    bool_,

    /// A `std::int64_t`
    int64,

    /// A `std::uint64_t`
    uint64,

    /// A `double`.
    double_,

    /// A @ref string.
    string,

    /// An @ref array.
    array,

    /// An @ref object.
    object
};

/** Return a string representing a kind.

    This provides a human-readable string
    representing a @ref kind. This may be
    useful for diagnostics.

    @returns The string.

    @param k The kind.
*/
BOOST_JSON_DECL
string_view
to_string(kind k) noexcept;

/** Format a kind to an output stream.

    This allows a @ref kind to be formatted as
    a string, typically for diagnostics.

    @returns The output stream.

    @param os The output stream to format to.

    @param k The kind to format.
*/
BOOST_JSON_DECL
std::ostream&
operator<<(std::ostream& os, kind k);

/** A tag type used to select a @ref value constructor overload.

    The library provides the constant @ref array_kind
    which may be used to select the @ref value constructor
    that creates an empty @ref array.

    @see @ref array_kind
*/
struct array_kind_t
{
};

/** A tag type used to select a @ref value constructor overload.

    The library provides the constant @ref object_kind
    which may be used to select the @ref value constructor
    that creates an empty @ref object.

    @see @ref object_kind
*/
struct object_kind_t
{
};

/** A tag type used to select a @ref value constructor overload.

    The library provides the constant @ref string_kind
    which may be used to select the @ref value constructor
    that creates an empty @ref string.

    @see @ref string_kind
*/
struct string_kind_t
{
};

/** A constant used to select a @ref value constructor overload.

    The library provides this constant to allow efficient
    construction of a @ref value containing an empty @ref array.

    @par Example
    @code
    storage_ptr sp;
    value jv( array_kind, sp ); // sp is an optional parameter
    @endcode

    @see @ref array_kind_t
*/
BOOST_JSON_INLINE_VARIABLE(array_kind, array_kind_t);

/** A constant used to select a @ref value constructor overload.

    The library provides this constant to allow efficient
    construction of a @ref value containing an empty @ref object.

    @par Example
    @code
    storage_ptr sp;
    value jv( object_kind, sp ); // sp is an optional parameter
    @endcode

    @see @ref object_kind_t
*/
BOOST_JSON_INLINE_VARIABLE(object_kind, object_kind_t);

/** A constant used to select a @ref value constructor overload.

    The library provides this constant to allow efficient
    construction of a @ref value containing an empty @ref string.

    @par Example
    @code
    storage_ptr sp;
    value jv( string_kind, sp ); // sp is an optional parameter
    @endcode

    @see @ref string_kind_t
*/
BOOST_JSON_INLINE_VARIABLE(string_kind, string_kind_t);

BOOST_JSON_NS_END

#endif

/* kind.hpp
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
*/