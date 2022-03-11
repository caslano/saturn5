//-----------------------------------------------------------------------------
// boost detail/reference_content.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_REFERENCE_CONTENT_HPP
#define BOOST_DETAIL_REFERENCE_CONTENT_HPP

#include "boost/config.hpp"

#   include "boost/type_traits/integral_constant.hpp"
#   include "boost/type_traits/has_nothrow_copy.hpp"

namespace boost {

namespace detail {

struct void_type {};

///////////////////////////////////////////////////////////////////////////////
// (detail) class template reference_content
//
// Non-Assignable wrapper for references.
//
template <typename RefT>
class reference_content
{
private: // representation

    RefT content_;

public: // structors

    ~reference_content()
    {
    }

    reference_content(RefT r)
        : content_( r )
    {
    }

    reference_content(const reference_content& operand)
        : content_( operand.content_ )
    {
    }

private: // non-Assignable

    reference_content& operator=(const reference_content&);

public: // queries

    RefT get() const
    {
        return content_;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction make_reference_content
//
// Wraps with reference_content if specified type is reference.
//

template <typename T = void_type> struct make_reference_content;


template <typename T>
struct make_reference_content
{
    typedef T type;
};

template <typename T>
struct make_reference_content< T& >
{
    typedef reference_content<T&> type;
};


template <>
struct make_reference_content< void_type >
{
    template <typename T>
    struct apply
        : make_reference_content<T>
    {
    };

    typedef void_type type;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// reference_content<T&> type traits specializations
//


template <typename T>
struct has_nothrow_copy<
      ::boost::detail::reference_content< T& >
    >
    : boost::true_type
{
};


} // namespace boost

#endif // BOOST_DETAIL_REFERENCE_CONTENT_HPP

/* reference_content.hpp
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
*/