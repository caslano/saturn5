// Copyright 2015-2018 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_IMPORT_CLASS_HPP_
#define BOOST_DLL_IMPORT_CLASS_HPP_

#include <boost/dll/smart_library.hpp>
#include <boost/dll/import_mangled.hpp>
#include <memory>

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