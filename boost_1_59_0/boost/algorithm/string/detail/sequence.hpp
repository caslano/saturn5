//  Boost string_algo library sequence.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_DETAIL_SEQUENCE_HPP
#define BOOST_STRING_DETAIL_SEQUENCE_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  insert helpers  -------------------------------------------------//
        
            template< typename InputT, typename ForwardIteratorT >
            inline void insert(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator At,
                ForwardIteratorT Begin,
                ForwardIteratorT End )
            {
                Input.insert( At, Begin, End );
            }

            template< typename InputT, typename InsertT >
            inline void insert(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator At,
                const InsertT& Insert )
            {
                ::boost::algorithm::detail::insert( Input, At, ::boost::begin(Insert), ::boost::end(Insert) );
            }
           
//  erase helper  ---------------------------------------------------//

            // Erase a range in the sequence
            /*
                Returns the iterator pointing just after the erase subrange
            */
            template< typename InputT >
            inline typename InputT::iterator erase(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator From,
                BOOST_STRING_TYPENAME InputT::iterator To )
            {
                return Input.erase( From, To );
            }

//  replace helper implementation  ----------------------------------//

            // Optimized version of replace for generic sequence containers
            // Assumption: insert and erase are expensive
            template< bool HasConstTimeOperations >
            struct replace_const_time_helper
            {
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End )
                {
                    // Copy data to the container ( as much as possible )
                    ForwardIteratorT InsertIt=Begin;
                    BOOST_STRING_TYPENAME InputT::iterator InputIt=From;
                    for(; InsertIt!=End && InputIt!=To; InsertIt++, InputIt++ )
                    {
                        *InputIt=*InsertIt;
                    }

                    if ( InsertIt!=End )
                    {
                        // Replace sequence is longer, insert it
                        Input.insert( InputIt, InsertIt, End );
                    }
                    else
                    {
                        if ( InputIt!=To )
                        {
                            // Replace sequence is shorter, erase the rest
                            Input.erase( InputIt, To );
                        }
                    }
                }
            };

            template<>
            struct replace_const_time_helper< true >
            {
                // Const-time erase and insert methods -> use them
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) 
                {
                    BOOST_STRING_TYPENAME InputT::iterator At=Input.erase( From, To );
                    if ( Begin!=End )
                    {
                        if(!Input.empty())
                        {
                            Input.insert( At, Begin, End );
                        }
                        else
                        {
                            Input.insert( Input.begin(), Begin, End );
                        }
                    }
                }
            };

            // No native replace method
            template< bool HasNative >
            struct replace_native_helper
            {
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) 
                {
                    replace_const_time_helper< 
                        boost::mpl::and_<
                            has_const_time_insert<InputT>,
                            has_const_time_erase<InputT> >::value >()(
                        Input, From, To, Begin, End );
                }
            };

            // Container has native replace method
            template<>
            struct replace_native_helper< true >
            {
                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End )
                {
                    Input.replace( From, To, Begin, End );
                }
            };

//  replace helper  -------------------------------------------------//
        
            template< typename InputT, typename ForwardIteratorT >
            inline void replace(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator From,
                BOOST_STRING_TYPENAME InputT::iterator To,
                ForwardIteratorT Begin,
                ForwardIteratorT End )
            {
                replace_native_helper< has_native_replace<InputT>::value >()(
                    Input, From, To, Begin, End );
            }

            template< typename InputT, typename InsertT >
            inline void replace(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator From,
                BOOST_STRING_TYPENAME InputT::iterator To,
                const InsertT& Insert )
            {
                if(From!=To)
                {
                    ::boost::algorithm::detail::replace( Input, From, To, ::boost::begin(Insert), ::boost::end(Insert) );
                }
                else
                {
                    ::boost::algorithm::detail::insert( Input, From, ::boost::begin(Insert), ::boost::end(Insert) );
                }
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_DETAIL_SEQUENCE_HPP

/* sequence.hpp
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
*/