/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#ifndef BOOST_ALGORITHM_BOYER_MOORE_HORSPOOOL_SEARCH_HPP
#define BOOST_ALGORITHM_BOYER_MOORE_HORSPOOOL_SEARCH_HPP

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

// #define  BOOST_ALGORITHM_BOYER_MOORE_HORSPOOL_DEBUG_HPP

namespace boost { namespace algorithm {

/*
    A templated version of the boyer-moore-horspool searching algorithm.
    
    Requirements:
        * Random access iterators
        * The two iterator types (patIter and corpusIter) must 
            "point to" the same underlying type.
        * Additional requirements may be imposed buy the skip table, such as:
        ** Numeric type (array-based skip table)
        ** Hashable type (map-based skip table)

http://www-igm.univ-mlv.fr/%7Elecroq/string/node18.html

*/

    template <typename patIter, typename traits = detail::BM_traits<patIter> >
    class boyer_moore_horspool {
        typedef typename std::iterator_traits<patIter>::difference_type difference_type;
    public:
        boyer_moore_horspool ( patIter first, patIter last ) 
                : pat_first ( first ), pat_last ( last ),
                  k_pattern_length ( std::distance ( pat_first, pat_last )),
                  skip_ ( k_pattern_length, k_pattern_length ) {
                  
        //  Build the skip table
            std::size_t i = 0;
            if ( first != last )    // empty pattern?
                for ( patIter iter = first; iter != last-1; ++iter, ++i )
                    skip_.insert ( *iter, k_pattern_length - 1 - i );
#ifdef BOOST_ALGORITHM_BOYER_MOORE_HORSPOOL_DEBUG_HPP
            skip_.PrintSkipTable ();
#endif
            }
            
        ~boyer_moore_horspool () {}
        
        /// \fn operator ( corpusIter corpus_first, corpusIter corpus_last)
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

        /// \fn do_search ( corpusIter corpus_first, corpusIter corpus_last )
        /// \brief Searches the corpus for the pattern that was passed into the constructor
        /// 
        /// \param corpus_first The start of the data to search (Random Access Iterator)
        /// \param corpus_last  One past the end of the data to search
        /// \param k_corpus_length The length of the corpus to search
        ///
        template <typename corpusIter>
        std::pair<corpusIter, corpusIter>
        do_search ( corpusIter corpus_first, corpusIter corpus_last ) const {
            corpusIter curPos = corpus_first;
            const corpusIter lastPos = corpus_last - k_pattern_length;
            while ( curPos <= lastPos ) {
            //  Do we match right where we are?
                std::size_t j = k_pattern_length - 1;
                while ( pat_first [j] == curPos [j] ) {
                //  We matched - we're done!
                    if ( j == 0 )
                        return std::make_pair(curPos, curPos + k_pattern_length);
                    j--;
                    }
        
                curPos += skip_ [ curPos [ k_pattern_length - 1 ]];
                }
            
            return std::make_pair(corpus_last, corpus_last);
            }
// \endcond
        };

/*  Two ranges as inputs gives us four possibilities; with 2,3,3,4 parameters
    Use a bit of TMP to disambiguate the 3-argument templates */

/// \fn boyer_moore_horspool_search ( corpusIter corpus_first, corpusIter corpus_last, 
///       patIter pat_first, patIter pat_last )
/// \brief Searches the corpus for the pattern.
/// 
/// \param corpus_first The start of the data to search (Random Access Iterator)
/// \param corpus_last  One past the end of the data to search
/// \param pat_first    The start of the pattern to search for (Random Access Iterator)
/// \param pat_last     One past the end of the data to search for
///
    template <typename patIter, typename corpusIter>
    std::pair<corpusIter, corpusIter> boyer_moore_horspool_search ( 
                  corpusIter corpus_first, corpusIter corpus_last, 
                  patIter pat_first, patIter pat_last )
    {
        boyer_moore_horspool<patIter> bmh ( pat_first, pat_last );
        return bmh ( corpus_first, corpus_last );
    }

    template <typename PatternRange, typename corpusIter>
    std::pair<corpusIter, corpusIter> boyer_moore_horspool_search ( 
        corpusIter corpus_first, corpusIter corpus_last, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        boyer_moore_horspool<pattern_iterator> bmh ( boost::begin(pattern), boost::end (pattern));
        return bmh ( corpus_first, corpus_last );
    }
    
    template <typename patIter, typename CorpusRange>
    typename boost::disable_if_c<
        boost::is_same<CorpusRange, patIter>::value, 
        std::pair<typename boost::range_iterator<CorpusRange>::type, typename boost::range_iterator<CorpusRange>::type> >
    ::type
    boyer_moore_horspool_search ( CorpusRange &corpus, patIter pat_first, patIter pat_last )
    {
        boyer_moore_horspool<patIter> bmh ( pat_first, pat_last );
        return bm (boost::begin (corpus), boost::end (corpus));
    }
    
    template <typename PatternRange, typename CorpusRange>
    std::pair<typename boost::range_iterator<CorpusRange>::type, typename boost::range_iterator<CorpusRange>::type>
    boyer_moore_horspool_search ( CorpusRange &corpus, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        boyer_moore_horspool<pattern_iterator> bmh ( boost::begin(pattern), boost::end (pattern));
        return bmh (boost::begin (corpus), boost::end (corpus));
    }


    //  Creator functions -- take a pattern range, return an object
    template <typename Range>
    boost::algorithm::boyer_moore_horspool<typename boost::range_iterator<const Range>::type>
    make_boyer_moore_horspool ( const Range &r ) {
        return boost::algorithm::boyer_moore_horspool
            <typename boost::range_iterator<const Range>::type> (boost::begin(r), boost::end(r));
        }
    
    template <typename Range>
    boost::algorithm::boyer_moore_horspool<typename boost::range_iterator<Range>::type>
    make_boyer_moore_horspool ( Range &r ) {
        return boost::algorithm::boyer_moore_horspool
            <typename boost::range_iterator<Range>::type> (boost::begin(r), boost::end(r));
        }

}}

#endif  //  BOOST_ALGORITHM_BOYER_MOORE_HORSPOOOL_SEARCH_HPP

/* boyer_moore_horspool.hpp
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
*/