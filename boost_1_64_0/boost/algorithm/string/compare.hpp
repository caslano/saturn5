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
Nt8HM3Pvuef2c88995RN+B698fM4/hKz8XNwvB4IJzLznUUR+EGtnXP+PtvjZqK2Pxrp1o+c4BBles2wWX4kWr4sRqrzsO14p+kHziR17+M80chrtkd/s96nPEZDPFHB5SfxM189j2xHE3cB7W/kyKvoLkrNrdoAEDotUb0ukPiNW149SksiBE9JckkDXleCRy3W5cET0riO9RRHBfHnKU5z6s84fBBIAi2dP+Ld2+7veP27er9syhwFGW9d7Bn2TLZV/eM5an3XSky+13Dow43OLf7Ox2CmP62KnG4xnnxHUbn5ZQ6HH7A7m604Bh6fvUYdUl+/x7oB3lGlau8XNIla5cFvmi7dxzd//yTXxpNV1LKPCPocNxzK83nDMOoC6kNutSp4a0Om9ThbE8lex2XwxJv3iH45TQJqWh+J6oGvpLI0pFjBWZJV5w+5AhyfMufFOFd4pill1MceR1PkqpeQiq/puj4vBesum5SqjLJJaWq6JGVYSR41BklopU3LKJtOzD9iRVREf57eo+ck08n0ZcCK0uBv20NOlFJu4zueSbaHnPD3MDvI2h8Jv5YQpaNANmduLf1N1vCcClrcsJimoDfqqCbh79SilXJRYoH2+VF8//jgJUt7vp04mDG9gaKSZw6ChPuzO/qvfEEdekNYl6+2cg11ybZkulOt2cL072xaUv72fuu3W4/qMNDc46r/CuYxwG8mcnQG/OQNl7IN3QJ7aWysBN3l/WT6/95lXpzVB59a49OG/ON/KMOewsM+xRz2d16nQaFKPdTl64rWxQOA1brUPZtphHolqC4v8ZdEwlWHkNALBRUvaamGrAl1ATP18f0yU10IrLuAjS6cIrNS70NiKF9SQ18X8/6jmHP2NxvWAk7BtFhJv3MaIq3X9TvlaKT1qiBdgGPJxz4Jc8Nw3QEZt2slLLo5bssLWUoaJBnTuZonHYsHVvNN4gbp+vQAee7G1MYcFKPgqqtKg+l06MBehb3Gsls6ZLwKIldSDZDtHuPtYo31reZYT/UYNMYeJ+1JVQcHiZWQP8Npy4xTS0Ct1Bsv8MyYAUWYJ4IjhizTfTvqcq1kSyR87w8kPeMs983TpNKbCqfKzA39gGZujXpkncxcjzd4L/0bds9v/5nyxR926LV/gMaAA7YeLaKLbnxOkqVQ9Kj0Z9F+6s/j/ObxdkFItKfWLxPbLAwcMCRyaiB5eWnwt+ufatXPdd9u1m2punil7lpc92MsJ+5rr7vmX8zZ2C31FtxXGc++5VypHNoeOk5LqS10nn6ziZpzbk49VFfGCwrs9hLFrMoY6lR5z4cvG2SmGzvZEs9DqyyOVw+vwdYQxZ25XxWr/f7YizAkRfbfH4b/zvwg/PfGMvDjDoT/zqfy4efZvrdlUPzxJ1CYj7RSf2nw1OefCV97hwnf79MI8D4L/zXva/glkfBnWPjbmvCHPykHX75/Fv8f6s8HunxipPr2bbP6Y8LP/SRS/7dZ+N/T8BvuPlX7DrxXrn1jrPreMMu7ItXXSeApfokJP/lABPhYC94aP3ck+H1bTXirPXUjwT9twT9kzv9nH0SafxM+dse7Gn5lJPgMC/6WfRp+bCT4eAv+hIk/NRL8V8Um/Efm+DgrhodbgLiicvoHT0v5dAme+Hbh4w5irxxxxIlujFOzXiwNhriU8o/t5fANDsfnzx5tw9au8thMfLEV4Is28f39hdPGt3ZLeXxRJj7/6eMbUxbfGMKEM3WHuvx0sPH5wrxjfcHoZtHCAZUPfSg6pLarkxuBby+YCGIWhwdm31Ma/G3+fvNmbS+To74ntlOcF9A6KcpNbeL7kai9Uddi/zdAbhqxvz7Btwjicb6r+bM=
*/