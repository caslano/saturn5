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
rFien0mtD3ekYB6AO9Gu3LHyzCScYuUYu0JnLXK8y0YvfL1SmLIAho7y74wcRwnCwOG5p4H9zIVrwUbLZR3NQMsKKCPNfZUw1xfNU4wpwHQnrFPk+cTA/hC9GfcuVmRlUr/CDyqMjuQrUfXkpme9qF7M04qfj5WwtT2U/rT+WHxE/jTf40ip8LWaFMhBMLWVtsxeGL9LVjYSd3F6k8BzaECtKOU2QuRFsWfHiH2KJ1BJCBjRjvgJbDsuu6n7t4LE3MyJMeT1QH4TXukaeN8MTErEX+Rmozrki9TGiDxyjnmMVt+H66b86RFgFbu2WB7qcKQgplORIUWBEuQv8da8dK/M1GnWzhJ8T75+ic79sQ+rDqM/NCHxphMvsV/2/hXl2KMGr+L3z8yGE9OLlpD8ckjtZji7XYcJtkypSPwD/NgeOz+ZaYeC0OpV2d6WI6pmu56LQ7LHkP8GBuuAytBcb5iRP8RadUJhI366d+SSdo2oEvzlW4RW0cnlbkK6EMtgFQteT3e4Vp/Csw2FJJTT0EMQEpQJ2V7bwOJEkIEu1uAXrXr7X8sUciyDqQ==
*/