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

#if defined(BOOST_BEAST_ALLOW_DEPRECATED) && !defined(BOOST_BEAST_DOXYGEN)


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

#endif // defined(BOOST_BEAST_ALLOW_DEPRECATED) && !BOOST_BEAST_DOXYGEN

#endif

/* string_param.hpp
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
*/