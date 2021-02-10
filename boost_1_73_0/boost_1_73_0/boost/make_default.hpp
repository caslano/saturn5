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
SnyvRIkyT0CJ8VYSlpSwStoFxVqYARwiKQFDDzl1lf40MyKxQaG5dJknniOP/FRsjaFSFFMVdJYKquHJsK0iZ/se2yQG3E7Ii6rUIeMh9NTepVbl2epEFUoAmV9VqXDRJ2teRBH1eoA+O/qgXmgS4v2o4mgg6WBfcOP00LDMS9b4IokWMkOF9yes5DbrNuRv3dLbaentbJ2slPJHusSqGOb6gL87lgmCkh1wH812052uAd1wN93ZGmauOd+lOYYSUwN4F+OEKQXa0SYl7ViCFAOAZPTIKu/Po0u1by3zOrk/Vz15iXmMOWdNipM3U4kgRUc+Zv+yOcYf94LKghVLdl+D4/1JHhal0CklM0tWlows2tguDlZib2zEROt9FLuMgRvOSVnRfkzdIlN3T6bTItPpnkxnRaazfZgmmv4xY6oHQuzYxAkn+08YRWMZfbq5727FtnSHKHZImyWNlaaNhiyxwRFg2eDNEZwL7VeYaNdDtaeB8lvzH7+1/3nYaouv6v+vcKe6uztRoOoocv9NEd6iLha9ValcXfeZ6rYqlas7fRF1EqVydWcvqK6kVKIuXRB16rLMdEtMq03e0lh8rurq0NAmE8z/lJ7peX6IVS2VzYG/otKX8uekPKccSURjINHlOir1X6ncG08c
*/