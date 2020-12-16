//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PREV_PERMUTATION_HPP
#define BOOST_COMPUTE_ALGORITHM_PREV_PERMUTATION_HPP

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
/// \brief Helper function for prev_permutation
///
/// To find rightmost element which is greater
/// than its next element
///
template<class InputIterator>
inline InputIterator prev_permutation_helper(InputIterator first,
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

    detail::meta_kernel k("prev_permutation");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << k.decl<const value_type>("next_value") << "="
      <<     first[k.expr<const int_>("i+1")] << ";\n"
      << "if(cur_value > next_value){\n"
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
/// \brief Helper function for prev_permutation
///
/// To find the largest element to the right of the element found above
/// that is smaller than it
///
template<class InputIterator, class ValueType>
inline InputIterator pp_floor(InputIterator first,
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

    detail::meta_kernel k("pp_floor");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    size_t value_arg = k.add_arg<value_type>(memory_object::private_memory, "value");
    atomic_max<int_> atomic_max_int;

    k << k.decl<const int_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("cur_value") << "="
      <<     first[k.var<const int_>("i")] << ";\n"
      << "if(cur_value >= " << first[k.expr<int_>("*index")]
      << "      && cur_value < value){\n"
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
/// Transforms the range [first, last) into the previous permutation from
/// the set of all permutations arranged in lexicographic order
/// \return Boolean value signifying if the first permutation was crossed
/// and the range was reset
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(1)
template<class InputIterator>
inline bool prev_permutation(InputIterator first,
                             InputIterator last,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == last) return false;

    InputIterator first_element =
        detail::prev_permutation_helper(first, last, queue);

    if(first_element == last)
    {
        reverse(first, last, queue);
        return false;
    }

    value_type first_value = first_element.read(queue);

    InputIterator ceiling_element =
        detail::pp_floor(first_element + 1, last, first_value, queue);

    value_type ceiling_value = ceiling_element.read(queue);

    first_element.write(ceiling_value, queue);
    ceiling_element.write(first_value, queue);

    reverse(first_element + 1, last, queue);

    return true;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PREV_PERMUTATION_HPP

/* prev_permutation.hpp
Kox+Oimrq+z/mB5O2f/rw+zb1M61nGcj63fwG/Qcn2sxHxDH3zNMHpmO4yJvbmQi+kj45VaBfa6BptHOVaa8J35Gx6IJ20b9qWmxe7ET16Uf3NTT/g6dFNbOY8Rvoui7duoTRv+k8V/sbGfNc4H4DSXXLSR8Ab7dxO0CPRvIliVfcgRt75RN1vfsdjuH68tXfyND3iinfBTeEx/pd4DONwTc92x++rI+l3zZfOYpn/xjaMGgF/+35ZTXWzoH632kQs86WRvUE6bv/FrB9jANdgiRW06HA2AbWAgz4EzYFq6E7eAZGv5s2AH+FGbBG2En1ffQGT6u4fSdq84RzFUueuRyCNIc9oPtYC7MgkNhPzgMDofDYTEcAUvhWDgf5sFFcBQ8C46GG+AYeK2GO/X/UU73i0ZZ3WP9Huxr3nelfNT4zqvx1/hr/DX+/pO/72b/f1nl/PKa2qO1//9f7J0LfFZjGMDP+bZsUdparTXFWrVakjVdVipT1BRZiiaX1CxNtaZdhDBELpW7XMIi5D73EA1FiFxSLiG3hCiV+/X/PXu+9/vO53xtI/1cztPv7b/3ft7LOd857+V5Z5j9/4juAdiAaYN5HfOe/3uuo/me09wj7u3WsB3MXtGeYn9cwq+R8HIEZvDbTfzbmT393cS+xHzD27KmPnjeRX/xf1TsuSZ+Zoj++UlcjjnrDH9dh6ZryPYLuZ4yCR/Q0X5g/KH4d7QCcWxZf8mHq0nbClsnP1rCXeC6H/kA8Uv6w1hBrvFb+Ie9/xdgxtTjuzDSmMAacZN6NjoCqEtdy646Asz3odSXOUOJOlG99bp2M2ysgPp3jA1caezOsYF2DYJ6AhL0PPCPCJOd7hwb0A4Vaa+yhu/o3n+Mf3uzJrdA7FOtY/h/VzN2wK0Tstb1iPTgmUe5Jo3E8D5kxieKxT/fOoTyab/SOBnb6keEqb0f+ct4qoRra84xcutPZaYesPPXw2L3OcYVpP/U8Vwi7T/OPc+R+4+ONfjrse79R8/bIpxzvexWWPkvWut3u3yzlyZf8M1Zw64ddW6nkTfEdWv4ceRv/yPk239l2tID+789N/6e9Gmj1md2K+d7UMYW+nzXscOIb6fNuGvQqKQNMRed6a0NDIzVlEp5p9923RufPJeRcdZzw6cWzrp1Q/3HIrbXmI/qotbfA34XdZ2U0UWtYxQdYArsBtvAETAVlsK2cCpMgzNgR7gAputYRSf4DOys65f2gq/DLkZnqz5H4A2av9HZquufEmEPuAfMgt1hL7gf7AOPgX1hOeyn19MfngOz4Wy150Rtc/2OGb84uA/frpjwsYrovnwfY9zGLCbWMm7RqB/EdOPv7H51H8NY3o90MVn7kS9mK27ToH9MYyYMH9dYomMbH8MFMDo7OMbROTvyOMdMl7GO6mzKh3Fd+7M/JoNvfTgCE2nsYyZuVZj5/L0SRhoHma5jIcv8bmZMBDNg2+MinQcEx0ayBxAGExwjIfyA4DjJFQMoHyZ0vGTZAOeYSbcDah832RoydtIRBsZPiuEVmAcx4WMpG/7EeMrEgYTFVGGWY9zGV6xBwTGWLMxxOtZSGTbe8iD27+EaPzHhYy/NcoLjL31yaENMqY7DXAGrMJd0x85YzFxvPMYTT/53soO+/zMLt6P+v4KQ7/+fdQ3AKapfqhBzIT4pbYLfbORu9P/NwI9vraKCk823jIbdW75leLdwn/c34VKMDqpssQ8M2X9caM6wzjXhe8q30Zk1+ZoxhsPEb3+xDzNhM833X2zY/O8p4t/cseeyv6bf1Jx9bMI55oH1bEBxmxnv1Ed1tITvY/ZtBvci6/e07oUbLeFaqN3WfGLNft8TyGt8HcY=
*/