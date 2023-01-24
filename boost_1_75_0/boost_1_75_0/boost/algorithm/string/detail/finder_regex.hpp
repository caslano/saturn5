//  Boost string_algo library find_regex.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FINDER_REGEX_DETAIL_HPP
#define BOOST_STRING_FINDER_REGEX_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/regex.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  regex find functor -----------------------------------------------//

            // regex search result
            template<typename IteratorT>
            struct regex_search_result : 
                public iterator_range<IteratorT>
            {
                typedef regex_search_result<IteratorT> type;
                typedef iterator_range<IteratorT> base_type;
                typedef BOOST_STRING_TYPENAME base_type::value_type value_type;
                typedef BOOST_STRING_TYPENAME base_type::difference_type difference_type;
                typedef BOOST_STRING_TYPENAME base_type::const_iterator const_iterator;
                typedef BOOST_STRING_TYPENAME base_type::iterator iterator;
                typedef boost::match_results<iterator> match_results_type;

                // Construction

                // Construction from the match result
                regex_search_result( const match_results_type& MatchResults ) :
                    base_type( MatchResults[0].first, MatchResults[0].second ),
                    m_MatchResults( MatchResults ) {}
                
                // Construction of empty match. End iterator has to be specified
                regex_search_result( IteratorT End ) :
                    base_type( End, End ) {}

                regex_search_result( const regex_search_result& Other ) :
                    base_type( Other.begin(), Other.end() ),
                    m_MatchResults( Other.m_MatchResults ) {}

                // Assignment
                regex_search_result& operator=( const regex_search_result& Other )
                {
                    base_type::operator=( Other );
                    m_MatchResults=Other.m_MatchResults;
                    return *this;
                }

                // Match result retrieval
                const match_results_type& match_results() const
                {
                    return m_MatchResults;
                }

            private:
                // Saved match result
                match_results_type m_MatchResults;
            };

            // find_regex
            /*
                Regex based search functor
            */
            template<typename RegExT>
            struct find_regexF
            {
                typedef RegExT regex_type;
                typedef const RegExT& regex_reference_type;
                    
                // Construction
                find_regexF( regex_reference_type Rx, match_flag_type MatchFlags = match_default ) : 
                    m_Rx(Rx), m_MatchFlags(MatchFlags) {}   

                // Operation
                template< typename ForwardIteratorT >
                regex_search_result<ForwardIteratorT>
                operator()( 
                    ForwardIteratorT Begin, 
                    ForwardIteratorT End ) const
                {
                    typedef ForwardIteratorT input_iterator_type;
                    typedef regex_search_result<ForwardIteratorT> result_type;

                    // instantiate match result
                    match_results<input_iterator_type> result;
                    // search for a match
                    if ( ::boost::regex_search( Begin, End, result, m_Rx, m_MatchFlags ) )
                    {
                        // construct a result
                        return result_type( result );
                    }
                    else
                    {
                        // empty result
                        return result_type( End );
                    }
                }

            private:
                regex_reference_type m_Rx; // Regexp
                match_flag_type m_MatchFlags;     // match flags
            };

        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FIND_DETAIL_HPP

/* finder_regex.hpp
46hAoY+89vLPVIbLVtu91vM4a1BNZUDn9Otl5uO6+0UTUIuvDERqmfEvpyz5ONEjdQCjAMEL9udybIxV2rlpk2VQXKOCsMKVinMbOXT4eVExN/IuwhOZydkhS+H8TznW83uTvwfNv6Okr+BY5Ng+SnsPGlwwkKudSodcD/8taN/sATtpMtvzCNWMlEudtcSAV1aBZ+eoh12hAX8Y1f2LXQrcIs1VT/B5Cekq0tTWndKcPSFfhxgHzsRx1UxVK1rFOs2KLrRE4lBlYxl4Wox1cQ5KqJs+BpYIabmB9jm33O/+X3zP1i/equLP9FIuh3X+Pc8bOZ6q/iZsbUCsTSNCM5kh9U79mGORKWbjjfXN2lHPmpl10NyeyMHr6h77fm7CYPWMGt7SFqwe/gRynKqfDG0c6pabIs23SZYXq2oOhvCuAAPnvpfX49736b82ZIu1iXO3Gm9CHJY3Ps4bckTLA2YxuI6fEXjj0vkf0o680oeAxt6LYbt0kBvxai7SPT5qGu+s2y2F1/4mkYrXLuLYyJcnUTHK5TbrwXPR+M6QKTFpWKLJm1Zq0IzOZ7Grtz8AIaDmesoY0SVW9KtjkF0AVl6XoWJonU6L+KCKvVI2Eg5ALl3Y1VZ0+L20iMTwSSWNQifWmyWnZNWcGM2P47X4DN2Jp5I5tUvq8yc+tEI66R+OfrUe1kfsiAGUPMgMqNhj409bdlU5tvGZi9KN
*/