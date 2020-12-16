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
mvUlVzbivirPNbznHl9lu6H2fJ5VdAe2ynYjvKXM7IzmBOeD6+my13gprVRLrgB/te+rSihDgswSTFM+LVpB12MfRzrj52lUFXfaSp5FP/x2rDk//r6Xa0qXO3v7abSvQixcASe7g/1+iVuZ92CVkvFOw989a++NgVEY9/ud5TTyHa+0wZiftaesKGnWntcCvfH0QOX0rRnr6VlcU41XNkuGxxe5NDzmsA5w8JYmY8lyWvoOkDdCs4TZsbLoLOSNurT5hIUjSbXZ0tyYXqGKRkSPaQvHxYLjKgtHa1W1+egNUzl/spw6RWl/x7PYtIeb3olabCh5nSVYY7vRwMe6dNCktiytszxX1MRqtwvHi9eEM5GGX/KJ0sUMKtVRguLMKQEfFBrBCJ5gBJNSsbAHTiW1QqJNHNw8a494znkKoPxIVNpRajKA6MHx0fzG89VqsgCL1nkQgE2PyHzWPgf+gURYNN+Ad7FJpVf8Z2LvQuDrCYYah+ozCnps8UwrBcdEFJiFAuPtEY9Hf2CTAneHC1ytC6w+RIH1kQV+ZZMC7wUuqpRjzmgJZTnmkIsl9WBsxHPY4y23Hm+TZxlCcD/STbdwchtV3i4mQacb+AalnUtpLqTxCSgSAZNFjW3TAMmMF31W5ZPX7LM11gbt2WMEUrEbFgC1SBO9QSqOOvJrD853KWtHnfV1GlR/WyLXY01vcPLKcTUBL1PufyLRfNF7DoH/HohNw8bJfr5CiFPe1VwAMki5RVepmQLnJbjBBMemPBbc/QLXCyloCr5JiNh33+Di8t9gabEbP5sN8ui3PbRHpbEUfTo6/S8UiIVAi5TP3hSI7a3F58qX+DWqyM3S/5kG9UD7Stm2278VtrERd0mNnXn0wvxndCJUWhnmFqeafp5f4LZVPdoJ1/hmscUqahD0C6uYmEPi/2oawEWlMj5XUq6SEPVfDrwyUsDIy8RHFrOnPyGZC3paK4tcUErwzCNDAfxCg+sXSy5sQdQVb7D2/Q5+gQeQwCWAyOh8l/NxJhBjZvmZZBlAMAXIQukjkAepbIuEHy+GBy+0/HAOr1H4x0Tw0mZCsIj3kjk7qPLzuMbSIvQdhKLJ1AXM3UXeZhwLK41K8Tz6+b/dDLHZ+616wXC84m7tD561oW8SHPl6p5Att+OVqYnYEzheub6t3/gsx3BNd7zidFd8mehJ2l2xORE52phfW+grSX8heFySynG+jUC7HGcFYJMUwg4OeJxL4P+/QqU4XlnNgWTHK9UcSMwxHl1IPj5znI8GY3BGQwmOV8r5M46ir5obk2Nf4TYqzOwVZvYKzv6Qzv5QRPYKfOrsQyk7rr5XmtkrzeyVnH2Ozj4nInslPnV2z1zE9bcl1ePfWFQ5qR7/IGynmGlx/YNxyWiAHGPYRCeBxHuca6kx+rdCLAcSOOB27s4xcotynLgYvvTHNcUat7HYzL7YzL6Ys8/X2edHZF8M2sYjSqPwE4oNP6Y53E6FWgM0d4IHtXKuQ6UO1r9Na4QiWqxSBS1bqd26UqOd9ejDY9JRh61P05qgFUZIHQ/dUVcdtqOOXqWMYfmHr9gP6aihx66jjGHelq2T2VH+Y9hRLVghNJCLauSsF77nOXYdldWS9Qp3VJ+j2lFmdRBh1gjowpXKbNlKmTOq17GcUektWyezo3oe1Y46XKVSW7ZSZkelHZOOMuui65bSMnUyO+qUY9pRyUenozoepKPMekTWrcXrlNiydTI7qu0x7KiDVSjHOCGyTmaFgOnI+inumEyoll52dR+hf2AvljNvepodqHC3Lw2fwOXGK8A2DiZSMNZYgmQKxVEomVSb6fQZj08BaWVUaZBEhARDa4QktQ1QSWo=
*/