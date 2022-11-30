//  Copyright 2016 Klemens Morgenstern
//  Copyright Antony Polukhin, 2019-2022
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SMART_LIBRARY_HPP_
#define BOOST_DLL_SMART_LIBRARY_HPP_

/// \file boost/dll/smart_library.hpp
/// \warning Extremely experimental! Requires C++11! Will change in next version of Boost! boost/dll/smart_library.hpp is not included in boost/dll.hpp
/// \brief Contains the boost::dll::experimental::smart_library class for loading mangled symbols.

#include <boost/dll/config.hpp>
#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows
#   include <boost/dll/detail/demangling/msvc.hpp>
#else
#   include <boost/dll/detail/demangling/itanium.hpp>
#endif

#if (__cplusplus < 201103L) && (!defined(_MSVC_LANG) || _MSVC_LANG < 201103L)
#  error This file requires C++11 at least!
#endif

#include <boost/dll/shared_library.hpp>
#include <boost/dll/detail/get_mem_fn_type.hpp>
#include <boost/dll/detail/ctor_dtor.hpp>
#include <boost/dll/detail/type_info.hpp>
#include <boost/type_traits/is_object.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_function.hpp>



namespace boost {
namespace dll {
namespace experimental {

using boost::dll::detail::constructor;
using boost::dll::detail::destructor;

/*!
* \brief This class is an extension of \ref shared_library, which allows to load C++ symbols.
*
* This class allows type safe loading of overloaded functions, member-functions, constructors and variables.
* It also allows to overwrite classes so they can be loaded, while being declared with different names.
*
* \warning Is still very experimental.
*
* Currently known limitations:
*
* Member functions must be defined outside of the class to be exported. That is:
* \code
* //not exported:
* struct BOOST_SYMBOL_EXPORT my_class { void func() {}};
* //exported
* struct BOOST_SYMBOL_EXPORT my_class { void func();};
* void my_class::func() {};
* \endcode
*
* With the current analysis, the first version does get exported in MSVC.
* MinGW also does export it, BOOST_SYMBOL_EXPORT is written before it. To allow this on windows one can use
* BOOST_DLL_MEMBER_EXPORT for this, so that MinGW and MSVC can provide those functions. This does however not work with gcc on linux.
*
* Direct initialization of members.
* On linux the following member variable i will not be initialized when using the allocating constructor:
* \code
* struct BOOST_SYMBOL_EXPORT my_class { int i; my_class() : i(42) {} };
* \endcode
*
* This does however not happen when the value is set inside the constructor function.
*/
class smart_library {
    shared_library _lib;
    detail::mangled_storage_impl _storage;

public:
    /*!
     * Get the underlying shared_library
     */
    const shared_library &shared_lib() const {return _lib;}

    using mangled_storage = detail::mangled_storage_impl;
    /*!
    * Access to the mangled storage, which is created on construction.
    *
    * \throw Nothing.
    */
    const mangled_storage &symbol_storage() const {return _storage;}

    ///Overload, for current development.
    mangled_storage &symbol_storage() {return _storage;}

    //! \copydoc shared_library::shared_library()
    smart_library() BOOST_NOEXCEPT {};

    //! \copydoc shared_library::shared_library(const boost::dll::fs::path& lib_path, load_mode::type mode = load_mode::default_mode)
    smart_library(const boost::dll::fs::path& lib_path, load_mode::type mode = load_mode::default_mode) {
        _lib.load(lib_path, mode);
        _storage.load(lib_path);
    }

    //! \copydoc shared_library::shared_library(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode)
    smart_library(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode) {
        load(lib_path, mode, ec);
    }

    //! \copydoc shared_library::shared_library(const boost::dll::fs::path& lib_path, load_mode::type mode, boost::dll::fs::error_code& ec)
    smart_library(const boost::dll::fs::path& lib_path, load_mode::type mode, boost::dll::fs::error_code& ec) {
        load(lib_path, mode, ec);
    }
    /*!
     * copy a smart_library object.
     *
     * \param lib A smart_library to move from.
     *
     * \throw Nothing.
     */
     smart_library(const smart_library & lib) BOOST_NOEXCEPT
         : _lib(lib._lib), _storage(lib._storage)
     {}
   /*!
    * Move a smart_library object.
    *
    * \param lib A smart_library to move from.
    *
    * \throw Nothing.
    */
    smart_library(BOOST_RV_REF(smart_library) lib) BOOST_NOEXCEPT
        : _lib(boost::move(lib._lib)), _storage(boost::move(lib._storage))
    {}

    /*!
      * Construct from a shared_library object.
      *
      * \param lib A shared_library to move from.
      *
      * \throw Nothing.
      */
      explicit smart_library(const shared_library & lib) BOOST_NOEXCEPT
          : _lib(lib)
      {
          _storage.load(lib.location());
      }
     /*!
     * Construct from a shared_library object.
     *
     * \param lib A shared_library to move from.
     *
     * \throw Nothing.
     */
     explicit smart_library(BOOST_RV_REF(shared_library) lib) BOOST_NOEXCEPT
         : _lib(boost::move(static_cast<shared_library&>(lib)))
     {
         _storage.load(lib.location());
     }

    /*!
    * Destroys the smart_library.
    * `unload()` is called if the DLL/DSO was loaded. If library was loaded multiple times
    * by different instances of shared_library, the actual DLL/DSO won't be unloaded until
    * there is at least one instance of shared_library.
    *
    * \throw Nothing.
    */
    ~smart_library() BOOST_NOEXCEPT {};

    //! \copydoc shared_library::load(const boost::dll::fs::path& lib_path, load_mode::type mode = load_mode::default_mode)
    void load(const boost::dll::fs::path& lib_path, load_mode::type mode = load_mode::default_mode) {
        boost::dll::fs::error_code ec;
        _storage.load(lib_path);
        _lib.load(lib_path, mode, ec);

        if (ec) {
            boost::dll::detail::report_error(ec, "load() failed");
        }
    }

    //! \copydoc shared_library::load(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode)
    void load(const boost::dll::fs::path& lib_path, boost::dll::fs::error_code& ec, load_mode::type mode = load_mode::default_mode) {
        ec.clear();
        _storage.load(lib_path);
        _lib.load(lib_path, mode, ec);
    }

    //! \copydoc shared_library::load(const boost::dll::fs::path& lib_path, load_mode::type mode, boost::dll::fs::error_code& ec)
    void load(const boost::dll::fs::path& lib_path, load_mode::type mode, boost::dll::fs::error_code& ec) {
        ec.clear();
        _storage.load(lib_path);
        _lib.load(lib_path, mode, ec);
    }

    /*!
     * Load a variable from the referenced library.
     *
     * Unlinke shared_library::get this function will also load scoped variables, which also includes static class members.
     *
     * \note When mangled, MSVC will also check the type.
     *
     * \param name Name of the variable
     * \tparam T Type of the variable
     * \return A reference to the variable of type T.
     *
     * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
     */
    template<typename T>
    T& get_variable(const std::string &name) const {
        return _lib.get<T>(_storage.get_variable<T>(name));
    }

    /*!
     * Load a function from the referenced library.
     *
     * \b Example:
     *
     * \code
     * smart_library lib("test_lib.so");
     * typedef int      (&add_ints)(int, int);
     * typedef double (&add_doubles)(double, double);
     * add_ints     f1 = lib.get_function<int(int, int)>         ("func_name");
     * add_doubles  f2 = lib.get_function<double(double, double)>("func_name");
     * \endcode
     *
     * \note When mangled, MSVC will also check the return type.
     *
     * \param name Name of the function.
     * \tparam Func Type of the function, required for determining the overload
     * \return A reference to the function of type F.
     *
     * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
     */
    template<typename Func>
    Func& get_function(const std::string &name) const {
        return _lib.get<Func>(_storage.get_function<Func>(name));
    }

    /*!
     * Load a member-function from the referenced library.
     *
     * \b Example (import class is MyClass, which is available inside the library and the host):
     *
     * \code
     * smart_library lib("test_lib.so");
     *
     * typedef int      MyClass(*func)(int);
     * typedef int   MyClass(*func_const)(int) const;
     *
     * add_ints     f1 = lib.get_mem_fn<MyClass, int(int)>              ("MyClass::function");
     * add_doubles  f2 = lib.get_mem_fn<const MyClass, double(double)>("MyClass::function");
     * \endcode
     *
     * \note When mangled, MSVC will also check the return type.
     *
     * \param name Name of the function.
     * \tparam Class The class the function is a member of. If Class is const, the function will be assumed as taking a const this-pointer. The same applies for volatile.
     * \tparam Func Signature of the function, required for determining the overload
     * \return A pointer to the member-function with the signature provided
     *
     * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
     */
    template<typename Class, typename Func>
    typename boost::dll::detail::get_mem_fn_type<Class, Func>::mem_fn get_mem_fn(const std::string& name) const {
        return _lib.get<typename boost::dll::detail::get_mem_fn_type<Class, Func>::mem_fn>(
                _storage.get_mem_fn<Class, Func>(name)
        );
    }

    /*!
     * Load a constructor from the referenced library.
     *
     * \b Example (import class is MyClass, which is available inside the library and the host):
     *
     * \code
     * smart_library lib("test_lib.so");
     *
     * constructor<MyClass(int)    f1 = lib.get_mem_fn<MyClass(int)>();
     * \endcode
     *
     * \tparam Signature Signature of the function, required for determining the overload. The return type is the class which this is the constructor of.
     * \return A constructor object.
     *
     * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
     */
    template<typename Signature>
    constructor<Signature> get_constructor() const {
        return boost::dll::detail::load_ctor<Signature>(_lib, _storage.get_constructor<Signature>());
    }

    /*!
     * Load a destructor from the referenced library.
     *
     * \b Example (import class is MyClass, which is available inside the library and the host):
     *
     * \code
     * smart_library lib("test_lib.so");
     *
     * destructor<MyClass>     f1 = lib.get_mem_fn<MyClass>();
     * \endcode
     *
     * \tparam Class The class whose destructor shall be loaded
     * \return A destructor object.
     *
     * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
     *
     */
    template<typename Class>
    destructor<Class> get_destructor() const {
        return boost::dll::detail::load_dtor<Class>(_lib, _storage.get_destructor<Class>());
    }
    /*!
     * Load the typeinfo of the given type.
     *
     * \b Example (import class is MyClass, which is available inside the library and the host):
     *
     * \code
     * smart_library lib("test_lib.so");
     *
     * std::type_info &ti = lib.get_Type_info<MyClass>();
     * \endcode
     *
     * \tparam Class The class whose typeinfo shall be loaded
     * \return A reference to a type_info object.
     *
     * \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
     *
     */
    template<typename Class>
    const std::type_info& get_type_info() const
    {
        return boost::dll::detail::load_type_info<Class>(_lib, _storage);
    }
    /**
     * This function can be used to add a type alias.
     *
     * This is to be used, when a class shall be imported, which is not declared on the host side.
     *
     * Example:
     * \code
     * smart_library lib("test_lib.so");
     *
     * lib.add_type_alias<MyAlias>("MyClass"); //when using MyAlias, the library will look for MyClass
     *
     * //get the destructor of MyClass
     * destructor<MyAlias> dtor = lib.get_destructor<MyAlias>();
     * \endcode
     *
     *
     * \param name Name of the class the alias is for.
     *
     * \attention If the alias-type is not large enough for the imported class, it will result in undefined behaviour.
     * \warning The alias will only be applied for the type signature, it will not replace the token in the scoped name.
     */
    template<typename Alias> void add_type_alias(const std::string& name) {
        this->_storage.add_alias<Alias>(name);
    }

    //! \copydoc shared_library::unload()
    void unload() BOOST_NOEXCEPT {
        _storage.clear();
        _lib.unload();
    }

    //! \copydoc shared_library::is_loaded() const
    bool is_loaded() const BOOST_NOEXCEPT {
        return _lib.is_loaded();
    }

    //! \copydoc shared_library::operator!() const
    bool operator!() const BOOST_NOEXCEPT {
        return !is_loaded();
    }

    //! \copydoc shared_library::operator bool() const
    BOOST_EXPLICIT_OPERATOR_BOOL()

    //! \copydoc shared_library::has(const char* symbol_name) const
    bool has(const char* symbol_name) const BOOST_NOEXCEPT {
        return _lib.has(symbol_name);
    }

    //! \copydoc shared_library::has(const std::string& symbol_name) const
    bool has(const std::string& symbol_name) const BOOST_NOEXCEPT {
        return _lib.has(symbol_name);
    }

    //! \copydoc shared_library::assign(const shared_library& lib)
    smart_library& assign(const smart_library& lib) {
       _lib.assign(lib._lib);
       _storage.assign(lib._storage);
       return *this;
    }

    //! \copydoc shared_library::swap(shared_library& rhs)
    void swap(smart_library& rhs) BOOST_NOEXCEPT {
        _lib.swap(rhs._lib);
        _storage.swap(rhs._storage);
    }
};

/// Very fast equality check that compares the actual DLL/DSO objects. Throws nothing.
inline bool operator==(const smart_library& lhs, const smart_library& rhs) BOOST_NOEXCEPT {
    return lhs.shared_lib().native() == rhs.shared_lib().native();
}

/// Very fast inequality check that compares the actual DLL/DSO objects. Throws nothing.
inline bool operator!=(const smart_library& lhs, const smart_library& rhs) BOOST_NOEXCEPT {
    return lhs.shared_lib().native() != rhs.shared_lib().native();
}

/// Compare the actual DLL/DSO objects without any guarantee to be stable between runs. Throws nothing.
inline bool operator<(const smart_library& lhs, const smart_library& rhs) BOOST_NOEXCEPT {
    return lhs.shared_lib().native() < rhs.shared_lib().native();
}

/// Swaps two shared libraries. Does not invalidate symbols and functions loaded from libraries. Throws nothing.
inline void swap(smart_library& lhs, smart_library& rhs) BOOST_NOEXCEPT {
    lhs.swap(rhs);
}


#ifdef BOOST_DLL_DOXYGEN
/** Helper functions for overloads.
 *
 * Gets either a variable, function or member-function, depending on the signature.
 *
 * @code
 * smart_library sm("lib.so");
 * get<int>(sm, "space::value"); //import a variable
 * get<void(int)>(sm, "space::func"); //import a function
 * get<some_class, void(int)>(sm, "space::class_::mem_fn"); //import a member function
 * @endcode
 *
 * @param sm A reference to the @ref smart_library
 * @param name The name of the entity to import
 */
template<class T, class T2>
void get(const smart_library& sm, const std::string &name);
#endif

template<class T>
typename boost::enable_if<boost::is_object<T>, T&>::type get(const smart_library& sm, const std::string &name)

{
    return sm.get_variable<T>(name);
}

template<class T>
typename boost::enable_if<boost::is_function<T>, T&>::type get(const smart_library& sm, const std::string &name)
{
    return sm.get_function<T>(name);
}

template<class Class, class Signature>
auto get(const smart_library& sm, const std::string &name) -> typename detail::get_mem_fn_type<Class, Signature>::mem_fn
{
    return sm.get_mem_fn<Class, Signature>(name);
}


} /* namespace experimental */
} /* namespace dll */
} /* namespace boost */

#endif /* BOOST_DLL_SMART_LIBRARY_HPP_ */

/* smart_library.hpp
yygOpi6UurJXDw9XFHu9sRFbda4To3GVuPheN94qejlJj+kyFJEaL56ibyUnKCMXHH+8slDZ7LETurt3FCbc7RHJma5Ho1a3G/ZV7e7pX7T0LKKylq9Q2FV5TOrdm1pGX1bPaAIxQcfAhyPe+RduSPyQHLFAO/c0Q6Gu4C1bwgWY5PThDGYLu6Mq3O1JOuMnMPFCuS198LWOR4fLHhtto2bDCpI9uEI8OPQ/7ZwiKm+ZTvdanekYjSGjFSMVZedKkEJgzcO9/gom8DKZ9MUEVffF+5+5stEOApTCQI8s7FNIOlkTt7zEDqxCBEGndT+rxJQNDFeGtO3tI4L0HHAq005IupotV76r6hR0G6/THrLNn3tQGpmEZbEG2zTAMvtqMjhcZM8QEh89FinlcSH6+I6vpd/BxMY/0eZnIarqyI6Z7DIKuED+0y8/4P9YNXyQ5Xe4MNG0ZqHzNO41stI8vOn+w8aFcjnSwD+WRWr8tseqrV2TX1vOZdOdbKsS/6ftjvAfq02E9AX/IAg+63h3YBH1yz29zklmmXctAHDDFCvciTdlFoXQSuI63Jr264n0tNCw6nlLFg5LRT/EhijIUdGmZJKAQhID3nFWpbGBDiQbO+o47FwbNnJ0qCVKMWH4MzbJCI0l5aB6JEq9EGO03equuDguz/jEtYcSZHzQFK8xjucAy+0brkkkxrazMrkpzouAbkfY4nCtGTMwmhJ8wdVoCs5+dLLJ5UW6tZ8rs1iSkV2YmWLbPRMfgqgS9w40/JeM42KflWARgixQVG0Ep2yU0pQgdGlWwHd54XxsluZJsBK6yRI9lv2OgDksEa2xNJpO0iqRdeZX5Z+WIUxh1rUgMPjNUuOTLSaqk8AhMzSzdqlPEZ8jWWHrC8+VGWypHMoihyESExP9Rvlcw7gD41Q4mp5Spe5u2PZ95u87ghbPkfjLfRdXlEKx2h2d8uV5oFgDItagRhbCJ8hd1bPSNZKRFJRB4fKQhuN2OTfGsSZfzG+ZozXzNfmWGVfnGyqaiql5Tc5z0Mn5AyiOBjXCk7+fO8awYLjoHzLooibO0XgsOGXItF8tWuajFSmSKYGqomSUKRW1XRX7j8VnrwrI9jvQMpktD7Fa1YIfMDiCrwdpfAYVm0PRkuwZQcmqcsHU0AGzgYwVUqRSJT/eI6/wkghjBxKJg0LSbfdqT43KcFnmgaE0bwQ2BPrtsmCBDo8mmuocfeEkLnC7hzALpIr0yF4ZbdUKUk4E0YrTi0tT15nMzsY0aQRMew4kH8PswPmpAbhdKYQTHP2QYSBz2NYtVzBRF9aT0MYlkdfB227HyeWVQqq76BGb+vOkrXzS58IRO8FAlw4T3DQ/L9OpwBkBG86hgegrl+I8lm1pWRHruhMFd/wTcPDFvKE2zdeRLu3QxdltjxYvvCtXH/OXhWLpd8MK0W/KKoOxhSK0E1swaAWHpbdTaJ9Jq875k9xbECxIYgufA6rqmLQTyOjl9m0DwqGvJK3JrIm91yD6jGW6C5t6gUe6TDUkozC9/woKyPgk7ZacSSNLXQLx9sHdn8S7NoZr80/XVwLYNsLFTHD2UReNBW/utmL3rmLJROzhdXNqdt2VJ9sVIAEABEAZdtuchPbPgrjUXbRgP1/yK93kx7lXcu1NSV/Ou+pf000mY+3zJHK8L4ZYXb21sFfNrAntnYB70rp7MmpDTdKqtr8mwALAaItVxIJxAL/2EIK4qW5XS3QKjl0mTDHfpf49sMSmmZx7FpN8usEU1mA8gJsEFO3ox0co32tifdkHYNdkUHbWkiShBmSd7Txe9VaAXrFrzLtXiYtXdMM1ndpvgKP02USU055hUvdlRlUxz3yriWuVhr4sQ6s8z6DF5a5uOS4H/T3lQkPUmNER+aqDceR9jJ2/MtLQxCbksDmUcEBGp5InsCcYO85k/Bq6dvck5k32qnmZHwnVSyhxgT2pa5VJdVV0UBiKvgFXRnXubKkQ30WrBbJs1mOM0bjBZGx02i5IEViwxV4A83WUy/Fj+HCLNp+TnhptB63QEdaeT2L20tCn9JBFTZdw54TH2Rpnp1BP2fZEb9+2U41fkbiNP2tNuc5nnc6cU28fpZ7whDcz9J1SL9U/ycegOf4MOouv0lc4GcJSja8/DnDiWmaFte+4J7kARoBd/hsK9xoE4vv2FJANBC40iVd3sk2RRHwkQFc9hyAGZ4ghN2qvYov9WN6nTrIYC9AG7TnwJWVu49pDLLW+teKccd5dR88kmxiUEK3CWa9ygwlGeVeLeOiciaR6tbfru7NM4kJ9g3KA8bede6gd/3oyXeV6/bVMS3jhW7nZ4ZobkoMGMWoZfjp2x7ndWqk5/nXibKhrhUHb1SNdFQXNen7dLqBMOyQ1Nk4/Z5KVlzums5KMXkFN9nsjbLovADWKGbXl72Tv3ha52lNM83408YWVB9SfmgGjBBvkgebqyCi9g/Lp0nPfRiZSnhvRcrN8IPuFIocdzg8rV+Tb2lMw3ZXSxb4yKvlrtK+11OOw4io9CPQza/KxRC4rBJxe9nyp9U490tEnZDpOo5J5zrKTFsVxT4emi1QvGtjR8X6Y44mdz21QOuRX7mspc7xyTJadUDfJXphPYh5Y/22Hk3BmBN0LnaANIRL9wb/jG6+OJLYyNd0627tek36sTVu1MyXpyeStj1G5OJtvn5ZBMEMvSkI+gF9Er8OI7BbdY9Vz6gxkxQeeL021WL6R4zIe0yvN8S/REHpMK0fa6qouUs6sPWeORYi8gPJi0vwlQ32j8fKkK5lb5w3h1l7t6Jrhqa/OqGcWBiFDIJXDvM2M8RoghxIpClAv8CKvoixzmEoc9d3pUTeobHUn3m2EOeth+hDZBsOxMWVR5Nss2lFOqr5B72Zhp36WtA8ItQG7JySTcSJY2jjyNpSr62dlbIWzlhdBf7o41+gGTUOiDKl2MTrI+/8KF9Tf6ZY3OCKjyeuvupv2xTMW/uHdsRM7A7mWtwZXi9eXaLAUzzGwZRMf2uBWRmsoFd5x4/OiuvCcmnqUbJc+XTkyDo4ye3SR0C8f4enBSrGFsyLs3jjgZ1c2QOQ+tUdzA8t+g10G3hyK1/EBAay8kDY1oJcl/agyZtwONKRnDyRCi3dXPNqMffee7f5G7hzGpdLKQlM448xdkbOOOnyi7nFuVq5GaxzehfA/n6ilu9nD4TR1s2p1TL3o4VLL7h5NhDNt6mP3N8mB2ChqMtOMOgy99t4TKY+LDALNUN1wIfXSlb1v2UGwNywFGmt8tg3/FJh7QSI5xLrjfGYnmn5gX5rgH3UgGsLuX7JZYOtmgwI6684HU61o0chwKm3i4QnCcF2R3j5Pf/EqLQo5oNsm9cKDJju7oe3S7pFIWfTJUF33tgFQGLG11FB3jgxf27AgX7iZS/RNQGIosq37qzmISuQxuJYnBavIY97GaEUiyyI9JM5x6fR3lDH0X2XkEfzj+7bzckHLLTG+uy+gf8b0dBB6uZuZoxk/3nkdku2RiAKEO0N2hj6s5wRgsbL4IQQi/qcw805+i02w6tm1fDAWtPxVTjq9mf9rSqKfsPiBZHkx4IirHP8m2sF3EQCHD+WjN7COSyO9aCrwjClEIffwX3EVqJ8PVPF/niyeZwky7tygEh/7MOvYquFadepWqJx+FllyBsN9avYYOHTQoCKqJtgInAdAfuHQIADqfHz4H9oARAB+qeYhwEviCvEAXy5rink/c3MAcsTBf8BYXYskjiBBwsJTAovkhNuT5vz40GmRsYCzwfGCRKLh/DYM9+70APr5isgxEbIMYViCoH6OCPwa/P38sEe4PhA0/I7oSkn7EPcg7YD/AlsB6JTlPj1DGn+Uy9Cfn0EkCij5LNm7gYPvDhYGkQUOZbM5xg3RkyN6wUeAbM8A5gPOz9m9RYSXNNVI5Xqbv3+bcyhFItDjkqOBncGhpwap78Da7w72z+xExi9GRP4BC41krOBUc29z71j3YJjodMd/03uS29C1Jf20DM8MDU4NzKSKgpyw04YjzP9q1Bqdno68L2lN7c4MDVz1JucGBaGEQkHiwwmgL/NjAAUh9WMMlpdZ0ofp/ieZmk/Zj8/fWQhN5I+ojaVG/BcMNecFrsZFp2wVQeC+NjuNOI2DdYXWpmallw3mtNcSHTrpfDVE/p+WjfVg2aXeaURFsrzkDykypFGIwA+66FIZMJ8YPqCFk/9fMzF8BDlXXrMnm2TCLrEyENb3bOm3FNtJ9sHH2YibTmAJy8F7vGybSzVc4zxvJbze46lZSuvFrUmF0EoFtCvu6rUnDkjdyujoU3xTlIEBervE5ynGwliJe+MKSkERWRTeR9FlLH8bJKMnxHs7gTcnpNX46iHYvL5lklAJ/mgmesrLrvwFSvT3bWYyZi7C+q+8n/lInnqgagioGPJo8zMGvouy706ls88xa1M3gtw5exZdDJk444Zc6xUkWTGj9f5SwZHWjCFIFV03MhDkchdM5UXiJicKT+vm217a6Iu51BkRC+HOAlUIXwg964X65Im5sxN3/DPMmiiGuy5dFsRpFsS4XUSWysgQKNm9yDkmszPIJJDlbCcrPS5yODBUyoD5eQZ+fDOznWY0CDhvKFhpeALmc9ErDjcu03kfPo3yHLdnktVDXjxbMaA+cL6sIiPmeb+n+uWVKuqkvY5oYr49FHScCIlrKvLtZmA8KTjS65LLZ0B8qYkXMl5zrmWVPc98vWbw4W5aUoBAeXPkd8ULvxoiwry3aWDll8AdV0wd9xBsna0d5Xi04Va8d8Cl1U5WilLsjbtHIPj5o83Ogg5Z507Nxsyn7ZcqZB0KAJcFjpyYuZVDE0V+3GjphVQH0GsbNLcU4uk+pOKcvz1IjhhRtIbtadp4zn0yMTYdWeDMUDg5ID5kxCeCu0cSksmOB061SJIZg0FOO8235lDt50aaS2qraeRLzgCEME//WP+SsWHZsfPqOrhzcQKVC0SVUFusRByD7qCnfFAGWVJEpOBcjCE6WlkkK9lsQeB1ovmSZWncZQ4lYhPr5Lhrodhq30zSDSdGNU/LVUD87kGvnNmFmY4mc8PIMqFl8GHBgwMHOwjs8HheyIZf8lH1X9EMqH0857p9YneOuPmFfx/pTJ5Z7PbIR8KgICD4QfdW+/z5Qf/R5+fr/5PdAHsnsZPLh1ZZXVp4/3aZ83X8/DeWQ2o21V4gGl+z+IguDSA5+anPUQ5FpF4vOGtE/CmBycDnGoAaTrcuubrmRJgax/MlGOVxfv06XE0ALec4M1fW2lG+UGnd2N0PCo5kMRtNuQFiB58qENP8h/c7sbMmN5JiXyxTNvg2oruwnLVgQXy9MmDd+yF0eG8/UvmKKGnXfQWcczz6OQ1uAamAsJ021ua+Zig7wDjAw2NBgZDgJi/4R5KLfb+y3iP9XEg4K++QoVkhkRsPnkM3JQ99X7bJlaqZz2KCNi3YtSBXLwg5KOXCPCo0JodlsrlvZ9ffKOpshzDEhrY3Co7588hWCjNYmeYirpGiDzO2+d07rUn/RnRWhGfd9oo9OMTn0/TlK33YwOcsB4cZKP2EIt51wgBzg4myC9EXg4cj4LJKlITRZIxuK88QUFFgXPCH/RqlxlYPQJKfJO8Oex57X4zfk44u6C9vb3IoU+7kreGY6fHJQKydQ9vLAxHXVlV3dRfX+7GzvP9oqAO/so8tAQJESlCE4LBPa75ZfFev8tnl5acsyobbl1Li6i7iBdqHXcBAhDj+Z6qQjQPP4cPw87WDaRWrgG3X5HZ+uHmzvimuZCp3QeVBGNlG1BvszXK2KJFkvWUWxGz89fuKX7a3N8EhwhHpfhq4WaCaoSUmIl5eXrjpvvd+RjD79qShFKR/6m5nWhdQr4gng0/KW0H9eWBhDsiUV/jq82QPB9s1YLcsn5G655IZ6KuLOJvPpILLncauRlsobsJCcufh+6GFxQe8TbkuDTRPGXuyi41kMbXKA9rn58A1NiDgmCn+AEblaOvasQkuk2/YwDWZtz7PMcUegYDvcv/ySEWheeWCuOhrRTTOTV6xfNtyxP7UKX/jLPP5QAUiogQpVtr2NUlJRXjBLBOyN6FPMXw+kU2ICbRfddpZJWFgfq/2zi7G060Zzh9kL6E8+rK4uDMWjz3yR905Dg84WtYcHVTasH/a1UwkFx46KwSlFzLr85WE1ZsOKlIbfVRzYlXli39aaGj+2kOnDKhnWnGP5qHszFWwIkT5dFx+89w4zo9hgQdV44Vea1hv2wxt5mSvog29t4lMaX15NyB96GHmYqJZoil31y5+Mk2v6+cKmgTaFobzfKw8YEvm7ui0mxYMjybxlqXAalXbHohZOqMgkrczAZkohn566O9Ys+DEIh8/3wzt5oUagn9o8Ti6POduJshI+N7E2M5Ui5u7y+6966WBwTeWdxtswfj+zVc5fsW8ADnFaZFKWKQLMvzzJiqGJxv/Mvrjvv1K3zI3SQR6KYOXHrQLwxbldqQx01e5cJ1CwnvahjqVc/ZEZRvHJ6MUW/eDZF/380+OMwh9rZeGfsxvFRHsDol8e4XZaGEXCqVSmLR7coM8vo1idwe++OMQUIGZHpcbjg9tL1ojeAzY5kcZ8hsN4xnez6NIBsQSdsmCWGKquQ/kYJQIGcmF+znDqG7eVmvZ8lJkzmYw8VLn7HBmaFViDiYrFdllRdmMab5Nn53LDuiYgcqaU7UThHGVCjYYjxShazQK5b3uXQ/HXpWB07iu05Wj3rgnvZPMrvIxuk9saZNOJVcIjDw9w9uEOEdl3o3HNAK3toZ0JZJ3wqJZ3ntiPMeZLoXvgCk8OlfCUNc8rc2kvXgfxskbR6YV3ZEeEv5bZgDZFscgGFCG0y2CdBYvD3nbLphV/1Hb2QTxKFkj+CZi9dsqYpFQzjiXMDJMHCaatQKkkEY6z0e9RVu14lx5aiqj2mzgj6OGimt7bU7LW1moAMkkA5RcrbyfxLs2bv4pv2+8qNq/HK4POvw2kyR0CVjIwjmQQEhdJok7VSQXawHByh+khzDgiZdK8VvKW7+61ns9pTllI6WlZQQ0JBWELgIIlJReAmqyWhDDwIavD+km3+8SrI5VvOEyy8P9Qz3jR94Da3ivQsbqYI6lmOqA7YYIoWq0jTkB6heiJRGIx0QxkspvBtI2UKbvMhtev50EVXMBGl3NMpsx9021Ag5qVfUIiEjZNXH7YmVG3GnUa5TiwZILVvDbmKJa8R96QsFp/Ky63qsRc5jtCTDVZ4tdR5hJAfhulfAXnvSPdwdBgdPjVEM8zW7hzBjCE8HVv6PmL/A7V0S6UTH+Dw3jA7PFMxGnlqAcDnNV8Ko1Zevb9U6G43NwA3+9bAi2oV0lQb82RrPGWdKtF2iWk99q1SYIW6AQpPPoEg+Bzqy54I0tc2PvRDhWvQn+QEiY+d6FBOjuhVoTabcfZC8uNGK56Ltole8HjrRT806W8/rXpfh4NWD19h7UmRnV2j8Qr/hyJN7SSZzjhd/7FiR1cf1RQf2nmrRwy+L+zVT1r+AfvcZPuAoChu6j0fgrXfBjb0FhKNMZ3pUJsteIxF7tRbw9XjjMk3HaTlGZFZTWV469X2GZgsTGWZ8nvrVpuWsd0hR/EtDuRXbYQhhPe+kUYh8/aWTy
*/