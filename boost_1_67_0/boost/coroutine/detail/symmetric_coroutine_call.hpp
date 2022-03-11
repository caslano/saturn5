
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
+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
*/