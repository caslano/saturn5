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
YLkvfDBpIX3yhORrGLLIgQ0MMxZsBkH7mZvf1kK7cankioZ8Ew2Ga8wG7KHIwYV0sxfLXazb7mB0A3tHeHd4z1gHBbZpNu5mInEYcG0qcMgkWBRAdggou7WDZXr1bkxxhflTfDaYuZRD9oo6hxUSE6nigSbUs3/XCrHlfApD6VvX2dFWAn6hcjJczz/4jtomv2qaVbNuOio3hkw5G8aT0WzUHQ2mUcwTJO70fo1/Hg96TgsGgJX4Jre0cHnK2XsPtgHGZ3zN0mc8DaD7C5RdeqgX/68t+P9rwI+334iHkX0DvQduvHC/6Cc6OtjfcnQYjOZdQMmBktgacZfXKNIgAKoRF+EAi+tBJvSGKyXcif1a7B3xQyGjtxdhtufHFtBmXMLmh+aZWz7xKksfB+s+eD0+x2GQv5myXAYB4l63w7D76mXnr3vWb2sWJ008mPTi0/OmdvROnVfu6E83ph+llT0AS1XmcD+kYESjxtUl1w090MgL/c1nHNeGpo8gGRnmZWEsO37k34G42263+lF207wz8rjlI9DxTtyZyPjGbhLDpU0tfuXDG9/JSaf5//YEn9ZhYAeHyFeVXX0suLnuqtZTlD0+9jllT5bAhGvTnz21eAZ9xFCmcXhXccX5RtF8itm3CmX7DnO9emTj
*/