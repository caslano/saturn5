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
Ly46dGmvOX+qVp6F5fcVzxBB3r0ACBKNLqiSIDcyu72qD5mwLNeITRegyOs8kmLTXoPN3Wz3sZ3A3YbgsozgXACuzIkXjIidNuNn/VZjJ9W82Krml9+ympc6ucWIrD4E1otF2H1p5cjx2EPQarLQ0NcIbQVAi3LqxBVWZGCXF2WDI9QKbruYr73SUDGJfY2gPp5lQawLAOqmaDp+ZIpoOU7+eKMMFLIXI8ayuSFDiR9Di8v3q/mMmVhJuTmsrMPOZ+h7DZAF+5Sy/1mHF3JfGOblwf5ghO+YaN4PkTUbC9fsZ30BEAk7HfbiY3H+phapMX5HID4QQznQTOAFRk1ohIXg5hafPVlyYYwM1p8KvewjsYQZg6e2PAAC84Rbi2VKPoW5a0+4415OZ0DBikjyUT+JX7saSFkhRh3KJzznyEIzMv9ABDtbVqsJq1phI0IBEBRdIn0Me2WK7Yly1pGtgscJXPa0fLFc4eCnYiwS7+OmeQWoWmBHrJC4ODG4aQlrUhQtPnZFwoIp8j2umkoEhMapEn5PhC/Cq+Nf/L1eMd+ThY/HKvZEXpn8U5wavgYbHuO/lP/AjYIkop4E1p+AP0UraGLkamgnP4R+eClonA7dvmbTYa2Dqyb3soL4EIF8wUsikpPIDaemOszze3c9q/nd1FhooD3kItCM8Pu1r8UisKSK4Qfxd6rqMRGvam+koLiwmmYAigCUkfRPNeDUNPCpl+ZRr8IrRbLdkHyRIAI/wVZG8BHBthBgEWaJ1o1j1bOB5RB2jQ0awr5+7Hgn6rgdO36NseMrNdbxaOiuglM6Z7R0XJVkCwcbCEbjxWrh5cIEA7DAAf5zP4fNIYHJm797rQAh8m+CAULgeQHftKD2oveXE/sIgfHrympzNEf5XPnXvS22mOKvGFmOsALcRj5G6mCL5IMiQ+uBbqq0kim0qb21DBLTSc2CxgxxbYS8JhUNHIMBhEG+FQZ2wOAGVkC290kUtYeWj0sxTdd2fAFSEYGvTBSTi2u9iuQIfhfLZ1eytLdEi+au5+LTSoXG0sMiaS6t5XNprZhwaqG//V5tUQi756PuLeplMeFas1M5Oj1C2CGargIKVxssxR+ynYferpYGQpcT4PReFnR7hV00B3rKfaaqx7Eablv4QX2MSElj9WNPIU/eJqTTqhqpdnwai15NRV+RRUezotBHGxQHxXMJfqWQSdn0AGvUzk9SbBVxKCBxY9ClrK9gil3J7+96CmsINOtRZbOeJJv5W4lUPNW9cqxaFhOsxK0QLs4qn0RYtgEsJTtsiYcOTKYsp8hCaMsx63rK+jZTGIXMjQcVJJD7IH/xqVc9tJnSaj1j/P/z/89/yico/g+cclAViW/7XB+p3tvNYStqLVcfCwW4hJ0sGrXcnFiCvjPZd4cqX6ylm8Cyq6ZF/lYwoeTvDvDbQj9/5MfqP18/fws1itKAshvDEiE63M7mRN1BnBAZqhYzGoaugZs3OkglYCGOrzew8qStzLWZWgEx5uR4ObBGE+Uy81sYb2xsyckR9MD7GUrFpQ5esWoE6NxC1ZUnj5HBop5lYZTxDXRwBeKlHKhc5mLbH5xQ2g4JzhFICsRJkFhx3YkzEq3u9D9B9z/VyF/KPU5X/M71oVyLl8P2MP4Fdqnbuorw0QuZliGQpmTNlFnXv14dRpcRH2WSlf4g8XEbiewyDvClhgF2mwbYZRyReIQHowHzMQ5/wfhKSy18KeD2k7XaLjoSZTV+R91IQMSqVTmMKcOZ3rV+jFH8E43IOI3Sd1erIhYSfyJHMzGwAX/uroP+y436r++rre6PLn0mnPsj4/hu+N4wvkB/lZAhR0D2qLco0tvRtrAl/+E=
*/