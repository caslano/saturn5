//  Boost string_algo library formatter_regex.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FORMATTER_REGEX_DETAIL_HPP
#define BOOST_STRING_FORMATTER_REGEX_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <string>
#include <boost/regex.hpp>
#include <boost/algorithm/string/detail/finder_regex.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  regex format functor -----------------------------------------//

            // regex format functor
            template<typename StringT>
            struct regex_formatF
            {
            private:
                typedef StringT result_type;
                typedef BOOST_STRING_TYPENAME StringT::value_type char_type;

            public:
                // Construction
                regex_formatF( const StringT& Fmt, match_flag_type Flags=format_default ) :
                    m_Fmt(Fmt), m_Flags( Flags ) {}

                template<typename InputIteratorT>
                result_type operator()( 
                    const regex_search_result<InputIteratorT>& Replace ) const
                {
                    if ( Replace.empty() )
                    {
                        return result_type();
                    }
                    else
                    {
                        return Replace.match_results().format( m_Fmt, m_Flags );                      
                    }
                }
            private:
                const StringT& m_Fmt;
                match_flag_type m_Flags;
            };

        
        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FORMATTER_DETAIL_HPP

/* formatter_regex.hpp
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
*/