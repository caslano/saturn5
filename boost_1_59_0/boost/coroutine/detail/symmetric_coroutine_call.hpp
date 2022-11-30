
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_CALL_H
#define BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_CALL_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

#include <boost/coroutine/attributes.hpp>
#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/preallocated.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_impl.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_object.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_yield.hpp>
#include <boost/coroutine/stack_allocator.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Arg >
class symmetric_coroutine_call
{
private:
    template< typename X >
    friend class symmetric_coroutine_yield;

    typedef symmetric_coroutine_impl< Arg >   impl_type;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_call)

    struct dummy {};

    impl_type       *   impl_;

public:
    typedef Arg                                value_type;
    typedef symmetric_coroutine_yield< Arg >   yield_type;

    symmetric_coroutine_call() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( yield_type &);

    explicit symmetric_coroutine_call( coroutine_fn fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, coroutine_fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< coroutine_fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename StackAllocator >
    explicit symmetric_coroutine_call( coroutine_fn fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, coroutine_fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< coroutine_fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
# endif
    template< typename Fn >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< Fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< Fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
#else
    template< typename Fn >
    explicit symmetric_coroutine_call( Fn fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( Fn fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
#endif

    ~symmetric_coroutine_call()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    symmetric_coroutine_call( BOOST_RV_REF( symmetric_coroutine_call) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    symmetric_coroutine_call & operator=( BOOST_RV_REF( symmetric_coroutine_call) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_call tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete() || impl_->is_running(); }

    void swap( symmetric_coroutine_call & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    symmetric_coroutine_call & operator()( Arg arg) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( * this);

        impl_->resume( arg);
        return * this;
    }
};

template< typename Arg >
class symmetric_coroutine_call< Arg & >
{
private:
    template< typename X >
    friend class symmetric_coroutine_yield;

    typedef symmetric_coroutine_impl< Arg & >     impl_type;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_call)

    struct dummy {};

    impl_type       *   impl_;

public:
    typedef Arg                                    value_type;
    typedef symmetric_coroutine_yield< Arg & >     yield_type;

    symmetric_coroutine_call() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( yield_type &);

    explicit symmetric_coroutine_call( coroutine_fn fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, coroutine_fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< coroutine_fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename StackAllocator >
    explicit symmetric_coroutine_call( coroutine_fn fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, coroutine_fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< coroutine_fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
# endif
    template< typename Fn >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< Fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< Fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
#else
    template< typename Fn >
    explicit symmetric_coroutine_call( Fn fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( Fn fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< Arg &, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
#endif

    ~symmetric_coroutine_call()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    symmetric_coroutine_call( BOOST_RV_REF( symmetric_coroutine_call) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    symmetric_coroutine_call & operator=( BOOST_RV_REF( symmetric_coroutine_call) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_call tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete() || impl_->is_running(); }

    void swap( symmetric_coroutine_call & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    symmetric_coroutine_call & operator()( Arg & arg) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( * this);

        impl_->resume( arg);
        return * this;
    }
};

template<>
class symmetric_coroutine_call< void >
{
private:
    template< typename X >
    friend class symmetric_coroutine_yield;

    typedef symmetric_coroutine_impl< void >        impl_type;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_call)

    struct dummy {};

    impl_type       *   impl_;

public:
    typedef void                                     value_type;
    typedef symmetric_coroutine_yield< void >        yield_type;

    symmetric_coroutine_call() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( yield_type &);

    explicit symmetric_coroutine_call( coroutine_fn fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, coroutine_fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< coroutine_fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename StackAllocator >
    explicit symmetric_coroutine_call( coroutine_fn fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, coroutine_fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< coroutine_fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
# endif
    template< typename Fn >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< Fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    boost::forward< Fn >( fn), attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
#else
    template< typename Fn >
    explicit symmetric_coroutine_call( Fn fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( Fn fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs = attributes(),
                                       stack_allocator stack_alloc = stack_allocator() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, Fn, stack_allocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }

    template< typename Fn, typename StackAllocator >
    explicit symmetric_coroutine_call( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs,
                                       StackAllocator stack_alloc) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef symmetric_coroutine_object< void, Fn, StackAllocator > object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                    fn, attrs, preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
    }
#endif

    ~symmetric_coroutine_call()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    inline symmetric_coroutine_call( BOOST_RV_REF( symmetric_coroutine_call) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    inline symmetric_coroutine_call & operator=( BOOST_RV_REF( symmetric_coroutine_call) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_call tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    inline bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete() || impl_->is_running(); }

    inline void swap( symmetric_coroutine_call & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    inline symmetric_coroutine_call & operator()() BOOST_NOEXCEPT
    {
        BOOST_ASSERT( * this);

        impl_->resume();
        return * this;
    }
};

template< typename Arg >
void swap( symmetric_coroutine_call< Arg > & l,
           symmetric_coroutine_call< Arg > & r)
{ l.swap( r); }

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_CALL_H

/* symmetric_coroutine_call.hpp
3pEV0yL1nTmJHD6/cpgw/rMnPOCsgFVFFlOXJOgxrtKbkUD8eR2EYEmIT5ufvLX6pi5xk97+QvE9aJAAgXMBwsPXq67tmtr4rHITFiKK+su12IDhm6v0QcSEXj3Z0bmtRY4+A/8w4NtlStrV3ePhD62drGhZ4oIWM3UutiFIQ5h/ARXirRvb5JeAQyHFevCFjZDIyZoxMBgjvJFrLrresGWJQB8cKNwVH53jwIy0aOIaEn1is5J5PTYSYhjnn3DJMXzgSuv3Nh0VnvnQkFjEx8PM0vbGGaePWRaSJZ4lZTBY0oW7R1P450I2SjSVjFu12cFJBisCBbafDLaAzyT3rpqM4L7WAxznvCls9IxtNhMJoX2feJlFWEEj7W3E3YiJnfgZg7qDpPuYInGNXYvweAE7CWZtgVU2qVtxF4E6Ev8XxSA33OT1oCX0dQcpugpVcsr8N1hI7noaZHzAUbSxwWqXmjUzOuaUeNJ8fh0yr01qexX51EajXJPZcjo4P6vUXT5yTaU0hBcEdyRX2YY7WKIFpVsVf62vbOmI1hVCPwzLK9dRlTfW9bkb3WgGsj/J2v4kW+nhQpACuHTlqTCWdD7VLmRorF1hBKG93zInJqt+QrM2kkFLwt9j7V/AOFYYUn8cm32k3omfvxMfP0B2Wi3ld1X8g5Yy7S2S9/IdaF/wcXYLz65WWWrAsA3ltn62Qb/gkxjhgNAN+0RNITJyeYIS3Nc7gVeNdjDesiqz8pZYWObipl9MlEiglcHBjg6nrY7AEZgj6I1FNJOT5plrYHkVPoOBBIaJFheqOoIjqDHwdO8giIsw17AOCJ+l3Dbs+b0CZHQkmNlep2vNWQ1CJH2TBV6CQAoGIYv9gYpPTFHeM+esgCdCIB4KpSWk7CSB0vC7uySdwfMIQTdlP32gUKkZRC3Zp0KvuP0jsb7nmXa6JqPpti3Q8m9ZbPqzWEOMdsEiAuuQ6sesGtNCi4uHe6QU7YLwEUAMV60lYfhLhjCujqb3lcfDkuQS8F/23+GVpuDi6BvaMT4f4Rt8mKPxPWYLjVtOavDY2xSkx0NDIdcsmUteRLgRCxeQ4lz8FxQfQN+DxhMd2WFX4IDJlbsytsti6OJPRZkDRktF9VzH3rQysIfu/hAI+jFBMEvZX9uvLyYc87vTiKOaanXp6YlHGF0//tOAzl/grI3/Grb7y3WBkukuC0TJPso3UG8kc7f3z1jew9/V3zRigYtOFS+uOFNLWudkdIhUpL11MI1Ng/FHE1peim3HDjQrmobKWySmwZtdYoDYizqJWvQU1NQDnTUOJ41uciRZmo0LPmgibooEK67CQoACOmjTs6uzEiEjgsxmc8LksMS7KDy1jCzRgBtN40rLyYvaQtzFvjBwrhvSkkBOYbNG/96sxXjVIrH0F6Imiti8HQhjsfdyQv+29eNU2ZPXBgYFODlJJqvICcYgG83YiHyyGkXHX93roUo+bOdjkQXbl40guM1l4lvCRrqHOW0ujkBitFSy18xhY7Q9uaF1i0v8mRPO9HmfwFrWJUc9q5n+9IelkALyVPt5u0ZES36XEV+kZrUKYIXcR15N74Qaab7XqDZYp2xqltWCDzZVXlI5rAeKidPuANd/KQTRig6C1dR3KKOuE8TzoKoLzQm0DUNxmNsb31s9vOamhAMCr07vGHmW2EcEqXFMwpqxPyr06hzVc1GUWhENvhS6Nvi9le22Hh8Z4BeqsLkq9O5aTbtZMOAzFQjHnecG07QIxWoH8i3mUbuoPKc0FUo13E9P6w0walhqX5WWUeYzlnX9og59MBW+Si6ev8lMMr+kSKE2n7bOxxzj7eDyBhl6c+aD5To9sA5M7ylXV7a/lIfoHUkKYMD/1a6MgRIl5K2qeHwtLESCcvkoFxAxOMg1curs5sj1BltsNABZL5L8MpEU8Oqfq3GeyomdTTFSFujGj86SLBqPirGWzKVZbcUzZy1PnhtwT23uKLheE2pdDfmomnLgSJrv/XjfGNr/vNZtXqGlb9FL91JK93pHseO5Cn7jh24356k5+8DSLReYW4DV4mJ8F0+toKXHHE69msFL1R6zlKyPcj290nNOvmWGop7bUndu3Pw+Dzl8c38+BQ8sF36T7vBTEnAEIoFYsHJS4uEvxgzMS3EzH8TrGCDpCOCllYvWKaNEMvXPTTASKhOVgygiLR+cYZFabZ1Qx8iGkBglgwh1J92BBkXMZ7m9GSDtzrEDQdq5IlQIsbAZrip2pODbMSBSrKcp9q8dn/jlJ0K3gwwh8rz7OYw7K2gJdhthEMGudJhRCK3TWT6uPbJpq9mBXyShzzz5nVxIS4pdxtOsdx2A64vT0dGEuds0ruJmkkCqShF+PoYEJFjgaVKVzYOD/E2LEy1qs+LeQnLQgPqip2UxWkiRDwbHg4Segs1KZLz1ZPRCnROSa+G2PWCcPg2SvXuZZqiW8+Ra5zE+LtgQz5c1XdxAjp6eMXa9rDSmKD375HXNIGDMDbQtgpwrhPccZ6Q5aPMOrIuMVCxdOvlWkwniXCYGE9uOlb6kfa5SlRiJIhdeV69NcgrsDHI0hcrhjxeUm2JEL+i5pN0vacjget0VlQuqA8miEAUmcJgc4tsi/xjdd5oP9L66u/tvuKkn0PwRpA526CjRp9fRjvI82D6SsMtNDtQrQOf8l3PqLVZXVmyHil24HtUGTPH2AEQzyTjGnDc2tSuoPBYvxag2Q1uYAu1yMDG/wqvhYmMhKSRX2kVVD/Cvge9N7X/h5AvDwwjTBxj7PKd/RXzfCpch8HaVGBkY5RAw9kgf7a6DUTHV3I0HRdpZ9DyAOpHaN7BxG4pdEZnOEXF7f7aVrlSpn8e39hSlOqnyGLZSqs8Naf86z8NUj0FzFo/mp5vU4I6kKFS/Deau3v5OuYBSOBye9aJ6K9u4et6YJdetcpRBPixMKpUMVmj3mmGeBfYGUdXOuuL/Vb0SXLTQ+mOBQOpfUI4vdtyaekqeoJbbERQKatwKeQmbBeMlT4De2nJKFIoxFE+lXcng+b3tMYuDFtNPWN4FOaXRa2xqi+2Pj1K2R4mOa2YT+PXFhyZhLxMsHM8m/mHvLO8bMO9BIzYP5ezEz4QSQIw6Sh4pQ/0U+o7EogBzgLeNCMIiKeGv5K9RLh3PVK20rxse+Hvg1oBvLArOkEEY5y9PtKAQ/6JRQ8Wt9Cf934XhTUvWGvwncF1YmaArSWYbsqAhMu5MKAbjW2PrINB7sGWe1EGS43DxMXAvBy0Usf3r8DBMzPKbL5M1DeAg1d8KitvqIKshZ9FPwob0+dm7P67AHX3whD4l/pJCo30D/X/8wB/7dpu3YObx87//IYBC1B8gtKyhZtTQPSqvJKu9nFpDcAsJqQYjxsORROSA3a3cae6SJcxvez+7foemJrji6ckEX5F5TinxZPOppKMQQSVzAEeySi6IpfOKkfpuqozhQ4ZP/UTGRCmTojylA/Uih/xT4A+bCH9KM1f/B92OKTJtbOJ2v+XwKGDRf9sTSh+dmdiGcDSMavPR0BHcUBcCOkjHc84qHhmXmc0LkZyDrv1uAS3RaOjWqYu0PMh4/w9LjLgHpT1qegZ8HG1aZ+C644XYG7+M5TqXnCRJmexUS9eVifXGx7V+y/6TvhFGJ6Rj7M8ywVWzoOSq1fVfmNDXtZds2K8KHj38DTF5obO3aHMrq/hRBfj9NLXqXBQk0WMf4tQKn94HUJypua9+beB5qRXZFKrynBXChFhx7/G0Sf+IAdg1IzqO9ld4TS4xE1AYeP3BvRemupknIfxquRJ74deoiio9Qc4L6vQmk4geXbSZM5aOgPmyGbrn8kbRep6MixY6ApVhLXWaj3It5lMjb0plwbsbEGAUD7nPj4+B5ujBXkPtRvNc0NGOthe1U63Br3t8fmb3wL/Bd3ROxmg8HMsmc9eNuBV2ZZWzYtw9aFgVdgUngk9u/mwWuPRs4mGhvzquICFtkU/fGbE6B7QJW/c2toySWmZjaVEME+NRm2yQRZCLRiGvhj3vlr4RskbI9i0bQcrtnE49kuTMJrV/WXG91c2t99+lV2QX+2h2WJHcXVLPBivnQ4YlNwfPQTFI1rZJpJoUHkKMTc2QnMaS84Vp7lW7qnDhlXcTlhU+1d6hFyWdhtxyUrbO/X25gRfwFpWzN6z7cddXyp8fAWOgPVP87hRbSV4dMB1zjnI7OuiW503DnfNUCibdpKVocOAXSMLl41NpCCSWllXQXxrnmaH96fac44nmVOtq7XDAQhOjc59/2cj1lwnl4fvtbWg1u62PsL6u/+M5e7zdI2DhVEvOiWAntLnTivUw5EejBUQdYVf2LTurydAMex+q2yYeDFfR1OOI2XE+FMAfJNLr7VpiEs7QlwIq0AXVb65Cua+g/zkPHst8uERrimyVXcGRPr7w+0UksBSs+c7oBcjPoxrhHTwLTWKvxZ9FrIItt82u/xzdnbocQwCnx/pX9cFZWp1WWtoSMIO4qsrAoOwPivtGow7U/qMK/iQrFDGwAfNt+TJWKBrZKNNlloTKgik7Xkke2OGnYfjQ8OzgDSZMyzPJsiyICav0bphG809gT0mKov6SzKjCo1akoT6j2kx6NZc04k/Vl09fIlAsbySZSuVoVE9nbI9Ruu6LpkZSWLJ1SDe1MVOiyxGj6vvEE5PaH02Og2R3b0Uqu27Nwtx5FwTODAjFg03+7eYoNyXupsnTycEvhBzkARXxqNgvO8iawXaV8iH8Ef/4ePwfCyMn6ucnMrfGEPv76G+888qo1PfaKfFdvLyun5GmWODdPLD7X+Hccm4/CvnB7nGhqnrk0Hcx6IugNJMJku45/SE1temcd6wWohQB4NM7YDvzcSvYFvA93Fv0iGu3Fa/MCQGDygPa0htY/J9fW2lDDKiwUc2sMp00VrwNrTZmZieTKSIFITExH2JhbcaNVoIjnxqrq3yXfCXDAi6gWPLeQPuJflLb/WgNlMHoCBtthC5btXXQvKlIC/SKyfFHaMW42+Wthkkl8IXD9bTxFiYNGn3TGu+xPA9tJNqignJAIKsMpdfRK/oNNmFdUGAaZFcKQwjjz5T05YfuKctWx6+pw1s+PQ8rFv76yw03iyErawfdvW9aGx+z2vgJV2hDmswEhiw3BluXTCQWf8GycnIlbtxlkH1Nzs27nwothUFspyNhAzGEoAeDWNVzTj9GBIDF3oQQgOaiN8tKkZD79NpaHyr33SHrLNfwOxI4TmmoGeOhsQOIwQPm/0m4kqQQKNNVaNOV58azFjtZb4zVYFixb2HbOsd/VQkpapdx/zbLofg95E27M7ZalqyfVvTz/RKckzwc/VMnvo3Lrln23Wf27XonAXmAZ8AUxaRDR/hjQCqGkkBzcXcV9BOaScckZaIzTkM9N0aYhf3LEhEed1oHJdsXtZFPv+ae34wH+ww9WDPxzCgw+wOGfMeKBnbZBGsjObZ/dZjmDNvBRuwY09jlziQBVkfLfZ97GwEhnEhpXtRHLEvwwHbcTbCwYkMrgGDdq1ydFin0Tmvd+8Igv0bCrapEuqz6uWrI/Be/COupYF71kNlZ9eof60p99xR5eceB2J7NC1VtAuyQCbdfetH361mbdM1tyWqrWqEaIaMZhXTApMiagj9nIv+s+Ehoe7o+8XLbo6MjZBrN1SDqMRC4SQ7icWY5PMOfZNEg+kGnYfJgy3U85f2EyJQ/xkwsqdk6DqXAiNzrQhreGJ6f4YUP7ObbVLhI5puwTiyCk4QRaxHVqon+eaZy4ay7olVeMM2pwDAvAOsrez4ROsYz1jc1CmA+znTlAy48XwUYv8qYP9qy/c6PPkcEeo5W0bNVXAJ3KXs/qYCSbIrvnBT90OovTsq/wxtXEAU287IHEN1mG3/pnsch9kBfCKMFhuZmlV2oBH1d43QNrxh/Kg8IuCwxsz0w6pW1hZ2ATvM3PvtQfP4A7cANo1uh/b/3XZ0qWus/kz/KlVq2KzKlyaddHa3MQPTCI2KuUM3bHroVVkehnazzgfLIblYEmsiCgQJME53M2k5gh8/FqkLUrC5Sq0jCkPmI7iYINfc0XVOMfvbKziHHg0X3SL8Uy+qlj0pGv3N30PATZMK4aKrikrqrMIKSWClKmVEX06lLmQ2TqNNi04ghI+ulkbs1YcuuAxVdukSilm7pfaLlRnc+RKrCyz41U+S5vhVkzp9eFuLG10saxhDaoXH+Qv0cl1/bVWx80/2N6CT8fJsfK3UDiVN2z+47wCPAvH0Fi5vobMEajPIfH5M+uVZ1Oq6pj31eOZVZUry/YX8tyw78Ljh4KVsgFNn/Ftn360+U6xZUZQEqX3+tqWCMIr2JK3CNI241866C4/QowqiWT36fyMvngQo60TflpdNzfCsYfanumD9f1Nd1gH0B+o4tQmX/MnnoxW/oteNH6DKH0NCuF+h5he//2Zv3IVzTiuOc/Hw1tOocgCjTzS3PxJ1UeiPAfOpWNZauyfctoevjILwzRCO0Urz3y7ksVL/24BIoQzIHFu1lrDkOEYJBQNdjsXtDGe/fYgZmkqB2SJLPWbTqAyOxTpJ5d8LcdK1zpjY8phCYIzFGHv70870hl/e3KtF7RYkPh6dCF2R1y4LyO/mDdfRjm4B5/HNZJSmZ89s8Nxc6fjuJDHz8brcwuhNo84TtIRWKYWEvFQ6VkAZnEDv0DPNRvNrfv/LSLuXAZRiZRKdWhqE3cJOcevAEZOZtHYSs+YvcB1nUDkXNoKtVPr534dyqOx3ShP5btzcEhzkNvKuvjtV4/6djxkjUYhvWL8VgQLfQkgUTX90suBMCTqlPDkpz4ZeBiW6VTHbREul2Ii7RvBmdmhV6SPBUOMfjNsqNWGMks3arzNJW8R8b/AxfQf76SXBXdNh2MCuKLHH1eMNfLfgduGLkUiyGEc50lwWVjq2UbhCHhEqygmQE/Tco0oUg/4K7KyH+8EjfmT7pKhFGOv/jod4XPlERBa/6Fw5T1QhZPpuvVJ5DWS0z/Q4LPdj2w4/pnZJOvbmmtP/XMUamynk/Rj8OXMWB3VbULuOAkVE+Zv/2aUqzTYHYTkB9/Z+K6o3Zc0IiX0EyyR/kmJTBwHdfuJd+uce4P5hLMovSk5kMyjcP8J09eV1BoF0muqGn5OvjplapxkVL3081Sh/FdgmHIG8Ezno87frPlAWqxMDn6AQ2lrsDybBd7O8MLlLZ9n6jk62cA/SejG+qxgUnTRiVfRBG6lkNH6dETQnVxLwLsGBD+92DMnUjiDcKndTtazMkYuqb8X7NUJ/8ryi7dV8lflpqO2PfXzTwa/GgUdUvHQ8d2vx8kWlDzvtZ7fH3+uspDo+em2+NvOd4OQR6ulzTuzTr6fxaXu9LQjd9McQosIP5cx+/RB1K0Ly+HiKqL3rWkIwUc1YEx61mI1cm42VCF7TvcRdvrSjzqI/MmpOnKhOq8HusqFsuUut1V0aXY3cUxm1WlZoNY6yvXjWVbNVk1ipx1tbvOhIcO/5Qb8j9d3fMv01xelPcJcCz80gZyxeaj7Pby63G5hIwV/5oe/3WfWo6tJBZW6MvarAKthqxIzliB+z5T7y5+TN7pD3V3XqsLuCEp3Xb3AyyOJUVk0lLppsnLW70JFfbGD5kTHFb
*/