//  Boost string_algo library find.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_HPP
#define BOOST_STRING_FIND_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/constants.hpp>

/*! \file
    Defines a set of find algorithms. The algorithms are searching
    for a substring of the input. The result is given as an \c iterator_range
    delimiting the substring.
*/

namespace boost {
    namespace algorithm {

//  Generic find -----------------------------------------------//

        //! Generic find algorithm
        /*!
            Search the input using the given finder.

            \param Input A string which will be searched.
            \param Finder Finder object used for searching.
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c RangeT::iterator or 
                \c RangeT::const_iterator, depending on the constness of 
                the input parameter.
        */
        template<typename RangeT, typename FinderT>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
        find( 
            RangeT& Input, 
            const FinderT& Finder)
        {
            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return Finder(::boost::begin(lit_input),::boost::end(lit_input));
        }

//  find_first  -----------------------------------------------//

        //! Find first algorithm
        /*!
            Search for the first occurrence of the substring in the input. 
            
            \param Input A string which will be searched.
            \param Search A substring to be searched for.
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c RangeT::iterator or 
                \c RangeT::const_iterator, depending on the constness of 
                the input parameter.

              \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<Range1T>::type>
        find_first( 
            Range1T& Input, 
            const Range2T& Search)
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::first_finder(Search));
        }

        //! Find first algorithm ( case insensitive )
        /*!
            Search for the first occurrence of the substring in the input. 
            Searching is case insensitive.
            
            \param Input A string which will be searched.
            \param Search A substring to be searched for.
            \param Loc A locale used for case insensitive comparison
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c Range1T::iterator or 
                \c Range1T::const_iterator, depending on the constness of 
                the input parameter.

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<Range1T>::type>
        ifind_first( 
            Range1T& Input, 
            const Range2T& Search,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::first_finder(Search,is_iequal(Loc)));
        }

//  find_last  -----------------------------------------------//

        //! Find last algorithm
        /*!
            Search for the last occurrence of the substring in the input. 
            
            \param Input A string which will be searched.
            \param Search A substring to be searched for.
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c Range1T::iterator or 
                \c Range1T::const_iterator, depending on the constness of 
                the input parameter.

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<Range1T>::type>
        find_last( 
            Range1T& Input, 
            const Range2T& Search)
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::last_finder(Search));
        }

        //! Find last algorithm ( case insensitive )
        /*!
            Search for the last match a string in the input. 
            Searching is case insensitive.
            
            \param Input A string which will be searched.
            \param Search A substring to be searched for.
            \param Loc A locale used for case insensitive comparison
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c Range1T::iterator or 
                \c Range1T::const_iterator, depending on the constness of 
                the input parameter.
        
            \note This function provides the strong exception-safety guarantee    
        */
        template<typename Range1T, typename Range2T>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<Range1T>::type>
        ifind_last( 
            Range1T& Input, 
            const Range2T& Search,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::last_finder(Search, is_iequal(Loc)));
        }

//  find_nth ----------------------------------------------------------------------//

        //! Find n-th algorithm 
        /*!
            Search for the n-th (zero-indexed) occurrence of the substring in the 
            input.         
            
            \param Input A string which will be searched.
            \param Search A substring to be searched for.
            \param Nth An index (zero-indexed) of the match to be found.
                For negative N, the matches are counted from the end of string.
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c Range1T::iterator or 
                \c Range1T::const_iterator, depending on the constness of 
                the input parameter.
        */
        template<typename Range1T, typename Range2T>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<Range1T>::type>
        find_nth( 
            Range1T& Input, 
            const Range2T& Search,
            int Nth)
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::nth_finder(Search,Nth));
        }

        //! Find n-th algorithm ( case insensitive ).
        /*!
            Search for the n-th (zero-indexed) occurrence of the substring in the 
            input. Searching is case insensitive.
            
            \param Input A string which will be searched.
            \param Search A substring to be searched for.
            \param Nth An index (zero-indexed) of the match to be found. 
                For negative N, the matches are counted from the end of string.
            \param Loc A locale used for case insensitive comparison
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c Range1T::iterator or 
                \c Range1T::const_iterator, depending on the constness of 
                the input parameter.


            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<Range1T>::type>
        ifind_nth( 
            Range1T& Input, 
            const Range2T& Search,
            int Nth,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::nth_finder(Search,Nth,is_iequal(Loc)));
        }

//  find_head ----------------------------------------------------------------------//

        //! Find head algorithm
        /*!
            Get the head of the input. Head is a prefix of the string of the 
            given size. If the input is shorter then required, whole input is considered 
            to be the head.

            \param Input An input string
            \param N Length of the head
                For N>=0, at most N characters are extracted.
                For N<0, at most size(Input)-|N| characters are extracted.
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c Range1T::iterator or 
                \c Range1T::const_iterator, depending on the constness of 
                the input parameter.

            \note This function provides the strong exception-safety guarantee
        */
        template<typename RangeT>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
        find_head( 
            RangeT& Input, 
            int N)
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::head_finder(N));
        }

//  find_tail ----------------------------------------------------------------------//

        //! Find tail algorithm
        /*!
            Get the tail of the input. Tail is a suffix of the string of the 
            given size. If the input is shorter then required, whole input is considered 
            to be the tail.

            \param Input An input string
            \param N Length of the tail. 
                For N>=0, at most N characters are extracted.
                For N<0, at most size(Input)-|N| characters are extracted.
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c RangeT::iterator or 
                \c RangeT::const_iterator, depending on the constness of 
                the input parameter.


            \note This function provides the strong exception-safety guarantee
        */
        template<typename RangeT>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
        find_tail( 
            RangeT& Input, 
            int N)
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::tail_finder(N));
        }

//  find_token --------------------------------------------------------------------//

        //! Find token algorithm
        /*!
            Look for a given token in the string. Token is a character that matches the
            given predicate.
            If the "token compress mode" is enabled, adjacent tokens are considered to be one match.
            
            \param Input A input string.
            \param Pred A unary predicate to identify a token
            \param eCompress Enable/Disable compressing of adjacent tokens
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c RangeT::iterator or 
                \c RangeT::const_iterator, depending on the constness of 
                the input parameter.
        
            \note This function provides the strong exception-safety guarantee    
        */
        template<typename RangeT, typename PredicateT>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
        find_token( 
            RangeT& Input,
            PredicateT Pred,
            token_compress_mode_type eCompress=token_compress_off)
        {
            return ::boost::algorithm::find(Input, ::boost::algorithm::token_finder(Pred, eCompress));
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find;
    using algorithm::find_first;
    using algorithm::ifind_first;
    using algorithm::find_last;
    using algorithm::ifind_last;
    using algorithm::find_nth;
    using algorithm::ifind_nth;
    using algorithm::find_head;
    using algorithm::find_tail;
    using algorithm::find_token;

} // namespace boost


#endif  // BOOST_STRING_FIND_HPP

/* find.hpp
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
*/