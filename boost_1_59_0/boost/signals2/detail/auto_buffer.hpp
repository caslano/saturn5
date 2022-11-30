// Copyright Thorsten Ottosen, 2009.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SIGNALS2_DETAIL_AUTO_BUFFER_HPP_25_02_2009
#define BOOST_SIGNALS2_DETAIL_AUTO_BUFFER_HPP_25_02_2009

#include <boost/detail/workaround.hpp>

#if defined(_MSC_VER)
# pragma once
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4996)
#endif

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/signals2/detail/scope_guard.hpp>
#include <boost/swap.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <algorithm>
#include <cstring>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace boost
{
namespace signals2
{
namespace detail
{
    //
    // Policies for creating the stack buffer.
    //
    template< unsigned N >
    struct store_n_objects
    {
        BOOST_STATIC_CONSTANT( unsigned, value = N );
    };

    template< unsigned N >
    struct store_n_bytes
    {
        BOOST_STATIC_CONSTANT( unsigned, value = N );
    };

    namespace auto_buffer_detail
    {
        template< class Policy, class T >
        struct compute_buffer_size
        {
            BOOST_STATIC_CONSTANT( unsigned, value = Policy::value * sizeof(T) );
        };

        template< unsigned N, class T >
        struct compute_buffer_size< store_n_bytes<N>, T >
        {
            BOOST_STATIC_CONSTANT( unsigned, value = N );
        };

        template< class Policy, class T >
        struct compute_buffer_objects
        {
            BOOST_STATIC_CONSTANT( unsigned, value = Policy::value );
        };

        template< unsigned N, class T >
        struct compute_buffer_objects< store_n_bytes<N>, T >
        {
            BOOST_STATIC_CONSTANT( unsigned, value = N / sizeof(T) );
        };
    }

    struct default_grow_policy
    {
        template< class SizeType >
        static SizeType new_capacity( SizeType capacity )
        {
            //
            // @remark: we grow the capacity quite agressively.
            //          this is justified since we aim to minimize
            //          heap-allocations, and because we mostly use
            //          the buffer locally.
            return capacity * 4u;
        }

        template< class SizeType >
        static bool should_shrink( SizeType, SizeType )
        {
            //
            // @remark: when defining a new grow policy, one might
            //          choose that if the waated space is less
            //          than a certain percentage, then it is of
            //          little use to shrink.
            //
            return true;
        }
    };

    template< class T,
              class StackBufferPolicy = store_n_objects<256>,
              class GrowPolicy        = default_grow_policy,
              class Allocator         = std::allocator<T> >
    class auto_buffer;



    template
    <
        class T,
        class StackBufferPolicy,
        class GrowPolicy,
        class Allocator
    >
    class auto_buffer : Allocator
    {
    private:
        enum { N = auto_buffer_detail::
                   compute_buffer_objects<StackBufferPolicy,T>::value };

        BOOST_STATIC_CONSTANT( bool, is_stack_buffer_empty = N == 0u );

        typedef auto_buffer<T, store_n_objects<0>, GrowPolicy, Allocator>
                                                         local_buffer;

    public:
        typedef Allocator                                allocator_type;
        typedef T                                        value_type;
        typedef typename boost::allocator_size_type<Allocator>::type size_type;
        typedef typename boost::allocator_difference_type<Allocator>::type difference_type;
        typedef T*                                       pointer;
        typedef typename boost::allocator_pointer<Allocator>::type allocator_pointer;
        typedef const T*                                 const_pointer;
        typedef T&                                       reference;
        typedef const T&                                 const_reference;
        typedef pointer                                  iterator;
        typedef const_pointer                            const_iterator;
        typedef boost::reverse_iterator<iterator>        reverse_iterator;
        typedef boost::reverse_iterator<const_iterator>  const_reverse_iterator;
        typedef typename boost::mpl::if_c< boost::has_trivial_assign<T>::value
                                           && sizeof(T) <= sizeof(long double),
                                          const value_type,
                                          const_reference >::type
                                                      optimized_const_reference;
    private:

        pointer allocate( size_type capacity_arg )
        {
            if( capacity_arg > N )
                return &*get_allocator().allocate( capacity_arg );
            else
                return static_cast<T*>( members_.address() );
        }

        void deallocate( pointer where, size_type capacity_arg )
        {
            if( capacity_arg <= N )
                return;
            get_allocator().deallocate( allocator_pointer(where), capacity_arg );
        }

        template< class I >
        static void copy_impl( I begin, I end, pointer where, std::random_access_iterator_tag )
        {
            copy_rai( begin, end, where, boost::has_trivial_assign<T>() );
        }

        static void copy_rai( const T* begin, const T* end,
                              pointer where, const boost::true_type& )
        {
            std::memcpy( where, begin, sizeof(T) * std::distance(begin,end) );
        }

        template< class I, bool b >
        static void copy_rai( I begin, I end,
                              pointer where, const boost::integral_constant<bool, b>& )
        {
            std::uninitialized_copy( begin, end, where );
        }

        template< class I >
        static void copy_impl( I begin, I end, pointer where, std::bidirectional_iterator_tag )
        {
            std::uninitialized_copy( begin, end, where );
        }

        template< class I >
        static void copy_impl( I begin, I end, pointer where )
        {
            copy_impl( begin, end, where,
                       typename std::iterator_traits<I>::iterator_category() );
        }

        template< class I, class I2 >
        static void assign_impl( I begin, I end, I2 where )
        {
            assign_impl( begin, end, where, boost::has_trivial_assign<T>() );
        }

        template< class I, class I2 >
        static void assign_impl( I begin, I end, I2 where, const boost::true_type& )
        {
            std::memcpy( where, begin, sizeof(T) * std::distance(begin,end) );
        }

        template< class I, class I2 >
        static void assign_impl( I begin, I end, I2 where, const boost::false_type& )
        {
            for( ; begin != end; ++begin, ++where )
                *where = *begin;
        }

        void unchecked_push_back_n( size_type n, const boost::true_type& )
        {
            std::uninitialized_fill( end(), end() + n, T() );
            size_ += n;
        }

        void unchecked_push_back_n( size_type n, const boost::false_type& )
        {
            for( size_type i = 0u; i < n; ++i )
                unchecked_push_back();
        }

        void auto_buffer_destroy( pointer where, const boost::false_type& )
        {
            (*where).~T();
        }

        void auto_buffer_destroy( pointer, const boost::true_type& )
        { }

        void auto_buffer_destroy( pointer where )
        {
            auto_buffer_destroy( where, boost::has_trivial_destructor<T>() );
        }

        void auto_buffer_destroy()
        {
            BOOST_ASSERT( is_valid() );
            if( buffer_ ) // do we need this check? Yes, but only
                // for N = 0u + local instances in one_sided_swap()
                auto_buffer_destroy( boost::has_trivial_destructor<T>() );
        }

        void destroy_back_n( size_type n, const boost::false_type& )
        {
            BOOST_ASSERT( n > 0 );
            pointer buffer  = buffer_ + size_ - 1u;
            pointer new_end = buffer - n;
            for( ; buffer > new_end; --buffer )
                auto_buffer_destroy( buffer );
        }

        void destroy_back_n( size_type, const boost::true_type& )
        { }

        void destroy_back_n( size_type n )
        {
            destroy_back_n( n, boost::has_trivial_destructor<T>() );
        }

        void auto_buffer_destroy( const boost::false_type& x )
        {
            if( size_ )
                destroy_back_n( size_, x );
            deallocate( buffer_, members_.capacity_ );
        }

        void auto_buffer_destroy( const boost::true_type& )
        {
            deallocate( buffer_, members_.capacity_ );
        }

        pointer move_to_new_buffer( size_type new_capacity, const boost::false_type& )
        {
            pointer new_buffer = allocate( new_capacity ); // strong
            scope_guard guard = make_obj_guard( *this,
                                                &auto_buffer::deallocate,
                                                new_buffer,
                                                new_capacity );
            copy_impl( begin(), end(), new_buffer ); // strong
            guard.dismiss();                         // nothrow
            return new_buffer;
        }

        pointer move_to_new_buffer( size_type new_capacity, const boost::true_type& )
        {
            pointer new_buffer = allocate( new_capacity ); // strong
            copy_impl( begin(), end(), new_buffer );       // nothrow
            return new_buffer;
        }

        void reserve_impl( size_type new_capacity )
        {
            pointer new_buffer = move_to_new_buffer( new_capacity,
                                                 boost::has_nothrow_copy<T>() );
            auto_buffer_destroy();
            buffer_   = new_buffer;
            members_.capacity_ = new_capacity;
            BOOST_ASSERT( size_ <= members_.capacity_ );
        }

        size_type new_capacity_impl( size_type n )
        {
            BOOST_ASSERT( n > members_.capacity_ );
            size_type new_capacity = GrowPolicy::new_capacity( members_.capacity_ );
            // @todo: consider to check for allocator.max_size()
            return (std::max)(new_capacity,n);
        }

        static void swap_helper( auto_buffer& l, auto_buffer& r,
                                 const boost::true_type& )
        {
            BOOST_ASSERT( l.is_on_stack() && r.is_on_stack() );

            auto_buffer temp( l.begin(), l.end() );
            assign_impl( r.begin(), r.end(), l.begin() );
            assign_impl( temp.begin(), temp.end(), r.begin() );
            boost::swap( l.size_, r.size_ );
            boost::swap( l.members_.capacity_, r.members_.capacity_ );
        }

        static void swap_helper( auto_buffer& l, auto_buffer& r,
                                 const boost::false_type& )
        {
            BOOST_ASSERT( l.is_on_stack() && r.is_on_stack() );
            size_type min_size    = (std::min)(l.size_,r.size_);
            size_type max_size    = (std::max)(l.size_,r.size_);
            size_type diff        = max_size - min_size;
            auto_buffer* smallest = l.size_ == min_size ? &l : &r;
            auto_buffer* largest  = smallest == &l ? &r : &l;

            // @remark: the implementation below is not as fast
            //          as it could be if we assumed T had a default
            //          constructor.

            size_type i = 0u;
            for(  ; i < min_size; ++i )
                boost::swap( (*smallest)[i], (*largest)[i] );

            for( ; i < max_size; ++i )
                smallest->unchecked_push_back( (*largest)[i] );

            largest->pop_back_n( diff );
            boost::swap( l.members_.capacity_, r.members_.capacity_ );
        }

        void one_sided_swap( auto_buffer& temp ) // nothrow
        {
            BOOST_ASSERT( !temp.is_on_stack() );
            auto_buffer_destroy();
            // @remark: must be nothrow
            get_allocator()    = temp.get_allocator();
            members_.capacity_ = temp.members_.capacity_;
            buffer_            = temp.buffer_;
            BOOST_ASSERT( temp.size_ >= size_ + 1u );
            size_              = temp.size_;
            temp.buffer_       = 0;
            BOOST_ASSERT( temp.is_valid() );
        }

        template< class I >
        void insert_impl( const_iterator before, I begin_arg, I end_arg,
                          std::input_iterator_tag )
        {
            for( ; begin_arg != end_arg; ++begin_arg )
            {
                before = insert( before, *begin_arg );
                ++before;
            }
        }

        void grow_back( size_type n, const boost::true_type& )
        {
            BOOST_ASSERT( size_ + n <= members_.capacity_ );
            size_ += n;
        }

        void grow_back( size_type n, const boost::false_type& )
        {
            unchecked_push_back_n(n);
        }

        void grow_back( size_type n )
        {
            grow_back( n, boost::has_trivial_constructor<T>() );
        }

        void grow_back_one( const boost::true_type& )
        {
            BOOST_ASSERT( size_ + 1 <= members_.capacity_ );
            size_ += 1;
        }

        void grow_back_one( const boost::false_type& )
        {
            unchecked_push_back();
        }

        void grow_back_one()
        {
            grow_back_one( boost::has_trivial_constructor<T>() );
        }

        template< class I >
        void insert_impl( const_iterator before, I begin_arg, I end_arg,
                          std::forward_iterator_tag )
        {
            difference_type n = std::distance(begin_arg, end_arg);

            if( size_ + n <= members_.capacity_ )
            {
                bool is_back_insertion = before == cend();
                if( !is_back_insertion )
                {
                    grow_back( n );
                    iterator where = const_cast<T*>(before);
                    std::copy( before, cend() - n, where + n );
                    assign_impl( begin_arg, end_arg, where );
                }
                else
                {
                    unchecked_push_back( begin_arg, end_arg );
                }
                BOOST_ASSERT( is_valid() );
                return;
            }

            auto_buffer temp( new_capacity_impl( size_ + n ) );
            temp.unchecked_push_back( cbegin(), before );
            temp.unchecked_push_back( begin_arg, end_arg );
            temp.unchecked_push_back( before, cend() );
            one_sided_swap( temp );
            BOOST_ASSERT( is_valid() );
        }

    public:
        bool is_valid() const // invariant
        {
            // @remark: allowed for N==0 and when
            //          using a locally instance
            //          in insert()/one_sided_swap()
            if( buffer_ == 0 )
                return true;

            if( members_.capacity_ < N )
                return false;

            if( !is_on_stack() && members_.capacity_ <= N )
                return false;

            if( buffer_ == members_.address() )
                if( members_.capacity_ > N )
                    return false;

            if( size_ > members_.capacity_ )
                return false;

            return true;
        }

        auto_buffer()
            : members_( N ),
              buffer_( static_cast<T*>(members_.address()) ),
              size_( 0u )
        {
            BOOST_ASSERT( is_valid() );
        }

        auto_buffer( const auto_buffer& r )
            : members_( (std::max)(r.size_,size_type(N)) ),
              buffer_( allocate( members_.capacity_ ) ),
              size_( 0 )
        {
            copy_impl( r.begin(), r.end(), buffer_ );
            size_ = r.size_;
            BOOST_ASSERT( is_valid() );
        }

        auto_buffer& operator=( const auto_buffer& r ) // basic
        {
            if( this == &r )
                return *this;

            difference_type diff = size_ - r.size_;
            if( diff >= 0 )
            {
                pop_back_n( static_cast<size_type>(diff) );
                assign_impl( r.begin(), r.end(), begin() );
            }
            else
            {
                if( members_.capacity_ >= r.size() )
                {
                    unchecked_push_back_n( static_cast<size_type>(-diff) );
                    assign_impl( r.begin(), r.end(), begin() );
                }
                else
                {
                    // @remark: we release memory as early as possible
                    //          since we only give the basic guarantee
                    auto_buffer_destroy();
                    buffer_ = 0;
                    pointer new_buffer = allocate( r.size() );
                    scope_guard guard = make_obj_guard( *this,
                                                        &auto_buffer::deallocate,
                                                        new_buffer,
                                                        r.size() );
                    copy_impl( r.begin(), r.end(), new_buffer );
                    guard.dismiss();
                    buffer_            = new_buffer;
                    members_.capacity_ = r.size();
                    size_              = members_.capacity_;
                }
            }

            BOOST_ASSERT( size() == r.size() );
            BOOST_ASSERT( is_valid() );
            return *this;
        }

        explicit auto_buffer( size_type capacity_arg )
            : members_( (std::max)(capacity_arg, size_type(N)) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            BOOST_ASSERT( is_valid() );
        }

        auto_buffer( size_type size_arg, optimized_const_reference init_value )
            : members_( (std::max)(size_arg, size_type(N)) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            std::uninitialized_fill( buffer_, buffer_ + size_arg, init_value );
            size_ = size_arg;
            BOOST_ASSERT( is_valid() );
        }

        auto_buffer( size_type capacity_arg, const allocator_type& a )
            : allocator_type( a ),
              members_( (std::max)(capacity_arg, size_type(N)) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            BOOST_ASSERT( is_valid() );
        }

        auto_buffer( size_type size_arg, optimized_const_reference init_value,
                     const allocator_type& a )
            : allocator_type( a ),
              members_( (std::max)(size_arg, size_type(N)) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            std::uninitialized_fill( buffer_, buffer_ + size_arg, init_value );
            size_ = size_arg;
            BOOST_ASSERT( is_valid() );
        }

        template< class ForwardIterator >
        auto_buffer( ForwardIterator begin_arg, ForwardIterator end_arg )
            :
              members_( std::distance(begin_arg, end_arg) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            copy_impl( begin_arg, end_arg, buffer_ );
            size_ = members_.capacity_;
            if( members_.capacity_ < N )
                members_.capacity_ = N;
            BOOST_ASSERT( is_valid() );
        }

        template< class ForwardIterator >
        auto_buffer( ForwardIterator begin_arg, ForwardIterator end_arg,
                     const allocator_type& a )
            : allocator_type( a ),
              members_( std::distance(begin_arg, end_arg) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            copy_impl( begin_arg, end_arg, buffer_ );
            size_ = members_.capacity_;
            if( members_.capacity_ < N )
                members_.capacity_ = N;
            BOOST_ASSERT( is_valid() );
        }

        ~auto_buffer()
        {
            auto_buffer_destroy();
        }

    public:
        bool empty() const
        {
            return size_ == 0;
        }

        bool full() const
        {
            return size_ == members_.capacity_;
        }

        bool is_on_stack() const
        {
            return members_.capacity_ <= N;
        }

        size_type size() const
        {
            return size_;
        }

        size_type capacity() const
        {
            return members_.capacity_;
        }

    public:
        pointer data()
        {
            return buffer_;
        }

        const_pointer data() const
        {
            return buffer_;
        }

        allocator_type& get_allocator()
        {
            return static_cast<allocator_type&>(*this);
        }

        const allocator_type& get_allocator() const
        {
            return static_cast<const allocator_type&>(*this);
        }

    public:
        iterator begin()
        {
            return buffer_;
        }

        const_iterator begin() const
        {
            return buffer_;
        }

        iterator end()
        {
            return buffer_ + size_;
        }

        const_iterator end() const
        {
            return buffer_ + size_;
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        const_iterator cbegin() const
        {
            return const_cast<const auto_buffer*>(this)->begin();
        }

        const_iterator cend() const
        {
            return const_cast<const auto_buffer*>(this)->end();
        }

        const_reverse_iterator crbegin() const
        {
            return const_cast<const auto_buffer*>(this)->rbegin();
        }

        const_reverse_iterator crend() const
        {
            return const_cast<const auto_buffer*>(this)->rend();
        }

    public:
        reference front()
        {
            return buffer_[0];
        }

        optimized_const_reference front() const
        {
            return buffer_[0];
        }

        reference back()
        {
            return buffer_[size_-1];
        }

        optimized_const_reference back() const
        {
            return buffer_[size_-1];
        }

        reference operator[]( size_type n )
        {
            BOOST_ASSERT( n < size_ );
            return buffer_[n];
        }

        optimized_const_reference operator[]( size_type n ) const
        {
            BOOST_ASSERT( n < size_ );
            return buffer_[n];
        }

        void unchecked_push_back()
        {
            BOOST_ASSERT( !full() );
            new (buffer_ + size_) T;
            ++size_;
        }

        void unchecked_push_back_n( size_type n )
        {
            BOOST_ASSERT( size_ + n <= members_.capacity_ );
            unchecked_push_back_n( n, boost::has_trivial_assign<T>() );
        }

        void unchecked_push_back( optimized_const_reference x ) // non-growing
        {
            BOOST_ASSERT( !full() );
            new (buffer_ + size_) T( x );
            ++size_;
        }

        template< class ForwardIterator >
        void unchecked_push_back( ForwardIterator begin_arg,
                                  ForwardIterator end_arg ) // non-growing
        {
            BOOST_ASSERT( size_ + std::distance(begin_arg, end_arg) <= members_.capacity_ );
            copy_impl( begin_arg, end_arg, buffer_ + size_ );
            size_ += std::distance(begin_arg, end_arg);
        }

        void reserve_precisely( size_type n )
        {
            BOOST_ASSERT( members_.capacity_  >= N );

            if( n <= members_.capacity_ )
                return;
            reserve_impl( n );
            BOOST_ASSERT( members_.capacity_ == n );
        }

        void reserve( size_type n ) // strong
        {
            BOOST_ASSERT( members_.capacity_  >= N );

            if( n <= members_.capacity_ )
                return;

            reserve_impl( new_capacity_impl( n ) );
            BOOST_ASSERT( members_.capacity_ >= n );
        }

        void push_back()
        {
            if( size_ != members_.capacity_ )
            {
                unchecked_push_back();
            }
            else
            {
                reserve( size_ + 1u );
                unchecked_push_back();
            }
        }

        void push_back( optimized_const_reference x )
        {
            if( size_ != members_.capacity_ )
            {
                unchecked_push_back( x );
            }
            else
            {
               reserve( size_ + 1u );
               unchecked_push_back( x );
            }
        }

        template< class ForwardIterator >
        void push_back( ForwardIterator begin_arg, ForwardIterator end_arg )
        {
            difference_type diff = std::distance(begin_arg, end_arg);
            if( size_ + diff > members_.capacity_ )
                reserve( size_ + diff );
            unchecked_push_back( begin_arg, end_arg );
        }

        iterator insert( const_iterator before, optimized_const_reference x ) // basic
        {
            // @todo: consider if we want to support x in 'this'
            if( size_ < members_.capacity_ )
            {
                bool is_back_insertion = before == cend();
                iterator where = const_cast<T*>(before);

                if( !is_back_insertion )
                {
                    grow_back_one();
                    std::copy( before, cend() - 1u, where + 1u );
                    *where = x;
                    BOOST_ASSERT( is_valid() );
                 }
                else
                {
                    unchecked_push_back( x );
                }
                return where;
            }

            auto_buffer temp( new_capacity_impl( size_ + 1u ) );
            temp.unchecked_push_back( cbegin(), before );
            iterator result = temp.end();
            temp.unchecked_push_back( x );
            temp.unchecked_push_back( before, cend() );
            one_sided_swap( temp );
            BOOST_ASSERT( is_valid() );
            return result;
        }

        void insert( const_iterator before, size_type n,
                     optimized_const_reference x )
        {
            // @todo: see problems above
            if( size_ + n <= members_.capacity_ )
            {
                grow_back( n );
                iterator where = const_cast<T*>(before);
                std::copy( before, cend() - n, where + n );
                std::fill( where, where + n, x );
                BOOST_ASSERT( is_valid() );
                return;
            }

            auto_buffer temp( new_capacity_impl( size_ + n ) );
            temp.unchecked_push_back( cbegin(), before );
            std::uninitialized_fill_n( temp.end(), n, x );
            temp.size_ += n;
            temp.unchecked_push_back( before, cend() );
            one_sided_swap( temp );
            BOOST_ASSERT( is_valid() );
        }

        template< class ForwardIterator >
        void insert( const_iterator before,
                     ForwardIterator begin_arg, ForwardIterator end_arg ) // basic
        {
            typedef typename std::iterator_traits<ForwardIterator>
                ::iterator_category category;
            insert_impl( before, begin_arg, end_arg, category() );
        }

        void pop_back()
        {
            BOOST_ASSERT( !empty() );
            auto_buffer_destroy( buffer_ + size_ - 1, boost::has_trivial_destructor<T>() );
            --size_;
        }

        void pop_back_n( size_type n )
        {
            BOOST_ASSERT( n <= size_ );
            if( n )
            {
                destroy_back_n( n );
                size_ -= n;
            }
        }

        void clear()
        {
            pop_back_n( size_ );
        }

        iterator erase( const_iterator where )
        {
            BOOST_ASSERT( !empty() );
            BOOST_ASSERT( cbegin() <= where );
            BOOST_ASSERT( cend() > where );

            unsigned elements = cend() - where - 1u;

            if( elements > 0u )
            {
                const_iterator start = where + 1u;
                std::copy( start, start + elements,
                           const_cast<T*>(where) );
            }
            pop_back();
            BOOST_ASSERT( !full() );
            iterator result = const_cast<T*>( where );
            BOOST_ASSERT( result <= end() );
            return result;
        }

        iterator erase( const_iterator from, const_iterator to )
        {
            BOOST_ASSERT( !(std::distance(from,to)>0) ||
                          !empty() );
            BOOST_ASSERT( cbegin() <= from );
            BOOST_ASSERT( cend() >= to );

            unsigned elements = std::distance(to,cend());

            if( elements > 0u )
            {
                BOOST_ASSERT( elements > 0u );
                std::copy( to, to + elements,
                           const_cast<T*>(from) );
            }
            pop_back_n( std::distance(from,to) );
            BOOST_ASSERT( !full() );
            iterator result = const_cast<T*>( from );
            BOOST_ASSERT( result <= end() );
            return result;
        }

        void shrink_to_fit()
        {
            if( is_on_stack() || !GrowPolicy::should_shrink(size_,members_.capacity_) )
                return;

            reserve_impl( size_ );
            members_.capacity_ = (std::max)(size_type(N),members_.capacity_);
            BOOST_ASSERT( is_on_stack() || size_ == members_.capacity_ );
            BOOST_ASSERT( !is_on_stack() || size_ <= members_.capacity_ );
        }

        pointer uninitialized_grow( size_type n ) // strong
        {
            if( size_ + n > members_.capacity_ )
                reserve( size_ + n );

            pointer res = end();
            size_ += n;
            return res;
        }

        void uninitialized_shrink( size_type n ) // nothrow
        {
            // @remark: test for wrap-around
            BOOST_ASSERT( size_ - n <= members_.capacity_ );
            size_ -= n;
        }

        void uninitialized_resize( size_type n )
        {
            if( n > size() )
                uninitialized_grow( n - size() );
            else if( n < size() )
                uninitialized_shrink( size() - n );

           BOOST_ASSERT( size() == n );
        }

        // nothrow  - if both buffer are on the heap, or
        //          - if one buffer is on the heap and one has
        //            'has_allocated_buffer() == false', or
        //          - if copy-construction cannot throw
        // basic    - otherwise (better guarantee impossible)
        // requirement: the allocator must be no-throw-swappable
        void swap( auto_buffer& r )
        {
            bool on_stack      = is_on_stack();
            bool r_on_stack    = r.is_on_stack();
            bool both_on_heap  = !on_stack && !r_on_stack;
            if( both_on_heap )
            {
                boost::swap( get_allocator(), r.get_allocator() );
                boost::swap( members_.capacity_, r.members_.capacity_ );
                boost::swap( buffer_, r.buffer_ );
                boost::swap( size_, r.size_ );
                BOOST_ASSERT( is_valid() );
                BOOST_ASSERT( r.is_valid() );
                return;
            }

            BOOST_ASSERT( on_stack || r_on_stack );
            bool exactly_one_on_stack = (on_stack && !r_on_stack) ||
                                        (!on_stack && r_on_stack);

            //
            // Remark: we now know that we can copy into
            //         the unused stack buffer.
            //
            if( exactly_one_on_stack )
            {
                auto_buffer* one_on_stack = on_stack ? this : &r;
                auto_buffer* other        = on_stack ? &r : this;
                pointer new_buffer = static_cast<T*>(other->members_.address());
                copy_impl( one_on_stack->begin(), one_on_stack->end(),
                           new_buffer );                            // strong
                one_on_stack->auto_buffer_destroy();                       // nothrow
                boost::swap( get_allocator(), r.get_allocator() );  // assume nothrow
                boost::swap( members_.capacity_, r.members_.capacity_ );
                boost::swap( size_, r.size_ );
                one_on_stack->buffer_ = other->buffer_;
                other->buffer_        = new_buffer;
                BOOST_ASSERT( other->is_on_stack() );
                BOOST_ASSERT( !one_on_stack->is_on_stack() );
                BOOST_ASSERT( is_valid() );
                BOOST_ASSERT( r.is_valid() );
                return;
            }

            BOOST_ASSERT( on_stack && r_on_stack );
            swap_helper( *this, r, boost::has_trivial_assign<T>() );
            BOOST_ASSERT( is_valid() );
            BOOST_ASSERT( r.is_valid() );
        }

    private:
        typedef boost::aligned_storage< N * sizeof(T),
                                        boost::alignment_of<T>::value >
                               storage;

        struct members_type : storage /* to enable EBO */
        {
            size_type capacity_;

            members_type( size_type capacity )
               : capacity_(capacity)
            { }

            void* address() const
            { return const_cast<storage&>(static_cast<const storage&>(*this)).address(); }
        };

        members_type members_;
        pointer      buffer_;
        size_type    size_;

    };

    template< class T, class SBP, class GP, class A >
    inline void swap( auto_buffer<T,SBP,GP,A>& l, auto_buffer<T,SBP,GP,A>& r )
    {
        l.swap( r );
    }

    template< class T, class SBP, class GP, class A >
    inline bool operator==( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        if( l.size() != r.size() )
            return false;
        return std::equal( l.begin(), l.end(), r.begin() );
    }

    template< class T, class SBP, class GP, class A >
    inline bool operator!=( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        return !(l == r);
    }

    template< class T, class SBP, class GP, class A >
    inline bool operator<( const auto_buffer<T,SBP,GP,A>& l,
                           const auto_buffer<T,SBP,GP,A>& r )
    {
        return std::lexicographical_compare( l.begin(), l.end(),
                                             r.begin(), r.end() );
    }

    template< class T, class SBP, class GP, class A >
    inline bool operator>( const auto_buffer<T,SBP,GP,A>& l,
                           const auto_buffer<T,SBP,GP,A>& r )
    {
        return (r < l);
    }

    template< class T, class SBP, class GP, class A >
    inline bool operator<=( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        return !(l > r);
    }

    template< class T, class SBP, class GP, class A >
    inline bool operator>=( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        return !(l < r);
    }

} // namespace detail
} // namespace signals2
}

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

#endif

/* auto_buffer.hpp
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
*/