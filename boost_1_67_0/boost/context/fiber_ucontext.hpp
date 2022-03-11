
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_FIBER_H
#define BOOST_CONTEXT_FIBER_H

#include <boost/predef.h>
#if BOOST_OS_MACOS
#define _XOPEN_SOURCE 600
#endif

extern "C" {
#include <ucontext.h>
}

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
#include <boost/context/detail/externc.hpp>
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/fixedsize_stack.hpp>
#include <boost/context/flags.hpp>
#include <boost/context/preallocated.hpp>
#if defined(BOOST_USE_SEGMENTED_STACKS)
#include <boost/context/segmented_stack.hpp>
#endif
#include <boost/context/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

// tampoline function
// entered if the execution context
// is resumed for the first time
template< typename Record >
static void fiber_entry_func( void * data) noexcept {
    Record * record = static_cast< Record * >( data);
    BOOST_ASSERT( nullptr != record);
    // start execution of toplevel context-function
    record->run();
}

struct BOOST_CONTEXT_DECL fiber_activation_record {
    ucontext_t                                                  uctx{};
    stack_context                                               sctx{};
    bool                                                        main_ctx{ true };
	fiber_activation_record                                       *	from{ nullptr };
    std::function< fiber_activation_record*(fiber_activation_record*&) >    ontop{};
    bool                                                        terminated{ false };
    bool                                                        force_unwind{ false };
#if defined(BOOST_USE_ASAN)
    void                                                    *   fake_stack{ nullptr };
    void                                                    *   stack_bottom{ nullptr };
    std::size_t                                                 stack_size{ 0 };
#endif

    static fiber_activation_record *& current() noexcept;

    // used for toplevel-context
    // (e.g. main context, thread-entry context)
    fiber_activation_record() {
        if ( BOOST_UNLIKELY( 0 != ::getcontext( & uctx) ) ) {
            throw std::system_error(
                    std::error_code( errno, std::system_category() ),
                    "getcontext() failed");
        }
    }

    fiber_activation_record( stack_context sctx_) noexcept :
        sctx( sctx_ ),
        main_ctx( false ) {
    } 

    virtual ~fiber_activation_record() {
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
#if defined(BOOST_USE_SEGMENTED_STACKS)
        // adjust segmented stack properties
        __splitstack_getcontext( from->sctx.segments_ctx);
        __splitstack_setcontext( sctx.segments_ctx);
#endif
#if defined(BOOST_USE_ASAN)
        if ( terminated) {
            __sanitizer_start_switch_fiber( nullptr, stack_bottom, stack_size);
        } else {
            __sanitizer_start_switch_fiber( & from->fake_stack, stack_bottom, stack_size);
        }
#endif
        // context switch from parent context to `this`-context
        ::swapcontext( & from->uctx, & uctx);
#if defined(BOOST_USE_ASAN)
        __sanitizer_finish_switch_fiber( current()->fake_stack,
                                         (const void **) & current()->from->stack_bottom,
                                         & current()->from->stack_size);
#endif
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return exchange( current()->from, nullptr);
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
#if defined(BOOST_USE_SEGMENTED_STACKS)
        // adjust segmented stack properties
        __splitstack_getcontext( from->sctx.segments_ctx);
        __splitstack_setcontext( sctx.segments_ctx);
#endif
#if defined(BOOST_USE_ASAN)
        __sanitizer_start_switch_fiber( & from->fake_stack, stack_bottom, stack_size);
#endif
        // context switch from parent context to `this`-context
        ::swapcontext( & from->uctx, & uctx);
#if defined(BOOST_USE_ASAN)
        __sanitizer_finish_switch_fiber( current()->fake_stack,
                                         (const void **) & current()->from->stack_bottom,
                                         & current()->from->stack_size);
#endif
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return exchange( current()->from, nullptr);
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
#ifndef BOOST_ASSERT_IS_VOID
    bool                        caught{ false };
#endif

    forced_unwind( fiber_activation_record * from_) noexcept :
        from{ from_ } {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
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
        fiber_activation_record{ sctx },
        salloc_{ std::forward< StackAlloc >( salloc) },
        fn_( std::forward< Fn >( fn) ) {
    }

    void deallocate() noexcept override final {
        BOOST_ASSERT( main_ctx || ( ! main_ctx && terminated) );
        destroy( this);
    }

    void run() {
#if defined(BOOST_USE_ASAN)
        __sanitizer_finish_switch_fiber( fake_stack,
                                         (const void **) & from->stack_bottom,
                                         & from->stack_size);
#endif
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
        std::move( c).resume();
        BOOST_ASSERT_MSG( false, "fiber already terminated");
    }
};

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber1( StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t;

    auto sctx = salloc.allocate();
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // stack bottom
    void * stack_bottom = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sctx.size) );
    // create user-context
    if ( BOOST_UNLIKELY( 0 != ::getcontext( & record->uctx) ) ) {
        record->~capture_t();
        salloc.deallocate( sctx);
        throw std::system_error(
                std::error_code( errno, std::system_category() ),
                "getcontext() failed");
    }
    record->uctx.uc_stack.ss_sp = stack_bottom;
    // 64byte gap between control structure and stack top
    record->uctx.uc_stack.ss_size = reinterpret_cast< uintptr_t >( storage) -
            reinterpret_cast< uintptr_t >( stack_bottom) - static_cast< uintptr_t >( 64);
    record->uctx.uc_link = nullptr;
    ::makecontext( & record->uctx, ( void (*)() ) & fiber_entry_func< capture_t >, 1, record);
#if defined(BOOST_USE_ASAN)
    record->stack_bottom = record->uctx.uc_stack.ss_sp;
    record->stack_size = record->uctx.uc_stack.ss_size;
#endif
    return record;
}

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t; 

    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( palloc.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            palloc.sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // stack bottom
    void * stack_bottom = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( palloc.sctx.sp) - static_cast< uintptr_t >( palloc.sctx.size) );
    // create user-context
    if ( BOOST_UNLIKELY( 0 != ::getcontext( & record->uctx) ) ) {
        record->~capture_t();
        salloc.deallocate( palloc.sctx);
        throw std::system_error(
                std::error_code( errno, std::system_category() ),
                "getcontext() failed");
    }
    record->uctx.uc_stack.ss_sp = stack_bottom;
    // 64byte gap between control structure and stack top
    record->uctx.uc_stack.ss_size = reinterpret_cast< uintptr_t >( storage) -
            reinterpret_cast< uintptr_t >( stack_bottom) - static_cast< uintptr_t >( 64);
    record->uctx.uc_link = nullptr;
    ::makecontext( & record->uctx,  ( void (*)() ) & fiber_entry_func< capture_t >, 1, record);
#if defined(BOOST_USE_ASAN)
    record->stack_bottom = record->uctx.uc_stack.ss_sp;
    record->stack_size = record->uctx.uc_stack.ss_size;
#endif
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
        fiber{
                std::allocator_arg,
#if defined(BOOST_USE_SEGMENTED_STACKS)
                segmented_stack(),
#else
                fixedsize_stack(),
#endif
                std::forward< Fn >( fn) } {
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) :
        ptr_{ detail::create_fiber1< fiber >(
                std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {
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

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

    void swap( fiber & other) noexcept {
        std::swap( ptr_, other.ptr_);
    }
};

inline
void swap( fiber & l, fiber & r) noexcept {
    l.swap( r);
}

typedef fiber fiber_context;

}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_FIBER_H

/* fiber_ucontext.hpp
nurQuWZ/oSur5SrZmt8IfoSpErMQRlKgSdJcfnZ1tmB8exIMuqQUY2697YognbDPIxCeIoSmVlBXM3m6zMGXcwnEhTzwHnW9EdlIFUY+dwQ3hpwgrAYz/xzx7Foz2oN/H+Myxwelj2h819n4VfmRJx+dDw1cES2mOOqPf9DIm8ETlmbQeDWPzt18j+cVbVvV8w3buWfpwbTBFlX7QNtJUgtDZDmGgOpah7GdsDxYcClFpxrN0nXs+h2SK5Qg0vgK3x4dJHL57ilCW0L5chOPhfNQsEhudR4FxEw/y45h6G/ol/eho+pZtGxLZ4vAwgd70KuKS983mr6LoAMehYd8v2VnqHu2ucwM4niWgYji3/sHX8moczqTwKbGbAWvMSR0jLjywYgrQr+xr1BhVyrahMJ9ES2a56j4C7s+xYQTuy0mECc2iWtde+Fhocj9XH7Hn2GhJhcIq2bzQeMQ3q7gf5rv88PnCnNCWIW+TTHgDxaXzRYJod1rptAGFTsq402XiHHaG3zPASVCH7HuF1X4nJsQpk6YUAluiVmQ1D233cZjqNtshhVDq9FChU21xzR21JIh4FG6Y7P7KOl8z5D+0PjqLyhPCeUTSaSYdWJ7udq1n8fKBrp+obgtMEGl93tAy+bep+1mrlHmKMlah7L9FcSP0ILHEdZRp+ClCXTUpE0llTp0uSXHd20B1UtKSjDJ5EmA526CNAk+FagZSvO2DDahoOcsT2DuuA4vRQHhSvgOgxTTfifcgP9+P0hPCIGsl28ugVZzoTBwsqSISHzwrQss9lw66NSeiYUBihk1OJ62aMG8zKjKqXQZJ+ShAkfHswZbkB5ybeP0OT9dcIbOTnrPPhe0xYljEOuf46NENe/1tbmzuizVQMQzd17wHqFN0WQeKid/NueP1gGUchS4o+Vk8zGnGDifUwLmBSbW55qURHPWiKufl3hGY/1u6kNTctKHkXvWyYXzUhJSXDm/M1OzBZ/dWnZoru/VSHZsqO9VSnYUegb3cj+PWHsgTs+jJeEchsfTQVX1uytBkF2DX4Yvuywib7zHtmYT7g9qhOLpD8Oc7y06TGemx7890RpJG338YHd9abVO0K4oCaEeR1k1gxxntttCdgeXVrG37jWm2DXIE4VeIscyB5rcVTZ3n62nePo99woL+ZXyG3rE+f0gwgpk/gDOX9R1GOGzdn0w0H83shXyq4Gb7fTstFbqZe7t1rHbIbWxKvLM4Vm7w+xiPcUTIWdZlPK5rRE9J6/TyOHCuKuDO1uff7A/1+g6RWLewk22IlThpmPpcAla1r2+89h/Q8zWunHaFrZroa5+7JTfuxVPmBeXvcsz4kRA9uVdvZ3oV/DygGNrT2+S43HZPcHsFwErpxAed9OFPsIRv0gOwziIg5ego8dKqsJZkVuhdXfYS3++4IKubA0ktbQ8I72THY9apwKvkipswrdbizq+iFyfcjxT4wprIC6EfWvaam+n502np8PnPQFT8NmtrvLqDLxTXE0rmB+WTXCKW2uHujbFrZjbxAeX1m9ypUC7g8Jpv3tmWlFnVMlzndRXLB3ad1D48m2XtXer1luinTOjQT5madDTmnbV8aUpdgcQ+TUlpM53jxFvBLVr74zPPHUhW885XZMTRvmwnuZbMJ+6WP4S0rM4qlWL+OSbS+SnndnxG4NaL1i/1GBwue0VbbM1YaGXKtYe054u9P4an0IpNYOWmbPQIw1fEHcr6l6ykjrBh9hfP/Ac1pV51K87fO4IPIC9FodHfh5bq+hUzP1MW4vTyP3ciT2nLlPhobJs+ID5WDg9glSsK4RX4S+npe151tJWHuuO9H9AvK44udHDMuhc6xn7CDkRYo6w2BFaTfhR97Eyj5Cn65A/aODgUIq3sNghlduwctcdt/y2Hm91lv+Gb7sGDrN/jT2G607wDOHrbBl8g6efObGfZ+AhbxxTbsz7Kmyl6LFrEe58yNO6E5mzKN5d0KUmqUa+PcEtwlDjr0hDKjaYiWqFXIiql2Ul7F3qybr0O+TmvJaQyXwxIeW7M6MqaC8nqWONrDwE3ars6gpDZe2hKhEPdrGXflP8Q/Mb4IcdzJYdkm3G0UUsCXu0yu+9GuUpqkAw3DUMfQfBeOD2fEvlN93WvQtkHdZQr6xtuPXmic0vLka6ckKh/fYUlCBc/9HXcDaBCn0Em8tYHUEfnyjXQ25CkBj+rYkPCYfCQMvVepBVZPqe7HKpHraic4PArVjjSc5i0S6wWUmWIkbsyzrYheIvXiO0lbXJZ7BlqPzdrM268t2t594htNrPLUprPFoPWjufKIVc/xU2VKJncSSE+KqxykbPg6scnuX2HBvoBqLwx647dtG0dFOdvyuAuhSxtrqo8WI779KxwLAQp1+G21fDNFw1uJyaZiPWdz50KQapN0otH+Gu9QAtVx2Kc+38NsK3nnXzPfwGjVCwUh3/GV6/0ULCOtuufMZpWmY94dWVo4fgFuLB9cMWUg7tkCOowwFbIpFIJCzUfjvBeLEHEiP8Vn3Ivif9nf3qu4ZCnxLt1ROby/6j3DC95ttNWoNy3nk2M/6OUYpp0Lzfvr95fpww8MIalC74FdpAbukWY2ePB+ijPvqkqVva8+8KTR/BXry3zU+8Tv+8OedM/+w8b7boJhzXLVceZoNOs93ObrC856uPtJk0KN0NiAvau3PPSSPNdtyu8Pe27YraaOlaoVXKtELIhaaGClndQxCnyLR7QQFCWoP4q6hL6PFw4Zz1ax45jrcVP/FfwJNyGyLTibzOY2tpNTYVMbFhkfjevoAPd8biGjocVvk2Z28F93Arzh6aBo6QDCnpDw9RLyrXlK1P62WNeMwe9pnlg5Y4fG/TXpQAt3xw/qE7LadYP1dITg6Up3fVNuM68aP+3y1lKR/RssDzgoRP2kEvgXWfJlB7+0LazILs8ULjY5Ky9DRT+G6sVQZXAHddrxm8UJln92ihssiqMCEtnUm0Cu7RzmUu1PN0pvDntvl/bxVclNDAWNU9Lf4WZeoMQPwi9HtkaBCAbjrz9KQsXSrRwfN02vTTAxpPueuecgeaSoDDIoaBVUjOwT3ld8hAK9E90wbaSuRHyin+XVp+WlYxmBTfEM5v6n+H/FN3us0MZtJc5m/hKny6B5y0dihXTnEtXgPY80I5OZn/v2Okpk8HWcz8b6TGVGZ+sh2AT0Or4Ophnznb4J6EwFGhph/8o9zf7WTpK3JppiwtgjjZ4nFoTxw6LX2as6u/4FkD8DjPcq8emm7jLFyYjBps5KEDLeFk5DTxQm7b8ekfx6fny8lVmCCjmVZuDjjCRxsU4nZTPghvrlC32KqPBFYlWgoqy/DVUAf/O0v7gOmDW4HHFDggRXK2cVuWkoeWG7AEjr9TPNgIcXCD7FzSABVzZpdWpHO2CwBjrTgbQfbTbW0G1jJ1E95yS5kC0PwP9JeC3186fI/gxHr1hPMP7qB91Kc8VCIvxEpxboLlncZkpAgirdFzACUO+5CA+Y4H9po5B+1TnP0bROC02+svak1ZB7pj0Jyf3YRHFTiop/XuWisSD23v3/xLRVpyyBH0CXH2S2/FepLm9gWf2RvA1lSNJDSmWzloAnN+t3Mm/zQLOoIuSgw9Snl/nUOX1cPQT4LA7gAaYiwDifsh0orBc0C0eQBONFn3gNPoN92a5zR1IgULNWWpchhZYHZOuIn7Ac5i5IDBAGcR5+nFNc24CHyvmQ/nvDZASB1KcMWVL4BlfQrN75Bl04JHg4vrbMYQWvV/Z2v66DNrW1IGDii+s6QH+fgtqjeMG8BFkSSxzZvb/7ZyIc22cmHi2JJSeFjGqYS1nFOQLn/Y34yPI9tgz3c6tQXLTw9DVwJN3Vr+qsX/UbkkfVvHvdZmSSMlWDotLA/9lt3dAyARV6dCrz87PScUUExj4tb6jgKP3IclUEd1NU0LlRO02HreacEXDODAKRn/aDw9UGfqBtrSbLJ2HnMCDrKZtvQJ9ya912zTHpf7eydZEKA1EADYJwdg/HiCVY9F8wsAkk1Ah4CkT0tnMO+TRaZ3ADJkfcLZyDKucTRHog4YB/kInHemrRlIBmcgiDyepf0LJ/3k0sI+oH8AJwsbEJ0ej3wKGfEocQD0DIgcAGFf2LG/0BSS/fYu9MJOuIEilXkAVHf2QYFU4qQqkM+9u23cixKKQEgYLwAQiOtXyCJjO1UsDh0FmiydyfMKAdyBT7k4Mb4NcGuTk0n+d8Ya05nN3kAY6znUlQAHxNQB9GoFlubmxO0nsFFBgKlr02HeA5b2gUEn/o+o7xoitAF4/Djyxr85J+wsm0YfDeaRYs+VsedwHRwqcFZd4Kz6X/olI0GAepn5BJU04dBTAB7/pRHm9v+P2hwCzgtkBzAKVtJURn3ih/YJ7eHm8P5pfhPOlqOHcznkv3ra0BW6CqwKpKZ2JNN/EqA2RROG4dIIym8q4yA905rDARngMxCVeudUQEWokd/hIAMWT5Lg/9TQbWbuv4Tra5BLY47+FeH/GBhXmQ8wMH/CcUklnd6/uEd1xCCs0SX4UXArCfkBfVtjS3B37FfdG8q974Vov2mt3bEh/Cft1fiFzVkYkJPOv6gnAwCN0w0D9MX5Z8olWgvu3xZFzVcBf19hb/DEvxk6AWkq9Jk7sZmaTv9PyJrJyiLA0XE5XdtaCcH9lxR1IvFPwzU4aaQpGzx3i5OZnKBzFIRDIPA0pwr8TfhUQBAA2oI/ceJClv1bdnDFzj/NFiWosJ0HIDo+xY4j7xycbTmkJv7V7UWtvE2OvscArAnAXMroSvJWXKu8Qx7xIL5peOnQZONM5uhfzH/VZ1S36Y4s5ROl9i6bj/Io6a/CWcrSSxwAtvxNFUDhFiUqrTJ4tv8qnD2YzpgCYuMfdEKDU1f+oxcQGY4+/F33uOKcW06onoMEez+57e8wINJvHDhclgFKYgQQxM2/OojIoUpXZOW/77JMoh5q9nPsPo6e09w77PNfDhC3Y/Gz8SCjZkCxP0LfLugE8FC30kzdEKt0+Sdep8t3d/mUFYNuQW7NAJ7hACpxQR7Q+C3t7+HaHKk9BHtL0gHKyJ5E0x3npeq3YfdGd5R5OGw34++gnAPUarmOw9JIQJvhQR+bpvH/r4JRRMxZ+RPI/J5KTmb/4FSP6Z8KHKXhAuZtehEK1ONdU04yiYzY9iCOcVItGeIZb+rDCf1awhz8pfbuhe04jopB9JCRgI6hfvj+V5ZISbVL7JH2nHXjkDuWFywseeX9eri/nTEbO0fN3iD+yT13LOjHc/WXcUY69+8Wn+FFJ1npHM5KnTe0iuZ/2bJttujklMPWhPyuPwWZ/OzXOPAn8rJJF2Pbi8CPIsuxBVBD5hU9AU0LQiK0H1yglR4kzVRlc2WYfYjRNNvi/IXLiXao0tNn4HuxqgtP/a1AeBcXKDmeRWuXallOe7bFisOg6leXLfjhrXJO9LPQoDZBzMoggfaBCzF7GmnSFVxs37+8lxcaRPqcr+GcHI8J6pDDDMeG0SL5oYgTq8z4wPqFmDow/hhsVh8+nAImVeP5WogSqPo1fHHj5mLF3iZmN3Bzt55XMSgJS5JzJsmi8Brwtqzpl1i6EMEvXNikC6k4FAo8uWiX2RHbvFnfFWonRH2TXrAgTMp81hToyaeyqTDwx8jn16UVGp2aC5byR4P8rH16c+jcEL8YVD2BepC6lzvbokuYorRgTxMJ3fz1Yna4537a9b2VzNV6XYQiliiJxfH4cdXjKWtINt4TH0jfpOczZ3lg3Tm0lFymDGJJEdajwFpqdR+Bw7UXpoWnd+qDZ5uEaTo6RM2g2WncZlBFNz9dDLVgB+8onc7FLkuO404wwwmBxL1GR6pjOpickCvop+/TnSM8DcfcIp9Gkq1Z62vZi3yIHsX6AX089Vfo3xddtylsc1CffWGOv6l7QxizWU/ZzkVD9tbZ+I5K8m9KKL15GuMfh9UZ1wlMBHeL4Bph6Wu52r1CuoGpIkxRsA4iWbvHHNZrQVdhr68hdetw6dPk6aUkShgOJqKJNcKMGIHGmdrkQ4p+Hf7a9TmOHaWwNGzfxuJ5DC6L+RKRSGBexi7GJ/gQ2NIauMOIbiRNChLYa85KBfflLL6bnlekD7igpGDrWP+E5vSEnAUXQvG0EAAozRAuVZdSGpRWmjtFoZLjsLQBf676cEd8IJw6nYRIFaElipClWAXF06naFP4WHB+i2t9ZG19Dyd3InhrEp19mviLo2NHTIPRQFobqGZTilau9Dru1qI3qC6y/hPgVDsZZtKBNfMjFTGACJJrNmn/eibeC9yigvXNpjqD6ATCSREiQwpRKDW5EoaXY8UwhND88STEXS0Ki8XtyqF67/8WaA91aUPoa8xJ7ee0YDFCYHNwtDmXM66t1/26NMlyOoCRTVyXwO8noSygitzPuORNgSy+WIjiDywTISbo8TjdifYicTtQmSYEWJdn9EGaEYr15DWI79w7DjsCNmjWsIAYyo+2aegn0OB8/880fhGcAsS4hZvV9iBbMHiSzB0zhR8yZ+VCq9iDP2YpTbDcqGkgDOaYQajgNskhl3tCAp4CJ2qgFp81uEeZLnvrTCLIUgoxmGiqykrFND9l202y5HUTHHoXbCRc9HQ9Z6a0khwLZ47ggQsvZ9OM8tpUo6CfFai+exiH/S4jg36zKBrbdBvszAw9kdQzw2F/U4QsaTT1CtBzgaIE4HiBdWe1IWnsxMwNFi0HRssbX2ZnNEP8TlRNICBEItzZAdMdFAv041C8OMRsIxweyksDLohq4W8DRaP8XY0rDHoTKQvmwx/eaOhSDWmOY8RBStB1dF0USRJF4mIME5iCYzAUiiiLmLWAAzf63msY6+w0D0caCfkfA/2YC7WylXxogDU09aqz/pOH/oY+Yt94E0O+AMAesGeAatjWh1ZrNXOBvIHJWW5G1W9xhdkKZnQCSM4sN00lg4kse+v8hGQEkNhTzjZ21uWeOJxYBkDR1n2X9PyQFMTgejoZxNgkEbrMdyYyyqFdBDJn59HhjqtgOO/A+zSa3/9tkGoQkOz4c20zP2WTG84SIC4XOnQb01t+rk8Go1cXUjk+FjERAiJnu663QZwDeHPE0TyjIVwSlxDOMVXYhuy35bO2dYCNoA8A5YA9B+Q7DQ9oDD29AYLMHkBxRJkZUmmEDtxHjIMKqeXpBfiCgipi/cwmEdh/njALEfBnpvoXaYpVjUM2ry1nu2SjHDq/hoXQf5hsqR+X1gCWhmb4inNM7hbA3tRZA8GIoZyLPTl2i4AztOOGZhdZglrCJESSELNUyHKt7uRlBmEYgfvtuBpkAn1Qwo+tU88Go/7foFs4CVigQ6hjCntNaYLJnm0ZiWX5qnI03SAg1k3KfbRUaDQ+BB8oFwkY4s2FHGLp4dq5/MZAoZyuBdTjDRqYzh/iBMiUFwEE9BKH9hLKCcr52iWzfUtnts2kgcyoLi5nr3gTmFAYjArADRKHA3qIP61mOg8ru8F9ot9K9gJqwO6y7smzGwwLmIkUpwoDJ2WVUZKXW7oLEynKMXdO8AmcrnEoGFEVihvt6G2RrHkCWuo3AMigtlFv+XsDW/7difGDTQrgw8yUSg9rTXQdO2qsAzBgKewpsjisECOKfS0DVxRLfPWMyya3elYOEoHRBz04Q08SC1W6X+bWrkB25udBWGk+VAsahGL8QdT/lnBcdMr8mOBaHDg8Jiph0Cf+tuB2QdJbICjuJQTOGNogLAViFzmk0kAQxpPhAWAHAlizOTmmmWrvsRa18NqQJDIRjd/5sZZCZys5cYIOUED4OyF2Vge9c9X+DiyijdtkJha0kP9uyAECsUY0RwMdTAcbp0v7j098ib0CwaDJCBkGJr/ibOJO1OQz7Yjg8MucgqJsSj+GAQ7DYIK3YGEGaxIFQASU+7i+fFpj0AyL/Iwpnspk1FIpDuvXWymfmAN7HoUFd2hjSS4BzGkBcMbSf/HDKupZLggccTelHcOXHOCZN6VLwMURAF5rxgCwIsmfpHAi1QY17/heNIB7dx1mJSNpNrZ0CfoTTDmMtoBODqBFxSo4PA55pGorDEjkRAmKg78OxGBGVQFo0Di5jtzq4nQFGKOWD/0fp3SKAr+YwSSG8BTCGgK0AosxhEWpebWU5ro6TTUNIjj7AiurV8hWBZMPCitgeu4giDY5N4ngb4huNphFAJPX+IkM/Dfl7HnpApzByLQcITiUQd784HxMj6F/LZQxEhyMBKjv1W3uMAABSABlRO8C6bJlXvx8SJADIwQA8Ob4sD6gGGpBldgcH41lgOXOtwRwA40DOTJ43EPVRaE7efuVhL5k1o751pe+OSKxcDeSwdLkTGsRhUvrflJUEAg4wCQOZWCgtjcc8A8SpSIBBFMQkx7d4dgr7/X/j9XcUxGOLfY/NEQZTwL78X/rvzh8QobV7cJL2TziCEsfCOgZsmavsJJZiaex3QCCfmWmxhPkbKNqg5VaRFuxNlc1wFGfCFuwqu5zCtsWq1rlnazsDI4F8HBQiBHVxcUjHUYo5uZVldsLadKbvJudcmUtjsdQIADPOI395av6/M9AGAscF9lD+m0GtgB4CoBVOBbJAF+uBugHoKxHwsxnPtoo4uGHX9vZsjDhJA3CTalQxpLCybEEtWNjr4mLBWMOxKPRbMH3EnxtCS0bRW4XBfxa4ENh/nInkcAyAc8gIh0RAXmhwtsjZb44zMwLL/ERN2KEN1XNEIwfgUSAnYy2AuGlwuDavsrJsrshq2GIVY9hNq8sx/E2zaYAy/k3Yldxn2WDd5HjKLZWdWcUQ0ngh1WJzTmoPMawNaACnCDYVcjg2Qwdi20nv47AybIWTjOMBnSC2H4Zz4v+jCScEYGLS3x8AyDqFmVkICH4MEH4g+wGqLuy1AnXi76YKgJ+mAfFlprkrLUyzuVKxUe67gpyv+M1nVmoNzGwWST8PvBKPc8FdalcZPd1eFxIX9G/hwUNtLXrXCvmHPhhJd5zoOHzM0sDw4KEzBmUnC08fMr2m8KEzg5qetjZygQIeH6xeis/JwOeGcsHGnarZgfVsw2pUE6WZtj6QMF8NHdpKVISdRTIGCfP+WFI4cgqDDQPMw8xOpyCG6Lx13R9FFxWh4Yph80AsfgYCw5F5ce4E/B+GZiByD7nAhlzH5C6E6mHoPhX8ucLklwk=
*/