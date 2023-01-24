//  Boost string_algo library predicate.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_DETAIL_HPP
#define BOOST_STRING_PREDICATE_DETAIL_HPP

#include <iterator>
#include <boost/algorithm/string/find.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  ends_with predicate implementation ----------------------------------//

            template< 
                typename ForwardIterator1T, 
                typename ForwardIterator2T,
                typename PredicateT>
            inline bool ends_with_iter_select( 
                ForwardIterator1T Begin, 
                ForwardIterator1T End, 
                ForwardIterator2T SubBegin,
                ForwardIterator2T SubEnd,
                PredicateT Comp,
                std::bidirectional_iterator_tag)
            {
                ForwardIterator1T it=End;
                ForwardIterator2T pit=SubEnd;
                for(;it!=Begin && pit!=SubBegin;)
                {
                    if( !(Comp(*(--it),*(--pit))) )
                        return false;
                }

                return pit==SubBegin;
            }

            template< 
                typename ForwardIterator1T, 
                typename ForwardIterator2T,
                typename PredicateT>
            inline bool ends_with_iter_select( 
                ForwardIterator1T Begin, 
                ForwardIterator1T End, 
                ForwardIterator2T SubBegin,
                ForwardIterator2T SubEnd,
                PredicateT Comp,
                std::forward_iterator_tag)
            {
                if ( SubBegin==SubEnd )
                {
                    // empty subsequence check
                    return true;
                }

                iterator_range<ForwardIterator1T> Result
                    =last_finder( 
                        ::boost::make_iterator_range(SubBegin, SubEnd),
                        Comp)(Begin, End);

                return !Result.empty() && Result.end()==End;
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_PREDICATE_DETAIL_HPP

/* predicate.hpp
pTLHix/qgJ9IjeOuiOD45AmS9Sa/G8kJeSeLDT7VAFVYj0OPye02/Hmr+0Q2XKPbmoaHDGIFXsqFDWisy49hESH1rletQsqTGAegrNHTFMfvrNCUn4PrFxQi4yrL5XjJRD/fPut8f0fRSlxjPc6JhhlPps1u0V/p0oZaEbJmGsJo+1b5yGmU9t9twEhnRYs4HW8w+ccb+z+GiN/N4If8U0uWzO4sCCCGbYLBT4G4JzGpr/1m/Nr6x+hfTzIErlRpsM2NW1n8vK8wpXAQJnccj74NsYkYccozr6UhkhznF5TUuonv71wvmsp2nKo2r6JFTgnso6+Gm9cxtoQLl1BX9wS4QzXKotK0EDFC13VVEqqVrX/Bnsjjfb0raJu4Q+Esgo6lAjNINzaPp1wx+CFulJozkuGaiNGdvwHX4HzoCeCu6htYbudOM5PWnA+rRUuqCSSFi1ApBJqUtAxG/Dlcl+ZRCxVFjrc1rWLEXsJZRV0p8pn4Id8HjGWlSD0xsMashEPFKklq8fvDSYG0d1+qqxWS/LFCMHRfB9pIlvHyaP9m1x3APuoxYVY2Y6DHcF7ZtxmIH4DY8ksxUitqqP6NcyfwHkprl0wlN7fAz9wRdcXTOXNkMUVFODrIP2n02+ybAHDgdwIkH0X7hlXzqKXx4q7Zghfm4zY76yRNXp/t33dhJdZkhcjJDpfhsZmdqMv7o3k1FTLNX576dJ8o
*/