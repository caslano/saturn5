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
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
*/