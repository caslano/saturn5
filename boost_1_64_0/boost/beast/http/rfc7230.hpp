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
N1rphTdBmbfilIMaCTcgSDn4s5SDRyQf10PL5qOwn3LL/DD72VaetbGj9r0aZsp8LrHzF5gOa6S+PQtnwr9J+a2DhfB5uAi+AC+Em+BVqk775stshtfCl+CNcAt8wLq2lIvX4BPwdfgS3AG3wTfgdvge3A0/gHXwI/gD/BhGWPO7YDT8BCZBdNQ80zfhYPgWHAbfhtlwF8wVvSK4By6BX8DL5PxycVfBL+Gtcn4VfBL+Xdwyj0eeQ5366ZnH08T05WdT2AlGwzQYA/vAFvA4GAczxW3nd7XYzQyS3/0N33zOAbCtdV7q/fGSbwMlfurbFrHTTexEwXSx01fKWz9p946DncUt88/k+YnnMgnvnn+WKPFoI+E7QrXnMxwJU+FcmAYvh13hctgd/h72hPfA3tJe9IHrqRCr+dhsI7IH6XAsc2GQCmQ9UovkcN6aUzSJuURFyNWIa36RmlsUdRLzbhCZYxQwv6gI2ZfunWcU35drwlQYNxwiA/k7C9pzj4qQCmQFstY1F6mmrz0fCVu49yHJzD0agsxA9nF+KXTPT6rE3UvmKS2RuUobkav5+yO4GkYxD2kD3ISk83ct3I8kHuedy1SJTD+OMDAPliM1WaQZcc9v2iRznA645jl1GIlkMN8ITkfS+XsJHAZnIkVIBVLJubWINRdqO6yB+2HyKNz8nQX3QHtu1OUyP2qTdR45kOGbKxWXyf0dHaHmTPXK5JpIHrIUqZQ5VNb8qY0wHb3t8CMkazR6iDWnKqo/9wBZitueX7WCv1cj1hyrcmTTaO9cq8s5N5C//edcVXN+LbIR2YV7n8zB2o67l8zFMph3VQpXIOuRRNzdEHuO1h7XPK2lSKVmvtY23LXIPiRmIPd2LLrIWmSLaz7XMDjJ8keMceSVa37XECRH5nlVI+55Xutx74e7LCLxx1OOkQwkC0kcT1hYigzj75lIOVKBewVci1Tx9562zCNMjjF6IZOQIqQSWYNsQeqQ+HbMA0OmtgvPpQof/39HFDL/lx3/n12cX16QXVR4rpoCcBTmADydajj9qukRsh4D0lG+pUzqY3145vSpjP7V1PEnT8tWschbWOpb7+kfhDYNWU7PvZ6hCjdB+lZsOwPoJ52s9pSu49zIzjzPRKXGRUc3j2s+vnn35l0Y8o6M9PQLydrczjWyrSEDuU4SzFB2p7n0zi0qmX1ethqVc40L9lR6OUaC0pM1w7K9e7GkKp0ipXObelF10uWsOTxUrmeNozfUD5Qk/UDcI/qBxJZff/Z2ue+p0mfWFnmOa68Net9VR5/Ez3vf5T5LuFTnHubGN7zWtB1PbAbEc5TEc4nMEWniKu9tKR+1weM5N79c1s3WlBOJr4RvIuuA1R/HGM29HC5xTI4KjGMycazTx1F1UuvjR9ijEL+xEr+aIPFrZ9Wxrdr45ZU4S1XWex+xceTxnCDxLGoSGM8U4hmvjaeS3LL5mdmluQtyi8vqj2v8UYirnedxTQPj2p64purjqoYn9fEj7FGIn30vNzQNfi8z9PEra8y9zDgKcbXbomHyaHaKzAsZgbxIm5AVPK504tffPicYdtjOTjucrdx96m2vj3HCdXTa5nOUO1PbfifCs5VOb1mr07bRvt72fIFcx/nNCWEcJEXaSxnv8aQ7xTMW5E1bkmdMSOLv1852kHkSzeSClrOjtd5i8Dwo87Sz+t8FCd9M6bRRa2xKMGcs09EJuSx5fi/kvBUQ+5wX+371tS5I+jqTvhpt+qSN1qdNwjZT4zztVdpUkEPj00eYrgRJV3uVLmXb065vbxaYplewsU2bJm+7rk+b2JB8S1Bpc4JK+tA5wvTZ+Zag0ufY95TLNc0lbWJQtSU=
*/