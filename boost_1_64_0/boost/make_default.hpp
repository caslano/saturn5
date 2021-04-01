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
g5Gv9jyQ0ITuUCPWCCVFYatw5XXNonmBhAaqWaRvUz0JUVpUQydPLzzs0FK47FGEbZ31X9hvB4tv+pU8C0bOUQq88ubw80l1Swg7iAm1e8NMrsRzanNXOOnOYj45YxZ069W6fqCEsWJRdrvHl8uvbYJq7XbDboE0ST68QcjzewgmQZLBGOL3ilRZ11nV44unRJKCAjYByw/kwEgOg+voS/c+izSXMxX/M6iSxJWkqQ+ZQ+oanivpsSk5/NfeO4MqNFQKj3yPt73f9mlwR3QSVrE8oDDyDYAdU/uQTC3eNCR+2RReH7b05T9S+nZ2bDFiKPcOeXnDR0w/u7/WcsbPMuZmc33oQMIv4KO150d+JdJTYnS+1DFVDB+ar56tEI1f21MIQjnPh7xwsQg3/RCGDRY8uYtDA5dI3+R7ReGjCAZehKX1SZVTCE/wF9gKb0U5y23Kz70FKPNdcCaGLZy7rCTlWNgDiiWwW5RUhUR/16IvKpmECzN26UrauO/KBwE3vzMzEfXwRJ4Q7e5h5AugnE/bS2YLXxcrwgZ3+i4DNc7QOooR0IifKCqhjA==
*/