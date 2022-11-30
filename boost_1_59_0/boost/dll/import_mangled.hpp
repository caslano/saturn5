// Copyright 2015-2018 Klemens D. Morgenstern
// Copyright Antony Polukhin, 2019-2022
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_DLL_IMPORT_MANGLED_HPP_
#define BOOST_DLL_IMPORT_MANGLED_HPP_

/// \file boost/dll/import_mangled.hpp
/// \warning Extremely experimental! Requires C++11! Will change in next version of Boost! boost/dll/import_mangled.hpp is not included in boost/dll.hpp
/// \brief Contains the boost::dll::experimental::import_mangled function for importing mangled symbols.

#include <boost/dll/config.hpp>
#if (__cplusplus < 201103L) && (!defined(_MSVC_LANG) || _MSVC_LANG < 201103L)
#  error This file requires C++11 at least!
#endif

#include <boost/make_shared.hpp>
#include <boost/move/move.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/dll/detail/import_mangled_helpers.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_object.hpp>


#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace experimental {

namespace detail
{

template <class ... Ts>
class mangled_library_function {
    // Copying of `boost::dll::shared_library` is very expensive, so we use a `shared_ptr` to make it faster.
    boost::shared_ptr<shared_library> lib_;
    function_tuple<Ts...>   f_;
public:
    constexpr mangled_library_function(const boost::shared_ptr<shared_library>& lib, Ts*... func_ptr) BOOST_NOEXCEPT
        : lib_(lib)
        , f_(func_ptr...)
    {}


    // Compilation error at this point means that imported function
    // was called with unmatching parameters.
    //
    // Example:
    // auto f = dll::import_mangled<void(int), void(double)>("function", "lib.so");
    // f("Hello");  // error: invalid conversion from 'const char*' to 'int'
    // f(1, 2);     // error: too many arguments to function
    // f();         // error: too few arguments to function
    template <class... Args>
    auto operator()(Args&&... args) const
        -> decltype( f_(static_cast<Args&&>(args)...) )
    {
        return f_(static_cast<Args&&>(args)...);
    }
};


template<class Class, class Sequence>
class mangled_library_mem_fn;

template <class Class, class ... Ts>
class mangled_library_mem_fn<Class, sequence<Ts...>> {
    // Copying of `boost::dll::shared_library` is very expensive, so we use a `shared_ptr` to make it faster.
    typedef mem_fn_tuple<Ts...> call_tuple_t;
    boost::shared_ptr<shared_library>   lib_;
    call_tuple_t f_;

public:
    constexpr mangled_library_mem_fn(const boost::shared_ptr<shared_library>& lib, typename Ts::mem_fn... func_ptr) BOOST_NOEXCEPT
        : lib_(lib)
        , f_(func_ptr...)
    {}

    template <class ClassIn, class... Args>
    auto operator()(ClassIn *cl, Args&&... args) const
        -> decltype( f_(cl, static_cast<Args&&>(args)...) )
    {
        return f_(cl, static_cast<Args&&>(args)...);
    }
};




// simple enough to be here
template<class Seq>  struct is_variable : boost::false_type {};
template<typename T> struct is_variable<sequence<T>> : boost::is_object<T> {};

template <class Sequence,
          bool isFunction = is_function_seq<Sequence>::value,
          bool isMemFn    = is_mem_fn_seq  <Sequence>::value,
          bool isVariable = is_variable    <Sequence>::value>
struct mangled_import_type;

template <class ...Args>
struct mangled_import_type<sequence<Args...>, true,false,false> //is function
{
    typedef boost::dll::experimental::detail::mangled_library_function<Args...> type;
    static type make(
           const boost::dll::experimental::smart_library& p,
           const std::string& name)
    {
        return type(
                boost::make_shared<shared_library>(p.shared_lib()),
                boost::addressof(p.get_function<Args>(name))...);
    }
};

template <class Class, class ...Args>
struct mangled_import_type<sequence<Class, Args...>, false, true, false> //is member-function
{
    typedef typename boost::dll::experimental::detail::make_mem_fn_seq<Class, Args...>::type actual_sequence;
    typedef typename boost::dll::experimental::detail::mangled_library_mem_fn<Class, actual_sequence> type;


    template<class ... ArgsIn>
    static type make_impl(
            const boost::dll::experimental::smart_library& p,
            const std::string & name,
            sequence<ArgsIn...> * )
    {
        return type(boost::make_shared<shared_library>(p.shared_lib()),
                    p.get_mem_fn<typename ArgsIn::class_type, typename ArgsIn::func_type>(name)...);
    }

    static type make(
           const boost::dll::experimental::smart_library& p,
           const std::string& name)
    {
        return make_impl(p, name, static_cast<actual_sequence*>(nullptr));
    }

};

template <class T>
struct mangled_import_type<sequence<T>, false, false, true> //is variable
{
    typedef boost::shared_ptr<T> type;

    static type make(
           const boost::dll::experimental::smart_library& p,
           const std::string& name)
    {
        return type(
                boost::make_shared<shared_library>(p.shared_lib()),
                boost::addressof(p.get_variable<T>(name)));
    }

};


} // namespace detail


#ifndef BOOST_DLL_DOXYGEN
#   define BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE inline typename \
    boost::dll::experimental::detail::mangled_import_type<boost::dll::experimental::detail::sequence<Args...>>::type
#endif

/*
 * Variants:
 * import_mangled<int>("Stuff");
 * import_mangled<thingy(xyz)>("Function");
 * import mangled<thingy, void(int)>("Function");
 */

/*!
* Returns callable object or boost::shared_ptr<T> that holds the symbol imported
* from the loaded library. Returned value refcounts usage
* of the loaded shared library, so that it won't get unload until all copies of return value
* are not destroyed.
*
* For importing symbols by \b alias names use \forcedlink{import_alias} method.
*
* \b Examples:
*
* \code
* boost::function<int(int)> f = import_mangled<int(int)>("test_lib.so", "integer_func_name");
*
* auto f_cpp11 = import_mangled<int(int)>("test_lib.so", "integer_func_name");
* \endcode
*
* \code
* boost::shared_ptr<int> i = import_mangled<int>("test_lib.so", "integer_name");
* \endcode
*
* Additionally you can also import overloaded symbols, including member-functions.
*
* \code
* auto fp = import_mangled<void(int), void(double)>("test_lib.so", "func");
* \endcode
*
* \code
* auto fp = import_mangled<my_class, void(int), void(double)>("test_lib.so", "func");
* \endcode
*
* If qualified member-functions are needed, this can be set by repeating the class name with const or volatile.
* All following signatures after the redifintion will use this, i.e. the latest.
*
* * * \code
* auto fp = import_mangled<my_class, void(int), void(double),
*                          const my_class, void(int), void(double)>("test_lib.so", "func");
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


template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const boost::dll::fs::path& lib, const char* name,
    load_mode::type mode = load_mode::default_mode)
{
    typedef typename boost::dll::experimental::detail::mangled_import_type<
                     boost::dll::experimental::detail::sequence<Args...>> type;

    boost::dll::experimental::smart_library p(lib, mode);
    //the load
    return type::make(p, name);
}



//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const boost::dll::fs::path& lib, const std::string& name,
    load_mode::type mode = load_mode::default_mode)
{
    return import_mangled<Args...>(lib, name.c_str(), mode);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const smart_library& lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    return type::make(lib, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const smart_library& lib, const std::string& name) {
    return import_mangled<Args...>(lib, name.c_str());
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(smart_library) lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    return type::make(lib, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(smart_library) lib, const std::string& name) {
    return import_mangled<Args...>(boost::move(lib), name.c_str());
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const shared_library& lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    boost::shared_ptr<boost::dll::experimental::smart_library> p = boost::make_shared<boost::dll::experimental::smart_library>(lib);
    return type::make(p, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const shared_library& lib, const std::string& name) {
    return import_mangled<Args...>(lib, name.c_str());
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(shared_library) lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    boost::dll::experimental::smart_library p(boost::move(lib));

    return type::make(p, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(shared_library) lib, const std::string& name) {
    return import_mangled<Args...>(boost::move(lib), name.c_str());
}

#undef BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE

}}}


#endif /* BOOST_DLL_IMPORT_MANGLED_HPP_ */

/* import_mangled.hpp
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
*/