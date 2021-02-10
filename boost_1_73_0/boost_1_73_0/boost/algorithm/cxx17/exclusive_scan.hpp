/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  exclusive_scan.hpp
/// \brief ???
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP
#define BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator exclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, T init, BinaryOperation bOp)
{
    if (first != last)
    {
        T saved = init;
        do
        {
            init = bOp(init, *first);
            *result = saved;
            saved = init;
            ++result;
        } while (++first != last);
    }
    return result;
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator exclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, T init)
{
	typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::exclusive_scan(first, last, result, init, std::plus<VT>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP

/* exclusive_scan.hpp
kPdfmXgKc4sh8orweOhlL4LJ5Q1BJUxgp8r8JD/f927B5kkuIToKPAWSHwk910fhNlmaAlM2D6DWJ7me+GSZzNkO0VTegMcUsHQM1to424IHp9N6OHu2F3MYQycXk/mx9873vvP/Eq+RH+E5AlBNQHoSQhULYevuC7BLV6jvwzwlzjyfONTxxKhJ3sKNKxQ84w0CWXeeNgXP/RN+uInZhwI6UHwjoRJfelMDGv9U5nMOWlyObrAjHmgvi9FzWAEoDxgnY+Q0dWJ9oVI7XTHpr8Sg/sXZBfMbCZSEBN/X7dw40h1+Y6lILl4gYbOlNA8Asn2DDU805hl3scMzEIDhzjn43Jc1BIcBc/NpJipdlFP/gvgsQQgn+DAqfYrVhZ4yAWHzLSb+Ftu4V+pADoVNFq7EEnrbaTZKzjD93O3dKO/IuvJ1EKP4BwPdjNmjtzu5dv8/OziAbOPu5M3sWaVTPu0ks4929BnZmXrw4n72rdgdzy0zf/rbO7HKWeAURiF5QfEt+COnoLsNkwlZAvY++fpE3EyhDm2lwLX9haR2lD9AEWP607XglYXyVBTErfmoZvvaK9Xilk02rtPHGiTyF3fEa5KFBSfCgwwe7IPrCvQXMv5la37wx5QoNAEjhjhKhML4SPitIUZjwoHg
*/