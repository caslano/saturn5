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
            ? boost::dll::fs::path((sl.has_parent_path() ? sl.parent_path() / L"lib" : L"lib").native() + sl.filename().native())
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
olV2GnzJRy9goW5gWgzd8utOi4T3TVbstI9v2qOdQVgNfqK+sT2FxvZDX4mx3e5rGNtvmPaxHdTHNhFj2avU0ia2T0N953sCdemCWgOLKGP3rAI0LjlafUXnkc+INJV8G+5SLl+srh5CG666ujaO9hcjzutggMVdznnS4g4LHrIWYKiitVBoznhVrEAW203FdqpiVb2QUqdWpeGfiVWIROy4KoQTC1fdi3/yqg7AtGH0ZxA+cWF+8xoJs+S70nz7I9JX+FQXUXTXdbXWEPEfaGw+t4PxHvx7Av59BP8+hX+GN8HPQ39SEiSnehv+GSnePf+lTK/cAXi+Bf+ek/gz7mlpaZ60/+EfcBH4LxVo/cIf+RdKbP/+L95AiikqVdJZcProODwjny+RpB4EcpenMzR5OsNFngau5jOEmtuS1V3k5cwG5OmszUnJfxmtLFySlE9ZknaFx/KfA58G5O9AU9dn6sD5/7CW2vKIl/76zJHPQTRv6YxohzwhKfEzYlnm0nRQ9if5wpOmpc6g+mAjSOdRJ3/SVmrW/vM53cJooD0jGthv6AJL4+kJ6cHGj4+k6K3KZ+xZf9rlqeTGN443q8sr3pJdMJK64I3atsZ6IQc/f4e91zuJDhau/XzqE8axV+v3JPdLS8IjrKtDye7ncqlI0vlzGpk/2Mj8WZQ/ufamN769GY2BHxCZk92vwsWVxuOTSUWauP+iwZb1BvEX7QJOLp23n27iefuteN5+O5+3G2BVSNsgH7GiYDIuQZz7CdZH6uvVNmH/+bpSSM5/mxWSD8hzme2Y4/IXUOPEDivhK5RfgZhsh2Mjs1po6i/CZkyiKyJGDJtxITYjys0YCvlQxYkQjZLOeVUREqPjT/qlXu/gtWCZ3gmPbbdjUUynBC/Yi2OFhZD9LZyZKeJaLhkbnyoPQt6STs9QsU+/2AHyOCBegrYPIoe5EJCRyn+kfxwsrdlF2FghUR+6i/ZFA26lmR/BjorYb0odUIstXGlv4UkbBUIvEOiQBB0WoEejS0zz1Z0Eeskjmt5WXSQuJdCbaxD0bXbQPz1N5s5Am90QVn4/wlJeRiSV/tYUNozUQlSvviV78gskBBzkL9pI1c2j6iaI6krt1VU8rW5y8/EcqVn77xJq1m2//9MFx/mkdv/7FZ59BfAQHykeOtE2dDAZdMal5+FCmV5oBqpFeq5Iz8V0OuFHoodwqQ5BcDCqI2BGzPqwtvGvkYd4ftrR/XqHRHdkzQ+dYYD3gH1XbhoqwMS7L2mvQSwkviAS02qWC1e7q2lqlX4Mc0Vo+7663n6OmRIDxRcE6Y1A9VkA65j6LlwS5vgiYN3iW934A6pMwFDriVCtWZ2GqgWc0g9SvcbHSoAZ9DFM6eba9d3HaNS9+1FbdXVvJY+6Tk/iqGs05ZL7kai1arugJuD4iTh1aH3d99AA8UjC1rRF8G3w+bfreOL+YZPOEwgi+w8X90GFMcyLEJKXbHJxsOD4gp7qAbXgDdEKomB7RODlVIO1L/FoB3TaBUnf74akO7368z5Gyf55VZ2Jys+9j/oHpHLEo+chef94efvTT2bsuHfGa48+jC6V0aUyOh2i+XJaezJXYa/PY2Gt8O19ryT5bv7kmr3MczO38wXYjDHhc4B8mTDo/7mrLZsTebOlNNZaqqzTs8tbLPFR88mXf46IHOuVuDfa21jI1f/XS3L4pJ0qSZ6VJyZYyGEVecSKhs4ItVZnEFRpZkL+1p5C5XTWghEYNX9WJ6ebt/hGoEHsNfiC++kHJtM4bb+x8kUp7H5KA2n8B2q6Lvwg4X7D2VWTCIh1ZFDeAg3W0asdIB1tDqjh02dWOvSFuJ6TDLJu+s8XrE0=
*/