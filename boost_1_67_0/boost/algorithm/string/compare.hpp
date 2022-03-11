//  Boost string_algo library compare.hpp header file  -------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_COMPARE_HPP
#define BOOST_STRING_COMPARE_HPP

#include <boost/algorithm/string/config.hpp>
#include <locale>

/*! \file
    Defines element comparison predicates. Many algorithms in this library can
    take an additional argument with a predicate used to compare elements.
    This makes it possible, for instance, to have case insensitive versions
    of the algorithms.
*/

namespace boost {
    namespace algorithm {

        //  is_equal functor  -----------------------------------------------//

        //! is_equal functor
        /*!
            Standard STL equal_to only handle comparison between arguments
            of the same type. This is a less restrictive version which wraps operator ==.
        */
        struct is_equal
        {
            //! Function operator
            /*!
                Compare two operands for equality
            */
            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                return Arg1==Arg2;
            }
        };

        //! case insensitive version of is_equal
        /*!
            Case insensitive comparison predicate. Comparison is done using
            specified locales.
        */
        struct is_iequal
        {
            //! Constructor
            /*!
                \param Loc locales used for comparison
            */
            is_iequal( const std::locale& Loc=std::locale() ) :
                m_Loc( Loc ) {}

            //! Function operator
            /*!
                Compare two operands. Case is ignored.
            */
            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                    return std::toupper(Arg1)==std::toupper(Arg2);
                #else
                    return std::toupper<T1>(Arg1,m_Loc)==std::toupper<T2>(Arg2,m_Loc);
                #endif
            }

        private:
            std::locale m_Loc;
        };

        //  is_less functor  -----------------------------------------------//

        //! is_less functor
        /*!
            Convenient version of standard std::less. Operation is templated, therefore it is 
            not required to specify the exact types upon the construction
         */
        struct is_less
        {
            //! Functor operation
            /*!
                Compare two operands using > operator
             */
            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                return Arg1<Arg2;
            }
        };


        //! case insensitive version of is_less
        /*!
            Case insensitive comparison predicate. Comparison is done using
            specified locales.
        */
        struct is_iless
        {
            //! Constructor
            /*!
                \param Loc locales used for comparison
            */
            is_iless( const std::locale& Loc=std::locale() ) :
                m_Loc( Loc ) {}

            //! Function operator
            /*!
                Compare two operands. Case is ignored.
            */
            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                    return std::toupper(Arg1)<std::toupper(Arg2);
                #else
                    return std::toupper<T1>(Arg1,m_Loc)<std::toupper<T2>(Arg2,m_Loc);
                #endif
            }

        private:
            std::locale m_Loc;
        };

        //  is_not_greater functor  -----------------------------------------------//

        //! is_not_greater functor
        /*!
            Convenient version of standard std::not_greater_to. Operation is templated, therefore it is 
            not required to specify the exact types upon the construction
         */
        struct is_not_greater
        {
            //! Functor operation
            /*!
                Compare two operands using > operator
             */
            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                return Arg1<=Arg2;
            }
        };


        //! case insensitive version of is_not_greater
        /*!
            Case insensitive comparison predicate. Comparison is done using
            specified locales.
        */
        struct is_not_igreater
        {
            //! Constructor
            /*!
                \param Loc locales used for comparison
            */
            is_not_igreater( const std::locale& Loc=std::locale() ) :
                m_Loc( Loc ) {}

            //! Function operator
            /*!
                Compare two operands. Case is ignored.
            */
            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                    return std::toupper(Arg1)<=std::toupper(Arg2);
                #else
                    return std::toupper<T1>(Arg1,m_Loc)<=std::toupper<T2>(Arg2,m_Loc);
                #endif
            }

        private:
            std::locale m_Loc;
        };


    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::is_equal;
    using algorithm::is_iequal;
    using algorithm::is_less;
    using algorithm::is_iless;
    using algorithm::is_not_greater;
    using algorithm::is_not_igreater;

} // namespace boost


#endif  // BOOST_STRING_COMPARE_HPP

/* compare.hpp
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
*/