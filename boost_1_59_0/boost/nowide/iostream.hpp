//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020-2021 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NOWIDE_IOSTREAM_HPP_INCLUDED
#define BOOST_NOWIDE_IOSTREAM_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#ifdef BOOST_WINDOWS
#include <istream>
#include <memory>
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
        public:
            winconsole_ostream(bool isBuffered, winconsole_ostream* tieStream);
            ~winconsole_ostream();

        private:
            std::unique_ptr<console_output_buffer> d;
            // Ensure the std streams are initialized and alive during the lifetime of this instance
            std::ios_base::Init init_;
        };

        class BOOST_NOWIDE_DECL winconsole_istream : public std::istream
        {
        public:
            explicit winconsole_istream(winconsole_ostream* tieStream);
            ~winconsole_istream();

        private:
            std::unique_ptr<console_input_buffer> d;
            // Ensure the std streams are initialized and alive during the lifetime of this instance
            std::ios_base::Init init_;
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