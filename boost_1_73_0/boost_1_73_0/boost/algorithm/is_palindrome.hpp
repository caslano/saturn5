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
EaXaSm7qCfTBAwkJ43OSjHrcM66pbKh1gv23wnuKqAuyOyrJufCBJTVluZ57RAaLpbxgM14hYeBcQii8RyzU0d5GNdWxRC1TdBTopnD4NhkjXUKOHEP4p45BBubqCPT4XEI1DoBxfsaKlYNc3ySoM+AQMTfeYEuMZ/yMWNB1oP+NpYHy/EjSxwy6QI840pf6pHvaieOo/lEq9vMjj1IqJ7Nsucxhk4a7zFwxrpHcJhxqOCoG9cac/F668FCKgms+mi/8qsjWs/kEz2Ghi2hIot3UVHP4cATXAL2a2ksNrXSI0B7doUBJFeJrz6tadGxhgyHY1YLEsvF3ztNTazG6pXsMcR06mUngYZcn+zg4TvuD8dtj/RKWf3tQIU37yWFyNtpSPN21LYGsFuVhWaw9wsggpCD6MNeIoMQRejt3b8Gj9smiHENr2xz88qo1574eYanDot48PFJLNQNqX+hhclbGHiiCARIvF335ooPwZxAVmAMlstcwMSgyOunOSw8PA2a10Ap0WtFnhSnVNVdcDyb058v5x2C6us6YG3helXfd0jlQWGK/AZhDVuiRfRVMToDaBmqk38AS1nf1vnce2NKY4dpG/LX697770LCZ9x/mdZwKzE4NnKfNA7zIBPuVRpqJUAGof1RuljSp
*/