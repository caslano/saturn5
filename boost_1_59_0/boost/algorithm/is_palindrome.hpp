/*
  Copyright (c) Alexander Zaitsev <zamazan4ik@gmail.com>, 2016

  Distributed under the Boost Software License, Version 1.0. (See
  accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt)

  See http://www.boost.org/ for latest version.
*/

/// \file  is_palindrome.hpp
/// \brief Checks the input sequence on palindrome.
/// \author Alexander Zaitsev

#ifndef BOOST_ALGORITHM_IS_PALINDROME_HPP
#define BOOST_ALGORITHM_IS_PALINDROME_HPP

#include <iterator>
#include <functional>
#include <cstring>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {  namespace algorithm {

/// \fn is_palindrome ( BidirectionalIterator begin, BidirectionalIterator end, Predicate p )
/// \return true if the entire sequence is palindrome
///
/// \param begin    The start of the input sequence
/// \param end		One past the end of the input sequence
/// \param p        A predicate used to compare the values.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename BidirectionalIterator, typename Predicate>
bool is_palindrome(BidirectionalIterator begin, BidirectionalIterator end, Predicate p)
{
    if(begin == end)
    {
        return true;
    }

    --end;
    while(begin != end)
    {
        if(!p(*begin, *end))
        {
            return false;
        }
        ++begin;
        if(begin == end)
        {
            break;
        }
        --end;
    }
    return true;
}

/// \fn is_palindrome ( BidirectionalIterator begin, BidirectionalIterator end )
/// \return true if the entire sequence is palindrome
///
/// \param begin    The start of the input sequence
/// \param end	    One past the end of the input sequence
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename BidirectionalIterator>
bool is_palindrome(BidirectionalIterator begin, BidirectionalIterator end)
{
    return is_palindrome(begin, end,
                         std::equal_to<typename std::iterator_traits<BidirectionalIterator>::value_type> ());
}

/// \fn is_palindrome ( const R& range )
/// \return true if the entire sequence is palindrome
///
/// \param range The range to be tested.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename R>
bool is_palindrome(const R& range)
{
    return is_palindrome(boost::begin(range), boost::end(range));
}

/// \fn is_palindrome ( const R& range, Predicate p )
/// \return true if the entire sequence is palindrome
///
/// \param range The range to be tested.
/// \param p     A predicate used to compare the values.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template <typename R, typename Predicate>
bool is_palindrome(const R& range, Predicate p)
{
    return is_palindrome(boost::begin(range), boost::end(range), p);
}

/// \fn is_palindrome ( const char* str )
/// \return true if the entire sequence is palindrome
///
/// \param str C-string to be tested.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
bool is_palindrome(const char* str)
{
    if(!str)
	    return true;
    return is_palindrome(str, str + strlen(str));
}

/// \fn is_palindrome ( const char* str, Predicate p )
/// \return true if the entire sequence is palindrome
///
/// \param str C-string to be tested.
/// \param p   A predicate used to compare the values.
///
/// \note This function will return true for empty sequences and for palindromes.
///     For other sequences function will return false.
///     Complexity: O(N).
template<typename Predicate>
bool is_palindrome(const char* str, Predicate p)
{
    if(!str)
	    return true;
    return is_palindrome(str, str + strlen(str), p);
}
}}

#endif // BOOST_ALGORITHM_IS_PALINDROME_HPP

/* is_palindrome.hpp
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
*/