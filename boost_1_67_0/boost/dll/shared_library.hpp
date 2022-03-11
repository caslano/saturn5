// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SHARED_LIBRARY_HPP
#define BOOST_DLL_SHARED_LIBRARY_HPP

/// \file boost/dll/shared_library.hpp
/// \brief Contains the boost::dll::shared_library class, core class for all the
/// DLL/DSO operations.

#include <boost/dll/config.hpp>
#include <boost/predef/os.h>
#include <boost/core/enable_if.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/dll/detail/system_error.hpp>
#include <boost/dll/detail/aggressive_ptr_cast.hpp>

#if BOOST_OS_WINDOWS
#   include <boost/dll/detail/windows/shared_library_impl.hpp>
#else
#   include <boost/dll/detail/posix/shared_library_impl.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll {

/*!
* \brief This class can be used to load a
*        Dynamic link libraries (DLL's) or Shared Libraries, also know
*        as dynamic shared objects (DSO's) and get their exported
*        symbols (functions and variables).
*
* shared_library instances share reference count to an actual loaded DLL/DSO, so it
* is safe and memory efficient to have multiple instances of shared_library referencing the same DLL/DSO
* even if those instances were loaded using different paths (relative + absolute) referencing the same object.
*
* On Linux/POSIX link with library "dl". "-fvisibility=hidden" flag is also recommended for use on Linux/POSIX.
*/
class shared_library
/// @cond
    : private boost::dll::detail::shared_library_impl
/// @endcond
{
    typedef boost::dll::detail::shared_library_impl base_t;
    BOOST_COPYABLE_AND_MOVABLE(shared_library)

public:
#ifdef BOOST_DLL_DOXYGEN
    typedef platform_specific native_handle_t;
#else
    typedef shared_library_impl::native_handle_t native_handle_t;
#endif

    /*!
    * Creates in anstance that does not reference any DLL/DSO.
    *
    * \post this->is_loaded() returns false.
    * \throw Nothing.
    */
    shared_library() BOOST_NOEXCEPT {}

    /*!
    * Copy constructor that increments the reference count of an underlying shared library.
    * Same as calling constructor with `lib.location()` parameter.
    *
    * \param lib A library to copy.
    * \post lib == *this
    * \throw \forcedlinkfs{system_error}, std::bad_alloc in case of insufficient memory.
    */
    shared_library(const shared_library& lib)
        : base_t()
    {
        assign(lib);
    }

    /*!
    * Copy constructor that increments the reference count of an underlying shared library.
    * Same as calling constructor with `lib.location(), ec` parameters.
    *
    * \param lib A shared library to copy.
    * \param ec Variable that will be set to the result of the operation.
    * \post lib == *this
    * \throw std::bad_alloc in case of insufficient memory.
    */
    shared_library(const shared_library& lib, boost::dll::fs::error_code& ec)
        : base_t()
    {
        assign(lib, ec);
    }

    /*!
    * Move constructor. Does not invalidate existing symbols and functions loaded from lib.
    *
    * \param lib A shared library to move from.
    * \post lib.is_loaded() returns false, this->is_loaded() return true.
    * \throw Nothing.
    */
    shared_library(BOOST_RV_REF(shared_library) lib) BOOST_NOEXCEPT
        : base_t(boost::move(static_cast<base_t&>(lib)))
    {}

    /*!
    * Loads a library by specified path with a specified mode.
    *
    * \param lib_path Library file name. Can handle std::string, const char*, std::wstring,
    *           const wchar_t* or \forcedlinkfs{path}.
    * \param mode A mode that will be used on library load.
    * \throw \forcedlinkfs{system_error}, std::bad_alloc in case of insufficient memory.
    */
    explicit shared_library(const boost::dll::fs::path& lib_path, load_mode::type mode = load_mode::default_mode) {
        shared_library::load(lib_path, mode);
    }

    /*!
    * Loads a library by specified path with a specified mode.
    *
    * \param lib_path Library file name. Can handle std::string, const char*, std::wstring,
    *           const wchar_t* or \forcedlinkfs{path}.
    * \param mode A mode that will be used on library load.
    * \param ec Variable that will be set to the result of the operation.
    * \throw std::bad_alloc in case of insufficient memory.
    */
    shared_library(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode) {
        shared_library::load(lib_path, mode, ec);
    }

    //! \overload shared_library(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode)
    shared_library(const boost::dll::fs::path& lib_path, load_mode::type mode, boost::dll::fs::error_code& ec) {
        shared_library::load(lib_path, mode, ec);
    }

    /*!
    * Assignment operator. If this->is_loaded() then calls this->unload(). Does not invalidate existing symbols and functions loaded from lib.
    *
    * \param lib A shared library to assign from.
    * \post lib == *this
    * \throw \forcedlinkfs{system_error}, std::bad_alloc in case of insufficient memory.
    */
    shared_library& operator=(BOOST_COPY_ASSIGN_REF(shared_library) lib) {
        boost::dll::fs::error_code ec;
        assign(lib, ec);
        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::shared_library::operator= failed");
        }

        return *this;
    }

    /*!
    * Move assignment operator. If this->is_loaded() then calls this->unload(). Does not invalidate existing symbols and functions loaded from lib.
    *
    * \param lib A library to move from.
    * \post lib.is_loaded() returns false.
    * \throw Nothing.
    */
    shared_library& operator=(BOOST_RV_REF(shared_library) lib) BOOST_NOEXCEPT {
        if (lib.native() != native()) {
            swap(lib);
        }

        return *this;
    }

    /*!
    * Destroys the object by calling `unload()`. If library was loaded multiple times
    * by different instances, the actual DLL/DSO won't be unloaded until
    * there is at least one instance that references the DLL/DSO.
    *
    * \throw Nothing.
    */
    ~shared_library() BOOST_NOEXCEPT {}

    /*!
    * Makes *this share the same shared object as lib. If *this is loaded, then unloads it.
    *
    * \post lib.location() == this->location(), lib == *this
    * \param lib A library to copy.
    * \param ec Variable that will be set to the result of the operation.
    * \throw std::bad_alloc in case of insufficient memory.
    */
    shared_library& assign(const shared_library& lib, boost::dll::fs::error_code& ec) {
        ec.clear();

        if (native() == lib.native()) {
            return *this;
        }

        if (!lib) {
            unload();
            return *this;
        }

        boost::dll::fs::path loc = lib.location(ec);
        if (ec) {
            return *this;
        }

        shared_library copy(loc, ec);
        if (ec) {
            return *this;
        }

        swap(copy);
        return *this;
    }

    /*!
    * Makes *this share the same shared object as lib. If *this is loaded, then unloads it.
    *
    * \param lib A library instance to assign from.
    * \post lib.location() == this->location()
    * \throw \forcedlinkfs{system_error}, std::bad_alloc in case of insufficient memory.
    */
    shared_library& assign(const shared_library& lib) {
        boost::dll::fs::error_code ec;
        assign(lib, ec);
        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::shared_library::assign() failed");
        }

        return *this;
    }

    /*!
    * Loads a library by specified path with a specified mode.
    *
    * Note that if some library is already loaded in this instance, load will
    * call unload() and then load the new provided library.
    *
    * \param lib_path Library file name. Can handle std::string, const char*, std::wstring,
    *           const wchar_t* or \forcedlinkfs{path}.
    * \param mode A mode that will be used on library load.
    * \throw \forcedlinkfs{system_error}, std::bad_alloc in case of insufficient memory.
    *
    */
    void load(const boost::dll::fs::path& lib_path, load_mode::type mode = load_mode::default_mode) {
        boost::dll::fs::error_code ec;

        base_t::load(lib_path, mode, ec);

        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::shared_library::load() failed");
        }
    }

    /*!
    * Loads a library by specified path with a specified mode.
    *
    * Note that if some library is already loaded in this instance, load will
    * call unload() and then load the new provided library.
    *
    * \param lib_path Library file name. Can handle std::string, const char*, std::wstring,
    *           const wchar_t* or \forcedlinkfs{path}.
    * \param ec Variable that will be set to the result of the operation.
    * \param mode A mode that will be used on library load.
    * \throw std::bad_alloc in case of insufficient memory.
    */
    void load(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode) {
        ec.clear();
        base_t::load(lib_path, mode, ec);
    }

    //! \overload void load(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode)
    void load(const boost::dll::fs::path& lib_path, load_mode::type mode, boost::dll::fs::error_code& ec) {
        ec.clear();
        base_t::load(lib_path, mode, ec);
    }

    /*!
    * Unloads a shared library.  If library was loaded multiple times
    * by different instances, the actual DLL/DSO won't be unloaded until
    * there is at least one instance that references the DLL/DSO.
    *
    * \post this->is_loaded() returns false.
    * \throw Nothing.
    */
    void unload() BOOST_NOEXCEPT {
        base_t::unload();
    }

    /*!
    * Check if an library is loaded.
    *
    * \return true if a library has been loaded.
    * \throw Nothing.
    */
    bool is_loaded() const BOOST_NOEXCEPT {
        return base_t::is_loaded();
    }

    /*!
    * Check if an library is not loaded.
    *
    * \return true if a library has not been loaded.
    * \throw Nothing.
    */
    bool operator!() const BOOST_NOEXCEPT {
        return !is_loaded();
    }

    /*!
    * Check if an library is loaded.
    *
    * \return true if a library has been loaded.
    * \throw Nothing.
    */
    BOOST_EXPLICIT_OPERATOR_BOOL()

    /*!
    * Search for a given symbol on loaded library. Works for all symbols, including alias names.
    *
    * \param symbol_name Null-terminated symbol name. Can handle std::string, char*, const char*.
    * \return `true` if the loaded library contains a symbol with a given name.
    * \throw Nothing.
    */
    bool has(const char* symbol_name) const BOOST_NOEXCEPT {
        boost::dll::fs::error_code ec;
        return is_loaded() && !!base_t::symbol_addr(symbol_name, ec) && !ec;
    }

    //! \overload bool has(const char* symbol_name) const
    bool has(const std::string& symbol_name) const BOOST_NOEXCEPT {
        return has(symbol_name.c_str());
    }

    /*!
    * Returns reference to the symbol (function or variable) with the given name from the loaded library.
    * This call will always succeed and throw nothing if call to `has(const char* )`
    * member function with the same symbol name returned `true`.
    *
    * \b Example:
    * \code
    * int& i0 = lib.get<int>("integer_name");
    * int& i1 = *lib.get<int*>("integer_alias_name");
    * \endcode
    *
    * \tparam T Type of the symbol that we are going to import. Must be explicitly specified.
    * \param symbol_name Null-terminated symbol name. Can handle std::string, char*, const char*.
    * \return Reference to the symbol.
    * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
    */
    template <typename T>
    inline typename boost::enable_if_c<boost::is_member_pointer<T>::value || boost::is_reference<T>::value, T>::type  get(const std::string& symbol_name) const {
        return get<T>(symbol_name.c_str());
    }

    //! \overload T& get(const std::string& symbol_name) const
    template <typename T>
    inline typename boost::disable_if_c<boost::is_member_pointer<T>::value || boost::is_reference<T>::value, T&>::type get(const std::string& symbol_name) const {
        return get<T>(symbol_name.c_str());
    }

    //! \overload T& get(const std::string& symbol_name) const
    template <typename T>
    inline typename boost::enable_if_c<boost::is_member_pointer<T>::value || boost::is_reference<T>::value, T>::type get(const char* symbol_name) const {
        return boost::dll::detail::aggressive_ptr_cast<T>(
            get_void(symbol_name)
        );
    }

    //! \overload T& get(const std::string& symbol_name) const
    template <typename T>
    inline typename boost::disable_if_c<boost::is_member_pointer<T>::value || boost::is_reference<T>::value, T&>::type get(const char* symbol_name) const {
        return *boost::dll::detail::aggressive_ptr_cast<T*>(
            get_void(symbol_name)
        );
    }

    /*!
    * Returns a symbol (function or variable) from a shared library by alias name of the symbol.
    *
    * \b Example:
    * \code
    * int& i = lib.get_alias<int>("integer_alias_name");
    * \endcode
    *
    * \tparam T Type of the symbol that we are going to import. Must be explicitly specified..
    * \param alias_name Null-terminated alias symbol name. Can handle std::string, char*, const char*.
    * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
    */
    template <typename T>
    inline T& get_alias(const char* alias_name) const {
        return *get<T*>(alias_name);
    }

    //! \overload T& get_alias(const char* alias_name) const
    template <typename T>
    inline T& get_alias(const std::string& alias_name) const {
        return *get<T*>(alias_name.c_str());
    }

private:
    /// @cond
    // get_void is required to reduce binary size: it does not depend on a template
    // parameter and will be instantiated only once.
    void* get_void(const char* sb) const {
        boost::dll::fs::error_code ec;

        if (!is_loaded()) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );

            // report_error() calls dlsym, do not use it here!
            boost::throw_exception(
                boost::dll::fs::system_error(
                    ec, "boost::dll::shared_library::get() failed: no library was loaded"
                )
            );
        }

        void* const ret = base_t::symbol_addr(sb, ec);
        if (ec || !ret) {
            boost::dll::detail::report_error(ec, "boost::dll::shared_library::get() failed");
        }

        return ret;
    }
    /// @endcond

public:

    /*!
    * Returns the native handler of the loaded library.
    *
    * \return Platform-specific handle.
    */
    native_handle_t native() const BOOST_NOEXCEPT {
        return base_t::native();
    }

   /*!
    * Returns full path and name of this shared object.
    *
    * \b Example:
    * \code
    * shared_library lib("test_lib.dll");
    * filesystem::path full_path = lib.location(); // C:\Windows\System32\test_lib.dll
    * \endcode
    *
    * \return Full path to the shared library.
    * \throw \forcedlinkfs{system_error}, std::bad_alloc.
    */
    boost::dll::fs::path location() const {
        boost::dll::fs::error_code ec;
        if (!is_loaded()) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );

            boost::throw_exception(
                boost::dll::fs::system_error(
                    ec, "boost::dll::shared_library::location() failed (no library was loaded)"
                )
            );
        }

        boost::dll::fs::path full_path = base_t::full_module_path(ec);

        if (ec) {
            boost::dll::detail::report_error(ec, "boost::dll::shared_library::location() failed");
        }

        return full_path;
    }

   /*!
    * Returns full path and name of shared module.
    *
    * \b Example:
    * \code
    * shared_library lib("test_lib.dll");
    * filesystem::path full_path = lib.location(); // C:\Windows\System32\test_lib.dll
    * \endcode
    *
    * \param ec Variable that will be set to the result of the operation.
    * \return Full path to the shared library.
    * \throw std::bad_alloc.
    */
    boost::dll::fs::path location(boost::dll::fs::error_code& ec) const {
        if (!is_loaded()) {
            ec = boost::dll::fs::make_error_code(
                boost::dll::fs::errc::bad_file_descriptor
            );

            return boost::dll::fs::path();
        }

        ec.clear();
        return base_t::full_module_path(ec);
    }

    /*!
    * Returns suffix of shared module:
    * in a call to load() or the constructor/load.
    *
    * \return The suffix od shared module: ".dll" (Windows), ".so" (Unix/Linux/BSD), ".dylib" (MacOS/IOS)
    */
    static boost::dll::fs::path suffix() {
        return base_t::suffix();
    }

    /*!
    * Returns the decorated path to a shared module name, i.e. with needed prefix/suffix added.
    *
    * \b Recommendations: Use `load` with `load_mode::append_decorations` instead of constructing the decorated path via `decorate()` and loading by it.
    *
    * For instance, for a path like "path/to/boost" it returns :
    * - path/to/libboost.so on posix platforms
    * - path/to/libboost.dylib on OSX
    * - path/to/boost.dll on Windows
    *
    * Method handles both relative and absolute paths.
    *
    * - Windows note: `decorate()` does not prepend "lib" to the decorated path. Use `load` with `load_mode::append_decorations` for MinGW compatibility purpose.
    * - Posix note: if the initial module name is already prepended with lib, only the suffix() is appended to the path
    *
    * \param sl the module name and path to decorate - for instance : /usr/lib/boost
    *
    * \return The decorated unportable path that may not exists in the filesystem or could be wrong due to platform specifics.
    */
    static boost::dll::fs::path decorate(const boost::dll::fs::path& sl) {
        return base_t::decorate(sl);
    }

    /*!
    * Swaps two libraries. Does not invalidate existing symbols and functions loaded from libraries.
    *
    * \param rhs Library to swap with.
    * \throw Nothing.
    */
    void swap(shared_library& rhs) BOOST_NOEXCEPT {
        base_t::swap(rhs);
    }
};



/// Very fast equality check that compares the actual DLL/DSO objects. Throws nothing.
inline bool operator==(const shared_library& lhs, const shared_library& rhs) BOOST_NOEXCEPT {
    return lhs.native() == rhs.native();
}

/// Very fast inequality check that compares the actual DLL/DSO objects. Throws nothing.
inline bool operator!=(const shared_library& lhs, const shared_library& rhs) BOOST_NOEXCEPT {
    return lhs.native() != rhs.native();
}

/// Compare the actual DLL/DSO objects without any guarantee to be stable between runs. Throws nothing.
inline bool operator<(const shared_library& lhs, const shared_library& rhs) BOOST_NOEXCEPT {
    return lhs.native() < rhs.native();
}

/// Swaps two shared libraries. Does not invalidate symbols and functions loaded from libraries. Throws nothing.
inline void swap(shared_library& lhs, shared_library& rhs) BOOST_NOEXCEPT {
    lhs.swap(rhs);
}

}} // boost::dll

#endif // BOOST_DLL_SHARED_LIBRARY_HPP

/* shared_library.hpp
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
*/