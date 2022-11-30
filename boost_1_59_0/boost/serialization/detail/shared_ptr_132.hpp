#ifndef BOOST_SHARED_PTR_132_HPP_INCLUDED
#define BOOST_SHARED_PTR_132_HPP_INCLUDED

//
//  shared_ptr.hpp
//
//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002, 2003 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/shared_ptr.htm for documentation.
//

#include <boost/config.hpp>   // for broken compiler workarounds

#if defined(BOOST_NO_MEMBER_TEMPLATES) && !defined(BOOST_MSVC6_MEMBER_TEMPLATES)
#include <boost/serialization/detail/shared_ptr_nmt_132.hpp>
#else

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/detail/shared_count_132.hpp>

#include <memory>               // for std::auto_ptr
#include <algorithm>            // for std::swap
#include <functional>           // for std::less
#include <typeinfo>             // for std::bad_cast
#include <iosfwd>               // for std::basic_ostream

#ifdef BOOST_MSVC  // moved here to work around VC++ compiler crash
# pragma warning(push)
# pragma warning(disable:4284) // odd return type for operator->
#endif

namespace boost_132 {

template<class T> class weak_ptr;
template<class T> class enable_shared_from_this;

namespace detail
{

struct static_cast_tag {};
struct const_cast_tag {};
struct dynamic_cast_tag {};
struct polymorphic_cast_tag {};

template<class T> struct shared_ptr_traits
{
    typedef T & reference;
};

template<> struct shared_ptr_traits<void>
{
    typedef void reference;
};

#if !defined(BOOST_NO_CV_VOID_SPECIALIZATIONS)

template<> struct shared_ptr_traits<void const>
{
    typedef void reference;
};

template<> struct shared_ptr_traits<void volatile>
{
    typedef void reference;
};

template<> struct shared_ptr_traits<void const volatile>
{
    typedef void reference;
};

#endif

// enable_shared_from_this support

template<class T, class Y> void sp_enable_shared_from_this( shared_count const & pn, enable_shared_from_this< T > const * pe, Y const * px )
{
    if(pe != 0) pe->_internal_weak_this._internal_assign(const_cast<Y*>(px), pn);
}

inline void sp_enable_shared_from_this( shared_count const & /*pn*/, ... )
{
}

} // namespace detail


//
//  shared_ptr
//
//  An enhanced relative of scoped_ptr with reference counted copy semantics.
//  The object pointed to is deleted when the last shared_ptr pointing to it
//  is destroyed or reset.
//

template<class T> class shared_ptr
{
private:
    // Borland 5.5.1 specific workaround
    typedef shared_ptr< T > this_type;

public:

    typedef T element_type;
    typedef T value_type;
    typedef T * pointer;
    typedef typename detail::shared_ptr_traits< T >::reference reference;

    shared_ptr(): px(0), pn() // never throws in 1.30+
    {
    }

    template<class Y>
    explicit shared_ptr(Y * p): px(p), pn(p, boost::checked_deleter<Y>()) // Y must be complete
    {
        detail::sp_enable_shared_from_this( pn, p, p );
    }

    //
    // Requirements: D's copy constructor must not throw
    //
    // shared_ptr will release p by calling d(p)
    //

    template<class Y, class D> shared_ptr(Y * p, D d): px(p), pn(p, d)
    {
        detail::sp_enable_shared_from_this( pn, p, p );
    }

//  generated copy constructor, assignment, destructor are fine...

//  except that Borland C++ has a bug, and g++ with -Wsynth warns
#if defined(__GNUC__)
    shared_ptr & operator=(shared_ptr const & r) // never throws
    {
        px = r.px;
        pn = r.pn; // shared_count::op= doesn't throw
        return *this;
    }
#endif

    template<class Y>
    explicit shared_ptr(weak_ptr<Y> const & r): pn(r.pn) // may throw
    {
        // it is now safe to copy r.px, as pn(r.pn) did not throw
        px = r.px;
    }

    template<class Y>
    shared_ptr(shared_ptr<Y> const & r): px(r.px), pn(r.pn) // never throws
    {
    }

    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::static_cast_tag): px(static_cast<element_type *>(r.px)), pn(r.pn)
    {
    }

    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::const_cast_tag): px(const_cast<element_type *>(r.px)), pn(r.pn)
    {
    }

    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::dynamic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
    {
        if(px == 0) // need to allocate new counter -- the cast failed
        {
            pn = detail::shared_count();
        }
    }

    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::polymorphic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
    {
        if(px == 0)
        {
            boost::serialization::throw_exception(std::bad_cast());
        }
    }

#ifndef BOOST_NO_AUTO_PTR

    template<class Y>
    explicit shared_ptr(std::auto_ptr<Y> & r): px(r.get()), pn()
    {
        Y * tmp = r.get();
        pn = detail::shared_count(r);
        detail::sp_enable_shared_from_this( pn, tmp, tmp );
    }

#endif

#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)

    template<class Y>
    shared_ptr & operator=(shared_ptr<Y> const & r) // never throws
    {
        px = r.px;
        pn = r.pn; // shared_count::op= doesn't throw
        return *this;
    }

#endif

#ifndef BOOST_NO_AUTO_PTR

    template<class Y>
    shared_ptr & operator=(std::auto_ptr<Y> & r)
    {
        this_type(r).swap(*this);
        return *this;
    }

#endif

    void reset() // never throws in 1.30+
    {
        this_type().swap(*this);
    }

    template<class Y> void reset(Y * p) // Y must be complete
    {
        BOOST_ASSERT(p == 0 || p != px); // catch self-reset errors
        this_type(p).swap(*this);
    }

    template<class Y, class D> void reset(Y * p, D d)
    {
        this_type(p, d).swap(*this);
    }

    reference operator* () const // never throws
    {
        BOOST_ASSERT(px != 0);
        return *px;
    }

    T * operator-> () const // never throws
    {
        BOOST_ASSERT(px != 0);
        return px;
    }

    T * get() const // never throws
    {
        return px;
    }

    // implicit conversion to "bool"

#if defined(__SUNPRO_CC) && BOOST_WORKAROUND(__SUNPRO_CC, <= 0x530)

    operator bool () const
    {
        return px != 0;
    }

#elif defined(__MWERKS__) && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
    typedef T * (this_type::*unspecified_bool_type)() const;

    operator unspecified_bool_type() const // never throws
    {
        return px == 0? 0: &this_type::get;
    }

#else

    typedef T * this_type::*unspecified_bool_type;

    operator unspecified_bool_type() const // never throws
    {
        return px == 0? 0: &this_type::px;
    }

#endif

    // operator! is redundant, but some compilers need it

    bool operator! () const // never throws
    {
        return px == 0;
    }

    bool unique() const // never throws
    {
        return pn.unique();
    }

    long use_count() const // never throws
    {
        return pn.use_count();
    }

    void swap(shared_ptr< T > & other) // never throws
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }

    template<class Y> bool _internal_less(shared_ptr<Y> const & rhs) const
    {
        return pn < rhs.pn;
    }

    void * _internal_get_deleter(std::type_info const & ti) const
    {
        return pn.get_deleter(ti);
    }

// Tasteless as this may seem, making all members public allows member templates
// to work in the absence of member template friends. (Matthew Langston)

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

private:

    template<class Y> friend class shared_ptr;
    template<class Y> friend class weak_ptr;


#endif
public: // for serialization
    T * px;                     // contained pointer
    detail::shared_count pn;    // reference counter

};  // shared_ptr

template<class T, class U> inline bool operator==(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() != b.get();
}

template<class T, class U> inline bool operator<(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a._internal_less(b);
}

template<class T> inline void swap(shared_ptr< T > & a, shared_ptr< T > & b)
{
    a.swap(b);
}

template<class T, class U> shared_ptr< T > static_pointer_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::static_cast_tag());
}

template<class T, class U> shared_ptr< T > const_pointer_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::const_cast_tag());
}

template<class T, class U> shared_ptr< T > dynamic_pointer_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::dynamic_cast_tag());
}

// shared_*_cast names are deprecated. Use *_pointer_cast instead.

template<class T, class U> shared_ptr< T > shared_static_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::static_cast_tag());
}

template<class T, class U> shared_ptr< T > shared_dynamic_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::dynamic_cast_tag());
}

template<class T, class U> shared_ptr< T > shared_polymorphic_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::polymorphic_cast_tag());
}

template<class T, class U> shared_ptr< T > shared_polymorphic_downcast(shared_ptr<U> const & r)
{
    BOOST_ASSERT(dynamic_cast<T *>(r.get()) == r.get());
    return shared_static_cast< T >(r);
}

// get_pointer() enables boost::mem_fn to recognize shared_ptr

template<class T> inline T * get_pointer(shared_ptr< T > const & p)
{
    return p.get();
}

// operator<<


template<class E, class T, class Y> std::basic_ostream<E, T> & operator<< (std::basic_ostream<E, T> & os, shared_ptr<Y> const & p)
{
    os << p.get();
    return os;
}

// get_deleter (experimental)

#if defined(__EDG_VERSION__) && (__EDG_VERSION__ <= 238)

// g++ 2.9x doesn't allow static_cast<X const *>(void *)
// apparently EDG 2.38 also doesn't accept it

template<class D, class T> D * get_deleter(shared_ptr< T > const & p)
{
    void const * q = p._internal_get_deleter(typeid(D));
    return const_cast<D *>(static_cast<D const *>(q));
}

#else

template<class D, class T> D * get_deleter(shared_ptr< T > const & p)
{
    return static_cast<D *>(p._internal_get_deleter(typeid(D)));
}

#endif

} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif  // #if defined(BOOST_NO_MEMBER_TEMPLATES) && !defined(BOOST_MSVC6_MEMBER_TEMPLATES)

#endif  // #ifndef BOOST_SHARED_PTR_132_HPP_INCLUDED

/* shared_ptr_132.hpp
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
*/