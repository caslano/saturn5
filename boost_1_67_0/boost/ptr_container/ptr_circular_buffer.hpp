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
38UHiqmwuF/hpSyH0hLkywjMKRoxBPmvUFpUkkOb6sHt64CEDmxYPQZxHOpERxToRSBQH0xDt40+ThVhSZMv93ZUloCgIzPOhW7Vk6MBp4sltY3p6a8hi/Pve8Q9v3FNxm5FG/z3H8lama+DG04pOSnPBaf2yI6NcTDWPplKSEVIWPEUR/MNrHEXZ8HN3yGP7oCNbzHMvSN6mTyOq/1x5Ob0mL4mr/pXqh7bWE7qm8+IDVnx/qzUCFAexNnwmQEAAkAEuyIDnrty6ypSk5SL+KNm+VtZ5zyjqmtqAGAwGL7Uo3lbUNovCuNdoSIhdbORJf6+DqEUTFJK0+Xh4dH8/u3b5/9uoOkyMcxsTYSYWXMP+sJCyEcP8JJsZjJ6kFP+L5+R3PrbGIeHyGPbuJrcCbrUZA570QocbrcOLvSinyDwjlGPM98+kKNGpJ0qRdArl3UwpSYtiqc4sembURjCKFbvD7JiCyFNF1sr3xmsj6wtmnT31mN10iy1ci5+/DdDX83wva/QNHXZpZ6rVQbKtasCpYqot/HgbhRCBGMBOfkyy7IiYFp8gK0K8zGbreibNtXG6VWzVtXQAjVAwn+7s5iL2X9HwOcjuDvqbD3U1Hrl9nbUIbuB6Avdorf9JKN68V+dA9jZfOmYhOmzh09AxemK8zDp1Dqs3SMCqVrQc4lpcuP84Zx6OwDW3wyVxqqm1GQXP/51/4OAwujcbUFj6FzCjiqa6G6VweJSBinbQpXoygtpeRfszjLWfkzlKd8y1Hk69M2DclAI2BONvhZLI8EmKbzmvFO3q0o6XDM4QjV2gTpbXPlSlP5F1ML/y482wy+KkopqeXQBXfkLSuvOTZDvIUZ3aT4Yue24GLcQpBg8dwu10HsEOpafOismVz18eV4a96Zi9r56bB+ZCPRB3fFVnFabUt46y9+dPvuxmwHRAvv2Qm8F8cLr3uNwzWal5wIlJ+us+waVJ8KoZ4S3tQ8L75e/sRoqkhsPj36rl00nPz6Ay3LwTO0SlVToX8iYTKi39i7IaIq8Glvr+FOU9U3NynTDWuPqM6fERmWN2h/ffIQfwz4+8nyZJc1jyqKCguuR7kxXnKsKAn1UTm5uj/9+HQCBg/n9Yov/ePlG7WJBPoKAW5j+r3Nv0QLM7iuH4c0NNDmJ4UrnYmJiwm6p7B4MW7qk36/MVLP9iUc2zd7H16/6KU1XRjCBff0tujKWk++FZ/ZLBZ76SlKWCQn3ZbD1ScPVyKMxc4DMneIJUtTxnDZGw+m9wmgz/m0Z2M4Il1mdk2KUtK9l4plT6DK4Ty8/Httq52D32W7uT1wL28G0HDfNFg75UGFEcuqk5AnNXGuQ1TVgg0SSU6SXuVTBjO6ks0mJVuXPwgQ27oYc/jhepM5LtZvZQFwsN83nsyOpbNKpqLzbStASPIo/yifPj3ZCNuhSyifK2cVFRuM1t/2uwHukIIv5PYo6DNxFG4LbGhqvrq6+iJG7TRohZDZMKJ1/RyEG2pR9AbDmLb6Z1Hv/YvPsNelr58WTxdcHENxxdXG8wNo4Xr7dAHv4J32rcjinHKwOzjsHmy8+55wis00R6luHa7ObrD6yz30YCXOkN7Un5IlpsZeI7r2YxyngkLLvfBOlXUxHorxvgwpdwsRqU+Dwh1ArWkSc42+Wp9a5MEt1Fpr6nz/KAso+LqCnxTXX2nb2LnmTgKjyTJkd/K8vOyM/VPwun4Y/JFUfWDtgQXdYWDznZmd9awrmNb+CedYGbfdQem2qa+YRcUwTzZcyYFLR22zSw6mzPmGCMUFG4ASfjwG6n+mEnqzuIzL4yITKOMHeFh6BWJcKPImqfFPOQtnxwk1BDivsFBARzmsRZpu9nHt+Y8NxakdxCn02rNftG6j5mX0udTnMu3LrS1WO03dDQtl+2x+xwd+1EXxfWEE/3tDLv580NZnrOrREVufUgl8xlYjuPFdg/5LP812Wza21ePW0KmGa+d3Sw43xBukYkJNKvtl8n/QNW6hsHLV77t2/ScpgMNOvU9JghNdppaTUqXDUJQDveHBZ1Evxr4pLmgVL6JvmeUKvDplXlWO6NPGnq7Fg0qr65X0QkPTJ4LfpjwGg+T14Z7b1vorwnDQET+s5u560FmEOT1lAqw/Bhbpiv0kgYKt90k1jyxY/JttNsVblFRtnMWVkqBzKdTgco+A5jGodJoIFUQTjqWPMnzJi4m/860eer2TmDEq24Q8r7pcPVOeblRHPWQO2U46WaivK2PfNlr57A/Zf1Z2dDSdiTOm9Cjfotm4rL6iePFhvo2Fy1KTg7vaXY1vhpty2IEaXO5j3aeIPD8sZcro87bRHR+9XoM8zOTLSePK8x/2i3uvqAhqbms6BYANefZu6CkIbZB64GW+cIbdVFk/FmJZaFPvzp0M4TjGUozgFl+z5jUooLzIvhFbykWR/QeTdkEKHJFBZWZlT9tvNHS8sth3rGrC8ZDJXu6/o9XZxgKCIpfqcMnTRftyOlml1Kk+KbUHK17apKjZEkZMmfaIusBb+sR9+78RFRo7UoffmfUOLqr6s9zLwkLmgwx4esKWLK5fNkk3wXwQJlF1bHG/gySloCTY7WHJosKbsA8dKdwccKV/zbe8lD+IsaAjT9VDVXtJKADPK/4jXU9n3bbsdhprQLR96GUlxgPo6NBILEt3owfxOZJ3UrD45ThxsU2LlSFDa0PsKK1Chf//FK6FOl6s/hJ2z7+zWKcn/Pp0v5mO6wjZ/euiCzWPlAZ/dZ1j5o1YLFw57dBCS6sg4qEIvy9v3OvwUHyBnYbqR0vC0dZEAvgq+5p+a0qZ6TiYg3dNqGF0ACQFT/G2q2rKBgVP8StTS8gcIuHOcRYoTKV3dY8GHyyRHx9i4ZP1c621JEjm0WRxVcZ+lPAvos93dHK7dBBx1g52fuwQPTY7nL8Bcd8ngzvPil9GE+b7nG8QIWVTNb3h4q2vRYfvQ+e1MchZOFGO3ty1i9FH576WXP6ySjthFSvW4roiMwtyfJZ+bRe6WGz8rwJ4kyVDyJbCy8KV+YMnsK6F780TdKNzUZpQ+xob/E9R3JLiDgsGGBNsd+NrO9Hd7CWQj6xUETqpCdCKBrvYmj+RWj24vtYNU/orddnKZmG8re1tpt9Kv+cR+JPfstR3PUim0WI3mIm0a8HunARyw1Jsk6GZxofAF0ydjAREAKM6+aELKuTem4JDPzhRdI38RqqYqcBd66/vuHrA2JYUlCCuR+KmBpOwDsQaZbBDDyVHRBBnjY6VesjzqS6LuvIJTGYxu2C6CrGErux7oBvF0ipqfeS/ZiR2nyWmkn6DkSk9oe+B8kV8dqGY1G51mPeBs6SdlBu44VitFyIwuQ/q/q9GEHKZT3hofDGLUCumNOakQBOCL76s0K+eCWd/T2DLY8189zNwcXo4uOpivAEKPqj/19/Ud+FmUskxQ+NEuIJ/OVX7sJuCZJ0s+ODV0Z4E0ALcIgvlQ+8Zun6jG6RayUYS0eR5wyQZxzjuNn3cCt8b8KHHDbb3hmRcOQcg2AW8QD9OUj605j2x/r1vIrn0sRbg2Inn5lM422v382BR/HgYmf1hXqBz8sP69phHibKbgNExDkDE5bht5q5/j6gO7OozaO7pKkCBg8aNpl0KnSF9lgiX8cQLrJuDW9wzNbc24v8OWJ9zGO9g/8g+kHdEiNVv2VF4roB5qYVEeH1bi84ORCGsxL8stqWOb616WIsqEvpwJio1r7Q9l0s4m7idWQdLHdU+7v1gMFHqs8x94Q0pZ9nYOjFrAUT5TH1nN8xw66Blr2Mp6NfGI1oX1wDgnUlN9BC60oWqdbnNzUz5HKpFJrunStIHmCQo2dvmcjnNixAiNMm5n2Li4kYTFWkMApxL7+/sBk24WTv6YBYtx/bUEtGCZK6psv6iyns9xy3/rmCMSV9NBEDlQtmsAtJP6Hp3J3VqIg+QzbBHbE9lxeil9URhhcmpdfOXVoQdH0klfbpYpifP+QEXmrGd7/jCKpjsgu2aQiv1YDWJc7mlSRTMO8tl6WT5dy3Y43VuHVTqGLUYz3ghijEaT4x/s07r7Xd8R8COXMx/f9GmZnqSbV1nBCKwZRSQJagei2VtVMf8frMBLKHmO95/aWbTVUJrvLxk9XpW9L5en68ubpSaw/r72NynkhcxMq8AjXaa/WcEM1hRrGwIUPxHarstc45k7rRU5OZbdAIPW5blvhHmNvZL6uYjpdt6ts/XI46Rb6KLKiDjuywefzr16SBx/wVdakbPrpRb959QHFzNTJ2nzsOQzlfNgoG/PDpX2a3yJvjyBz3BUH30jwqB+vIIGWp9iv3EXz1ZD8xwpMc0R1jbBDPuR7vwyttKB8yjslRpNaoyjyHcjAPdJ5SCXM/pZQDotD+32B4McrK1j2ERwgtLu88yQjQHtJX2e0x2EwhFmUnJRsJPri8sM0sY37tKr7Io+ZWnQZAfnCshStJLRkMn5ylPKzKChDq4ONkvhm9edqeqpFIKyn925ybhH6U11q4P3LvMM/R5VXtD5syduV2Rpe65EBHV33LrLFkkVS3nYIXGXQoM6lurVM8l4ygJKhw66lQfxjFmUkkFad+n7rnkEjT8Ti6fZoLr6jN/tmiz9bQpU0KcVRR3KZEr2IMmVezqMelegQTLBDUEDHawrLiuP3Rh8aHzYfZh8+E6vNDL60/pTn11tpPC/4U/pf32BWplKmab9ymcKC0oLisurC9far7VTXFz3pz9jOGU85T2laKQ64zm9dUpzwHKw3HF5hfJMXXshH7yCAbhn+AKdIBhzyRzQzpbAuhE0p9UaY2c25dMfCGGHPU8By4vT5EL65u/8ur4wHjydZ6SSPYdstXsB95MEP6Oi4yBVivDOGurHSl+IjaMcHGohF1bNgaESMDP0x8EvPqy1MCKvUyv6xznXj/NIYmKDV/xEeXbueXZtTikox82ifyoN6z554ex4KZaEE/iMvus7Qgjp1m5ZTW+JB1fCe8peljW0FnL7trX1rJ+vyXh1gBumCXawHdot/pPsGUjetOLuJKJW+Y22sexWMM9zW5fdLYc3IF7DUN9Y8HtR3tm+iW8RjY5/WMhTUnVrGFCtvuIVCX5CdZy5xPP20+3EJU2//t9wE36ir685FgIKke+QDWoKaoGKCAltt02Vm/CBFgKmNp0RyDbrOFnHVmt40cAwueSfD+BYcaaDp08VV482B+TNx2PV5JuAXRVPPXKaJXHp15jPFlSqIxf4cJFTb2VM5Pia+CSWewK8yyMW5GvzYjxE2ZpyPPgkLO41wmqb8qOILxT66TxgEnxHbVoHygqUC3GVjXCUe3+HUzQ5MZ5lK2ld/aJMKLo8moKTzGPE9Lbis8Ahl8I9g70Hr/qEd85fL0zcah7vtKdYQ8qevVWfMpRY9cinwue9g598TSOxeqpMBu+8sbnvpDoRPBpjQ+e1wjr1zR1ISfM0mUNbJv7V+YxUiZ2fmlk0Y6XtHubR5jEUDd0cTH9Rgcxr7uS9i1CzAaSDpmxsALOGEYeJ7vu5LdAyW0gzZHkzh+C7ML46vRGQkgCDVYCbFs9OVThWlzWagDdwM43KIFAOmK6JCc0vrJ5pzoRWGiR6LdZvomew5mh+gsR0bzDh8DORl5jWxQloy0zDaScQVn+bYr2s2eXa2M/iqAmHxl1TTxND0oLOxKJ5hMLcxbLcVToT7B589jSRq/5d94D/p8ZLMd9PEXEFq0679cOJlOWv5l4obVsrro5Q9F5zj6T/dEuQeyztivyVxTXUDOG106wUvHAr3LSiOuCt5+xfztFkdZBrM2sjk6aF84MKRtcC+ZvUPGl0PGk3eO6gLZiaHQjRvCONudVF+Jq45ZS8vBpzmCao+yRe7yTxeHt0/ev6ZwAHoYgL65YNmh195zm1CceR/ijxGOKshtXhP2X0eFn890/255uLBs6itNGNAgQE/vf98Rw/nZAcl2LcosdgQIW2j960e4THEqQf/4XQDJaDZi593uOUQiWRo7gUtrNgNzBF4SHklY1HLcM18+oosIcy+wJyPgJLEUPsPK9dNOvE2jHEMjbT24nqcDHXr5zH388Kyjm4tH2hIOmdjh0/VBY8DHRQwExR/mb6qOXm3MbDUmswJF87dqp7AvjY1liHeVmlMLNxrYSq7NYbh8fobQEOTR57kYoq/egFDac/E8GCMYyVX7REeex3Okr6AyZ0HS0aPgfeLRRAtR1NnRt9oLlzf0xlDSNg0u5PNPjvGvT2OUmctTPTP0mc9HkNIX8nTC6NB1fNmIHl3SrekULTsb5gTM4pZH9Omuc7wsq7T+c7meJOQ9bAdoxpkPtQYJ+xB5+chNKiKaJOsOfIy30J5efiJ2fAhSmF0XuWecBaG478s3H9AT3HRtHHBMOFZbtGWCh2vFtB81+T2hFMZ7zON7VvuOf1UYJWT71bkVP1iVGwlHzS6FVg0feLMueeW0aRwpL3/fWYTmu0w0H1ayFvxUSDlAXuqltqdRh3JkzuxzA+Q+a58Fi2yc7sfahRISOGjgPLihijwaqpcdV+aio7glLy4pu/SH71kxoLSNQdJkNpyuPk5n1dX/IUwuPwRRQChTNxpAAF8TJ/AXAgm/ErAjXI5o1ASvwd8n/7cfltIJashNnp8B8+8fEDT+V0KPHIYpcbL2Kjt40smpBSd2aX0861AuieOw80T2e4v7Fen/jZnPp9YVqJy9xB4N13BkId4pOnxfo540841efCEKsNLtSKrr421PfC4UCaiXuIygKXf8N1vLsTMVKfWFXRsHpahVoQn4jyvCLNbyO49o1nX0CwpHSDb+/hVYkOitCz7d+J7JMv1+kmKVstHi7JWDXsCOjSvF358nqRkSeIrXEqOqPu0xl3ldMcGvVJmSVm4e7fqeCbG9cmgnPZjO/r8KRNUBOi5J9Z/MpkdCun8wpqSj5MTM+5NZ3WqljWdruoSbFwOfA8zLRE6ANTVIOdQXaudvZ/1sySjtFwLnkv+3flxnXectFQ56Zun/6fstHQ6Jz8v+aSu8/eYBtJYgQlnpnM1SW+8X0lnu1D62HsPtGPEnGH4HVK5wvpa2yXpGwVJCAOB6VzGkKyYAt2fF7318x+rzKqiHHfGvRddrPwDOglr9Cu2yksTZPalVCuiNaWccQ3gtE0blIOhlMivtqgFOw8/ypa/sDpkiV8na5HXEYRgGJmKKZxaJGIw+4WZwHk1wRfVikVbFfCsqi+MYKgUj5t8RluuaWFV82kh8WNV5w2afdEuVzkq7rtn1f3UpfxSQLFJShAHcMM21ZWkNDzdY0WNcudK4Ry8yL5EWois1eQUujHXovPXivPWZjwtYoP9BXFA57R98ct3wMa5ozxtZPVllqtT34cnHCXskTzC4M1tgXoaWmF3HGJo7qO4H7H4eazfTEFTAPBy5InHCwvUvXvIYqCxVz9ZxIj1hy9cZFmDrKW791W3KiqYHAtIIqeJwz6GjGhDAUJdXBUb0Dv4N6+gLyTv3crE8ZzqFdsfb0vFj9JlGXCBfDKNfHhpHx8PxkIvroRoOXBqGzTyBjLLhxucof/D4KhmH4n4bQJLC+M1VwDv96pMr/SvkZOzFfa9M+C3Ua8oC+mj/hxdSS0607+Vf9l03ZA7V2F6u9bNBz6MAmlwe1nnF53P1iFxOpn5+YHtss2LATBYG2Mfmb3RPnopptcdS0cdGfFN99NUkxd/5WPj29VPOVPP0aRSqjwiTG1rdbNwz2EwPQDa6tXyy167ZelO91jmt7H3w7jfcA5k3S7V8h9GDuTUc2nDmMFMovDzQVQ5+D83Roxp3+tO7NBnLdCJvR2ha1+Q//ZNDNtc9ELolnSIRLZ2NnROYx8pi0F7YXs5473URWiugk43NnLKbIhGmXa2ywDXlsojZGAnxAWdv2zcP0x65GZSQ0zC6is3fzjAA9hTZS/RTYK19kWYi8liMIIEiSmw+sTWru1l/8c4xAW4hr31B4X03OcyqWT/Qtk2yOSebACm/1thYq/oGv3LkxTZ3TFHuD1lITk5lSGqVA3ubIUxsyG39N/chbd/knqXt7BL4mVvCl7pVOaJa1iQvMCO8xQ/CWarphKooSqjyGXCizCRwG+Nl/mE0RqCr/wWEAK3DdDD239I8k9tSj5wi+JfQGQD8st8gr29xzIChgK+LUELnrh4enZ5jEd3iDhDlhBfvTf6dfc8J4SaFPFJw9TU3ITtgRKmgKJR7VF3YOYxRZ1T22aXUnPQFckkuWOrod2BOziMH+Qfnt148I6uvvZxhl9QoPYtJ8Fy2zI4QDuTl8AZrzeomnZuInPztPiXDGc/OvHz/qfC0wyIJ9sXCdguIlIQ7uxlRahrQ5KetJzhmioSzmbCWab7sRtsLMK9FO8T2S2bH8Y17UcFy/Sw7AR+I5blvG3QQE+VfPXxdFDt0d/LOAVGj8f6k2F8EayOIsejDeulvGwcFuX52ZKPeyrcgpPxeILWFlm5HObgneDdrjsYyw/cI0D9XjEA+8tSU291qOxfTJ5XpEtb1muEOAbmcKORzXrrj8qZLxR6WXZaGEWNX/7gUWAo2Mtnjng9CLzvaHh9rGcgWAxFbcrxvxerIpflHG9Mwe6cV5TVXvV3mlwLP/9ugAJxI6NaitS8YzYadFqxLaT9X+btZxwYXY6lHralGpKLLE7N3maZ/rP6fSHgXyHO+97SvDNzjnXMcjPD1dxxhobXalz69/fYRp0MU6t2OFzl3DBh0uEUePMKELLtuIAsb1jLRAT6AHPf+CCvRt2GJqyXPjIauPFrmFT/FPzv2MPNWajojqoz3MqNnkw99PfZQsocAKZPE+J1AcK/RZiny4q7l7qkvsKn2w/zyikGrkWctj55wGULfkZ/bAK/bf1aLasMLYsuYk3dUFzyexDWT34mzPASnAUpun50dN8KluLX4wloXguXvNJfaU4vHIJo4hzIdhiWz5JTl/xCo8lIAxlJhZYVdVrjL89zDGi89PjXO5T5bs29G7gE6RjwErgfj/GRPm58uVIVkM/ujfCYGNvtsYc9gUUiv7WCEghG0H5+fn5Phwxz5LHRzX1PKc22yzqEcilgRji7Wl0GPW1a+bV095V5uh9Od+uMHp2rz3TR4DEd0rofns3iClSXpKKaH+QG15trXrfSKk+ypmS0DDkKLYKqBuRGEwD2hoJYFx3LRvhk24=
*/