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
rSVXOU1Vss7IuE4YmHfQl/nq5mfxd177txYqfbeQwgex4WhH3nrQeVrZt3/Mcl+Pa6Gi44t74rVzcVsE6x0RqnMwJlPZWuSZb3IPNW4/iZORsvX77Z6qwgPG8gNh1h2f2czh12ScXbgBN82MVucRM1ZPUbfrzlLd+dtEOm+8iPNGmPCEs3BTvvnH/FFgUGVHNq7+6CUf3BAa6Tx2wuc8Vka3ht/wlaFDWWtLj6YCJ30KlOPAxgXqcKdoNVozyhbS4xq4TszGOyAp63NMm3CTnJOyXb7nHkd3hnEp212RqA2ueBiOKdscng3Wgl6JrqqclE2oGDqSqfrMSez/01z1WnOwXRnN5ElWThETs2vmdapLWyoHQ/b1aExmj0WIiuIgTqz680L81uskiinIkEaSGRZfJG3iNjy7VSeTNlieTxKlGHoVm0HeJsXQWDHKxFoeqh7/NopYS9tRf6+9lpIr9DYuB22p8Y+aBY8/1VZzxTz+fS3iH31Ue+F4JgyvKDi8tjq8tzEUURAyvO7B4b3aRoM3mvrXr3MI8VYY3sH44PF9dHit0D/oi0OAJ/0f44P4T7cJ8H+Mj/aPf/F57QX9H1X/7/iL9Ke1Fm7w6Oi5EqIbt3Nu/++mFwkflEpXq4S7BjZYVpu4IEaq/v9Ng/hntw6Mh3Glf/yTA6HOV0QQ+PdeGQC/yOzv/x1yPI8VTS5yvvzWY33YhdYj+2Lh11+PKWEXtR47GweJT9Iq0B/cPz6JCCEeBtuvldrJ3GJWY+1SYuJU3dwiFTnYHx1KddoOHGFFZV2tFpt0EEakBpx+XzVjPZ4f7tlVEyGWwYqUQ/3PU7e7Aqleq2xF290j2O5qRRwUaqRQGgzWgG1vMAunUHVR2vO7kSejW3ZGNgH+iOWqY5S+BR0QP0Sht/ByfY/in8ZQhNZnapHJQVFxGy87ngYFU1tWo9MIL4cLQvB4rt2vUKfuELYqOVG7vq31VWhsbil3kireSeZrCo2YMzz4tn7uqDkf12qm8vcl8pZy6fFa+b1CX63EJFrqojhtqfMn13PaWcaeOnZpm1hGX8F/cVuxHl+zlQNI3MbfTtBVxp5wFflF1VHGC+026uMWcrgOHu5iOdy54sofajXbErjquPpYC3/wuHpKE6hsrGMz8bt9vPLwbm5lZlu7r2h+nZ9qqREydZtq0DfWSacXxj64CBmBjvIyO1IYk9iaerciGBEXq4g4QiJinxaEiAo/EHL/aYmIf4xk+Wue040pTitjVSwRlo29apL5JZOdTFlWHJ4tH/L6SvOXjFpXrD1Pdcmp+VzCuwnw+KIsmvXFu9UxRopHoKIBkRg7atop+z+gUa/wdZ/5Mzgr3w3hN7B3kp8p7r/TEjcA/3MZ/xtp+G8l/LcS/tf6439ziRCljBCLdPw/xfg/XnOfsKnuE7CSqu8+gakKzX0i6oxHm9fWwdwn4DkRIvGcm//HXiT/9+4vbmuYuO0HzwUZsz//b/ij2ht49iLbm3Kx7WF/k3o67xZ37+lQGlXjX8T8+PZuPRNKe+c7H86MCdRP3818bb1oZ9D100lA5+7xEp2r6UqYPAM0hL4B21VgxIGmrepFHJhyQGfxL7T86byhzj/eJdGB473/iBxvN48f+WY3leN9mcl3oTZa5/Fgo+3Qst5o5zbUfb/eaHF5R5s5Qp4V/xalnxhSISYRVyC7xmiSkZxsqU6t7OMjHtuL80GSz4zsbCTK6/iMaGZDoUlk2oRUiFlfRAEEOetwBdFjWiSYlE23wN/ErjtnwMbA0WfW6JsgWYDGNZGT9hEhiVu+QReLqRPx36EcwQT8msZ0fvyYxnC4DR8rudkPOfkTSt7FyRXUrR8tvpA=
*/