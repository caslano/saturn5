//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_convert
{
    invoked_convert(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref convert function converts its argument to type \c T (similar to
/// static_cast<T>).
///
/// \see \ref as "as<T>"
template<class T>
struct convert
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_convert<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_convert<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

/* convert.hpp
fqzEzR0fZakDY71bSkYLf+zFz6ciTxqE5wYJqrAV7qP4SZE0r3WddlJlevBR7PV5ZFwog5rKFOhYdG0JTH5Yu9/kvuE9JXvj9CFUfZMTXKTK6CVpioJjkG2+t484xpozUNAIMGT9KhaNoy9zsY+4hcYWKFCmP53apM8dj4rGdG9FhOsZtolc4VXmhVO6VUAo22o8WYAojn6APz1MNTPqZbbPubVVHQuD2mgMyCLZIBVY853V878ci2uloNCuF4k9L5KiPL4YdSc5/6Xh4iaBb7BZIZ6sTxiCYz/lj/si0gUNQfHMabvEPsIGnFidup67UZhk3g6NnVdbAr9xR2plL78YFCG4Niqo42kCsuNcZVocZbvJUM77HjsxeBBnKugYoJHcDuSUnhuMM/w47dUXYGj/HODtpZxxmQzBAsgALWjLTTP30xpi9jDiXvfYMKxTrD8tXDMCjuVEL9dotwuRIcr/xcvQG6crEO+zGb3GaIZ7JJz7if772KPDWz6s6AlSxK6w0C4x4UoztkT7rza+qnWusVAY4MSk3i9UGq+lmJBkW2pcr/P3WxRq7A==
*/