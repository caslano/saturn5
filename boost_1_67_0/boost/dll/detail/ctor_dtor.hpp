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