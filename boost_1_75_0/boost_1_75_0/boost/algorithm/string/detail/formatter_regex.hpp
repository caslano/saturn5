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
BOxyvDV6r0YHgly/wp90yPrzniJr3TOTV17DxkSUdHBLMhV9SD7aOFDjHB323Ss13tHz4n9PQkSrf1SYnAsRgFe76PhQlFvuC+9Y/FaGYywG6tpS8DcjCh5Yurb7YybCTSzZAblk4f/x5ih8AMoA7EAdKBH/Gl281ITHh+CI48Z0lCWbG+U1wsRFEPCGLt5oQieAsv3vdq/exIodJSXCxJ8JMIw2AB5w2mJJJgvnzPO+vWV5IAv/EVHwxnJRszvkOXAzzvJAHB4TXnDGclF9NJRtQsCOAo4oALNkC6GYR5jY4gJ6iMJbw012WNy+/XdExZ0Aa+D2WdhHX2HPmbz1QmVj8DcST8ITqbfzl4bKIouDaVQLn18uTWUKzzac7Fm0mimfugLCcCS1/5h0IOt3k3+7BNDYwc23e3Qx38lHXMR7AjOiEHfpcFr+gFHSHZeNWG05ky272Te9aSEF5A6NGhz/liP+LL6kLUxEGF9D7ttYfaOFaew9lsNEXmR+QMu+SUY7JKG5p0oSjbJaFTKlV4hvnxB082bw8nG+28jaTIizWcGeeIZbLNbCw6kOfdWrIaDHe8fbwKiZseQbG7hDlDKom4RwLGEy6JQkTMfg5cjaufI0XjDrC01tHmbpRr727WcPqryrd7S4rBOo4H8im/uEGI4mXT0v5RoInXX0ZArIRT0K0CJKqobaHyG1wvo9DXn0Z/1M+XzgLhf4
*/