
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_FIBER_H
#define BOOST_CONTEXT_FIBER_H

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
static VOID WINAPI fiber_entry_func( LPVOID data) noexcept {
    Record * record = static_cast< Record * >( data);
    BOOST_ASSERT( nullptr != record);
    // start execution of toplevel context-function
    record->run();
}

struct BOOST_CONTEXT_DECL fiber_activation_record {
    LPVOID                                                      fiber{ nullptr };
    stack_context                                               sctx{};
    bool                                                        main_ctx{ true };
    fiber_activation_record                                       *   from{ nullptr };
    std::function< fiber_activation_record*(fiber_activation_record*&) >    ontop{};
    bool                                                        terminated{ false };
    bool                                                        force_unwind{ false };

    static fiber_activation_record *& current() noexcept;

    // used for toplevel-context
    // (e.g. main context, thread-entry context)
    fiber_activation_record() noexcept {
#if ( _WIN32_WINNT > 0x0600)
        if ( ::IsThreadAFiber() ) {
            fiber = ::GetCurrentFiber();
        } else {
            fiber = ::ConvertThreadToFiber( nullptr);
        }
#else
        fiber = ::ConvertThreadToFiber( nullptr);
        if ( BOOST_UNLIKELY( nullptr == fiber) ) {
            BOOST_ASSERT( ERROR_ALREADY_FIBER == ::GetLastError());
            fiber = ::GetCurrentFiber(); 
            BOOST_ASSERT( nullptr != fiber);
            BOOST_ASSERT( reinterpret_cast< LPVOID >( 0x1E00) != fiber);
        }
#endif
    }

    fiber_activation_record( stack_context sctx_) noexcept :
        sctx{ sctx_ },
        main_ctx{ false } {
    } 

    virtual ~fiber_activation_record() {
        if ( BOOST_UNLIKELY( main_ctx) ) {
            ::ConvertFiberToThread();
        } else {
            ::DeleteFiber( fiber);
        }
    }

    fiber_activation_record( fiber_activation_record const&) = delete;
    fiber_activation_record & operator=( fiber_activation_record const&) = delete;

    bool is_main_context() const noexcept {
        return main_ctx;
    }

    fiber_activation_record * resume() {
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
    fiber_activation_record * resume_with( Fn && fn) {
        from = current();
        // store `this` in static, thread local pointer
        // `this` will become the active (running) context
        // returned by fiber::current()
        current() = this;
#if defined(BOOST_NO_CXX14_GENERIC_LAMBDAS)
        current()->ontop = std::bind(
                [](typename std::decay< Fn >::type & fn, fiber_activation_record *& ptr){
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
        current()->ontop = [fn=std::forward<Fn>(fn)](fiber_activation_record *& ptr){
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

struct BOOST_CONTEXT_DECL fiber_activation_record_initializer {
    fiber_activation_record_initializer() noexcept;
    ~fiber_activation_record_initializer();
};

struct forced_unwind {
    fiber_activation_record  *  from{ nullptr };

    explicit forced_unwind( fiber_activation_record * from_) :
        from{ from_ } {
    }
};

template< typename Ctx, typename StackAlloc, typename Fn >
class fiber_capture_record : public fiber_activation_record {
private:
    typename std::decay< StackAlloc >::type             salloc_;
    typename std::decay< Fn >::type                     fn_;

    static void destroy( fiber_capture_record * p) noexcept {
        typename std::decay< StackAlloc >::type salloc = std::move( p->salloc_);
        stack_context sctx = p->sctx;
        // deallocate activation record
        p->~fiber_capture_record();
        // destroy stack with stack allocator
        salloc.deallocate( sctx);
    }

public:
    fiber_capture_record( stack_context sctx, StackAlloc && salloc, Fn && fn) noexcept :
        fiber_activation_record( sctx),
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
        }
        // this context has finished its task
        from = nullptr;
        ontop = nullptr;
        terminated = true;
        force_unwind = false;
        std::move( c).resume();
        BOOST_ASSERT_MSG( false, "fiber already terminated");
    }
};

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber1( StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t;

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
    record->fiber = ::CreateFiber( sctx.size, & detail::fiber_entry_func< capture_t >, record);
    return record;
}

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t; 

    BOOST_ASSERT( ( sizeof( capture_t) ) < palloc.size);
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( palloc.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            palloc.sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // create user-context
    record->fiber = ::CreateFiber( palloc.sctx.size, & detail::fiber_entry_func< capture_t >, record);
    return record;
}

}

class BOOST_CONTEXT_DECL fiber {
private:
    friend struct detail::fiber_activation_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend class detail::fiber_capture_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::fiber_activation_record * detail::create_fiber1( StackAlloc &&, Fn &&);

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::fiber_activation_record * detail::create_fiber2( preallocated, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend fiber
    callcc( std::allocator_arg_t, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend fiber
    callcc( std::allocator_arg_t, preallocated, StackAlloc &&, Fn &&);

    detail::fiber_activation_record   *   ptr_{ nullptr };

    fiber( detail::fiber_activation_record * ptr) noexcept :
        ptr_{ ptr } {
    }

public:
    fiber() = default;

    template< typename Fn, typename = detail::disable_overload< fiber, Fn > >
    fiber( Fn && fn) :
        fiber{ std::allocator_arg,
               fixedsize_stack(),
               std::forward< Fn >( fn) } {
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) :
        ptr_{ detail::create_fiber1< fiber >(
                std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {;
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, preallocated palloc, StackAlloc && salloc, Fn && fn) :
        ptr_{ detail::create_fiber2< fiber >(
                palloc, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {
    }

    ~fiber() {
        if ( BOOST_UNLIKELY( nullptr != ptr_) && ! ptr_->main_ctx) {
            if ( BOOST_LIKELY( ! ptr_->terminated) ) {
                ptr_->force_unwind = true;
                ptr_->resume();
                BOOST_ASSERT( ptr_->terminated);
            }
            ptr_->deallocate();
        }
    }

    fiber( fiber const&) = delete;
    fiber & operator=( fiber const&) = delete;

    fiber( fiber && other) noexcept {
        swap( other);
    }

    fiber & operator=( fiber && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            fiber tmp = std::move( other);
            swap( tmp);
        }
        return * this;
    }

    fiber resume() && {
        BOOST_ASSERT( nullptr != ptr_);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::fiber_activation_record * ptr = detail::exchange( ptr_, nullptr)->resume();
#else
        detail::fiber_activation_record * ptr = std::exchange( ptr_, nullptr)->resume();
#endif
        if ( BOOST_UNLIKELY( detail::fiber_activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::fiber_activation_record::current()->ontop) ) {
            ptr = detail::fiber_activation_record::current()->ontop( ptr);
            detail::fiber_activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    template< typename Fn >
    fiber resume_with( Fn && fn) && {
        BOOST_ASSERT( nullptr != ptr_);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::fiber_activation_record * ptr =
            detail::exchange( ptr_, nullptr)->resume_with< fiber >( std::forward< Fn >( fn) );
#else
        detail::fiber_activation_record * ptr =
            std::exchange( ptr_, nullptr)->resume_with< fiber >( std::forward< Fn >( fn) );
#endif
        if ( BOOST_UNLIKELY( detail::fiber_activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::fiber_activation_record::current()->ontop) ) {
            ptr = detail::fiber_activation_record::current()->ontop( ptr);
            detail::fiber_activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    explicit operator bool() const noexcept {
        return nullptr != ptr_ && ! ptr_->terminated;
    }

    bool operator!() const noexcept {
        return nullptr == ptr_ || ptr_->terminated;
    }

    bool operator<( fiber const& other) const noexcept {
        return ptr_ < other.ptr_;
    }
    
    #if !defined(BOOST_EMBTC)
    
    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

    #else
    
    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other);

    #endif

    void swap( fiber & other) noexcept {
        std::swap( ptr_, other.ptr_);
    }
};

#if defined(BOOST_EMBTC)

    template< typename charT, class traitsT >
    inline std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

#endif

inline
void swap( fiber & l, fiber & r) noexcept {
    l.swap( r);
}

typedef fiber fiber_context;

}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_FIBER_H

/* fiber_winfib.hpp
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
*/