//  Boost string_algo library find_format.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
// 
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_DETAIL_HPP
#define BOOST_STRING_FIND_FORMAT_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <boost/algorithm/string/detail/find_format_store.hpp>
#include <boost/algorithm/string/detail/replace_storage.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

// find_format_copy (iterator variant) implementation -------------------------------//

           template< 
                typename OutputIteratorT,
                typename InputT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline OutputIteratorT find_format_copy_impl2(
                OutputIteratorT Output,
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult )
            {       
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Match not found - return original sequence
                    Output = std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                    return Output;
                }

                // Copy the beginning of the sequence
                Output = std::copy( ::boost::begin(Input), ::boost::begin(M), Output );
                // Format find result
                // Copy formatted result
                Output = std::copy( ::boost::begin(M.format_result()), ::boost::end(M.format_result()), Output );
                // Copy the rest of the sequence
                Output = std::copy( M.end(), ::boost::end(Input), Output );

                return Output;
            }

            template< 
                typename OutputIteratorT,
                typename InputT,
                typename FormatterT,
                typename FindResultT >
            inline OutputIteratorT find_format_copy_impl(
                OutputIteratorT Output,
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult )
            {   
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_copy_impl2( 
                        Output,
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                }
            }

 
// find_format_copy implementation --------------------------------------------------//

           template< 
                typename InputT, 
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline InputT find_format_copy_impl2(
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Match not found - return original sequence
                    return InputT( Input );
                }

                InputT Output;
                // Copy the beginning of the sequence
                boost::algorithm::detail::insert( Output, ::boost::end(Output), ::boost::begin(Input), M.begin() );
                // Copy formatted result
                boost::algorithm::detail::insert( Output, ::boost::end(Output), M.format_result() );
                // Copy the rest of the sequence
                boost::algorithm::detail::insert( Output, ::boost::end(Output), M.end(), ::boost::end(Input) );

                return Output;
            }

            template< 
                typename InputT, 
                typename FormatterT,
                typename FindResultT >
            inline InputT find_format_copy_impl(
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_copy_impl2(
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return Input;
                }
            }

 // replace implementation ----------------------------------------------------//
        
            template<
                typename InputT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline void find_format_impl2( 
                InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Search not found - return original sequence
                    return;
                }

                // Replace match
                ::boost::algorithm::detail::replace( Input, M.begin(), M.end(), M.format_result() );
            }

            template<
                typename InputT,
                typename FormatterT,
                typename FindResultT >
            inline void find_format_impl( 
                InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    ::boost::algorithm::detail::find_format_impl2(
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                }
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FIND_FORMAT_DETAIL_HPP

/* find_format.hpp
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
*/