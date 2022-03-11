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