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