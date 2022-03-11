
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
        impl_{ make_worker_context( policy, std::forward< StackAllocator >( salloc), std::forward< Fn >( fn), std::forward< Arg >( arg) ... ) } {
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