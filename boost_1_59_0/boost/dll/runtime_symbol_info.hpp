// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_RUNTIME_SYMBOL_INFO_HPP
#define BOOST_DLL_RUNTIME_SYMBOL_INFO_HPP

#include <boost/dll/config.hpp>
#include <boost/predef/os.h>
#include <boost/predef/compiler/visualc.h>
#include <boost/dll/detail/aggressive_ptr_cast.hpp>
#if BOOST_OS_WINDOWS
#   include <boost/winapi/dll.hpp>
#   include <boost/dll/detail/windows/path_from_handle.hpp>
#else
#   include <dlfcn.h>
#   include <boost/dll/detail/posix/program_location_impl.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

/// \file boost/dll/runtime_symbol_info.hpp
/// \brief Provides methods for getting acceptable by boost::dll::shared_library location of symbol, source line or program.
namespace boost { namespace dll {

#if BOOST_OS_WINDOWS
namespace detail {
    inline boost::dll::fs::path program_location_impl(boost::dll::fs::error_code& ec) {
        return boost::dll::detail::path_from_handle(NULL, ec);
    }
} // namespace detail
#endif

    /*!
    * On success returns full path and name to the binary object that holds symbol pointed by ptr_to_symbol.
    *
    * \param ptr_to_symbol Pointer to symbol which location is to be determined.
    * \param ec Variable that will be set to the result of the operation.
    * \return Path to the binary object that holds symbol or empty path in case error.
    * \throws std::bad_alloc in case of insufficient memory. Overload that does not accept \forcedlinkfs{error_code} also throws \forcedlinkfs{system_error}.
    *
    * \b Examples:
    * \code
    * int main() {
    *    dll::symbol_location_ptr(std::set_terminate(0));       // returns "/some/path/libmy_terminate_handler.so"
    *    dll::symbol_location_ptr(::signal(SIGSEGV, SIG_DFL));  // returns "/some/path/libmy_symbol_handler.so"
    * }
    * \endcode
    */
    template <class T>
    inline boost::dll::fs::path symbol_location_ptr(T ptr_to_symbol, boost::dll::fs::error_code& ec) {
        BOOST_STATIC_ASSERT_MSG(boost::is_pointer<T>::value, "boost::dll::symbol_location_ptr works only with pointers! `ptr_to_symbol` must be a pointer");
        boost::dll::fs::path ret;
        if (!ptr_to_symbol) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_address
            );

            return ret;
        }
        ec.clear();

        const void* ptr = boost::dll::detail::aggressive_ptr_cast<const void*>(ptr_to_symbol);

#if BOOST_OS_WINDOWS
        boost::winapi::MEMORY_BASIC_INFORMATION_ mbi;
        if (!boost::winapi::VirtualQuery(ptr, &mbi, sizeof(mbi))) {
            ec = boost::dll::detail::last_error_code();
            return ret;
        }

        return boost::dll::detail::path_from_handle(reinterpret_cast<boost::winapi::HMODULE_>(mbi.AllocationBase), ec);
#else
        Dl_info info;

        // Some of the libc headers miss `const` in `dladdr(const void*, Dl_info*)`
        const int res = dladdr(const_cast<void*>(ptr), &info);

        if (res) {
            ret = info.dli_fname;
        } else {
            boost::dll::detail::reset_dlerror();
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_address
            );
        }

        return ret;
#endif
    }

    //! \overload symbol_location_ptr(const void* ptr_to_symbol, boost::dll::fs::error_code& ec)
    template <class T>
    inline boost::dll::fs::path symbol_location_ptr(T ptr_to_symbol) {
        boost::dll::fs::path ret;
        boost::dll::fs::error_code ec;
        ret = boost::dll::symbol_location_ptr(ptr_to_symbol, ec);

        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::symbol_location_ptr(T ptr_to_symbol) failed");
        }

        return ret;
    }

    /*!
    * On success returns full path and name of the binary object that holds symbol.
    *
    * \tparam T Type of the symbol, must not be explicitly specified.
    * \param symbol Symbol which location is to be determined.
    * \param ec Variable that will be set to the result of the operation.
    * \return Path to the binary object that holds symbol or empty path in case error.
    * \throws std::bad_alloc in case of insufficient memory. Overload that does not accept \forcedlinkfs{error_code} also throws \forcedlinkfs{system_error}.
    *
    * \b Examples:
    * \code
    * int var;
    * void foo() {}
    *
    * int main() {
    *    dll::symbol_location(var);                     // returns program location
    *    dll::symbol_location(foo);                     // returns program location
    *    dll::symbol_location(std::cerr);               // returns location of libstdc++: "/usr/lib/x86_64-linux-gnu/libstdc++.so.6"
    *    dll::symbol_location(std::placeholders::_1);   // returns location of libstdc++: "/usr/lib/x86_64-linux-gnu/libstdc++.so.6"
    *    dll::symbol_location(std::puts);               // returns location of libc: "/lib/x86_64-linux-gnu/libc.so.6"
    * }
    * \endcode
    */
    template <class T>
    inline boost::dll::fs::path symbol_location(const T& symbol, boost::dll::fs::error_code& ec) {
        ec.clear();
        return boost::dll::symbol_location_ptr(
            boost::dll::detail::aggressive_ptr_cast<const void*>(boost::addressof(symbol)),
            ec
        );
    }

#if BOOST_COMP_MSVC < BOOST_VERSION_NUMBER(14,0,0)
    // Without this MSVC 7.1 fails with:
    //  ..\boost\dll\runtime_symbol_info.hpp(133) : error C2780: 'filesystem::path dll::symbol_location(const T &)' : expects 1 arguments - 2 provided
    template <class T>
    inline boost::dll::fs::path symbol_location(const T& symbol, const char* /*workaround*/ = 0)
#else
    //! \overload symbol_location(const T& symbol, boost::dll::fs::error_code& ec)
    template <class T>
    inline boost::dll::fs::path symbol_location(const T& symbol)
#endif
    {
        boost::dll::fs::path ret;
        boost::dll::fs::error_code ec;
        ret = boost::dll::symbol_location_ptr(
            boost::dll::detail::aggressive_ptr_cast<const void*>(boost::addressof(symbol)),
            ec
        );

        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::symbol_location(const T& symbol) failed");
        }

        return ret;
    }

    /// @cond
    // We have anonymous namespace here to make sure that `this_line_location()` method is instantiated in
    // current translation unit and is not shadowed by instantiations from other units.
    //
    // boost-no-inspect
    namespace {
    /// @endcond

    /*!
    * On success returns full path and name of the binary object that holds the current line of code
    * (the line in which the `this_line_location()` method was called).
    *
    * \param ec Variable that will be set to the result of the operation.
    * \throws std::bad_alloc in case of insufficient memory. Overload that does not accept \forcedlinkfs{error_code} also throws \forcedlinkfs{system_error}.
    */
    static inline boost::dll::fs::path this_line_location(boost::dll::fs::error_code& ec) {
        typedef boost::dll::fs::path(func_t)(boost::dll::fs::error_code& );
        func_t& f = this_line_location;
        return boost::dll::symbol_location(f, ec);
    }

    //! \overload this_line_location(boost::dll::fs::error_code& ec)
    static inline boost::dll::fs::path this_line_location() {
        boost::dll::fs::path ret;
        boost::dll::fs::error_code ec;
        ret = this_line_location(ec);

        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::this_line_location() failed");
        }

        return ret;
    }

    /// @cond
    } // anonymous namespace
    /// @endcond

    /*!
    * On success returns full path and name of the currently running program (the one which contains the `main()` function).
    * 
    * Return value can be used as a parameter for shared_library. See Tutorial "Linking plugin into the executable"
    * for usage example. Flag '-rdynamic' must be used when linking the plugin into the executable
    * on Linux OS.
    *
    * \param ec Variable that will be set to the result of the operation.
    * \throws std::bad_alloc in case of insufficient memory. Overload that does not accept \forcedlinkfs{error_code} also throws \forcedlinkfs{system_error}.
    */
    inline boost::dll::fs::path program_location(boost::dll::fs::error_code& ec) {
        ec.clear();
        return boost::dll::detail::program_location_impl(ec);
    }

    //! \overload program_location(boost::dll::fs::error_code& ec) {
    inline boost::dll::fs::path program_location() {
        boost::dll::fs::path ret;
        boost::dll::fs::error_code ec;
        ret = boost::dll::detail::program_location_impl(ec);

        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::program_location() failed");
        }

        return ret;
    }

}} // namespace boost::dll

#endif // BOOST_DLL_RUNTIME_SYMBOL_INFO_HPP


/* runtime_symbol_info.hpp
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
*/