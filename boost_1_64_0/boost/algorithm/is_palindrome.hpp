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
SFZcw8KfERkZ1Qb27oFVUTAy1RH0+PTA/H0xoLkpBaY7fcX1k3h2HHafrFqIyafjA9f+upxsPxm4bCSzv9JfiLUKeXUU/wtFn3hur4vbNVnjo7gSluuh/Y6bhvjR26aFlb8APkdpyt9/nyAifSVYFHGLU/y1WyWekLB3XRjXUPw4ji+fJtc/WPeuniXRFwKvhWLjSxznJ7uywgD8EAe0mHzM2xcoqg14ztmvOnH5cq1eeVpqAhzjOT/V1gSKXvP8RDVMbG95ldoBLduUxmUyZJdopVYdPm8Tdzh117/7PA/zwWi+/3C1UA1KW2n5lRQSFrNiLAxM+t39dHzBMxoLHrNmWg1aHqm6U3wX6djY/62SnUrma68fkaBPflHw98IK5iVEwInQM2CICG2V0O9rZRnfqfeg+PqqZJVt/eZ+IVvWb5e6sH6bd99hWL+9v9K+fusB5p3osq3f/FFepWVxtjAzmvkQrdIGySqtwWlbpS1+Z3fsYNZn16xssz5L4PXZW8ay7LJOlmXPi0tUuTSU1j8FxpIsi5dkt+VgOZYly7EsYzn20z68HKNg061IcnM765zWi6jPE2kR5aMiF/6TvWsBj6K6wtnMJtlkF3bRgMGiBhM1sLYuWa3BWJshuzADs4hFEZ/FN0prkRAQtQou6G7HrbTWVvvUPq3aVltLeVTMJoYEIuSBvKQqguLGKAQohIcw/c+5M7ubBATUtvaRT9yZO/dx7rnnnnPPueeeW0PI+AHXhroTt/2YFlWj+BpLapX/UKQmM7m+qng4tb56hNdX0r9mIdXraOj+Bsa3dca1PWSGNDsRwFrX9cfGnRtT7CC0LyZe+9POw4Q0cy/AwkrO6CNuB62+Wqy6hiGhepxYdZ1JzwEiJ+p+528EiZ6ZDIpI61q4B6LhH9pIQTw3MZVbYm8k64h7O3FY2l3t/1tk0pvcp9Fywm2Fjyng8DEfLLZ5+DBoYuvSnUb7o4Im56KAQlc4nZFL+3gn4HxmMt+p4OYdU8W+VskYZ/r6plf9WdUfUNFMs2gYTXScR3sFqB/lKP9piIx3QWAg5z/g6J7/T48if9a/4+L6I/Erhbcu600iqNHoHJ+MqcfEPlzVxznopLAvpM8nSg7hGZ5TGaGYgvOeFR5mqRqxUlraFCa+LjGfUeoW32QO7L0ikNjLhovGNza6OfGD55mEkOsYusvnibsHxVUIWHH/y8C0BQFHiOcFASqnVRhOFRN0IevEc2I/GkbKuZjgOBL8vHlfIQCjvSP8JGZiqZH420KW/olX8YvIkIlX+HevQrs9j/J547fdcx/Cg7j1Hg+LHaiKlgXbmncaQX0lBtzftohCxiRGfw+VETCceQIyB4XGUQjB62/jKMgrhKgfjo+qiI6xcL5IOjMt3D3OO08fEKKT2RwG/fEfiSySTdiCy5DI0j1xl3l8tz0jWd9kUR9cjJLh8sV+OlWPssk1Q6VZ6+8o4w3T4RpWfmjGiRxZ/JXE6WYtQDVDc0IKGieXmz4Lz1RiJEGk0NnnD9byh0maBLIRcHrvKVa4QapzpfheYQL60sPcxLybMT86vJxfdOpXIl8BsCbKgom0Ds4lCvMJfomFX+IUGPyomqlgwFT7ZPwSiifh17qyAJWtwHzXUTB9CfNiy87uMXv/Q44ZV4yn2XG5mMZfqOWZEdL3IeYMHN6I6N95DkanvdPc8/4MPPEdXhTBXNwBOJ1W9rvU1m3hLbaxsbP9idt+iAqSEbQRkE1MLIrhAjJ8jB/ryScK+vOrqMxaQU340KDhmSEu0ybxciemVssBF/Pcvz2QjH0aGhMbdGZiEQvMRq4orQ1WKZioVotqjQMGX+YnLzooJOi9XOM6EiE=
*/