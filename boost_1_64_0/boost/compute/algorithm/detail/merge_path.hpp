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
/HnDMfTfe2m7kr7nvNDD6LuJ49vI43B23JQcj+f/iF4Frxnr9J7MWPlC2Wr+X3wr7E6Ohxw8R9di8btIvfs0eGW+Ojy/U3JG5nfu+NMCfiDeF4z1ZOq86qZZ+M+qYfa/W1y5Xx1yt/5gfqwzicvnZifP8wF+ewv7vwX+LQ15BS+nv7AfHPB9v9tRjOd+kH4k/XYzI+7IDwtOwM//RD0leML4fqg+AH1jy/8mjqjL1a2kd1GPi/ON1ZEPxvzGKvW4DuPYNfzlWnH3SHFkrXjVqh/yM3b1A/YCz9R/qp5cjie8Ae7Nxj/a1/wD8XhHsXv1uyVvyLf/kB4fqp454UN1sZNTeS6chl9ehg+okDd9hhf7XbbfM1dfuENdNhffxH66Vus3yMnrNzDk4PlWLqOfI1Lc1bDZe2VPwznP+f5Q761Zx44pcG2hOup0OG6DPAGPVUzP2+K9zZDzhXjsp/Bqb9P7Z+A66+7B41SeId+fGv/HPFlfQXI85PchPPwKfvTAwenna82/STyvlAdm+kPxfT0/5O+G279vqXvAfS2v4f3f5j/L+JPIa2PsgBPH4tf2eM/7c3ACfqb5Gvqc8G/5sS9r6X+Ffe2vbjtggN/DgFeHybcjzsT88/OdZ9/2Ec+HwReHJmM8j3VMv14dWb94hfcYWo9M7bmk07ybvb9AD7t6xLmIF3H+MHJZIS59D7/1R+tcrg8VH1ozkjzEv7EX2a8r5H3j8UTj2fWf4Gjr7Wm2Hn00I/CTleS9IOJaPC/82cCft63khz9WD/sjXi9+JzHWP4g+3An/Fci36uHG6HOP69jDutPgOXhrGZ5z+Do8bQO83Q7PBv8fnzN4LdMHq+62oBq/foI8Gx6uaMN/tSSf4/rN/Ag8sPM2OCdT75NHFtwnbvl9zqo/i5O/l0fDTw0Xqc8ldf4DIo547gXvy8ez9dGcxS9+Db74UF28lv2pv4/4lN3pYy2Wz+46Hy58C981WBwoxA/W+b/iX1ZXyvS3TsC35eWl5/fwG7GOGDP+u018/sA+H8hur0zGkFPErzj+kPdov2DdeJgueW3J7ORzjEn+mBP7sZBf/hOezDpqPHfHbDz/SfClPvyVLfzExeq1Q8TdQfIB+zj0EvzADfKb29QJop4f59PHdffjyR+lDyPYZ5M87Fo8ZPA/Mf6Ev4VvJl3A7k8SB34bn2Pf4fjZ8kj/16jEvI142OrHxKvfJ2M8/7Huu0TeG/4irp8qbi6FL26lRxncfD+cXklfz4X77tAPc6L3HJ6Bz/EO257LTuWdef/rx+LBDezH/jQd4vMMuNr6uy9V56OnfRPpnf63xhX8IR797HOsi/+rXZ6eX6T/cpL3XmcdSg8uxZOIM3012en68MqF5Fl9F/57L7z2Sh7+Oyd9riODd0nmeZ58v43vhGvrj+O/TtF/frJxfB4+l/02DsQ741/z/N75o/ziTPWO4+Hj4+Vhy+GgU/kH/rua/m4rVM+7gD3nk8814v1vBuK3+4sn6fHSqGvF+vbiUVvYBT0tVO+ZNV+/yzbX58iv8JstZerCp8P5c9hfKzttw9Nkfh/6M/4qH94O+4r5fwfn7xCnr4YHPV/Wd/F/0e8fx+eJ7wkvmR3XRf9jXDeZH66llwfoA9orP5kjflwAL8Ebla/jpc5Uz/gYD0vP97ysnjUNb4+vHEXfVu6Lz+p2/15+oFveIK9btK94O5Hf/Lp1v8vfwBvl0Uce543Gp8KZNRfxU/d5zy/jV27Bo8k3+qbgiSfyI0fDRePkV97H7Gkg948GsutM/276/YJb5C30uOtaeeDL5LSxP15XHOZvus+3X/LRyp0ZvIAX/4C/kce2fR7/6j5DsqybHPM=
*/