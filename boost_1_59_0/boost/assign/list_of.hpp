// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_LIST_OF_HPP
#define BOOST_ASSIGN_LIST_OF_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/assignment_exception.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/declval.hpp>
#include <boost/mpl/if.hpp>
#include <boost/move/utility.hpp>
#include <deque>
#include <cstddef>
#include <utility>
#ifndef BOOST_NO_CXX11_HDR_ARRAY
#include <array>
#endif
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

// some gcc < 4.7 do not support all of the variadic features required for boost::assign
#if !(defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || BOOST_WORKAROUND(BOOST_GCC, < 40700) \
       || defined(BOOST_NO_CXX11_RVALUE_REFERENCES))
# define BOOST_ASSIGN_USE_VARIADIC_TEMPLATES
#endif

#if !defined(BOOST_ASSIGN_USE_VARIADIC_TEMPLATES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#endif

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
// BCB requires full type definition for is_array<> to work correctly.
#include <boost/array.hpp>
#endif

namespace boost
{

// this here is necessary to avoid compiler error in <boost/array.hpp>
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    template< class T, std::size_t sz >
    class array;
#endif

namespace assign_detail
{
    /////////////////////////////////////////////////////////////////////////
    // Part 0: common conversion code
    /////////////////////////////////////////////////////////////////////////

    template< class T >
    struct assign_decay
    {
        //
        // Add constness to array parameters
        // to support string literals properly
        //
        typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
            ::boost::is_array<T>,
            ::boost::decay<const T>,
            ::boost::decay<T> >::type type;
    };

    template< class T, std::size_t sz >
    type_traits::yes_type assign_is_array( const array<T,sz>* );
#ifndef BOOST_NO_CXX11_HDR_ARRAY
    template< class T, std::size_t sz >
    type_traits::yes_type assign_is_array( const std::array<T, sz>* );
#endif
    type_traits::no_type assign_is_array( ... );
    template< class T, class U >
    type_traits::yes_type assign_is_pair( const std::pair<T,U>* );
    type_traits::no_type assign_is_pair( ... );



    struct array_type_tag
    {
    #if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct adapter_type_tag
    {
    #if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct pair_type_tag
    {
    #if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct default_type_tag
    {
    #if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    template< class C >
    struct is_initializer_list : boost::false_type {};

    template< class E >
    struct is_initializer_list< std::initializer_list<E> > : boost::true_type {};
#endif

    template< class DerivedTAssign, class Iterator >
    class converter
    {
    public: // Range operations
        typedef Iterator iterator;
        typedef Iterator const_iterator;

        iterator begin() const
        {
            return static_cast<const DerivedTAssign*>(this)->begin();
        }

        iterator end() const
        {
            return static_cast<const DerivedTAssign*>(this)->end();
        }

    public:

        template< class Container >
        Container convert_to_container() const
        {
            static Container* c = 0;
            BOOST_STATIC_CONSTANT( bool, is_array_flag = sizeof( assign_detail::assign_is_array( c ) )
                                   == sizeof( type_traits::yes_type ) );

            typedef BOOST_DEDUCED_TYPENAME mpl::if_c< is_array_flag,
                                                      array_type_tag,
                                             default_type_tag >::type tag_type;

            return convert<Container>( c, tag_type() );
        }

    private:

        template< class Container >
        Container convert( const Container*, default_type_tag ) const
        {

#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
// old Dinkumware doesn't support iterator type as template
            Container result;
            iterator it  = begin(),
                     e   = end();
            while( it != e )
            {
                result.insert( result.end(), *it );
                ++it;
            }
            return result;
#else
            return Container( begin(), end() );
#endif
        }

        template< class Array >
        Array convert( const Array*, array_type_tag ) const
        {
            typedef BOOST_DEDUCED_TYPENAME Array::value_type value_type;

#if BOOST_WORKAROUND(BOOST_INTEL, <= 910 ) || BOOST_WORKAROUND(__SUNPRO_CC, <= 0x5100 )
            BOOST_DEDUCED_TYPENAME remove_const<Array>::type ar;
#else
            Array ar;
#endif
            const std::size_t sz = ar.size();
            if( sz < static_cast<const DerivedTAssign*>(this)->size() )
                BOOST_THROW_EXCEPTION( assign::assignment_exception( "array initialized with too many elements" ) );
            std::size_t n = 0;
            iterator i   = begin(),
                     e   = end();
            for( ; i != e; ++i, ++n )
                ar[n] = *i;
            for( ; n < sz; ++n )
                ar[n] = value_type();
            return ar;
        }

        template< class Adapter >
        Adapter convert_to_adapter( const Adapter* = 0 ) const
        {
            Adapter a;
            iterator i   = begin(),
                     e   = end();
            for( ; i != e; ++i )
                a.push( *i );
            return a;
        }

    private:
        struct adapter_converter;
        friend struct adapter_converter;

        struct adapter_converter
        {
            const converter& gl;
            adapter_converter( const converter& this_ ) : gl( this_ )
            {}

            adapter_converter( const adapter_converter& r )
            : gl( r.gl )
            { }

            template< class Adapter >
            operator Adapter() const
            {
                return gl.convert_to_adapter<Adapter>();
            }
        };

    public:
        template< class Container >
        Container to_container( Container& c ) const
        {
            return convert( &c, default_type_tag() );
        }

        adapter_converter to_adapter() const
        {
            return adapter_converter( *this );
        }

        template< class Adapter >
        Adapter to_adapter( Adapter& a ) const
        {
            return this->convert_to_adapter( &a );
        }

        template< class Array >
        Array to_array( Array& a ) const
        {
            return convert( &a, array_type_tag() );
        }
    };

    template< class T, class I, class Range >
    inline bool operator==( const converter<T,I>& l, const Range& r )
    {
        return ::boost::iterator_range_detail::equal( l, r );
    }

    template< class T, class I, class Range >
    inline bool operator==( const Range& l, const converter<T,I>& r )
    {
        return r == l;
    }

    template< class T, class I, class Range >
    inline bool operator!=( const converter<T,I>& l, const Range& r )
    {
        return !( l == r );
    }

    template< class T, class I, class Range >
    inline bool operator!=( const Range& l, const converter<T,I>& r )
    {
        return !( l == r );
    }

    template< class T, class I, class Range >
    inline bool operator<( const converter<T,I>& l, const Range& r )
    {
        return ::boost::iterator_range_detail::less_than( l, r );
    }

    template< class T, class I, class Range >
    inline bool operator<( const Range& l, const converter<T,I>& r )
    {
        return ::boost::iterator_range_detail::less_than( l, r );
    }

    template< class T, class I, class Range >
    inline bool operator>( const converter<T,I>& l, const Range& r )
    {
        return r < l;
    }

    template< class T, class I, class Range >
    inline bool operator>( const Range& l, const converter<T,I>& r )
    {
        return r < l;
    }

    template< class T, class I, class Range >
    inline bool operator<=( const converter<T,I>& l, const Range& r )
    {
        return !( l > r );
    }

    template< class T, class I, class Range >
    inline bool operator<=( const Range& l, const converter<T,I>& r )
    {
        return !( l > r );
    }

    template< class T, class I, class Range >
    inline bool operator>=( const converter<T,I>& l, const Range& r )
    {
        return !( l < r );
    }

    template< class T, class I, class Range >
    inline bool operator>=( const Range& l, const converter<T,I>& r )
    {
        return !( l < r );
    }

    template< class T, class I, class Elem, class Traits >
    inline std::basic_ostream<Elem,Traits>&
    operator<<( std::basic_ostream<Elem, Traits>& Os,
                const converter<T,I>& r )
    {
        return Os << ::boost::make_iterator_range( r.begin(), r.end() );
    }

    /////////////////////////////////////////////////////////////////////////
    // Part 1: flexible, but inefficient interface
    /////////////////////////////////////////////////////////////////////////

    template< class T >
    class generic_list :
        public converter< generic_list< BOOST_DEDUCED_TYPENAME assign_decay<T>::type >,
                          BOOST_DEDUCED_TYPENAME std::deque<BOOST_DEDUCED_TYPENAME
                                                            assign_decay<T>::type>::iterator >
    {
        typedef BOOST_DEDUCED_TYPENAME assign_decay<T>::type Ty;
        typedef std::deque<Ty>  impl_type;
        mutable impl_type       values_;

    public:
        typedef BOOST_DEDUCED_TYPENAME impl_type::iterator         iterator;
        typedef iterator                                           const_iterator;
        typedef BOOST_DEDUCED_TYPENAME impl_type::value_type       value_type;
        typedef BOOST_DEDUCED_TYPENAME impl_type::size_type        size_type;
        typedef BOOST_DEDUCED_TYPENAME impl_type::difference_type  difference_type;

    public:
        iterator begin() const       { return values_.begin(); }
        iterator end() const         { return values_.end(); }
        bool empty() const           { return values_.empty(); }
        size_type size() const       { return values_.size(); }

    private:
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        void push_back( value_type r ) { values_.push_back( r ); }
#else
        void push_back( const value_type& r ) { values_.push_back( r ); }
        void push_back( value_type&& r ) { values_.push_back( boost::move( r ) ); }
#endif
    public:
        generic_list& operator,( const Ty& u )
        {
            this->push_back( u );
            return *this;
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

        generic_list& operator,( Ty&& u )
        {
            this->push_back( boost::move(u) );
            return *this;
        }
#endif
        generic_list& operator()( const Ty& u )
        {
            this->push_back( u );
            return *this;
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

        generic_list& operator()(Ty&& u)
        {
            this->push_back( boost::move(u) );
            return *this;
        }
#endif

        generic_list& operator()()
        {
            this->push_back( Ty() );
            return *this;
        }

#if !defined(BOOST_ASSIGN_USE_VARIADIC_TEMPLATES)

#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 5
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class U)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, U, const& u)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, u)
#define BOOST_ASSIGN_PARAMS4(n) BOOST_PP_ENUM_PARAMS(n, U)
#define BOOST_ASSIGN_PARAMS2_NO_REF(n) BOOST_PP_ENUM_BINARY_PARAMS(n, U, u)

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class U, BOOST_ASSIGN_PARAMS1(n) > \
    generic_list& operator()(U const& u, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        this->push_back( Ty(u, BOOST_ASSIGN_PARAMS3(n))); \
        return *this; \
    } \
    /**/

#include BOOST_PP_LOCAL_ITERATE()

#else
        template< class U0, class U1, class... Us >
        generic_list& operator()(U0&& u0, U1&& u1, Us&&... us)
        {
            this->push_back(Ty(boost::forward<U0>(u0), boost::forward<U1>(u1), boost::forward<Us>(us)...));
            return *this;
        }
#endif

        template< class U >
        generic_list& repeat( std::size_t sz, U u )
        {
            std::size_t i = 0;
            while( i++ != sz )
                this->push_back( u );
            return *this;
        }

        template< class Nullary_function >
        generic_list& repeat_fun( std::size_t sz, Nullary_function fun )
        {
            std::size_t i = 0;
            while( i++ != sz )
                this->push_back( fun() );
            return *this;
        }

        template< class SinglePassIterator >
        generic_list& range( SinglePassIterator first,
                             SinglePassIterator last )
        {
            for( ; first != last; ++first )
                this->push_back( *first );
            return *this;
        }

        template< class SinglePassRange >
        generic_list& range( const SinglePassRange& r )
        {
            return range( boost::begin(r), boost::end(r) );
        }
#if !defined(BOOST_NO_CXX11_DECLTYPE_N3276) && !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
        template< class Container,
            class = decltype(Container(
                boost::declval<BOOST_DEDUCED_TYPENAME std::deque<BOOST_DEDUCED_TYPENAME assign_decay<T>::type>::iterator>(),
                boost::declval<BOOST_DEDUCED_TYPENAME std::deque<BOOST_DEDUCED_TYPENAME assign_decay<T>::type>::iterator>()
                ))
        >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }

        template< class Container,
            class = typename boost::enable_if< boost::is_same< boost::type_traits::yes_type, decltype(assign_is_array((Container*)0))> >::type,
            class = void
        >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }
#elif !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
        template< class Container
# if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
          , class = typename boost::disable_if< is_initializer_list<Container> >::type
# endif
          , class = typename Container::iterator
        >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }
#else
        template< class Container >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }
#endif
    };

    /////////////////////////////////////////////////////////////////////////
    // Part 2: efficient, but inconvenient interface
    /////////////////////////////////////////////////////////////////////////

    template< class T >
    struct assign_reference
    {
        assign_reference() : ref_(0)
        { /* intentionally empty */ }

        assign_reference( T& r ) : ref_(&r)
        { }

        void operator=( T& r )
        {
            ref_ = &r;
        }

        operator T&() const
        {
            return *ref_;
        }

        void swap( assign_reference& r )
        {
            std::swap( *ref_, *r.ref_ );
        }

        T& get_ref() const
        {
            return *ref_;
        }

    private:
        T* ref_;

    };

    template< class T >
    inline bool operator<( const assign_reference<T>& l,
                           const assign_reference<T>& r )
    {
        return l.get_ref() < r.get_ref();
    }

    template< class T >
    inline bool operator>( const assign_reference<T>& l,
                           const assign_reference<T>& r )
    {
        return l.get_ref() > r.get_ref();
    }

    template< class T >
    inline void swap( assign_reference<T>& l,
                      assign_reference<T>& r )
    {
        l.swap( r );
    }



    template< class T, int N >
    struct static_generic_list :
        public converter< static_generic_list<T,N>, assign_reference<T>* >
    {
    private:
        typedef T                                     internal_value_type;

    public:
        typedef assign_reference<internal_value_type> value_type;
        typedef value_type*                           iterator;
        typedef value_type*                           const_iterator;
        typedef std::size_t                           size_type;
        typedef std::ptrdiff_t                        difference_type;


        static_generic_list( T& r ) :
            current_(1)
        {
            refs_[0] = r;
        }

        static_generic_list& operator()( T& r )
        {
            insert( r );
            return *this;
        }

        iterator begin() const
        {
            return &refs_[0];
        }

        iterator end() const
        {
            return &refs_[current_];
        }

        size_type size() const
        {
            return static_cast<size_type>( current_ );
        }

        bool empty() const
        {
            return false;
        }

        template< class ForwardIterator >
        static_generic_list& range( ForwardIterator first,
                                    ForwardIterator last )
        {
            for( ; first != last; ++first )
                this->insert( *first );
            return *this;
        }

        template< class ForwardRange >
        static_generic_list& range( ForwardRange& r )
        {
            return range( boost::begin(r), boost::end(r) );
        }

        template< class ForwardRange >
        static_generic_list& range( const ForwardRange& r )
        {
            return range( boost::begin(r), boost::end(r) );
        }

#if !defined(BOOST_NO_CXX11_DECLTYPE_N3276) && !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
        template< class Container,
            class = decltype(Container(boost::declval<assign_reference<T>*>(), boost::declval<assign_reference<T>*>()))
        >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }

        template< class Container,
            class = typename boost::enable_if< boost::is_same< boost::type_traits::yes_type, decltype(assign_is_array((Container*)0))> >::type,
            class = void
        >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }
#elif !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
        template< class Container
# if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
          , class = typename boost::disable_if< is_initializer_list<Container> >::type
# endif
          , class = typename Container::iterator
        >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }
#else
        template< class Container >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }
#endif

    private:
        void insert( T& r )
        {
            refs_[current_] = r;
            ++current_;
        }

        static_generic_list();

        mutable assign_reference<internal_value_type> refs_[N];
        int current_;
    };

} // namespace 'assign_detail'

namespace assign
{
    template< class T >
    inline assign_detail::generic_list<BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type>
    list_of()
    {
        assign_detail::generic_list<BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type> gl;
        gl();
        return gl;
    }

#if !defined(BOOST_ASSIGN_USE_VARIADIC_TEMPLATES)

    template< class T >
    inline assign_detail::generic_list<T>
    list_of( const T& t )
    {
        return assign_detail::generic_list<T>()( t );
    }

#else

    template< class T >
    inline assign_detail::generic_list<BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type>
    list_of(T&& t)
    {
        assign_detail::generic_list<BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type> gl;
        gl(boost::forward<T>(t));
        return gl;
    }

#endif

    template< int N, class T >
    inline assign_detail::static_generic_list< BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type,N>
    ref_list_of( T& t )
    {
        return assign_detail::static_generic_list<BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type,N>( t );
    }

    template< int N, class T >
    inline assign_detail::static_generic_list<const BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type,N>
    cref_list_of( const T& t )
    {
        return assign_detail::static_generic_list<const BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type,N>( t );
    }

#if !defined(BOOST_ASSIGN_USE_VARIADIC_TEMPLATES)

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, class U, BOOST_ASSIGN_PARAMS1(n) > \
    inline assign_detail::generic_list<T> \
    list_of(U const& u, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        return assign_detail::generic_list<T>()(u, BOOST_ASSIGN_PARAMS3(n)); \
    } \
    /**/

#include BOOST_PP_LOCAL_ITERATE()

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class U, BOOST_ASSIGN_PARAMS1(n) > \
    inline assign_detail::generic_list< tuple<U, BOOST_ASSIGN_PARAMS4(n)> > \
    tuple_list_of(U u, BOOST_ASSIGN_PARAMS2_NO_REF(n) ) \
    { \
        return assign_detail::generic_list< tuple<U, BOOST_ASSIGN_PARAMS4(n)> >()( tuple<U,BOOST_ASSIGN_PARAMS4(n)>( u, BOOST_ASSIGN_PARAMS3(n) )); \
    } \
    /**/

#include BOOST_PP_LOCAL_ITERATE()

#else
    template< class T, class U, class... Us >
    inline assign_detail::generic_list<BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type>
    list_of(U&& u, Us&&... us)
    {
        assign_detail::generic_list<BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type> gl;
        gl(boost::forward<U>(u), boost::forward<Us>(us)...);
        return gl;
    }


    template< class U, class... Us >
    inline assign_detail::generic_list< tuple<U, Us...> >
    tuple_list_of(U u, Us... us)
    {
        assign_detail::generic_list< tuple<U, Us...> > gl;
        gl(tuple<U, Us...>(u, us...));
        return gl;
    }
#endif

    template< class Key, class T >
    inline assign_detail::generic_list< std::pair
        <
            BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<Key>::type,
            BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type
        > >
    map_list_of( const Key& k, const T& t )
    {
        typedef BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<Key>::type k_type;
        typedef BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<T>::type   t_type;
        return assign_detail::generic_list< std::pair<k_type,t_type> >()( k, t );
    }

    template< class F, class S >
    inline assign_detail::generic_list< std::pair
        <
            BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<F>::type,
            BOOST_DEDUCED_TYPENAME assign_detail::assign_decay<S>::type
        > >
    pair_list_of( const F& f, const S& s )
    {
        return map_list_of( f, s );
    }


} // namespace 'assign'
} // namespace 'boost'


#if !defined(BOOST_ASSIGN_USE_VARIADIC_TEMPLATES)

#undef BOOST_ASSIGN_PARAMS1
#undef BOOST_ASSIGN_PARAMS2
#undef BOOST_ASSIGN_PARAMS3
#undef BOOST_ASSIGN_PARAMS4
#undef BOOST_ASSIGN_PARAMS2_NO_REF
#undef BOOST_ASSIGN_MAX_PARAMETERS

#endif


#endif

/* list_of.hpp
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
*/