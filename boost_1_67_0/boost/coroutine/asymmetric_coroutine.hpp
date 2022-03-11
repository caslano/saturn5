
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
#include <boost/range.hpp>
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
{ return boost::begin( c); }

template< typename R >
typename pull_coroutine< R >::const_iterator
begin( pull_coroutine< R > const& c)
{ return boost::begin( c); }

template< typename R >
typename pull_coroutine< R >::iterator
end( pull_coroutine< R > & c)
{ return boost::end( c); }

template< typename R >
typename pull_coroutine< R >::const_iterator
end( pull_coroutine< R > const& c)
{ return boost::end( c); }

template< typename R >
typename push_coroutine< R >::iterator
begin( push_coroutine< R > & c)
{ return boost::begin( c); }

template< typename R >
typename push_coroutine< R >::iterator
end( push_coroutine< R > & c)
{ return boost::end( c); }

}

template< typename Arg >
struct range_mutable_iterator< coroutines::push_coroutine< Arg > >
{ typedef typename coroutines::push_coroutine< Arg >::iterator type; };

template< typename R >
struct range_mutable_iterator< coroutines::pull_coroutine< R > >
{ typedef typename coroutines::pull_coroutine< R >::iterator type; };

}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_ASYMMETRIC_COROUTINE_H

/* asymmetric_coroutine.hpp
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
*/