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