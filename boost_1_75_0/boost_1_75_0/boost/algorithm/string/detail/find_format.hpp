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
vPFqsN74l7iPjJf+3zNlEyELjuCgYY0Njjb6D+bJ2z8HXlFcmn3w3y6qiAHecfjVrPHyu6HtsrfcZwNmRLBtiM4LJCgs5R0I9w+6hgFwxXhi9LLZh7yp07f68mQPMDc+FQqUP3hGSf69sfokhMEVSNDjZ82JM3OxOZYjnMxt4KAB5UhV3mSCEksH3HI4+fxyaLRz97MV+fy6DVsnXwWJYTft5/ZLAvlE22eDM7riuNgtXEjsBX6PF9ntusegcbdA4GaxMrYIxXVLtymMYxmuV6F1/96YP4Iz2hLntf+Z+fjtnWpDnuODU9XKjeM+kDqv1KoNn+kjH+jm9tqR4MQQ4jR+bZ9Cwx2U0D6vgp8aW9BKt/wj4vEQj0KRqo1s6QvdL8BLTyVjx5p94wppqG4qFd2Fp26KrrWutjJbnKkoRzwGeKa0unotOLLM67VpXBZmdsL3MyNrCKsPD9x33iHv6dGKkKwXaboKdGF9i2/cmrzRcaxqDxae8ZEvrQHmPGpKzm00brm03f7HObYat0wp2PUjefVu/ivYHpTczlh2Szphf4H4z5misxDcl4hca3a+nnQck68h+WbFHBYAM1AZ+6bFIdlGZymy5ogqAagNqiQb0eJD40y77pIvrj3refeb4ZdfT8d+rSaXX/+p8HEnmHf7cubVATjt+W4kuH15HBBN7dk1aO0HQX+rmtGLERmLelNaWG4u2NAo724/
*/