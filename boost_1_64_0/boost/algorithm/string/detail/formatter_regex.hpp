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
FmwiNrMYL4KrXcqt5/O7iZB5jGRgE/UQ+fNVEX3MsS5x5JZ9LCC/fABa6l0PUL7GUPaq8v2azSN9ItAFJAP3872Wep8JFGHuE29+TmjvM4JYmjLoG0oJfFslDB2tI/52qXFape8d9oOYTIdJoh/Sn9IaZU//g+X+5iqoclqPb9sD5qIxIWgZayNHYOBZdCKvJdnxqWbjqa1+TJ72nGWyze5Tl5n7pBuIT+V2yG5kQvKd5AsbkCFVlrNbkcwufIiy4ObCs4cs3cjbxbD8xGFdnukWbtcYHfXBpalz1YzHqm6I72uZIdE/HmCjH+JslTcOuzFu4EReBNQjg1vzo3ZWzSCoJNDYBRcGUnFpgN5Ie83w9hQNIIxW7RiglQYGqGNGqikKaNc0gFdlkoy6lmkPs9lEdKQuE0DoCl/bFCHlsqzh84kWZaVvGpl4qrYDJ55L/0VSuz4MaC2m74kb3aHuXhLO0MJA5m5BLyIUpgoDqU3GYp3c78gsLBruV4f2WUOxw6YtR/GQHpTrat1UpmCn8x7WkFa4JMsKMdz0yhSeZjTO2iX29ozwrJt3oA==
*/