// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_IMPORT_HPP
#define BOOST_DLL_IMPORT_HPP

#include <boost/dll/config.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_object.hpp>
#include <boost/make_shared.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/move/move.hpp>

#if defined(BOOST_NO_CXX11_TRAILING_RESULT_TYPES) || defined(BOOST_NO_CXX11_DECLTYPE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#   include <boost/function.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

/// \file boost/dll/import.hpp
/// \brief Contains all the boost::dll::import* reference counting
/// functions that hold a shared pointer to the instance of
/// boost::dll::shared_library.

namespace boost { namespace dll {


namespace detail {

    template <class T>
    class library_function {
        // Copying of `boost::dll::shared_library` is very expensive, so we use a `shared_ptr` to make it faster.
        boost::shared_ptr<T>   f_;

    public:
        inline library_function(const boost::shared_ptr<shared_library>& lib, T* func_ptr) BOOST_NOEXCEPT
            : f_(lib, func_ptr)
        {}

#if defined(BOOST_NO_CXX11_TRAILING_RESULT_TYPES) || defined(BOOST_NO_CXX11_DECLTYPE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        operator T*() const BOOST_NOEXCEPT {
            return f_.get();
        }
#else

        // Compilation error at this point means that imported function
        // was called with unmatching parameters.
        //
        // Example:
        // auto f = dll::import_symbol<void(int)>("function", "lib.so");
        // f("Hello");  // error: invalid conversion from 'const char*' to 'int'
        // f(1, 2);     // error: too many arguments to function
        // f();         // error: too few arguments to function
        template <class... Args>
        inline auto operator()(Args&&... args) const
            -> decltype( (*f_)(static_cast<Args&&>(args)...) )
        {
            return (*f_)(static_cast<Args&&>(args)...);
        }
#endif
    };

    template <class T, class = void>
    struct import_type;

    template <class T>
    struct import_type<T, typename boost::disable_if<boost::is_object<T> >::type> {
        typedef boost::dll::detail::library_function<T> base_type;

#if defined(BOOST_NO_CXX11_TRAILING_RESULT_TYPES) || defined(BOOST_NO_CXX11_DECLTYPE) || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        typedef boost::function<T>                      type;
#else
        typedef boost::dll::detail::library_function<T> type;
#endif
    };

    template <class T>
    struct import_type<T, typename boost::enable_if<boost::is_object<T> >::type> {
        typedef boost::shared_ptr<T> base_type;
        typedef boost::shared_ptr<T> type;
    };
} // namespace detail


#ifndef BOOST_DLL_DOXYGEN
#   define BOOST_DLL_IMPORT_RESULT_TYPE inline typename boost::dll::detail::import_type<T>::type
#endif


/*!
* Returns callable object or boost::shared_ptr<T> that holds the symbol imported
* from the loaded library. Returned value refcounts usage
* of the loaded shared library, so that it won't get unload until all copies of return value
* are not destroyed.
*
* This call will succeed if call to \forcedlink{shared_library}`::has(const char* )`
* function with the same symbol name returned `true`.
*
* For importing symbols by \b alias names use \forcedlink{import_alias} method.
*
* \b Examples:
*
* \code
* boost::function<int(int)> f = import_symbol<int(int)>("test_lib.so", "integer_func_name");
*
* auto f_cpp11 = import_symbol<int(int)>("test_lib.so", "integer_func_name");
* \endcode
*
* \code
* boost::shared_ptr<int> i = import_symbol<int>("test_lib.so", "integer_name");
* \endcode
*
* \b Template \b parameter \b T:    Type of the symbol that we are going to import. Must be explicitly specified.
*
* \param lib Path to shared library or shared library to load function from.
* \param name Null-terminated C or C++ mangled name of the function to import. Can handle std::string, char*, const char*.
* \param mode An mode that will be used on library load.
*
* \return callable object if T is a function type, or boost::shared_ptr<T> if T is an object type.
*
* \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
*       Overload that accepts path also throws std::bad_alloc in case of insufficient memory.
*/
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_symbol(const boost::dll::fs::path& lib, const char* name,
    load_mode::type mode = load_mode::default_mode)
{
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(lib, mode);
    return type(p, boost::addressof(p->get<T>(name)));
}

//! \overload boost::dll::import_symbol(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_symbol(const boost::dll::fs::path& lib, const std::string& name,
    load_mode::type mode = load_mode::default_mode)
{
    return dll::import_symbol<T>(lib, name.c_str(), mode);
}

//! \overload boost::dll::import_symbol(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_symbol(const shared_library& lib, const char* name) {
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(lib);
    return type(p, boost::addressof(p->get<T>(name)));
}

//! \overload boost::dll::import_symbol(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_symbol(const shared_library& lib, const std::string& name) {
    return dll::import_symbol<T>(lib, name.c_str());
}

//! \overload boost::dll::import_symbol(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_symbol(BOOST_RV_REF(shared_library) lib, const char* name) {
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(
        boost::move(lib)
    );
    return type(p, boost::addressof(p->get<T>(name)));
}

//! \overload boost::dll::import_symbol(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_symbol(BOOST_RV_REF(shared_library) lib, const std::string& name) {
    return dll::import_symbol<T>(boost::move(lib), name.c_str());
}




/*!
* Returns callable object or boost::shared_ptr<T> that holds the symbol imported
* from the loaded library. Returned value refcounts usage
* of the loaded shared library, so that it won't get unload until all copies of return value
* are not destroyed.
*
* This call will succeed if call to \forcedlink{shared_library}`::has(const char* )`
* function with the same symbol name returned `true`.
*
* For importing symbols by \b non \b alias names use \forcedlink{import} method.
*
* \b Examples:
*
* \code
* boost::function<int(int)> f = import_alias<int(int)>("test_lib.so", "integer_func_alias_name");
*
* auto f_cpp11 = import_alias<int(int)>("test_lib.so", "integer_func_alias_name");
* \endcode
*
* \code
* boost::shared_ptr<int> i = import_alias<int>("test_lib.so", "integer_alias_name");
* \endcode
*
* \code
* \endcode
*
* \b Template \b parameter \b T:    Type of the symbol alias that we are going to import. Must be explicitly specified.
*
* \param lib Path to shared library or shared library to load function from.
* \param name Null-terminated C or C++ mangled name of the function or variable to import. Can handle std::string, char*, const char*.
* \param mode An mode that will be used on library load.
*
* \return callable object if T is a function type, or boost::shared_ptr<T> if T is an object type.
*
* \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
*       Overload that accepts path also throws std::bad_alloc in case of insufficient memory.
*/
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_alias(const boost::dll::fs::path& lib, const char* name,
    load_mode::type mode = load_mode::default_mode)
{
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(lib, mode);
    return type(p, p->get<T*>(name));
}

//! \overload boost::dll::import_alias(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_alias(const boost::dll::fs::path& lib, const std::string& name,
    load_mode::type mode = load_mode::default_mode)
{
    return dll::import_alias<T>(lib, name.c_str(), mode);
}

//! \overload boost::dll::import_alias(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_alias(const shared_library& lib, const char* name) {
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(lib);
    return type(p, p->get<T*>(name));
}

//! \overload boost::dll::import_alias(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_alias(const shared_library& lib, const std::string& name) {
    return dll::import_alias<T>(lib, name.c_str());
}

//! \overload boost::dll::import_alias(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_alias(BOOST_RV_REF(shared_library) lib, const char* name) {
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(
        boost::move(lib)
    );
    return type(p, p->get<T*>(name));
}

//! \overload boost::dll::import_alias(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import_alias(BOOST_RV_REF(shared_library) lib, const std::string& name) {
    return dll::import_alias<T>(boost::move(lib), name.c_str());
}

#undef BOOST_DLL_IMPORT_RESULT_TYPE


}} // boost::dll

#endif // BOOST_DLL_IMPORT_HPP


/* import.hpp
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
*/