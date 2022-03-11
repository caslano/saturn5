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