#ifndef BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_THREAD_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_THREAD_HPP_INCLUDED

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

#endif // #ifndef BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_THREAD_HPP_INCLUDED

/* lightweight_thread.hpp
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
*/