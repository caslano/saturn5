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
d3il7CCYguuwdDIp9NqCxCGgnaKBi+wHVPkuCXnBkElnlh9iZo0tzDD+XWYP0+W7s2+fnyeSDuEguRgeUBxSwMeso3tk0sm94Iq4/HasHuEDzlglwjUi45PbBxd8MT5gbs2uMhCAQAb66EMOxz+YI8wbDvwBqsuWvwtI44v75HetudykJQvCPmG2V2qrdwnCamWyvdpFhlV0Zse1+4uoTJfF9Anons04YhaStGgoa9G4hVx5YPvJx7utZEHaTYkmk5dQ013r3WTSndgpHfcOzpPr7++ctz8HJ3/myP8CUEsDBAoAAAAIAC1nSlKH0sRfTxUAAFM1AAAeAAkAY3VybC1tYXN0ZXIvZG9jcy9DT05UUklCVVRFLm1kVVQFAAG2SCRgrVttc9w2kv7OX4HIdWXrdl7iZHNX56rcli07WSfySyz7fDmVK+aQmBlEJDEhSI0n5R9/z9MNkBzFXsdbq3JZMyTQaDT65elu6JY5803XulXfuWZjOm+6rTVF31Zm1/pfbdFl2cutC6b0RV/bpjP47JrONqUtOdyv17Y1m96VtnKNDcY3Zuv3fLWyoTNFIm8j8WxKfGGEOAYVtm2CaezerG3e9S0o5cHsbVXxd+HbFsOdxxiQse9cIL/Zusr3WLI1q34TFll265Y5
*/