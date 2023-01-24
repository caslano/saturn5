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
X+2kw8iIEO6ncHBvwsCeJoTiQxGofwy1xxU3R+BMonfyT0m5eHzNg2aI0Ve21cKKTx1YBOER/btz7HYItTV4bfjtPIFzzv7TdSTCaOoHDqFgLe+zovM4uwRe1RrLdT4uLyyZyaymcFQxVPuDCruVHc3mRnC9Rl3PTn5DIg3RIk7a2gFzEDj4KXPbm4LIa06z3E2391Omp3vffBgOTvlUi19hdadh6Z1MqdHkvQU2IWPYzslts0bXgIoroQVl20eb7Ez8bj9YjIQrMptzysgai4iRkZez3xC6pXY6ogZ7fzWfl8swRN00xHyegVs43gTafW6RhBiWy/hqrU5ZMxW16fAXG07x6s68Ua+STjZqQ8dWWTxW+DPu6DLWrmXI0zMJ0Rr8muj1pL/ynu9anwJsecaP1UuRfbOB8Yc3D5brudiZXz/W+uLxf1eFka33Pc1VGFWxrfdhQ0L6+8jxq7DibE57z6H92bgi7sBaR5M67dJmO/LgN+bgEdhybychMCLCDrhU52/jux2Liei73Eme8nt17bnM78u+6h6uJOFZY9fuXl/vK3K/377wsIPHko+zU2h0gEfH9253Z7KBd738owYK8ZgVW/mmRdAc4vyoqcWsYAMfMzXY8JiyHlTivXxIt+qxYwpuKJRtIxFond2mfu1GZWzJko9sWBfZZuzrbcjk6h1tl4DDbwmqvJT/MN9qhmwGZAEu/Dbh1N2O
*/