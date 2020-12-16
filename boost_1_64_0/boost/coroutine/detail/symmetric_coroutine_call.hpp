
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
xHr0JfxPbezW98XuODplRxiX0r/0TAqcH9VFjnE9HTFZXFi7fTRsbu+yjvSmPMx8zryBX3vWODq2KGwfIe8cWUWOcLl4uVYdjk68LR89V42v4bjhd9Dtzu8jBhqO11d+HKyjzMAtGTj9pSi4Tx9Upye/7B0hp4fptHmvGvy/qOPJ5qaxmvcWfEvfdk3G/8F7IO45T9sf1MSuwYW0z3O0zo8j5Kj0TEE1h/JfwW5zUWqK2B5Fq+P/t4eZL5rtuy0R9AOuEvPDqtG07+IEa8EfsckJ+fOwDGvMP+ILPvKFZ1ddGORuOIK/xsGLqvD3mFzo4BC6yLytvhnui2kmDxUwr8X57us4fIt9Pg3Eyo4X+LD+VpFXVxK31eiiC/hSvhBbuu6PeDlrEg3+tOfTFS/ClJ+D7wNxTX+1rsSb1O354636N1TfY+JoKMeerC2uv3B/572vVaSdWqmPLqe3nreuc88Jcbw80E1yZ/5RNhE3q9vGsW0GffKaGE6JVA+m2/arAY1+iAZvpw803rIH6d94MULLTawLJ9gjBse0Umd7Qw6acFxOulW8fcBP/D6cz8apHXSmATZeKQf0rMvY+6Wv+XmGnOQynE4jtLCu2eQkXFY3eHmqWsZHcDsOfm6gvf7ERx+ho8Xf1hQ1M/OXthi2NKMd+eAuY+zNjwuXwVN+3609zuc+9HOPtmBqiCbE8a3VS9h/YW9+LUd6pqv4+8TcuV++KfI+dYWDzn/5Vvm3n+vgRKES5pNOe+oALej3r9mviJ9HGvAdPy/KZoPdYlg9LV+9IMeT71aFFePp99/QeRX4Z3PrN+oGTTxvHZsf+h38MCdt1Qkf+BT/laNJ5e6prunBWRZnuMdCOXAJn2n6cPpZKe+JWfP/cC9+ch2t3Q6O6us3b/L9AeZc/1cXpv9H6VennO9UK/oenp5j7m/Tnxn8ZbPzyuKo59RVYuQXn/LxYL+O+1+jddG6ar20Plp/rc3j6m/irE9/9VT71LPUutoH+yQO4S510nbN2HNVgJv2YpSGQXvw8qc0CL34vBr7IBqrxhE+AY9rt/XeylCYeIp+gsEzGkaq1+vvhfYm1eRzC3B88OyN6jFqJzd8pP5Oxz902F47PFTiMP7Z55k320MHb+rRJxXV7xJq00pV8AWOjZhDl7+NjwfRYu6VrzYdMRBOWfcY+Vu2+5AdjbljWB0qqFvB8II4sW+QR9Ci909iM/79oWuH5LEHQssfYFpdmgwO1ukTUiOGo3xm+zHrfheHjBF/qlvs6kj/slEXfjV/pHdg9sv9XmRz99qrfawd0A5pBUvqi3ahVlorq5XXLtEqa9W1QtprD+H336k92R/RoRYMhZ83leOfM2iiW9Trv7Yv4SQbwpDWV9BpNMrYPvaADZWDFRKnPdX+MmiIz3HO1Xjvcfvq2WoRfx2wmq74hC8cob2HwVOYH/0WO9Ibg5PVHOnJkeK2ZI/Q6f06edvD46H0gjqlGqq1WFrybfVBcXVU3lV4FfxJYxNtyHT4rQ9lzEWpCPVsnJZ/CX/tDEtej+SgsKANbttsnt+gV1Mj5bBypXL+DrgpTq7aSE2used/SufT9ckzaTz2b/6NGuGl7q8Wv+0T12bIi5JpSrG49cKc9/E+SscDc4McyXroIP06Kgd9O0INLMK7dMbCJ5fTj+Oa4eYazhODFdW6R/DnC56hMWDk4XvgEhvseN5+u/F4uiF99KF5r4h3k9Up9sEPc7QNXjSOo0EeZPvP8L161g3D1PMWyvlpkh9o3TuHwIHleChkvWcu/MqrZmNvUWYFeak9seHXnM+/Au39dUF9ShRTf5Rbw9E/tcTdJfRRPzvBvlm4+sXesKIm7M9Wvyo=
*/