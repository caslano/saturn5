#ifndef BOOST_SMART_PTR_SCOPED_PTR_HPP_INCLUDED
#define BOOST_SMART_PTR_SCOPED_PTR_HPP_INCLUDED

//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/smart_ptr/detail/sp_nullptr_t.hpp>
#include <boost/smart_ptr/detail/sp_disable_deprecated.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <boost/config/workaround.hpp>

#ifndef BOOST_NO_AUTO_PTR
# include <memory>          // for std::auto_ptr
#endif

#if defined( BOOST_SP_DISABLE_DEPRECATED )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

// Debug hooks

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

void sp_scalar_constructor_hook(void * p);
void sp_scalar_destructor_hook(void * p);

#endif

//  scoped_ptr mimics a built-in pointer except that it guarantees deletion
//  of the object pointed to, either on destruction of the scoped_ptr or via
//  an explicit reset(). scoped_ptr is a simple solution for simple needs;
//  use shared_ptr or std::auto_ptr if your needs are more complex.

template<class T> class scoped_ptr // noncopyable
{
private:

    T * px;

    scoped_ptr(scoped_ptr const &);
    scoped_ptr & operator=(scoped_ptr const &);

    typedef scoped_ptr<T> this_type;

    void operator==( scoped_ptr const& ) const;
    void operator!=( scoped_ptr const& ) const;

public:

    typedef T element_type;

    explicit scoped_ptr( T * p = 0 ) BOOST_SP_NOEXCEPT : px( p )
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_constructor_hook( px );
#endif
    }

#ifndef BOOST_NO_AUTO_PTR

    explicit scoped_ptr( std::auto_ptr<T> p ) BOOST_SP_NOEXCEPT : px( p.release() )
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_constructor_hook( px );
#endif
    }

#endif

    ~scoped_ptr() BOOST_SP_NOEXCEPT
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_destructor_hook( px );
#endif
        boost::checked_delete( px );
    }

    void reset(T * p = 0) BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( p == 0 || p != px ); // catch self-reset errors
        this_type(p).swap(*this);
    }

    T & operator*() const BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( px != 0 );
        return *px;
    }

    T * operator->() const BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( px != 0 );
        return px;
    }

    T * get() const BOOST_SP_NOEXCEPT
    {
        return px;
    }

// implicit conversion to "bool"
#include <boost/smart_ptr/detail/operator_bool.hpp>

    void swap(scoped_ptr & b) BOOST_SP_NOEXCEPT
    {
        T * tmp = b.px;
        b.px = px;
        px = tmp;
    }
};

#if !defined( BOOST_NO_CXX11_NULLPTR )

template<class T> inline bool operator==( scoped_ptr<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator==( boost::detail::sp_nullptr_t, scoped_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator!=( scoped_ptr<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

template<class T> inline bool operator!=( boost::detail::sp_nullptr_t, scoped_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

#endif

template<class T> inline void swap(scoped_ptr<T> & a, scoped_ptr<T> & b) BOOST_SP_NOEXCEPT
{
    a.swap(b);
}

// get_pointer(p) is a generic way to say p.get()

template<class T> inline T * get_pointer(scoped_ptr<T> const & p) BOOST_SP_NOEXCEPT
{
    return p.get();
}

} // namespace boost

#if defined( BOOST_SP_DISABLE_DEPRECATED )
#pragma GCC diagnostic pop
#endif

#endif // #ifndef BOOST_SMART_PTR_SCOPED_PTR_HPP_INCLUDED

/* scoped_ptr.hpp
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
*/