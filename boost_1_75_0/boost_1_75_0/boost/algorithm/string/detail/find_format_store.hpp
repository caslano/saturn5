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
IUfexl0I4dIYrWmiKcisqTtgWG/B9Ft/fg7HcRNwZuNQ5DaKAP/HJ9+M3yzw7ugVqZJQXAbjROBuwBjBcqrn7kwsvnAMYynqaNh7/qM3M2t68YO5sVrDldOPmUSk5yDb6NgCFcz0iJVAiy6Qz8/2nGkYyP1X/znV+sd9/0muKNJrvQdMPUV3wEADqbTPm2TtHJ40Qv+hSG+HHv70nHnwu77dF2XkhrzahgKW4umy6z2qnjC2xG1l7HjND4dZpuXxo5uxW0x4Czcr3eLNIq2zLW8vSDTDvKAUpUrNjYJrI+cE0utp6YTKAxFtJ7rNc3BNajP3C0IEfaOCry5g9rpnxcapKDAeQbndXMhSC6GbZfL0xM4kYM9NYfI46JflKXt2l/7zzM53PiL1aeXcmaK090W7lpU+ZYIN7HWdzX3l2hqVV49XJOFbCf35zW2eZGYKFd8fdPF5Xh4Aj/LleYiOflfoW1ETSNOfjp8dGYcjp9mJWaQx87CRsvDSluGK7VJAT8vU28tNKImTN5V4We/W002t899yjsgY/GlW24ZOnJFCfTIeY9VIkGInB+ax3resD7I+gvtD0khYDc9JJOtc08XncI5OOAa0MhfYbU/lfAspueLKb+dvJqKUT3OfaWSUT7PfbZS/XqJwqAebmpkt4CTmHE/1t+7blBMwrNuycH7gKT7rBaxaNCRiOFdZGTfNNqk9KGN/ZQoB0zAo
*/