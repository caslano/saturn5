// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SHARED_LIBRARY_IMPL_HPP
#define BOOST_DLL_SHARED_LIBRARY_IMPL_HPP

#include <boost/dll/config.hpp>
#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/dll/detail/aggressive_ptr_cast.hpp>
#include <boost/dll/detail/system_error.hpp>
#include <boost/dll/detail/windows/path_from_handle.hpp>

#include <boost/move/utility.hpp>
#include <boost/swap.hpp>

#include <boost/winapi/dll.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace detail {

class shared_library_impl {
    BOOST_MOVABLE_BUT_NOT_COPYABLE(shared_library_impl)

public:
    typedef boost::winapi::HMODULE_ native_handle_t;

    shared_library_impl() BOOST_NOEXCEPT
        : handle_(NULL)
    {}

    ~shared_library_impl() BOOST_NOEXCEPT {
        unload();
    }

    shared_library_impl(BOOST_RV_REF(shared_library_impl) sl) BOOST_NOEXCEPT
        : handle_(sl.handle_)
    {
        sl.handle_ = NULL;
    }

    shared_library_impl & operator=(BOOST_RV_REF(shared_library_impl) sl) BOOST_NOEXCEPT {
        swap(sl);
        return *this;
    }

    static boost::dll::fs::path decorate(const boost::dll::fs::path& sl) {
        boost::dll::fs::path actual_path = sl;
        actual_path += suffix();
        return actual_path;
    }

    void load(boost::dll::fs::path sl, load_mode::type portable_mode, boost::dll::fs::error_code &ec) {
        typedef boost::winapi::DWORD_ native_mode_t;
        native_mode_t native_mode = static_cast<native_mode_t>(portable_mode);
        unload();

        if (!sl.is_absolute() && !(native_mode & load_mode::search_system_folders)) {
            boost::dll::fs::error_code current_path_ec;
            boost::dll::fs::path prog_loc = boost::dll::fs::current_path(current_path_ec);

            if (!current_path_ec) {
                prog_loc /= sl;
                sl.swap(prog_loc);
            }
        }
        native_mode = static_cast<unsigned>(native_mode) & ~static_cast<unsigned>(load_mode::search_system_folders);

        // Trying to open with appended decorations
        if (!!(native_mode & load_mode::append_decorations)) {
            native_mode = static_cast<unsigned>(native_mode) & ~static_cast<unsigned>(load_mode::append_decorations);

            if (load_impl(decorate(sl), native_mode, ec)) {
                return;
            }

            // MinGW loves 'lib' prefix and puts it even on Windows platform.
            const boost::dll::fs::path mingw_load_path = (
                sl.has_parent_path()
                ? sl.parent_path() / L"lib"
                : L"lib"
            ).native() + sl.filename().native() + suffix().native();
            if (load_impl(mingw_load_path, native_mode, ec)) {
                return;
            }
        }

        // From MSDN: If the string specifies a module name without a path and the
        // file name extension is omitted, the function appends the default library
        // extension .dll to the module name.
        //
        // From experiments: Default library extension appended to the module name even if
        // we have some path. So we do not check for path, only for extension. We can not be sure that
        // such behavior remain across all platforms, so we add L"." by hand.
        if (sl.has_extension()) {
            handle_ = boost::winapi::LoadLibraryExW(sl.c_str(), 0, native_mode);
        } else {
            handle_ = boost::winapi::LoadLibraryExW((sl.native() + L".").c_str(), 0, native_mode);
        }

        // LoadLibraryExW method is capable of self loading from program_location() path. No special actions
        // must be taken to allow self loading.
        if (!handle_) {
            ec = boost::dll::detail::last_error_code();
        }
    }

    bool is_loaded() const BOOST_NOEXCEPT {
        return (handle_ != 0);
    }

    void unload() BOOST_NOEXCEPT {
        if (handle_) {
            boost::winapi::FreeLibrary(handle_);
            handle_ = 0;
        }
    }

    void swap(shared_library_impl& rhs) BOOST_NOEXCEPT {
        boost::swap(handle_, rhs.handle_);
    }

    boost::dll::fs::path full_module_path(boost::dll::fs::error_code &ec) const {
        return boost::dll::detail::path_from_handle(handle_, ec);
    }

    static boost::dll::fs::path suffix() {
        return L".dll";
    }

    void* symbol_addr(const char* sb, boost::dll::fs::error_code &ec) const BOOST_NOEXCEPT {
        if (is_resource()) {
            // `GetProcAddress` could not be called for libraries loaded with
            // `LOAD_LIBRARY_AS_DATAFILE`, `LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE`
            // or `LOAD_LIBRARY_AS_IMAGE_RESOURCE`.
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::operation_not_supported
            );

            return NULL;
        }

        // Judging by the documentation of GetProcAddress
        // there is no version for UNICODE on desktop/server Windows, because
        // names of functions are stored in narrow characters.
        void* const symbol = boost::dll::detail::aggressive_ptr_cast<void*>(
            boost::winapi::get_proc_address(handle_, sb)
        );
        if (symbol == NULL) {
            ec = boost::dll::detail::last_error_code();
        }

        return symbol;
    }

    native_handle_t native() const BOOST_NOEXCEPT {
        return handle_;
    }

private:
    // Returns true if this load attempt should be the last one.
    bool load_impl(const boost::dll::fs::path &load_path, boost::winapi::DWORD_ mode, boost::dll::fs::error_code &ec) {
        handle_ = boost::winapi::LoadLibraryExW(load_path.c_str(), 0, mode);
        if (handle_) {
            return true;
        }

        ec = boost::dll::detail::last_error_code();
        if (boost::dll::fs::exists(load_path)) {
            // decorated path exists : current error is not a bad file descriptor
            return true;
        }

        ec.clear();
        return false;
    }

    bool is_resource() const BOOST_NOEXCEPT {
        return false; /*!!(
            reinterpret_cast<boost::winapi::ULONG_PTR_>(handle_) & static_cast<boost::winapi::ULONG_PTR_>(3)
        );*/
    }

    native_handle_t handle_;
};

}}} // boost::dll::detail

#endif // BOOST_DLL_SHARED_LIBRARY_IMPL_HPP

/* shared_library_impl.hpp
I7yEwu7tqxIO39cp3nPdBpY9UW5Sblx0BSNdpAtmhZUzoADdlCjb6UVD2ndtdwYPURny5dvd6hhbv74XiEdKa55KYfC6V+NDkwUgjiEnWQiGwe7oHvX8JB5qErs8SVQDcQ2ALJAg6Rx0PQhY5RCqyZTFA2RrDCdGLR1Ob/Tm+xcWQgpdz3Rt3RRyrzFCp2u9iFE8qLyyVJO7St0p+PNQyeZZl9GxbE25UHmvsZ2qRzvq1yHD5o/zmTkPA2wJo0F0jCDRwXxuRArriGRaiBDgDxYRFhS6ErguwoZuIDVlC0HQrUgQLMfXn5wV2bp0wDW8WqFz0ZoydtUzMNmBIheY8bFjLMg+c+lKulklbBou6hueAt9Kje4Kybzrat2PNm82SCI/oFpI5FV/AIl8z36J/aWMf6gx/s3+nZKcb3zXq9UfPaj41+uPOq9W5xr2K9aD+aCE5xtULJ7EdZnMnFWftdNpxB3JUHjWimCIh5W1CX1AzdpKrMiauAHaIsoc5gOXyom7DEMpq3SfxDRxRT4i2VEXi4mrnjPlmSC86Qa1uRt0YETlHehkWugQ+GyJC4VeXOKYvs2Etr0/Tjqeu5F8vSImnpy7s0qhOdr5yQ9P/gbnJ8mP32X3N8bfT3aSbzskfj+qO9WnTmSy4HlB7WHuTjgW6JnkvCzOQ2vah8pFJvU5L8YlU8lap+QgYVVBgK4TbGteRyGAnPI4SUUZV9FIK5QF+moHee9vwxOZW1AYv41PZMpurI1LnQ8ZTpxHCPB8IqOJkXosHyNFaOhhFsnLe+ot2BrMwqRYZ4rBoXPiw8z2d2PSdB0uvRswrJ6qIsWy8OOGvZ6go56bLuB6KvU+z1G37PPWe8QmCbHYgPPOKrv1GV4PTpJWVEJPWsB4kNtvZzfxMUb3fPKOIhfQiDl/Ge9f0v4oHjY1UTfyN03UHVdJI+3VFU2Qv5vpkDyVTvl7zDPJy9+P36OBWneVJn+PfzSB/N15iyY/O7nEOQRv0Cv0XtHAv0LQxRYDmWsWHHC3hlx0wN3+wqRUxs76frzbVt+m5fXXd3Oqqm/RbU2qr5zr82Hw+AbqexHr82DOwaVNqq+rvb73b6i/vlO5vlUrk6yPq3pgrW5vjLPsBHWn4ah1coxtSJFewJ5bZD3OTJl7q8wPPurMfPOihh0hNoxfBuGnqrkPqhFUoLo8fPWrv4YaLQjIrFWxdoydR2IXX+hsykzpJNuLN/3wU6xpYM0z1BcdT4DCXvMQCSlng2c+QXq0DqQ+nHvFI87cly9sMlWSotfO1bapsfo65p6dN6Sw1BRYqM54ksJDv/+y2jY0x+jwPQz/rbJGwneMf6rEGulW1/SWB2Q+EZUPAqnsq4hv0LPyzpQv1kvlAuMfTpcf4QyZLRlLeXf85t71+8KPuPqHqwRWxOnGX14bJ54wBr9wlTZHwpd59fXwv3Fn17sAbU7GXiHTA8BnrlKbjsK1vOkwaL8fkWoAelwiuj/KwfhZFsgo8asAvqoiRa2DSNRqvhFFrQtQtihhUStzmRC1kJObwceQHV5LxfHw8zqXV0v6E7ANT7sAe75SAIuoV0sIB9z2hIUM0lb1hM986w4xXcPWXeqgj2REGSEebZ+ArczxqDsGuR7rjgEE+I4B5jAzYF4uoTxm7+V2o6WDNKMlQ2CeZ8e8DWBecwU7YRH40ip+8mLpE2kGeYiCCli3nMO5MufKXKNFLsAcs6CwRem7/yLTe6eoqVwC1BVPRpIvO2lYVCLz/UKKd4GIeVylIFY+NCbfuBh58KcQza+L2J20htFJ68V/rtOQyssl6Ds8hGI+oGiv/XiF5XzIUge3mVGZegakxsoRuyBi1+8BfAqEPIU=
*/