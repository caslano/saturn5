#ifndef BOOST_DETAIL_LIGHTWEIGHT_THREAD_HPP_INCLUDED
#define BOOST_DETAIL_LIGHTWEIGHT_THREAD_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  boost/detail/lightweight_thread.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2008, 2018 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//
//  typedef /*...*/ lw_thread_t; // as pthread_t
//  template<class F> int lw_thread_create( lw_thread_t & th, F f );
//  void lw_thread_join( lw_thread_t th );


#include <boost/config.hpp>
#include <memory>
#include <cerrno>

#if defined( BOOST_HAS_PTHREADS )

#include <pthread.h>

namespace boost
{
namespace detail
{

typedef ::pthread_t lw_thread_t;

inline int lw_thread_create_( lw_thread_t* thread, const pthread_attr_t* attr, void* (*start_routine)( void* ), void* arg )
{
    return ::pthread_create( thread, attr, start_routine, arg );
}

inline void lw_thread_join( lw_thread_t th )
{
    ::pthread_join( th, 0 );
}

} // namespace detail
} // namespace boost

#else // defined( BOOST_HAS_PTHREADS )

#include <windows.h>
#include <process.h>

namespace boost
{
namespace detail
{

typedef HANDLE lw_thread_t;

inline int lw_thread_create_( lw_thread_t * thread, void const *, unsigned (__stdcall * start_routine) (void*), void* arg )
{
    HANDLE h = (HANDLE)_beginthreadex( 0, 0, start_routine, arg, 0, 0 );

    if( h != 0 )
    {
        *thread = h;
        return 0;
    }
    else
    {
        return EAGAIN;
    }
}

inline void lw_thread_join( lw_thread_t thread )
{
    ::WaitForSingleObject( thread, INFINITE );
    ::CloseHandle( thread );
}

} // namespace detail
} // namespace boost

#endif // defined( BOOST_HAS_PTHREADS )


namespace boost
{
namespace detail
{

class lw_abstract_thread
{
public:

    virtual ~lw_abstract_thread() {}
    virtual void run() = 0;
};

#if defined( BOOST_HAS_PTHREADS )

extern "C" void * lw_thread_routine( void * pv )
{
#if defined(BOOST_NO_CXX11_SMART_PTR)

    std::auto_ptr<lw_abstract_thread> pt( static_cast<lw_abstract_thread *>( pv ) );

#else

    std::unique_ptr<lw_abstract_thread> pt( static_cast<lw_abstract_thread *>( pv ) );

#endif

    pt->run();

    return 0;
}

#else

unsigned __stdcall lw_thread_routine( void * pv )
{
#if defined(BOOST_NO_CXX11_SMART_PTR)

    std::auto_ptr<lw_abstract_thread> pt( static_cast<lw_abstract_thread *>( pv ) );

#else

    std::unique_ptr<lw_abstract_thread> pt( static_cast<lw_abstract_thread *>( pv ) );

#endif

    pt->run();

    return 0;
}

#endif

template<class F> class lw_thread_impl: public lw_abstract_thread
{
public:

    explicit lw_thread_impl( F f ): f_( f )
    {
    }

    void run()
    {
        f_();
    }

private:

    F f_;
};

template<class F> int lw_thread_create( lw_thread_t & th, F f )
{
#if defined(BOOST_NO_CXX11_SMART_PTR)

    std::auto_ptr<lw_abstract_thread> p( new lw_thread_impl<F>( f ) );

#else

    std::unique_ptr<lw_abstract_thread> p( new lw_thread_impl<F>( f ) );

#endif

    int r = lw_thread_create_( &th, 0, lw_thread_routine, p.get() );

    if( r == 0 )
    {
        p.release();
    }

    return r;
}

} // namespace detail
} // namespace boost

#endif // #ifndef BOOST_DETAIL_LIGHTWEIGHT_THREAD_HPP_INCLUDED

/* lightweight_thread.hpp
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
*/