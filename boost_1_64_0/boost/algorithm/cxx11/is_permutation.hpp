/*
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_permutation.hpp
/// \brief Is a sequence a permutation of another sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IS_PERMUTATION11_HPP
#define BOOST_ALGORITHM_IS_PERMUTATION11_HPP

#include <algorithm>    // for std::find_if, count_if, mismatch
#include <utility>      // for std::pair
#include <functional>   // for std::equal_to
#include <iterator>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace algorithm {

/// \cond DOXYGEN_HIDE
namespace detail {
    template <typename Predicate, typename Iterator>
    struct value_predicate {
        value_predicate ( Predicate p, Iterator it ) : p_ ( p ), it_ ( it ) {}

        template <typename T1>
        bool operator () ( const T1 &t1 ) const { return p_ ( *it_, t1 ); }
    private:
        Predicate p_;
        Iterator it_;
        };
        
//  Preconditions:
//  1. The sequences are the same length
//  2. Any common elements on the front have been removed (not necessary for correctness, just for performance)
    template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
    bool is_permutation_inner ( ForwardIterator1 first1, ForwardIterator1 last1,
                                ForwardIterator2 first2, ForwardIterator2 last2,
                                BinaryPredicate p ) {
        //  for each unique value in the sequence [first1,last1), count how many times
        //  it occurs, and make sure it occurs the same number of times in [first2, last2)
            for ( ForwardIterator1 iter = first1; iter != last1; ++iter ) {
                value_predicate<BinaryPredicate, ForwardIterator1> pred ( p, iter );

            /*  For each value we haven't seen yet... */
                if ( std::find_if ( first1, iter, pred ) == iter ) {
                    std::size_t dest_count = std::count_if ( first2, last2, pred );
                    if ( dest_count == 0 || dest_count != (std::size_t) std::count_if ( iter, last1, pred ))
                        return false;
                    }
                }

        return true;
        }                      

    template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    bool is_permutation_tag ( ForwardIterator1 first1, ForwardIterator1 last1, 
                          ForwardIterator2 first2, ForwardIterator2 last2, 
                          BinaryPredicate p,
                          std::forward_iterator_tag, std::forward_iterator_tag ) {

    //  Skip the common prefix (if any)
        while ( first1 != last1 && first2 != last2 && p ( *first1, *first2 )) {
            ++first1;
            ++first2;
            }
        if ( first1 != last1 && first2 != last2 )
            return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2,
                std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> ());
        return first1 == last1 && first2 == last2;
        }

    template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate>
    bool is_permutation_tag ( RandomAccessIterator1 first1, RandomAccessIterator1 last1, 
                          RandomAccessIterator2 first2, RandomAccessIterator2 last2, 
                          BinaryPredicate p,
                          std::random_access_iterator_tag, std::random_access_iterator_tag ) {
    //  Cheap check
        if ( std::distance ( first1, last1 ) != std::distance ( first2, last2 ))
            return false;
    //  Skip the common prefix (if any)
        while ( first1 != last1 && first2 != last2 && p ( *first1, *first2 )) {
            ++first1;
            ++first2;
            }

        if ( first1 != last1 && first2 != last2 )
            return is_permutation_inner (first1, last1, first2, last2, p);
        return first1 == last1 && first2 == last2;
        }

}
/// \endcond

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 first2, BinaryPredicate p )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last1    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \param p        The predicate to compare elements with
///
/// \note           This function is part of the C++2011 standard library.
template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1,
                      ForwardIterator2 first2, BinaryPredicate p )
{
//  Skip the common prefix (if any)
    std::pair<ForwardIterator1, ForwardIterator2> eq = std::mismatch (first1, last1, first2, p);
    first1 = eq.first;
    first2 = eq.second;
    if ( first1 != last1 ) {
    //  Create last2
        ForwardIterator2 last2 = first2;
        std::advance ( last2, std::distance (first1, last1));
        return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2, p );
        }

    return true;
}

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, ForwardIterator2 first2 )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last2    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \note           This function is part of the C++2011 standard library.
template< class ForwardIterator1, class ForwardIterator2 >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2 )
{
//  How should I deal with the idea that ForwardIterator1::value_type
//  and ForwardIterator2::value_type could be different? Define my own comparison predicate?
//  Skip the common prefix (if any)
    std::pair<ForwardIterator1, ForwardIterator2> eq = std::mismatch (first1, last1, first2 );
    first1 = eq.first;
    first2 = eq.second;
    if ( first1 != last1 ) {
    //  Create last2
        ForwardIterator2 last2 = first2;
        std::advance ( last2, std::distance (first1, last1));
        return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2,
            std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> ());
        }
    return true;
}


/// \fn is_permutation ( const Range &r, ForwardIterator first2 )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param r        The input range
/// \param first2   The start of the second sequence
template <typename Range, typename ForwardIterator>
bool is_permutation ( const Range &r, ForwardIterator first2 )
{
    return boost::algorithm::is_permutation (boost::begin (r), boost::end (r), first2 );
}

/// \fn is_permutation ( const Range &r, ForwardIterator first2, BinaryPredicate pred )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param r        The input range
/// \param first2   The start of the second sequence
/// \param pred     The predicate to compare elements with
///
//  Disable this template when the first two parameters are the same type
//  That way the non-range version will be chosen.
template <typename Range, typename ForwardIterator, typename BinaryPredicate>
typename boost::disable_if_c<boost::is_same<Range, ForwardIterator>::value, bool>::type
is_permutation ( const Range &r, ForwardIterator first2, BinaryPredicate pred )
{
    return boost::algorithm::is_permutation (boost::begin (r), boost::end (r), first2, pred );
}

}}

#endif  // BOOST_ALGORITHM_IS_PERMUTATION11_HPP

/* is_permutation.hpp
DQhsnIiQ+/7IA0iLhBw3fgjNlm2FMXIM9SzPWHJ8+3vqtTIH5onoSzxeqvUwHi/DbLZ6cvJ8LpzdIirl0hsxuty95FTcsgVdjLGCID2v0GoKn/PC+mReXV8U47l+J5X0JeUI8PEAx2znqY/ZzrPeiPn6Z9L9zGsyBLf9NjTZfsVFAPMn5HyjR6re+53Gh3qfA3mFep/3l8XfWFn3ybxyHeaQyhzKacyhA8LlLdZp39W8HxguTJws6A0WnNBFfL0C2wAwU7PLskcc8aX2vqEDTOgmNkpr2vBHj7ssxyksBwK2efQZFFqfT3aeiNmGcQufbRhB9oq70eW1YQEOmz+20nvAVcXZngzYZhHo0UKXlwy+mgze8rOFL4V/w/wZQgseqxD49vqE0/UhvP5PhgrBJd84OI9jm9K0IbGHHfK3Yb+gMW5WEQ+pIV0AvAvBu9jQtOJ7h8Nu+FDQVhhLMbTccj4uMjtrUBYy2JP4UIh/tUFZf14WOyLKx5vXiX6ARi0rgMdqVAbzASQVV+LvkBqqiZ3AxgtAZzUDiuAXVIA+ZysZb6YLIM6PsG05TQo0dsm3rJeK9s7hD25g84fay+WAm01NYVGBOgmz4jswWIR64R8BgoUS0VD95MkyU/VDyHLH+aWypOx+ZXBZhAw3vBbsZ69D+aIReM6voWZoW6x8P2HPqQTGybb2V9XXbiT+MuSjQdC+BY52KdpPeMGE5nJXVg00CqgNOQlkr+yFhgV1U3vzFWowPsO9A2sD+pDeQ1x9FiOwV/84NwCCQzW0f6ofFr9w17+1H3tZuqLMkYwWwPtvb3fOxsmfUDm/kCepphqtPVpTAqjNyU1x0RBmOfHZeDzuwmM1dT36StNtHO4sXAeAav8LdBsn8qP7o59i1+h+N51oQ0JNoL9Y+LyDYyhi6c1DiY0nqql113fQFB5VFiZgPr9WU+WRHUxVpg4m08m5xc8d0jQSTp1N4OEjwcl7I/57XC7vvYNJ/1FAE3IdxtwknAIAQ1vJ58AFq5StZI+Z8IwFGll7yKVeO8ouvSyGdidYI6TsNoWnjZ3bFx+ZPSXBpQZUf/aZnnqHvFeyVXzfJQ8+YlRX32NCgEFVq4ZbuD40F9etaDPbXk19AW98UcRUS+aipEgnMNJ4rr/dasLWCyy7m/RW7XHBvdOd8ibwSsDJm9XU+us6YFI2QgPy0FYOA/siEvqOgHDq6ULlBDCXy9qWtd4h16mpa0QZumT30FMoJAHPGKf8A/n9tUAHJNkQeBYxMMrrVf6x0T00ZVE77kX20TuDbpV8XniGHh/s7diLx3pjr0IP5OVsmnxAUrdIMAtGfbY3Y68aW9x4oa3kPXwITz1tJRXi6QZbCa9gBVVYkAfIcUPzk0xes+3NuKvxMNYrxdbOZ9wGxETHK1ngFdYrjJ+DFnXWHaupG6/tYEIPld7M60Y7NXX6cBqBzmrqBSPCKEzOBy1sVu6nTZcMMpFBJjLIxHeLYVB0YxD4VsUOuJC5XgeWKRahdiINbxHImp+KVzGBe7rWPaqmVg6nT8SQynI+LEsN6r+LkSqcQ8xIPja21/Dubt+k7oWp8CdbpNLaOaUtHO6PlXp1nOn5hg1aXHHDNRd2mchhD0PMkreIpZNGeBWoBHWfw3V7OtEGN438RcSOAl5lJWdyBSpcMX86uRYfrpw9zCIWDFF3bSOEtU3/bz9Z/mxzYXsxS9vyLJ3dy+Q5YKuo76IzlOjxirM5/nsi0xmCWlh9khnsKDtYcbtwZJbehR0MJc8fSHuNfo2+gQuV0sO0/2Kwn4sPyYPXhdhZx0SDnWWCnY0BOxsHVvbjKJ2V2RGYCqpaSf6I9MxyIPvMwtOKjumf86s=
*/