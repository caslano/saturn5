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
0RJSdGYXF4AEFmq/i59vQ/dMpsIUMAkMSkk+ozTmfGT1z3GGad0f8Ax+Q+HfaC4A2EB2j0CHVo9tjDPe7nUV2z2uvFCOVPMWAJxLQ2VBitSSuXa1Ck5DebRKhSFaaogiHlueRTpt9cxmR3hv/Q5YptSPh8e9vzHV+JeMskhNZe4xk0e4LgfWFjb2n1wG8/kw7/jmMkvuJ+VJ3vEtuZ3ClAapE23EyPyNi5vdil5YdbAPxse8Al0PpbxOPMddE8Be/bhdoX9CgdQkevCMUsCtxAir/t6jfHUGCc4GJq0S81wdoBgsOwnfjhOeoeQDL4jeWBulNPaKgpjbWG7A9ZH7EEyXAXkRyEcx85Do5eeMYXlVvQfFwIoEb+wldkw5gj/EUzQb26Tm7D3eSQbFPBDIcKLVMXiPPW2v3VNkEiUHRjII/l53doAwdmU0QGFUu4P21dM9QfseFIALAG3xtwiaOLhJTNuOIG2ikE4O0Mh32z0OgDQAo9WtGIRVJcYeBH3urPAvXXRuYl7TA2Jn3gVAu+t/jJAH7WkH7Z6ZKXZJI2ZIUG8c0gEAPYWB7pDq3EqssOqN2B7Qrzs79EvPDf3jT/WA3nIB0Cf/j9FaEdNOiZ7KDLsUxiDUL/KuQOoCFDI0FOxSs7sy2SiswnzOYTQAbcJEOjsm88+NyRs1PTAZfQGYTPhvmGtUuEMJ6hUbiaDMzdRRaEaOAcwdgEQf
*/