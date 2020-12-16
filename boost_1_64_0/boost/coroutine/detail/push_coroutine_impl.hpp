
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_IMPL_H
#define BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_IMPL_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/parameters.hpp>
#include <boost/coroutine/detail/trampoline_push.hpp>
#include <boost/coroutine/exceptions.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct stack_context;

namespace detail {

template< typename Arg >
class push_coroutine_impl : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;

public:
    typedef parameters< Arg >                           param_type;

    push_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~push_coroutine_impl() {}

    bool force_unwind() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_force_unwind); }

    bool unwind_requested() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_unwind_stack); }

    bool is_started() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_started); }

    bool is_running() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_running); }

    bool is_complete() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_complete); }

    void unwind_stack() BOOST_NOEXCEPT
    {
        if ( is_started() && ! is_complete() && force_unwind() )
        {
            flags_ |= flag_unwind_stack;
            param_type to( unwind_t::force_unwind);
            caller_->jump(
                * callee_,
                & to);
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    void push( Arg const& arg)
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( const_cast< Arg * >( & arg), this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    void push( BOOST_RV_REF( Arg) arg)
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( const_cast< Arg * >( & arg), this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    virtual void destroy() = 0;
};

template< typename Arg >
class push_coroutine_impl< Arg & > : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;

public:
    typedef parameters< Arg & >                         param_type;

    push_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~push_coroutine_impl() {}

    bool force_unwind() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_force_unwind); }

    bool unwind_requested() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_unwind_stack); }

    bool is_started() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_started); }

    bool is_running() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_running); }

    bool is_complete() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_complete); }

    void unwind_stack() BOOST_NOEXCEPT
    {
        if ( is_started() && ! is_complete() && force_unwind() )
        {
            flags_ |= flag_unwind_stack;
            param_type to( unwind_t::force_unwind);
            caller_->jump(
                * callee_,
                & to);
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    void push( Arg & arg)
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( & arg, this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    virtual void destroy() = 0;
};

template<>
class push_coroutine_impl< void > : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;

public:
    typedef parameters< void >                          param_type;

    push_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~push_coroutine_impl() {}

    inline bool force_unwind() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_force_unwind); }

    inline bool unwind_requested() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_unwind_stack); }

    inline bool is_started() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_started); }

    inline bool is_running() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_running); }

    inline bool is_complete() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_complete); }

    inline void unwind_stack() BOOST_NOEXCEPT
    {
        if ( is_started() && ! is_complete() && force_unwind() )
        {
            flags_ |= flag_unwind_stack;
            param_type to( unwind_t::force_unwind);
            caller_->jump(
                * callee_,
                & to);
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    inline void push()
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    virtual void destroy() = 0;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_IMPL_H

/* push_coroutine_impl.hpp
i+jTNfCmKvo4ipz3L/CemDIF2xCfT1yMTHVtDz7GlifXxx60wUeRx/gaO6zMwqfsBjv9lVh8Cb6IdSgFP8WlIO/XcdYhm1wSBj+RPOdd36KD+YyhL3smbyOTXZhvb9ZmA7xi/h3AOPYZ+Nj12I4ljC2VfYU48j1vcM4OH1wTWa/Xj/wN+86+0WC0hsgitPQj5P2J+eLxUWOYy5us6agZrNUn8HgGeUgw4xRwgh4v/DiRHIwek6dxDrcvPKuOP43Uz00Rz5MLavYTOGIE63GYPN4q8Bbz/gb5PYmf8TnJAUwNYNw1yOqVR/HD8HnGQ6w9fhhTIwbPgzfIzpQTgTOpN0xg3vAk/Dp0nL7aUNpROh5iTcKJJd3ESvG0J8gVHkT+j2Mbyat1H0LOBNtuKwED63tkLYnj8MV3I4f1s7GVI1lr5Gs4fqNTY2SUea8hlo15kv56gsnR4UvzwPajyP32IJb4GpyELSt8B542Re+r6EGDkXchR3i4IzF2PXKBp9nffRI+ZiJ/xEDuD9DHPoytPTnDqcgf958hfzVpEeMEl68lPkyrA3/JFdVC9vd9icxlg3GK0LtniB0fJy/mAxfgG2/ZiX5hw74awN4UONyDzamxgDz0R/g2ME2jrfj2Duz3RIOLsdUuZO3zXfhPsN946uwdTE77Ne5lrdbHIaPYyLm3AulYpyP48ysZe7tpGnoFfkD+PkvEDxCvRlwHz57F38aC0Ygfx4G3voGPrchXTijFdrCfH05cNB6c0YDcT85yYqyWYImhYHjm95ydfbSXiAWdxCWsnQN8ZL+LeKsx8eON2GHswHXV4amdsSDXPta9Ojx6nTijB/OKWYEf474DHTmPkYSfgkev3wc+GKTAHGIQ+DhpIbkObHokuL0rsrRkNf02IAeH/uftIb7Glqovks9DXlw70NftzK8/ujyL9UVvf8XX5yID71zNnJthA/eByUaABfOIu7CjE/W9RcawmbIcmR69Erwym/PsYCE7+hSXwN7lBHwcuarlc4n9ExhTMuU7bBB4vx4xbH/i4NVjkKVOrCs4dOQkbFkcZwB6gVNp91PKJvZJej6KDSDWb1AHvPM9tjCBWMYOJstnLhns877Gni5174glLtfvawHe6U3um3ijyQzWHpt2CPp9l4Mx+5JjcaI7NWAVpR6lAeXUE5wlGQ1+UfBV2NTbC/GpE1kP5GBoZ2Qmn1xxAudY4dl914PLVmNnsQFHXiE/+yb8AuvWxyd2exg7Qt/JZ5k/+GX5S/DoVfba0O8Fw8CJz2PjbmPPEVtam/Gtq4Z8wNtNYKwX0MmBV+P34E8SYxpLyabkULZQ9lL2U+afxibdgr1I5UwebRW9pz/DAe+JH1cmMY9p6FM31mcg/oI9j9aMMZ09lrIz7K+3Br+Oo7107Cv4p8VlyP1YsEcXsARrUL8+vncIPLwPX9CG+KIuscZVyFEKPB2MDx9FLLOMHEsOPqGjwAayj9wAnccX1b0fXOjhfPhkdAfs9YQen8Ir173k24mb28/Cf97Leu1nT4D92QJsZ+8X8DtPCfaS8en68xO0vQF/WJ9YZyO4JmaeCp5RyOXRnhc/0I+5ouPxf2PvzuN8rvM4gP9+M+4rhHIkZ265QnKPwTgGM+NsNMsYTMYMM+PMRuuoSFaXIkKF2nSnpROdQuQoSRHRQSGVatM+v2bC7tp797889rMz8/19j8/n/Xm/X6/X+/35fH/BkVlipv1TcOA+9hsBO2LYSt14/2y8gcMS8Ouz9M7l4qF/TXk07u73uPy9D11JX7XBo33H0SvJ4jbEnpvVUGF48xHGdyv8WChm3qU529P9crqhDWgh9dWIy9yrlhjgv7Pg0Zg0/Ms=
*/