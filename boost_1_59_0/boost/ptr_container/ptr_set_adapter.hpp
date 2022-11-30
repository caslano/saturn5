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

#ifndef BOOST_PTR_CONTAINER_PTR_SET_ADAPTER_HPP
#define BOOST_PTR_CONTAINER_PTR_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/detail/associative_ptr_container.hpp>
#include <boost/ptr_container/detail/meta_functions.hpp>
#include <boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/range/iterator_range.hpp>

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
        class Key,
        class VoidPtrSet,
        bool  Ordered
    >
    struct set_config
    {
       typedef VoidPtrSet 
                    void_container_type;

       typedef BOOST_DEDUCED_TYPENAME VoidPtrSet::allocator_type 
                    allocator_type;

       typedef Key  value_type;

       typedef value_type 
                    key_type;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::eval_if_c<Ordered, 
                          select_value_compare<VoidPtrSet>, 
                          mpl::identity<void> >::type
                    value_compare;

       typedef value_compare 
                    key_compare;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::eval_if_c<Ordered,
                          mpl::identity<void>,
                          select_hasher<VoidPtrSet> >::type
                    hasher;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::eval_if_c<Ordered,
                          mpl::identity<void>,
                          select_key_equal<VoidPtrSet> >::type
                    key_equal;

       typedef BOOST_DEDUCED_TYPENAME 
           mpl::if_c<Ordered,
                     ordered_associative_container_tag,
                     unordered_associative_container_tag>::type
                    container_type;

       typedef void_ptr_iterator<
                       BOOST_DEDUCED_TYPENAME VoidPtrSet::iterator, Key > 
                    iterator;

       typedef void_ptr_iterator<
                        BOOST_DEDUCED_TYPENAME VoidPtrSet::const_iterator, const Key >
                    const_iterator;

       typedef void_ptr_iterator<
           BOOST_DEDUCED_TYPENAME 
             mpl::eval_if_c<Ordered, 
                            select_iterator<VoidPtrSet>,
                            select_local_iterator<VoidPtrSet> >::type,
             Key >
                    local_iterator;

       typedef void_ptr_iterator<
           BOOST_DEDUCED_TYPENAME 
             mpl::eval_if_c<Ordered, 
                            select_iterator<VoidPtrSet>,
                            select_const_local_iterator<VoidPtrSet> >::type,
             const Key >
                    const_local_iterator;           
       
       template< class Iter >
       static Key* get_pointer( Iter i )
       {
           return static_cast<Key*>( *i.base() );
       }

       template< class Iter >
       static const Key* get_const_pointer( Iter i )
       {
           return static_cast<const Key*>( *i.base() );
       }

       BOOST_STATIC_CONSTANT(bool, allow_null = false );
    };

 
    
    template
    < 
        class Key,
        class VoidPtrSet, 
        class CloneAllocator = heap_clone_allocator,
        bool  Ordered        = true
    >
    class ptr_set_adapter_base 
        : public ptr_container_detail::associative_ptr_container< set_config<Key,VoidPtrSet,Ordered>,
                                                      CloneAllocator >
    {
        typedef ptr_container_detail::associative_ptr_container< set_config<Key,VoidPtrSet,Ordered>,
                                                     CloneAllocator >
              base_type;
    public:  
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator 
                      iterator;
        typedef BOOST_DEDUCED_TYPENAME base_type::const_iterator 
                      const_iterator;
        typedef Key   key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                      size_type;

    public:
        ptr_set_adapter_base() 
        { }

        template< class SizeType >
        ptr_set_adapter_base( SizeType n, 
                              ptr_container_detail::unordered_associative_container_tag tag )
          : base_type( n, tag )
        { }
                
        template< class Compare, class Allocator >
        ptr_set_adapter_base( const Compare& comp,
                              const Allocator& a ) 
         : base_type( comp, a ) 
        { }

        template< class Hash, class Pred, class Allocator >
        ptr_set_adapter_base( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }

        template< class InputIterator, class Compare, class Allocator >
        ptr_set_adapter_base( InputIterator first, InputIterator last,
                              const Compare& comp,
                              const Allocator& a ) 
         : base_type( first, last, comp, a ) 
        { }

        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_set_adapter_base( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }
               
        template< class U, class Set, class CA, bool b >
        ptr_set_adapter_base( const ptr_set_adapter_base<U,Set,CA,b>& r )
          : base_type( r )
        { }

        ptr_set_adapter_base( const ptr_set_adapter_base& r )
          : base_type( r )
        { }
                
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        explicit ptr_set_adapter_base( std::auto_ptr<PtrContainer> clone )
         : base_type( clone )
        { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        explicit ptr_set_adapter_base( std::unique_ptr<PtrContainer> clone )
         : base_type( std::move( clone ) )
        { }
#endif
        
        ptr_set_adapter_base& operator=( ptr_set_adapter_base r ) 
        {
            this->swap( r );
            return *this;
        }
        
#ifndef BOOST_NO_AUTO_PTR
        template< typename PtrContainer >
        ptr_set_adapter_base& operator=( std::auto_ptr<PtrContainer> clone )
        {
            base_type::operator=( clone );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< typename PtrContainer >
        ptr_set_adapter_base& operator=( std::unique_ptr<PtrContainer> clone )
        {
            base_type::operator=( std::move( clone ) );
            return *this;
        }
#endif

        using base_type::erase;
        
        size_type erase( const key_type& x ) // nothrow
        {
            key_type* key = const_cast<key_type*>(&x);
            iterator i( this->base().find( key ) );       
            if( i == this->end() )                                  // nothrow
                return 0u;                                          // nothrow
            key = static_cast<key_type*>(*i.base());                // nothrow
            size_type res = this->base().erase( key );              // nothrow 
            this->remove( key );                                    // nothrow
            return res;
        }


        iterator find( const key_type& x )                                                
        {                                                                            
            return iterator( this->base().
                             find( const_cast<key_type*>(&x) ) );            
        }                                                                            

        const_iterator find( const key_type& x ) const                                    
        {                                                                            
            return const_iterator( this->base().
                                   find( const_cast<key_type*>(&x) ) );                  
        }                                                                            

        size_type count( const key_type& x ) const                                        
        {                                                                            
            return this->base().count( const_cast<key_type*>(&x) );                      
        }                                                                            
                                                                                     
        iterator lower_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().
                             lower_bound( const_cast<key_type*>(&x) ) );                   
        }                                                                            
                                                                                     
        const_iterator lower_bound( const key_type& x ) const                             
        {                                                                            
            return const_iterator( this->base().
                                   lower_bound( const_cast<key_type*>(&x) ) );       
        }                                                                            
                                                                                     
        iterator upper_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().
                             upper_bound( const_cast<key_type*>(&x) ) );           
        }                                                                            
                                                                                     
        const_iterator upper_bound( const key_type& x ) const                             
        {                                                                            
            return const_iterator( this->base().
                                   upper_bound( const_cast<key_type*>(&x) ) );             
        }                                                                            
                                                                                     
        iterator_range<iterator> equal_range( const key_type& x )                    
        {                                                                            
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,
                      BOOST_DEDUCED_TYPENAME base_type::ptr_iterator> 
                p = this->base().
                equal_range( const_cast<key_type*>(&x) );   
            return make_iterator_range( iterator( p.first ), 
                                        iterator( p.second ) );      
        }                                                                            
                                                                                     
        iterator_range<const_iterator> equal_range( const key_type& x ) const  
        {                                                                            
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_const_iterator,
                      BOOST_DEDUCED_TYPENAME base_type::ptr_const_iterator> 
                p = this->base().
                equal_range( const_cast<key_type*>(&x) ); 
            return make_iterator_range( const_iterator( p.first ), 
                                        const_iterator( p.second ) );    
        }    

    protected:
        size_type bucket( const key_type& key ) const
        {
            return this->base().bucket( const_cast<key_type*>(&key) );
        }
    };

} // ptr_container_detail

    /////////////////////////////////////////////////////////////////////////
    // ptr_set_adapter
    /////////////////////////////////////////////////////////////////////////
  
    template
    <
        class Key,
        class VoidPtrSet, 
        class CloneAllocator = heap_clone_allocator,
        bool  Ordered        = true
    >
    class ptr_set_adapter : 
        public ptr_container_detail::ptr_set_adapter_base<Key,VoidPtrSet,CloneAllocator,Ordered>
    {
        typedef ptr_container_detail::ptr_set_adapter_base<Key,VoidPtrSet,CloneAllocator,Ordered> 
            base_type;
    
    public: // typedefs
       
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator
                     iterator;                 
        typedef BOOST_DEDUCED_TYPENAME base_type::const_iterator
                     const_iterator;                 
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                     size_type;    
        typedef Key  key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type
                     auto_type;
        typedef BOOST_DEDUCED_TYPENAME VoidPtrSet::allocator_type
                     allocator_type;        
    private:
        
        template< typename II >                                               
        void set_basic_clone_and_insert( II first, II last ) // basic                 
        {                                                                     
            while( first != last )                                            
            {           
                if( this->find( *first ) == this->end() )
                    insert( this->null_policy_allocate_clone_from_iterator( first ) ); // strong, commit
                ++first;                                                      
            }                                                                 
        }                         

    public:
        ptr_set_adapter()
        { }

        template< class SizeType >
        ptr_set_adapter( SizeType n, 
                         ptr_container_detail::unordered_associative_container_tag tag )
          : base_type( n, tag )
        { }
        
        template< class Comp >
        explicit ptr_set_adapter( const Comp& comp,
                                  const allocator_type& a ) 
          : base_type( comp, a ) 
        {
            BOOST_ASSERT( this->empty() ); 
        }

        template< class SizeType, class Hash, class Pred, class Allocator >
        ptr_set_adapter( SizeType n,
                         const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
         : base_type( n, hash, pred, a )
        { }
        
        template< class Hash, class Pred, class Allocator >
        ptr_set_adapter( const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
         : base_type( hash, pred, a )
        { }

        template< class InputIterator >
        ptr_set_adapter( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }

        template< class InputIterator, class Compare, class Allocator >
        ptr_set_adapter( InputIterator first, InputIterator last, 
                         const Compare& comp,
                         const Allocator a = Allocator() )
          : base_type( comp, a )
        {
            BOOST_ASSERT( this->empty() );
            set_basic_clone_and_insert( first, last );
        }

        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_set_adapter( InputIterator first, InputIterator last,
                         const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
          : base_type( first, last, hash, pred, a )
        { }

        explicit ptr_set_adapter( const ptr_set_adapter& r )
          : base_type( r )
        { }

        template< class U, class Set, class CA, bool b >
        explicit ptr_set_adapter( const ptr_set_adapter<U,Set,CA,b>& r )
          : base_type( r )
        { }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        explicit ptr_set_adapter( std::auto_ptr<PtrContainer> clone )
         : base_type( clone )
        { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        explicit ptr_set_adapter( std::unique_ptr<PtrContainer> clone )
         : base_type( std::move( clone ) )
        { }
#endif

        template< class U, class Set, class CA, bool b >
        ptr_set_adapter& operator=( const ptr_set_adapter<U,Set,CA,b>& r ) 
        {
            base_type::operator=( r );
            return *this;
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        void operator=( std::auto_ptr<T> r )
        {
            base_type::operator=( r );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        void operator=( std::unique_ptr<T> r )
        {
            base_type::operator=( std::move( r ) );
        }
#endif

        std::pair<iterator,bool> insert( key_type* x ) // strong                      
        {       
            this->enforce_null_policy( x, "Null pointer in 'ptr_set::insert()'" );
            
            auto_type ptr( x, *this );                                
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,bool>
                 res = this->base().insert( x );       
            if( res.second )                                                 
                ptr.release();                                                  
            return std::make_pair( iterator( res.first ), res.second );     
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        std::pair<iterator,bool> insert( std::auto_ptr<U> x )
        {
            return insert( x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        std::pair<iterator,bool> insert( std::unique_ptr<U> x )
        {
            return insert( x.release() );
        }
#endif

        
        iterator insert( iterator where, key_type* x ) // strong
        {
            this->enforce_null_policy( x, "Null pointer in 'ptr_set::insert()'" );

            auto_type ptr( x, *this );                                
            BOOST_DEDUCED_TYPENAME base_type::ptr_iterator 
                res = this->base().insert( where.base(), x );
            if( *res == x )                                                 
                ptr.release();                                                  
            return iterator( res);
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator insert( iterator where, std::auto_ptr<U> x )
        {
            return insert( where, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator insert( iterator where, std::unique_ptr<U> x )
        {
            return insert( where, x.release() );
        }
#endif
        
        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            set_basic_clone_and_insert( first, last );
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else    
        
        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        insert( const Range& r )
        {
            insert( boost::begin(r), boost::end(r) );
        }

#endif        

        template< class PtrSetAdapter >
        bool transfer( BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator object, 
                       PtrSetAdapter& from ) // strong
        {
            return this->single_transfer( object, from );
        }

        template< class PtrSetAdapter >
        size_type 
        transfer( BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator first, 
                  BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator last, 
                  PtrSetAdapter& from ) // basic
        {
            return this->single_transfer( first, last, from );
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else    

        template< class PtrSetAdapter, class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                            BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator >,
                                                            size_type >::type
        transfer( const Range& r, PtrSetAdapter& from ) // basic
        {
            return transfer( boost::begin(r), boost::end(r), from );
        }

#endif

        template< class PtrSetAdapter >
        size_type transfer( PtrSetAdapter& from ) // basic
        {
            return transfer( from.begin(), from.end(), from );
        }

    };
    
    /////////////////////////////////////////////////////////////////////////
    // ptr_multiset_adapter
    /////////////////////////////////////////////////////////////////////////

    template
    < 
        class Key,
        class VoidPtrMultiSet, 
        class CloneAllocator = heap_clone_allocator,
        bool Ordered         = true 
    >
    class ptr_multiset_adapter : 
        public ptr_container_detail::ptr_set_adapter_base<Key,VoidPtrMultiSet,CloneAllocator,Ordered>
    {
         typedef ptr_container_detail::ptr_set_adapter_base<Key,VoidPtrMultiSet,CloneAllocator,Ordered> base_type;
    
    public: // typedefs
    
        typedef BOOST_DEDUCED_TYPENAME base_type::iterator   
                       iterator;          
        typedef BOOST_DEDUCED_TYPENAME base_type::size_type
                       size_type;
        typedef Key    key_type;
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type
                       auto_type;
        typedef BOOST_DEDUCED_TYPENAME VoidPtrMultiSet::allocator_type
                       allocator_type;        
    private:
        template< typename II >                                               
        void set_basic_clone_and_insert( II first, II last ) // basic                 
        {               
            while( first != last )                                            
            {           
                insert( this->null_policy_allocate_clone_from_iterator( first ) ); // strong, commit                              
                ++first;                                                     
            }                                                                 
        }                         
    
    public:
        ptr_multiset_adapter()
        { }

        template< class SizeType >
        ptr_multiset_adapter( SizeType n, 
                              ptr_container_detail::unordered_associative_container_tag tag )
          : base_type( n, tag )
        { }

        template< class Comp >
        explicit ptr_multiset_adapter( const Comp& comp,
                                       const allocator_type& a )
        : base_type( comp, a ) 
        { }

        template< class Hash, class Pred, class Allocator >
        ptr_multiset_adapter( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }

        template< class InputIterator >
        ptr_multiset_adapter( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }
        
        template< class InputIterator, class Comp >
        ptr_multiset_adapter( InputIterator first, InputIterator last,
                              const Comp& comp,
                              const allocator_type& a = allocator_type() )
        : base_type( comp, a ) 
        {
            set_basic_clone_and_insert( first, last );
        }

        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_multiset_adapter( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }
                
        template< class U, class Set, class CA, bool b >
        explicit ptr_multiset_adapter( const ptr_multiset_adapter<U,Set,CA,b>& r )
          : base_type( r )
        { }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        explicit ptr_multiset_adapter( std::auto_ptr<PtrContainer> clone )
         : base_type( clone )
        { }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        explicit ptr_multiset_adapter( std::unique_ptr<PtrContainer> clone )
         : base_type( std::move( clone ) )
        { }
#endif

        template< class U, class Set, class CA, bool b >
        ptr_multiset_adapter& operator=( const ptr_multiset_adapter<U,Set,CA,b>& r ) 
        {
            base_type::operator=( r );
            return *this;
        }
        
#ifndef BOOST_NO_AUTO_PTR
        template< class T >
        void operator=( std::auto_ptr<T> r ) 
        {
            base_type::operator=( r ); 
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class T >
        void operator=( std::unique_ptr<T> r ) 
        {
            base_type::operator=( std::move( r ) ); 
        }
#endif

        iterator insert( iterator before, key_type* x ) // strong  
        {
            return base_type::insert( before, x ); 
        } 

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator insert( iterator before, std::auto_ptr<U> x )
        {
            return insert( before, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator insert( iterator before, std::unique_ptr<U> x )
        {
            return insert( before, x.release() );
        }
#endif
    
        iterator insert( key_type* x ) // strong                                      
        {   
            this->enforce_null_policy( x, "Null pointer in 'ptr_multiset::insert()'" );
    
            auto_type ptr( x, *this );                                
            BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                 res = this->base().insert( x );                         
            ptr.release();                                                      
            return iterator( res );                                             
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        iterator insert( std::auto_ptr<U> x )
        {
            return insert( x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        iterator insert( std::unique_ptr<U> x )
        {
            return insert( x.release() );
        }
#endif
    
        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            set_basic_clone_and_insert( first, last );
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else    
        
        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        insert( const Range& r )
        {
            insert( boost::begin(r), boost::end(r) );
        }

#endif

        template< class PtrSetAdapter >
        void transfer( BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator object, 
                       PtrSetAdapter& from ) // strong
        {
            this->multi_transfer( object, from );
        }

        template< class PtrSetAdapter >
        size_type transfer( BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator first, 
                            BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator last, 
                            PtrSetAdapter& from ) // basic
        {
            return this->multi_transfer( first, last, from );
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else    
        
        template< class PtrSetAdapter, class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                       BOOST_DEDUCED_TYPENAME PtrSetAdapter::iterator >, size_type >::type
        transfer(  const Range& r, PtrSetAdapter& from ) // basic
        {
            return transfer( boost::begin(r), boost::end(r), from );
        }

#endif        

        template< class PtrSetAdapter >
        void transfer( PtrSetAdapter& from ) // basic
        {
            transfer( from.begin(), from.end(), from );
            BOOST_ASSERT( from.empty() );
        }
        
    };

} // namespace 'boost'  

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#endif

/* ptr_set_adapter.hpp
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
*/