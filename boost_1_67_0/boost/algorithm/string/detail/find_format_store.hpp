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