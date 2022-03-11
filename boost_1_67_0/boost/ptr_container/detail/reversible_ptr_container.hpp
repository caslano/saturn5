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


#ifndef BOOST_PTR_CONTAINER_DETAIL_REVERSIBLE_PTR_CONTAINER_HPP
#define BOOST_PTR_CONTAINER_DETAIL_REVERSIBLE_PTR_CONTAINER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/ptr_container/detail/throw_exception.hpp>
#include <boost/ptr_container/detail/scoped_deleter.hpp>
#include <boost/ptr_container/detail/static_move_ptr.hpp>
#include <boost/ptr_container/detail/ptr_container_disable_deprecated.hpp>
#include <boost/ptr_container/exception.hpp>
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/ptr_container/nullable.hpp>

#ifdef BOOST_NO_SFINAE
#else
#include <boost/range/functions.hpp>
#endif

#include <boost/config.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/swap.hpp>
#include <typeinfo>
#include <memory>

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#pragma warning(push)  
#pragma warning(disable:4127)
#pragma warning(disable:4224) // formal parameter was previously defined as a type.
#endif  

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

namespace ptr_container_detail
{
    template< class Container >
    struct dynamic_clone_deleter
    {
        dynamic_clone_deleter() { }
        dynamic_clone_deleter( Container& cont ) : cont(&cont) { }
        Container* cont;

        template< class T >
        void operator()( const T* p ) const
        {
            // remark: static_move_ptr already test for null
            cont->get_clone_allocator().deallocate_clone( p );
        }
    };

    template< class CloneAllocator >
    struct static_clone_deleter
    {
        static_clone_deleter() { }
        template< class Dummy >
        static_clone_deleter( const Dummy& ) { }
            
        template< class T >
        void operator()( const T* p ) const
        {
            // remark: static_move_ptr already test for null
            CloneAllocator::deallocate_clone( p );
        }
    };

    template< class T >
    struct is_pointer_or_integral
    {
        BOOST_STATIC_CONSTANT(bool, value = is_pointer<T>::value || is_integral<T>::value );
    };

    struct is_pointer_or_integral_tag {};
    struct is_range_tag {};
    struct sequence_tag {};
    struct fixed_length_sequence_tag : sequence_tag {};
    struct associative_container_tag {};
    struct ordered_associative_container_tag : associative_container_tag {};
    struct unordered_associative_container_tag : associative_container_tag {};
    

    
    template
    < 
        class Config, 
        class CloneAllocator
    >
    class reversible_ptr_container : CloneAllocator
    {
    private:
        BOOST_STATIC_CONSTANT( bool, allow_null = Config::allow_null );
        BOOST_STATIC_CONSTANT( bool, is_clone_allocator_empty = sizeof(CloneAllocator) < sizeof(void*) );

        typedef BOOST_DEDUCED_TYPENAME Config::value_type Ty_;
        typedef BOOST_DEDUCED_TYPENAME Config::void_container_type  container_type;
        typedef dynamic_clone_deleter<reversible_ptr_container>     dynamic_deleter_type;
        typedef static_clone_deleter<CloneAllocator>                static_deleter_type;
        
        container_type c_;

    public:
        container_type&       base()               { return c_; }
    protected: // having this public could break encapsulation
        const container_type& base() const         { return c_; }        
        
    public: // typedefs
        typedef  Ty_           object_type;
        typedef  Ty_*          value_type;
        typedef  Ty_*          pointer;
        typedef  Ty_&          reference;
        typedef  const Ty_&    const_reference;
        
        typedef  BOOST_DEDUCED_TYPENAME Config::iterator 
                                   iterator;
        typedef  BOOST_DEDUCED_TYPENAME Config::const_iterator
                                   const_iterator;
        typedef  boost::reverse_iterator< iterator > 
                                   reverse_iterator;  
        typedef  boost::reverse_iterator< const_iterator >     
                                   const_reverse_iterator;
        typedef  BOOST_DEDUCED_TYPENAME container_type::difference_type
                                   difference_type; 
        typedef  BOOST_DEDUCED_TYPENAME container_type::size_type
                                   size_type;
        typedef  BOOST_DEDUCED_TYPENAME Config::allocator_type
                                   allocator_type;
        typedef CloneAllocator     clone_allocator_type;
        typedef ptr_container_detail::static_move_ptr<Ty_, 
                     BOOST_DEDUCED_TYPENAME boost::mpl::if_c<is_clone_allocator_empty,
                                                                static_deleter_type,
                                                                dynamic_deleter_type>::type 
                                                     >
                                   auto_type;
            
    protected: 
            
        typedef ptr_container_detail::scoped_deleter<reversible_ptr_container>
                                   scoped_deleter;
        typedef BOOST_DEDUCED_TYPENAME container_type::iterator
                                   ptr_iterator; 
        typedef BOOST_DEDUCED_TYPENAME container_type::const_iterator
                                   ptr_const_iterator; 
    private:

        template< class InputIterator >  
        void copy( InputIterator first, InputIterator last ) 
        {
            std::copy( first, last, begin() );
        }
        
        void copy( const reversible_ptr_container& r )
        { 
            this->copy( r.begin(), r.end() );
        }
        
        void copy_clones_and_release( scoped_deleter& sd ) // nothrow
        {
            BOOST_ASSERT( size_type( std::distance( sd.begin(), sd.end() ) ) == c_.size() );
            std::copy( sd.begin(), sd.end(), c_.begin() );
            sd.release(); 
        }
        
        template< class ForwardIterator >
        void clone_assign( ForwardIterator first, 
                           ForwardIterator last ) // strong 
        {
            BOOST_ASSERT( first != last );
            scoped_deleter sd( *this, first, last ); // strong
            copy_clones_and_release( sd );           // nothrow
        }

        template< class ForwardIterator >
        void clone_back_insert( ForwardIterator first,
                                ForwardIterator last )
        {
            BOOST_ASSERT( first != last );
            scoped_deleter sd( *this, first, last );
            insert_clones_and_release( sd, end() );
        }
        
        void remove_all() 
        {
            this->remove( begin(), end() ); 
        }

    protected:

        void insert_clones_and_release( scoped_deleter& sd, 
                                        iterator where ) // strong
        {
            //
            // 'c_.insert' always provides the strong guarantee for T* elements
            // since a copy constructor of a pointer cannot throw
            //
            c_.insert( where.base(), 
                       sd.begin(), sd.end() ); 
            sd.release();
        }

        void insert_clones_and_release( scoped_deleter& sd ) // strong
        {
            c_.insert( sd.begin(), sd.end() );
            sd.release();
        }

        template< class U >
        void remove( U* ptr )
        {
            this->deallocate_clone( ptr );
        }
        
        template< class I >
        void remove( I i )
        { 
            this->deallocate_clone( Config::get_const_pointer(i) );
        }

        template< class I >
        void remove( I first, I last ) 
        {
            for( ; first != last; ++first )
                this->remove( first );
        }

        static void enforce_null_policy( const Ty_* x, const char* msg )
        {
            if( !allow_null )
            {
                BOOST_PTR_CONTAINER_THROW_EXCEPTION( 0 == x && "null not allowed", 
                                                     bad_pointer, msg );
            }
        }

    public:
        Ty_* null_policy_allocate_clone( const Ty_* x )
        {
            if( allow_null )
            {
                if( x == 0 )
                    return 0;
            }
            else
            {
                BOOST_ASSERT( x != 0 && "Cannot insert clone of null!" );
            }

            Ty_* res = this->get_clone_allocator().allocate_clone( *x );
            BOOST_ASSERT( typeid(*res) == typeid(*x) &&
                          "CloneAllocator::allocate_clone() does not clone the "
                          "object properly. Check that new_clone() is implemented"
                          " correctly" );
            return res;
        }

        template< class Iterator >
        Ty_* null_policy_allocate_clone_from_iterator( Iterator i )
        {
            return this->null_policy_allocate_clone(Config::get_const_pointer(i));
        }
        
        void null_policy_deallocate_clone( const Ty_* x )
        {
            if( allow_null )
            {
                if( x == 0 )
                    return;
            }

            this->get_clone_allocator().deallocate_clone( x );
        }
        
    private:
        template< class ForwardIterator >
        ForwardIterator advance( ForwardIterator begin, size_type n ) 
        {
            ForwardIterator iter = begin;
            std::advance( iter, n );
            return iter;
        }        

        template< class I >
        void constructor_impl( I first, I last, std::input_iterator_tag ) // basic
        {
            while( first != last )
            {
                insert( end(), this->allocate_clone_from_iterator(first) );
                ++first;
            }
        }

        template< class I >
        void constructor_impl( I first, I last, std::forward_iterator_tag ) // strong
        {
            if( first == last )
                return;
            clone_back_insert( first, last );
        }

        template< class I >
        void associative_constructor_impl( I first, I last ) // strong
        {
            if( first == last )
                return;

            scoped_deleter sd( *this, first, last );
            insert_clones_and_release( sd );             
        }

    public: // foundation: should be protected, but public for poor compilers' sake.
        reversible_ptr_container()
        { }

        template< class SizeType >
        reversible_ptr_container( SizeType n, unordered_associative_container_tag )
          : c_( n )
        { }

        template< class SizeType >
        reversible_ptr_container( SizeType n, fixed_length_sequence_tag )
          : c_( n )
        { }

        template< class SizeType >
        reversible_ptr_container( SizeType n, const allocator_type& a, 
                                  fixed_length_sequence_tag )
          : c_( n, a )
        { }
        
        explicit reversible_ptr_container( const allocator_type& a ) 
         : c_( a )
        { }

#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        explicit reversible_ptr_container( std::auto_ptr<PtrContainer> clone )
        {
            swap( *clone );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        explicit reversible_ptr_container( std::unique_ptr<PtrContainer> clone )
        {
            swap( *clone );
        }
#endif

        reversible_ptr_container( const reversible_ptr_container& r ) 
        {
            constructor_impl( r.begin(), r.end(), std::forward_iterator_tag() ); 
        }

        template< class C, class V >
        reversible_ptr_container( const reversible_ptr_container<C,V>& r ) 
        {
            constructor_impl( r.begin(), r.end(), std::forward_iterator_tag() ); 
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class PtrContainer >
        reversible_ptr_container& operator=( std::auto_ptr<PtrContainer> clone ) // nothrow
        {
            swap( *clone );
            return *this;
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class PtrContainer >
        reversible_ptr_container& operator=( std::unique_ptr<PtrContainer> clone ) // nothrow
        {
            swap( *clone );
            return *this;
        }
#endif

        reversible_ptr_container& operator=( reversible_ptr_container r ) // strong 
        {
            swap( r );
            return *this;
        }
        
        // overhead: null-initilization of container pointer (very cheap compared to cloning)
        // overhead: 1 heap allocation (very cheap compared to cloning)
        template< class InputIterator >
        reversible_ptr_container( InputIterator first, 
                                  InputIterator last,
                                  const allocator_type& a = allocator_type() ) // basic, strong
          : c_( a )
        { 
            constructor_impl( first, last, 
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#else
                              BOOST_DEDUCED_TYPENAME
#endif                              
                              iterator_category<InputIterator>::type() );
        }

        template< class Compare >
        reversible_ptr_container( const Compare& comp,
                                  const allocator_type& a )
          : c_( comp, a ) {}

        template< class ForwardIterator >
        reversible_ptr_container( ForwardIterator first,
                                  ForwardIterator last,
                                  fixed_length_sequence_tag )
          : c_( std::distance(first,last) )
        {
            constructor_impl( first, last, 
                              std::forward_iterator_tag() );
        }

        template< class SizeType, class InputIterator >
        reversible_ptr_container( SizeType n,
                                  InputIterator first,
                                  InputIterator last,
                                  fixed_length_sequence_tag )
          : c_( n )
        {
            constructor_impl( first, last, 
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#else
                              BOOST_DEDUCED_TYPENAME
#endif                              
                              iterator_category<InputIterator>::type() );
        }

        template< class Compare >
        reversible_ptr_container( const Compare& comp,
                                  const allocator_type& a,
                                  associative_container_tag )
          : c_( comp, a )
        { }
                
        template< class InputIterator >
        reversible_ptr_container( InputIterator first,
                                  InputIterator last,
                                  associative_container_tag )
        {
            associative_constructor_impl( first, last );
        }
        
        template< class InputIterator, class Compare >
        reversible_ptr_container( InputIterator first,
                                  InputIterator last,
                                  const Compare& comp,
                                  const allocator_type& a,
                                  associative_container_tag )
          : c_( comp, a ) 
        {
            associative_constructor_impl( first, last );
        }

        explicit reversible_ptr_container( size_type n )
          : c_( n ) {}

        template< class Hash, class Pred >
        reversible_ptr_container( const Hash& h,
                                  const Pred& pred,
                                  const allocator_type& a )
          : c_( h, pred, a ) {}

        template< class InputIterator, class Hash, class Pred >
        reversible_ptr_container( InputIterator first,
                                  InputIterator last,
                                  const Hash& h,
                                  const Pred& pred,
                                  const allocator_type& a )
          : c_( h, pred, a )
        {
            associative_constructor_impl( first, last );
        }

    public:        
        ~reversible_ptr_container()
        { 
            remove_all();
        }
        
    public:
        
        allocator_type get_allocator() const                   
        {
            return c_.get_allocator(); 
        }
        
        clone_allocator_type& get_clone_allocator()
        {
            return static_cast<clone_allocator_type&>(*this);
        }
 
        const clone_allocator_type& get_clone_allocator() const
        {
            return static_cast<const clone_allocator_type&>(*this);
        }
 
    public: // container requirements
        iterator begin()            
            { return iterator( c_.begin() ); }
        const_iterator begin() const      
            { return const_iterator( c_.begin() ); }
        iterator end()              
            { return iterator( c_.end() ); }
        const_iterator end() const        
            { return const_iterator( c_.end() ); }
        
        reverse_iterator rbegin()           
            { return reverse_iterator( this->end() ); } 
        const_reverse_iterator rbegin() const     
            { return const_reverse_iterator( this->end() ); } 
        reverse_iterator rend()             
            { return reverse_iterator( this->begin() ); } 
        const_reverse_iterator rend() const       
            { return const_reverse_iterator( this->begin() ); } 

        const_iterator cbegin() const      
            { return const_iterator( c_.begin() ); }
        const_iterator cend() const             
            { return const_iterator( c_.end() ); }

        const_reverse_iterator crbegin() const      
            { return const_reverse_iterator( this->end() ); }
        const_reverse_iterator crend() const             
            { return const_reverse_iterator( this->begin() ); }

        void swap( reversible_ptr_container& r ) // nothrow
        { 
            boost::swap( get_clone_allocator(), r.get_clone_allocator() ); // nothrow
            c_.swap( r.c_ ); // nothrow
        }
          
        size_type size() const // nothrow
        {
            return c_.size();
        }

        size_type max_size() const // nothrow
        {
            return c_.max_size(); 
        }
        
        bool empty() const // nothrow
        {
            return c_.empty();
        }

    public: // optional container requirements

        bool operator==( const reversible_ptr_container& r ) const // nothrow
        { 
            if( size() != r.size() )
                return false;
            else
                return std::equal( begin(), end(), r.begin() );
        }

        bool operator!=( const reversible_ptr_container& r ) const // nothrow
        {
            return !(*this == r);
        }
        
        bool operator<( const reversible_ptr_container& r ) const // nothrow 
        {
             return std::lexicographical_compare( begin(), end(), r.begin(), r.end() );
        }

        bool operator<=( const reversible_ptr_container& r ) const // nothrow 
        {
            return !(r < *this);
        }

        bool operator>( const reversible_ptr_container& r ) const // nothrow 
        {
            return r < *this;
        }

        bool operator>=( const reversible_ptr_container& r ) const // nothrow 
        {
            return !(*this < r);
        }

    public: // modifiers

        iterator insert( iterator before, Ty_* x )
        {
            enforce_null_policy( x, "Null pointer in 'insert()'" );

            auto_type ptr( x, *this );                     // nothrow
            iterator res( c_.insert( before.base(), x ) ); // strong, commit
            ptr.release();                                 // nothrow
            return res;
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

        iterator erase( iterator x ) // nothrow
        {
            BOOST_ASSERT( !empty() );
            BOOST_ASSERT( x != end() );

            remove( x );
            return iterator( c_.erase( x.base() ) );
        }

        iterator erase( iterator first, iterator last ) // nothrow
        {
            remove( first, last );
            return iterator( c_.erase( first.base(),
                                       last.base() ) );
        }

        template< class Range >
        iterator erase( const Range& r )
        {
            return erase( boost::begin(r), boost::end(r) );
        }

        void clear()
        {
            remove_all();
            c_.clear();
        }
        
    public: // access interface
        
        auto_type release( iterator where )
        { 
            BOOST_ASSERT( where != end() );
            
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( empty(), bad_ptr_container_operation,
                                                 "'release()' on empty container" ); 
            
            auto_type ptr( Config::get_pointer(where), *this );  // nothrow
            c_.erase( where.base() );                            // nothrow
            return boost::ptr_container_detail::move( ptr ); 
        }

        auto_type replace( iterator where, Ty_* x ) // strong  
        { 
            BOOST_ASSERT( where != end() );
            enforce_null_policy( x, "Null pointer in 'replace()'" );            

            auto_type ptr( x, *this );
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( empty(), bad_ptr_container_operation,
                                                 "'replace()' on empty container" );

            auto_type old( Config::get_pointer(where), *this );  // nothrow            
            const_cast<void*&>(*where.base()) = ptr.release();                
            return boost::ptr_container_detail::move( old );
        }

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        auto_type replace( iterator where, std::auto_ptr<U> x )
        {
            return replace( where, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        auto_type replace( iterator where, std::unique_ptr<U> x )
        {
            return replace( where, x.release() );
        }
#endif

        auto_type replace( size_type idx, Ty_* x ) // strong
        {
            enforce_null_policy( x, "Null pointer in 'replace()'" );            

            auto_type ptr( x, *this ); 
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( idx >= size(), bad_index, 
                                                 "'replace()' out of bounds" );
            
            auto_type old( static_cast<Ty_*>(c_[idx]), *this ); // nothrow
            c_[idx] = ptr.release();                            // nothrow, commit
            return boost::ptr_container_detail::move( old );
        } 

#ifndef BOOST_NO_AUTO_PTR
        template< class U >
        auto_type replace( size_type idx, std::auto_ptr<U> x )
        {
            return replace( idx, x.release() );
        }
#endif
#ifndef BOOST_NO_CXX11_SMART_PTR
        template< class U >
        auto_type replace( size_type idx, std::unique_ptr<U> x )
        {
            return replace( idx, x.release() );
        }
#endif
                
    }; // 'reversible_ptr_container'


#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))    
#define BOOST_PTR_CONTAINER_DEFINE_RELEASE( base_type ) \
    typename base_type::auto_type                   \
    release( typename base_type::iterator i )       \
    {                                               \
        return boost::ptr_container_detail::move(base_type::release(i)); \
    }                                               
#else
#define BOOST_PTR_CONTAINER_DEFINE_RELEASE( base_type ) \
    using base_type::release;
#endif

#ifndef BOOST_NO_AUTO_PTR
#define BOOST_PTR_CONTAINER_COPY_AND_ASSIGN_AUTO( PC, base_type, this_type ) \
    explicit PC( std::auto_ptr<this_type> r )       \
    : base_type ( r ) { }                           \
                                                    \
    PC& operator=( std::auto_ptr<this_type> r )     \
    {                                               \
        base_type::operator=( r );                  \
        return *this;                               \
    }
#else
#define BOOST_PTR_CONTAINER_COPY_AND_ASSIGN_AUTO( PC, base_type, this_type )
#endif

#ifndef BOOST_NO_CXX11_SMART_PTR
#define BOOST_PTR_CONTAINER_COPY_AND_ASSIGN_UNIQUE( PC, base_type, this_type ) \
    explicit PC( std::unique_ptr<this_type> r )     \
    : base_type ( std::move( r ) ) { }              \
                                                    \
    PC& operator=( std::unique_ptr<this_type> r )   \
    {                                               \
        base_type::operator=( std::move( r ) );     \
        return *this;                               \
    }
#else
#define BOOST_PTR_CONTAINER_COPY_AND_ASSIGN_UNIQUE( PC, base_type, this_type )
#endif

#ifndef BOOST_NO_AUTO_PTR
#define BOOST_PTR_CONTAINER_RELEASE_AND_CLONE( this_type ) \
    std::auto_ptr<this_type> release()              \
    {                                               \
      std::auto_ptr<this_type> ptr( new this_type );\
      this->swap( *ptr );                           \
      return ptr;                                   \
    }                                               \
                                                    \
    std::auto_ptr<this_type> clone() const          \
    {                                               \
       return std::auto_ptr<this_type>( new this_type( this->begin(), this->end() ) ); \
    }
#elif !defined( BOOST_NO_CXX11_SMART_PTR )
#define BOOST_PTR_CONTAINER_RELEASE_AND_CLONE( this_type ) \
    std::unique_ptr<this_type> release()              \
    {                                                 \
      std::unique_ptr<this_type> ptr( new this_type );\
      this->swap( *ptr );                             \
      return ptr;                                     \
    }                                                 \
                                                      \
    std::unique_ptr<this_type> clone() const          \
    {                                                 \
       return std::unique_ptr<this_type>( new this_type( this->begin(), this->end() ) ); \
    }
#else
#define BOOST_PTR_CONTAINER_RELEASE_AND_CLONE( this_type )
#endif

    //
    // two-phase lookup of template functions
    // is buggy on most compilers, so we use a macro instead
    //
#define BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( PC, base_type, this_type )  \
    BOOST_PTR_CONTAINER_COPY_AND_ASSIGN_AUTO( PC, base_type, this_type )   \
    BOOST_PTR_CONTAINER_COPY_AND_ASSIGN_UNIQUE( PC, base_type, this_type ) \
    BOOST_PTR_CONTAINER_RELEASE_AND_CLONE( this_type )                     \
    BOOST_PTR_CONTAINER_DEFINE_RELEASE( base_type )

#define BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( PC, base_type ) \
                                                                      \
    template< class U >                                               \
    PC( const PC<U>& r ) : base_type( r ) { }                         \
                                                                      \
    PC& operator=( PC r )                                             \
    {                                                                 \
        this->swap( r );                                              \
        return *this;                                                 \
    }                                                                 \
                                                                           

#define BOOST_PTR_CONTAINER_DEFINE_CONSTRUCTORS( PC, base_type )                       \
    typedef BOOST_DEDUCED_TYPENAME base_type::iterator        iterator;                \
    typedef BOOST_DEDUCED_TYPENAME base_type::size_type       size_type;               \
    typedef BOOST_DEDUCED_TYPENAME base_type::const_reference const_reference;         \
    typedef BOOST_DEDUCED_TYPENAME base_type::allocator_type  allocator_type;          \
    PC() {}                                                                            \
    explicit PC( const allocator_type& a ) : base_type(a) {}                           \
    template< class InputIterator >                                                    \
    PC( InputIterator first, InputIterator last ) : base_type( first, last ) {}        \
    template< class InputIterator >                                                    \
    PC( InputIterator first, InputIterator last,                                       \
        const allocator_type& a ) : base_type( first, last, a ) {}  
                 
#define BOOST_PTR_CONTAINER_DEFINE_NON_INHERITED_MEMBERS( PC, base_type, this_type )           \
   BOOST_PTR_CONTAINER_DEFINE_CONSTRUCTORS( PC, base_type )                                    \
   BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( PC, base_type, this_type )

#define BOOST_PTR_CONTAINER_DEFINE_SEQEUENCE_MEMBERS( PC, base_type, this_type )  \
    BOOST_PTR_CONTAINER_DEFINE_NON_INHERITED_MEMBERS( PC, base_type, this_type )  \
    BOOST_PTR_CONTAINER_DEFINE_COPY_CONSTRUCTORS( PC, base_type )

} // namespace 'ptr_container_detail'

    //
    // @remark: expose movability of internal move-pointer
    //
    namespace ptr_container
    {        
        using ptr_container_detail::move;
    }

} // namespace 'boost'  

#if defined(BOOST_PTR_CONTAINER_DISABLE_DEPRECATED)
#pragma GCC diagnostic pop
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)  
#pragma warning(pop)  
#endif  

#endif

/* reversible_ptr_container.hpp
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
*/