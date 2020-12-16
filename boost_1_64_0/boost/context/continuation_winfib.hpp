
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_CONTINUATION_H
#define BOOST_CONTEXT_CONTINUATION_H

#include <windows.h>

#include <boost/context/detail/config.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <memory>
#include <ostream>
#include <system_error>
#include <tuple>
#include <utility>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/disable_overload.hpp>
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
#include <boost/context/detail/exchange.hpp>
#endif
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/fixedsize_stack.hpp>
#include <boost/context/flags.hpp>
#include <boost/context/preallocated.hpp>
#include <boost/context/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4702)
#endif

namespace boost {
namespace context {
namespace detail {

// tampoline function
// entered if the execution context
// is resumed for the first time
template< typename Record >
static VOID WINAPI entry_func( LPVOID data) noexcept {
    Record * record = static_cast< Record * >( data);
    BOOST_ASSERT( nullptr != record);
    // start execution of toplevel context-function
    record->run();
}

struct BOOST_CONTEXT_DECL activation_record {
    LPVOID                                                      fiber{ nullptr };
    stack_context                                               sctx{};
    bool                                                        main_ctx{ true };
    activation_record                                       *   from{ nullptr };
    std::function< activation_record*(activation_record*&) >    ontop{};
    bool                                                        terminated{ false };
    bool                                                        force_unwind{ false };

    static activation_record *& current() noexcept;

    // used for toplevel-context
    // (e.g. main context, thread-entry context)
    activation_record() noexcept {
#if ( _WIN32_WINNT > 0x0600)
        if ( ::IsThreadAFiber() ) {
            fiber = ::GetCurrentFiber();
        } else {
            fiber = ::ConvertThreadToFiber( nullptr);
        }
#else
        fiber = ::ConvertThreadToFiber( nullptr);
        if ( BOOST_UNLIKELY( nullptr == fiber) ) {
            DWORD err = ::GetLastError();
            BOOST_ASSERT( ERROR_ALREADY_FIBER == err);
            fiber = ::GetCurrentFiber(); 
            BOOST_ASSERT( nullptr != fiber);
            BOOST_ASSERT( reinterpret_cast< LPVOID >( 0x1E00) != fiber);
        }
#endif
    }

    activation_record( stack_context sctx_) noexcept :
        sctx{ sctx_ },
        main_ctx{ false } {
    } 

    virtual ~activation_record() {
        if ( BOOST_UNLIKELY( main_ctx) ) {
            ::ConvertFiberToThread();
        } else {
            ::DeleteFiber( fiber);
        }
    }

    activation_record( activation_record const&) = delete;
    activation_record & operator=( activation_record const&) = delete;

    bool is_main_context() const noexcept {
        return main_ctx;
    }

    activation_record * resume() {
        from = current();
        // store `this` in static, thread local pointer
        // `this` will become the active (running) context
        current() = this;
        // context switch from parent context to `this`-context
        // context switch
        ::SwitchToFiber( fiber);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return detail::exchange( current()->from, nullptr);
#else
        return std::exchange( current()->from, nullptr);
#endif
    }

    template< typename Ctx, typename Fn >
    activation_record * resume_with( Fn && fn) {
        from = current();
        // store `this` in static, thread local pointer
        // `this` will become the active (running) context
        // returned by continuation::current()
        current() = this;
#if defined(BOOST_NO_CXX14_GENERIC_LAMBDAS)
        current()->ontop = std::bind(
                [](typename std::decay< Fn >::type & fn, activation_record *& ptr){
                    Ctx c{ ptr };
                    c = fn( std::move( c) );
                    if ( ! c) {
                        ptr = nullptr;
                    }
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                    return exchange( c.ptr_, nullptr);
#else
                    return std::exchange( c.ptr_, nullptr);
#endif
                },
                std::forward< Fn >( fn),
                std::placeholders::_1);
#else
        current()->ontop = [fn=std::forward<Fn>(fn)](activation_record *& ptr){
            Ctx c{ ptr };
            c = fn( std::move( c) );
            if ( ! c) {
                ptr = nullptr;
            }
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
            return exchange( c.ptr_, nullptr);
#else
            return std::exchange( c.ptr_, nullptr);
#endif
        };
#endif
        // context switch
        ::SwitchToFiber( fiber);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return detail::exchange( current()->from, nullptr);
#else
        return std::exchange( current()->from, nullptr);
#endif
    }

    virtual void deallocate() noexcept {
    }
};

struct BOOST_CONTEXT_DECL activation_record_initializer {
    activation_record_initializer() noexcept;
    ~activation_record_initializer();
};

struct forced_unwind {
    activation_record   *   from{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool                    caught{ false };
#endif

    explicit forced_unwind( activation_record * from_) :
        from{ from_ } {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

template< typename Ctx, typename StackAlloc, typename Fn >
class capture_record : public activation_record {
private:
    typename std::decay< StackAlloc >::type             salloc_;
    typename std::decay< Fn >::type                     fn_;

    static void destroy( capture_record * p) noexcept {
        typename std::decay< StackAlloc >::type salloc = std::move( p->salloc_);
        stack_context sctx = p->sctx;
        // deallocate activation record
        p->~capture_record();
        // destroy stack with stack allocator
        salloc.deallocate( sctx);
    }

public:
    capture_record( stack_context sctx, StackAlloc && salloc, Fn && fn) noexcept :
        activation_record( sctx),
        salloc_( std::forward< StackAlloc >( salloc)),
        fn_( std::forward< Fn >( fn) ) {
    }

    void deallocate() noexcept override final {
        BOOST_ASSERT( main_ctx || ( ! main_ctx && terminated) );
        destroy( this);
    }

    void run() {
        Ctx c{ from };
        try {
            // invoke context-function
#if defined(BOOST_NO_CXX17_STD_INVOKE)
            c = boost::context::detail::invoke( fn_, std::move( c) );
#else
            c = std::invoke( fn_, std::move( c) );
#endif  
        } catch ( forced_unwind const& ex) {
            c = Ctx{ ex.from };
#ifndef BOOST_ASSERT_IS_VOID
            const_cast< forced_unwind & >( ex).caught = true;
#endif
        }
        // this context has finished its task
        from = nullptr;
        ontop = nullptr;
        terminated = true;
        force_unwind = false;
        c.resume();
        BOOST_ASSERT_MSG( false, "continuation already terminated");
    }
};

template< typename Ctx, typename StackAlloc, typename Fn >
static activation_record * create_context1( StackAlloc && salloc, Fn && fn) {
    typedef capture_record< Ctx, StackAlloc, Fn >  capture_t;

    auto sctx = salloc.allocate();
    BOOST_ASSERT( ( sizeof( capture_t) ) < sctx.size);
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // create user-context
    record->fiber = ::CreateFiber( sctx.size, & detail::entry_func< capture_t >, record);
    return record;
}

template< typename Ctx, typename StackAlloc, typename Fn >
static activation_record * create_context2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    typedef capture_record< Ctx, StackAlloc, Fn >  capture_t; 

    BOOST_ASSERT( ( sizeof( capture_t) ) < palloc.size);
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( palloc.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            palloc.sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // create user-context
    record->fiber = ::CreateFiber( palloc.sctx.size, & detail::entry_func< capture_t >, record);
    return record;
}

}

class BOOST_CONTEXT_DECL continuation {
private:
    friend struct detail::activation_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend class detail::capture_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::activation_record * detail::create_context1( StackAlloc &&, Fn &&);

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::activation_record * detail::create_context2( preallocated, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend continuation
    callcc( std::allocator_arg_t, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend continuation
    callcc( std::allocator_arg_t, preallocated, StackAlloc &&, Fn &&);

    detail::activation_record   *   ptr_{ nullptr };

    continuation( detail::activation_record * ptr) noexcept :
        ptr_{ ptr } {
    }

public:
    continuation() = default;

    ~continuation() {
        if ( BOOST_UNLIKELY( nullptr != ptr_) && ! ptr_->main_ctx) {
            if ( BOOST_LIKELY( ! ptr_->terminated) ) {
                ptr_->force_unwind = true;
                ptr_->resume();
                BOOST_ASSERT( ptr_->terminated);
            }
            ptr_->deallocate();
        }
    }

    continuation( continuation const&) = delete;
    continuation & operator=( continuation const&) = delete;

    continuation( continuation && other) noexcept {
        swap( other);
    }

    continuation & operator=( continuation && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            continuation tmp = std::move( other);
            swap( tmp);
        }
        return * this;
    }

    continuation resume() & {
        return std::move( * this).resume();
    }

    continuation resume() && {
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::activation_record * ptr = detail::exchange( ptr_, nullptr)->resume();
#else
        detail::activation_record * ptr = std::exchange( ptr_, nullptr)->resume();
#endif
        if ( BOOST_UNLIKELY( detail::activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::activation_record::current()->ontop) ) {
            ptr = detail::activation_record::current()->ontop( ptr);
            detail::activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    template< typename Fn >
    continuation resume_with( Fn && fn) & {
        return std::move( * this).resume_with( std::forward< Fn >( fn) );
    }

    template< typename Fn >
    continuation resume_with( Fn && fn) && {
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::activation_record * ptr =
            detail::exchange( ptr_, nullptr)->resume_with< continuation >( std::forward< Fn >( fn) );
#else
        detail::activation_record * ptr =
            std::exchange( ptr_, nullptr)->resume_with< continuation >( std::forward< Fn >( fn) );
#endif
        if ( BOOST_UNLIKELY( detail::activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::activation_record::current()->ontop) ) {
            ptr = detail::activation_record::current()->ontop( ptr);
            detail::activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    explicit operator bool() const noexcept {
        return nullptr != ptr_ && ! ptr_->terminated;
    }

    bool operator!() const noexcept {
        return nullptr == ptr_ || ptr_->terminated;
    }

    bool operator<( continuation const& other) const noexcept {
        return ptr_ < other.ptr_;
    }

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, continuation const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

    void swap( continuation & other) noexcept {
        std::swap( ptr_, other.ptr_);
    }
};

template<
    typename Fn,
    typename = detail::disable_overload< continuation, Fn >
>
continuation
callcc( Fn && fn) {
    return callcc(
            std::allocator_arg,
            fixedsize_stack(),
            std::forward< Fn >( fn) );
}

template< typename StackAlloc, typename Fn >
continuation
callcc( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) {
    return continuation{
        detail::create_context1< continuation >(
                std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) }.resume();
}

template< typename StackAlloc, typename Fn >
continuation
callcc( std::allocator_arg_t, preallocated palloc, StackAlloc && salloc, Fn && fn) {
    return continuation{
        detail::create_context2< continuation >(
                palloc, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) }.resume();
}

inline
void swap( continuation & l, continuation & r) noexcept {
    l.swap( r);
}

}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_CONTINUATION_H

/* continuation_winfib.hpp
dino5VSIl0eCzkFdY9tZPjMO+ktjyAOofxwcpX6b2qWO/OAZ5KvfE/MrJ4Ht/gnkM3Y86FgS9AP+8+9HjWAfC635iYng04Gv+TsDXbCDv8H8zaomaN8u8COgOw9CG194BsQ2EyCugvT7xDxD0zZiLibml9dPTxdjMYq7DjkY5Ac2edllwHez8EtDKR5OO0X9ThwC/ddW0N9BWyw4CuwIdHTUaJA1yPmzBNgOtMfqVuhLrwHgNurvT4Z6Z7Gbl+uh3S4H/QL9rR0MbTreD3PwLd7nSaDzP47ROITmHWKToD85BvQLyj4RrhEWzgWDaP5kd4gR9RyXv//rcIr6vToQ4tGdwZ5Gi3HcxizxNqVtBB1815ozKqF5s8+gvbuiYC+nQTuVwvgJdOpy8OXngnzvPxT8Lchx6t5gQ4LHO4ZAeY3ZefvxXBjvQj/8UATGbUGIobogfoS4JH4O+MdlYMegYzdeBHmgt+3gn9JQl2NXgy+BMlbB1Qjt0jMG5g63FfOfpwEPYl6mM2z5lpPAj4COydAytZj8+dWgu5Odgn5brvOn3Ql12W5xjrnXwblpPTwA7ItkPJJkdT3U6x3wi6fBczPEtxmQS9e5YCcg7yeuBZ0cCXa4D9yDrhwD7bJ0ZJa5m17yeWeLebzR4Id2BJvtB3WA+xsPzM5T9flgMzw3yrgNoANgB4vB18YOgPkVgPnLbNCDBmiv/UF3QL/7g95/vh/pTSnoRQuU1WKNb6h9tv0e+K69YMx5KI3514F+j/bCroK+dB9rPDQedOC5KTTHU0VzFtv46zAiRjp9jkXTivP3bYN++Bpv2h+AtzEDnG9/3/6+/X37+/b37e/b37e/b3/f/r79ffv7X/8S06c7ezgDyvtXqTHIvPq6+W2Bxqb6uQtmNjgqrR+lNRyu06Y5g6v6w+grrV6HlwLGgrltjQgxr3lmQ6DtiJYGZ/z36g7bJ0sGFLV5mDOg6hjAG6um/WC26TgoeyiUo98QdXbogy06gqGIs1mlK9ghKr0zGc8kdFoA0laptI6eeBjgGH+1SoNtkKlkyFFpxwLcGpWWUp9wcDZPdgZVDQLeg+I1eWk/JKy2vEO5ivUFMgFY3rJ5a6df6fFqmRDe9y8NAf62IBlVl4Sj6zIM6rIH1UXPLqeCgY5gT7R7GfISAZz+kIZfmgM644EXJccOyYujNm4Hw2HNBz8gD9MAHiQGKPIXaGsJ1M9tqGta0BKY3dq8oAURfalAQfHdRXzPID71CDgVaJ+IMsTnfuq51jz3V8+TzPMA9byPluVAyD6O+Uf5HJiJqa++hvdOBzunIS+eFOBjjFdGgSVU9k5U1pJapI2y6S6S9jSivRjx5gcysUC789EWpN9j0pZgGuqMTkOJf6TapERZQUmsNGt5bXZ55VRe3KUNOgC89wPeEx7eo7GA26x0D/gzsrYpNztYwmQQx+JUYiLiZUmndk1Su0LZfnrZy0bdTZMdDgTdXUF1gTSF05PqwGPToywbzhuIecZKOS+Adop5aJVSxttiOlumTs8AfKlKJ+tU8LVkn71CdpVONBHoSQnzNM+qHuNz2kVLc/NcROAHgNb2u9S1337lCnFACV7wPKQU2h818QSAUbAnss1kL6euvq1xYV1bY3NToL65qa3h8DZdpD+d2uokojcrtz3XzZ07o67+EHDD89vqmuobuBL+HKJ5ilWfU0v99TmN6rNCw8L9oHLVNv2UTPi+n7kf1X/L5lmkE2dge8yFne+zMjFcH65t9kxMb1Gns6bSkVia2/wsnZ6M9gbTEaCv7HkAMLGySHse5ekbZnUHO1PoS1chnZSj7BXqW3J2gfb6mIfeQn2qLOnjMtTflni8W9c=
*/