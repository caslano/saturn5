//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_RFC7230_HPP
#define BOOST_BEAST_HTTP_RFC7230_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/http/detail/rfc7230.hpp>
#include <boost/beast/http/detail/basic_parsed_list.hpp>

namespace boost {
namespace beast {
namespace http {

/** A list of parameters in an HTTP extension field value.

    This container allows iteration of the parameter list in an HTTP
    extension. The parameter list is a series of name/value pairs
    with each pair starting with a semicolon. The value is optional.

    If a parsing error is encountered while iterating the string,
    the behavior of the container will be as if a string containing
    only characters up to but excluding the first invalid character
    was used to construct the list.

    @par BNF
    @code
        param-list  = *( OWS ";" OWS param )
        param       = token OWS [ "=" OWS ( token / quoted-string ) ]
    @endcode

    To use this class, construct with the string to be parsed and
    then use @ref begin and @ref end, or range-for to iterate each
    item:

    @par Example
    @code
    for(auto const& param : param_list{";level=9;no_context_takeover;bits=15"})
    {
        std::cout << ";" << param.first;
        if(! param.second.empty())
            std::cout << "=" << param.second;
        std::cout << "\n";
    }
    @endcode
*/
class param_list
{
    string_view s_;

public:
    /** The type of each element in the list.

        The first string in the pair is the name of the parameter,
        and the second string in the pair is its value (which may
        be empty).
    */
    using value_type =
        std::pair<string_view, string_view>;

    /// A constant iterator to the list
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    class const_iterator;
#endif

    /// Default constructor.
    param_list() = default;

    /** Construct a list.

        @param s A string containing the list contents. The string
        must remain valid for the lifetime of the container.
    */
    explicit
    param_list(string_view s)
        : s_(s)
    {
    }

    /// Return a const iterator to the beginning of the list
    const_iterator begin() const;

    /// Return a const iterator to the end of the list
    const_iterator end() const;

    /// Return a const iterator to the beginning of the list
    const_iterator cbegin() const;

    /// Return a const iterator to the end of the list
    const_iterator cend() const;
};

//------------------------------------------------------------------------------

/** A list of extensions in a comma separated HTTP field value.

    This container allows iteration of the extensions in an HTTP
    field value. The extension list is a comma separated list of
    token parameter list pairs.

    If a parsing error is encountered while iterating the string,
    the behavior of the container will be as if a string containing
    only characters up to but excluding the first invalid character
    was used to construct the list.

    @par BNF
    @code
        ext-list    = *( "," OWS ) ext *( OWS "," [ OWS ext ] )
        ext         = token param-list
        param-list  = *( OWS ";" OWS param )
        param       = token OWS [ "=" OWS ( token / quoted-string ) ]
    @endcode

    To use this class, construct with the string to be parsed and
    then use @ref begin and @ref end, or range-for to iterate each
    item:

    @par Example
    @code
    for(auto const& ext : ext_list{"none, 7z;level=9, zip;no_context_takeover;bits=15"})
    {
        std::cout << ext.first << "\n";
        for(auto const& param : ext.second)
        {
            std::cout << ";" << param.first;
            if(! param.second.empty())
                std::cout << "=" << param.second;
            std::cout << "\n";
        }
    }
    @endcode
*/
class ext_list
{
    using iter_type = string_view::const_iterator;

    string_view s_;

public:
    /** The type of each element in the list.

        The first element of the pair is the extension token, and the
        second element of the pair is an iterable container holding the
        extension's name/value parameters.
    */
    using value_type = std::pair<string_view, param_list>;

    /// A constant iterator to the list
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    class const_iterator;
#endif

    /** Construct a list.

        @param s A string containing the list contents. The string
        must remain valid for the lifetime of the container.
    */
    explicit
    ext_list(string_view s)
        : s_(s)
    {
    }

    /// Return a const iterator to the beginning of the list
    const_iterator begin() const;

    /// Return a const iterator to the end of the list
    const_iterator end() const;

    /// Return a const iterator to the beginning of the list
    const_iterator cbegin() const;

    /// Return a const iterator to the end of the list
    const_iterator cend() const;

    /** Find a token in the list.

        @param s The token to find. A case-insensitive comparison is used.

        @return An iterator to the matching token, or `end()` if no
        token exists.
    */
    BOOST_BEAST_DECL
    const_iterator
    find(string_view const& s);

    /** Return `true` if a token is present in the list.

        @param s The token to find. A case-insensitive comparison is used.
    */
    BOOST_BEAST_DECL
    bool
    exists(string_view const& s);
};

//------------------------------------------------------------------------------

/** A list of tokens in a comma separated HTTP field value.

    This container allows iteration of a list of items in a
    header field value. The input is a comma separated list of
    tokens.

    If a parsing error is encountered while iterating the string,
    the behavior of the container will be as if a string containing
    only characters up to but excluding the first invalid character
    was used to construct the list.

    @par BNF
    @code
        token-list  = *( "," OWS ) token *( OWS "," [ OWS token ] )
    @endcode

    To use this class, construct with the string to be parsed and
    then use @ref begin and @ref end, or range-for to iterate each
    item:

    @par Example
    @code
    for(auto const& token : token_list{"apple, pear, banana"})
        std::cout << token << "\n";
    @endcode
*/
class token_list
{
    using iter_type = string_view::const_iterator;

    string_view s_;

public:
    /// The type of each element in the token list.
    using value_type = string_view;

    /// A constant iterator to the list
#if BOOST_BEAST_DOXYGEN
    using const_iterator = __implementation_defined__;
#else
    class const_iterator;
#endif

    /** Construct a list.

        @param s A string containing the list contents. The string
        must remain valid for the lifetime of the container.
    */
    explicit
    token_list(string_view s)
        : s_(s)
    {
    }

    /// Return a const iterator to the beginning of the list
    const_iterator begin() const;

    /// Return a const iterator to the end of the list
    const_iterator end() const;

    /// Return a const iterator to the beginning of the list
    const_iterator cbegin() const;

    /// Return a const iterator to the end of the list
    const_iterator cend() const;

    /** Return `true` if a token is present in the list.

        @param s The token to find. A case-insensitive comparison is used.
    */
    BOOST_BEAST_DECL
    bool
    exists(string_view const& s);
};

/** A list of tokens in a comma separated HTTP field value.

    This container allows iteration of a list of items in a
    header field value. The input is a comma separated list of
    tokens.

    If a parsing error is encountered while iterating the string,
    the behavior of the container will be as if a string containing
    only characters up to but excluding the first invalid character
    was used to construct the list.

    @par BNF
    @code
        token-list  = *( "," OWS ) token *( OWS "," [ OWS token ] )
    @endcode

    To use this class, construct with the string to be parsed and
    then use `begin` and `end`, or range-for to iterate each item:

    @par Example
    @code
    for(auto const& token : token_list{"apple, pear, banana"})
        std::cout << token << "\n";
    @endcode
*/
using opt_token_list =
    detail::basic_parsed_list<
        detail::opt_token_list_policy>;

/** Returns `true` if a parsed list is parsed without errors.

    This function iterates a single pass through a parsed list
    and returns `true` if there were no parsing errors, else
    returns `false`.
*/
template<class Policy>
bool
validate_list(detail::basic_parsed_list<
    Policy> const& list);

} // http
} // beast
} // boost

#include <boost/beast/http/impl/rfc7230.hpp>

#endif

/* rfc7230.hpp
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
*/