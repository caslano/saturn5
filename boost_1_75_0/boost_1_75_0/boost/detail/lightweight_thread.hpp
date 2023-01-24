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
x/tkvm+N93F8n4T3jbfRfQe8/4HvXXh/hO9T8f5Dvu+O93W3cYzOfDgPG64O+6WnbmiRvBQ9WJ0CZNc+SG3405Milnk/IDbHe7Wl5oo8DbvB0gPPejRz+1Iq2yeHZeFt1FX0H6QPwGeOFmneURQPNT7Rw/GNNHXk0I2cEr1iZ6CtHpxSAvVxRPKSdWNYEaVFXM/SDMyUIsgZVijS7ue0QkwrEGl3cloBpqVhWiuzF/iKqzHAOa5GN7brofxEPVSYrIeKUjAq6w2+4VmKa75zjHqfcUg3TjordsPPYIEJZQQ8JUB4RDeyPEV6KMvjNt9N0DRoqTZVuC2g/in4U3YqGe6Lk3Rjr/lKrAYv06rhq6oYyBl4qLgNpj4Yp2kNZtmpDkg3dysipw/8vLhjllGD2e9pBDJqGvKnD3yXIW0A3/B91X/haVu0WKR/VzfeLe6kbzOTpw/cV9weiVxI9C4mbf49AWneL46HzMDXm/9Qf36YUa0b4z15ujHLk4/vVACt4Z1UA/0SGu9JpNi08Sm8uTn1j0jkeI0jkLQFmwQf0WoWMsd4T7pu1FKQuIb63NimG61Fd7lFb2Ebp9VQmdC6AY8bCy6AIfmWGxgoYzu2X57PuakR+z3k92Rm7M/YGXEd+keqFtwTmQ4IPRtrOqpED/s96eYd8Rr0m+HHZzuyM3bq4dEeXQ+N9rizjB1IFsnLzDheUe2srMYGHQD4
*/