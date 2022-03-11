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
HOh9XYzjN44Dg0xAdLNSDQIP3Soibzj3J+fn59+G5x7zVuUu/OYHgdDx2Otr7xq842PIo0On6B7je79vT/TAcmL4jzZ1DRTb7c5CDQ/o7zvfiltn7xFUaVid4SFPr1za9/IEEh7/ofqklZlYvBDMjPOmyfDJO5z7oJuzFLsgDNHMbaZ/v/fBYcj1B0nWRPZOFKxTkYHbre+EFgBefdVbJi2odaAMuLJs7qAXjg1Afcn1r4pderfELpXXemBthEK3DfIuJeNfgdmygBGW7ynfApQE+7GNlrJhVNHhSb+vwEIUFho9axPfo3L1fNsbZfN/AHQbxWn40Agzeo+HxH/dzffMTnmDKKrD1++FekH6x4RLb5afusMHA3I7sSMEhB6wnMDX5TUubFjiYR9BCfJyDPkvP0R7BkLukjzN4ZVl68rdgKFy0ipPO3xFiO8ggG/hTMShfyZvu4Dx444u95s4RZVOrStnrNwMTrgrWUAq3smMev26Bl6VFIjnl5Y2ayXZcV6+DYSU87x4gSk8Pj7mi46OFpVivX15/coton62QABiBkxjdOyNrG4bFkaq0d//jBUvyAokD0Hbv8J+llNoTz3Dub1Yy0wEthGlTi8mOs0FcdRySlcz6f28zHs9T3qxc1m410lQ97E5j7OPVhrzGfVFUno1aM1dI0YfPEG4wlB1Wkxys0sQCGb7AnzQ7e/EdhDEiZKjlHb9DnyQiHySjGQ8BvQ5S1iG+uFGXWmkKUMhw+foPmtDQMItKa0TQW9RBoWlutOJ73NzPM2pg/E7Lofd+3z6Kn895XibiqmvbVw9DOMXbV7fFTH5KYer8Jv2AwGqzIrKvbSXLgl+HTj3XEvEmyoGIyeGNHTsZk5HluysnSXc5Xt+tYvtmIvuXJVgApTwevCiHOt1iKl3GJ4oeK0YEnXuSFNclpBJE/4gFZ7cBGfnuSKpFajkwq4A3QBRs7nza3eLKgFo+tP465fTVGenwsT5HWqRBr+RQ4bRiwYssz+uE5l34rqYEMn8J4hrYaUpQhUkefWVc/fv9hGxuzq5NucfDmlvyRqRuH7hQ4VEL1AlMyJ6X4kLbCm7P5U14T5Be5RqOpG+EZZzD4Ci9bPOmyZT3Fo5JPUXVCFRn762KZOhnIoNSvskEdyUwjZD2IGSq86CQNuE778zs0L9c/5acXi4WZpSGVCNZI3rXU5kALOlAC1hrPavELJZMfbkedW3aUuyORPrA+UUGj+8bmqDAl3au15IH8cLhwOc3MzKh1jGV/HqNZ23w44Jty1Jb9M+0x/ewaag16ARPuHyfUngUki/KRcpIngf+7xGoBEkiEzC2VE/Z4odxj6PmUnEOXISP8MSz+CI6+j3x7//UjVLoaOlF+GW+aly/IS2HPUbm4rkmL91cbXfCjcjCw5044uU0CnXy05Pf+J+F+1uDSmwwBDE6MhIsfDtbW0JYTf7/j2tqvnZT3iXcwwr4+yOSuKP89A7nL0FXDn7sSaSGAKuAkjftdsxky0EF407izE1EdLrxjUWLYdKTZnTLF6u3SlE3WxvFecoMsZRViWPMCaJmuWJdEjaxRf66+g2Qc3tIXB7KvCky9f5n+f79wSNAr8CH/wgCd4qh5zCojGXmmC2GOCDJA/BnqxyJujgcPniehthiGCjcHdOoKEyfcnuPVEzSg367trnliv2sFtw1FISjsv29rQu0SqP9VEjqHdpucra4fsSfBCH+9so7JZx+IvB0WiRbMUFldkPj+TXXAc3PCbbDICF3H04rz/1Evt8G9oB+5QM5TyHRUrDqXC0KqjvT8aNbOU8coAGtV4lg+MFT9+HtNKIjpoEY5bh4RHZSCurH5CR84sCytm4VfOTsZVz1qRv3wKOTraHz8BJcV5HR0esU4SlGrkyOK7f9O+Y12WC5pxQZdJsM09b1XktclUuf7v6/gvWmLkPszjNWLqlehSQaSldQ9QX0sD+wp9kVEVyvQAMqrmAJNqvhH/7SsgtuxdTJsxf8k5aCdCY/6yL8Gg+fCL5v2xaUNVNH/IxgKHyQfsbLzZpV6XRBjpkY9pnqaj0bc3hPxHz6DV3isq0SL82nm9Aze2Py7t6dg4R0hcNPQEF7H/LSNb3gnzBXy7wjXHA8QlCMHFTrshZbSe+wDdQP1dlZbZFNnvYNw43oDQccdF0dCrUR3aZiu0PyDVyh8/Z2CVg+YWxUGqnAGEPmCWidRCWfphpMA+yQZU94RS1e6SXKahppYCkpZaIjnUYAOWxq8bvq7MMTtZzi/3q2HpKG3eIexOAyD4EmHt+npHo40Auoi+l/K80h09i3f4Lzbl4Lz4+PtaR0dEc8M3VqewcmiFih9javMk3DC0h5XrQ60XztGy1acu+5vnJ/I1MZxYNYC74z4bS7oesyKVQDzdIAhUcMB+G629gljt1s/+e666sd8Y+ne2VhPzx7wCqgKR1InkneuWe7P/4Mo8kzrJO4sGG5xffsR7bNqHzgB/i6qMd2U60wm6FuwSCXALGo6OU2N1USLL0BSh9yAVQYkTdPUV4ivpnHvh3TWZjhVuc49xHldydfz7YMBrxM/nAl+YycOx2UInjxwD+35aUw8ynaND1yDfclrk7wslqFMRz6JNhhDRJQ488xMbs2ZE1gWoRIJssQe+/wYnGZAcBNRaf2LF2nslpE/qWSoqVBPWpKG54iapVBl3TC0aHez7tH7skGykxz8Ymllm7YY0flEYpcZsghH/I3t7e63DQXbMo0zuiXom1xqJ2fA2OPW5BwtDtd7mVeSaJ/meE3KcyoLmJbEJb6c6PiwfLaCoUPjPRdZrqZ6c3pzhYYLQ0KyF/MZ45SfjhvyRa7p20W5GfS9RO2//WdTm0robOqLPWWVwq2+fIgh8SztHftz5Ro5SmHIatcktTKgC+WtewM0+9pzpj8fHg0zokK9gN+h8xam478Pr8MgSUbJlnZuJOUV/CgOM1oPEJIomBm0FKLE6eZbt5vXr8V89yqfC3W4Tkl8N4Luso8cA/ilaBb7f9o2OKge5jrfBxZ3Y0nSk1+5xLbbV+tWVzT/CLXtskIupYuhoXdqx+zLTRK12bDrlkIigtnWdyxoS5rYJODmn9vIquHaOmu3l8qy7Lt1gCseo1MyVxWDxTdJJsBJRqfaEaXuXh5naaOTc3ZyHWWoENjAo3fIcikM6zIkdfLbrAk4HVSHGa2ZCS868kM9Zovd5syQatbLdHMMlA0gaBlWRR+ZMVC3kkmjYu9KijNKLtTaRbJ+aKsH+8ZZyQRCvB9UEx17JWzmbQPo0GuJ0plh46/m0r3vtUJvpGDkXHIh/49hXxULx1o9D3CzmGXsdOQ7KvNmXs2qPdNLWn28Y2my0u24s9N8yC7xRbyQwOq2J/koigvtQANaRy4aJvjnvOMeYsB36i2xDPM9hK284VvRsk5jAaKn4kMdDUf/4Oqo+H0M1cc+yYpJ1XPHJHyB8/qXXW3/b/1RlQm+yHGGwdK2n4BmWab/i902BVPRgFc+dpHuJ1EPiTJ46I+SX+XPfjEy3vji83d0XeZ6VrTRtjWz7iS2DvEY+TOxYMgboAZG9NnJx+QVNmF5tvf0Ii7MOR7z98CDvNCoD3tcNm30gh/FiAlE4TGVGjHK6zVXcyx9Xm/Sr8IHWSsK8r2/XlJGnpS/qsWWalsA5acTofGuZzub3SLtQXekdtqKvoMn3sE7xDE40cgFneIIASHBU8YcHYCWa7y2wKSTg2mZcir9/MEE64q6yo1/qis31vi2tSA2CK8zYNcxX5JHVCKQM32vHA82UJ9fozdHOOjUVYJ77it87NTjA0pPyI6Pxdm/6TWUi/f4NejSzi08eVu6XgwRIuvsT+0bt0tkX0trp0GULvQfD3H80+vHTerarLx0bRsjyjq6Mx1sx1Unn/54mBUAy3mIschVPZm7HYuVuMZL/w0bYP9kx0PlCGdVBYFjssYS5wQXEbaO/XFtnXPDg46PP8+fN7vjn03cb8WmQPAA+4IrBSVZOEnTwC1Ovgo5JBhdUceLc8WK6xPb4+qNee84OKOKfgQijQVbl5htzouc+mobSm7xJ1ceQKt8al/F+jOx775316kMMAxZ0yHDdjuHPDSUIrhsbHQWtlb2J0Va1b9Yd7Y/JJusuHxcByofN0d0iaN5BF5Fu9z/u4u3m9KL59Hvmc9iCg6yX24a2PAQYuCn6YZK1hntkJ678IxvYAmULuZB+Gn+nW5LW7S9LS2J9EqLvAvEvN720NyxGBOQ02bJ/+vEa75ftgW3h4E7xwOuzu+BPjeUVJ278qfj9Ie/ZUNrNEV4t6ST7ktoX4/rSo7jMGd/i0XmIe75ibkhRYmBobg/d3dxtX1o5WckCnCU7Rfb29rXfC8LmygKWFCS/4/u/RLhjSt8Jp+6M1Hz4XroJlfEjptkvdWB1Py3+yjGfXXWFye7nN9qGvmUN0hZweBewXgnCAOshCufw1UzbDo2gCdXPJikji8gR5GCrm2Xf7yeQN5BnAUV0TBnQDMLbHinoTDKWR+SQMBhtpHnqoLxlAS/zniX6cl8ej37Of92XnJM93y4ZQceE5Uzn4qaiHwQeeZTlUoDJdVRVN2yRnyvnk7H/YKR8rKHxrqWJPgGp8voQiQN8SpJ/aWpHLt3+s2y+ZKs2e8f7xwev6CI1ZvvluJESfHRPjjvCQ2QnuXloCwZFovxw0WgZZdcYmcYXEoQgmYDrnFgUOFmA3J1sA4NxfGV304msgwGoJoFUnq/nTKk4ex7MwewIVETPKl4/Pc7BQPHKaUD5qoHea0C9SdoKFicLp3s8zTts7ambTBZ99p6R5RszO9fzBXmLQGwnGCO7zgPIsKEhf1kMSbMIc6PnZ7JPFtd9WDlUgMjc5ObnisrFp9KTtSd/T8K5TH1TQR3p+U4eb3cJ42K5gAgNbm0oNBS/mC8/RB5GKv0ZzDdsvePMBEfTl2R6gy4qPMnKA6sNA0vyAX1QBDnzWwTPs8i0Epb2xqCCDRKbmJ5i+P3nc1kyDBQ2FLwO4ypKk9ghbxr/DMmVWlVnnoqmbVlBBuMGmJ2Y92D1C2HQB6u/gL9bmwRvXgogVTckfUCL7JXh3Y2CAOhYqSqAWIJCRmia7VGI1/PPyQNTC4VY3Nswtt7nqcR2KVjt/C6t5/rEAwrIBOyY7yu2flajPLVSGpoT9tgh5GE7c87ajP5pMQUWXUrsTwMnOS7moLxXZo7Gkhlxcdf/QpziC3vQRAI7//Zu8tjaKdfnBDonE/2lrg040eew4ytycdI39BRIaEaZcsF20PjCYnVSamkgDwMlrkxf0Z/5YZEizQGalyNvQ76qZDUPGQ5yoqBqBbuxMiSWQUJlq0id/+Pqla2iJ1ha1mJsIt37nlKjNhWYULZe8u1CwuTa//gIyrtlqLb9DAqsnDYuc/W+Bheibcf3D8O178y0eDwqltxFTtxhvQvBLXAlOTvng8YEGKAJfCt03n4A9Pq//cGTgZMTqQHuUS7NssGuIPGBAe8VgwbCqOHH4/41iBCMhsrU/nlCh7PyDLnk64G0NMeaUvT+KNIyT40GkKoBzzomWDjdV8cAUw8YfG9eYNXSagKjI2njWdHtycrL1RNiuceysWbzvaazKOWhkZGTSSZdDmnh/xXpe52mbCmiQ5FrCiaoOym5edAeNm6v0vbmLSd7r9peGNzPsh+PEW350vzPevxH6N6yrlTb9j3M/6WJQ50k2d+RK6FnjMipIuuT9pUKb4mj/Uvh2Oc5h4FTeqbJKweOYoHcZt1tBoXl5EquNLiy7HGh6LV0vgL63CYTpYLvIjTkWZrXRxr3+2r8KL72mYXHNs79nZgW3ddBbYE9qZXTxNDQyJ6fQfmlWBwuuS9jwA4ts72qllirqZdAVvzCmee6YQE0fjCqxfMpKptBoxYo7oShPlyZS5HIyHUX49iN1LqMGkUZn+NbW1h7g8V2bGcoNiWZiZMyRgV57XkOQbehScEDTIVGyeWEkisDIp9U8DGtstVBraoR8LGCIR+keGmKeeqIIDjpixR6fvOQIBrHrtxC97a1wNWzgFPYkcY8HF7xyB6lZt+4SQrSyd2MXvkNL3p3LKzYDMoQo8tinUpsuZTwNrniwvvzat/Qt2desenUCbohcP3lKD0iv30RrAZSvTQ70A7qPJzs6KIVK12uMlbBtEff6O+Z6aqNZeoi3bwqghB9oGEughHE7jFkLY5OFEmbhZ7osUd/q+6Nn2YQl7pdSscfgOuYar6y2cQ35Qh9vGz0uwrcXhHaqpMq7VQ6ffmdmt9rkFlfpfHs/8qnW04zuBMPHqutv7719+vZpelGC7jrbp6fZtgnq35Rr3lIMPPN7mkuToKCtFPWW9MWzj0VZuglq2splb8lLn3kV5YgkqEwqxSXZTSoYD5BOqiy8Jdl7alaUiUowd/+GSgxwj3qUIC+kFDbwyT0s69lOv597UExCtO13U46qxKHNh01q5lwuCaABk02uTeczCgz9Gb9ffKtGgJoMG+u3+P6xfvi33KRATtakQC442608PslfAR99A8I8w9BiWM9eYEQxFmdPMFk3YTesBOkiqbIborPBuwaV1Bfq4aOjo2IA9JPR49OttKc7s7MzMzLiIiI0d020YnBAGyqjX1rhQsrSABgo3XiGdxIXno7VzK2PIlHjNbycpvnXTJCafUWgi66a1CocxMlhy2N9sZjgsBAnsvihl0BjMwwpr1VEr2bdpkUHByRHypSoPXf3VosCSagBrIq6IqKzUbf8tcIkto/EFl/6IfIFkT93QBLSgSXyP1ujkIDpvT0cGDU7jt7Dcf16tFuMRuv/d2ymUBrkl3tnVsO3sWJatrbH9pbL/zU56B+Cv0/AumKocqxnv8Y4O49+SB03+bdORVdXrDZvmh9PzIH9y4PXswc4ePSuxeWDoXMTQ3S2zyz0WHA04cBKGwrFcf735Auy9XxUYBpIPUBWHJAgqiSa459kKgaKEIv9WUNcBu7Y/hjPYYt8OUfh0pO46hwx/Vk1y4rr23CO65wPJ8+/APdONIfsIFPoBFaLQXG9NT2EpdNvxod+gbxx3Er70jOSJOuT1WhvVnWV8fGGxIUM70LV7BTZm+ygi5wg8dw7kx/AgGmPhC2YpwJ80hP9chMXQJM2byIT/VjrLRxsV+yLLmOnYXcvC15PRQyKEKrpXHCrT7JzmYfHOPBpc4iIlV10FnB97ru2/7l6k/459VwYeNbyLeefU7drdJW2jk7uqevdD6+B38QPEN4923ei6nxnH3NRE8DWZud4224QuxP4sgbJPr8b+6z2B7dTwTpJFW9OkGVV8gPyhbhXIxRK+9JU9guxSgfAorBjZXAaaDIezClsLZBRg3PdbqSzN/EU81HQYM0jqct8tVRUbAfQGmJXe891zVquI1rls5+D0sFCoy7Jy9ExN2BtqyJ87DS8DJpUgPWeCPhNWhFa1L45HZAT6ZVLWm+k0hvAOciiMgMl3ny2m/jkVzindnS3TYchbgk3fevswC/YlJV0SlmlD2nZBFqYmGRmbW3LdM1LwwbTdLW13QFQuT6nPcL6PqVjpremTVoyrp9Q9yYrAgzxXZK/E2TYzKsD8CFirQd9D8hOu7WW+ZUYvDl7D0MNo+kfH5qXvD3Vu7QbBI/etQJGRQ7SkTqIC8btbfzgSjn+Jd8HPcG+KqqsDAPzX8+2mWivy2KGMe+nYZHNIC308/2VSJ27ygv2eS+UGl6VvgASvsx0lRqL6TWl3q95H3XJMxnD/VYwj23iy6GY9GSBVwxOwtclKxwT/16laNbDAmK+dUuN+2Uv8QrJinLN2VsdxS5vHDzaurnG4wMCzS1c+vGC8xpllxlvoRKJMmyQqcpwnlQLRfkYCh47RGyoMBePefU1JvDrbVzxMJE3p3oL0xoq6ExsHktbgrIinybmQX8OZ/IaXBlOaf2njp54wzadGEdrjKpNke1ZgsEdecdYp1pbc5ij0fBinHutDrrYrtefy7nH7uclmTLWrjdgApbuB0//jYgZ9BRWe4IlS4rpf/+KjVMlfvqN9L9Bkq9u3WZej73v2u0/Yb0Zrtz+kIAIncZqo+NjYvwf09OjG8MlkT7xstB+85rFu2J9awlm9s7VTgmaVnRZGVza9n+tq91aXLUnD3G/q7f5u4S0IrDZCe7jsumJP+4JqojWdP2XtZkMN6HzOC+rftKCtuhw4pA3BXjwT932/fxatvvLyoyolEnqQZSY0ehCzkVr+V52+ZVQH5Jlyh8kijCz83aEq6NcrJYaNLFFcwo4kxJoh9rRXZ3CZDzBRt75D5HeE7ttnB1NcVpCqoOSflbib8SXr9Vs13NQtRXEFI3ssb2XqL3QraNLqj/UycmpOhyrToJOmxN88ezZ1p+VlRXncoLRUunnwTdGZj4pBgYL2W8qzduCM5a4y/3WAoYhh0i3kx7JBFoUZZmNuYJqh7wnLUneT9Qr4xpAvtAAK3mcXJ0dcaE0130WDKMnneOEUdHG7N6EHke/sYwTZACZLIUoX52+STuumggw+a23ppSoNxHwLoi277zCob9eCNmQJzEUHOVJpqbNx/1GiJ1rJQLFwKld+GgOc/Zv68murVgdj1nA6GkCJiVDfebTpnr43S1T/AC00efj0x2mwZWz4+PPfjnv4zf/eezTTVK0o1s5wLRBaKBlkXV/aKaPsu2AX8wfqazSTlgSZRp3/ZSVRhWTL3FMyfgNUCjO94DvCbvDyGQen2r0HymWhbOLctL7hAvRMbvcKfX+5wzwCszl418KJr/JuWiOFsfVjB/+Ow2L9YPTXojrT9saaaVbKac/xo4MY0f6Y0TZRRcehCCfD0NshS558SSmAUcFQ2MgoNDs/rlxOjqQmZn5BgpAp1PcTZt1EHOBIribdXQ5+SBj/jRxjT7bwbij2eo+Y86bbpIFJmGqptsXSoet1JexU5SNh/zdRyYRgxGEJdE25Ak0X3unLUXEFca/58t7/KAbmZcQ2WEYz1A9u4srbOiTLFFc5LrTemuZn19ymkCzgG69i/2Ki83/TFHvB/nWJ30a4csdLqM0dGYinY3Cvw5s5v7uzTVjztUt01v2jAAjpA6kpdslMyOjVXrJDw7xr1WcN1n5+/dZm90Fq/9Jx39598xfsgkgeufIMHezE6cWkzPKHVnW3uQpK0Mhlu0tNJsbUkr3KzbvNTtDfSR7ybs=
*/