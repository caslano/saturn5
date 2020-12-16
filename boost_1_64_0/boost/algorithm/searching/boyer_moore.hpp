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
D7LkvoYmmCil0jKwEhIDZPSNj0Qaql+iVb99ABMJHTmApM/fECuLg0zWy/oknULmU31CXNcoVVp6ujwYnKP1Gkd9Cphyg5cCqtoQBVR6mxB90KWaVty4lqrsojdmPDsgXO5f0lF32H5eCpfNGNwzAHdWzAM4OIs2Js4HHctrNGD3TLPYEs3Rt50qQN6QOMwUODIIkCVCeiyApp6lwqE2pt5Y0amLfrailyJf472vuZNUB+gUEU8iEe/3J2rxXA5qODQ5KjNHaiUgk1GB506rBZLteVoJpFtLGjjcTcNFq7NqdhTVtxob1CTq4/y7HOd1vbRxnhbLeV9BuCwjfe7SJkp0jqjzQLLSdButI+QRTM6EXVHRSFHRSgE68Sdqq6qPY32lThM/f27RIC7+D/KNpj7ITZWXyIfpHYySa9hHbgPfksjX5izLnsfX3tGWZb/Bp82dHQ1WNrlnLNj9zYv4rZNr9NAPn/JzemuxJE+hgDsnShiv1EJLWFkGKKyg6ldhwTiEfTgg2E17CjKud+2lZ2OQH9a7s+t9lDmTjjIUIIIL7l8YD6ElyiD37R6xVIsz9iGDpKH3eUufGwUGixLvpVP/fo88FvJfk/v9KqQi3xPvpgxTbUHf6PxUvfPHJDId6EHI9DsgU4TIgm6ctxmfIei9KKBeuIcYPfGjuQ8+oE5LUI9JUEx/J1oGgsLjstF29WxJZx3udN0C7pv6m3KUs574L2QqMNuyqk1m8XVi2Mlafk4XbxD15GLFbUCMnvi/qgVLSPcCaSeN+tMojPvTgPozZoZ7KA65A+eIKS2l3IYOcM/0fhH9tOrD2sEullWN7J5KBldwsnN+a32MTSTMv3bXxtis5k+kZino29nlLdVMlnpQL9W85n4C/05vPpo53KPNkiBbNiWpNtPy6DplXfU0SGI6iG/kZDp0EB7xcovAydRjnVh/nirJi/rz9a98tbO6X54sPBWNZ5rcrVddjxDrVxeeasO/SulXfOGppvj+Dr4jCPA6+rBk79FFj/eQIMYZfKUTLMIgJOhFjD3MBv8nu1IMoT5vcl795NGUQP3c9xapn3s+0U8/NyVNamMeCiNtzO2afu6d5qyf6+V/3/8Yjs2sj5SX/nxsUG/+Y9I1VduVKPQT6CQzR8nDIanW7EDWUsI+EZGiSTb/WKyp1lj/pxQZ+CrjAJ8ZyfRqmrMEPSfV2VgxtjdfirGC0YbpS81WjthJM4YZGdFNzsgLPCN3aPqpPzbj3fxFoxSFwN+kKGRURSFqDZ9PUK++ulLesJPuTOzlHydYcyk244eTX8aR1yvgF5ZlEfjCTPMHPl+e5UuLOxbj5rKAbg2eN5E6T4tKAzGyaMO8uOUFCyMKEpeYPRvseEIUwfHKSb60RRSoAqYd8i3AWgq/iCBot8cWAOFSsdik2LCWxvDhIe5ufglrEK5coJBR0icoAfcuyfJMg8qmNH6NGrnurAhqgVRZJrx9svEugoKXxfXeaz0XYWrPHx6g3rtCQYgyFJtn9R1SAPsylZjM02IQdDt6WBO7uK2XeqoWE/CNtCujKAWfrydIHspzLuUI/pRr4kT6E/zbrT0J9XIPFiMIX+TZeIJ8f8udFWXP20bHg84ArQf0Wosu0oqrUT6GmN1Zp+x5ezAmBe9/iaT7IwF8gHk1TS8RhnLcVtzZJES6D4zNGoxmDGOgmWZEzg3mJbM4Vbxv1Bb176xwUNfVEmxZ6Z+9vLZ2rA6v6mkTr2rrgoJFBdH589y9u/JkuQfSkMR49IUR6hHA1nfPQV3l6nviE1y8e95pz9tCHePgCfTcownPsNvuk+PjjLytstPK9xijkZY03qgt6WAeGmRX1owxFdEyfdY=
*/