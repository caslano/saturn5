/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#ifndef BOOST_ALGORITHM_BOYER_MOORE_SEARCH_HPP
#define BOOST_ALGORITHM_BOYER_MOORE_SEARCH_HPP

#include <iterator>     // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/algorithm/searching/detail/bm_traits.hpp>
#include <boost/algorithm/searching/detail/debugging.hpp>

namespace boost { namespace algorithm {

/*
    A templated version of the boyer-moore searching algorithm.
    
References:
    http://www.cs.utexas.edu/users/moore/best-ideas/string-searching/
    http://www.cs.utexas.edu/~moore/publications/fstrpos.pdf
    
Explanations:
    http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm
    http://www.movsd.com/bm.htm
    http://www.cs.ucdavis.edu/~gusfield/cs224f09/bnotes.pdf

The Boyer-Moore search algorithm uses two tables, a "bad character" table
to tell how far to skip ahead when it hits a character that is not in the pattern,
and a "good character" table to tell how far to skip ahead when it hits a
mismatch on a character that _is_ in the pattern.

Requirements:
        * Random access iterators
        * The two iterator types (patIter and corpusIter) must 
            "point to" the same underlying type and be comparable.
        * Additional requirements may be imposed but the skip table, such as:
        ** Numeric type (array-based skip table)
        ** Hashable type (map-based skip table)
*/

    template <typename patIter, typename traits = detail::BM_traits<patIter> >
    class boyer_moore {
        typedef typename std::iterator_traits<patIter>::difference_type difference_type;
    public:
        boyer_moore ( patIter first, patIter last ) 
                : pat_first ( first ), pat_last ( last ),
                  k_pattern_length ( std::distance ( pat_first, pat_last )),
                  skip_ ( k_pattern_length, -1 ),
                  suffix_ ( k_pattern_length + 1 )
            {
            this->build_skip_table   ( first, last );
            this->build_suffix_table ( first, last );
            }
            
        ~boyer_moore () {}
        
        /// \fn operator ( corpusIter corpus_first, corpusIter corpus_last )
        /// \brief Searches the corpus for the pattern that was passed into the constructor
        /// 
        /// \param corpus_first The start of the data to search (Random Access Iterator)
        /// \param corpus_last  One past the end of the data to search
        ///
        template <typename corpusIter>
        std::pair<corpusIter, corpusIter>
        operator () ( corpusIter corpus_first, corpusIter corpus_last ) const {
            BOOST_STATIC_ASSERT (( boost::is_same<
                                    typename std::iterator_traits<patIter>::value_type, 
                                    typename std::iterator_traits<corpusIter>::value_type>::value ));

            if ( corpus_first == corpus_last ) return std::make_pair(corpus_last, corpus_last);   // if nothing to search, we didn't find it!
            if (    pat_first ==    pat_last ) return std::make_pair(corpus_first, corpus_first); // empty pattern matches at start

            const difference_type k_corpus_length  = std::distance ( corpus_first, corpus_last );
        //  If the pattern is larger than the corpus, we can't find it!
            if ( k_corpus_length < k_pattern_length ) 
                return std::make_pair(corpus_last, corpus_last);

        //  Do the search 
            return this->do_search ( corpus_first, corpus_last );
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
        typename traits::skip_table_t skip_;
        std::vector <difference_type> suffix_;

        /// \fn operator ( corpusIter corpus_first, corpusIter corpus_last, Pred p )
        /// \brief Searches the corpus for the pattern that was passed into the constructor
        /// 
        /// \param corpus_first The start of the data to search (Random Access Iterator)
        /// \param corpus_last  One past the end of the data to search
        /// \param p            A predicate used for the search comparisons.
        ///
        template <typename corpusIter>
        std::pair<corpusIter, corpusIter>
        do_search ( corpusIter corpus_first, corpusIter corpus_last ) const {
        /*  ---- Do the matching ---- */
            corpusIter curPos = corpus_first;
            const corpusIter lastPos = corpus_last - k_pattern_length;
            difference_type j, k, m;

            while ( curPos <= lastPos ) {
        /*  while ( std::distance ( curPos, corpus_last ) >= k_pattern_length ) { */
            //  Do we match right where we are?
                j = k_pattern_length;
                while ( pat_first [j-1] == curPos [j-1] ) {
                    j--;
                //  We matched - we're done!
                    if ( j == 0 )
                        return std::make_pair(curPos, curPos + k_pattern_length);
                    }
                
            //  Since we didn't match, figure out how far to skip forward
                k = skip_ [ curPos [ j - 1 ]];
                m = j - k - 1;
                if ( k < j && m > suffix_ [ j ] )
                    curPos += m;
                else
                    curPos += suffix_ [ j ];
                }
        
            return std::make_pair(corpus_last, corpus_last);     // We didn't find anything
            }


        void build_skip_table ( patIter first, patIter last ) {
            for ( std::size_t i = 0; first != last; ++first, ++i )
                skip_.insert ( *first, i );
            }
        

        template<typename Iter, typename Container>
        void compute_bm_prefix ( Iter first, Iter last, Container &prefix ) {
            const std::size_t count = std::distance ( first, last );
            BOOST_ASSERT ( count > 0 );
            BOOST_ASSERT ( prefix.size () == count );
                            
            prefix[0] = 0;
            std::size_t k = 0;
            for ( std::size_t i = 1; i < count; ++i ) {
                BOOST_ASSERT ( k < count );
                while ( k > 0 && ( first[k] != first[i] )) {
                    BOOST_ASSERT ( k < count );
                    k = prefix [ k - 1 ];
                    }
                    
                if ( first[k] == first[i] )
                    k++;
                prefix [ i ] = k;
                }
            }

        void build_suffix_table ( patIter first, patIter last ) {
            const std::size_t count = (std::size_t) std::distance ( first, last );
            
            if ( count > 0 ) {  // empty pattern
                std::vector<typename std::iterator_traits<patIter>::value_type> reversed(count);
                (void) std::reverse_copy ( first, last, reversed.begin ());
                
                std::vector<difference_type> prefix (count);
                compute_bm_prefix ( first, last, prefix );
        
                std::vector<difference_type> prefix_reversed (count);
                compute_bm_prefix ( reversed.begin (), reversed.end (), prefix_reversed );
                
                for ( std::size_t i = 0; i <= count; i++ )
                    suffix_[i] = count - prefix [count-1];
         
                for ( std::size_t i = 0; i < count; i++ ) {
                    const std::size_t     j = count - prefix_reversed[i];
                    const difference_type k = i -     prefix_reversed[i] + 1;
         
                    if (suffix_[j] > k)
                        suffix_[j] = k;
                    }
                }
            }
/// \endcond
        };


/*  Two ranges as inputs gives us four possibilities; with 2,3,3,4 parameters
    Use a bit of TMP to disambiguate the 3-argument templates */

/// \fn boyer_moore_search ( corpusIter corpus_first, corpusIter corpus_last, 
///       patIter pat_first, patIter pat_last )
/// \brief Searches the corpus for the pattern.
/// 
/// \param corpus_first The start of the data to search (Random Access Iterator)
/// \param corpus_last  One past the end of the data to search
/// \param pat_first    The start of the pattern to search for (Random Access Iterator)
/// \param pat_last     One past the end of the data to search for
///
    template <typename patIter, typename corpusIter>
    std::pair<corpusIter, corpusIter> boyer_moore_search ( 
                  corpusIter corpus_first, corpusIter corpus_last, 
                  patIter pat_first, patIter pat_last )
    {
        boyer_moore<patIter> bm ( pat_first, pat_last );
        return bm ( corpus_first, corpus_last );
    }

    template <typename PatternRange, typename corpusIter>
    std::pair<corpusIter, corpusIter> boyer_moore_search ( 
        corpusIter corpus_first, corpusIter corpus_last, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        boyer_moore<pattern_iterator> bm ( boost::begin(pattern), boost::end (pattern));
        return bm ( corpus_first, corpus_last );
    }
    
    template <typename patIter, typename CorpusRange>
    typename boost::disable_if_c<
        boost::is_same<CorpusRange, patIter>::value, 
        std::pair<typename boost::range_iterator<CorpusRange>::type, typename boost::range_iterator<CorpusRange>::type> >
    ::type
    boyer_moore_search ( CorpusRange &corpus, patIter pat_first, patIter pat_last )
    {
        boyer_moore<patIter> bm ( pat_first, pat_last );
        return bm (boost::begin (corpus), boost::end (corpus));
    }
    
    template <typename PatternRange, typename CorpusRange>
    std::pair<typename boost::range_iterator<CorpusRange>::type, typename boost::range_iterator<CorpusRange>::type>
    boyer_moore_search ( CorpusRange &corpus, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        boyer_moore<pattern_iterator> bm ( boost::begin(pattern), boost::end (pattern));
        return bm (boost::begin (corpus), boost::end (corpus));
    }


    //  Creator functions -- take a pattern range, return an object
    template <typename Range>
    boost::algorithm::boyer_moore<typename boost::range_iterator<const Range>::type>
    make_boyer_moore ( const Range &r ) {
        return boost::algorithm::boyer_moore
            <typename boost::range_iterator<const Range>::type> (boost::begin(r), boost::end(r));
        }
    
    template <typename Range>
    boost::algorithm::boyer_moore<typename boost::range_iterator<Range>::type>
    make_boyer_moore ( Range &r ) {
        return boost::algorithm::boyer_moore
            <typename boost::range_iterator<Range>::type> (boost::begin(r), boost::end(r));
        }

}}

#endif  //  BOOST_ALGORITHM_BOYER_MOORE_SEARCH_HPP

/* boyer_moore.hpp
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
*/