//  Boost string_algo library find_format_store.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_STORE_DETAIL_HPP
#define BOOST_STRING_FIND_FORMAT_STORE_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  temporary format and find result storage --------------------------------//

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif
            template< 
                typename ForwardIteratorT,
                typename FormatterT,
                typename FormatResultT >
            class find_format_store : 
                public iterator_range<ForwardIteratorT>
            {
            public:
                // typedefs
                typedef iterator_range<ForwardIteratorT> base_type;
                typedef FormatterT  formatter_type;
                typedef FormatResultT format_result_type;
                
            public:
                // Construction
                find_format_store( 
                        const base_type& FindResult,
                        const format_result_type& FormatResult,
                        const formatter_type& Formatter ) :
                    base_type(FindResult),
                    m_FormatResult(FormatResult),
                    m_Formatter(Formatter) {}

                // Assignment
                template< typename FindResultT >
                find_format_store& operator=( FindResultT FindResult )
                {
                    iterator_range<ForwardIteratorT>::operator=(FindResult);
                    if( !this->empty() ) {
                        m_FormatResult=m_Formatter(FindResult);
                    }
                    
                    return *this;
                }

                // Retrieve format result
                const format_result_type& format_result()
                {   
                    return m_FormatResult;
                }

            private:
                format_result_type m_FormatResult;
                const formatter_type& m_Formatter;
            };

            template<typename InputT, typename FindResultT>
            bool check_find_result(InputT&, FindResultT& FindResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 
                iterator_range<input_iterator_type> ResultRange(FindResult);
                return !ResultRange.empty();
            }

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif
        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FIND_FORMAT_STORE_DETAIL_HPP

/* find_format_store.hpp
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
*/