//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_ALL_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_ALL_HPP

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Search kernel class
///
/// Subclass of meta_kernel which is capable of performing pattern matching
///
template<class PatternIterator, class TextIterator, class OutputIterator>
class search_kernel : public meta_kernel
{
public:
    search_kernel() : meta_kernel("search")
    {}

    void set_range(PatternIterator p_first,
                   PatternIterator p_last,
                   TextIterator t_first,
                   TextIterator t_last,
                   OutputIterator result)
    {
        m_p_count = iterator_range_size(p_first, p_last);
        m_p_count_arg = add_arg<uint_>("p_count");

        m_count = iterator_range_size(t_first, t_last);
        m_count = m_count + 1 - m_p_count;

        *this <<
            "uint i = get_global_id(0);\n" <<
            "const uint i1 = i;\n" <<
            "uint j;\n" <<
            "for(j = 0; j<p_count; j++,i++)\n" <<
            "{\n" <<
            "   if(" << p_first[expr<uint_>("j")] << " != " <<
                    t_first[expr<uint_>("i")] << ")\n" <<
            "       j = p_count + 1;\n" <<
            "}\n" <<
            "if(j == p_count)\n" <<
            result[expr<uint_>("i1")] << " = 1;\n" <<
            "else\n" <<
            result[expr<uint_>("i1")] << " = 0;\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        set_arg(m_p_count_arg, uint_(m_p_count));

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_p_count;
    size_t m_p_count_arg;
    size_t m_count;
};

} //end detail namespace
} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SEARCH_ALL_HPP

/* search_all.hpp
Dcbg5J66Tj+Ia64DYbcDqONW5g8aK2+MqaLecBq8sGAVG23lqUjtsPsEiJ7QCSnLaysVD6QmRw91Niv6NjQE5giGPgpWhGlh2bAJMH2t/zUCzl2++A0sC/l7pnPWUYMS5qFVM3nkjXmcUzYOuB7kGS25vdkpfxLapxaGKbTGBMIxwkAu1OI5jOivuQsf2kjMX60EoXCInHk/L9fVqgfjXxAhVvqcoM3/cy1kLz9PC6y/TEWohxuKYfTKmzILgedN5ecWcsUBqU7QjqVtv2EfI8mhM+DV8kIrEeg0AV8sda2vLaQ/VSAcq9XbXqb6k9JKk8bOFD1U01bFhL9sEcQHsvtyKEw3HdAlsCfs5KhmJ/06iZqOVa0LIJI4kF89KZR2zFPa6MVgYsKXf8fQ0/huR8APKMfRT5xZ87oGtHNDd5N1WQepnsx9NUuhlabclLGVa1tnOe6h8/sqC2iDWqhNgU3etnJ82uJ047x5Xxr0YdreP2VWjkueKTBv7Y6KoNRDo80EGT7qWeE9xVQkBQfEcg0AOI50lFHpnbCr6KeuVy74RUqOeqn7WHhQJQ==
*/