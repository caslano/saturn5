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
#include <boost/detail/iterator.hpp>

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

                    typedef BOOST_STRING_TYPENAME boost::detail::
                        iterator_traits<ForwardIteratorT>::iterator_category category;

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
                for(
                    unsigned int Index=0;
                    Index<N && It!=End; ++Index,++It ) {};

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
                typedef BOOST_STRING_TYPENAME boost::detail::
                    iterator_traits<ForwardIteratorT>::iterator_category category;

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
                for( Index=0; Index<N && It2!=End; ++Index,++It2 ) {};

                // Advance It, It2 to the end
                for(; It2!=End; ++It,++It2 ) {};

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
                for(
                    unsigned int Index=0;
                    Index<N && It!=Begin; ++Index,--It ) {};

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
                typedef BOOST_STRING_TYPENAME boost::detail::
                    iterator_traits<ForwardIteratorT>::iterator_category category;

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