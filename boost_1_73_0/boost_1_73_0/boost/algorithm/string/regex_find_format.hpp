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
F65tsHDXSV47ta1duZ6rM9WWdmVNlvT+LRw27G0R/9oyszc2a3UOe8qmtsu2cThso2+i52yt3LZUVMGVOk8a7Rs43uvGesqfJ8n3bd1FPER2BVvDsXWbMyLfOd/QZ5BXiCHwq2gnHmgrOCBTS5phkqvcLo/TjUmvfZ3Oq/xK+bS2VYO4ljfuGnu2ttmoKzgcwYvrrpSrFXxVUkpmVrrNGzwmDP2ytZDud9C7CF7lm0bpVYMwXc2PYXl052xmSr3MzUxicSXmLA12IPtoKTILjixdXeg83+EBUpgU2FKoFVTQ5Q6pJQFyee62knvr1mYmt6XxUwWBO9eqn1rfJKWBMViaukpMjz7TOfNvJ2cyweXLoIToMrxjEuF/6ZJK141N21zX0KktW89wiue5HTuVN+L+EI0k+ZGHeOSKq69hY52hHpA4tmHM9yVH8Vtdl3g7W9WGVYN9uShU6J9cnaDiGphd+JDJpVqb0tQ4nStZf+VODdZ4VTnvLbw1V+f9MW55Y13r812ytZCeahjeneuVvKOjl1A6TU3VMGv8zNKQe/fUS12wZJLLmh6jARrLyxmDGv4uZQWyCMlnJEo7+oQFuWrLtLGuDPrf6Noy+gl2RBzJnPHlUYPFQBaP7/AwakMiXBhdBgsYUb9xLdKM
*/