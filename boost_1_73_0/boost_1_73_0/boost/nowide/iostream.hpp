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
XN2F8IE5y68VfXwca/5LCNwArccDVF4JDVqW5oEqDvhci4I3mjOgGhjXhRJrXIgGTMWhFDWHWXZ1s0g/hvBQiaKyIFvZga5kVzOo6D0HxQsu7nuMlioDssRwBGdCGwTsjJDNGHNzMFxttMWw6WmtJdB7Kmq6xkTUQGVMq0+jqOhUjewjJgsdFbvyx5XZPFdygyQ2dAuyNWAkdJqHYD1D2EgmSjujIGhsu3UtdBXu2WCqhkVSgeZ1bbEwTnDd0+awGuQJrRu0yFgYO2nZaJvqoZKbfziijhal7FSDiVAHdGISZQ6haxhXztlVvksxaOoEfrU1e74MZINkYBSvYLEawZpqoUP4vMh/y65z+Bwvl3Ga30B2AXF6Y8EuF+k5tl5gMgX8sVVcY3IFYtPWgrMh5/cbkef9IJqi7hiHkeEaezU6NG34hvF1d+fM2lAjCrBNJloWf3FDcM+0uA/dwr+XgsFJgUQb04bet+8AcDg20mxbjt1WrcS9cDQKte3wongmQRlTcGL/UarA+4IAjkgwIE6fDYPP3jAwtYayVaIxpa8N9l2FMDooK8CDYnCPaJhdLxOyymaX85ycxee3zSiwwf3rf7+del89D0HByuoXFUWa6NFTtL4oFRYBP0N6nSTTwVhIZg+mRrNdzslF
*/