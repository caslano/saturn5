// Copyright 2015-2018 Klemens D. Morgenstern
// Copyright Antony Polukhin, 2019-2022
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_IMPORT_CLASS_HPP_
#define BOOST_DLL_IMPORT_CLASS_HPP_

/// \file boost/dll/import_class.hpp
/// \warning Extremely experimental! Requires C++11! Will change in next version of Boost! boost/dll/import_class.hpp is not included in boost/dll.hpp
/// \brief Contains the boost::dll::experimental::import_class function for importing classes.

#include <boost/dll/smart_library.hpp>
#include <boost/dll/import_mangled.hpp>
#include <memory>

#if (__cplusplus < 201103L) && (!defined(_MSVC_LANG) || _MSVC_LANG < 201103L)
#  error This file requires C++11 at least!
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace experimental {

namespace detail
{

template<typename T>
struct deleter
{
    destructor<T> dtor;
    bool use_deleting;

    deleter(const destructor<T> & dtor, bool use_deleting = false) :
        dtor(dtor), use_deleting(use_deleting) {}

    void operator()(T*t)
    {
        if (use_deleting)
            dtor.call_deleting(t);
        else
        {
            dtor.call_standard(t);
            //the thing is actually an array, so delete[]
            auto p = reinterpret_cast<char*>(t);
            delete [] p;
        }
    }
};

template<class T, class = void>
struct mem_fn_call_proxy;

template<class Class, class U>
struct mem_fn_call_proxy<Class, boost::dll::experimental::detail::mangled_library_mem_fn<Class, U>>
{
    typedef boost::dll::experimental::detail::mangled_library_mem_fn<Class, U> mem_fn_t;
    Class* t;
    mem_fn_t & mem_fn;

    mem_fn_call_proxy(mem_fn_call_proxy&&) = default;
    mem_fn_call_proxy(const mem_fn_call_proxy & ) = delete;
    mem_fn_call_proxy(Class * t, mem_fn_t & mem_fn)
                : t(t), mem_fn(mem_fn) {}

    template<typename ...Args>
    auto operator()(Args&&...args) const
    {
        return mem_fn(t, std::forward<Args>(args)...);
    }

};

template<class T, class Return, class ...Args>
struct mem_fn_call_proxy<T, Return(Args...)>
{
    T* t;
    const std::string &name;
    smart_library &_lib;

    mem_fn_call_proxy(mem_fn_call_proxy&&) = default;
    mem_fn_call_proxy(const mem_fn_call_proxy&) = delete;
    mem_fn_call_proxy(T *t, const std::string &name, smart_library & _lib)
        : t(t), name(name), _lib(_lib) {};

    Return operator()(Args...args) const
    {
        auto f = _lib.get_mem_fn<T, Return(Args...)>(name);
        return (t->*f)(static_cast<Args>(args)...);
    }
};

}

template<typename T>
class imported_class;

template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib, Args...args);
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib, const std::string & alias_name, Args...args);
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib, std::size_t size, Args...args);
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib, std::size_t size,
             const std::string & alias_name, Args...args);


/*! This class represents an imported class.
 *
 * \note It must be constructed via \ref boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
 *
 * \tparam The type or type-alias of the imported class.
 */
template<typename T>
class imported_class
{
    smart_library _lib;
    std::unique_ptr<T, detail::deleter<T>> _data;
    bool _is_allocating;
    std::size_t _size;
    const std::type_info& _ti;

    template<typename ... Args>
    inline std::unique_ptr<T, detail::deleter<T>> make_data(const smart_library& lib, Args ... args);
    template<typename ... Args>
    inline std::unique_ptr<T, detail::deleter<T>> make_data(const smart_library& lib, std::size_t size, Args...args);

    template<typename ...Args>
    imported_class(detail::sequence<Args...> *, const smart_library& lib,  Args...args);

    template<typename ...Args>
    imported_class(detail::sequence<Args...> *, const smart_library& lib, std::size_t size,  Args...args);

    template<typename ...Args>
    imported_class(detail::sequence<Args...> *, smart_library&& lib,  Args...args);

    template<typename ...Args>
    imported_class(detail::sequence<Args...> *, smart_library&& lib, std::size_t size,  Args...args);
public:
    //alias to construct with explicit parameter list
    template<typename ...Args>
    static imported_class<T> make(smart_library&& lib,  Args...args)
    {
        typedef detail::sequence<Args...> *seq;
        return imported_class(seq(), boost::move(lib), static_cast<Args>(args)...);
    }

    template<typename ...Args>
    static imported_class<T> make(smart_library&& lib, std::size_t size,  Args...args)
    {
        typedef detail::sequence<Args...> *seq;
        return imported_class(seq(), boost::move(lib), size, static_cast<Args>(args)...);
    }
    template<typename ...Args>
    static imported_class<T> make(const smart_library& lib,  Args...args)
    {
        typedef detail::sequence<Args...> *seq;
        return imported_class(seq(), lib, static_cast<Args>(args)...);
    }

    template<typename ...Args>
    static imported_class<T> make(const smart_library& lib, std::size_t size,  Args...args)
    {
        typedef detail::sequence<Args...> *seq;
        return imported_class(seq(), lib, size, static_cast<Args>(args)...);
    }

    typedef imported_class<T> base_t;
    ///Returns a pointer to the underlying class
    T* get() {return _data.get();}
    imported_class() = delete;

    imported_class(imported_class&) = delete;
    imported_class(imported_class&&) = default;                ///<Move constructor
    imported_class& operator=(imported_class&) = delete;
    imported_class& operator=(imported_class&&) = default;  ///<Move assignmend

    ///Check if the imported class is move-constructible
    bool is_move_constructible() {return !_lib.symbol_storage().template get_constructor<T(T&&)>     ().empty();}
    ///Check if the imported class is move-assignable
    bool is_move_assignable()    {return !_lib.symbol_storage().template get_mem_fn<T, T&(T&&)>     ("operator=").empty();}
    ///Check if the imported class is copy-constructible
    bool is_copy_constructible() {return !_lib.symbol_storage().template get_constructor<T(const T&)>().empty();}
    ///Check if the imported class is copy-assignable
    bool is_copy_assignable()    {return !_lib.symbol_storage().template get_mem_fn<T, T&(const T&)>("operator=").empty();}

    imported_class<T> copy() const; ///<Invoke the copy constructor. \attention Undefined behaviour if the imported object is not copy constructible.
    imported_class<T> move();       ///<Invoke the move constructor. \attention Undefined behaviour if the imported object is not move constructible.

    ///Invoke the copy assignment. \attention Undefined behaviour if the imported object is not copy assignable.
    void copy_assign(const imported_class<T> & lhs) const;
    ///Invoke the move assignment. \attention Undefined behaviour if the imported object is not move assignable.
    void move_assign(      imported_class<T> & lhs);

    ///Check if the class is loaded.
    explicit operator bool() const  {return _data;}

    ///Get a const reference to the std::type_info.
    const std::type_info& get_type_info() {return _ti;};

    /*! Call a member function. This returns a proxy to the function.
     * The proxy mechanic mechanic is necessary, so the signaute can be passed.
     *
     * \b Example
     *
     * \code
     * im_class.call<void(const char*)>("function_name")("MyString");
     * \endcode
     */
    template<class Signature>
    const detail::mem_fn_call_proxy<T, Signature> call(const std::string& name)
    {
        return detail::mem_fn_call_proxy<T, Signature>(_data.get(), name, _lib);
    }
    /*! Call a qualified member function, i.e. const and or volatile.
     *
     * \b Example
     *
     * \code
     * im_class.call<const type_alias, void(const char*)>("function_name")("MyString");
     * \endcode
     */
    template<class Tin, class Signature, class = boost::enable_if<detail::unqalified_is_same<T, Tin>>>
    const detail::mem_fn_call_proxy<Tin, Signature> call(const std::string& name)
    {
        return detail::mem_fn_call_proxy<Tin, Signature>(_data.get(), name, _lib);
    }
    ///Overload of ->* for an imported method.
    template<class Tin, class T2>
    const detail::mem_fn_call_proxy<Tin, boost::dll::experimental::detail::mangled_library_mem_fn<Tin, T2>>
            operator->*(detail::mangled_library_mem_fn<Tin, T2>& mn)
    {
        return detail::mem_fn_call_proxy<Tin, boost::dll::experimental::detail::mangled_library_mem_fn<Tin, T2>>(_data.get(), mn);
    }

    ///Import a method of the class.
    template <class ...Args>
    typename boost::dll::experimental::detail::mangled_import_type<boost::dll::experimental::detail::sequence<T, Args...>>::type
    import(const std::string & name)
    {
        return boost::dll::experimental::import_mangled<T, Args...>(_lib, name);
    }
};



//helper function, uses the allocating
template<typename T>
template<typename ... Args>
inline std::unique_ptr<T, detail::deleter<T>> imported_class<T>::make_data(const smart_library& lib, Args ... args)
{
    constructor<T(Args...)> ctor = lib.get_constructor<T(Args...)>();
    destructor<T>           dtor = lib.get_destructor <T>();

    if (!ctor.has_allocating() || !dtor.has_deleting())
    {
        boost::dll::fs::error_code ec;

        ec = boost::dll::fs::make_error_code(
            boost::dll::fs::errc::bad_file_descriptor
        );

        // report_error() calls dlsym, do not use it here!
        boost::throw_exception(
            boost::dll::fs::system_error(
                ec, "boost::dll::detail::make_data() failed: no allocating ctor or dtor was found"
            )
        );
    }

     return std::unique_ptr<T, detail::deleter<T>> (
            ctor.call_allocating(static_cast<Args>(args)...),
            detail::deleter<T>(dtor, false /* not deleting dtor*/));
}

//helper function, using the standard
template<typename T>
template<typename ... Args>
inline std::unique_ptr<T, detail::deleter<T>> imported_class<T>::make_data(const smart_library& lib, std::size_t size, Args...args)
{
    constructor<T(Args...)> ctor = lib.get_constructor<T(Args...)>();
    destructor<T>           dtor = lib.get_destructor <T>();

    if (!ctor.has_standard() || !dtor.has_standard())
    {
        boost::dll::fs::error_code ec;

        ec = boost::dll::fs::make_error_code(
            boost::dll::fs::errc::bad_file_descriptor
        );

        // report_error() calls dlsym, do not use it here!
        boost::throw_exception(
            boost::dll::fs::system_error(
                ec, "boost::dll::detail::make_data() failed: no regular ctor or dtor was found"
            )
        );
    }

    T *data = reinterpret_cast<T*>(new char[size]);

    ctor.call_standard(data, static_cast<Args>(args)...);

    return std::unique_ptr<T, detail::deleter<T>> (
            reinterpret_cast<T*>(data),
            detail::deleter<T>(dtor, false /* not deleting dtor*/));

}


template<typename T>
template<typename ...Args>
imported_class<T>::imported_class(detail::sequence<Args...> *, const smart_library & lib,  Args...args)
    : _lib(lib),
      _data(make_data<Args...>(lib, static_cast<Args>(args)...)),
      _is_allocating(false),
      _size(0),
      _ti(lib.get_type_info<T>())
{

}

template<typename T>
template<typename ...Args>
imported_class<T>::imported_class(detail::sequence<Args...> *, const smart_library & lib, std::size_t size,  Args...args)
    : _lib(lib),
      _data(make_data<Args...>(lib, size, static_cast<Args>(args)...)),
      _is_allocating(true),
      _size(size),
      _ti(lib.get_type_info<T>())
{

}

template<typename T>
template<typename ...Args>
imported_class<T>::imported_class(detail::sequence<Args...> *, smart_library && lib,  Args...args)
    : _lib(boost::move(lib)),
      _data(make_data<Args...>(lib, static_cast<Args>(args)...)),
      _is_allocating(false),
      _size(0),
      _ti(lib.get_type_info<T>())
{

}

template<typename T>
template<typename ...Args>
imported_class<T>::imported_class(detail::sequence<Args...> *, smart_library && lib, std::size_t size,  Args...args)
    : _lib(boost::move(lib)),
      _data(make_data<Args...>(lib, size, static_cast<Args>(args)...)),
      _is_allocating(true),
      _size(size),
      _ti(lib.get_type_info<T>())
{

}

template<typename T>
inline imported_class<T> boost::dll::experimental::imported_class<T>::copy() const
{
    if (this->_is_allocating)
        return imported_class<T>::template make<const T&>(_lib, *_data);
    else
        return imported_class<T>::template make<const T&>(_lib, _size, *_data);
}

template<typename T>
inline imported_class<T> boost::dll::experimental::imported_class<T>::move()
{
    if (this->_is_allocating)
        return imported_class<T>::template make<T&&>(_lib, *_data);
    else
        return imported_class<T>::template make<T&&>(_lib, _size, *_data);
}

template<typename T>
inline void boost::dll::experimental::imported_class<T>::copy_assign(const imported_class<T>& lhs) const
{
    this->call<T&(const T&)>("operator=")(*lhs._data);
}

template<typename T>
inline void boost::dll::experimental::imported_class<T>::move_assign(imported_class<T>& lhs)
{
    this->call<T&(T&&)>("operator=")(static_cast<T&&>(*lhs._data));
}



/*!
* Returns an instance of \ref imported_class which allows to call or import more functions.
* It takes a copy of the smart_libray, so no added type_aliases will be visible,
* for the object.
*
* Few compilers do implement an allocating constructor, which allows the construction
* of the class without knowing the size. That is not portable, so the actual size of the class
* shall always be provided.
*
* \b Example:
*
* \code
* auto import_class<class type_alias, const std::string&, std::size_t>(lib, "class_name", 20, "param1", 42);
* \endcode
*
* In this example we construct an instance of the class "class_name" with the size 20, which has "type_alias" as an alias,
* through a constructor which takes a const-ref of std::string and an std::size_t parameter.
*
* \tparam T Class type or alias
* \tparam Args Constructor argument list.
* \param lib Path to shared library or shared library to load function from.
* \param name Null-terminated C or C++ mangled name of the function to import. Can handle std::string, char*, const char*.
* \param mode An mode that will be used on library load.
*
* \return class object.
*
* \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
*       Overload that accepts path also throws std::bad_alloc in case of insufficient memory.
*/
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib_, std::size_t size, Args...args)
{
    smart_library lib(lib_);

    return imported_class<T>::template make<Args...>(boost::move(lib), size, static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib_, Args...args)
{
    smart_library lib(lib_);
    return imported_class<T>::template make<Args...>(boost::move(lib), static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib_, const std::string & alias_name, Args...args)
{
    smart_library lib(lib_);
    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(boost::move(lib), static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib_, std::size_t size, const std::string & alias_name, Args...args)
{
    smart_library lib(lib_);

    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(boost::move(lib), size, static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(const smart_library& lib_, const std::string & alias_name, std::size_t size, Args...args)
{
    smart_library lib(lib_);

    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(boost::move(lib), size, static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library && lib, Args...args)
{
    return imported_class<T>::template make<Args...>(boost::move(lib), static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library && lib, const std::string & alias_name, Args...args)
{
    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(boost::move(lib), static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library && lib, std::size_t size, Args...args)
{
    return imported_class<T>::template make<Args...>(boost::move(lib), size, static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library && lib, std::size_t size, const std::string & alias_name, Args...args)
{
    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(boost::move(lib), size, static_cast<Args>(args)...);
}

//! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library && lib, const std::string & alias_name, std::size_t size, Args...args)
{
    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(boost::move(lib), size, static_cast<Args>(args)...);
}



/*! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
 * \note This function does add the type alias to the \ref boost::dll::experimental::smart_library.
 */

template<typename T, typename ... Args> imported_class<T>
import_class(smart_library & lib, Args...args)
{
    return imported_class<T>::template make<Args...>(lib, static_cast<Args>(args)...);
}

/*! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
 * \note This function does add the type alias to the \ref boost::dll::experimental::smart_library.
 */
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library & lib, const std::string & alias_name, Args...args)
{
    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(lib, static_cast<Args>(args)...);
}

/*! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
 * \note This function does add the type alias to the \ref boost::dll::experimental::smart_library.
 */
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library & lib, std::size_t size, Args...args)
{
    return imported_class<T>::template make<Args...>(lib, size, static_cast<Args>(args)...);
}

/*! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
 * \note This function does add the type alias to the \ref boost::dll::experimental::smart_library.
 */
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library & lib, std::size_t size, const std::string & alias_name, Args...args)
{
    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(lib, size, static_cast<Args>(args)...);
}

/*! \overload boost::dll::import_class(const smart_library& lib, std::size_t, Args...)
 * \note This function does add the type alias to the \ref boost::dll::experimental::smart_library.
 */
template<typename T, typename ... Args> imported_class<T>
import_class(smart_library & lib, const std::string & alias_name, std::size_t size, Args...args)
{
    lib.add_type_alias<T>(alias_name);
    return imported_class<T>::template make<Args...>(lib, size, static_cast<Args>(args)...);
}

}
}
}



#endif /* BOOST_DLL_IMPORT_CLASS_HPP_ */

/* import_class.hpp
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
*/