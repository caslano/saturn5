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
Nl5gHYAF+VlUkHp7Gs/jFWqFXBEwN3b3FwnwZzarSj5QgpSx0ySl2iYVcl5kVuhkXaFRs8wKzZ1Ir4f8FpBldpHfG1VfTfI8WwQZXkY6NZk+vAa6nIZDyaAsP8IomlobSSkqTxdOJiEqZbLVD0TIx5Mk7RxK+y4QVZ3FOq0DVwcnEVQf2bNiHDTcIanf0txZiQ/TlukLRIjYgBWBJtGT+YxWenhQOvihOj2LJSqGf5GNhSAGqLsjsPw2hmuaLpgIzch8OWwGeUuR4oLIwVvcu5iQovGI8+bJXQu9DxwvKYOpog4q4HSrgCI3NUIYeeMQqbrQmE80zr7QpLHIoVZjOvBbprXphK0Cn2Wztdz2hshtV2DHFRxYjP66S228kmgVxkKrRyIxkcDFQKj1Av4geLqxxGeMzPIZN2I3/Llm6P+Zxzv/dX8N73a9dHREU7L0RC826X1axk3mnkoMHYorCoqXo8uMhyl1FSZCMRhDjGOBGKr2Rwfmu+gULx6STehdjJFkddEw6sf+WJXXLGrN3suvAFKNohR7BZ59vW/nQKrKlEC6OkMCmeo0CWSpThJwqbYS8Cq7BPLV3smMk7eS1TdwmK/lvi7hWXKm2ellunL6GCUMuYsOJ38r8ftfkuPIixDpbYFnuqw/PtDEOo7bUrGQQzns9ZVAJl3G4XxfiS2yLEQlVzaTPzMifxbyVzZJT4lIT43Anx6F3/L/faN5V3nCV+1jSHZpqxr60EIWPxIRBxVTLPlH8mM0jGB5xDV4e8iiP/HA8jbfINLHMoa2uQX6APs3gYLaF5JHStA7ER0zGhsi1Xi+tR3LAAPJ15ukQSyp3GBuxhYMa3KHeKmrwMbaiKG8ucdw46q6gOI4jeLn0Sj8w2hMXCZjouavMiZ+NqsJXjTb+bVms5Vnc7OlIQLrCu3xoThoA60BWS76iAdOnCKbUSrvKub5PzPVXKCkGKUELx2r3rlcNiKLZjYtrWRacm1r9cF0MSSjGUVb2hR16iSOSfSaN1HHENv9HU1CPdsML4jZ0aZk0GiZd3fdxHz+YT1Ps2jwnMTzFCjaE4pbAYaWyK0ZxXrQyh9oBdhyf/r8Y3x4f9gAaduoBhPisTQxKzyWmtvPaPsvnZ+2iXuAxcXvC20l5Uw8NQK0VNO8MQhjCWqLcH5MoDX6j2/mX0iW2K1Vw0hq7RtdBHIcs57NHDPJC0COyVdrOGZafoTCSGwSIBMcob4o8i/afkdX5dfjwlXZjaqgiK/NejDtWTGBE4n242UUiSGOlA7aUZOzhO5MppvZ6slCdxbDM/Gc6YeQ3Hz7bx4bJrqGepFpj6Y7NbLNhdLiK5nSFJPSVHUrx0wjZRHHpKtrOObG9BZqc2/JcVd82b7peePpY6P53bnWYWXrqNUzWh+5fYy1ixNbJb/hchGTtrtDq3llTCVpCq82xOAP1QLYANqQyOK5+ghNHqP+DPfo7ostSOv8UyjxGyXEBK2VPJi/QbW5me2mE1jHkA5VA63nNsfj8mnhaY5fOwSr8Ou9QS9dAPvqBfDr7DMtk8nJjuQEd+k5wlHfRqKjfYwjeUiyo7032ZE8INXR3pWK70x8Z+LbhW8XvvPxnY/vAnxDLeJQZ2XKATxQtovmS+5Sp2C/9QXh15MhvJb9TsucFwiXvRxpppb/CTUmX9tyO8t/LG8jVnyJlpVCheYoR3vYYdhI59vPoz2+mErLSpqQuRwxfHVw6pGIGiQiRMsHtih4Eg2i092uyG9IG03hs5rAj2/ynd7kO7XJd8oh5RUM9ibfI5p8F1Q2z99kUJVdJ6qVvWhDNOUOtNjDz5Gi16UazrKGlddd2gnQJVO8SJ+CdNovtD7bGiMdZIw=
*/