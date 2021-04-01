/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_exclusive_scan.hpp
/// \brief ????
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP
#define BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T,
         class BinaryOperation, class UnaryOperation>
OutputIterator transform_exclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result, T init,
                                        BinaryOperation bOp, UnaryOperation uOp)
{
    if (first != last)
    {
        T saved = init;
        do
        {
            init = bOp(init, uOp(*first));
            *result = saved;
            saved = init;
            ++result;
        } while (++first != last);
    }
    return result;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

/* transform_exclusive_scan.hpp
X9BFaEDdwf0xcQRXDwPythNGUeIGbh1X3C2tZiGKHdexGYzue3OFbrQbY/jl+OKZzuagwYhLy+enRDp2oo5HEn6ARMZlKt5KkiGosDniIdTGrjpGszLRc1JH8L1qiPYB3BHQwPF8iIbwr5/PPz7uOhA+OK6dDUknNwZb4xeBdARCteL6TsB0s64xpxn3aYzd/7IlergmFrlvpOSDDdzpLoHEZjsF05BHIdRNAprkW4w14wfGfAry6ttyyPB9K1PFCHpUeZF8aFfh5lrj4CkK4M8ysWw8+zPwk73gKHSl+s1QLRnHjDB0Ro98EBgEoh+6MxWd6J4Kw7803hyxl6yQ650pTihQ10Qm9kIlLntsYgXJU/MHHmbtSKoPUeygfmZg/ysllSGa1902u1Rn8ZFxi9GxXglLTkUhNyo7wm08Yt5XLifezZTQqKTRS+CH7tx5JddP/3MCd5l2SIRg07whFiGZTJfaZTsW6ipoUJWMMdKGlFCbnE5FciG5J8TmtQlgqDfbD+Vp5uxqQYvgpb4BI3hJe+Oo3ER/3QTjgVZcc9wgB+Ei7zIeVTaWIQ==
*/