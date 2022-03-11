//  Copyright 2016 Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_SMART_LIBRARY_HPP_
#define BOOST_DLL_SMART_LIBRARY_HPP_

/// \file boost/dll/smart_library.hpp
/// \warning Extremely experimental! Requires C++14! Will change in next version of Boost! boost/dll/smart_library.hpp is not included in boost/dll.hpp
/// \brief Contains the boost::dll::experimental::smart_library class for loading mangled symbols.

#include <boost/dll/config.hpp>
#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows
#   include <boost/dll/detail/demangling/msvc.hpp>
#else
#   include <boost/dll/detail/demangling/itanium.hpp>
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
T& get(const smart_library& sm, const std::string &name, typename boost::enable_if<boost::is_object<T>,T>::type* = nullptr)

{
    return sm.get_variable<T>(name);
}

template<class T>
auto get(const smart_library& sm, const std::string &name, typename boost::enable_if<boost::is_function<T>>::type* = nullptr)
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
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
*/