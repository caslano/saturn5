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