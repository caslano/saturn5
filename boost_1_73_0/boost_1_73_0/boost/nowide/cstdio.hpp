//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDIO_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDIO_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <cstdio>

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::fopen;
    using std::freopen;
    using std::remove;
    using std::rename;
#else

    ///
    /// \brief Same as freopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* freopen(const char* file_name, const char* mode, FILE* stream);
    ///
    /// \brief Same as fopen but file_name and mode are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL FILE* fopen(const char* file_name, const char* mode);
    ///
    /// \brief Same as rename but old_name and new_name are UTF-8 strings
    ///
    BOOST_NOWIDE_DECL int rename(const char* old_name, const char* new_name);
    ///
    /// \brief Same as rename but name is UTF-8 string
    ///
    BOOST_NOWIDE_DECL int remove(const char* name);
#endif
    namespace detail {
        BOOST_NOWIDE_DECL FILE* wfopen(const wchar_t* filename, const wchar_t* mode);
    }
} // namespace nowide
} // namespace boost

#endif

/* cstdio.hpp
wa8aeueePatG1b3ywA8fPzR52WzG/kLwxxa4Pztx8ezX7uh5e18kJ/ISY0o+wh+572HHuvy8kzWROdva35kT5i8kteQ8dLBw3g15nq9rLyp8+r8uens/Y7sIfuJ/9xTcfe3aLbV/OB6OLZt4iLGB/RB++a6rH7IcHPGLRdd/+M+tXzTcx9h0gj/5348d/Gp07dW/rU6+/HzVc5uBPwQ/uqn03ul720+s/eSh/7z+oQt/ydg2gqdHbTy29tJ7Lrs=
*/