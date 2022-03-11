// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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