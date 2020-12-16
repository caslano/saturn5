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
mD9jHF00jkvCcUxRKyrEwb95CXLi2TqFQ+NF6zSBtYzdpv7jYtN+PUt7oD+mLn6CCMRVTqI0beZZ98g2FHH1n+Au3PnV6DRUNRbTd0jcYgxnfh3q+or5eguFeHM2xvfq7iS6z6Q/7N9VpEXZ0tws41NW1wyoK0jgsiKKSJfpfzCb3XYSfRWp97vUYY/aO8hy2VmH2xMGSkRlkYR3YXsodSFUsE0phDqPfb4IBEaFCUvduSFVZSFHNTmuModQU+vzSDjezwkq+4WfvrqMo0Yjkr9PxYhSi1IpPjxg2dIKhCJlr7HTInOq40B+YCMCdz+GXMcPA3o2VqEWq/unmoOdf62TgnvyC6Ota38UT87ryWvJ88rFw3rOz5PEbyefkUZ//eEiz3OKPM8tL9NTISbRNHzeWD2LrrzdmtfWLxaq8cDQMH+l89h3i0yWmruIsLzBv1XOo/SDM615Gjdb4vSE3oBdqtkCjC7G0FAq427+GoXLQ2d6o35vDsC1qI9mCKuBeD6i6CDoONNCc7SkP2tt4yBW3y+Q++0VvDFO0LmdPwsbSBTr0FsyBKh1tTYE+MUuAJtXQQQosGVf7vjD/tIGWvNFo61+MUye6tAn9ewWkhLOeiwZn4A64AOrK4CPdFi0sKoo/nlpDQxVRwaHpqltNCkyjwqpvzRGAgXeS2CjCOZEthL6b4h52sAPb0NlhXQCxBJjH+2TQQ8xj8PyrslgVIxSknjVZvX9XCZKJb7ck+e68g7zQKIRvGSQvVu/IBm92aGF15jsVFfzQ/UQpmlXzQpJZMeiQn4oIo4d+5VDa3fgve+ih03DAYz4kq5ev910rksC1mSHrhSnPVE+BbaJ8FEXc09qydwcA6d5kpHOlzDyycMtJFloJttlUFY6M9hOkqCwUgd3ZjftD9/Nwp9slnd8NrIFUt88XnXBzeqNqyCoU667d5wMIiUDnM90WFCO5/Ucl3KQ9M9Y/pdpvEcr+x9PEj7IfOn5l1oitphUP5pDENfkM0R3lOe7zki567x0p8gNstlRnjCkI6cyaD2MDhnksBXqcBJEnkvbID5TWOtE1Rtp/CN/BiYD8879k6VA22ODdC5ed27lXBYgJk7nPqp8+VmXf+5QM/HTQG12O0/nCuZ2dtv0Df4gsvdv+9Pyv0U2ffXBFcj/bPnXz6lA/mfLd66qQP5py980ogL550Kb/LOC+jfb8j+bXYH805a/+qYK5J+2/LEQypTT3xT7R4FiZ1DH2QOvuNNahP2qXNoVWzKbayEP6gjsdkTrBPHW2oLTiCXWlQ7ozfWXc4qy705Tc1wUxo0DZGKZwE71sQu8JEfle0U7EK6Sa7HjzZOCY8a96/ZnOlQr2TYty5VClbaT5eFltJPUYGxwhjS2h9D3HRoW9Nn1gLCYiczjzhYGs7a6dAowNKVS0+FMko24Vc4AJjJCm1yjiQP9/c5XKj1+y/M0pxkgP4LHycNUv0fDPMXAaI2fCsFKU3P/2i8senyrVdxRVnHmCASmknufySyg7Osu6CLE5MRK8t3leV/NzJYOt0XxfyKRzdXDi7tVLRRntn0po4HbZmh5D3WexZGx6yMvXmDar6qhY8IUkufoBk7miZxkNm/CpDKKwetYET9lpuV8DIzG6WkK29sTzLXas3V0WHu+XSHtmc/tmWy25+8Ty7ZnBeF5csaZt8f0TzHVbMsB9SUu9e51zMaxvRXEl1XFOUUXMF2nKJ8SKn/OtVR+lb18NSl/HGvit9ZrGtO/O/R6PcBW19/jsjF3sYhf7sgqDZqmOWAR6ckUo+alh2esXYpk5coI0GY13sGPJKxragULQ67pbQ4yy9zz75dBfpgDB9hW5W23Yv92YjU=
*/