// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_LIST_INSERTER_HPP
#define BOOST_ASSIGN_LIST_INSERTER_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/detail/workaround.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <cstddef>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

#endif

namespace boost
{
namespace assign_detail
{
    template< class T >
    struct repeater
    {
        std::size_t  sz;
        T            val;

        repeater( std::size_t sz_, T r ) : sz( sz_ ), val( r )
        { }
    };
    
    template< class Fun >
    struct fun_repeater
    {
        std::size_t  sz;
        Fun          val;
        
        fun_repeater( std::size_t sz_, Fun r ) : sz( sz_ ), val( r )
        { }
    };


    template< class T >
    struct is_repeater : boost::false_type {};

    template< class T >
    struct is_repeater< boost::assign_detail::repeater<T> > : boost::true_type{};

    template< class Fun >
    struct is_repeater< boost::assign_detail::fun_repeater<Fun> > : boost::true_type{};


    template< class C >
    class call_push_back
    {
        C& c_;
    public:
        call_push_back( C& c ) : c_( c )
        { }
        
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template< class T >
        void operator()( T r ) 
        {
            c_.push_back( r );
        }
#else
        template< class T >
        void operator()(T&& r)
        {
            c_.push_back(boost::forward<T>(r));
        }
#endif
    };
    
    template< class C >
    class call_push_front
    {
        C& c_;
    public:
        call_push_front( C& c ) : c_( c )
        { }

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template< class T >
        void operator()( T r ) 
        {
            c_.push_front( r );
        }
#else
        template< class T >
        void operator()(T&& r)
        {
            c_.push_front(boost::forward<T>(r));
        }
#endif
    };
    
    template< class C >
    class call_push
    {
        C& c_;
    public:
        call_push( C& c ) : c_( c )
        { }
    
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template< class T >
        void operator()( T r ) 
        {
            c_.push( r );
        }
#else
        template< class T >
        void operator()(T&& r)
        {
            c_.push(boost::forward<T>(r));
        }
#endif
    };
    
    template< class C >
    class call_insert
    {
        C& c_;
    public:
        call_insert( C& c ) : c_( c )
        { }

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template< class T >
        void operator()( T r ) 
        {
            c_.insert( r );
        }
#else
        template< class T >
        void operator()(T&& r)
        {
            c_.insert(boost::forward<T>(r));
        }
#endif
    };

    template< class C >
    class call_add_edge
    {
        C& c_;
    public:
        call_add_edge( C& c ) : c_(c)
        { }

        template< class T >
        void operator()( T l, T r )
        {
            add_edge( l, r, c_ );
        }

        template< class T, class EP >
        void operator()( T l, T r, const EP& ep )
        {
            add_edge( l, r, ep, c_ );
        }

    };
    
    struct forward_n_arguments {};
    
} // namespace 'assign_detail'

namespace assign
{

    template< class T >
    inline assign_detail::repeater<T>
    repeat( std::size_t sz, T r )
    {
        return assign_detail::repeater<T>( sz, r );
    }
    
    template< class Function >
    inline assign_detail::fun_repeater<Function>
    repeat_fun( std::size_t sz, Function r )
    {
        return assign_detail::fun_repeater<Function>( sz, r );
    }
    

    template< class Function, class Argument = assign_detail::forward_n_arguments > 
    class list_inserter
    {
        struct single_arg_type   {};
        struct n_arg_type        {};
        struct repeater_arg_type {};

        typedef BOOST_DEDUCED_TYPENAME mpl::if_c< is_same<Argument,assign_detail::forward_n_arguments>::value,
                                                  n_arg_type,
                                                  single_arg_type >::type arg_type;  
            
    public:
        
        list_inserter( Function fun ) : insert_( fun )
        {}
        
        template< class Function2, class Arg >
        list_inserter( const list_inserter<Function2,Arg>& r ) 
        : insert_( r.fun_private() ) 
        {}

        list_inserter( const list_inserter& r ) : insert_( r.insert_ )
        {}

        list_inserter& operator()()
        {
            insert_( Argument() );
            return *this;
        }

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template< class T >
        list_inserter& operator=( const T& r )
        {
            insert_( r );
            return *this;
        }

        template< class T >
        list_inserter& operator=( assign_detail::repeater<T> r )
        {
            return operator,( r );
        }
        
        template< class Nullary_function >
        list_inserter& operator=( const assign_detail::fun_repeater<Nullary_function>& r )
        {
            return operator,( r );
        }
        
        template< class T >
        list_inserter& operator,( const T& r )
        {
            insert_( r  );
            return *this;
        }

#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205))
        template< class T >
        list_inserter& operator,( const assign_detail::repeater<T> & r )
        {
            return repeat( r.sz, r.val ); 
        }
#else
        template< class T >
        list_inserter& operator,( assign_detail::repeater<T> r )
        {
            return repeat( r.sz, r.val ); 
        }
#endif
        
        template< class Nullary_function >
        list_inserter& operator,( const assign_detail::fun_repeater<Nullary_function>& r )
        {
            return repeat_fun( r.sz, r.val ); 
        }
#else
        // BOOST_NO_CXX11_RVALUE_REFERENCES
        template< class T >
        list_inserter& operator=(T&& r)
        {
            return operator,(boost::forward<T>(r));
        }
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
        template< class T >
        list_inserter& operator,(T&& r)
        {
            typedef BOOST_DEDUCED_TYPENAME mpl::if_c< assign_detail::is_repeater< T >::value,
                repeater_arg_type,
                arg_type >::type tag;

            insert(boost::forward<T>(r), tag());
            return *this;
        }
#else
        // we add the tag as the first argument when using variadic templates
        template< class T >
        list_inserter& operator,(T&& r)
        {
            typedef BOOST_DEDUCED_TYPENAME mpl::if_c< assign_detail::is_repeater< T >::value,
                repeater_arg_type,
                arg_type >::type tag;

            insert(tag(), boost::forward<T>(r));
            return *this;
        }
#endif
#endif

        template< class T >
        list_inserter& repeat( std::size_t sz, T r )
        {
            std::size_t i = 0;
            while( i++ != sz )
                insert_( r );
            return *this;
        }
        
        template< class Nullary_function >
        list_inserter& repeat_fun( std::size_t sz, Nullary_function fun )
        {
            std::size_t i = 0;
            while( i++ != sz )
                insert_( fun() );
            return *this;
        }

        template< class SinglePassIterator >
        list_inserter& range( SinglePassIterator first, 
                              SinglePassIterator last )
        {
            for( ; first != last; ++first )
                insert_( *first );
            return *this;
        }
        
        template< class SinglePassRange >
        list_inserter& range( const SinglePassRange& r )
        {
            return range( boost::begin(r), boost::end(r) );
        }
        
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template< class T >
        list_inserter& operator()( const T& t )
        {
            insert_( t );
            return *this;
        }

#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 5        
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class T)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& t)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, t)
        
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    list_inserter& operator()(T t, BOOST_ASSIGN_PARAMS2(n) ) \
        { \
            BOOST_PP_CAT(insert, BOOST_PP_INC(n))(t, BOOST_ASSIGN_PARAMS3(n), arg_type()); \
            return *this; \
        } \
        /**/

#include BOOST_PP_LOCAL_ITERATE()
        

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    void BOOST_PP_CAT(insert, BOOST_PP_INC(n))(T const& t, BOOST_ASSIGN_PARAMS2(n), single_arg_type) \
    { \
        insert_( Argument(t, BOOST_ASSIGN_PARAMS3(n) )); \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    void BOOST_PP_CAT(insert, BOOST_PP_INC(n))(T const& t, BOOST_ASSIGN_PARAMS2(n), n_arg_type) \
    { \
        insert_(t, BOOST_ASSIGN_PARAMS3(n) ); \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

#else
        template< class... Ts >
        list_inserter& operator()(Ts&&... ts)
        {
            insert(arg_type(), boost::forward<Ts>(ts)...);
            return *this;
        }

        template< class T >
        void insert(single_arg_type, T&& t)
        {
            // Special implementation for single argument overload to prevent accidental casts (type-cast using functional notation)
            insert_(boost::forward<T>(t));
        }

        template< class T1, class T2, class... Ts >
        void insert(single_arg_type, T1&& t1, T2&& t2, Ts&&... ts)
        {
            insert_(Argument(boost::forward<T1>(t1), boost::forward<T2>(t2), boost::forward<Ts>(ts)...));
        }

        template< class... Ts >
        void insert(n_arg_type, Ts&&... ts)
        {
            insert_(boost::forward<Ts>(ts)...);
        }

#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

        template< class T >
        void insert( T&& r, arg_type)
        {
            insert_( boost::forward<T>(r) );
        }

        template< class T >
        void insert(assign_detail::repeater<T> r, repeater_arg_type)
        {
            repeat(r.sz, r.val);
        }

        template< class Nullary_function >
        void insert(const assign_detail::fun_repeater<Nullary_function>& r, repeater_arg_type)
        {
            repeat_fun(r.sz, r.val);
        }
#else
        template< class T >
        void insert(repeater_arg_type, assign_detail::repeater<T> r)
        {
            repeat(r.sz, r.val);
        }

        template< class Nullary_function >
        void insert(repeater_arg_type, const assign_detail::fun_repeater<Nullary_function>& r)
        {
            repeat_fun(r.sz, r.val);
        }
#endif
#endif


        Function fun_private() const
        {
            return insert_;
        }

    private:
        
        list_inserter& operator=( const list_inserter& );
        Function insert_;
    };
    
    template< class Function >
    inline list_inserter< Function >
    make_list_inserter( Function fun )
    {
        return list_inserter< Function >( fun );
    }
    
    template< class Function, class Argument >
    inline list_inserter<Function,Argument>
    make_list_inserter( Function fun, Argument* )
    {
        return list_inserter<Function,Argument>( fun );
    }

    template< class C >
    inline list_inserter< assign_detail::call_push_back<C>, 
                          BOOST_DEDUCED_TYPENAME C::value_type >
    push_back( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_push_back<C>( c ), 
                                   p );
    }
    
    template< class C >
    inline list_inserter< assign_detail::call_push_front<C>,
                          BOOST_DEDUCED_TYPENAME C::value_type >
    push_front( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_push_front<C>( c ),
                                   p );
    }

    template< class C >
    inline list_inserter< assign_detail::call_insert<C>, 
                          BOOST_DEDUCED_TYPENAME C::value_type >
    insert( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_insert<C>( c ),
                                   p );
    }

    template< class C >
    inline list_inserter< assign_detail::call_push<C>, 
                          BOOST_DEDUCED_TYPENAME C::value_type >
    push( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_push<C>( c ),
                                   p );
    }

    template< class C >
    inline list_inserter< assign_detail::call_add_edge<C> >
    add_edge( C& c )   
    {
        return make_list_inserter( assign_detail::call_add_edge<C>( c ) );
    }
    
} // namespace 'assign'
} // namespace 'boost'

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#undef BOOST_ASSIGN_PARAMS1
#undef BOOST_ASSIGN_PARAMS2
#undef BOOST_ASSIGN_PARAMS3
#undef BOOST_ASSIGN_MAX_PARAMETERS

#endif

#endif

/* list_inserter.hpp
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
*/