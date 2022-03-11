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