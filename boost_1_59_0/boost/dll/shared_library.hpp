// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
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