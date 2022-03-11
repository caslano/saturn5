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