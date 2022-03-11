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