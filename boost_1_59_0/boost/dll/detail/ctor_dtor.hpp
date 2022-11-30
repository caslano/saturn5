// Copyright 2016 Klemens Morgenstern, Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_DLL_DETAIL_CTOR_DTOR_HPP_
#define BOOST_DLL_DETAIL_CTOR_DTOR_HPP_

#include <boost/dll/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

#include <boost/dll/detail/aggressive_ptr_cast.hpp>
#include <boost/dll/detail/get_mem_fn_type.hpp>

#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows
#   include <boost/dll/detail/demangling/msvc.hpp>
#else
#   include <boost/dll/detail/demangling/itanium.hpp>
#endif


namespace boost { namespace dll { namespace detail {

/*!
 * This class stores a constructor.
 *
 * In some compilers there are several constructors in code, which may include an allocating one.
 * This can be used if the imported class shall be put on the heap, which is why the class provied both types.
 */
template<typename Signature>
struct constructor;

template<typename Class, typename ...Args>
struct constructor<Class(Args...)> {
    typedef typename detail::get_mem_fn_type<Class, void(Args...)>::mem_fn standard_t;
    typedef Class*(*allocating_t)(Args...);


    //! The standard, i.e. not allocating constructor. @warning May differ with the compiler. Use @ref constructor::call_standard instead.
    standard_t standard;
    //! The allocating constructor.  @warning May differ with the compiler. Use @ref constructor::call_allocating instead.
    allocating_t allocating;

    //! Call the standard constructor
    void call_standard  (Class * const ptr, Args...args){ (ptr->*standard)(static_cast<Args>(args)...); }

    //! Call the deleting destructor
    Class * call_allocating(Args...args){ return allocating(static_cast<Args>(args)...); }


    //! True if a allocating constructor could be loaded.
    bool has_allocating() const { return allocating != nullptr; }

    //! True if a standard constructor could be loaded.
    bool has_standard() const { return standard != nullptr; }

    //! False if neither the allocating nor the standard constructor is available.
    bool is_empty() const { return (allocating == nullptr) && (standard == nullptr) ; }

    constructor() = delete;
    constructor(const constructor &) = default;

    explicit constructor(standard_t standard, allocating_t allocating = nullptr)
        : standard(standard)
        , allocating(allocating)
    {}
};



template <typename Class>
struct destructor {
#if !defined(_WIN32)
    typedef void(*type)(Class* const);
#elif !defined(_WIN64)
    typedef void(__thiscall * type)(Class* const);
#else
    typedef void(__cdecl * type)(Class* const);
#endif

    typedef type standard_t;
    typedef type deleting_t;

    //! The standard, i.e. not deleting destructor. @warning May differ with the compiler. Use @ref destructor::call_standard instead.
    standard_t standard;
    //! The deleting destructor. @warning May differ with the compiler. Use @ref destructor::call_deallocating instead.
    deleting_t deleting;

    //! Call the standard constructor
    void call_standard(Class * const ptr){ standard(ptr); }

    //! Call the deleting destructor
    void call_deleting(Class * const ptr){ deleting(ptr); }

    //! True if a deleting destructor could be loaded.
    bool has_deleting() const { return deleting != nullptr; }

    //! True if a standard destructor could be loaded.
    bool has_standard() const { return standard != nullptr; }

    //! False if neither the deleting nor the standard destructor is available.
    bool is_empty() const { return (deleting == nullptr) && (standard == nullptr) ; }
    destructor() = delete;

    //! Copy destructor.
    destructor(const destructor &) = default;

    //! Construct it from both the standard destructor and the allocating destructor
    explicit destructor(const standard_t &standard, const deleting_t &deleting = nullptr)
        : standard(standard)
        , deleting(deleting)
    {}
};

#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows

template<typename Signature, typename Lib>
constructor<Signature> load_ctor(Lib & lib, const mangled_storage_impl::ctor_sym & ct) {
    typedef typename constructor<Signature>::standard_t standard_t;
    standard_t ctor = lib.template get<standard_t>(ct);
    return constructor<Signature>(ctor);
}

template<typename Class, typename Lib>
destructor<Class> load_dtor(Lib & lib, const mangled_storage_impl::dtor_sym & dt) {
    typedef typename destructor<Class>::standard_t standard_t;
    //@apolukhin That does NOT work this way with MSVC-14 x32 via memcpy. The x64 is different.
    //standard_t dtor = &lib.template get< typename boost::remove_pointer<standard_t>::type >(dt);
    void * buf = &lib.template get<unsigned char>(dt);
    standard_t dtor;
    std::memcpy(&dtor, &buf, sizeof(dtor));
    return destructor<Class>(dtor);
}

#else

template<typename Signature, typename Lib>
constructor<Signature> load_ctor(Lib & lib, const mangled_storage_impl::ctor_sym & ct) {
    typedef typename constructor<Signature>::standard_t   stand;
    typedef typename constructor<Signature>::allocating_t alloc;

    stand s = nullptr;
    alloc a = nullptr;

    //see here for the abi http://mentorembedded.github.io/cxx-abi/abi.html#mangling-special-ctor-dtor

    if (!ct.C1.empty())
    {
        //the only way this works on mingw/win.
        //For some reason there is always an 0xA in the following poniter, which screws with the this pointer.
        void *buf = &lib.template get<unsigned char>(ct.C1);
        std::memcpy(&s, &buf, sizeof(void*));
    }
    if (!ct.C3.empty())
    {
        void *buf = &lib.template get<unsigned char>(ct.C3);
        std::memcpy(&a, &buf, sizeof(void*));
    }

    return constructor<Signature>(s,a);
}

template<typename Class, typename Lib>
destructor<Class> load_dtor(Lib & lib, const mangled_storage_impl::dtor_sym & dt) {
    typedef typename destructor<Class>::standard_t stand;
    typedef typename destructor<Class>::deleting_t delet;

    stand s = nullptr;
    delet d = nullptr;

    //see here for the abi http://mentorembedded.github.io/cxx-abi/abi.html#mangling-special-ctor-dtor
    if (!dt.D1.empty()) {
        s = &lib.template get< typename boost::remove_pointer<stand>::type >(dt.D1);
    }

    if (!dt.D0.empty()) {
        d = &lib.template get< typename boost::remove_pointer<delet>::type >(dt.D0);
    }

    return destructor<Class>(s,d);

}

#endif

}}} // namespace boost::dll::detail

#endif /* BOOST_DLL_DETAIL_CTOR_DTOR_HPP_ */

/* ctor_dtor.hpp
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
*/