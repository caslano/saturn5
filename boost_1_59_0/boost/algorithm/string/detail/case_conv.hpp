//  Boost string_algo library string_funct.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CASE_CONV_DETAIL_HPP
#define BOOST_STRING_CASE_CONV_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <locale>
#include <functional>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  case conversion functors -----------------------------------------------//

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

            // a tolower functor
            template<typename CharT>
            struct to_lowerF
            {
                typedef CharT argument_type;
                typedef CharT result_type;
                // Constructor
                to_lowerF( const std::locale& Loc ) : m_Loc( &Loc ) {}

                // Operation
                CharT operator ()( CharT Ch ) const
                {
                    #if defined(BOOST_BORLANDC) && (BOOST_BORLANDC >= 0x560) && (BOOST_BORLANDC <= 0x564) && !defined(_USE_OLD_RW_STL)
                        return std::tolower( static_cast<typename boost::make_unsigned <CharT>::type> ( Ch ));
                    #else
                        return std::tolower<CharT>( Ch, *m_Loc );
                    #endif
                }
            private:
                const std::locale* m_Loc;
            };

            // a toupper functor
            template<typename CharT>
            struct to_upperF
            {
                typedef CharT argument_type;
                typedef CharT result_type;
                // Constructor
                to_upperF( const std::locale& Loc ) : m_Loc( &Loc ) {}

                // Operation
                CharT operator ()( CharT Ch ) const
                {
                    #if defined(BOOST_BORLANDC) && (BOOST_BORLANDC >= 0x560) && (BOOST_BORLANDC <= 0x564) && !defined(_USE_OLD_RW_STL)
                        return std::toupper( static_cast<typename boost::make_unsigned <CharT>::type> ( Ch ));
                    #else
                        return std::toupper<CharT>( Ch, *m_Loc );
                    #endif
                }
            private:
                const std::locale* m_Loc;
            };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

// algorithm implementation -------------------------------------------------------------------------

            // Transform a range
            template<typename OutputIteratorT, typename RangeT, typename FunctorT>
            OutputIteratorT transform_range_copy(
                OutputIteratorT Output,
                const RangeT& Input,
                FunctorT Functor)
            {
                return std::transform( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    Output,
                    Functor);
            }

            // Transform a range (in-place)
            template<typename RangeT, typename FunctorT>
            void transform_range(
                const RangeT& Input,
                FunctorT Functor)
            {
                std::transform( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    ::boost::begin(Input),
                    Functor);
            }

            template<typename SequenceT, typename RangeT, typename FunctorT>
            inline SequenceT transform_range_copy( 
                const RangeT& Input, 
                FunctorT Functor)
            {
                return SequenceT(
                    ::boost::make_transform_iterator(
                        ::boost::begin(Input),
                        Functor),
                    ::boost::make_transform_iterator(
                        ::boost::end(Input), 
                        Functor));
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_CASE_CONV_DETAIL_HPP

/* case_conv.hpp
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
*/