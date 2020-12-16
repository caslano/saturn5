//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NEXT_PERMUTATION_HPP
#define BOOST_COMPUTE_ALGORITHM_NEXT_PERMUTATION_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Helper function for next_permutation
///
/// To find rightmost element which is smaller
/// than its next element
///
template<class InputIterator>
inline InputIterator next_permutation_helper(InputIterator first,
                                             InputIterator last,
                                             command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0 || count == 1){
        return last;
    }
    count = count - 1;
    const context &context = queue.get_context();

    detail::meta_kernel k("next_permutation");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << k.decl<const value_type>("next_value") << "="
      <<     first[k.expr<const int_>("i+1")] << ";\n"
      << "if(cur_value < next_value){\n"
      << "    " << atomic_max_int(k.var<int_ *>("index"), k.var<int_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<int_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    index.write(static_cast<int_>(-1), queue);

    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    int result = static_cast<int>(index.read(queue));
    if(result == -1) return last;
    else return first + result;
}

///
/// \brief Helper function for next_permutation
///
/// To find the smallest element to the right of the element found above
/// that is greater than it
///
template<class InputIterator, class ValueType>
inline InputIterator np_ceiling(InputIterator first,
                                InputIterator last,
                                ValueType value,
                                command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return last;
    }
    const context &context = queue.get_context();

    detail::meta_kernel k("np_ceiling");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    size_t value_arg = k.add_arg<value_type>(memory_object::private_memory, "value");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << "if(cur_value <= " << first[k.expr<int_>("*index")]
      << "      && cur_value > value){\n"
      << "    " << atomic_max_int(k.var<int_ *>("index"), k.var<int_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<int_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    index.write(static_cast<int_>(0), queue);

    kernel.set_arg(value_arg, value);

    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    int result = static_cast<int>(index.read(queue));
    return first + result;
}

} // end detail namespace

///
/// \brief Permutation generating algorithm
///
/// Transforms the range [first, last) into the next permutation from the
/// set of all permutations arranged in lexicographic order
/// \return Boolean value signifying if the last permutation was crossed
/// and the range was reset
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(1)
template<class InputIterator>
inline bool next_permutation(InputIterator first,
                             InputIterator last,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == last) return false;

    InputIterator first_element =
        detail::next_permutation_helper(first, last, queue);

    if(first_element == last)
    {
        reverse(first, last, queue);
        return false;
    }

    value_type first_value = first_element.read(queue);

    InputIterator ceiling_element =
        detail::np_ceiling(first_element + 1, last, first_value, queue);

    value_type ceiling_value = ceiling_element.read(queue);

    first_element.write(ceiling_value, queue);
    ceiling_element.write(first_value, queue);

    reverse(first_element + 1, last, queue);

    return true;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NEXT_PERMUTATION_HPP

/* next_permutation.hpp
8kv8sLG2TvcbvKzrhaeCa4Yi6ZM8PEp/jDTWNFx707d+KPb7kevzRJqXNU5bs9fgTLHfa20kX3bbBC5dY+bGMyTM3cgnJlDPk1t0SsYRj3f9lD8vxu+LTihIKEClfes4ec5J1TAZhHknEKYTzzXNo8XvaI3tQL1eUGTmW7E/p/bTkr/fehf/23XEnyxy8zNGP+374Q/uLNp1xbzLb7v/ruP+P3XE54XI0+d6RHZSnkNZvzLH89yrf39jMV7079Mw7+jfZ2FUn6K+q5X3z/g59Sl2VdnAbrAT7A4PwgNefX+l70wLRc4aWVx9l91Hw+fA0TAXFsDBsAIOgT+FI+BjsBS+CefA9+AE+Bc4ESboGavJcCpMg+XwODgPToXzYQWsgGfBSngeHAUvgqPh7XAsvBeOgw/A4+Ej8DT4GJwNn4AnwKfgTNiEMp0Ee8AimAMXwVGwCpbCxfAMuASuh9VwA6yFj8Ll8A9wBfwj/AH8DK6GX8MzYaDiz4Kx8IcwAa7h/yT4I5gKz4Zt4TkwC66F3eC58Dh4HhwAz4dD4Do4El4AR8EL4Th4EZwIfwwL4U/gSfASOB9eCtfAy+BaeDk8H14BL4JXwh/DDfAaeDW8Hl4Db4bXwq1wE9wON6vs9w3wd/BG+Bq8Cb4Fb4Wfw/ugh/F8P4yDD8AmcBtsAe+GafAemA5vh+3gVtgZ3gG7wofhBPgInAZ/CVfBHfAH8FfwHPg4vAk+AW+BT8KtcBd8Bz4Do6Ll7GR7r8VMs9eCsfft9lrkBYym1wxTGLbnpavuVekBfbAnjIa9YVPYBwbTKdF0Wruk00/TGajpDIIJcAhMg0M1nULz7My1NJ1YOFbTydN0xmg6YzWdfJgCx8G2cDzsASfY+dNnUfLikr+phEuCM2BHOBN2hifC3vAkTSc3+CwI4iQdpyzzV1r/32j9/wPGyl4Au3x+jZ/rUr7VXKcFPAumwh9q/VwE28GzNT8Xwhxx1z0K5lmJMmi6TeCpmu4p2l6naTlna32thK1hOewA58PusBL2hQvhBLgITtXwWg/6DEPZXeohSq8Tq+nGwS4wXuO/b9ba+kyCSZf+Wfd70aoL/3vYT/v1UO3Xo7RfT9J+PUP79Wzt14vgm3ApfAuuCpHxfxuuh+/ATfBdeDvcB++Ef4Tb4Hvwl/BP8An4Z/gbuB++AD+Er8CP4Buaz33wIPwAfgK/hu+bvQO6BtV1b2HY3oEW2s7JsD1MgbmwJRwKU+EK2AqugmnwHNgangfT4WWwDbwSZsAtsC28BbaDW2F7eBfsqHtKMuGvYAf4lLqvOQKZ+0Z9xUdfnv7byNJ/H/UVP/IOuooxUe8mWBmY/phJmDLMaszlmG2Y3Zh9mKh9jfL0jb/GX+Ov8df4a/w1/hp/jb/GX+Ov8df4+37+vhv5fz39/yjo/r85RP7/a5UfXaFyGksDTA4o57Blz/OnzJycP33UjPyxxfPLa51n/yWJTEAw/Hi+0cQZveG3Drb18ZEkv2Xmm+xr4pcR1M+rYScTOtNVR+Dz4p+o9mDaPpG33I7/gx7SoFyJaYOtVNxWY9+OuQ03vsTiau8DuF118QVMQ8+/0zMIjZ3yYF8m31xHa13u0e9P6VqXIgtOwMwhkeoy0KgD+wflEJPl23X1shDdixo33VHnWoe2n5brtiPQ78a1yL9ey3GuYqnuTXDq7m+rZUrBtKRMee5lqgn2jzzn2ZAavq34JdV917d1v4ufX9otoCuohGveEWjLKH9iNC/aj6Sd8pxnRaqc6QpHO1VH1W+n1GTcI5XJtJNr2TReuunnHtPP8Qtrozsb0EaRyqJ9znG2ZEF0/bK0IeB697LULikePUXa3O5PlSE=
*/