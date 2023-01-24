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
+VVNQe/j5Aay6/XDZHDe+J+mD2d7ndGfRHuMd+Txwaa2WndHzLI7Pe5wNl/gvAT81sXp8RxxrdvmlGv5KYI5vsycRPcb/lM+1XwJs04I5RFRuZQ20LqylaDdX/S6dF1zZroLxjHt8qcRQBBxDV3xI3Oqtvf92eczyUXvRCJZfl6tUWK2iaNLvkQJ+ggkqESXDdP6LAQi9Vcg6ok/tcb3bAiUBLr7tpHxlVbv9ZSrY3mtYN5sUUoQ9jgK4Ir4YdHtZL+xSQWjz0+EwWlRQy8ZMoWv+L/0VLxVlG0noRzZEf94fCLy29K9SnLmz4Hiao/fhM80/or26Rh3VWVg0f1gULyAnh8xBr11qteZ2nav6mvwkC7iJz26yEF3/L0Ssq4OvZN4XqnPsRZxCCm/4uESWZinqo0AQfImWgJPsh1CntJSY6rP9BLMh5yif4ZdA+QlpzNKHUXXFrH13F+MwYVCPEbwpzsVa4kDso7qBd3GVPQ5GWgMfxtqBcEojykLvTVNExDuGtngj4rRz/Gs2vlkSPV//AZFpf2ffRgI3advaC81OR97AchNZHyaJYLft6DjO7NS7d6R7l3P78uF30jbpL2VVfZF/FkfsISQLaHylpd0kK4TP/WRmPNGYa6ez5VnfGntxSRG7V+EKJFlsv29ChcRepStoZ8vaiwg0dMKtWzgjV+J0as5CF8hF3Pnzzc8CNeofn6Y8+ELBVIZ
*/