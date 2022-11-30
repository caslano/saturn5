
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_CONTEXT_H
#define BOOST_FIBERS_CONTEXT_H

#include <atomic>
#include <chrono>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/core/ignore_unused.hpp>
#if defined(BOOST_NO_CXX17_STD_APPLY)
#include <boost/context/detail/apply.hpp>
#endif
#include <boost/context/fiber.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/parent_from_member.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/slist.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/data.hpp>
#include <boost/fiber/detail/decay_copy.hpp>
#include <boost/fiber/detail/fss.hpp>
#include <boost/fiber/detail/spinlock.hpp>
#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/fixedsize_stack.hpp>
#include <boost/fiber/policy.hpp>
#include <boost/fiber/properties.hpp>
#include <boost/fiber/segmented_stack.hpp>
#include <boost/fiber/type.hpp>
#include <boost/fiber/waker.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class context;
class fiber;
class scheduler;

namespace detail {

struct ready_tag;
typedef intrusive::list_member_hook<
    intrusive::tag< ready_tag >,
    intrusive::link_mode<
        intrusive::auto_unlink
    >
>                                       ready_hook;

struct sleep_tag;
typedef intrusive::set_member_hook<
    intrusive::tag< sleep_tag >,
    intrusive::link_mode<
        intrusive::auto_unlink
    >
>                                       sleep_hook;

struct worker_tag;
typedef intrusive::list_member_hook<
    intrusive::tag< worker_tag >,
    intrusive::link_mode<
        intrusive::auto_unlink
    >
>                                       worker_hook;

struct terminated_tag;
typedef intrusive::slist_member_hook<
    intrusive::tag< terminated_tag >,
    intrusive::link_mode<
        intrusive::safe_link
    >
>                                       terminated_hook;

struct remote_ready_tag;
typedef intrusive::slist_member_hook<
    intrusive::tag< remote_ready_tag >,
    intrusive::link_mode<
        intrusive::safe_link
    >
>                                       remote_ready_hook;

}

class BOOST_FIBERS_DECL context {
private:
    friend class dispatcher_context;
    friend class main_context;
    template< typename Fn, typename ... Arg > friend class worker_context;
    friend class scheduler;

    struct fss_data {
        void                                *   vp{ nullptr };
        detail::fss_cleanup_function::ptr_t     cleanup_function{};

        fss_data() = default;

        fss_data( void * vp_,
                  detail::fss_cleanup_function::ptr_t fn) noexcept :
            vp( vp_),
            cleanup_function(std::move( fn)) {
            BOOST_ASSERT( cleanup_function);
        }

        void do_cleanup() {
            ( * cleanup_function)( vp);
        }
    };

    typedef std::map< uintptr_t, fss_data >             fss_data_t;

#if ! defined(BOOST_FIBERS_NO_ATOMICS)
    std::atomic< std::size_t >                          use_count_;
#else
    std::size_t                                         use_count_;
#endif
#if ! defined(BOOST_FIBERS_NO_ATOMICS)
    detail::remote_ready_hook                           remote_ready_hook_{};
#endif
    detail::spinlock                                    splk_{};
    bool                                                terminated_{ false };
    wait_queue                                          wait_queue_{};
public:
#if ! defined(BOOST_FIBERS_NO_ATOMICS)
    std::atomic<size_t>                                 waker_epoch_{ 0 };
#endif
private:
    scheduler                                       *   scheduler_{ nullptr };
    fss_data_t                                          fss_data_{};
    detail::sleep_hook                                  sleep_hook_{};
    waker                                               sleep_waker_{};
    detail::ready_hook                                  ready_hook_{};
    detail::terminated_hook                             terminated_hook_{};
    detail::worker_hook                                 worker_hook_{};
    fiber_properties                                *   properties_{ nullptr };
    boost::context::fiber                               c_{};
    std::chrono::steady_clock::time_point               tp_;
    type                                                type_;
    launch                                              policy_;

    context( std::size_t initial_count, type t, launch policy) noexcept :
        use_count_{ initial_count },
        tp_{ (std::chrono::steady_clock::time_point::max)() },
        type_{ t },
        policy_{ policy } {
    }

public:
    class id {
    private:
        context  *   impl_{ nullptr };

    public:
        id() = default;

        explicit id( context * impl) noexcept :
            impl_{ impl } {
        }

        bool operator==( id const& other) const noexcept {
            return impl_ == other.impl_;
        }

        bool operator!=( id const& other) const noexcept {
            return impl_ != other.impl_;
        }

        bool operator<( id const& other) const noexcept {
            return impl_ < other.impl_;
        }

        bool operator>( id const& other) const noexcept {
            return other.impl_ < impl_;
        }

        bool operator<=( id const& other) const noexcept {
            return ! ( * this > other);
        }

        bool operator>=( id const& other) const noexcept {
            return ! ( * this < other);
        }

        template< typename charT, class traitsT >
        friend std::basic_ostream< charT, traitsT > &
        operator<<( std::basic_ostream< charT, traitsT > & os, id const& other) {
            if ( nullptr != other.impl_) {
                return os << other.impl_;
            }
            return os << "{not-valid}";
        }

        explicit operator bool() const noexcept {
            return nullptr != impl_;
        }

        bool operator!() const noexcept {
            return nullptr == impl_;
        }
    };

    static context * active() noexcept;

    static void reset_active() noexcept;

    context( context const&) = delete;
    context( context &&) = delete;
    context & operator=( context const&) = delete;
    context & operator=( context &&) = delete;

    #if !defined(BOOST_EMBTC)
  
    friend bool
    operator==( context const& lhs, context const& rhs) noexcept {
        return & lhs == & rhs;
    }

    #else
  
    friend bool
    operator==( context const& lhs, context const& rhs) noexcept;

    #endif
      
    virtual ~context();

    scheduler * get_scheduler() const noexcept {
        return scheduler_;
    }

    id get_id() const noexcept;

    bool is_resumable() const noexcept {
        return static_cast<bool>(c_);
    }

    void resume() noexcept;
    void resume( detail::spinlock_lock &) noexcept;
    void resume( context *) noexcept;

    void suspend() noexcept;
    void suspend( detail::spinlock_lock &) noexcept;

    boost::context::fiber suspend_with_cc() noexcept;
    boost::context::fiber terminate() noexcept;

    void join();

    void yield() noexcept;

    bool wait_until( std::chrono::steady_clock::time_point const&) noexcept;
    bool wait_until( std::chrono::steady_clock::time_point const&,
                     detail::spinlock_lock &,
                     waker &&) noexcept;

    bool wake(const size_t) noexcept;

    waker create_waker() noexcept {
        // this operation makes all previously created wakers to be outdated
        return { this, ++waker_epoch_ };
    }

    void schedule( context *) noexcept;

    bool is_context( type t) const noexcept {
        return type::none != ( type_ & t);
    }

    void * get_fss_data( void const * vp) const;

    void set_fss_data(
        void const * vp,
        detail::fss_cleanup_function::ptr_t const& cleanup_fn,
        void * data,
        bool cleanup_existing);

    void set_properties( fiber_properties * props) noexcept;

    fiber_properties * get_properties() const noexcept {
        return properties_;
    }

    launch get_policy() const noexcept {
        return policy_;
    }

    bool worker_is_linked() const noexcept;

    bool ready_is_linked() const noexcept;

    bool remote_ready_is_linked() const noexcept;

    bool sleep_is_linked() const noexcept;

    bool terminated_is_linked() const noexcept;

    template< typename List >
    void worker_link( List & lst) noexcept {
        static_assert( std::is_same< typename List::value_traits::hook_type, detail::worker_hook >::value, "not a worker-queue");
        BOOST_ASSERT( ! worker_is_linked() );
        lst.push_back( * this);
    }

    template< typename List >
    void ready_link( List & lst) noexcept {
        static_assert( std::is_same< typename List::value_traits::hook_type, detail::ready_hook >::value, "not a ready-queue");
        BOOST_ASSERT( ! ready_is_linked() );
        lst.push_back( * this);
    }

    template< typename List >
    void remote_ready_link( List & lst) noexcept {
        static_assert( std::is_same< typename List::value_traits::hook_type, detail::remote_ready_hook >::value, "not a remote-ready-queue");
        BOOST_ASSERT( ! remote_ready_is_linked() );
        lst.push_back( * this);
    }

    template< typename Set >
    void sleep_link( Set & set) noexcept {
        static_assert( std::is_same< typename Set::value_traits::hook_type,detail::sleep_hook >::value, "not a sleep-queue");
        BOOST_ASSERT( ! sleep_is_linked() );
        set.insert( * this);
    }

    template< typename List >
    void terminated_link( List & lst) noexcept {
        static_assert( std::is_same< typename List::value_traits::hook_type, detail::terminated_hook >::value, "not a terminated-queue");
        BOOST_ASSERT( ! terminated_is_linked() );
        lst.push_back( * this);
    }

    void worker_unlink() noexcept;

    void ready_unlink() noexcept;

    void sleep_unlink() noexcept;

    void detach() noexcept;

    void attach( context *) noexcept;

    #if !defined(BOOST_EMBTC)
      
    friend void intrusive_ptr_add_ref( context * ctx) noexcept {
        BOOST_ASSERT( nullptr != ctx);
        ctx->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    friend void intrusive_ptr_release( context * ctx) noexcept {
        BOOST_ASSERT( nullptr != ctx);
        if ( 1 == ctx->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            boost::context::fiber c = std::move( ctx->c_);
            // destruct context
            ctx->~context();
            // deallocated stack
            std::move( c).resume();
        }
    }
    
    #else
      
    friend void intrusive_ptr_add_ref( context * ctx) noexcept;
    friend void intrusive_ptr_release( context * ctx) noexcept;
    
    #endif
      
};

#if defined(BOOST_EMBTC)

    inline bool
    operator==( context const& lhs, context const& rhs) noexcept {
        return & lhs == & rhs;
    }

    inline void intrusive_ptr_add_ref( context * ctx) noexcept {
        BOOST_ASSERT( nullptr != ctx);
        ctx->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    inline void intrusive_ptr_release( context * ctx) noexcept {
        BOOST_ASSERT( nullptr != ctx);
        if ( 1 == ctx->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            boost::context::fiber c = std::move( ctx->c_);
            // destruct context
            ctx->~context();
            // deallocated stack
            std::move( c).resume();
        }
    }
    
#endif
    
inline
bool operator<( context const& l, context const& r) noexcept {
    return l.get_id() < r.get_id();
}

template< typename Fn, typename ... Arg >
class worker_context final : public context {
private:
    typename std::decay< Fn >::type                     fn_;
    std::tuple< Arg ... >                               arg_;

    boost::context::fiber
    run_( boost::context::fiber && c) {
        {
            // fn and tpl must be destroyed before calling terminate()
            auto fn = std::move( fn_);
            auto arg = std::move( arg_);
#if (defined(BOOST_USE_UCONTEXT)||defined(BOOST_USE_WINFIB))
            std::move( c).resume();
#else
            boost::ignore_unused(c);
#endif
#if defined(BOOST_NO_CXX17_STD_APPLY)
           boost::context::detail::apply( std::move( fn), std::move( arg) );
#else
           std::apply( std::move( fn), std::move( arg) );
#endif
        }
        // terminate context
        return terminate();
    }

public:
    template< typename StackAlloc >
    worker_context( launch policy,
                    fiber_properties* properties,
                    boost::context::preallocated const& palloc, StackAlloc && salloc,
                    Fn && fn, Arg ... arg) :
            context{ 1, type::worker_context, policy },
            fn_( std::forward< Fn >( fn) ),
            arg_( std::forward< Arg >( arg) ... ) {
        if ( properties != nullptr ) {
            set_properties(properties);
            properties->set_context(this);
        }
        c_ = boost::context::fiber{ std::allocator_arg, palloc, std::forward< StackAlloc >( salloc),
                                    std::bind( & worker_context::run_, this, std::placeholders::_1) };
#if (defined(BOOST_USE_UCONTEXT)||defined(BOOST_USE_WINFIB))
        c_ = std::move( c_).resume();
#endif
    }

    template< typename StackAlloc >
    worker_context( launch policy,
                    boost::context::preallocated const& palloc, StackAlloc && salloc,
                    Fn && fn, Arg ... arg) :
            worker_context( policy, palloc, salloc, nullptr, std::forward<Fn>( fn ), std::forward<Arg>( arg ) ... ){
    }
};


template< typename StackAlloc, typename Fn, typename ... Arg >
static intrusive_ptr< context > make_worker_context_with_properties( launch policy,
                                                     fiber_properties* properties,
                                                     StackAlloc && salloc,
                                                     Fn && fn, Arg ... arg) {
    typedef worker_context< Fn, Arg ... >   context_t;

    auto sctx = salloc.allocate();
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sizeof( context_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    void * stack_bottom = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sctx.size) );
    const std::size_t size = reinterpret_cast< uintptr_t >( storage) - reinterpret_cast< uintptr_t >( stack_bottom);
    // placement new of context on top of fiber's stack
    return intrusive_ptr< context >{ 
            new ( storage) context_t{
                policy,
                properties,
                boost::context::preallocated{ storage, size, sctx },
                std::forward< StackAlloc >( salloc),
                std::forward< Fn >( fn),
                std::forward< Arg >( arg) ... } };
}

template< typename StackAlloc, typename Fn, typename ... Arg >
static intrusive_ptr< context > make_worker_context( launch policy,
                                                     StackAlloc && salloc,
                                                     Fn && fn, Arg ... arg){
    return make_worker_context_with_properties( policy, nullptr, std::forward<StackAlloc>(salloc),
                                                std::forward<Fn>( fn ), std::forward<Arg>( arg ) ... );
}


}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_CONTEXT_H

/* context.hpp
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
*/