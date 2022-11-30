//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_PTR_SEQUENCE_ADAPTER_HPP
#define BOOST_PTR_CONTAINER_PTR_SEQUENCE_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif


#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/next_prior.hpp>

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{   
namespace ptr_container_detail
{    
    template
    < 
        class T, 
        class VoidPtrSeq
    >
    struct sequence_config
    {
        typedef BOOST_DEDUCED_TYPENAME remove_nullable<T>::type
                    U;
        typedef VoidPtrSeq
                    void_container_type;

        typedef BOOST_DEDUCED_TYPENAME VoidPtrSeq::allocator_type
                    allocator_type;
        
        typedef U   value_type;

        typedef void_ptr_iterator<
                        BOOST_DEDUCED_TYPENAME VoidPtrSeq::iterator, U > 
                    iterator;
       
        typedef void_ptr_iterator<
                        BOOST_DEDUCED_TYPENAME VoidPtrSeq::const_iterator, const U >
                    const_iterator;

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

        template< class Iter >
        static U* get_pointer( Iter i )
        {
            return static_cast<U*>( *i.base() );
        }
        
#else
        template< class Iter >
        static U* get_pointer( void_ptr_iterator<Iter,U> i )
        {
            return static_cast<U*>( *i.base() );
        }

        template< class Iter >
        static U* get_pointer( Iter i )
        {
            return &*i;
        }
#endif        

#if defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(__MWERKS__, <= 0x3003)

        template< class Iter >
        static const U* get_const_pointer( Iter i )
        {
            return static_cast<const U*>( *i.base() );
        }
        
#else // BOOST_NO_SFINAE

#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
        template< class Iter >
        static const U* get_const_pointer( void_ptr_iterator<Iter,U> i )
        {
            return static_cast<const U*>( *i.base() );
        }
#else // BOOST_WORKAROUND
        template< class Iter >
        static const U* get_const_pointer( void_ptr_iterator<Iter,const U> i )
        {
            return static_cast<const U*>( *i.base() );
        }
#endif // BOOST_WORKAROUND

        template< class Iter >
        static const U* get_const_pointer( Iter i )
        {
            return &*i;
        }
#endif // BOOST_NO_SFINAE

        BOOST_STATIC_CONSTANT(bool, allow_null = boost::is_nullable<T>::value );
    };
    
} // ptr_container_detail


    template< class Iterator, class T >
    inline bool is_null( void_ptr_iterator<Iterator,T> i )
    {
        return *i.base() == 0;
    }


    
    template
    < 
        class T,
        class VoidPtrSeq, 
        class CloneAllocator = heap_clone_allocator
    >
    class ptr_sequence_adapter : public 
        ptr_container_detail::reversible_ptr_container< ptr_container_detail::sequence_config<T,VoidPtrSeq>, 
                                            CloneAllocator >
    {
        typedef ptr_container_detail::reversible_ptr_container< ptr_container_detail::sequence_config<T,VoidPtrSeq>,
                                                    CloneAllocator >
             base_type;
        
        typedef ptr_sequence_adapter<T,VoidPtrSeq,CloneAllocator>                         
            this_type;

    protected:
        typedef BOOST_DEDUCED_TYPENAME base_type::scoped_deleter scoped_deleter;
         
    public:
        typedef BOOST_DEDUCED_TYPENAME base_type::value_type  value_type; 
        typedef BOOST_DEDUCED_TYPENAME base_type::reference   reference; 
        typedef BOOST_DEDUCED_TYPENAME base_type::const_reference 
                                                              const_reference;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type   auto_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::clone_allocator_type
                                                              clone_allocator_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator    iterator;          
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type   size_type;  
        typedef BOOST_DEDUCED_TYPENAME base_type::allocator_type  
                                                              allocator_type;
                
        ptr_sequence_adapter()
        { }

        template< class Allocator >
        explicit ptr_sequence_adapter( const Allocator& a )
          : base_type( a )
        { }

        template< class SizeType >
        ptr_sequence_adapter( SizeType n, 
                              ptr_container_detail::fixed_length_sequence_tag tag )
          : base_type( n, tag )
        { }

        template< class SizeType, class Allocator >
        ptr_sequence_adapter( SizeType n, const Allocator& a, 
                              ptr_container_detail::fixed_length_sequence_tag tag )
          : base_type( n, a, tag )
        { }

        template< class InputIterator >
        ptr_sequence_adapter( InputIterator first, InputIterator last )
          : base_type( first, last )
        { }

        template< class InputIterator, class Allocator >
        ptr_sequence_adapter( InputIterator first, InputIterator last,
                              const Allocator& a )
          : base_type( first, last, a )
        { }

        template< class ForwardIterator >
        ptr_sequence_adapter( ForwardIterator first,
                              ForwardIterator last,
                              ptr_container_detail::fixed_length_sequence_tag tag )
          : base_type( first, last,  tag )
        { }

        template< class SizeType, class ForwardIterator >
        ptr_sequence_adapter( SizeType n,
                              ForwardIterator first,
                              ForwardIterator last,
                              ptr_container_detail::fixed_length_sequence_tag tag )
          : base_type( n, first, last,  tag )
        { }

        ptr_sequence_adapter( const ptr_sequence_adapter& r )
          : base_type( r )
        { }
        
        template< class U >
        ptr_sequence_adapter( const ptr_sequence_adapter<U,VoidPtrSeq,CloneAllocator>& r )
          : base_type( r )
        { }
        
        ptr_sequence_adapter( const ptr_sequence_adapter& r,
                              ptr_container_detail::fixed_length_sequence_tag tag )
          : base_type( r, tag )
        { }
        
        template< class U >
        ptr_sequence_adapter( const ptr_sequence_adapter<U,VoidPtrSeq,CloneAllocator>& r,
                              ptr_container_detail::fixed_length_sequence_tag tag )
          : base_type( r, tag )
        { }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        explicit ptr_sequence_adapter( std::auto_ptr<PtrContainer> clone )
          : base_type( clone )
        { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        explicit ptr_sequence_adapter( std::unique_ptr<PtrContainer> clone )
          : base_type( std::move( clone ) )
        { }
#endif

        ptr_sequence_adapter& operator=( const ptr_sequence_adapter r )
        {
            this->swap( r );
            return *this; 
        }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        ptr_sequence_adapter& operator=( std::auto_ptr<PtrContainer> clone )
        {
            base_type::operator=( clone );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        ptr_sequence_adapter& operator=( std::unique_ptr<PtrContainer> clone )
        {
            base_type::operator=( std::move( clone ) );
            return *this;
        }
#endif

        /////////////////////////////////////////////////////////////
        // modifiers
        /////////////////////////////////////////////////////////////

        void push_back( value_type x )  // strong               
        {
            this->enforce_null_policy( x, "Null pointer in 'push_back()'" );
            auto_type ptr( x, *this );    // notrow
            this->base().push_back( x );  // strong, commit
            ptr.release();                // nothrow
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        void push_back( std::auto_ptr<U> x )
        {
            push_back( x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        void push_back( std::unique_ptr<U> x )
        {
            push_back( x.release() );
        }
#endif
        
        void push_front( value_type x )                
        {
            this->enforce_null_policy( x, "Null pointer in 'push_front()'" );
            auto_type ptr( x, *this );    // nothrow            
            this->base().push_front( x ); // strong, commit
            ptr.release();                // nothrow
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        void push_front( std::auto_ptr<U> x )
        {
            push_front( x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        void push_front( std::unique_ptr<U> x )
        {
            push_front( x.release() );
        }
#endif

        auto_type pop_back()
        {
            BOOST_ASSERT( !this->empty() && 
                          "'pop_back()' on empty container" );
            auto_type ptr( static_cast<value_type>(this->base().back()), *this );      
                                                       // nothrow
            this->base().pop_back();                   // nothrow
            return ptr_container_detail::move( ptr );  // nothrow
        }

        auto_type pop_front()
        {
            BOOST_ASSERT( !this->empty() &&
                          "'pop_front()' on empty container" ); 
            auto_type ptr( static_cast<value_type>(this->base().front()), *this ); 
                                         // nothrow 
            this->base().pop_front();    // nothrow
            return ptr_container_detail::move( ptr ); 
        }
        
        reference front()        
        { 
            BOOST_ASSERT( !this->empty() &&
                          "accessing 'front()' on empty container" );

            BOOST_ASSERT( !::boost::is_null( this->begin() ) );
            return *this->begin(); 
        }

        const_reference front() const  
        {
            return const_cast<ptr_sequence_adapter*>(this)->front();
        }

        reference back()
        {
            BOOST_ASSERT( !this->empty() &&
                          "accessing 'back()' on empty container" );
            BOOST_ASSERT( !::boost::is_null( --this->end() ) );
            return *--this->end(); 
        }

        const_reference back() const
        {
            return const_cast<ptr_sequence_adapter*>(this)->back();
        }

    public: // deque/vector inerface
        
        reference operator[]( size_type n ) // nothrow 
        {
            BOOST_ASSERT( n < this->size() );
            BOOST_ASSERT( !this->is_null( n ) );
            return *static_cast<value_type>( this->base()[n] ); 
        }
        
        const_reference operator[]( size_type n ) const // nothrow  
        { 
            BOOST_ASSERT( n < this->size() ); 
            BOOST_ASSERT( !this->is_null( n ) );
            return *static_cast<value_type>( this->base()[n] );
        }
        
        reference at( size_type n )
        {
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( n >= this->size(), bad_index, 
                                                 "'at()' out of bounds" );
            BOOST_ASSERT( !this->is_null( n ) );
            return (*this)[n];
        }
        
        const_reference at( size_type n ) const
        {
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( n >= this->size(), bad_index, 
                                                 "'at()' out of bounds" );
            BOOST_ASSERT( !this->is_null( n ) );
            return (*this)[n]; 
        }
        
    public: // vector interface
        
        size_type capacity() const
        {
            return this->base().capacity();
        }
        
        void reserve( size_type n )
        {
            this->base().reserve( n ); 
        }

        void reverse()
        {
            this->base().reverse(); 
        }

    public: // assign, insert, transfer

        // overhead: 1 heap allocation (very cheap compared to cloning)
        template< class InputIterator >
        void assign( InputIterator first, InputIterator last ) // strong
        { 
            base_type temp( first, last );
            this->swap( temp );
        }

        template< class Range >
        void assign( const Range& r ) // strong
        {
            assign( boost::begin(r), boost::end(r ) );
        }

    private:
        template< class I >
        void insert_impl( iterator before, I first, I last, std::input_iterator_tag ) // strong
        {
            ptr_sequence_adapter temp(first,last);  // strong
            transfer( before, temp );               // strong, commit
        }

        template< class I >
        void insert_impl( iterator before, I first, I last, std::forward_iterator_tag ) // strong
        {
            if( first == last ) 
                return;
            scoped_deleter sd( *this, first, last );         // strong
            this->insert_clones_and_release( sd, before );   // strong, commit 
        }

    public:

        using base_type::insert;
        
        template< class InputIterator >
        void insert( iterator before, InputIterator first, InputIterator last ) // strong
        {
            insert_impl( before, first, last, BOOST_DEDUCED_TYPENAME
                         iterator_category<InputIterator>::type() );
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
        
        template< class PtrSeqAdapter >
        void transfer( iterator before, 
                       BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator first, 
                       BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator last, 
                       PtrSeqAdapter& from ) // strong
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
            if( from.empty() )
                return;
            this->base().
                insert( before.base(), first.base(), last.base() ); // strong
            from.base().erase( first.base(), last.base() );         // nothrow
        }

        template< class PtrSeqAdapter >
        void transfer( iterator before, 
                       BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator object, 
                       PtrSeqAdapter& from ) // strong
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
            if( from.empty() )
                return;
            this->base().insert( before.base(), *object.base() ); // strong 
            from.base().erase( object.base() );                  // nothrow 
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else
        
        template< class PtrSeqAdapter, class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                      BOOST_DEDUCED_TYPENAME PtrSeqAdapter::iterator > >::type
        transfer( iterator before, const Range& r, PtrSeqAdapter& from ) // strong
        {
            transfer( before, boost::begin(r), boost::end(r), from );
        }

#endif
        template< class PtrSeqAdapter >
        void transfer( iterator before, PtrSeqAdapter& from ) // strong
        {
            BOOST_ASSERT( (void*)&from != (void*)this );
            if( from.empty() )
                return;
            this->base().
                insert( before.base(),
                        from.begin().base(), from.end().base() ); // strong
            from.base().clear();                                  // nothrow
        }

    public: // C-array support
    
        void transfer( iterator before, value_type* from, 
                       size_type size, bool delete_from = true ) // strong 
        {
            BOOST_ASSERT( from != 0 );
            if( delete_from )
            {
                BOOST_DEDUCED_TYPENAME base_type::scoped_deleter 
                    deleter( *this, from, size );                         // nothrow
                this->base().insert( before.base(), from, from + size );  // strong
                deleter.release();                                        // nothrow
            }
            else
            {
                this->base().insert( before.base(), from, from + size ); // strong
            }
        }

        value_type* c_array() // nothrow
        {
            if( this->empty() )
                return 0;
            T** res = reinterpret_cast<T**>( &this->begin().base()[0] );
            return res;
        }

    public: // null functions
         
        bool is_null( size_type idx ) const
        {
            BOOST_ASSERT( idx < this->size() );
            return this->base()[idx] == 0;
        }

    public: // resize

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
                
    public: // algorithms

        void sort( iterator first, iterator last )
        {
            sort( first, last, std::less<T>() );
        }
        
        void sort()
        {
            sort( this->begin(), this->end() );
        }

        template< class Compare >
        void sort( iterator first, iterator last, Compare comp )
        {
            BOOST_ASSERT( first <= last && "out of range sort()" );
            BOOST_ASSERT( this->begin() <= first && "out of range sort()" );
            BOOST_ASSERT( last <= this->end() && "out of range sort()" ); 
            // some static assert on the arguments of the comparison
            std::sort( first.base(), last.base(), 
                       void_ptr_indirect_fun<Compare,T>(comp) );
        }
        
        template< class Compare >
        void sort( Compare comp )
        {
            sort( this->begin(), this->end(), comp );
        }
        
        void unique( iterator first, iterator last )
        {
            unique( first, last, std::equal_to<T>() );
        }
        
        void unique()
        {
            unique( this->begin(), this->end() );
        }

    private:
        struct is_not_zero_ptr
        {
            template< class U >
            bool operator()( const U* r ) const
            {
                return r != 0;
            }
        };

    protected:
        template< class Fun, class Arg1 >
        class void_ptr_delete_if 
        {
            Fun fun;
        public:
        
            void_ptr_delete_if() : fun(Fun())
            { }
        
            void_ptr_delete_if( Fun f ) : fun(f)
            { }
        
            bool operator()( void* r ) const
            {
               BOOST_ASSERT( r != 0 );
               Arg1 arg1 = static_cast<Arg1>(r);
               if( fun( *arg1 ) )
               { 
                   clone_allocator_type::deallocate_clone( arg1 );
                   return true;
               }
               return false;
            }
        };

    private:
        void compact_and_erase_nulls( iterator first, iterator last ) // nothrow
        {
            typename base_type::ptr_iterator p = std::stable_partition( 
                                                    first.base(), 
                                                    last.base(), 
                                                    is_not_zero_ptr() );
            this->base().erase( p, this->end().base() );
            
        }

        void range_check_impl( iterator, iterator, 
                               std::bidirectional_iterator_tag )
        { /* do nothing */ }

        void range_check_impl( iterator first, iterator last,
                               std::random_access_iterator_tag )
        {
            BOOST_ASSERT( first <= last && "out of range unique()/erase_if()" );
            BOOST_ASSERT( this->begin() <= first && "out of range unique()/erase_if()" );
            BOOST_ASSERT( last <= this->end() && "out of range unique()/erase_if)(" );             
        }
        
        void range_check( iterator first, iterator last )
        {
            range_check_impl( first, last, 
                              BOOST_DEDUCED_TYPENAME iterator_category<iterator>::type() );
        }
        
    public:
        
        template< class Compare >
        void unique( iterator first, iterator last, Compare comp )
        {
            range_check(first,last);
            
            iterator prev = first;
            iterator next = first;
            ++next;
            for( ; next != last; ++next )
            {
                BOOST_ASSERT( !::boost::is_null(prev) );
                BOOST_ASSERT( !::boost::is_null(next) );
                if( comp( *prev, *next ) )
                {
                    this->remove( next ); // delete object
                    *next.base() = 0;     // mark pointer as deleted
                }
                else
                {
                    prev = next;
                }
                // ++next
            }

            compact_and_erase_nulls( first, last );
        }
        
        template< class Compare >
        void unique( Compare comp )
        {
            unique( this->begin(), this->end(), comp );
        }

        template< class Pred >
        void erase_if( iterator first, iterator last, Pred pred )
        {
            range_check(first,last);
            this->base().erase( std::remove_if( first.base(), last.base(), 
                                                void_ptr_delete_if<Pred,value_type>(pred) ),
                                last.base() );  
        }
        
        template< class Pred >
        void erase_if( Pred pred )
        {
            erase_if( this->begin(), this->end(), pred );
        }


        void merge( iterator first, iterator last, 
                    ptr_sequence_adapter& from )
        {
             merge( first, last, from, std::less<T>() );
        }
        
        template< class BinPred >
        void merge( iterator first, iterator last, 
                    ptr_sequence_adapter& from, BinPred pred )
        {
            void_ptr_indirect_fun<BinPred,T>  bin_pred(pred);
            size_type                         current_size = this->size(); 
            this->transfer( this->end(), first, last, from );
            typename base_type::ptr_iterator middle = this->begin().base();
            std::advance(middle,current_size); 
            std::inplace_merge( this->begin().base(),
                                middle,
                                this->end().base(),
                                bin_pred );
        }
        
        void merge( ptr_sequence_adapter& r )
        {
            merge( r, std::less<T>() );
            BOOST_ASSERT( r.empty() );
        }
        
        template< class BinPred >
        void merge( ptr_sequence_adapter& r, BinPred pred )
        {
            merge( r.begin(), r.end(), r, pred );
            BOOST_ASSERT( r.empty() );    
        }
        
    };


} // namespace 'boost'  

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_sequence_adapter.hpp
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
*/