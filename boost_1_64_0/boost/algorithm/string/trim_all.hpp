//  Boost string_algo library trim.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_TRIM_ALL_HPP
#define BOOST_STRING_TRIM_ALL_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/find_format.hpp>
#include <boost/algorithm/string/formatter.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <locale>

/*! \file
    Defines trim_all algorithms.
    
    Just like \c trim, \c trim_all removes all trailing and leading spaces from a 
    sequence (string). In addition, spaces in the middle of the sequence are truncated
    to just one character. Space is recognized using given locales.

    \c trim_fill acts as trim_all, but the spaces in the middle are replaces with 
    a user-define sequence of character.

    Parametric (\c _if) variants use a predicate (functor) to select which characters
    are to be trimmed.. 
    Functions take a selection predicate as a parameter, which is used to determine 
    whether a character is a space. Common predicates are provided in classification.hpp header.

*/

namespace boost {
    namespace algorithm {

        // multi line trim  ----------------------------------------------- //

        //! Trim All - parametric
        /*!
            Remove all leading and trailing spaces from the input and
            compress all other spaces to a single character.
            The result is a trimmed copy of the input

            \param Input An input sequence
             \param IsSpace A unary predicate identifying spaces
            \return A trimmed copy of the input
        */
        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_all_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            return 
                ::boost::find_format_all_copy(      
                    ::boost::trim_copy_if(Input, IsSpace),
                    ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                    ::boost::dissect_formatter(::boost::head_finder(1)));
        }


        //! Trim All
        /*!
            Remove all leading and trailing spaces from the input and
            compress all other spaces to a single character.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param IsSpace A unary predicate identifying spaces
        */
        template<typename SequenceT, typename PredicateT>
        inline void trim_all_if(SequenceT& Input, PredicateT IsSpace)
        {
            ::boost::trim_if(Input, IsSpace);
            ::boost::find_format_all(       
                Input,          
                ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                ::boost::dissect_formatter(::boost::head_finder(1)));
        }


        //! Trim All
        /*!
            Remove all leading and trailing spaces from the input and
            compress all other spaces to a single character.
            The result is a trimmed copy of the input

            \param Input An input sequence
            \param Loc A locale used for 'space' classification
            \return A trimmed copy of the input
        */
        template<typename SequenceT>
        inline SequenceT trim_all_copy(const SequenceT& Input, const std::locale& Loc =std::locale())
        {
            return trim_all_copy_if(Input, ::boost::is_space(Loc));
        }


        //! Trim All
        /*!
            Remove all leading and trailing spaces from the input and
            compress all other spaces to a single character.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param Loc A locale used for 'space' classification
            \return A trimmed copy of the input
        */
        template<typename SequenceT>
        inline void trim_all(SequenceT& Input, const std::locale& Loc =std::locale())
        {
            trim_all_if(Input, ::boost::is_space(Loc));
        }


        //! Trim Fill - parametric
        /*!
            Remove all leading and trailing spaces from the input and
            replace all every block of consecutive spaces with a fill string
            defined by user.
            The result is a trimmed copy of the input

            \param Input An input sequence
            \param Fill A string used to fill the inner spaces
            \param IsSpace A unary predicate identifying spaces
            \return A trimmed copy of the input
        */
        template<typename SequenceT, typename RangeT, typename PredicateT>
        inline SequenceT trim_fill_copy_if(const SequenceT& Input, const RangeT& Fill, PredicateT IsSpace)
        {
            return 
                ::boost::find_format_all_copy(      
                    ::boost::trim_copy_if(Input, IsSpace),
                    ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                    ::boost::const_formatter(::boost::as_literal(Fill)));
        }


        //! Trim Fill
        /*!
            Remove all leading and trailing spaces from the input and
            replace all every block of consecutive spaces with a fill string
            defined by user.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param Fill A string used to fill the inner spaces
            \param IsSpace A unary predicate identifying spaces
        */
        template<typename SequenceT, typename RangeT, typename PredicateT>
        inline void trim_fill_if(SequenceT& Input, const RangeT& Fill, PredicateT IsSpace)
        {
            ::boost::trim_if(Input, IsSpace);
            ::boost::find_format_all(       
                Input,          
                ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                ::boost::const_formatter(::boost::as_literal(Fill)));
        }


        //! Trim Fill
        /*!
            Remove all leading and trailing spaces from the input and
            replace all every block of consecutive spaces with a fill string
            defined by user.
            The result is a trimmed copy of the input

            \param Input An input sequence
            \param Fill A string used to fill the inner spaces
            \param Loc A locale used for 'space' classification
            \return A trimmed copy of the input
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT trim_fill_copy(const SequenceT& Input, const RangeT& Fill, const std::locale& Loc =std::locale())
        {
            return trim_fill_copy_if(Input, Fill, ::boost::is_space(Loc));
        }


        //! Trim Fill
        /*!
            Remove all leading and trailing spaces from the input and
            replace all every block of consecutive spaces with a fill string
            defined by user.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param Fill A string used to fill the inner spaces
            \param Loc A locale used for 'space' classification
            \return A trimmed copy of the input
        */
        template<typename SequenceT, typename RangeT>
        inline void trim_fill(SequenceT& Input, const RangeT& Fill, const std::locale& Loc =std::locale())
        {
            trim_fill_if(Input, Fill, ::boost::is_space(Loc));
        }


    } // namespace algorithm    

    // pull names to the boost namespace
    using algorithm::trim_all;
    using algorithm::trim_all_if;
    using algorithm::trim_all_copy;
    using algorithm::trim_all_copy_if;
    using algorithm::trim_fill;
    using algorithm::trim_fill_if;
    using algorithm::trim_fill_copy;
    using algorithm::trim_fill_copy_if;

} // namespace boost

#endif  // BOOST_STRING_TRIM_ALL_HPP

/* trim_all.hpp
6LPq6AtkIkWDcs7d2cRysVog+9RobhLBeURw7CGCKHEJ2sHc8BpGRO9c4c/ZbMuiGgztrf7YPMltC0jGcNWfJHStP/a8hG5myX0RdFXoZrNq3jceGQUfYz4ojxf5DGhvureOmWKDKtICVFmdX9voo+Vz3btAa0BE6CMd2PhE8Aa02AJ4zfMhTew8a9DqEAfwdlWh9Zk5PizZax/7yI8makZzaCIYlxPjzqolCnY2kbLnRd3VEloIOpVVo9lJ7Y3dAr6YQRE6mzw7ucmZ23QpVVIl5qS0OjGUynf/7U5Q4gy74d1JDW+D+yQ1vbuTUBte0Elnhk2nAOtS9QomFUU/E6Qa0EyFVkkI7ZFEaFZXQpP409UdmaXd9x+BKybtpDQ/uUYVTm1SbeYn16adR24SibndkFjPY45IIsRkMZRR2lwxTkSQGq8RmaoCCEoMCQpq2paUeamS0sbItWWlu4usVCjFtrTM6iItFYpLkZmbRCbwFbxOKHWB0m6pLLKpzO6WylqbxpxkGq3o5an0gfJuaGxQFGZ1S6E0Ns1ku6ex3qYwaz/1WPAZY45C8dh0uruvR2EpRWjefgh1dqpqOZ060MdnTZ4kWqTUI0tK1mCYHb01goG6TlLTslJUScEQGmxdCEkoekUXspLJtXWhnGRdyAIXp+hqrlQ6pcm6V9YYAby9f4VXpeCxSEwS46kk9rF4EjhK2SU6LXBpZz3mJau8Aq9PVchF0bAJlGawKczvhsLafaowr0sVuuwqzOuuCgs66cvqSp9S01iYZKRMaFqmTbqWiydTGhLBXhY8zLIMJlpRx7Ma6CN5ZpOROrNRSRV0zr5cybMvgQvDiKhEIsKVnAZTq9LItemV+swHzSn09kmeguUnTcGMNbDc0QDYQJQxtbtAQiZ3od16yTrdu4ZImlVLKYEIbRyqdi24Ata7kt1elGSXlFSj1QatI94AYfpJSQOom1XP4Wxb07Yabd5WWGtgwzFW6do2XyxMUO/Kko8QXt9jVh19GvXaz2Bd0zbH6yDsWktWeOu8qzC0z6rhyjRe13BCDqM0tDpteUkNjGSg2lvPHGssEyGDymiAucFf0ujzvs4VMisuTRGinrMURUdLLPGTA801Pu8ysT6s1lUeyOFMNBnMFKgRdM0V/hJURQ1hIC+M0YI1jnrZW506LkjwaajPZWTVqUZLVnubkNQoNCkUSBgPqRZhEPR5q0GSj+wcOKaKxhSxWOM3QG6jFIgoLUAT+o0mkdqLLduJF2UUO2eyDYVHGbGhEGFF3TGdkFjaSWI+EWSRWawrhbwZroh3waJF1bqadJc+pbq2BqWEQcu729uBVkbz7KLKRiINeWT7q0VxVvmoZUCUz1jn864nwQKihCAZQoQUcIDPWGqc7PditQ3FksIi9R0+6mZxVPhiP2g3mv0ylMO6Ra0hTM6imkQKmphGCBiVvKypIHMP4QzQVhlw6+OHsMZzEKi9yK996geRJEmX+aLTXaj5qIMF2DZdqyFDN2mJA7lnvREyxPKmY7rc4RM3ezB3c303s3XcF73AyRby6bnRqzx8S8waM8FX+uDuHbKo851t+LwGh6eUdxgxxNv7bMQhzNfjz/T/v////v/7/+//v3+PX/mFo8fIwq3jSWuDbPvunuo0MY8XWOINxI5s7U+ehz7BkRE+xh3EoVvzd7/na6+cOKx/ElwIMABnQM31CFdnkBeb5U9gDwVtwWWweel1gMlx3RuVG4wLXkCQDEKXffcLHjBI9i919hOqBDXkDi+AIKZY/OUFis13n2qTq7kvnpdJ+LuxkYMuMmV/4E3szAjR+Jg7rprIME/7KzsG8qjFcygO1pU7IaDFCh9am4MV/mM=
*/