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
+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
*/