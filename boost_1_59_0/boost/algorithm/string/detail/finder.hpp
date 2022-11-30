//  Boost string_algo library finder.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FINDER_DETAIL_HPP
#define BOOST_STRING_FINDER_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <iterator>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/as_literal.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {


//  find first functor -----------------------------------------------//

            // find a subsequence in the sequence ( functor )
            /*
                Returns a pair <begin,end> marking the subsequence in the sequence.
                If the find fails, functor returns <End,End>
            */
            template<typename SearchIteratorT,typename PredicateT>
            struct first_finderF
            {
                typedef SearchIteratorT search_iterator_type;

                // Construction
                template< typename SearchT >
                first_finderF( const SearchT& Search, PredicateT Comp ) :
                    m_Search(::boost::begin(Search), ::boost::end(Search)), m_Comp(Comp) {}
                first_finderF(
                        search_iterator_type SearchBegin,
                        search_iterator_type SearchEnd,
                        PredicateT Comp ) :
                    m_Search(SearchBegin, SearchEnd), m_Comp(Comp) {}

                // Operation
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                operator()(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) const
                {
                    typedef iterator_range<ForwardIteratorT> result_type;
                    typedef ForwardIteratorT input_iterator_type;

                    // Outer loop
                    for(input_iterator_type OuterIt=Begin;
                        OuterIt!=End;
                        ++OuterIt)
                    {
                        // Sanity check
                        if( boost::empty(m_Search) )
                            return result_type( End, End );

                        input_iterator_type InnerIt=OuterIt;
                        search_iterator_type SubstrIt=m_Search.begin();
                        for(;
                            InnerIt!=End && SubstrIt!=m_Search.end();
                            ++InnerIt,++SubstrIt)
                        {
                            if( !( m_Comp(*InnerIt,*SubstrIt) ) )
                                break;
                        }

                        // Substring matching succeeded
                        if ( SubstrIt==m_Search.end() )
                            return result_type( OuterIt, InnerIt );
                    }

                    return result_type( End, End );
                }

            private:
                iterator_range<search_iterator_type> m_Search;
                PredicateT m_Comp;
            };

//  find last functor -----------------------------------------------//

            // find the last match a subsequence in the sequence ( functor )
            /*
                Returns a pair <begin,end> marking the subsequence in the sequence.
                If the find fails, returns <End,End>
            */
            template<typename SearchIteratorT, typename PredicateT>
            struct last_finderF
            {
                typedef SearchIteratorT search_iterator_type;
                typedef first_finderF<
                    search_iterator_type,
                    PredicateT> first_finder_type;

                // Construction
                template< typename SearchT >
                last_finderF( const SearchT& Search, PredicateT Comp ) :
                    m_Search(::boost::begin(Search), ::boost::end(Search)), m_Comp(Comp) {}
                last_finderF(
                        search_iterator_type SearchBegin,
                        search_iterator_type SearchEnd,
                        PredicateT Comp ) :
                    m_Search(SearchBegin, SearchEnd), m_Comp(Comp) {}

                // Operation
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                operator()(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) const
                {
                    typedef iterator_range<ForwardIteratorT> result_type;

                    if( boost::empty(m_Search) )
                        return result_type( End, End );

                    typedef BOOST_STRING_TYPENAME
                        std::iterator_traits<ForwardIteratorT>::iterator_category category;

                    return findit( Begin, End, category() );
                }

            private:
                // forward iterator
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                findit(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End,
                    std::forward_iterator_tag ) const
                {
                    typedef iterator_range<ForwardIteratorT> result_type;

                    first_finder_type first_finder(
                        m_Search.begin(), m_Search.end(), m_Comp );

                    result_type M=first_finder( Begin, End );
                    result_type Last=M;

                    while( M )
                    {
                        Last=M;
                        M=first_finder( ::boost::end(M), End );
                    }

                    return Last;
                }

                // bidirectional iterator
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                findit(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End,
                    std::bidirectional_iterator_tag ) const
                {
                    typedef iterator_range<ForwardIteratorT> result_type;
                    typedef ForwardIteratorT input_iterator_type;

                    // Outer loop
                    for(input_iterator_type OuterIt=End;
                        OuterIt!=Begin; )
                    {
                        input_iterator_type OuterIt2=--OuterIt;

                        input_iterator_type InnerIt=OuterIt2;
                        search_iterator_type SubstrIt=m_Search.begin();
                        for(;
                            InnerIt!=End && SubstrIt!=m_Search.end();
                            ++InnerIt,++SubstrIt)
                        {
                            if( !( m_Comp(*InnerIt,*SubstrIt) ) )
                                break;
                        }

                        // Substring matching succeeded
                        if( SubstrIt==m_Search.end() )
                            return result_type( OuterIt2, InnerIt );
                    }

                    return result_type( End, End );
                }

            private:
                iterator_range<search_iterator_type> m_Search;
                PredicateT m_Comp;
            };

//  find n-th functor -----------------------------------------------//

            // find the n-th match of a subsequence in the sequence ( functor )
            /*
                Returns a pair <begin,end> marking the subsequence in the sequence.
                If the find fails, returns <End,End>
            */
            template<typename SearchIteratorT, typename PredicateT>
            struct nth_finderF
            {
                typedef SearchIteratorT search_iterator_type;
                typedef first_finderF<
                    search_iterator_type,
                    PredicateT> first_finder_type;
                typedef last_finderF<
                    search_iterator_type,
                    PredicateT> last_finder_type;

                // Construction
                template< typename SearchT >
                nth_finderF(
                        const SearchT& Search,
                        int Nth,
                        PredicateT Comp) :
                    m_Search(::boost::begin(Search), ::boost::end(Search)),
                    m_Nth(Nth),
                    m_Comp(Comp) {}
                nth_finderF(
                        search_iterator_type SearchBegin,
                        search_iterator_type SearchEnd,
                        int Nth,
                        PredicateT Comp) :
                    m_Search(SearchBegin, SearchEnd),
                    m_Nth(Nth),
                    m_Comp(Comp) {}

                // Operation
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                operator()(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) const
                {
                    if(m_Nth>=0)
                    {
                        return find_forward(Begin, End, m_Nth);
                    }
                    else
                    {
                        return find_backward(Begin, End, -m_Nth);
                    }

                }

            private:
                // Implementation helpers
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                find_forward(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End,
                    unsigned int N) const
                {
                    typedef iterator_range<ForwardIteratorT> result_type;

                    // Sanity check
                    if( boost::empty(m_Search) )
                        return result_type( End, End );

                    // Instantiate find functor
                    first_finder_type first_finder(
                        m_Search.begin(), m_Search.end(), m_Comp );

                    result_type M( Begin, Begin );

                    for( unsigned int n=0; n<=N; ++n )
                    {
                        // find next match
                        M=first_finder( ::boost::end(M), End );

                        if ( !M )
                        {
                            // Subsequence not found, return
                            return M;
                        }
                    }

                    return M;
                }

                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                find_backward(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End,
                    unsigned int N) const
                {
                    typedef iterator_range<ForwardIteratorT> result_type;

                    // Sanity check
                    if( boost::empty(m_Search) )
                        return result_type( End, End );

                    // Instantiate find functor
                    last_finder_type last_finder(
                        m_Search.begin(), m_Search.end(), m_Comp );

                    result_type M( End, End );

                    for( unsigned int n=1; n<=N; ++n )
                    {
                        // find next match
                        M=last_finder( Begin, ::boost::begin(M) );

                        if ( !M )
                        {
                            // Subsequence not found, return
                            return M;
                        }
                    }

                    return M;
                }


            private:
                iterator_range<search_iterator_type> m_Search;
                int m_Nth;
                PredicateT m_Comp;
            };

//  find head/tail implementation helpers ---------------------------//

            template<typename ForwardIteratorT>
                iterator_range<ForwardIteratorT>
            find_head_impl(
                ForwardIteratorT Begin,
                ForwardIteratorT End,
                unsigned int N,
                std::forward_iterator_tag )
            {
                typedef ForwardIteratorT input_iterator_type;
                typedef iterator_range<ForwardIteratorT> result_type;

                input_iterator_type It=Begin;
                for( unsigned int Index=0; Index<N && It!=End; ++Index,++It )
                    ;

                return result_type( Begin, It );
            }

            template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
            find_head_impl(
                ForwardIteratorT Begin,
                ForwardIteratorT End,
                unsigned int N,
                std::random_access_iterator_tag )
            {
                typedef iterator_range<ForwardIteratorT> result_type;

                if ( (End<=Begin) || ( static_cast<unsigned int>(End-Begin) < N ) )
                    return result_type( Begin, End );

                return result_type(Begin,Begin+N);
            }

            // Find head implementation
            template<typename ForwardIteratorT>
                iterator_range<ForwardIteratorT>
            find_head_impl(
                ForwardIteratorT Begin,
                ForwardIteratorT End,
                unsigned int N )
            {
                typedef BOOST_STRING_TYPENAME
                    std::iterator_traits<ForwardIteratorT>::iterator_category category;

                return ::boost::algorithm::detail::find_head_impl( Begin, End, N, category() );
            }

            template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
            find_tail_impl(
                ForwardIteratorT Begin,
                ForwardIteratorT End,
                unsigned int N,
                std::forward_iterator_tag )
            {
                typedef ForwardIteratorT input_iterator_type;
                typedef iterator_range<ForwardIteratorT> result_type;

                unsigned int Index=0;
                input_iterator_type It=Begin;
                input_iterator_type It2=Begin;

                // Advance It2 by N increments
                for( Index=0; Index<N && It2!=End; ++Index,++It2 )
                    ;

                // Advance It, It2 to the end
                for(; It2!=End; ++It,++It2 )
                	;

                return result_type( It, It2 );
            }

            template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
            find_tail_impl(
                ForwardIteratorT Begin,
                ForwardIteratorT End,
                unsigned int N,
                std::bidirectional_iterator_tag )
            {
                typedef ForwardIteratorT input_iterator_type;
                typedef iterator_range<ForwardIteratorT> result_type;

                input_iterator_type It=End;
                for( unsigned int Index=0; Index<N && It!=Begin; ++Index,--It )
                    ;

                return result_type( It, End );
            }

            template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
            find_tail_impl(
                ForwardIteratorT Begin,
                ForwardIteratorT End,
                unsigned int N,
                std::random_access_iterator_tag )
            {
                typedef iterator_range<ForwardIteratorT> result_type;

                if ( (End<=Begin) || ( static_cast<unsigned int>(End-Begin) < N ) )
                    return result_type( Begin, End );

                return result_type( End-N, End );
            }

                        // Operation
            template< typename ForwardIteratorT >
            iterator_range<ForwardIteratorT>
            find_tail_impl(
                ForwardIteratorT Begin,
                ForwardIteratorT End,
                unsigned int N )
            {
                typedef BOOST_STRING_TYPENAME
                    std::iterator_traits<ForwardIteratorT>::iterator_category category;

                return ::boost::algorithm::detail::find_tail_impl( Begin, End, N, category() );
            }



//  find head functor -----------------------------------------------//


            // find a head in the sequence ( functor )
            /*
                This functor find a head of the specified range. For
                a specified N, the head is a subsequence of N starting
                elements of the range.
            */
            struct head_finderF
            {
                // Construction
                head_finderF( int N ) : m_N(N) {}

                // Operation
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                operator()(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) const
                {
                    if(m_N>=0)
                    {
                        return ::boost::algorithm::detail::find_head_impl( Begin, End, m_N );
                    }
                    else
                    {
                        iterator_range<ForwardIteratorT> Res=
                            ::boost::algorithm::detail::find_tail_impl( Begin, End, -m_N );

                        return ::boost::make_iterator_range(Begin, Res.begin());
                    }
                }

            private:
                int m_N;
            };

//  find tail functor -----------------------------------------------//


            // find a tail in the sequence ( functor )
            /*
                This functor find a tail of the specified range. For
                a specified N, the head is a subsequence of N starting
                elements of the range.
            */
            struct tail_finderF
            {
                // Construction
                tail_finderF( int N ) : m_N(N) {}

                // Operation
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                operator()(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) const
                {
                    if(m_N>=0)
                    {
                        return ::boost::algorithm::detail::find_tail_impl( Begin, End, m_N );
                    }
                    else
                    {
                        iterator_range<ForwardIteratorT> Res=
                            ::boost::algorithm::detail::find_head_impl( Begin, End, -m_N );

                        return ::boost::make_iterator_range(Res.end(), End);
                    }
                }

            private:
                int m_N;
            };

//  find token functor -----------------------------------------------//

            // find a token in a sequence ( functor )
            /*
                This find functor finds a token specified be a predicate
                in a sequence. It is equivalent of std::find algorithm,
                with an exception that it return range instead of a single
                iterator.

                If bCompress is set to true, adjacent matching tokens are
                concatenated into one match.
            */
            template< typename PredicateT >
            struct token_finderF
            {
                // Construction
                token_finderF(
                    PredicateT Pred,
                    token_compress_mode_type eCompress=token_compress_off ) :
                        m_Pred(Pred), m_eCompress(eCompress) {}

                // Operation
                template< typename ForwardIteratorT >
                iterator_range<ForwardIteratorT>
                operator()(
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) const
                {
                    typedef iterator_range<ForwardIteratorT> result_type;

                    ForwardIteratorT It=std::find_if( Begin, End, m_Pred );

                    if( It==End )
                    {
                        return result_type( End, End );
                    }
                    else
                    {
                        ForwardIteratorT It2=It;

                        if( m_eCompress==token_compress_on )
                        {
                            // Find first non-matching character
                            while( It2!=End && m_Pred(*It2) ) ++It2;
                        }
                        else
                        {
                            // Advance by one position
                            ++It2;
                        }

                        return result_type( It, It2 );
                    }
                }

            private:
                PredicateT m_Pred;
                token_compress_mode_type m_eCompress;
            };

//  find range functor -----------------------------------------------//

            // find a range in the sequence ( functor )
            /*
                This functor actually does not perform any find operation.
                It always returns given iterator range as a result.
            */
            template<typename ForwardIterator1T>
            struct range_finderF
            {
                typedef ForwardIterator1T input_iterator_type;
                typedef iterator_range<input_iterator_type> result_type;

                // Construction
                range_finderF(
                    input_iterator_type Begin,
                    input_iterator_type End ) : m_Range(Begin, End) {}

                range_finderF(const iterator_range<input_iterator_type>& Range) :
                    m_Range(Range) {}

                // Operation
                template< typename ForwardIterator2T >
                iterator_range<ForwardIterator2T>
                operator()(
                    ForwardIterator2T,
                    ForwardIterator2T ) const
                {
#if BOOST_WORKAROUND( __MWERKS__, <= 0x3003 ) 
                    return iterator_range<const ForwardIterator2T>(this->m_Range);
#else
                    return m_Range;
#endif
                }

            private:
                iterator_range<input_iterator_type> m_Range;
            };


        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FINDER_DETAIL_HPP

/* finder.hpp
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
*/