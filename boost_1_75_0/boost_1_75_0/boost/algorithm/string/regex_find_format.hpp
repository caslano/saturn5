//  Boost string_algo library regex_find_format.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_REGEX_FIND_FORMAT_HPP
#define BOOST_STRING_REGEX_FIND_FORMAT_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/detail/finder_regex.hpp>
#include <boost/algorithm/string/detail/formatter_regex.hpp>

/*! \file
    Defines the \c regex_finder and \c regex_formatter generators. These two functors
    are designed to work together. \c regex_formatter uses additional information
    about a match contained in the regex_finder search result.
*/

namespace boost {
    namespace algorithm {

//  regex_finder  -----------------------------------------------//

        //! "Regex" finder 
        /*!
            Construct the \c regex_finder. Finder uses the regex engine to search
            for a match.
            Result is given in \c regex_search_result. This is an extension
            of the iterator_range. In addition it contains match results 
            from the \c regex_search algorithm.

            \param Rx A regular expression
            \param MatchFlags Regex search options
            \return An instance of the \c regex_finder object
        */
        template< 
            typename CharT, 
            typename RegexTraitsT>
        inline detail::find_regexF< basic_regex<CharT, RegexTraitsT> >
        regex_finder(
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type MatchFlags=match_default )
        {
            return detail::
                find_regexF< 
                    basic_regex<CharT, RegexTraitsT> >( Rx, MatchFlags );
        }

//  regex_formater  ---------------------------------------------//

        //! Regex formatter
        /*!
            Construct the \c regex_formatter. Regex formatter uses the regex engine to
            format a match found by the \c regex_finder. 
            This formatted it designed to closely cooperate with \c regex_finder.

            \param Format Regex format definition
            \param Flags Format flags
            \return An instance of the \c regex_formatter functor
        */
       template< 
            typename CharT, 
            typename TraitsT, typename AllocT >
        inline detail::regex_formatF< std::basic_string< CharT, TraitsT, AllocT > >
        regex_formatter( 
            const std::basic_string<CharT, TraitsT, AllocT>& Format,
            match_flag_type Flags=format_default )
        {
            return 
                detail::regex_formatF< std::basic_string<CharT, TraitsT, AllocT> >(
                    Format,
                    Flags );
        }

    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::regex_finder;
    using algorithm::regex_formatter;

} // namespace boost


#endif  // BOOST_STRING_REGEX_FIND_FORMAT_HPP

/* regex_find_format.hpp
yyXdk7hYweSL94/WLdSZtIE49tjjNJMeJKeMRudPZ23easOtFMCNNbn+cNAk1Zk/DrdMfKtKCvOBu+ppAWzw4pkYkZszhHD2w2rzTbL5heng3G/MxtPVl0jJuSeOK4mi9gt+1LSCAbiG9WBy2p/lO88HO3X5o+FqrgkTPdHvAripPNbEMBtHSVe4hajsps30pa/iGTd3EUPwyrHab5GGuO1PIyG1UOV7G1HxX7ORXW4SYeFh1pbdJha9hl/ynX/PyqKbV7svunh7hRQD15S+7jy68YxXavBtpR43l7lvDKCS9eEZMXeY+GSWL4YW9mfr9rq9D7nQ/5y+B3b7/YbFTINHH2imAn7EvaVOETt8tUvwwgU+df8P+F1NUKaN9FktSHLjL/H9i7AV1rvtACke8FQVtk4QlkhQo2fH13Db5VrstnaIwpEu24ZDYC7llOLa6mUVyKS4VaM2rzApL5PiFtdSZk2+tAzX30zK8/ujRX+H0nT9Mo/y/jOeXNLqjR0MvrcRttcpETFtORZou4cupeWEacMHG8yZzfP3Bin3WK7kc87KLswnpc5exA1PWHctAWI1WwsKZxA+SaMu1Et+3T+v+hzMeswXc7K/wV6erLdk55CrjlhvSd8gqXQ/zM7y2ENfmXWtVVSnOU0G0zhjOmo6nNpQMrCX8XPgWUki3ix0ZNk4N08uXNuTjzi+UDHXI0VGCUeWjwY97//e
*/