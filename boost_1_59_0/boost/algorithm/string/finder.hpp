//  Boost string_algo library finder.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FINDER_HPP
#define BOOST_STRING_FINDER_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>

#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/detail/finder.hpp>
#include <boost/algorithm/string/compare.hpp>

/*! \file
    Defines Finder generators. Finder object is a functor which is able to 
    find a substring matching a specific criteria in the input.
    Finders are used as a pluggable components for replace, find 
    and split facilities. This header contains generator functions 
    for finders provided in this library.
*/

namespace boost {
    namespace algorithm {

//  Finder generators ------------------------------------------//
        
        //! "First" finder 
        /*!
            Construct the \c first_finder. The finder searches for the first
            occurrence of the string in a given input.
            The result is given as an \c iterator_range delimiting the match.

            \param Search A substring to be searched for.
            \return An instance of the \c first_finder object
        */
        template<typename RangeT>
        inline detail::first_finderF<
            BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type,
            is_equal>
        first_finder( const RangeT& Search )
        {
            return 
                detail::first_finderF<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<RangeT>::type,
                        is_equal>( ::boost::as_literal(Search), is_equal() ) ;
        }

        //! "First" finder
        /*!
            \overload
        */
        template<typename RangeT,typename PredicateT>
        inline detail::first_finderF<
            BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type,
            PredicateT>
        first_finder( 
            const RangeT& Search, PredicateT Comp )
        {
            return 
                detail::first_finderF<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<RangeT>::type,
                    PredicateT>( ::boost::as_literal(Search), Comp );
        }

        //! "Last" finder
        /*!
            Construct the \c last_finder. The finder searches for the last
            occurrence of the string in a given input.
            The result is given as an \c iterator_range delimiting the match.

            \param Search A substring to be searched for.
            \return An instance of the \c last_finder object
        */
        template<typename RangeT>
        inline detail::last_finderF<
            BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type,
            is_equal>
        last_finder( const RangeT& Search )
        {
            return 
                detail::last_finderF<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<RangeT>::type,
                    is_equal>( ::boost::as_literal(Search), is_equal() );
        }
        //! "Last" finder
        /*!
            \overload
        */
        template<typename RangeT, typename PredicateT>
        inline detail::last_finderF<
            BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type,
            PredicateT>
        last_finder( const RangeT& Search, PredicateT Comp )
        {
            return 
                detail::last_finderF<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<RangeT>::type,
                    PredicateT>( ::boost::as_literal(Search), Comp ) ;
        }

        //! "Nth" finder
        /*!
            Construct the \c nth_finder. The finder searches for the n-th (zero-indexed)
            occurrence of the string in a given input.
            The result is given as an \c iterator_range delimiting the match.

            \param Search A substring to be searched for.
            \param Nth An index of the match to be find
            \return An instance of the \c nth_finder object
        */
        template<typename RangeT>
        inline detail::nth_finderF<
            BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type,
            is_equal>
        nth_finder( 
            const RangeT& Search, 
            int Nth)
        {
            return 
                detail::nth_finderF<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<RangeT>::type,
                    is_equal>( ::boost::as_literal(Search), Nth, is_equal() ) ;
        }
        //! "Nth" finder
        /*!
            \overload
        */
        template<typename RangeT, typename PredicateT>
        inline detail::nth_finderF<
            BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type,
            PredicateT>
        nth_finder( 
            const RangeT& Search, 
            int Nth, 
            PredicateT Comp )
        {
            return 
                detail::nth_finderF<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<RangeT>::type,
                    PredicateT>( ::boost::as_literal(Search), Nth, Comp );
        }

        //! "Head" finder
        /*!
            Construct the \c head_finder. The finder returns a head of a given
            input. The head is a prefix of a string up to n elements in
            size. If an input has less then n elements, whole input is 
            considered a head.
            The result is given as an \c iterator_range delimiting the match.

            \param N The size of the head
            \return An instance of the \c head_finder object
        */
        inline detail::head_finderF
        head_finder( int N )
        {
            return detail::head_finderF(N);
        }
        
        //! "Tail" finder
        /*!
            Construct the \c tail_finder. The finder returns a tail of a given
            input. The tail is a suffix of a string up to n elements in
            size. If an input has less then n elements, whole input is 
            considered a head.
            The result is given as an \c iterator_range delimiting the match.

            \param N The size of the head
            \return An instance of the \c tail_finder object
        */
        inline detail::tail_finderF
        tail_finder( int N )
        {
            return detail::tail_finderF(N);
        }

        //! "Token" finder
        /*!
            Construct the \c token_finder. The finder searches for a token 
            specified by a predicate. It is similar to std::find_if 
            algorithm, with an exception that it return a range of
            instead of a single iterator.

            If "compress token mode" is enabled, adjacent matching tokens are 
            concatenated into one match. Thus the finder can be used to 
            search for continuous segments of characters satisfying the 
            given predicate.

            The result is given as an \c iterator_range delimiting the match.

            \param Pred An element selection predicate
            \param eCompress Compress flag
            \return An instance of the \c token_finder object
        */
        template< typename PredicateT >
        inline detail::token_finderF<PredicateT>
        token_finder( 
            PredicateT Pred, 
            token_compress_mode_type eCompress=token_compress_off )
        {
            return detail::token_finderF<PredicateT>( Pred, eCompress );
        }

        //! "Range" finder
        /*!
            Construct the \c range_finder. The finder does not perform 
            any operation. It simply returns the given range for 
            any input. 

            \param Begin Beginning of the range
            \param End End of the range
            \return An instance of the \c range_finger object
        */
        template< typename ForwardIteratorT >
        inline detail::range_finderF<ForwardIteratorT>
        range_finder(
            ForwardIteratorT Begin,
            ForwardIteratorT End )
        {
            return detail::range_finderF<ForwardIteratorT>( Begin, End );
        }

        //! "Range" finder
        /*!       
            \overload
        */
        template< typename ForwardIteratorT >
        inline detail::range_finderF<ForwardIteratorT>
        range_finder( iterator_range<ForwardIteratorT> Range )
        {
            return detail::range_finderF<ForwardIteratorT>( Range );
        }

    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::first_finder;
    using algorithm::last_finder;
    using algorithm::nth_finder;
    using algorithm::head_finder;
    using algorithm::tail_finder;
    using algorithm::token_finder;
    using algorithm::range_finder;

} // namespace boost


#endif  // BOOST_STRING_FINDER_HPP

/* finder.hpp
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
*/