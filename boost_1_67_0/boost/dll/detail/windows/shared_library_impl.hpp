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
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
*/