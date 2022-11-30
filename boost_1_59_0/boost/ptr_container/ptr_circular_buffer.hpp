//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_PTR_CIRCULAR_BUFFER_HPP
#define BOOST_PTR_CONTAINER_PTR_CIRCULAR_BUFFER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/circular_buffer.hpp>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>
#include <boost/next_prior.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

    template
    < 
        class T, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<void*>
    >
    class ptr_circular_buffer : public 
        ptr_sequence_adapter< T, boost::circular_buffer<
                typename ptr_container_detail::void_ptr<T>::type,Allocator>, 
                              CloneAllocator >
    {  
        typedef ptr_sequence_adapter< T, boost::circular_buffer<
                typename ptr_container_detail::void_ptr<T>::type,Allocator>, 
                                      CloneAllocator > 
            base_type;

        typedef boost::circular_buffer<typename 
            ptr_container_detail::void_ptr<T>::type,Allocator>  circular_buffer_type;
        typedef ptr_circular_buffer<T,CloneAllocator,Allocator> this_type;
        
    public: // typedefs
        typedef typename base_type::value_type     value_type;
        typedef value_type*                        pointer;
        typedef const value_type*                  const_pointer;
        typedef typename base_type::size_type      size_type;
        typedef typename base_type::allocator_type allocator_type;
        typedef typename base_type::iterator       iterator;
        typedef typename base_type::const_iterator const_iterator;
        typedef typename base_type::auto_type      auto_type;
        
        typedef std::pair<pointer,size_type>                  array_range;
        typedef std::pair<const_pointer,size_type>            const_array_range;
        typedef typename circular_buffer_type::capacity_type  capacity_type;

    public: // constructors
        ptr_circular_buffer()
        { }

        explicit ptr_circular_buffer( capacity_type n )
          : base_type( n, ptr_container_detail::fixed_length_sequence_tag() )
        { }
        
        ptr_circular_buffer( capacity_type n,
                             const allocator_type& alloc )
          : base_type( n, alloc, ptr_container_detail::fixed_length_sequence_tag() )
        { }

        template< class ForwardIterator >
        ptr_circular_buffer( ForwardIterator first, ForwardIterator last )
          : base_type( first, last, ptr_container_detail::fixed_length_sequence_tag() )
        { }

        template< class InputIterator >
        ptr_circular_buffer( capacity_type n, InputIterator first, InputIterator last )
          : base_type( n, first, last, ptr_container_detail::fixed_length_sequence_tag() )
        { }

        ptr_circular_buffer( const ptr_circular_buffer& r )
          : base_type( r.size(), r.begin(), r.end(), 
                       ptr_container_detail::fixed_length_sequence_tag() )
        { }

        template< class U >
        ptr_circular_buffer( const ptr_circular_buffer<U>& r )
          : base_type( r.size(), r.begin(), r.end(), 
                       ptr_container_detail::fixed_length_sequence_tag() )
        { }

        ptr_circular_buffer& operator=( ptr_circular_buffer r )
        {
            this->swap( r );
            return *this;
        }

        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_circular_buffer,
                                                      base_type, this_type )
            
    public: // allocators
        allocator_type& get_allocator() 
        {
            return this->base().get_allocator();
        }

        allocator_type get_allocator() const
        {
            return this->base().get_allocator();
        }

    public: // circular buffer functions
        array_range array_one() // nothrow
        {
            typename circular_buffer_type::array_range r = this->base().array_one();
            return array_range( reinterpret_cast<pointer>(r.first), r.second );
        }

        const_array_range array_one() const // nothrow
        {
            typename circular_buffer_type::const_array_range r = this->base().array_one();
            return const_array_range( reinterpret_cast<const_pointer>(r.first), r.second );
        }

        array_range array_two() // nothrow
        {
            typename circular_buffer_type::array_range r = this->base().array_two();
            return array_range( reinterpret_cast<pointer>(r.first), r.second );
        }

        const_array_range array_two() const // nothrow
        {
            typename circular_buffer_type::const_array_range r = this->base().array_two();
            return const_array_range( reinterpret_cast<const_pointer>(r.first), r.second );
        }

        pointer linearize() // nothrow
        {
            return reinterpret_cast<pointer>(this->base().linearize());
        }

        bool full() const // nothrow
        {
            return this->base().full();
        }

        size_type reserve() const // nothrow
        {
            return this->base().reserve();
        }

        void reserve( size_type n ) // strong
        {
            if( capacity() < n )
                set_capacity( n );
        }

        capacity_type capacity() const // nothrow
        {
            return this->base().capacity();
        }

        void set_capacity( capacity_type new_capacity ) // strong
        {
            if( this->size() > new_capacity )
            {
                this->erase( this->begin() + new_capacity, this->end() );
            }
            this->base().set_capacity( new_capacity );
        }

        void rset_capacity( capacity_type new_capacity ) // strong
        {
            if( this->size() > new_capacity )
            {
                this->erase( this->begin(), 
                             this->begin() + (this->size()-new_capacity) );
            }
            this->base().rset_capacity( new_capacity );
        }

        void resize( size_type size ) // basic
        {
            size_type old_size = this->size();
            if( old_size > size )
            {
                this->erase( boost::next( this->begin(), size ), this->end() );  
            }
            else if( size > old_size )
            {
                for( ; old_size != size; ++old_size )
                    this->push_back( new BOOST_DEDUCED_TYPENAME 
                                     boost::remove_pointer<value_type>::type() ); 
            }

            BOOST_ASSERT( this->size() == size );
        }

        void resize( size_type size, value_type to_clone ) // basic
        {
            size_type old_size = this->size();
            if( old_size > size )
            {
                this->erase( boost::next( this->begin(), size ), this->end() );  
            }
            else if( size > old_size )
            {
                for( ; old_size != size; ++old_size )
                    this->push_back( this->null_policy_allocate_clone( to_clone ) ); 
            }

            BOOST_ASSERT( this->size() == size );        
        }

        void rresize( size_type size ) // basic
        {
            size_type old_size = this->size();
            if( old_size > size )
            {
                this->erase( this->begin(), 
                             boost::next( this->begin(), old_size - size ) );  
            }
            else if( size > old_size )
            {
                for( ; old_size != size; ++old_size )
                    this->push_front( new BOOST_DEDUCED_TYPENAME 
                                      boost::remove_pointer<value_type>::type() ); 
            }

            BOOST_ASSERT( this->size() == size );
        }

        void rresize( size_type size, value_type to_clone ) // basic
        {
            size_type old_size = this->size();
            if( old_size > size )
            {
                this->erase( this->begin(), 
                             boost::next( this->begin(), old_size - size ) );  
            }
            else if( size > old_size )
            {
                for( ; old_size != size; ++old_size )
                    this->push_front( this->null_policy_allocate_clone( to_clone ) ); 
            }

            BOOST_ASSERT( this->size() == size );
        }           

        template< class InputIterator >
        void assign( InputIterator first, InputIterator last ) // strong
        { 
            ptr_circular_buffer temp( first, last );
            this->swap( temp );
        }

        template< class Range >
        void assign( const Range& r ) // strong
        {
            assign( boost::begin(r), boost::end(r ) );
        }

        void assign( size_type n, value_type to_clone ) // strong
        {
            ptr_circular_buffer temp( n );
            for( size_type i = 0u; i != n; ++i )
               temp.push_back( temp.null_policy_allocate_clone( to_clone ) );
            this->swap( temp ); 
        }
        
        void assign( capacity_type capacity, size_type n, 
                     value_type to_clone ) // basic
        {
            this->assign( (std::min)(n,capacity), to_clone );
        }

        template< class InputIterator >
        void assign( capacity_type capacity, 
                     InputIterator first, InputIterator last ) // basic
        {
            this->assign( first, last );
            this->set_capacity( capacity );
        }

        void push_back( value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );
            this->enforce_null_policy( ptr, "Null pointer in 'push_back()'" );
         
            auto_type old_ptr( value_type(), *this );
            if( full() )
                old_ptr.reset( &*this->begin(), *this );
            this->base().push_back( ptr );           
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        void push_back( std::auto_ptr<U> ptr ) // nothrow
        {
            push_back( ptr.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        void push_back( std::unique_ptr<U> ptr ) // nothrow
        {
            push_back( ptr.release() );
        }
#endif

        void push_front( value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );
            this->enforce_null_policy( ptr, "Null pointer in 'push_front()'" );

            auto_type old_ptr( value_type(), *this );
            if( full() )
                old_ptr.reset( &*(--this->end()), *this );
            this->base().push_front( ptr );            
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        void push_front( std::auto_ptr<U> ptr ) // nothrow
        {
            push_front( ptr.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        void push_front( std::unique_ptr<U> ptr ) // nothrow
        {
            push_front( ptr.release() );
        }
#endif

        iterator insert( iterator pos, value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );
            this->enforce_null_policy( ptr, "Null pointer in 'insert()'" );

            auto_type new_ptr( ptr, *this );
            iterator b = this->begin();
            if( full() && pos == b )
                return b;
            
            new_ptr.release();            
            auto_type old_ptr( value_type(), *this );
            if( full() )
                old_ptr.reset( &*this->begin(), *this );

            return this->base().insert( pos.base(), ptr );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator insert( iterator pos, std::auto_ptr<U> ptr ) // nothrow
        {
            return insert( pos, ptr.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator insert( iterator pos, std::unique_ptr<U> ptr ) // nothrow
        {
            return insert( pos, ptr.release() );
        }
#endif

        template< class InputIterator >
        void insert( iterator pos, InputIterator first, InputIterator last ) // basic
        {
            for( ; first != last; ++first, ++pos )
                pos = insert( pos, this->null_policy_allocate_clone( &*first ) );                
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else
        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        insert( iterator before, const Range& r )
        {
            insert( before, boost::begin(r), boost::end(r) );
        }

#endif
           
        iterator rinsert( iterator pos, value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );
            this->enforce_null_policy( ptr, "Null pointer in 'rinsert()'" );

            auto_type new_ptr( ptr, *this );
            iterator b = this->end();
            if (full() && pos == b)
                return b;
                       
            new_ptr.release();            
            auto_type old_ptr( value_type(), *this );
            if( full() )
                old_ptr.reset( &this->back(), *this );

            return this->base().rinsert( pos.base(), ptr );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator rinsert( iterator pos, std::auto_ptr<U> ptr ) // nothrow
        {
            return rinsert( pos, ptr.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator rinsert( iterator pos, std::unique_ptr<U> ptr ) // nothrow
        {
            return rinsert( pos, ptr.release() );
        }
#endif

 
        template< class InputIterator >
        void rinsert( iterator pos, InputIterator first, InputIterator last ) // basic
        {
            for( ; first != last; ++first, ++pos )
                pos = rinsert( pos, this->null_policy_allocate_clone( &*first ) );                
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else
        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        rinsert( iterator before, const Range& r )
        {
            rinsert( before, boost::begin(r), boost::end(r) );
        }

#endif

        iterator rerase( iterator pos ) // nothrow
        {
            BOOST_ASSERT( !this->empty() );
            BOOST_ASSERT( pos != this->end() );

            this->remove( pos );
            return iterator( this->base().rerase( pos.base() ) );
        }

        iterator rerase( iterator first, iterator last ) // nothrow
        {
            this->remove( first, last );
            return iterator( this->base().rerase( first.base(),
                                                  last.base() ) );
        }

        template< class Range >
        iterator rerase( const Range& r ) // nothrow
        {
            return rerase( boost::begin(r), boost::end(r) );
        }

        void rotate( const_iterator new_begin ) // nothrow
        {
            this->base().rotate( new_begin.base() );
        }

    public: // transfer        
        template< class PtrSeqAdapter >
        void transfer( iterator before, 
                       BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator first, 
                       BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator last, 
                       PtrSeqAdapter& from ) // nothrow
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
            if( from.empty() )
                return;
            for( BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator begin = first; 
                 begin != last;  ++begin, ++before )
                before = insert( before, &*begin );          // nothrow
            from.base().erase( first.base(), last.base() );  // nothrow
        }

        template< class PtrSeqAdapter >
        void transfer( iterator before, 
                       BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator object, 
                       PtrSeqAdapter& from ) // nothrow
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
            if( from.empty() )
                return;
            insert( before, &*object );          // nothrow 
            from.base().erase( object.base() );  // nothrow 
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else
        
        template< class PtrSeqAdapter, class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                      BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator > >::type
        transfer( iterator before, const Range& r, PtrSeqAdapter& from ) // nothrow
        {
            transfer( before, boost::begin(r), boost::end(r), from );
        }

#endif
        template< class PtrSeqAdapter >
        void transfer( iterator before, PtrSeqAdapter& from ) // nothrow
        {
            transfer( before, from.begin(), from.end(), from );            
        }

    public: // C-array support
    
        void transfer( iterator before, value_type* from, 
                       size_type size, bool delete_from = true ) // nothrow 
        {
            BOOST_ASSERT( from != 0 );
            if( delete_from )
            {
                BOOST_DEDUCED_TYPENAME base_type::scoped_deleter 
                    deleter( *this, from, size );                  // nothrow
                for( size_type i = 0u; i != size; ++i, ++before )
                    before = insert( before, *(from+i) );          // nothrow
                deleter.release();                                 // nothrow
            }
            else
            {
                for( size_type i = 0u; i != size; ++i, ++before )
                    before = insert( before, *(from+i) );          // nothrow
           }
        }

        value_type* c_array() // nothrow
        {
            if( this->empty() )
                return 0;
            this->linearize();
            T** res = reinterpret_cast<T**>( &this->begin().base()[0] );
            return res;
        }

    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename T, typename CA, typename A >
    inline ptr_circular_buffer<T,CA,A>* new_clone( const ptr_circular_buffer<T,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_circular_buffer<T,CA,A>& l, ptr_circular_buffer<T,CA,A>& r )
    {
        l.swap(r);
    }
    
}

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_circular_buffer.hpp
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
*/