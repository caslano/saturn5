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
3Lfti+R838A/CoCb6TECfT9+JyQmGwX66b2zY7S+PbRQgOD86M+/fZkBUek0x3hVSvWhmYUXhW0GKuCkLemYGHWMUEk5hDLZO0FIddNmVzm+DUhdehzbPEqNSNRKxBQHh7qIe3sf38fIyiH4Ox0NNjxbiB+Qu9pezkwJ24iukvICSnBOFGTstDFvEJsUeAE5F+pQjPYlAVph+wSJgxp9l5dhIuPVJdW3k9LG+60Uu7uhUAnkvw4LvQTQta8cVmvS06Al4GlcLrEaehG4dUcUc1Aw6M/ZClh4YO2afLE+LvvZyU0Bwhr3S4hvVgYHgLmIU9vatiYC5IV0wDB5wOXE/Htn3uCsZ5taOej7wX1O8YxH6hZlVk3EGQ1HLiwPcddmNcIXiO9hk1l7K7OjivMRpvc2qKOztdVzEtOJAgscBt4QDh8P5UzenvXxxDW+SsO7+7ZL7LNKOmxqcc9OBJcXiCd6nCYyzfty50OgfQcB7uFwxCpMWYTNcw4aHLpbjsPYgmkv+KaPgrgNwVrKVwr4Tk8ta1AiQ5t4qMVEJ4NRkAcTDa1qRdz8FWYnx9b2mry460RwEzjexmxJ/p2JGtWCWPVRj97FxtVmSO2rkZGG8HCI/nDocIjmEkPum5qcEX+fmRxZ/vZVvv1N2i79+JQGdViMn7kYb0NwU3LeJxQNIfA7TXixrkSdtuT8dknN2/XQT1F598cC3fRaesEX
*/