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
6TwZ6aRUdtVEDBM1DPcThr8Tho3wJ7QLJmiZyq6yAp4ixoVoKBoi1A+osmzTnEiQVWZUODSJ27+REvfHQbrE7cGCYWHfbVHJRJRYqFMxE/NQuQonODVRjPUv0+r/mKz/saL+X4r6wzQuU9nJwQYFNBYxRSviSSoim4pYiEXMoCKm1NNIlRqGfxCG6DECgx8QhS4gDJUSQ/gpFM7203b41l+jUeQIKHmLDtB7kwd//90/W330oqGkj0o1DTUWnvxZ0Qy6NR2z9kyrprpTGBSp4+qaaiUjSKyjqX59pKGpugxN1dVUTfX9kxSeLBA85zgbmATuoN3o8qPEqFsGf0KfFPIkYKdG2msPFqHh7yu0ZKsov5NKa0+lTcTSbio0i3JdA4mXGkhuUgZNLSR7kcNTveqaaH49UtlejOt0snAzM6mkrR3TuT/oCl/rZqyYpTnGJoRdCq52xEuVy16jyuEqVQqLCsxpPGWMPVvWrkC888SJOp4iZtQMTeFIU1oW9KzwJOC64XIQ1sHFCVxfN6aPYwFvaCwSQaqj+BizPvr0yayPkimalSPcLedsnomVLrNyx3ux+FWotDdevuAkNlhsNg6Wc9Zgz11KwS30LHWU48wsQbmELQSOY1hSsStSI4tOlr4PC6lAIjBZFDFPFE9m1+7YJVhpMQ6RoeXBpK/cAMt0eegfSisTGn5Xeb3BYFKKkeG6TNhHfcxhvu2ELTzRiXwQJ+qLi2JEIg2StmHQEPhJbQN8ymM+5Qk+5Uk+5Y0+Art7HuZAEzvdjw5me5bGO8omim4VecOg782e29RqJlVg9BjsCt8CsymzfxK6IhdV9UxaUn+FStLHQxfFzl2Spnhu1Z4j14uCiAEFRltwJYtxccyVHCQqOagCwiHHIKrkIKzkoHorCSiLcUf4xt2gVSabCDhMETnay6NzTEI4B1KaO/kbJ2mLLq9UoyZs2o1qoN2CBZW2AC5WNh7NylrANWYABuO2t0joWU4Mm7Crb0kPVK6iqyGpyDoh5LJJlKQlojYJFA/B5Eorgzx4B8MkQQgYv4LG3HTUIVkHl3aSitXRNh0+7+DQUanlmibihMI5poViak65W+qZ/kh/KxOo1AkrSH3NofG0Gl8x436XnkuyjFvEIkWFjBudpoSpRkj4VQVLud3bPbalplBHbJar1DDWKeLdCq9S6/Ol1MvXpJ4u8Zv3DsbHlPhNXgqEN/2ida+vjheqez6p7gXithIyNx+/8GbRQYX14G/PflbT7P0X8aZWlnhvNsd0NXX011Ey0Tbu/GrQOL54GiFWZ1zEdmfojVNY7UUw7noCA1LhFdulAdJ2TycLSKG6LRFdLTen06/0TG4WR6MpHe1z7m1Rz9KJzsJfUxyw7xuEP/BKYpSeKODHJWg+07696hB6KYqkIqhyIVmly66iVxPDL7t0Jc04rdPBLtf5Ktdkl732fIzSnt+mNevZhwt9dhT8Cc2HsyWYxF575mOJRypd31HcwZCb3a8RG08GfV1E6rG2ZD5xpSRzUwwl36/IfF+u/zuS/aMjrv/BXo9JYpMZu+ATVMHX1C24uCs/IFwQahGKYsIMcQNmdHM8hRA+yYmzt5iCKdFZfkPJvIh12eIBDRoLT7qQ7WOxlkXhy9HclGfw+gyD169cJXjds05e64TCOVoUgLaXDBjtmNJxGDElcuEyD4+RNodts038/RWUmFK91h1ulh9u3xdXypRynzz/VU8nx8k7Uxxj4d/gXSmOjfDvcBgmzwP81S8pDh98O5yJ9HPFxSck7p9fs7UHf/Xt/50nJGZ2VX9a8R51GF6OS4KYczvUfXe7SOzVafLNJ+Vb6Hxofvn0SbZPHpYohVzts6s=
*/