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
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
*/