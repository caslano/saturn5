//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_IOSTREAM_HPP_INCLUDED
#define BOOST_NOWIDE_IOSTREAM_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#ifdef BOOST_WINDOWS
#include <boost/scoped_ptr.hpp>
#include <istream>
#include <ostream>

#include <boost/config/abi_prefix.hpp> // must be the last #include
#else
#include <iostream>
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::cout;
    using std::cerr;
    using std::cin;
    using std::clog;
#else

    /// \cond INTERNAL
    namespace detail {
        class console_output_buffer;
        class console_input_buffer;

        class BOOST_NOWIDE_DECL winconsole_ostream : public std::ostream
        {
            winconsole_ostream(const winconsole_ostream&);
            void operator=(const winconsole_ostream&);

        public:
            winconsole_ostream(int fd, winconsole_ostream* tieStream);
            ~winconsole_ostream();

        private:
            boost::scoped_ptr<console_output_buffer> d;
        };

        class BOOST_NOWIDE_DECL winconsole_istream : public std::istream
        {
            winconsole_istream(const winconsole_istream&);
            void operator=(const winconsole_istream&);

        public:
            explicit winconsole_istream(winconsole_ostream* tieStream);
            ~winconsole_istream();

        private:
            boost::scoped_ptr<console_input_buffer> d;
        };
    } // namespace detail

    /// \endcond

    ///
    /// \brief Same as std::cin, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_istream cin;
    ///
    /// \brief Same as std::cout, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_ostream cout;
    ///
    /// \brief Same as std::cerr, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_ostream cerr;
    ///
    /// \brief Same as std::clog, but uses UTF-8
    ///
    /// Note, the stream is not synchronized with stdio and not affected by std::ios::sync_with_stdio
    ///
    extern BOOST_NOWIDE_DECL detail::winconsole_ostream clog;

#endif

} // namespace nowide
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#ifdef BOOST_WINDOWS
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif

#endif

/* iostream.hpp
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
*/