// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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
3R9tznIQ1ZIfxJ6LFXQAjqG+jDuFjv/BwY3yw/Z5zjD0EAeQ1wCI1QxEW7YHPNFxK34v8ok1NOF0P7EeqfhAY5rlpGoK0Es3I61Z3l+rzfLBWn2W6WS4M846RVm6J+hO3kjz+9IwuJtPX2ObrYRCtND/Nnro1IPXfEU+ludJXULP3+DRcYazF9GrteJZ6GlHtKgJ4jL+X0hcAM1lWVnp/JpzSDq/Zqq/StVf9x6iDXXeT/Tb6ifcUNE/w+VmM1iHlyfq6OkfAbpt1rWpV5uPdxotTuRvA9ROK8UV+DXleHrq22SUnwDiWacpS/CQ/sAl4Ne+RPfqzOF0FbnSpXMDbiVOIIfnUnRvzsQw5AKYcLGT4IuqvFgB5W4T0C4Iupet91BtWVRFy0sN6gMk0eL2qK5inTKlq3ZUKSwp7Z0XEKDArqIu1FXUYyDdXgycGsI95YBUYhQUeZvL2misnOLIWtDIGm4Cwos6LVutEK5+Pr1cdVtWT6gOEIsKUrWSJMN+cn8klQJMMv/6D5/EEWN55FMPQjrPgHP7SZxNJI+TqyC4WztI8xA3I9utol2XABLTCOlMiSVnysjEBPMrodLA8SHIG7om9PhQgtn6ZfKjfGpYx4d2wmwSzLufjqNRJZgPLkEHijxDlIB1K8EK/sYzMBR0ncSimLpHd53AqwNecctDSEDBv0G1suIToVbuFn+C8Yq4dClvpPP8dPKG
*/