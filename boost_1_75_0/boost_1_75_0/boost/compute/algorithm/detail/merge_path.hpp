//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_PATH_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_PATH_HPP

#include <iterator>

#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Merge Path kernel class
///
/// Subclass of meta_kernel to break two sets into tiles according
/// to their merge path
///
class merge_path_kernel : public meta_kernel
{
public:
    unsigned int tile_size;

    merge_path_kernel() : meta_kernel("merge_path")
    {
        tile_size = 4;
    }

    template<class InputIterator1, class InputIterator2,
             class OutputIterator1, class OutputIterator2,
             class Compare>
    void set_range(InputIterator1 first1,
                   InputIterator1 last1,
                   InputIterator2 first2,
                   InputIterator2 last2,
                   OutputIterator1 result_a,
                   OutputIterator2 result_b,
                   Compare comp)
    {
        m_a_count = iterator_range_size(first1, last1);
        m_a_count_arg = add_arg<uint_>("a_count");

        m_b_count = iterator_range_size(first2, last2);
        m_b_count_arg = add_arg<uint_>("b_count");

        *this <<
            "uint i = get_global_id(0);\n" <<
            "uint target = (i+1)*" << tile_size << ";\n" <<
            "uint start = max(convert_int(0),convert_int(target)-convert_int(b_count));\n" <<
            "uint end = min(target,a_count);\n" <<
            "uint a_index, b_index;\n" <<
            "while(start<end)\n" <<
            "{\n" <<
            "   a_index = (start + end)/2;\n" <<
            "   b_index = target - a_index - 1;\n" <<
            "   if(!(" << comp(first2[expr<uint_>("b_index")],
                              first1[expr<uint_>("a_index")]) << "))\n" <<
            "       start = a_index + 1;\n" <<
            "   else end = a_index;\n" <<
            "}\n" <<
            result_a[expr<uint_>("i")] << " = start;\n" <<
            result_b[expr<uint_>("i")] << " = target - start;\n";
    }

    template<class InputIterator1, class InputIterator2,
             class OutputIterator1, class OutputIterator2>
    void set_range(InputIterator1 first1,
                   InputIterator1 last1,
                   InputIterator2 first2,
                   InputIterator2 last2,
                   OutputIterator1 result_a,
                   OutputIterator2 result_b)
    {
        typedef typename std::iterator_traits<InputIterator1>::value_type value_type;
        ::boost::compute::less<value_type> less_than;
        set_range(first1, last1, first2, last2, result_a, result_b, less_than);
    }

    event exec(command_queue &queue)
    {
        if((m_a_count + m_b_count)/tile_size == 0) {
            return event();
        }

        set_arg(m_a_count_arg, uint_(m_a_count));
        set_arg(m_b_count_arg, uint_(m_b_count));

        return exec_1d(queue, 0, (m_a_count + m_b_count)/tile_size);
    }

private:
    size_t m_a_count;
    size_t m_a_count_arg;
    size_t m_b_count;
    size_t m_b_count_arg;
};

} //end detail namespace
} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_PATH_HPP

/* merge_path.hpp
u398EeUji7AuP/T9LcFuwrrlKcK6rdmtLJ7wXoemYSg71oP6EtHAejEVTjr2JdWUoR5OZmqaOhZr+JGhkd67EzNPUFgVxUMCLLFchCMLEOBBBZj5mDW2wEcQ9HdZf21DeOIB3E3Lnopbp108N3GsbhVwLy49ksGlCwKRSdaS5VmGQI96MQsAXjoUl4GM1Mn60Zx4OZp9uEYwazuYY6IryVPwARdZU1zM8zahBFVdPB+ENdGm8/IbifmMTgL/h9wDWg2bDHouiOWZ3KLTA5OyoenmkGomGw7MdiZqgOU96EswwSXlpwl/qikIZ+RIkSUWf8SV6g1FjcHPKf4j83xsPdf8pbMRkSvZfjk2fCJ/NSEnJ/LhEXNbI+en4EyA6esFLJfdgBYXOQUnrXMuYd2Wvy9wOZ9WZ2swnQJnUG3MXBJQU41uQujuqlTtgkcmxJm4uzPn/4Om3Grmg1Fk5XIBdYm++MCB5tHX0Q0wpoPjNkQUUS2vx0XU9ZmtmsZyLwIigED3h2N41pVtwANxMDzDW3iUBxaWtvdFD9Nppe398e+Fpe2YLo3lj4k8+GU6pqczRpn+1ahVMS1KGgZc34OdWZgOsRh9y9O0qqPkuTXBEqWDOu786kDn1+gmauy1k8yMpj7bYuJeb2ExtcCNLe95PcrGQjkKoGrf9d3gjbeM1DuJxxNAgB8cPWVA2I4RbKnC7/+KMsJh+Gf9KBra
*/