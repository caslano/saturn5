//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_PARAM_HPP
#define BOOST_BEAST_STRING_PARAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/detail/static_ostream.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {

/** A function parameter which efficiently converts to string.

    This is used as a function parameter type to allow callers
    notational convenience: objects other than strings may be
    passed in contexts where a string is expected. The conversion
    to string is made using `operator<<` to a non-dynamically
    allocated static buffer if possible, else to a `std::string`
    on overflow.

    To use it, modify your function signature to accept
    `string_param` and then extract the string inside the
    function:
    @code
    void print(string_param s)
    {
        std::cout << s.str();
    }
    @endcode
*/
class string_param
{
    string_view sv_;
    char buf_[128];
    boost::optional<detail::static_ostream> os_;

    template<class T>
    typename std::enable_if<
        std::is_integral<T>::value>::type
    print(T const&);

    template<class T>
    typename std::enable_if<
        ! std::is_integral<T>::value &&
        ! std::is_convertible<T, string_view>::value
    >::type
    print(T const&);

    void
    print(string_view);

    template<class T>
    typename std::enable_if<
        std::is_integral<T>::value>::type
    print_1(T const&);

    template<class T>
    typename std::enable_if<
        ! std::is_integral<T>::value>::type
    print_1(T const&);

    void
    print_n()
    {
    }

    template<class T0, class... TN>
    void
    print_n(T0 const&, TN const&...);

    template<class T0, class T1, class... TN>
    void
    print(T0 const&, T1 const&, TN const&...);

public:
    /// Copy constructor (disallowed)
    string_param(string_param const&) = delete;

    /// Copy assignment (disallowed)
    string_param& operator=(string_param const&) = delete;

    /** Constructor

        This function constructs a string as if by concatenating
        the result of streaming each argument in order into an
        output stream. It is used as a notational convenience
        at call sites which expect a parameter with the semantics
        of a @ref string_view.

        The implementation uses a small, internal static buffer
        to avoid memory allocations especially for the case where
        the list of arguments to be converted consists of a single
        integral type.

        @param args One or more arguments to convert
    */
    template<class... Args>
    string_param(Args const&... args);

    /// Returns the contained string
    string_view
    str() const
    {
        return sv_;
    }

    /// Implicit conversion to @ref string_view
    operator string_view const() const
    {
        return sv_;
    }
};

} // beast
} // boost

#include <boost/beast/core/impl/string_param.hpp>

#endif

/* string_param.hpp
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
*/