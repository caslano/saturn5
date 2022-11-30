#ifndef BOOST_SMART_PTR_DETAIL_ATOMIC_COUNT_GCC_X86_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_ATOMIC_COUNT_GCC_X86_HPP_INCLUDED

//
//  boost/detail/atomic_count_gcc_x86.hpp
//
//  atomic_count for g++ on 486+/AMD64
//
//  Copyright 2007 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/smart_ptr/detail/sp_obsolete.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using g++/x86 atomic_count")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

class atomic_count
{
public:

    explicit atomic_count( long v ) : value_( static_cast< int >( v ) ) {}

    long operator++()
    {
        return atomic_exchange_and_add( &value_, +1 ) + 1;
    }

    long operator--()
    {
        return atomic_exchange_and_add( &value_, -1 ) - 1;
    }

    operator long() const
    {
        return atomic_exchange_and_add( &value_, 0 );
    }

private:

    atomic_count(atomic_count const &);
    atomic_count & operator=(atomic_count const &);

    mutable int value_;

private:

    static int atomic_exchange_and_add( int * pw, int dv )
    {
        // int r = *pw;
        // *pw += dv;
        // return r;

        int r;

        __asm__ __volatile__
        (
            "lock\n\t"
            "xadd %1, %0":
            "+m"( *pw ), "=r"( r ): // outputs (%0, %1)
            "1"( dv ): // inputs (%2 == %1)
            "memory", "cc" // clobbers
        );

        return r;
    }
};

} // namespace detail

} // namespace boost

#endif // #ifndef BOOST_SMART_PTR_DETAIL_ATOMIC_COUNT_GCC_X86_HPP_INCLUDED

/* atomic_count_gcc_x86.hpp
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
*/