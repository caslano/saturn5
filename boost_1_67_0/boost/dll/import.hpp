// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
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
        // auto f = dll::import<void(int)>("function", "lib.so");
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
* boost::function<int(int)> f = import<int(int)>("test_lib.so", "integer_func_name");
*
* auto f_cpp11 = import<int(int)>("test_lib.so", "integer_func_name");
* \endcode
*
* \code
* boost::shared_ptr<int> i = import<int>("test_lib.so", "integer_name");
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
BOOST_DLL_IMPORT_RESULT_TYPE import(const boost::dll::fs::path& lib, const char* name,
    load_mode::type mode = load_mode::default_mode)
{
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(lib, mode);
    return type(p, boost::addressof(p->get<T>(name)));
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import(const boost::dll::fs::path& lib, const std::string& name,
    load_mode::type mode = load_mode::default_mode)
{
    return import<T>(lib, name.c_str(), mode);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import(const shared_library& lib, const char* name) {
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(lib);
    return type(p, boost::addressof(p->get<T>(name)));
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import(const shared_library& lib, const std::string& name) {
    return import<T>(lib, name.c_str());
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import(BOOST_RV_REF(shared_library) lib, const char* name) {
    typedef typename boost::dll::detail::import_type<T>::base_type type;

    boost::shared_ptr<boost::dll::shared_library> p = boost::make_shared<boost::dll::shared_library>(
        boost::move(lib)
    );
    return type(p, boost::addressof(p->get<T>(name)));
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class T>
BOOST_DLL_IMPORT_RESULT_TYPE import(BOOST_RV_REF(shared_library) lib, const std::string& name) {
    return import<T>(boost::move(lib), name.c_str());
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
    return import_alias<T>(lib, name.c_str(), mode);
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
    return import_alias<T>(lib, name.c_str());
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
    return import_alias<T>(boost::move(lib), name.c_str());
}

#undef BOOST_DLL_IMPORT_RESULT_TYPE


}} // boost::dll

#endif // BOOST_DLL_IMPORT_HPP


/* import.hpp
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
*/