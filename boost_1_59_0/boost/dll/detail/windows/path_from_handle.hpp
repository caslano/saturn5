// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_WINDOWS_PATH_FROM_HANDLE_HPP
#define BOOST_DLL_DETAIL_WINDOWS_PATH_FROM_HANDLE_HPP

#include <boost/dll/config.hpp>
#include <boost/dll/detail/system_error.hpp>
#include <boost/winapi/dll.hpp>
#include <boost/winapi/get_last_error.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace detail {

    inline boost::dll::fs::error_code last_error_code() BOOST_NOEXCEPT {
        boost::winapi::DWORD_ err = boost::winapi::GetLastError();
        return boost::dll::fs::error_code(
            static_cast<int>(err),
            boost::dll::fs::system_category()
        );
    }

    inline boost::dll::fs::path path_from_handle(boost::winapi::HMODULE_ handle, boost::dll::fs::error_code &ec) {
        BOOST_STATIC_CONSTANT(boost::winapi::DWORD_, ERROR_INSUFFICIENT_BUFFER_ = 0x7A);
        BOOST_STATIC_CONSTANT(boost::winapi::DWORD_, DEFAULT_PATH_SIZE_ = 260);

        // On success, GetModuleFileNameW() doesn't reset last error to ERROR_SUCCESS. Resetting it manually.
        boost::winapi::GetLastError();

        // If `handle` parameter is NULL, GetModuleFileName retrieves the path of the
        // executable file of the current process.
        boost::winapi::WCHAR_ path_hldr[DEFAULT_PATH_SIZE_];
        boost::winapi::GetModuleFileNameW(handle, path_hldr, DEFAULT_PATH_SIZE_);
        ec = boost::dll::detail::last_error_code();
        if (!ec) {
            return boost::dll::fs::path(path_hldr);
        }

        for (unsigned i = 2; i < 1025 && static_cast<boost::winapi::DWORD_>(ec.value()) == ERROR_INSUFFICIENT_BUFFER_; i *= 2) {
            std::wstring p(DEFAULT_PATH_SIZE_ * i, L'\0');
            const std::size_t size = boost::winapi::GetModuleFileNameW(handle, &p[0], DEFAULT_PATH_SIZE_ * i);
            ec = boost::dll::detail::last_error_code();

            if (!ec) {
                p.resize(size);
                return boost::dll::fs::path(p);
            }
        }

        // Error other than ERROR_INSUFFICIENT_BUFFER_ occurred or failed to allocate buffer big enough.
        return boost::dll::fs::path();
    }

}}} // namespace boost::dll::detail

#endif // BOOST_DLL_DETAIL_WINDOWS_PATH_FROM_HANDLE_HPP


/* path_from_handle.hpp
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
*/