//  Boost string_algo library find_format_all.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_ALL_DETAIL_HPP
#define BOOST_STRING_FIND_FORMAT_ALL_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/algorithm/string/detail/find_format_store.hpp>
#include <boost/algorithm/string/detail/replace_storage.hpp>

#include <deque>

namespace boost {
    namespace algorithm {
        namespace detail {

// find_format_all_copy (iterator variant) implementation ---------------------------//

           template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline OutputIteratorT find_format_all_copy_impl2(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult )
            {       
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::boost::begin(Input);

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    Output = std::copy( LastMatch, M.begin(), Output );
                    // Copy formatted result
                    Output = std::copy( ::boost::begin(M.format_result()), ::boost::end(M.format_result()), Output );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::boost::end(Input) );
                }

                // Copy the rest of the sequence
                Output = std::copy( LastMatch, ::boost::end(Input), Output );

                return Output;
            }

            template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline OutputIteratorT find_format_all_copy_impl(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult )
            {   
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_all_copy_impl2( 
                        Output,
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                }
            }

 // find_format_all_copy implementation ----------------------------------------------//

           template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline InputT find_format_all_copy_impl2(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::boost::begin(Input);

                // Output temporary
                InputT Output;

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    boost::algorithm::detail::insert( Output, ::boost::end(Output), LastMatch, M.begin() );
                    // Copy formatted result
                    boost::algorithm::detail::insert( Output, ::boost::end(Output), M.format_result() );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::boost::end(Input) );
                }

                // Copy the rest of the sequence
                ::boost::algorithm::detail::insert( Output, ::boost::end(Output), LastMatch, ::boost::end(Input) );

                return Output;
            }

            template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline InputT find_format_all_copy_impl(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_all_copy_impl2(
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return Input;
                }
            }

 // find_format_all implementation ------------------------------------------------//
        
            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline void find_format_all_impl2( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult,
                FormatResultT FormatResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_iterator<InputT>::type input_iterator_type; 
                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );
          
                // Instantiate replacement storage
                std::deque<
                    BOOST_STRING_TYPENAME range_value<InputT>::type> Storage;

                // Initialize replacement iterators
                input_iterator_type InsertIt=::boost::begin(Input);
                input_iterator_type SearchIt=::boost::begin(Input);
                
                while( M )
                {
                    // process the segment
                    InsertIt=process_segment( 
                        Storage,
                        Input,
                        InsertIt,
                        SearchIt,
                        M.begin() );
                    
                    // Adjust search iterator
                    SearchIt=M.end();

                    // Copy formatted replace to the storage
                    ::boost::algorithm::detail::copy_to_storage( Storage, M.format_result() );

                    // Find range for a next match
                    M=Finder( SearchIt, ::boost::end(Input) );
                }

                // process the last segment
                InsertIt=::boost::algorithm::detail::process_segment( 
                    Storage,
                    Input,
                    InsertIt,
                    SearchIt,
                    ::boost::end(Input) );
                
                if ( Storage.empty() )
                {
                    // Truncate input
                    ::boost::algorithm::detail::erase( Input, InsertIt, ::boost::end(Input) );
                }
                else
                {
                    // Copy remaining data to the end of input
                    ::boost::algorithm::detail::insert( Input, ::boost::end(Input), Storage.begin(), Storage.end() );
                }
            }

            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline void find_format_all_impl( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    ::boost::algorithm::detail::find_format_all_impl2(
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                }
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FIND_FORMAT_ALL_DETAIL_HPP

/* find_format_all.hpp
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
*/