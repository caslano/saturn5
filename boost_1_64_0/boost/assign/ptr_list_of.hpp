// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_PTR_LIST_OF_HPP
#define BOOST_ASSIGN_PTR_LIST_OF_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/move/utility.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#endif

namespace boost
{

namespace assign_detail
{
    /////////////////////////////////////////////////////////////////////////
    // Part 1: flexible and efficient interface
    /////////////////////////////////////////////////////////////////////////

    template< class T >
    class generic_ptr_list :
        public converter< generic_ptr_list<T>,
                          BOOST_DEDUCED_TYPENAME boost::ptr_vector<T>::iterator >
    {
    protected:
        typedef boost::ptr_vector<T>       impl_type;
#if defined(BOOST_NO_AUTO_PTR)
        typedef std::unique_ptr<impl_type> release_type;
#else
        typedef std::auto_ptr<impl_type>   release_type;
#endif	
        mutable impl_type                  values_;

    public:
        typedef BOOST_DEDUCED_TYPENAME impl_type::iterator         iterator;
        typedef iterator                                           const_iterator;
        typedef BOOST_DEDUCED_TYPENAME impl_type::value_type       value_type;
        typedef BOOST_DEDUCED_TYPENAME impl_type::size_type        size_type;
        typedef BOOST_DEDUCED_TYPENAME impl_type::difference_type  difference_type;
    public:
        generic_ptr_list() : values_( 32u )
        { }

        generic_ptr_list( release_type r ) : values_(r)
        { }

        release_type release()
        {
            return values_.release();
        }

    public:
        iterator begin() const       { return values_.begin(); }
        iterator end() const         { return values_.end(); }
        bool empty() const           { return values_.empty(); }
        size_type size() const       { return values_.size(); }

    public:

        operator impl_type() const
        {
            return values_;
        }

        template< template<class,class,class> class Seq, class U,
                  class CA, class A >
        operator Seq<U,CA,A>() const
        {
            Seq<U,CA,A> result;
            result.transfer( result.end(), values_ );
            BOOST_ASSERT( empty() );
            return result;
        }

        template< class PtrContainer >
#if defined(BOOST_NO_AUTO_PTR)
        std::unique_ptr<PtrContainer>
#else
        std::auto_ptr<PtrContainer>
#endif	
		convert( const PtrContainer* c ) const
        {
#if defined(BOOST_NO_AUTO_PTR)
            std::unique_ptr<PtrContainer> res( new PtrContainer() );
#else
            std::auto_ptr<PtrContainer> res( new PtrContainer() );
#endif	
            while( !empty() )
                res->insert( res->end(),
                             values_.pop_back().release() );
            return res;
        }

        template< class PtrContainer >
#if defined(BOOST_NO_AUTO_PTR)
        std::unique_ptr<PtrContainer>
#else
        std::auto_ptr<PtrContainer>
#endif	
        to_container( const PtrContainer& c ) const
        {
            return convert( &c );
        }

    protected:
        void push_back( T* r ) { values_.push_back( r ); }

    public:
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

        generic_ptr_list& operator()()
        {
            this->push_back( new T() );
            return *this;
        }

        template< class U >
        generic_ptr_list& operator()( const U& u )
        {
            this->push_back( new T(u) );
            return *this;
        }


#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 5
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class U)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, U, const& u)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, u)

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class U, BOOST_ASSIGN_PARAMS1(n) > \
    generic_ptr_list& operator()(U const& u, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        this->push_back( new T(u, BOOST_ASSIGN_PARAMS3(n))); \
        return *this; \
    } \
    /**/

#include BOOST_PP_LOCAL_ITERATE()

#else
        template< class... Us >
        generic_ptr_list& operator()(Us&&... us)
        {
            this->push_back(new T(boost::forward<Us>(us)...));
            return *this;
        }
#endif



    }; // class 'generic_ptr_list'

} // namespace 'assign_detail'

namespace assign
{
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class T >
    inline assign_detail::generic_ptr_list<T>
    ptr_list_of()
    {
        assign_detail::generic_ptr_list<T> gpl;
        gpl();
        return gpl;
    }

    template< class T, class U >
    inline assign_detail::generic_ptr_list<T>
    ptr_list_of( const U& t )
    {
        assign_detail::generic_ptr_list<T> gpl;
        gpl( t );
        return gpl;
    }


#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, class U, BOOST_ASSIGN_PARAMS1(n) > \
    inline assign_detail::generic_ptr_list<T> \
    ptr_list_of(U const& u, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        return assign_detail::generic_ptr_list<T>()(u, BOOST_ASSIGN_PARAMS3(n)); \
    } \
    /**/

#include BOOST_PP_LOCAL_ITERATE()

#else
    template< class T, class... Us >
    inline assign_detail::generic_ptr_list<T>
    ptr_list_of(Us&&... us)
    {
        assign_detail::generic_ptr_list<T> gpl;
        gpl(boost::forward<Us>(us)...);
        return gpl;
    }

#endif

} // namespace 'assign'
} // namespace 'boost'

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#undef BOOST_ASSIGN_PARAMS1
#undef BOOST_ASSIGN_PARAMS2
#undef BOOST_ASSIGN_PARAMS3
#undef BOOST_ASSIGN_MAX_PARAMETERS

#endif

#endif

/* ptr_list_of.hpp
+FqXuFcJH74/i4ax+nqi66ZKhc9I2p3dnYXt2PsicTvUrif8Quwt1d/aI5+nti43E/93TQvGVQX0w90omxlclP+IpKMZTMW3N4Slvvpgm1RZSxA2XjqHADlZLmteGydy+lHqY5GuhfPuz1IKOwTdbFvy6qCaZd0W2T0MJG/D6trQFCNHE90v9VsTqGvLGobXtcI51dY1Dd/L1rWnGlZb1zR8D1svHhf75th1zcbpavc3e1TsH0ata2Nt+CxbN9eK/dPq6hpxqq1rtj8/S+pkPVuvLhZ785j16AFJ9y1PerM5dWg9zlbxP9uurz1V0uso9c5dH7eycaDeJcePSEpIGiJVL2a9U31Pgwi/pH3Nup3+HfWO9ThyTNN3ycmYj9M5X8S716w5s8qjjGfseLe3hB/Du4KjdTGYRlpkWdjn3VHi383Y96Dq3yVH1OZd8o00I8fXmOaYbW66hN3SIvx+4EyyIlY70vAd7HuDv6Vrv5pxUIK2Fd44xK2Jndt3jJu8ti2bRlv77mMk/Ev07MlV3xu0bXwvcd4yg4wTU8fZtZJOJ7WHX0dqaxmzTJ/meX+ZJv755K3PrtM0sk4z1C6GS5hzTA/KogHuX6TQ/2DSqb9+TnovE4APtyRfu3Cf2D8St/199wzV6f6QPMNN8iysDDc1NXLk06gOgCMgfSEC+54y1E0qqxlja/jOtm+7TeyH+Rp59dmF+kIN38c+d+8TeztfqC8kvLcvtHGy7Rr3SrH38Kz3LJ9WFuoLNXx323f+MWAPnMNo+OA5tE5slDB/9a79JJ3q+8cM7R8PPkB6Rcb0n5kGzpm2n/xLWxnHx+wn75T0O/mq1BetUw+Jf5b4zw+MxYvZ0VDGkVPteVdz3nInVpj0tnJf5MaZRsearA2UsSRNhd9Z0qdilz7Xuk/JCnA2dN2LdV/I3V1qN9asvo+ljMP6WHWL2scGyjYjrI+15Rexd6Dce1Q3b91/LNPI8byOA+6CX3KtlR3C6r4uxI5Z9zV8li2vN8R+o6P1MrLua/h+tu5/KPYlTpR9w2x7eq9DoG5pW9A0epsYdV/9e9q28q7Yr3ai1X1PXdd4dn/ImHV2s4S7wImos7YdfSL+Fzk67hB/GXfo9Z/f0fV/gffOu7V9O2ZyJxmX2vejBRLmn9jvizn+XSth+poklVHCpun4ZBzxBv3b9mY6fl08SAaw9dtFH78ehFt9/bY8JyvUPuZq3Xd1SJa6rGXdz4us+1ZPQHjdnxpjv62iKHW/NEbdz7Puks9SzwdpPb++pZHjYYd7g7c52se3i1bP5xVOn8uvKH19hpb9zRLvVOdkcxP93NHaDoLptbfvwJ07VNmfjwGUtgMbvqut46vFfmmgjtrwoW8OeRrHO75dJfbLItuaHQfcKv5znFnmcm0bwTQ6aRjH5LZ37dtMglkXY+8+2z6IW7ux8oeSZrLd19CIvbOTaxLItXFmd6i+6vl9un9v0P4+IV+PbH+2j7lJrmO5tq9Qf58R6O81jS9IY5pZzbl0rKH12Pbt1O/w58Cp4v9zjJ+lrCP6di1P27dXbQuLorcF20ZsP273cFXFixzH6bg6D5Pp5llA1rWssHx+6ZRy3YNQ8zNyTN1Mwg4yyaExtcZvFmoHHnnSkda/e3hfsh/jaq5D8y5yjkDOY+UTM/0/Qj5R5OyGD33oqCmH/HNp05u7nfFh+YD5dXKLP1Zu8Q/tRE6w611JI5qNueTpj3z1211YRtq/jXfdG21IXjqjw9ZBux/t+0DTkuFFseQZY+uEXSfpPPO3iZ/dUdxy2w9XrBj69w737TLmG3GvfH9Su2un3tngvKQXnYy9tz/83y8XGV3nbGzdtXmSD5uXFFw=
*/