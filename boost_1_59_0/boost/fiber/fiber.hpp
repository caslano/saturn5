
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIBER_H
#define BOOST_FIBERS_FIBER_H

#include <algorithm>
#include <exception>
#include <memory>
#include <utility>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/predef.h>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/disable_overload.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/fixedsize_stack.hpp>
#include <boost/fiber/policy.hpp>
#include <boost/fiber/properties.hpp>
#include <boost/fiber/segmented_stack.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL fiber {
private:
    friend class context;

    using ptr_t = intrusive_ptr<context>;

    ptr_t       impl_{};

    void start_() noexcept;

public:
    using id = context::id;

    fiber() = default;

    template< typename Fn,
              typename ... Arg,
              typename = detail::disable_overload< fiber, Fn >,
              typename = detail::disable_overload< launch, Fn >,
              typename = detail::disable_overload< std::allocator_arg_t, Fn >
    >
#if BOOST_COMP_GNUC < 50000000
    explicit fiber( Fn && fn, Arg && ... arg) :
#else
    fiber( Fn && fn, Arg ... arg) :
#endif
        fiber{ launch::post,
               std::allocator_arg, default_stack(),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename Fn,
              typename ... Arg,
              typename = detail::disable_overload< fiber, Fn >
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( launch policy, Fn && fn, Arg && ... arg) :
#else
    fiber( launch policy, Fn && fn, Arg ... arg) :
#endif
        fiber{ policy,
               std::allocator_arg, default_stack(),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename StackAllocator,
              typename Fn,
              typename ... Arg
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg && ... arg) :
#else
    fiber( std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg ... arg) :
#endif
        fiber{ launch::post,
               std::allocator_arg, std::forward< StackAllocator >( salloc),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename StackAllocator,
              typename Fn,
              typename ... Arg
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( launch policy, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg && ... arg) :
#else
    fiber( launch policy, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg ... arg) :
#endif
        fiber{ policy,
               static_cast<fiber_properties*>(nullptr),
               std::allocator_arg, std::forward< StackAllocator >( salloc),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename Fn,
              typename ... Arg,
              typename = detail::disable_overload< fiber, Fn >,
              typename = detail::disable_overload< launch, Fn >,
              typename = detail::disable_overload< std::allocator_arg_t, Fn >
    >
#if BOOST_COMP_GNUC < 50000000
    explicit fiber( fiber_properties* properties, Fn && fn, Arg && ... arg) :
#else
    fiber( fiber_properties* properties, Fn && fn, Arg ... arg) :
#endif
        fiber{ launch::post,
               properties,
               std::allocator_arg, default_stack(),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename Fn,
              typename ... Arg,
              typename = detail::disable_overload< fiber, Fn >
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( launch policy, fiber_properties* properties, Fn && fn, Arg && ... arg) :
#else
    fiber( launch policy, fiber_properties* properties, Fn && fn, Arg ... arg) :
#endif
        fiber{ policy,
               properties,
               std::allocator_arg, default_stack(),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename StackAllocator,
              typename Fn,
              typename ... Arg
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( fiber_properties* properties, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg && ... arg) :
#else
    fiber( fiber_properties* properties, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg ... arg) :
#endif
        fiber{ launch::post,
               properties,
               std::allocator_arg, std::forward< StackAllocator >( salloc),
               std::forward< Fn >( fn), std::forward< Arg >( arg) ... } {
    }

    template< typename StackAllocator,
              typename Fn,
              typename ... Arg
    >
#if BOOST_COMP_GNUC < 50000000
    fiber( launch policy, fiber_properties* properties, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg && ... arg) :
#else
    fiber( launch policy, fiber_properties* properties, std::allocator_arg_t, StackAllocator && salloc, Fn && fn, Arg ... arg) :
#endif
        impl_{ make_worker_context_with_properties( policy, properties, std::forward< StackAllocator >( salloc), std::forward< Fn >( fn), std::forward< Arg >( arg) ... ) } {
        start_();
    }

    ~fiber() {
        if ( joinable() ) {
            std::terminate();
        }
    }

    fiber( fiber const&) = delete;
    fiber & operator=( fiber const&) = delete;

    fiber( fiber && other) noexcept :
        impl_{} {
        swap( other);
    }

    fiber & operator=( fiber && other) noexcept {
        if ( joinable() ) {
            std::terminate();
        }
        if ( BOOST_UNLIKELY( this == & other) ) {
            return * this;
        }
        impl_.swap( other.impl_);
        return * this;
    }

    void swap( fiber & other) noexcept {
        impl_.swap( other.impl_);
    }

    id get_id() const noexcept {
        return impl_ ? impl_->get_id() : id();
    }

    bool joinable() const noexcept {
        return nullptr != impl_;
    }

    void join();

    void detach();

    template< typename PROPS >
    PROPS & properties() {
        auto props = impl_->get_properties();
        BOOST_ASSERT_MSG( props, "fiber::properties not set");
        return dynamic_cast< PROPS & >( * props );
    }
};

inline
bool operator<( fiber const& l, fiber const& r) noexcept {
    return l.get_id() < r.get_id();
}

inline
void swap( fiber & l, fiber & r) noexcept {
    return l.swap( r);
}

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIBER_H

/* fiber.hpp
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
*/