/// @file
// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_MAKE_DEFAULT_HPP
#define BOOST_MAKE_DEFAULT_HPP

namespace boost
{
    /// @details A considerable number of libraries require an instance of a class
    /// provided (storage created and initialized). For example,
    /// @code
    ///    Type result;
    ///    ...
    ///    istream >> result;
    /// @endcode
    /// In generic code that results in the Default Constructibility requirement imposed
    /// on every type 'Type' to be used with the respective code. Inevitably, that requirement
    /// a) either excludes all the classes that for various reasons do not meet that requirement or
    /// b) imposes certain (not necessarily desirable) design/implementation onto respective classes.
    ///
    /// Deployment of boost::make_default() eliminates the Default Constructibility requirement with
    /// @code
    ///    Type result = boost::make_default<Type>();
    ///    ...
    ///    istream >> result;
    /// @endcode
    /// Classes with no default constructor can now be included via a boost::make_default() specialization:
    /// @code
    /// namespace boost
    /// {
    ///     template<> inline Type make_default<Type>() { return Type(parameters); }
    /// }
    /// @endcode

    template<typename T> T make_default() { return T(); }
}

#endif // BOOST_MAKE_DEFAULT_HPP

/* make_default.hpp
jU3EvcR55NMl4hTymT7iAHJTJ/EE0tFG7EaWtBA7kKVNxH3EDHLzJuI00rmWeA65ZTGxG+lqJh4gLiGfLROvIt0jxDHk1h7iSaSnldiJfG4+cR9xAVlWJE4jn+8nDiLLu4i9yBeuIu4jZpDeLcQJZEUfsQ9Z2U7sQVa1ENuJi8jqAvEysqaHeBZZu4jYScwiXxwlXkH6VhLPI+vaiAeI80j/CHEEua2XeA5Z307sQW5vIbYT55CBInEc2bCceBI=
*/