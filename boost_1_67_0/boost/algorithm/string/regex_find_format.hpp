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