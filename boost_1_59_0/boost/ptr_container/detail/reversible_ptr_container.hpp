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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
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


#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))    
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