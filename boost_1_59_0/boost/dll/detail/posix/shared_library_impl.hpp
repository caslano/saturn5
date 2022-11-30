// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SHARED_LIBRARY_IMPL_HPP
#define BOOST_DLL_SHARED_LIBRARY_IMPL_HPP

#include <boost/dll/config.hpp>
#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/dll/detail/posix/path_from_handle.hpp>
#include <boost/dll/detail/posix/program_location_impl.hpp>

#include <boost/move/utility.hpp>
#include <boost/swap.hpp>
#include <boost/predef/os.h>

#include <dlfcn.h>
#include <cstring> // strncmp
#if !BOOST_OS_MACOS && !BOOST_OS_IOS && !BOOST_OS_QNX
#   include <link.h>
#elif BOOST_OS_QNX
// QNX's copy of <elf.h> and <link.h> reside in sys folder
#   include <sys/link.h>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace detail {

class shared_library_impl {

    BOOST_MOVABLE_BUT_NOT_COPYABLE(shared_library_impl)

public:
    typedef void* native_handle_t;

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


    static boost::dll::fs::path decorate(const boost::dll::fs::path & sl) {
        boost::dll::fs::path actual_path = (
            std::strncmp(sl.filename().string().c_str(), "lib", 3)
            ? boost::dll::fs::path((sl.has_parent_path() ? sl.parent_path() / "lib" : "lib").native() + sl.filename().native())
            : sl
        );
        actual_path += suffix();
        return actual_path;
    }

    void load(boost::dll::fs::path sl, load_mode::type portable_mode, boost::dll::fs::error_code &ec) {
        typedef int native_mode_t;
        native_mode_t native_mode = static_cast<native_mode_t>(portable_mode);
        unload();

        // Do not allow opening NULL paths. User must use program_location() instead
        if (sl.empty()) {
            boost::dll::detail::reset_dlerror();
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );

            return;
        }

        // Fixing modes
        if (!(native_mode & load_mode::rtld_now)) {
            native_mode |= load_mode::rtld_lazy;
        }

        if (!(native_mode & load_mode::rtld_global)) {
            native_mode |= load_mode::rtld_local;
        }

#if BOOST_OS_LINUX || BOOST_OS_ANDROID
        if (!sl.has_parent_path() && !(native_mode & load_mode::search_system_folders)) {
            sl = "." / sl;
        }
#else
        if (!sl.is_absolute() && !(native_mode & load_mode::search_system_folders)) {
            boost::dll::fs::error_code current_path_ec;
            boost::dll::fs::path prog_loc = boost::dll::fs::current_path(current_path_ec);
            if (!current_path_ec) {
                prog_loc /= sl;
                sl.swap(prog_loc);
            }
        }
#endif

        native_mode = static_cast<unsigned>(native_mode) & ~static_cast<unsigned>(load_mode::search_system_folders);

        // Trying to open with appended decorations
        if (!!(native_mode & load_mode::append_decorations)) {
            native_mode = static_cast<unsigned>(native_mode) & ~static_cast<unsigned>(load_mode::append_decorations);

            boost::dll::fs::path actual_path = decorate(sl);
            handle_ = dlopen(actual_path.c_str(), native_mode);
            if (handle_) {
                boost::dll::detail::reset_dlerror();
                return;
            }
            boost::dll::fs::error_code prog_loc_err;
            boost::dll::fs::path loc = boost::dll::detail::program_location_impl(prog_loc_err);
            if (boost::dll::fs::exists(actual_path) && !boost::dll::fs::equivalent(sl, loc, prog_loc_err)) {
                // decorated path exists : current error is not a bad file descriptor and we are not trying to load the executable itself
                ec = boost::dll::fs::make_error_code(
                    boost::dll::fs::errc::executable_format_error
                );
                return;
            }
        }

        // Opening by exactly specified path
        handle_ = dlopen(sl.c_str(), native_mode);
        if (handle_) {
            boost::dll::detail::reset_dlerror();
            return;
        }

        ec = boost::dll::fs::make_error_code(
            boost::dll::fs::errc::bad_file_descriptor
        );

        // Maybe user wanted to load the executable itself? Checking...
        // We assume that usually user wants to load a dynamic library not the executable itself, that's why
        // we try this only after traditional load fails.
        boost::dll::fs::error_code prog_loc_err;
        boost::dll::fs::path loc = boost::dll::detail::program_location_impl(prog_loc_err);
        if (!prog_loc_err && boost::dll::fs::equivalent(sl, loc, prog_loc_err) && !prog_loc_err) {
            // As is known the function dlopen() loads the dynamic library file
            // named by the null-terminated string filename and returns an opaque
            // "handle" for the dynamic library. If filename is NULL, then the
            // returned handle is for the main program.
            ec.clear();
            boost::dll::detail::reset_dlerror();
            handle_ = dlopen(NULL, native_mode);
            if (!handle_) {
                ec = boost::dll::fs::make_error_code(
                    boost::dll::fs::errc::bad_file_descriptor
                );
            }
        }
    }

    bool is_loaded() const BOOST_NOEXCEPT {
        return (handle_ != 0);
    }

    void unload() BOOST_NOEXCEPT {
        if (!is_loaded()) {
            return;
        }

        dlclose(handle_);
        handle_ = 0;
    }

    void swap(shared_library_impl& rhs) BOOST_NOEXCEPT {
        boost::swap(handle_, rhs.handle_);
    }

    boost::dll::fs::path full_module_path(boost::dll::fs::error_code &ec) const {
        return boost::dll::detail::path_from_handle(handle_, ec);
    }

    static boost::dll::fs::path suffix() {
        // https://sourceforge.net/p/predef/wiki/OperatingSystems/
#if BOOST_OS_MACOS || BOOST_OS_IOS
        return ".dylib";
#else
        return ".so";
#endif
    }

    void* symbol_addr(const char* sb, boost::dll::fs::error_code &ec) const BOOST_NOEXCEPT {
        // dlsym - obtain the address of a symbol from a dlopen object
        void* const symbol = dlsym(handle_, sb);
        if (symbol == NULL) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::invalid_seek
            );
        }

        // If handle does not refer to a valid object opened by dlopen(),
        // or if the named symbol cannot be found within any of the objects
        // associated with handle, dlsym() shall return NULL.
        // More detailed diagnostic information shall be available through dlerror().

        return symbol;
    }

    native_handle_t native() const BOOST_NOEXCEPT {
        return handle_;
    }

private:
    native_handle_t         handle_;
};

}}} // boost::dll::detail

#endif // BOOST_DLL_SHARED_LIBRARY_IMPL_HPP

/* shared_library_impl.hpp
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
*/