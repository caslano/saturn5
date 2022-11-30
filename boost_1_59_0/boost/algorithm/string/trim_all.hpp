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
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
*/