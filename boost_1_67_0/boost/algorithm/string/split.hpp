//  Boost string_algo library split.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_SPLIT_HPP
#define BOOST_STRING_SPLIT_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/compare.hpp>

/*! \file
    Defines basic split algorithms. 
    Split algorithms can be used to divide a string
    into several parts according to given criteria.
    
    Each part is copied and added as a new element to the
    output container.
    Thus the result container must be able to hold copies
    of the matches (in a compatible structure like std::string) or
    a reference to it (e.g. using the iterator range class).
    Examples of such a container are \c std::vector<std::string>
    or \c std::list<boost::iterator_range<std::string::iterator>>
*/

namespace boost {
    namespace algorithm {

//  find_all  ------------------------------------------------------------//

        //! Find all algorithm
        /*!
            This algorithm finds all occurrences of the search string
            in the input.
            
            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& find_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search)
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search) );        
        }

        //! Find all algorithm ( case insensitive ) 
        /*!
            This algorithm finds all occurrences of the search string
            in the input. 
            Each part is copied and added as a new element to the
            output container. Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            Searching is case insensitive.

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \param Loc A locale used for case insensitive comparison
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& ifind_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc) ) );        
        }


//  tokenize  -------------------------------------------------------------//

        //! Split algorithm
        /*! 
            Tokenize expression. This function is equivalent to C strtok. Input
            sequence is split into tokens, separated by separators. Separators 
            are given by means of the predicate.

            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>
    
            \param Result A container that can hold copies of references to the substrings          
            \param Input A container which will be searched.
            \param Pred A predicate to identify separators. This predicate is 
                supposed to return true if a given element is a separator.
            \param eCompress If eCompress argument is set to token_compress_on, adjacent 
                separators are merged together. Otherwise, every two separators
                delimit a token.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename RangeT, typename PredicateT >
        inline SequenceSequenceT& split(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            PredicateT Pred,
            token_compress_mode_type eCompress=token_compress_off )
        {
            return ::boost::algorithm::iter_split(
                Result,
                Input,
                ::boost::algorithm::token_finder( Pred, eCompress ) );         
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find_all;
    using algorithm::ifind_all;
    using algorithm::split;    

} // namespace boost


#endif  // BOOST_STRING_SPLIT_HPP


/* split.hpp
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
*/