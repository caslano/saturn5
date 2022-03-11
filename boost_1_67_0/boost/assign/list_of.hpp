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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// BCB requires full type definition for is_array<> to work correctly.
#include <boost/array.hpp>
#endif

namespace boost
{

// this here is necessary to avoid compiler error in <boost/array.hpp>
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct adapter_type_tag
    {
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct pair_type_tag
    {
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct default_type_tag
    {
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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