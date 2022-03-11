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