#ifndef BOOST_SMART_PTR_MAKE_LOCAL_SHARED_OBJECT_HPP_INCLUDED
#define BOOST_SMART_PTR_MAKE_LOCAL_SHARED_OBJECT_HPP_INCLUDED

//  make_local_shared_object.hpp
//
//  Copyright 2017 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.

#include <boost/smart_ptr/local_shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/config.hpp>
#include <utility>
#include <cstddef>

namespace boost
{

namespace detail
{

// lsp_if_not_array

template<class T> struct lsp_if_not_array
{
    typedef boost::local_shared_ptr<T> type;
};

template<class T> struct lsp_if_not_array<T[]>
{
};

template<class T, std::size_t N> struct lsp_if_not_array<T[N]>
{
};

// lsp_ms_deleter

template<class T, class A> class lsp_ms_deleter: public local_counted_impl_em
{
private:

    typedef typename sp_aligned_storage<sizeof(T), ::boost::alignment_of<T>::value>::type storage_type;

    storage_type storage_;
    A a_;
    bool initialized_;

private:

    void destroy() BOOST_SP_NOEXCEPT
    {
        if( initialized_ )
        {
            T * p = reinterpret_cast< T* >( storage_.data_ );

#if !defined( BOOST_NO_CXX11_ALLOCATOR )

            std::allocator_traits<A>::destroy( a_, p );

#else

            p->~T();

#endif

            initialized_ = false;
        }
    }

public:

    explicit lsp_ms_deleter( A const & a ) BOOST_SP_NOEXCEPT : a_( a ), initialized_( false )
    {
    }

    // optimization: do not copy storage_
    lsp_ms_deleter( lsp_ms_deleter const & r ) BOOST_SP_NOEXCEPT : a_( r.a_), initialized_( false )
    {
    }

    ~lsp_ms_deleter() BOOST_SP_NOEXCEPT
    {
        destroy();
    }

    void operator()( T * ) BOOST_SP_NOEXCEPT
    {
        destroy();
    }

    static void operator_fn( T* ) BOOST_SP_NOEXCEPT // operator() can't be static
    {
    }

    void * address() BOOST_SP_NOEXCEPT
    {
        return storage_.data_;
    }

    void set_initialized() BOOST_SP_NOEXCEPT
    {
        initialized_ = true;
    }
};

} // namespace detail

template<class T, class A, class... Args> typename boost::detail::lsp_if_not_array<T>::type allocate_local_shared( A const & a, Args&&... args )
{
#if !defined( BOOST_NO_CXX11_ALLOCATOR )

    typedef typename std::allocator_traits<A>::template rebind_alloc<T> A2;

#else

    typedef typename A::template rebind<T>::other A2;

#endif

    A2 a2( a );

    typedef boost::detail::lsp_ms_deleter<T, A2> D;

    boost::shared_ptr<T> pt( static_cast< T* >( 0 ), boost::detail::sp_inplace_tag<D>(), a2 );

    D * pd = static_cast< D* >( pt._internal_get_untyped_deleter() );
    void * pv = pd->address();

#if !defined( BOOST_NO_CXX11_ALLOCATOR )

    std::allocator_traits<A2>::construct( a2, static_cast< T* >( pv ), std::forward<Args>( args )... );

#else

    ::new( pv ) T( std::forward<Args>( args )... );

#endif

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );
    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );

    pd->pn_ = pt._internal_count();

    return boost::local_shared_ptr<T>( boost::detail::lsp_internal_constructor_tag(), pt2, pd );
}

template<class T, class A> typename boost::detail::lsp_if_not_array<T>::type allocate_local_shared_noinit( A const & a )
{
#if !defined( BOOST_NO_CXX11_ALLOCATOR )

    typedef typename std::allocator_traits<A>::template rebind_alloc<T> A2;

#else

    typedef typename A::template rebind<T>::other A2;

#endif

    A2 a2( a );

    typedef boost::detail::lsp_ms_deleter< T, std::allocator<T> > D;

    boost::shared_ptr<T> pt( static_cast< T* >( 0 ), boost::detail::sp_inplace_tag<D>(), a2 );

    D * pd = static_cast< D* >( pt._internal_get_untyped_deleter() );
    void * pv = pd->address();

    ::new( pv ) T;

    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );
    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );

    pd->pn_ = pt._internal_count();

    return boost::local_shared_ptr<T>( boost::detail::lsp_internal_constructor_tag(), pt2, pd );
}

template<class T, class... Args> typename boost::detail::lsp_if_not_array<T>::type make_local_shared( Args&&... args )
{
    typedef typename boost::remove_const<T>::type T2;
    return boost::allocate_local_shared<T2>( std::allocator<T2>(), std::forward<Args>(args)... );
}

template<class T> typename boost::detail::lsp_if_not_array<T>::type make_local_shared_noinit()
{
    typedef typename boost::remove_const<T>::type T2;
    return boost::allocate_shared_noinit<T2>( std::allocator<T2>() );
}

} // namespace boost

#endif // #ifndef BOOST_SMART_PTR_MAKE_SHARED_OBJECT_HPP_INCLUDED

/* make_local_shared_object.hpp
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
*/