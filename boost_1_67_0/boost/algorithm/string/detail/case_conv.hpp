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
                    #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
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
                    #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
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