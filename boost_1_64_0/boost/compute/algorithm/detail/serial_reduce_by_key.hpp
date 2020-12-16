//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_BY_KEY_HPP

#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
inline size_t serial_reduce_by_key(InputKeyIterator keys_first,
                                   InputKeyIterator keys_last,
                                   InputValueIterator values_first,
                                   OutputKeyIterator keys_result,
                                   OutputValueIterator values_result,
                                   BinaryFunction function,
                                   BinaryPredicate predicate,
                                   command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputValueIterator>::value_type value_type;
    typedef typename
        std::iterator_traits<InputKeyIterator>::value_type key_type;
    typedef typename
        ::boost::compute::result_of<BinaryFunction(value_type, value_type)>::type result_type;

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(keys_first, keys_last);
    if(count < 1){
        return count;
    }

    meta_kernel k("serial_reduce_by_key");
    size_t count_arg = k.add_arg<uint_>("count");
    size_t result_size_arg = k.add_arg<uint_ *>(memory_object::global_memory,
                                                "result_size");

    k <<
        k.decl<result_type>("result") <<
            " = " << values_first[0] << ";\n" <<
        k.decl<key_type>("previous_key") << " = " << keys_first[0] << ";\n" <<
        k.decl<result_type>("value") << ";\n" <<
        k.decl<key_type>("key") << ";\n" <<

        k.decl<uint_>("size") << " = 1;\n" <<

        keys_result[0] << " = previous_key;\n" <<
        values_result[0] << " = result;\n" <<

        "for(ulong i = 1; i < count; i++) {\n" <<
        "    value = " << values_first[k.var<uint_>("i")] << ";\n" <<
        "    key = " << keys_first[k.var<uint_>("i")] << ";\n" <<
        "    if (" << predicate(k.var<key_type>("previous_key"),
                                k.var<key_type>("key")) << ") {\n" <<

        "        result = " << function(k.var<result_type>("result"),
                                        k.var<result_type>("value")) << ";\n" <<
        "    }\n " <<
        "    else { \n" <<
                 keys_result[k.var<uint_>("size - 1")] << " = previous_key;\n" <<
                 values_result[k.var<uint_>("size - 1")] << " = result;\n" <<
        "        result = value;\n" <<
        "        size++;\n" <<
        "    } \n" <<
        "    previous_key = key;\n" <<
        "}\n" <<
        keys_result[k.var<uint_>("size - 1")] << " = previous_key;\n" <<
        values_result[k.var<uint_>("size - 1")] << " = result;\n" <<
        "*result_size = size;";

    kernel kernel = k.compile(context);

    scalar<uint_> result_size(context);
    kernel.set_arg(result_size_arg, result_size.get_buffer());
    kernel.set_arg(count_arg, static_cast<uint_>(count));

    queue.enqueue_task(kernel);

    return static_cast<size_t>(result_size.read(queue));
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_BY_KEY_HPP

/* serial_reduce_by_key.hpp
vGXfU/bgtb5X9K644zMvGZ6/FB/0vcLD2Cv9Nf8L+lBqFN2T/vcw/rUcPpgR/D6pSp6nBzWLd4tCnPcFffvTDsHvf8AzM/jvI/DIeeLFPvzgGvypO/6c5T3j5e9LguusuiD4/fYj8Aj6WlGV95ksnrbSl/40H1fRE06ND+53sPyUCA9WwONXwEn3w1VZ/Elcy2Y/Fb+pm8yhOx0lXiZHB++1iv4tv9ddCUf8TFcP+ffTwe/Th9KbBtI9XWdzhnl+nT6+GO/s48zsq9TLh4kLt+oXmE2ndP8lximdLrD+lAh8K/j96An8oEgd1O+ni1O157OLvd73llj1ZnZymPuskkfuge9uwQeekL/ehmeOjw/GoRsc1F8cHmpcB9EdHokL3n+cM9kfp9OdQb8qUVeolZ+PCq6/JIMuuzAm+D9drniA+T5OnX4PXjc7+Lval8VD4zKur7zXGz5RH61+B688A578Fz+cFjx36bf8/Ai6BtzfvEyeh4dT4PHKD8zzBvXCh9WDD6jbnm1c6HTT54iHb7aHD5z1vgQuEK/X4o2lJXF0PPm4W1Twf/XRRRc5sx+ejzxK/hoc/HxzJ3WHbfTNH32vozr+D+LO2/w7Hz/Bz5IPwc/vDr4fM0veq8B3PW9zrutM9/yj5KVv6NUvqHM9y99a4Ndcuvftxk1+SB2BrybiX2nsfDx7LpOX2we/7w9fFMML6483nn8E91lV4vluY+fn4cVn06n2421Hmter4PPYDsF1v5XHO9OF6sSrF6OD512pXrAOX9oX/HzFDPm8h/y2iX++LT4dg3eIZ0kp8vAl8MRb8YGdi79toU7/e6w+LPXp99nbLXiweVg0hn6MV66Ay0p/C8apsK/njIDDX8N7YoLflz4Nn7xkfugnLVe7bz5cNFYc68qf2W3ylcHft8lPs7rIty/CjXhcqeevmEC3eD2sZ4hD3ToE911p/EKeXSy+nAUXzWG3RfL/neKT/petM+SLU/G2Tfjp6fJrJv5Jv4mchucM8TwHs6OL6FTi9hSfVS973mzfa+WPw4PfbxdnVz6Lt2eGdVVxpbv5O0n9nI6R9kxwndnD4bF6OHspnPYeHt4UHfx+qX6pJvao/lvzMH2/k7zCHlu2q3t8Qu85DA6UP9O207V8v7xUHN0h7h4CR1fCC3/z10nBc6TCJVu7yuM/6Ou4JJqOoF73J109Bz99Pvh5wzBxuSt/0jdVfIc+kYTg7zLE39weEXivuPmlfqj/eN/V4lgUXXKu+D4WrloDv1XhWW/qC/kqQl6KgIeD+6bs1gcRTYeYrs6w1HPOoG/cCUe7T9k50YE9Xq6v6ZDguSrotKM/pud/Dm/hcYtupgMuoId/igeJQ3W/i2+l/AIOLt8nrrrfoGV45XWuN1CepbvXrpIPTgzep2ayuFIdow/MOKfzt/7mZztciY+W14grh+oHzGYfgzzXs/gbfTPnS/GPXyarB/enI9TvxWvu8h7idMwi+eYuceZq8/jv4Pmb8+jWoX+eLC+vML5PxgXzqx4/cq86FVxR8E3w/xz+VjafPajrjLs1Vj0/Jvhczr7UabO+EB9+xo8X0qv6wfn8I3eo+sALwf8zXxFP1+kzGEi/El/yH8Q7/uDvP8OJ9+mz6aIf+DV+xV5n98X/lvLnW+CgG/Awen0LXNecr9/hGHWLGvO9Fh7oBH+rx9aPgOvOoDcb1zh9dC0vi2sp6hQ79CvS++tOMG505jJ5IOtYfBLuS+osH5wJf3wtn97MbmfSzTbpx7vCfNKtluxjT+LOWv2TdV8Ev08cHfI9fOAp/dFD9CWrb0ROMa7P0TcGwil00rQb9QMn4t9n4UW3B58t8nZmhvl7DW6tVL8=
*/