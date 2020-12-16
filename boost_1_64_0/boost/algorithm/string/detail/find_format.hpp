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
WAazMlA6Sw94n5MeyJuCgfKkHiinyEDpiTRzoDyu+gy2Bgoj+rGjhep7qSwPlc3IP9ea/i34CKMapD72R5JX3SyJn2Xp4M8iuQEpRLeHNMVPReik5+UdIK4kAdNljMnL0h/JzCXZTMb3XeBBf6bQb327Ir9LLvXqTys9qwn8+Cbf6U2+U5t8pzT5Tm7yndjke0ST7wLr2zoPubxAW9yVe7KXzzyj7EY9CI6XQXDNs0l8aTE48BHV20/NyfcvZ4QBT9R+RQTQQYDJYUB4vKMrI7PeiJdb8Ed8e/PA9VNGxjPXCL2Fe0jNXfgB5kX2vpmktXv5DzIM0liQ7Rv0vodBcLEqHsQX1mvT6IZ6xlJ/Ybna/Y94GvW07c94m04j8PzOx4g7wAnF9xgN1v1XoQ/0TND0XMT0DAl6V4KegWrnQKbnwIbQ519Xm/l76vz9OH+emf+lQ+efa+X/6veS/1LOP9jMP+nQ+XOs/C/o/AM5v9/M7zxofhlbzX+L/VLvuVqekPMLSy/7LJW8YpS5Eyv7a5TXKC+0IjFA5iEDbTb6+5Tey0lzbvTTcZKaeynWlOJVliY2TjRmpKXlffUoUAxtKpLmfYpvMg19gk1D6RnUeysRlPfKl7jmTcBrLruTjVXz8PgLdHoVe1KMJRW7E6G8mufnWzNI6KYecIsey6ChXwjfk15WRIKUUb14WxEQLZE4rgI7zpXoq93BPl2AFlHu7MY7O3gL1/js76kxZ3Oqy/iktgdlcanLJOZsuuVduCKjkmMxcn32ler81+Lhx+ZjL2khQ0vc2R875vcLhehSs9eQivkNqTiVXI79IlyHR/rIOusG9pFFbS4KpO/tKeuH/THHxVZB9r/lrAtnHTjd1ZFzQdyCkjPBXm6WCLyHokvOv+SI5i+E+hcjzQE09UVrAN2n3VSm2jCKbwuR08tkBNmly6Np6ayn3EHDKZMGk5fV9XT+mqhuvlIf3W7EEaLX4fkIDIm0915EF+LYoC4Y1xd6encwL+TJ3jOzR9mvNUfsIxzx6afC6+d76rtc4ok1x0M/GyrPrp8RBu8n4IEI8I/VKgH/nHTIhQ+lpYDOvOBMG/TgGAj2kLuqVQyUquZzOlBD5wXHIvUT+GxghbSoop/TOvUHGM2EtMyBwbageRtcw4ZW5RUuUXWlxAmHkrlsxhJv4VsZS+nuZ8aqULX3YW/GCp/97X5VcVk2VQ44Yx0d4O3tLybwfYEyoyEnmDvcW1iHRfWVJ5P4ttDALqTGtA68H0c0VfIKUIka89qMTG71VQ4OU/byTMU4gOdUHAdy3/OZIt+FpwlbCQi3sZYmKr26WNyY6rhrGqHJpafZ8YJaj8HBuN7+7N23x+dlL5lUaLw1+9MuMTGzZiSElhUv2xSqMKpg+JRRkZexlBS9hat9DRugqHZ0ccXsdNxiK16ciscZb2mb6MULjr5gXOuxju3VO/Fa4yaK9ifWA8hdb0bW+7IXT68mJzXZS2ak4kQTzZnly1jnzVA4D6D34TP18/HbbIF6rhh5qsv38GEPW1JDCz5+pFRNoRqwprv3UapXCPV6kOo1QJ6cJ19W9go8M9/Vn73p9jYSkb160m3G0tN1/aqLqzeFyjN2E3MAe/bAS2vhOl/Ge3kZb8KkC32FqlI99XuVXF93cVUqftu2OaC+XFGp9Kbo+voKq7zZlTNSuRzgR6VTvRnr74usby3q6y4dJ0Ll808kxVAf7r5Jn/XVnuguvVHSFui0D2+i8W06pSX2dJ9mT/eOYfZEM1qOLI/CUe9/5V/pCJZ/hkXwTxczUUO4HILs03eeeYvUkOWTGepH1zBDHVF5aHkrOeK989J6tv8dZjLVtOcsproJKVQ=
*/