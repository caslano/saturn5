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
                #if defined(BOOST_BORLANDC) && (BOOST_BORLANDC >= 0x560) && (BOOST_BORLANDC <= 0x564) && !defined(_USE_OLD_RW_STL)
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
                #if defined(BOOST_BORLANDC) && (BOOST_BORLANDC >= 0x560) && (BOOST_BORLANDC <= 0x564) && !defined(_USE_OLD_RW_STL)
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
                #if defined(BOOST_BORLANDC) && (BOOST_BORLANDC >= 0x560) && (BOOST_BORLANDC <= 0x564) && !defined(_USE_OLD_RW_STL)
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