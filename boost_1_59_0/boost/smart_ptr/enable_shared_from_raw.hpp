#ifndef BOOST_ENABLE_SHARED_FROM_RAW_HPP_INCLUDED
#define BOOST_ENABLE_SHARED_FROM_RAW_HPP_INCLUDED

//
//  enable_shared_from_raw.hpp
//
//  Copyright 2002, 2009, 2014 Peter Dimov
//  Copyright 2008-2009 Frank Mori Hess
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/assert.hpp>
#include <boost/config/workaround.hpp>

namespace boost
{
template<typename T> boost::shared_ptr<T> shared_from_raw(T *);
template<typename T> boost::weak_ptr<T> weak_from_raw(T *);

namespace detail
{
template< class X, class Y > inline void sp_enable_shared_from_this( boost::shared_ptr<X> * ppx, Y const * py, boost::enable_shared_from_raw const * pe );

} // namespace detail

class enable_shared_from_raw
{
protected:

    enable_shared_from_raw()
    {
    }

    enable_shared_from_raw( enable_shared_from_raw const & )
    {
    }

    enable_shared_from_raw & operator=( enable_shared_from_raw const & )
    {
        return *this;
    }

    ~enable_shared_from_raw()
    {
        BOOST_ASSERT( shared_this_.use_count() <= 1 ); // make sure no dangling shared_ptr objects exist
    }

private:

    void init_if_expired() const
    {
        if( weak_this_.expired() )
        {
            shared_this_.reset( static_cast<void*>(0), detail::esft2_deleter_wrapper() );
            weak_this_ = shared_this_;
        }
    }

    void init_if_empty() const
    {
        if( weak_this_._empty() )
        {
            shared_this_.reset( static_cast<void*>(0), detail::esft2_deleter_wrapper() );
            weak_this_ = shared_this_;
        }
    }

#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
private:
    template<class Y> friend class shared_ptr;
    template<typename T> friend boost::shared_ptr<T> shared_from_raw(T *);
    template<typename T> friend boost::weak_ptr<T> weak_from_raw(T *);
    template< class X, class Y > friend inline void detail::sp_enable_shared_from_this( boost::shared_ptr<X> * ppx, Y const * py, boost::enable_shared_from_raw const * pe );
#endif

    shared_ptr<void const volatile> shared_from_this() const
    {
        init_if_expired();
        return shared_ptr<void const volatile>( weak_this_ );
    }

    shared_ptr<void const volatile> shared_from_this() const volatile
    {
        return const_cast< enable_shared_from_raw const * >( this )->shared_from_this();
    }

    weak_ptr<void const volatile> weak_from_this() const
    {
        init_if_empty();
        return weak_this_;
    }

    weak_ptr<void const volatile> weak_from_this() const volatile
    {
        return const_cast< enable_shared_from_raw const * >( this )->weak_from_this();
    }

    // Note: invoked automatically by shared_ptr; do not call
    template<class X, class Y> void _internal_accept_owner( shared_ptr<X> * ppx, Y * ) const
    {
        BOOST_ASSERT( ppx != 0 );

        if( weak_this_.expired() )
        {
            weak_this_ = *ppx;
        }
        else if( shared_this_.use_count() != 0 )
        {
            BOOST_ASSERT( ppx->unique() ); // no weak_ptrs should exist either, but there's no way to check that

            detail::esft2_deleter_wrapper * pd = boost::get_deleter<detail::esft2_deleter_wrapper>( shared_this_ );
            BOOST_ASSERT( pd != 0 );

            pd->set_deleter( *ppx );

            ppx->reset( shared_this_, ppx->get() );
            shared_this_.reset();
        }
    }

    mutable weak_ptr<void const volatile> weak_this_;

private:

    mutable shared_ptr<void const volatile> shared_this_;
};

template<typename T>
boost::shared_ptr<T> shared_from_raw(T *p)
{
    BOOST_ASSERT(p != 0);
    return boost::shared_ptr<T>(p->enable_shared_from_raw::shared_from_this(), p);
}

template<typename T>
boost::weak_ptr<T> weak_from_raw(T *p)
{
    BOOST_ASSERT(p != 0);
    boost::weak_ptr<T> result(p->enable_shared_from_raw::weak_from_this(), p);
    return result;
}

namespace detail
{
    template< class X, class Y > inline void sp_enable_shared_from_this( boost::shared_ptr<X> * ppx, Y const * py, boost::enable_shared_from_raw const * pe )
    {
        if( pe != 0 )
        {
            pe->_internal_accept_owner( ppx, const_cast< Y* >( py ) );
        }
    }
} // namepsace detail

} // namespace boost

#endif  // #ifndef BOOST_ENABLE_SHARED_FROM_RAW_HPP_INCLUDED

/* enable_shared_from_raw.hpp
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
*/