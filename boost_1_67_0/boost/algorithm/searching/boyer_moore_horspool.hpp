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