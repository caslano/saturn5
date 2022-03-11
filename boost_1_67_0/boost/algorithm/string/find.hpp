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