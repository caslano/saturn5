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
YhQw9mBx8OuMX8Ud9BQGdJ2uiMqfWIbjqDwYw29wcIAPa25D6xqockHxHQYBdF42TJ1ISr3Li6t8o1KW2cJHIOGFueiLrTkJdpe3tHv86sKJME0Twvl+//w8sVGaO+LJ4vL7vOnk2Cq7VjsF20XHTbSBi0f5nsKndbJyVvdB3psTkoU+wf7dqrInaYmQlhDipFlV8MFKMgooks3orWxbHaj5R1za5tq1vqGTD2Jrok8UEA83uVwToDiFnRxV6WXTedXRmYotRZ2Mosw8vrkmr+QAxS++PBq2dzAAUMf/KxzwvgE3q4PQGqYW0LTOt5gNcnjlsaX9lp7gmo4SrObwcxtOHQnfJJL3mEga9GgHE/pV7TrZVa4+9UMBMBoPvQdMstawJ8uKyojxpWm0H1EYGrmegu5FzM3Wu8ofICXsYA+FtjH8bDlFYxGeZsLJUmjJ2S3o5kVGEELpxHYNdPiGDSNo5C1/wWUEqseMar1xYDTOo0KJ+wTZK2t32HXX5jjMFXSdDynQOi+tcJcoL8xz8eVZXu3zQ6BYruko+6AORrhYqw+DjBs6jf1NX/SFuq7XpPvSS6BDDJ6qkgakBueANfXr5eOnLx+9eHr//CJL8OOPkaK010vx5w0jlQSKWXb58tnDZx8Y64uw7Hzp
*/