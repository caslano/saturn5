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
jYEooX0uXK3BnyoL3hvgbI5zUwW6LJUmfBHPo33zTX9+cUyzh4NlCR//v5oQB4hreHM6eHpaqzlOtIjGvojl2/yt4vkPKz+byq84nfIpYeW7U/kHK1PeYziKKsL3xTw7vm+mAd/KcHxg9ilrL7L41d/3lWoNJp/T2f+XVBdIziwNVmL9zwvrPyFdVWF9N1DWY1Jfu4rq2+CpTH0xYfXVBtLYsUGS/kXfVh3sYVidgjcAlaFT2v/N1diq8/J4C6Dh9m9zw9dPY/AkZfovEMaH6sIbeKMZ70q1pcQeVCaeXoe5WpkEFkCsvXcs93jQ1wJ4jI2pdXPOuZH1tecfB+y8qdXhET+4KTXBd9hV+H1Tf9t67oJGtKV80Z5RO3GMtFwG1fkW6bTVNxAfPRIqzyn+wcE9h+BH3xHcZNPPLtriDkZ59hz1+DOj4fsZwYiqpC5yn/TkHnL4PvNfcRK6+P4rgj23IE4svvJnFr1muvMvY53BrPyqmYYQ1d8djS+yfalrjh5jnL8/b3Lk1MbaCtl8GkVsW7qqzaY9R42jkDTU8veBgvyeed0uicqJDhZLAIJa95LGSSdmInvR8OxmH8BlrUrzDs7pkI7yKXvdewJe/xUOd3Ajjz/iOUVBYzyaHLXmbor27DnWc1GVupnQMfN9yeX9vYOMDGOVaWzCcNWNOl2b1PD1PkSWYL3Z4Z2vLv6KrsMqx2qSMMQkmsmG0MLLVoPGt27jZIZ/ThV0ppM53+S6d9T+9DbFiB2HILQTYkjeN70/Immui46i7qXvilExx7r+cvs+Uh/z96L5T0/t2MFXy98rqL9jODd7Rr2D4XxzCQ3nZmrgq25Lu7NOyTjRo1vUn9hJNANNSMH4mfVnjtopTfDEvKMCqNhef3pMKTfgPTTgHGnAvG4donw1qQEr53VLjsqpljlqy5YqSVi9m72m30V+AsQlH13ngfljblK0HhNYacaUHOn9P0t2789ZkDLk0NUaUwW7TNrDzbCDjY/TUjvk1F8y/xfevzVo/xalpSb7vnUV/tCUJizb+JbHKdu9vgpbe9AJDf0xrNs2+zmaXmbMTvUtRpQsbegdnq7w8+HQOw5xwZ6IEtrgiNLj2GtXzNGYAIbxzdzN0Zip+otrRWHORO9UVU8zRR5Q96Pd4rpnGZktLKH6drZ536pvDuqjeqC8Jein9J8Pn1XBIElOjLc3BmrM/zwYg7o3RuH6jyx4PpDgG9WMTYv6Oehbb9CV4phF55S0BI+aiVjqkBoa75IKfvO+WB+XbTzkXHQOjF5cr6LSRdXcMaX40fUH190TQdFvLK4GVWBy2O/On4AvX+ZUycrv1gLx0TkYZMiak3aZlkKd6WY7g7+UDamOnLrdzUndGNwwr3MUUeXSpkUR9H9maGvprYgDlGHzPubOPRY9myKi8C9E1KG44NEUyJHiN/rnRSUFg92DGJFpXQFa5fZ9AIlBzLlojnzlnx/VgvJjkP+6e/4GgpY0YKgBDEijOWRH0ZmILNN1a7qr31a3sYdPtcsGV8bj5qn9EUyczr0SZwSqOgui0MEiiEJDPggC0VhRlcPXNAzfuvyK8TW6trL4dk2z4xt3CnyugZXFNzcMX6NT4Ftdvn3l/T8KJqP2N3fXgyLPTcI1n4dt+xESQKfTc1iYdKvBvy7FL/PFIOm3/SNb/b/N3t6sK5k7EOtcW3v/0SNi//2x21aW83fpE8xQsvbV8hg1WHr24MLKNBL4qjO+0O91S8J/P3t/Gf+oS8N/5y8O/93o3jLwy8r4Sy2TP2x5+O8D9+F3ReO32GfeqiBCyQ3UyGlLquU16L9Lco85fO5MKMmQiH7BJNZ76VDGcRNiUEID5wEvK0g=
*/