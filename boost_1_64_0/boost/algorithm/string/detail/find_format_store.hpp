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
LIy5dgCBY1RBvBnB4ksJdNTSjRODzqkSjbXckDaAud6QxdWpGNZ5yns6pua0462SInuD0vrlND1XdzZrzMyuHR7gUHXzhmaJVSzUV34gTR7+ekR7QJSxBJUW1uPQ5hCnRG8kxwRlQn80wj1GDeQFmMQv8njh6OX90YebHBkak35NGHHg6BUEcEK+6vJqj4LdQkfZH9/5MTWLhjSKgpOgzjxoIP+Umh7FNp/WeG7jUTY9OS4cZsC2GT6Fan5mwkeunCrT/iFKrfZo4Bm16AhFUXbElYMeWBhlLkDrJu4Vsbx0/VaXrvQhAJ8vogRLDOiApPTpWrfAacbXEVe45Ul8kdTzf5r0yeZteWmen+Fq8kwQFOq6HWMf4in1q72S2BhQjvynJ3nOAgFxscF3UdeGHIJ3Ufhm4esCaEysbmQZPBk4047l5mKmFFmuwxfLasgNOgAhOfTVJ49GO8IPpmhxwv80f9yDzDpaxukp1t0LKd+UAQAZfhTAyCdn5V5OKBiyAhW1Mts0Xl9LezS1U3+HQHPnEneiNgpYMDXlq800Y+vhWhcexGSa5YlZfw==
*/