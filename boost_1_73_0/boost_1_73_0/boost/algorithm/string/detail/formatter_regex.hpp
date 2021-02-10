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
WDsD2uCduJroUWWNgf+hI8jT1GtE4/q0rqghQnfeT7Y+l5tIhakP8xiE51BmPPhvPhJ0s+Csjyyc/JVo0WwEZxDYeF8nqZPjkKTx3Kqwg3c4eblscsxlqxqTbufOQUafDLzHE5M3f+CXCGCQJW2RX1LfzldB8znR5GvXxiYWjTgVBFlHbYqqZ0jI+AL5TSm3PV41A9CM1W5wjmQQcnXv5uLNvCIfXog+wOrqoMho+EuSgGy5afLtYtP0C4T6Zbo7sdTrPmMr5lMjT4/o7vf7YWDw624Pn7GkCHrkQmFC9hMDT3VD4/ami2De3jVff7XQAxCosnB+GVP+yBlvYE46Sn96zunnrTXw/JnrHc07VTfyKljkNMz2Ymv5383la4vsKNdeYuxuStlekEQBfH8sU+h316+shET5a5C/XX/7U/1/X7++W/7H+U+PT7P/B1BLAwQKAAAACAAtZ0pSYEhww8oCAAAhCAAAIAAJAGN1cmwtbWFzdGVyL2RvY3MvQ1VSTC1ESVNBQkxFLm1kVVQFAAG2SCRgjVXBdqIwFN37Fe+cbtqF/YDZoaJyisKQtGe6ohGCchoJJwlt/ft5QacFTOmslAv35uW+m5cbmMucQ86LsuIajIS81GwnOBScmUYhxqocaiWNzKTQk8nN
*/