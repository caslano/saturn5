/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#ifndef BOOST_ALGORITHM_KNUTH_MORRIS_PRATT_SEARCH_HPP
#define BOOST_ALGORITHM_KNUTH_MORRIS_PRATT_SEARCH_HPP

#include <vector>
#include <iterator>     // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/algorithm/searching/detail/debugging.hpp>

// #define  BOOST_ALGORITHM_KNUTH_MORRIS_PRATT_DEBUG

namespace boost { namespace algorithm {

// #define  NEW_KMP

/*
    A templated version of the Knuth-Morris-Pratt searching algorithm.
    
    Requirements:
        * Random-access iterators
        * The two iterator types (I1 and I2) must "point to" the same underlying type.

    http://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm
    http://www.inf.fh-flensburg.de/lang/algorithmen/pattern/kmpen.htm
*/

    template <typename patIter>
    class knuth_morris_pratt {
        typedef typename std::iterator_traits<patIter>::difference_type difference_type;
    public:
        knuth_morris_pratt ( patIter first, patIter last ) 
                : pat_first ( first ), pat_last ( last ), 
                  k_pattern_length ( std::distance ( pat_first, pat_last )),
                  skip_ ( k_pattern_length + 1 ) {
#ifdef NEW_KMP
            preKmp ( pat_first, pat_last );
#else
            init_skip_table ( pat_first, pat_last );
#endif
#ifdef BOOST_ALGORITHM_KNUTH_MORRIS_PRATT_DEBUG
            detail::PrintTable ( skip_.begin (), skip_.end ());
#endif
            }
            
        ~knuth_morris_pratt () {}
        
        /// \fn operator ( corpusIter corpus_first, corpusIter corpus_last, Pred p )
        /// \brief Searches the corpus for the pattern that was passed into the constructor
        /// 
        /// \param corpus_first The start of the data to search (Random Access Iterator)
        /// \param corpus_last  One past the end of the data to search
        /// \param p            A predicate used for the search comparisons.
        ///
        template <typename corpusIter>
        std::pair<corpusIter, corpusIter>
        operator () ( corpusIter corpus_first, corpusIter corpus_last ) const {
            BOOST_STATIC_ASSERT (( boost::is_same<
                typename std::iterator_traits<patIter>::value_type, 
                typename std::iterator_traits<corpusIter>::value_type>::value ));

            if ( corpus_first == corpus_last ) return std::make_pair(corpus_last, corpus_last);   // if nothing to search, we didn't find it!
            if (    pat_first ==    pat_last ) return std::make_pair(corpus_first, corpus_first); // empty pattern matches at start

            const difference_type k_corpus_length = std::distance ( corpus_first, corpus_last );
        //  If the pattern is larger than the corpus, we can't find it!
            if ( k_corpus_length < k_pattern_length ) 
                return std::make_pair(corpus_last, corpus_last);

            return do_search ( corpus_first, corpus_last, k_corpus_length );
            }
    
        template <typename Range>
        std::pair<typename boost::range_iterator<Range>::type, typename boost::range_iterator<Range>::type>
        operator () ( Range &r ) const {
            return (*this) (boost::begin(r), boost::end(r));
            }

    private:
/// \cond DOXYGEN_HIDE
        patIter pat_first, pat_last;
        const difference_type k_pattern_length;
        std::vector <difference_type> skip_;

        /// \fn operator ( corpusIter corpus_first, corpusIter corpus_last, Pred p )
        /// \brief Searches the corpus for the pattern that was passed into the constructor
        /// 
        /// \param corpus_first The start of the data to search (Random Access Iterator)
        /// \param corpus_last  One past the end of the data to search
        /// \param p            A predicate used for the search comparisons.
        ///
        template <typename corpusIter>
        std::pair<corpusIter, corpusIter>
        do_search ( corpusIter corpus_first, corpusIter corpus_last, 
                                                difference_type k_corpus_length ) const {
            difference_type match_start = 0;  // position in the corpus that we're matching
            
#ifdef NEW_KMP
            int patternIdx = 0;
            while ( match_start < k_corpus_length ) {
                while ( patternIdx > -1 && pat_first[patternIdx] != corpus_first [match_start] )
                    patternIdx = skip_ [patternIdx]; //<--- Shifting the pattern on mismatch

                patternIdx++;
                match_start++; //<--- corpus is always increased by 1

                if ( patternIdx >= (int) k_pattern_length )
                    return corpus_first + match_start - patternIdx;
                }
            
#else
//  At this point, we know:
//          k_pattern_length <= k_corpus_length
//          for all elements of skip, it holds -1 .. k_pattern_length
//      
//          In the loop, we have the following invariants
//              idx is in the range 0 .. k_pattern_length
//              match_start is in the range 0 .. k_corpus_length - k_pattern_length + 1

            const difference_type last_match = k_corpus_length - k_pattern_length;
            difference_type idx = 0;          // position in the pattern we're comparing

            while ( match_start <= last_match ) {
                while ( pat_first [ idx ] == corpus_first [ match_start + idx ] ) {
                    if ( ++idx == k_pattern_length )
                        return std::make_pair(corpus_first + match_start, corpus_first + match_start + k_pattern_length);
                    }
            //  Figure out where to start searching again
           //   assert ( idx - skip_ [ idx ] > 0 ); // we're always moving forward
                match_start += idx - skip_ [ idx ];
                idx = skip_ [ idx ] >= 0 ? skip_ [ idx ] : 0;
           //   assert ( idx >= 0 && idx < k_pattern_length );
                }
#endif
                
        //  We didn't find anything
            return std::make_pair(corpus_last, corpus_last);
            }
    

        void preKmp ( patIter first, patIter last ) {
           const difference_type count = std::distance ( first, last );
        
           difference_type i, j;
        
           i = 0;
           j = skip_[0] = -1;
           while (i < count) {
              while (j > -1 && first[i] != first[j])
                 j = skip_[j];
              i++;
              j++;
              if (first[i] == first[j])
                 skip_[i] = skip_[j];
              else
                 skip_[i] = j;
           }
        }


        void init_skip_table ( patIter first, patIter last ) {
            const difference_type count = std::distance ( first, last );
    
            difference_type j;
            skip_ [ 0 ] = -1;
            for ( int i = 1; i <= count; ++i ) {
                j = skip_ [ i - 1 ];
                while ( j >= 0 ) {
                    if ( first [ j ] == first [ i - 1 ] )
                        break;
                    j = skip_ [ j ];
                    }
                skip_ [ i ] = j + 1;
                }
            }
// \endcond
        };


/*  Two ranges as inputs gives us four possibilities; with 2,3,3,4 parameters
    Use a bit of TMP to disambiguate the 3-argument templates */

/// \fn knuth_morris_pratt_search ( corpusIter corpus_first, corpusIter corpus_last, 
///       patIter pat_first, patIter pat_last )
/// \brief Searches the corpus for the pattern.
/// 
/// \param corpus_first The start of the data to search (Random Access Iterator)
/// \param corpus_last  One past the end of the data to search
/// \param pat_first    The start of the pattern to search for (Random Access Iterator)
/// \param pat_last     One past the end of the data to search for
///
    template <typename patIter, typename corpusIter>
    std::pair<corpusIter, corpusIter> knuth_morris_pratt_search ( 
                  corpusIter corpus_first, corpusIter corpus_last, 
                  patIter pat_first, patIter pat_last )
    {
        knuth_morris_pratt<patIter> kmp ( pat_first, pat_last );
        return kmp ( corpus_first, corpus_last );
    }

    template <typename PatternRange, typename corpusIter>
    std::pair<corpusIter, corpusIter> knuth_morris_pratt_search ( 
        corpusIter corpus_first, corpusIter corpus_last, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        knuth_morris_pratt<pattern_iterator> kmp ( boost::begin(pattern), boost::end (pattern));
        return kmp ( corpus_first, corpus_last );
    }
    
    template <typename patIter, typename CorpusRange>
    typename boost::disable_if_c<
        boost::is_same<CorpusRange, patIter>::value, 
        std::pair<typename boost::range_iterator<CorpusRange>::type, typename boost::range_iterator<CorpusRange>::type> >
    ::type
    knuth_morris_pratt_search ( CorpusRange &corpus, patIter pat_first, patIter pat_last )
    {
        knuth_morris_pratt<patIter> kmp ( pat_first, pat_last );
        return kmp (boost::begin (corpus), boost::end (corpus));
    }
    
    template <typename PatternRange, typename CorpusRange>
    std::pair<typename boost::range_iterator<CorpusRange>::type, typename boost::range_iterator<CorpusRange>::type>
    knuth_morris_pratt_search ( CorpusRange &corpus, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        knuth_morris_pratt<pattern_iterator> kmp ( boost::begin(pattern), boost::end (pattern));
        return kmp (boost::begin (corpus), boost::end (corpus));
    }


    //  Creator functions -- take a pattern range, return an object
    template <typename Range>
    boost::algorithm::knuth_morris_pratt<typename boost::range_iterator<const Range>::type>
    make_knuth_morris_pratt ( const Range &r ) {
        return boost::algorithm::knuth_morris_pratt
            <typename boost::range_iterator<const Range>::type> (boost::begin(r), boost::end(r));
        }
    
    template <typename Range>
    boost::algorithm::knuth_morris_pratt<typename boost::range_iterator<Range>::type>
    make_knuth_morris_pratt ( Range &r ) {
        return boost::algorithm::knuth_morris_pratt
            <typename boost::range_iterator<Range>::type> (boost::begin(r), boost::end(r));
        }
}}

#endif  // BOOST_ALGORITHM_KNUTH_MORRIS_PRATT_SEARCH_HPP

/* knuth_morris_pratt.hpp
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
*/