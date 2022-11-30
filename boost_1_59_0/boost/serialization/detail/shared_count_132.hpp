#ifndef BOOST_DETAIL_SHARED_COUNT_132_HPP_INCLUDED
#define BOOST_DETAIL_SHARED_COUNT_132_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER)
# pragma once
#endif

//
//  detail/shared_count.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>

#if defined(BOOST_SP_USE_STD_ALLOCATOR) && defined(BOOST_SP_USE_QUICK_ALLOCATOR)
# error BOOST_SP_USE_STD_ALLOCATOR and BOOST_SP_USE_QUICK_ALLOCATOR are incompatible.
#endif

#include <boost/checked_delete.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/detail/lightweight_mutex.hpp>

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)
#include <boost/detail/quick_allocator.hpp>
#endif

#include <memory>           // std::auto_ptr, std::allocator
#include <functional>       // std::less
#include <exception>        // std::exception
#include <new>              // std::bad_alloc
#include <typeinfo>         // std::type_info in get_deleter
#include <cstddef>          // std::size_t

#include <boost/config.hpp> // msvc 6.0 needs this for warning suppression
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

namespace boost_132 {

// Debug hooks

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

void sp_scalar_constructor_hook(void * px, std::size_t size, void * pn);
void sp_array_constructor_hook(void * px);
void sp_scalar_destructor_hook(void * px, std::size_t size, void * pn);
void sp_array_destructor_hook(void * px);

#endif


// The standard library that comes with Borland C++ 5.5.1
// defines std::exception and its members as having C calling
// convention (-pc). When the definition of bad_weak_ptr
// is compiled with -ps, the compiler issues an error.
// Hence, the temporary #pragma option -pc below. The version
// check is deliberately conservative.

class bad_weak_ptr: public std::exception
{
public:

    virtual char const * what() const throw()
    {
        return "boost::bad_weak_ptr";
    }
};

namespace detail{

class sp_counted_base
{
//private:

    typedef boost::detail::lightweight_mutex mutex_type;

public:

    sp_counted_base(): use_count_(1), weak_count_(1)
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destruct() is called when weak_count_ drops to zero.

    virtual void destruct() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter(std::type_info const & ti) = 0;

    void add_ref_copy()
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        ++use_count_;
    }

    void add_ref_lock()
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        if(use_count_ == 0) boost::serialization::throw_exception(bad_weak_ptr());
        ++use_count_;
    }

    void release() // nothrow
    {
        {
#if defined(BOOST_HAS_THREADS)
            mutex_type::scoped_lock lock(mtx_);
#endif
            long new_use_count = --use_count_;

            if(new_use_count != 0) return;
        }

        dispose();
        weak_release();
    }

    void weak_add_ref() // nothrow
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        ++weak_count_;
    }

    void weak_release() // nothrow
    {
        long new_weak_count;

        {
#if defined(BOOST_HAS_THREADS)
            mutex_type::scoped_lock lock(mtx_);
#endif
            new_weak_count = --weak_count_;
        }

        if(new_weak_count == 0)
        {
            destruct();
        }
    }

    long use_count() const // nothrow
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        return use_count_;
    }

//private:
public:
    sp_counted_base(sp_counted_base const &);
    sp_counted_base & operator= (sp_counted_base const &);

    long use_count_;        // #shared
    long weak_count_;       // #weak + (#shared != 0)

#if defined(BOOST_HAS_THREADS) || defined(BOOST_LWM_WIN32)
    mutable mutex_type mtx_;
#endif
};

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

template<class T> void cbi_call_constructor_hook(sp_counted_base * pn, T * px, boost::checked_deleter< T > const &)
{
    boost::sp_scalar_constructor_hook(px, sizeof(T), pn);
}

template<class T> void cbi_call_constructor_hook(sp_counted_base *, T * px, boost::checked_array_deleter< T > const &)
{
    boost::sp_array_constructor_hook(px);
}

template<class P, class D> void cbi_call_constructor_hook(sp_counted_base *, P const &, D const &, long)
{
}

template<class T> void cbi_call_destructor_hook(sp_counted_base * pn, T * px, boost::checked_deleter< T > const &)
{
    boost::sp_scalar_destructor_hook(px, sizeof(T), pn);
}

template<class T> void cbi_call_destructor_hook(sp_counted_base *, T * px, boost::checked_array_deleter< T > const &)
{
    boost::sp_array_destructor_hook(px);
}

template<class P, class D> void cbi_call_destructor_hook(sp_counted_base *, P const &, D const &, long)
{
}

#endif

//
// Borland's Codeguard trips up over the -Vx- option here:
//
#ifdef __CODEGUARD__
# pragma option push -Vx-
#endif

template<class P, class D> class sp_counted_base_impl: public sp_counted_base
{
//private:
public:
    P ptr; // copy constructor must not throw
    D del; // copy constructor must not throw

    sp_counted_base_impl(sp_counted_base_impl const &);
    sp_counted_base_impl & operator= (sp_counted_base_impl const &);

    typedef sp_counted_base_impl<P, D> this_type;

public:

    // pre: initial_use_count <= initial_weak_count, d(p) must not throw

    sp_counted_base_impl(P p, D d): ptr(p), del(d)
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        detail::cbi_call_constructor_hook(this, p, d, 0);
#endif
    }

    virtual void dispose() // nothrow
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        detail::cbi_call_destructor_hook(this, ptr, del, 0);
#endif
        del(ptr);
    }

    virtual void * get_deleter(std::type_info const & ti)
    {
        return ti == typeid(D)? &del: 0;
    }

#if defined(BOOST_SP_USE_STD_ALLOCATOR)

    void * operator new(std::size_t)
    {
        return std::allocator<this_type>().allocate(1, static_cast<this_type *>(0));
    }

    void operator delete(void * p)
    {
        std::allocator<this_type>().deallocate(static_cast<this_type *>(p), 1);
    }

#endif

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)

    void * operator new(std::size_t)
    {
        return boost::detail::quick_allocator<this_type>::alloc();
    }

    void operator delete(void * p)
    {
        boost::detail::quick_allocator<this_type>::dealloc(p);
    }

#endif
};

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

int const shared_count_id = 0x2C35F101;
int const   weak_count_id = 0x298C38A4;

#endif

class weak_count;

class shared_count
{
//private:
public:
    sp_counted_base * pi_;

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
    int id_;
#endif

    friend class weak_count;

public:

    shared_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
    }

    template<class P, class D> shared_count(P p, D d): pi_(0)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_base_impl<P, D>(p, d);
        }
        catch(...)
        {
            d(p); // delete p
            throw;
        }

#else

        pi_ = new sp_counted_base_impl<P, D>(p, d);

        if(pi_ == 0)
        {
            d(p); // delete p
            boost::serialization::throw_exception(std::bad_alloc());
        }

#endif
    }

#ifndef BOOST_NO_AUTO_PTR

    // auto_ptr<Y> is special cased to provide the strong guarantee

    template<class Y>
    explicit shared_count(std::auto_ptr<Y> & r): pi_(
        new sp_counted_base_impl<
            Y *,
            boost::checked_deleter<Y>
        >(r.get(), boost::checked_deleter<Y>()))
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        r.release();
    }

#endif

    ~shared_count() // nothrow
    {
        if(pi_ != 0) pi_->release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }

    shared_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->add_ref_copy();
    }

    explicit shared_count(weak_count const & r); // throws bad_weak_ptr when r.use_count() == 0

    shared_count & operator= (shared_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;

        if(tmp != pi_)
        {
            if(tmp != 0) tmp->add_ref_copy();
            if(pi_ != 0) pi_->release();
            pi_ = tmp;
        }

        return *this;
    }

    void swap(shared_count & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    long use_count() const // nothrow
    {
        return pi_ != 0? pi_->use_count(): 0;
    }

    bool unique() const // nothrow
    {
        return use_count() == 1;
    }

    friend inline bool operator==(shared_count const & a, shared_count const & b)
    {
        return a.pi_ == b.pi_;
    }

    friend inline bool operator<(shared_count const & a, shared_count const & b)
    {
        return std::less<sp_counted_base *>()(a.pi_, b.pi_);
    }

    void * get_deleter(std::type_info const & ti) const
    {
        return pi_? pi_->get_deleter(ti): 0;
    }
};

#ifdef __CODEGUARD__
# pragma option pop
#endif


class weak_count
{
private:

    sp_counted_base * pi_;

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
    int id_;
#endif

    friend class shared_count;

public:

    weak_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
    }

    weak_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }

    weak_count(weak_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }

    ~weak_count() // nothrow
    {
        if(pi_ != 0) pi_->weak_release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }

    weak_count & operator= (shared_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        if(tmp != 0) tmp->weak_add_ref();
        if(pi_ != 0) pi_->weak_release();
        pi_ = tmp;

        return *this;
    }

    weak_count & operator= (weak_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        if(tmp != 0) tmp->weak_add_ref();
        if(pi_ != 0) pi_->weak_release();
        pi_ = tmp;

        return *this;
    }

    void swap(weak_count & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    long use_count() const // nothrow
    {
        return pi_ != 0? pi_->use_count(): 0;
    }

    friend inline bool operator==(weak_count const & a, weak_count const & b)
    {
        return a.pi_ == b.pi_;
    }

    friend inline bool operator<(weak_count const & a, weak_count const & b)
    {
        return std::less<sp_counted_base *>()(a.pi_, b.pi_);
    }
};

inline shared_count::shared_count(weak_count const & r): pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
{
    if(pi_ != 0)
    {
        pi_->add_ref_lock();
    }
    else
    {
        boost::serialization::throw_exception(bad_weak_ptr());
    }
}

} // namespace detail

} // namespace boost

BOOST_SERIALIZATION_ASSUME_ABSTRACT(boost_132::detail::sp_counted_base)

#endif  // #ifndef BOOST_DETAIL_SHARED_COUNT_HPP_INCLUDED

/* shared_count_132.hpp
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
*/