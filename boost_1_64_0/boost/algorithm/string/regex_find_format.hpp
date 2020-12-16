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
OTXe+gCu9gOaHt6g+bRGv9FisZuvzPR5Td0b9+WYfm+LHt/S16+ZwfCHDvfsBz+V6d5k6tbX+KKHRac7o+DhaDDXF/2xhxSm/3ZfXN3KYyUBjG9jc9Fmn9GTBl3jqtwKowMSwFUR+w6csKHDtYEHdgewgSH+UXEQLInuHG/BG0zJG9F3cY/G9yALPkzXd77pL3lTL9mjl2xHy+rGG/rON0qa/TR3fS1Uslg3PgyWLArkNAZLwA5Z/pL3A1qjL2cTOiSGJ2OEk1knrlgHLJwDNCzkoBklFG9YqxGG2mDE/dqPciEj9YjfQVfhevCSrhtxPVKRhuB4SxHeNARm6BY406jzRyqcOmDAwGsWArPRDSOTeANVf5kMGDD6SYQeurGA0tpSBJQcGhAGIjSPQz3+yA9zUe4iPN0Izbd46OtgIDQVefBz0PEzpX6QvqShY7g7lSSH/Zpuq0v6v14NOYgKsu9/d8j9RIc4eWOo/wbozUevwCxoHb764isQPbLpen404xG7sMDUAA4YeZvw6R5Tvc3dM6NBEObiET2yBv+bPd5knHq8i3+AT9Z9IXXVOv+axtRNcF+x7GP3+8tY7+8FQDfloVM7bEl9WOK4j2PXaRnGRco7BB2cToTGbyPP8qXu/ttoCB2IC8BcsRGOlsWauH3mWzi+tb3TXvqQXKTzaSZXz+brULb8HjStNJa6/Xnb8E2uc64F1ulDN+CL3IZWiy9pNvOR0faaysHmqMPbqUJeAApMS49hpdTIe5k+lptP7eK6+g2D+HT+aZl8jL6gNdNYT376AK2knK9/jzEDeEfJgni4PRnX0tf4FogP3hVnZExHAPv4jOYdRSg9yWQ36xPyITNlSGBuz/I0h9NTnhZoyPj42l5pFBzYuZHkRFlNoNkMaDS0Zgd+XA0ITVaQzCrgtR6JLOvxEuB7mqfmB4Y0Btwj4oFoxp8QOvdHEyZMgGKi7/wovkszamjoaYo574hvSC+DhoBKerBaq3Fk3AtcFC0XxXgYr2YIi1IwgsuQY7SRvX0ybMzuX1bxStBbfuN9/dUCAMkJ5oRO/0Z6eE+B39jud4/caW7CPM9yz7PE7KWs5gscpOE2yG1aCF+/QsKfZqPh3xx7yKv+Cr+2l63aiRknQV3QyxrgiAe7CoeCNqga5lMq0tWU2HgkVlgCCGK05gGr97W9EFpPiLMYUdxGsMkTOBXjYWdcRVr2eAUdyCZkF2vbUNSIrIACFQKEEtjkTloq4XSmM+ErHVCh7UXlsHusCty1dWYoNvTe6WhdVR+4gzx3MO7xPmegc0ggURuYtZtaKQZJ3uYOmaR6uEO1sGoGhyy5frkerivQwx8WSM36hvwMHeLWp2DDNcBsaJ1eaB0NiZs5qMsJvL/qY/eVeR4EzXOKqd+Jd4SBtSa42xo/ds/M23ZNLzRQEj1nBgb6ensCsZmOAFzkVm3ZBmY9ckBuGp55dxOy+6T4tNxt7rFLIEPywtfYjBHBq+mFeeJVmWkId6BWSeGQbkVW/2oORPei6vo7CyXpwEaD+ESAw5Tvoq+6+0MSwMsUSYf/ir1ZX8VP2X92t8ley2oWtVdjspFq/xE4bP5rGGE0EFLsP4Cr+5DloMG8aWjKt5zizgYCMz6NBKZ1bbw4fGPdyTyJ9tsMvR9wSEHaEpYXpbjXvkeS8o5pLClv/DvLv8n01WH2xNAFx7ZDsUuWQr9F6N/B8r058C1GC1JAcAO/D51GQ9N5FLIW40NDxkC8EneFh/akLKvc5hPpFJ6mwolZ26tgJVoHNs2YcFxumvvO2tlICrTCgzHD6Gfe+j5n8Aa+zZlIWh2n/XyL0hf70X3XvXvte7/1C59wfXuXwZg1E8s=
*/