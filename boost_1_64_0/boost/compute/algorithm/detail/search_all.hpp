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
u5twUQs7/IhhCDlUBDnGaIMLPoQxiGGMofwewkYdrOhGBKYfEDaaYUcfBjCCPGb9kLqDFnTABR9CCGMYPSHCQgIZlN1LWmGDHV3wow9DGEEaeVT8iHTDhV5EMYhhZGH+MeWCVvSgHxmY+qiXqEEz7OiCH32IYQg55FFxH/lAC6LIwvwTwkYdGmFFKzzoRg8iSCAD0085trDBjgCGkEYe1f3UJXTACx96EUIUKYxh5lbiggPd6EcCZT8jT6hBLRpghxsDGMIILD/nuKAeTWhBGzrQixDCiGIQWYyhKkzcqIMVDjjRjR4EEUEcCSSRCRdvIJEmNKATMYwghzyqf0Fa0IQWtMGHMKIYxDDMvyReONCNOBJI/tKYdK5EDWphgx1uBDCAGIaQRg6WB4gbTWhBG7yIIovyX5FnWNGNCBJIIgPTg8SJBjTDhk64EUAMQ0gjB0uEckc9WtABHwZRtY1yhRVOBBFBAhmU/Zp8wYZOdMGPAYzA8hBhowku+BDGIMqjHDdY4YQHEcSRiBZvsBM2GmCDG10IoA9p5FH9MGWEDvgQwiCGkcIYqnZwDsCDfsSRgClGHtAAG9wIIIY0cqjeSfrRgjZ0wIswshiD+TeUE1rhQQ/6EUEGpkeIBzZ0wo8+DCGN6jjlhBZ0wIsQwogiC/Muygx1sCKICOJIoOy3lBdiGEEOlt/RRmAWWuCCD70IIYoszIOUERzwIIh+RJBE5aOUEezogh8xDCENy++JB7NQjzb4EEYWVX/gWKMOVjjghAfdCCKODGqGyAfs6EIAfRhCGtW7iQctaIMLXvjQixDCGEQWVX8kbljRjR4EEUEGoyh7jHjRABs64YYffUgjh4oE8aMebfAhikGMwfw4dQBOdKMH/Uggg7I/ES76MIAh5GD5M2GiBS74EMUwzMOkH3WwwoMI3HsIBwNIw/IX0oYmtMAFH3oRRQpZlP+VMoEVrXAgiAiSKN4kq0QtGtAMOzrRhQD6EMMQ0qh4gmOCerShAz6EEUUK5X8jTgQRRwajMP2d+FALN7owgBG0JDm28KEXYQwii/InKRM0ohVOdCOIOJKo/Ad5QDPscMOPAIYwghwse8kDZqEJLngRQhSDGEYKWZhTxAsruhFBEqMoe4q6hAbYYEcnAhhAGjnkUf1P4kQLXAhhEFmMwfwvjhWs8KAfCSRRliYO2BFAHwYwhBwsTxM2mtCCDrjgQy8GkUXVvylHWNGDfsSRgekZjgsaYIcbAQwhhzwqMuQDs9CGDrjgQxhRDCKFLMZQ/ix1Go1wwoMgIkggA9N/KEc0w40u+BHAAPKwPEe8aEIHvPAhhGFkUZUlHnQjiAjiyGAUZfuIBw2wwQ0/Ykgjh4rnqdtoQy/CGEQW5v3EgTq0ohsRjKI2R/rRhT7EMATLAcJDC9rQgWFkUfUCYcEBJ7rRgzhML1Kn0YA0cqgeJSy0wAUfQghjGGOoOkiYaIUTHvQgiDiSyGAUppeIA7WwoRN+9CGGEeRRcYi4MQtNcCEM8xhxoRFWeBBEPxIwHSZ81KABzbChEwHEMII8Kl4mb/AijGFkYT5CntAIK1rhQDeCiCCBJEZhyhMnGmBHJ9zwYwAxtIxzHOBDFClkMYaqo9RX1MEKJzzoRwRJjKKsQDxohg12dMINP4aQRh4VPLVSjzZ0wIUQohhEFuWTJpmqMBONsMKJICJIwDR5kqkMtehEADGMwHLaJFM1muBDGCmUmwkTVjjRjR4EMYqyKZNMlahBA+zoQh9GkEb1GyaZZqEeTWhBLwaRQhZjKD+duNAIJ3oQRARJFB/IqIUbfvRhBHlYphIHWuBFLwaRxRiqzphkqoMVDjgRRBwJJGF6I3lBLRrQDDs=
*/