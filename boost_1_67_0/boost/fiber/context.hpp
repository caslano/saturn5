
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

struct wait_tag;
typedef intrusive::list_member_hook<
    intrusive::tag< wait_tag >,
    intrusive::link_mode<
        intrusive::auto_unlink
    >
>                                 wait_hook;
// declaration of the functor that converts between
// the context class and the wait-hook
struct wait_functor {
    // required types
    using hook_type = wait_hook;
    using hook_ptr = hook_type *;
    using const_hook_ptr = const hook_type *;
    using value_type = context;
    using pointer = value_type *;
    using const_pointer = const value_type *;

    // required static functions
    static hook_ptr to_hook_ptr( value_type &value);
    static const_hook_ptr to_hook_ptr( value_type const& value);
    static pointer to_value_ptr( hook_ptr n);
    static const_pointer to_value_ptr( const_hook_ptr n);
};

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
public:
    typedef intrusive::list<
                context,
                intrusive::function_hook< detail::wait_functor >,
                intrusive::constant_time_size< false >
            >   wait_queue_t;

private:
    friend class dispatcher_context;
    friend class main_context;
    template< typename Fn, typename ... Arg > friend class worker_context;
    friend class scheduler;

    struct fss_data {
        void                                *   vp{ nullptr };
        detail::fss_cleanup_function::ptr_t     cleanup_function{};

        fss_data() noexcept = default;

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
    wait_queue_t                                        wait_queue_{};
public:
    detail::wait_hook                                   wait_hook_{};
#if ! defined(BOOST_FIBERS_NO_ATOMICS)
    std::atomic< std::intptr_t >                        twstatus{ 0 };
#endif
private:
    scheduler                                       *   scheduler_{ nullptr };
    fss_data_t                                          fss_data_{};
    detail::sleep_hook                                  sleep_hook_{};
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

    friend bool
    operator==( context const& lhs, context const& rhs) noexcept {
        return & lhs == & rhs;
    }

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
                     detail::spinlock_lock &) noexcept;

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

    bool wait_is_linked() const noexcept;

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

    template< typename List >
    void wait_link( List & lst) noexcept {
        static_assert( std::is_same< typename List::value_traits::hook_type, detail::wait_hook >::value, "not a wait-queue");
        BOOST_ASSERT( ! wait_is_linked() );
        lst.push_back( * this);
    }

    void worker_unlink() noexcept;

    void ready_unlink() noexcept;

    void sleep_unlink() noexcept;

    void wait_unlink() noexcept;

    void detach() noexcept;

    void attach( context *) noexcept;

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
};

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
                    boost::context::preallocated const& palloc, StackAlloc && salloc,
                    Fn && fn, Arg ... arg) :
            context{ 1, type::worker_context, policy },
            fn_( std::forward< Fn >( fn) ),
            arg_( std::forward< Arg >( arg) ... ) {
        c_ = boost::context::fiber{ std::allocator_arg, palloc, std::forward< StackAlloc >( salloc),
                                    std::bind( & worker_context::run_, this, std::placeholders::_1) };
#if (defined(BOOST_USE_UCONTEXT)||defined(BOOST_USE_WINFIB))
        c_ = std::move( c_).resume();
#endif
    }
};


template< typename StackAlloc, typename Fn, typename ... Arg >
static intrusive_ptr< context > make_worker_context( launch policy,
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
                boost::context::preallocated{ storage, size, sctx },
                std::forward< StackAlloc >( salloc),
                std::forward< Fn >( fn),
                std::forward< Arg >( arg) ... } };
}

namespace detail {

inline
wait_functor::hook_ptr wait_functor::to_hook_ptr( wait_functor::value_type & value) {
    return & value.wait_hook_;
}

inline
wait_functor::const_hook_ptr wait_functor::to_hook_ptr( wait_functor::value_type const& value) {
    return & value.wait_hook_;
}

inline
wait_functor::pointer wait_functor::to_value_ptr( wait_functor::hook_ptr n) {
    return intrusive::get_parent_from_member< context >( n, & context::wait_hook_);
}

inline
wait_functor::const_pointer wait_functor::to_value_ptr( wait_functor::const_hook_ptr n) {
    return intrusive::get_parent_from_member< context >( n, & context::wait_hook_);
}

}}}

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