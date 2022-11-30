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
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
*/