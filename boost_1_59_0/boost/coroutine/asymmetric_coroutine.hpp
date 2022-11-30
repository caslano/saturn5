
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_ASYMMETRIC_COROUTINE_H
#define BOOST_COROUTINES_ASYMMETRIC_COROUTINE_H

#include <cstddef>
#include <iterator>
#include <memory>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

#include <boost/coroutine/attributes.hpp>
#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/parameters.hpp>
#include <boost/coroutine/exceptions.hpp>
#include <boost/coroutine/stack_allocator.hpp>
#include <boost/coroutine/detail/pull_coroutine_impl.hpp>
#include <boost/coroutine/detail/pull_coroutine_object.hpp>
#include <boost/coroutine/detail/pull_coroutine_synthesized.hpp>
#include <boost/coroutine/detail/push_coroutine_impl.hpp>
#include <boost/coroutine/detail/push_coroutine_object.hpp>
#include <boost/coroutine/detail/push_coroutine_synthesized.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename R >
class pull_coroutine;

template< typename Arg >
class push_coroutine
{
private:
    template< typename V, typename X, typename Y, typename Z >
    friend class detail::pull_coroutine_object;

    typedef detail::push_coroutine_impl< Arg >          impl_type;
    typedef detail::push_coroutine_synthesized< Arg >   synth_type;
    typedef detail::parameters< Arg >                   param_type;

    struct dummy {};

    impl_type       *   impl_;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( push_coroutine)

    explicit push_coroutine( detail::synthesized_t::flag_t, impl_type & impl) :
        impl_( & impl)
    { BOOST_ASSERT( impl_); }

public:
    push_coroutine() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( pull_coroutine< Arg > &);

    explicit push_coroutine( coroutine_fn,
                             attributes const& = attributes() );

    template< typename StackAllocator >
    explicit push_coroutine( coroutine_fn,
                             attributes const&,
                             StackAllocator);
# endif
    template< typename Fn >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const&,
                             StackAllocator);
#else
    template< typename Fn >
    explicit push_coroutine( Fn fn,
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( Fn fn,
                             attributes const&,
                             StackAllocator);

    template< typename Fn >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const&,
                             StackAllocator);
#endif

    ~push_coroutine()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    push_coroutine( BOOST_RV_REF( push_coroutine) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    push_coroutine & operator=( BOOST_RV_REF( push_coroutine) other) BOOST_NOEXCEPT
    {
        push_coroutine tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete(); }

    void swap( push_coroutine & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    push_coroutine & operator()( Arg arg)
    {
        BOOST_ASSERT( * this);

        impl_->push( arg);
        return * this;
    }

    class iterator
    {
    private:
       push_coroutine< Arg >    *   c_;

    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        iterator() :
           c_( 0)
        {}

        explicit iterator( push_coroutine< Arg > * c) :
            c_( c)
        {}

        iterator & operator=( Arg a)
        {
            BOOST_ASSERT( c_);
            if ( ! ( * c_)( a) ) c_ = 0;
            return * this;
        }

        bool operator==( iterator const& other) const
        { return other.c_ == c_; }

        bool operator!=( iterator const& other) const
        { return other.c_ != c_; }

        iterator & operator*()
        { return * this; }

        iterator & operator++()
        { return * this; }
    };

    struct const_iterator;
};

template< typename Arg >
class push_coroutine< Arg & >
{
private:
    template< typename V, typename X, typename Y, typename Z >
    friend class detail::pull_coroutine_object;

    typedef detail::push_coroutine_impl< Arg & >          impl_type;
    typedef detail::push_coroutine_synthesized< Arg & >   synth_type;
    typedef detail::parameters< Arg & >                   param_type;

    struct dummy {};

    impl_type       *   impl_;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( push_coroutine)

    explicit push_coroutine( detail::synthesized_t::flag_t, impl_type & impl) :
        impl_( & impl)
    { BOOST_ASSERT( impl_); }

public:
    push_coroutine() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( pull_coroutine< Arg & > &);

    explicit push_coroutine( coroutine_fn,
                             attributes const& = attributes() );

    template< typename StackAllocator >
    explicit push_coroutine( coroutine_fn,
                             attributes const&,
                             StackAllocator);
# endif
    template< typename Fn >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const&,
                             StackAllocator);
#else
    template< typename Fn >
    explicit push_coroutine( Fn,
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( Fn,
                             attributes const&,
                             StackAllocator);

    template< typename Fn >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const&,
                             StackAllocator);
#endif

    ~push_coroutine()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    push_coroutine( BOOST_RV_REF( push_coroutine) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    push_coroutine & operator=( BOOST_RV_REF( push_coroutine) other) BOOST_NOEXCEPT
    {
        push_coroutine tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete(); }

    void swap( push_coroutine & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    push_coroutine & operator()( Arg & arg)
    {
        BOOST_ASSERT( * this);

        impl_->push( arg);
        return * this;
    }

    class iterator
    {
    private:
       push_coroutine< Arg & >  *   c_;

    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        iterator() :
           c_( 0)
        {}

        explicit iterator( push_coroutine< Arg & > * c) :
            c_( c)
        {}

        iterator & operator=( Arg & a)
        {
            BOOST_ASSERT( c_);
            if ( ! ( * c_)( a) ) c_ = 0;
            return * this;
        }

        bool operator==( iterator const& other) const
        { return other.c_ == c_; }

        bool operator!=( iterator const& other) const
        { return other.c_ != c_; }

        iterator & operator*()
        { return * this; }

        iterator & operator++()
        { return * this; }
    };

    struct const_iterator;
};

template<>
class push_coroutine< void >
{
private:
    template< typename V, typename X, typename Y, typename Z >
    friend class detail::pull_coroutine_object;

    typedef detail::push_coroutine_impl< void >          impl_type;
    typedef detail::push_coroutine_synthesized< void >   synth_type;
    typedef detail::parameters< void >                   param_type;

    struct dummy {};

    impl_type       *   impl_;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( push_coroutine)

    explicit push_coroutine( detail::synthesized_t::flag_t, impl_type & impl) :
        impl_( & impl)
    { BOOST_ASSERT( impl_); }

public:
    push_coroutine() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( pull_coroutine< void > &);

    explicit push_coroutine( coroutine_fn,
                             attributes const& = attributes() );

    template< typename StackAllocator >
    explicit push_coroutine( coroutine_fn,
                             attributes const&,
                             StackAllocator);
# endif
    template< typename Fn >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const&,
                             StackAllocator);
#else
    template< typename Fn >
    explicit push_coroutine( Fn,
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( Fn,
                             attributes const&,
                             StackAllocator);

    template< typename Fn >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const& = attributes() );

    template< typename Fn, typename StackAllocator >
    explicit push_coroutine( BOOST_RV_REF( Fn),
                             attributes const&,
                             StackAllocator);
#endif

    ~push_coroutine()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    inline push_coroutine( BOOST_RV_REF( push_coroutine) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    inline push_coroutine & operator=( BOOST_RV_REF( push_coroutine) other) BOOST_NOEXCEPT
    {
        push_coroutine tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    inline bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete(); }

    inline void swap( push_coroutine & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    inline push_coroutine & operator()()
    {
        BOOST_ASSERT( * this);

        impl_->push();
        return * this;
    }

    struct iterator;
    struct const_iterator;
};



template< typename R >
class pull_coroutine
{
private:
    template< typename V, typename X, typename Y, typename Z >
    friend class detail::push_coroutine_object;

    typedef detail::pull_coroutine_impl< R >            impl_type;
    typedef detail::pull_coroutine_synthesized< R >     synth_type;
    typedef detail::parameters< R >                     param_type;

    struct dummy {};

    impl_type       *   impl_;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( pull_coroutine)

    explicit pull_coroutine( detail::synthesized_t::flag_t, impl_type & impl) :
        impl_( & impl)
    { BOOST_ASSERT( impl_); }

public:
    pull_coroutine() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( push_coroutine< R > &);

    explicit pull_coroutine( coroutine_fn fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, coroutine_fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename StackAllocator >
    explicit pull_coroutine( coroutine_fn fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, coroutine_fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
# endif
    template< typename Fn >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, Fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, Fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
#else
    template< typename Fn >
    explicit pull_coroutine( Fn fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, Fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( Fn fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, Fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, Fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R >, R, Fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
#endif

    ~pull_coroutine()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    pull_coroutine( BOOST_RV_REF( pull_coroutine) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    pull_coroutine & operator=( BOOST_RV_REF( pull_coroutine) other) BOOST_NOEXCEPT
    {
        pull_coroutine tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete(); }

    void swap( pull_coroutine & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    pull_coroutine & operator()()
    {
        BOOST_ASSERT( * this);

        impl_->pull();
        return * this;
    }

    R get() const
    {
        BOOST_ASSERT( 0 != impl_);

        return impl_->get();
    }

    class iterator
    {
    private:
        pull_coroutine< R > *   c_;
        R                   *   val_;

        void fetch_()
        {
            BOOST_ASSERT( c_);

            if ( ! ( * c_) )
            {
                c_ = 0;
                val_ = 0;
                return;
            }
            val_ = c_->impl_->get_pointer();
        }

        void increment_()
        {
            BOOST_ASSERT( c_);
            BOOST_ASSERT( * c_);

            ( * c_)();
            fetch_();
        }

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef typename remove_reference< R >::type value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type * pointer;
        typedef value_type & reference;

        typedef pointer   pointer_t;
        typedef reference reference_t;

        iterator() :
            c_( 0), val_( 0)
        {}

        explicit iterator( pull_coroutine< R > * c) :
            c_( c), val_( 0)
        { fetch_(); }

        iterator( iterator const& other) :
            c_( other.c_), val_( other.val_)
        {}

        iterator & operator=( iterator const& other)
        {
            if ( this == & other) return * this;
            c_ = other.c_;
            val_ = other.val_;
            return * this;
        }

        bool operator==( iterator const& other) const
        { return other.c_ == c_ && other.val_ == val_; }

        bool operator!=( iterator const& other) const
        { return other.c_ != c_ || other.val_ != val_; }

        iterator & operator++()
        {
            increment_();
            return * this;
        }

        iterator operator++( int);

        reference_t operator*() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return * val_;
        }

        pointer_t operator->() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return val_;
        }
    };

    class const_iterator
    {
    private:
        pull_coroutine< R > *   c_;
        R                   *   val_;

        void fetch_()
        {
            BOOST_ASSERT( c_);

            if ( ! ( * c_) )
            {
                c_ = 0;
                val_ = 0;
                return;
            }
            val_ = c_->impl_->get_pointer();
        }

        void increment_()
        {
            BOOST_ASSERT( c_);
            BOOST_ASSERT( * c_);

            ( * c_)();
            fetch_();
        }

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef const typename remove_reference< R >::type value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type * pointer;
        typedef value_type & reference;

        typedef pointer   pointer_t;
        typedef reference reference_t;

        const_iterator() :
            c_( 0), val_( 0)
        {}

        explicit const_iterator( pull_coroutine< R > const* c) :
            c_( const_cast< pull_coroutine< R > * >( c) ),
            val_( 0)
        { fetch_(); }

        const_iterator( const_iterator const& other) :
            c_( other.c_), val_( other.val_)
        {}

        const_iterator & operator=( const_iterator const& other)
        {
            if ( this == & other) return * this;
            c_ = other.c_;
            val_ = other.val_;
            return * this;
        }

        bool operator==( const_iterator const& other) const
        { return other.c_ == c_ && other.val_ == val_; }

        bool operator!=( const_iterator const& other) const
        { return other.c_ != c_ || other.val_ != val_; }

        const_iterator & operator++()
        {
            increment_();
            return * this;
        }

        const_iterator operator++( int);

        reference_t operator*() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return * val_;
        }

        pointer_t operator->() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return val_;
        }
    };

    friend class iterator;
    friend class const_iterator;
};

template< typename R >
class pull_coroutine< R & >
{
private:
    template< typename V, typename X, typename Y, typename Z >
    friend class detail::push_coroutine_object;

    typedef detail::pull_coroutine_impl< R & >            impl_type;
    typedef detail::pull_coroutine_synthesized< R & >     synth_type;
    typedef detail::parameters< R & >                     param_type;

    struct dummy {};

    impl_type       *   impl_;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( pull_coroutine)

    explicit pull_coroutine( detail::synthesized_t::flag_t, impl_type & impl) :
        impl_( & impl)
    { BOOST_ASSERT( impl_); }

public:
    pull_coroutine() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( push_coroutine< R & > &);

    explicit pull_coroutine( coroutine_fn fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, coroutine_fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename StackAllocator >
    explicit pull_coroutine( coroutine_fn fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, coroutine_fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
# endif
    template< typename Fn >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, Fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, Fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
#else
    template< typename Fn >
    explicit pull_coroutine( Fn fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, Fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( Fn fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, Fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, Fn, stack_allocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< R & >, R &, Fn, StackAllocator
        >                                                        object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
#endif

    ~pull_coroutine()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    pull_coroutine( BOOST_RV_REF( pull_coroutine) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    pull_coroutine & operator=( BOOST_RV_REF( pull_coroutine) other) BOOST_NOEXCEPT
    {
        pull_coroutine tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete(); }

    void swap( pull_coroutine & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    pull_coroutine & operator()()
    {
        BOOST_ASSERT( * this);

        impl_->pull();
        return * this;
    }

    R & get() const
    { return impl_->get(); }

    class iterator
    {
    private:
        pull_coroutine< R & >   *   c_;
        R                       *   val_;

        void fetch_()
        {
            BOOST_ASSERT( c_);

            if ( ! ( * c_) )
            {
                c_ = 0;
                val_ = 0;
                return;
            }
            val_ = c_->impl_->get_pointer();
        }

        void increment_()
        {
            BOOST_ASSERT( c_);
            BOOST_ASSERT( * c_);

            ( * c_)();
            fetch_();
        }

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef typename remove_reference< R >::type value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type * pointer;
        typedef value_type & reference;

        typedef pointer   pointer_t;
        typedef reference reference_t;

        iterator() :
            c_( 0), val_( 0)
        {}

        explicit iterator( pull_coroutine< R & > * c) :
            c_( c), val_( 0)
        { fetch_(); }

        iterator( iterator const& other) :
            c_( other.c_), val_( other.val_)
        {}

        iterator & operator=( iterator const& other)
        {
            if ( this == & other) return * this;
            c_ = other.c_;
            val_ = other.val_;
            return * this;
        }

        bool operator==( iterator const& other) const
        { return other.c_ == c_ && other.val_ == val_; }

        bool operator!=( iterator const& other) const
        { return other.c_ != c_ || other.val_ != val_; }

        iterator & operator++()
        {
            increment_();
            return * this;
        }

        iterator operator++( int);

        reference_t operator*() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return * val_;
        }

        pointer_t operator->() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return val_;
        }
    };

    class const_iterator
    {
    private:
        pull_coroutine< R & >   *   c_;
        R                       *   val_;

        void fetch_()
        {
            BOOST_ASSERT( c_);

            if ( ! ( * c_) )
            {
                c_ = 0;
                val_ = 0;
                return;
            }
            val_ = c_->impl_->get_pointer();
        }

        void increment_()
        {
            BOOST_ASSERT( c_);
            BOOST_ASSERT( * c_);

            ( * c_)();
            fetch_();
        }

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef const typename remove_reference< R >::type value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type * pointer;
        typedef value_type & reference;

        typedef pointer   pointer_t;
        typedef reference reference_t;

        const_iterator() :
            c_( 0), val_( 0)
        {}

        explicit const_iterator( pull_coroutine< R & > const* c) :
            c_( const_cast< pull_coroutine< R & > * >( c) ),
            val_( 0)
        { fetch_(); }

        const_iterator( const_iterator const& other) :
            c_( other.c_), val_( other.val_)
        {}

        const_iterator & operator=( const_iterator const& other)
        {
            if ( this == & other) return * this;
            c_ = other.c_;
            val_ = other.val_;
            return * this;
        }

        bool operator==( const_iterator const& other) const
        { return other.c_ == c_ && other.val_ == val_; }

        bool operator!=( const_iterator const& other) const
        { return other.c_ != c_ || other.val_ != val_; }

        const_iterator & operator++()
        {
            increment_();
            return * this;
        }

        const_iterator operator++( int);

        reference_t operator*() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return * val_;
        }

        pointer_t operator->() const
        {
            if ( ! val_)
                boost::throw_exception(
                    invalid_result() );
            return val_;
        }
    };

    friend class iterator;
    friend class const_iterator;
};

template<>
class pull_coroutine< void >
{
private:
    template< typename V, typename X, typename Y, typename Z >
    friend class detail::push_coroutine_object;

    typedef detail::pull_coroutine_impl< void >            impl_type;
    typedef detail::pull_coroutine_synthesized< void >     synth_type;
    typedef detail::parameters< void >                     param_type;

    struct dummy {};

    impl_type       *   impl_;

    BOOST_MOVABLE_BUT_NOT_COPYABLE( pull_coroutine)

    explicit pull_coroutine( detail::synthesized_t::flag_t, impl_type & impl) :
        impl_( & impl)
    { BOOST_ASSERT( impl_); }

public:
    pull_coroutine() BOOST_NOEXCEPT :
        impl_( 0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
    typedef void ( * coroutine_fn)( push_coroutine< void > &);

    explicit pull_coroutine( coroutine_fn fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, coroutine_fn, stack_allocator
        >                                       object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename StackAllocator >
    explicit pull_coroutine( coroutine_fn fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, coroutine_fn, StackAllocator
        >                                                                   object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
# endif
    template< typename Fn >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, Fn, stack_allocator
        >                                                       object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, Fn, StackAllocator
        >                                                       object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
#else
    template< typename Fn >
    explicit pull_coroutine( Fn fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, Fn, stack_allocator
        >                                                       object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( Fn fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, Fn, StackAllocator
        >                                                       object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
                             attributes const& attrs = attributes() ) :
        impl_( 0)
    {
        // create a stack-context
        stack_context stack_ctx;
        stack_allocator stack_alloc;
        // allocate the coroutine-stack
        stack_alloc.allocate( stack_ctx, attrs.size);
        BOOST_ASSERT( 0 != stack_ctx.sp);
        // typedef of internal coroutine-type
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, Fn, stack_allocator
        >                                           object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }

    template< typename Fn, typename StackAllocator >
    explicit pull_coroutine( BOOST_RV_REF( Fn) fn,
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
        typedef detail::pull_coroutine_object<
            push_coroutine< void >, void, Fn, StackAllocator
        >                                           object_t;
        // reserve space on top of coroutine-stack for internal coroutine-type
        std::size_t size = stack_ctx.size - sizeof( object_t);
        BOOST_ASSERT( 0 != size);
        void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
        BOOST_ASSERT( 0 != sp);
        // placement new for internal coroutine
        impl_ = new ( sp) object_t(
                fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
        BOOST_ASSERT( impl_);
        impl_->pull();
    }
#endif

    ~pull_coroutine()
    {
        if ( 0 != impl_)
        {
            impl_->destroy();
            impl_ = 0;
        }
    }

    inline pull_coroutine( BOOST_RV_REF( pull_coroutine) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    inline pull_coroutine & operator=( BOOST_RV_REF( pull_coroutine) other) BOOST_NOEXCEPT
    {
        pull_coroutine tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    inline bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_ || impl_->is_complete(); }

    inline void swap( pull_coroutine & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    inline pull_coroutine & operator()()
    {
        BOOST_ASSERT( * this);

        impl_->pull();
        return * this;
    }

    struct iterator;
    struct const_iterator;
};

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
# ifdef BOOST_MSVC
template< typename Arg >
push_coroutine< Arg >::push_coroutine( coroutine_fn fn,
                                       attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, coroutine_fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename StackAllocator >
push_coroutine< Arg >::push_coroutine( coroutine_fn fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, coroutine_fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
push_coroutine< Arg & >::push_coroutine( coroutine_fn fn,
                                         attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, coroutine_fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename StackAllocator >
push_coroutine< Arg & >::push_coroutine( coroutine_fn fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, coroutine_fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

inline push_coroutine< void >::push_coroutine( coroutine_fn fn,
                                               attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, coroutine_fn, stack_allocator
    >                                                               object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename StackAllocator >
push_coroutine< void >::push_coroutine( coroutine_fn fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, coroutine_fn, StackAllocator
    >                                                               object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< coroutine_fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}
# endif
template< typename Arg >
template< typename Fn >
push_coroutine< Arg >::push_coroutine( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, Fn, stack_allocator
    >                                                    object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn, typename StackAllocator >
push_coroutine< Arg >::push_coroutine( BOOST_RV_REF( Fn) fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, Fn, StackAllocator
    >                                                    object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn >
push_coroutine< Arg & >::push_coroutine( BOOST_RV_REF( Fn) fn,
                                         attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, Fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn, typename StackAllocator >
push_coroutine< Arg & >::push_coroutine( BOOST_RV_REF( Fn) fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, Fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Fn >
push_coroutine< void >::push_coroutine( BOOST_RV_REF( Fn) fn,
                                        attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, Fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Fn, typename StackAllocator >
push_coroutine< void >::push_coroutine( BOOST_RV_REF( Fn) fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, Fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            boost::forward< Fn >( fn), attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}
#else
template< typename Arg >
template< typename Fn >
push_coroutine< Arg >::push_coroutine( Fn fn,
                                       attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, Fn, stack_allocator
    >                                                    object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn, typename StackAllocator >
push_coroutine< Arg >::push_coroutine( Fn fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, Fn, StackAllocator
    >                                                    object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn >
push_coroutine< Arg & >::push_coroutine( Fn fn,
                                         attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, Fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn, typename StackAllocator >
push_coroutine< Arg & >::push_coroutine( Fn fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, Fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Fn >
push_coroutine< void >::push_coroutine( Fn fn,
                                        attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, Fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Fn, typename StackAllocator >
push_coroutine< void >::push_coroutine( Fn fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, Fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn >
push_coroutine< Arg >::push_coroutine( BOOST_RV_REF( Fn) fn,
                                       attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, Fn, stack_allocator
    >                                                    object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn, typename StackAllocator >
push_coroutine< Arg >::push_coroutine( BOOST_RV_REF( Fn) fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg >, Arg, Fn, StackAllocator
    >                                                    object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn >
push_coroutine< Arg & >::push_coroutine( BOOST_RV_REF( Fn) fn,
                                         attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, Fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Arg >
template< typename Fn, typename StackAllocator >
push_coroutine< Arg & >::push_coroutine( BOOST_RV_REF( Fn) fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< Arg & >, Arg &, Fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Fn >
push_coroutine< void >::push_coroutine( BOOST_RV_REF( Fn) fn,
                                        attributes const& attrs) :
    impl_( 0)
{
    // create a stack-context
    stack_context stack_ctx;
    stack_allocator stack_alloc;
    // allocate the coroutine-stack
    stack_alloc.allocate( stack_ctx, attrs.size);
    BOOST_ASSERT( 0 != stack_ctx.sp);
    // typedef of internal coroutine-type
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, Fn, stack_allocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}

template< typename Fn, typename StackAllocator >
push_coroutine< void >::push_coroutine( BOOST_RV_REF( Fn) fn,
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
    typedef detail::push_coroutine_object<
        pull_coroutine< void >, void, Fn, StackAllocator
    >                                                            object_t;
    // reserve space on top of coroutine-stack for internal coroutine-type
    std::size_t size = stack_ctx.size - sizeof( object_t);
    BOOST_ASSERT( 0 != size);
    void * sp = static_cast< char * >( stack_ctx.sp) - sizeof( object_t);
    BOOST_ASSERT( 0 != sp);
    // placement new for internal coroutine
    impl_ = new ( sp) object_t(
            fn, attrs, detail::preallocated( sp, size, stack_ctx), stack_alloc); 
    BOOST_ASSERT( impl_);
}
#endif

template< typename R >
void swap( pull_coroutine< R > & l, pull_coroutine< R > & r) BOOST_NOEXCEPT
{ l.swap( r); }

template< typename Arg >
void swap( push_coroutine< Arg > & l, push_coroutine< Arg > & r) BOOST_NOEXCEPT
{ l.swap( r); }

template< typename R >
typename pull_coroutine< R >::iterator
range_begin( pull_coroutine< R > & c)
{ return typename pull_coroutine< R >::iterator( & c); }

template< typename R >
typename pull_coroutine< R >::const_iterator
range_begin( pull_coroutine< R > const& c)
{ return typename pull_coroutine< R >::const_iterator( & c); }

template< typename R >
typename pull_coroutine< R >::iterator
range_end( pull_coroutine< R > &)
{ return typename pull_coroutine< R >::iterator(); }

template< typename R >
typename pull_coroutine< R >::const_iterator
range_end( pull_coroutine< R > const&)
{ return typename pull_coroutine< R >::const_iterator(); }

template< typename Arg >
typename push_coroutine< Arg >::iterator
range_begin( push_coroutine< Arg > & c)
{ return typename push_coroutine< Arg >::iterator( & c); }

template< typename Arg >
typename push_coroutine< Arg >::iterator
range_end( push_coroutine< Arg > &)
{ return typename push_coroutine< Arg >::iterator(); }

template< typename T >
struct asymmetric_coroutine
{
    typedef push_coroutine< T > push_type;
    typedef pull_coroutine< T > pull_type;
};

// deprecated
template< typename T >
struct coroutine
{
    typedef push_coroutine< T > push_type;
    typedef pull_coroutine< T > pull_type;
};

template< typename R >
typename pull_coroutine< R >::iterator
begin( pull_coroutine< R > & c)
{ return coroutines::range_begin( c); }

template< typename R >
typename pull_coroutine< R >::const_iterator
begin( pull_coroutine< R > const& c)
{ return coroutines::range_begin( c); }

template< typename R >
typename pull_coroutine< R >::iterator
end( pull_coroutine< R > & c)
{ return coroutines::range_end( c); }

template< typename R >
typename pull_coroutine< R >::const_iterator
end( pull_coroutine< R > const& c)
{ return coroutines::range_end( c); }

template< typename R >
typename push_coroutine< R >::iterator
begin( push_coroutine< R > & c)
{ return coroutines::range_begin( c); }

template< typename R >
typename push_coroutine< R >::iterator
end( push_coroutine< R > & c)
{ return coroutines::range_end( c); }

}

// forward declaration of Boost.Range traits to break dependency on it
template<typename C, typename Enabler>
struct range_mutable_iterator;

template<typename C, typename Enabler>
struct range_const_iterator;

template< typename Arg >
struct range_mutable_iterator< coroutines::push_coroutine< Arg >, void >
{ typedef typename coroutines::push_coroutine< Arg >::iterator type; };

template< typename R >
struct range_mutable_iterator< coroutines::pull_coroutine< R >, void >
{ typedef typename coroutines::pull_coroutine< R >::iterator type; };

}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_ASYMMETRIC_COROUTINE_H

/* asymmetric_coroutine.hpp
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
*/