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