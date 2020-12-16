//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_BALLOT_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_BALLOT_HPP

#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/functional/detail/nvidia_ballot.hpp>
#include <boost/compute/functional/detail/nvidia_popcount.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Predicate>
inline size_t count_if_with_ballot(InputIterator first,
                                   InputIterator last,
                                   Predicate predicate,
                                   command_queue &queue)
{
    size_t count = iterator_range_size(first, last);
    size_t block_size = 32;
    size_t block_count = count / block_size;
    if(block_count * block_size != count){
        block_count++;
    }

    const ::boost::compute::context &context = queue.get_context();

    ::boost::compute::vector<uint_> counts(block_count, context);

    ::boost::compute::detail::nvidia_popcount<uint_> popc;
    ::boost::compute::detail::nvidia_ballot<uint_> ballot;

    meta_kernel k("count_if_with_ballot");
    k <<
        "const uint gid = get_global_id(0);\n" <<

        "bool value = false;\n" <<
        "if(gid < count)\n" <<
        "    value = " << predicate(first[k.var<const uint_>("gid")]) << ";\n" <<

        "uint bits = " << ballot(k.var<const uint_>("value")) << ";\n" <<

        "if(get_local_id(0) == 0)\n" <<
            counts.begin()[k.var<uint_>("get_group_id(0)") ]
                << " = " << popc(k.var<uint_>("bits")) << ";\n";

    k.add_set_arg<const uint_>("count", count);

    k.exec_1d(queue, 0, block_size * block_count, block_size);

    uint_ result;
    ::boost::compute::reduce(
        counts.begin(),
        counts.end(),
        &result,
        queue
    );
    return result;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_BALLOT_HPP

/* count_if_with_ballot.hpp
R/0mtNT4xIdxsHuprcNcM89aqx9x5prxmsbHShCH7yVHPoHD74dmT1214JNkB3b9Iv3wM1DXzIebbT68JF6wg7zkPjzhd6HxVaQWfw+oZZwzo3Guq23rVPuobf5C1NZ6OWpbvWVyv6kljjVlJ7y0UEs8rlWLn73UYsc4tcyDWZaX69WSN9vUEvcLIh6PwC/jP60Wf3n+kHefqkV/B/lF/nVVizwteq+P2sGP2bx92eKzMGpnL7WWvEKunlp4qB+1jdurZRyeH/BF3jOPZqllHndQ/LBjtVrG2WjrUKHNJ553zM+Y4o7fy9US7xVqiet7aokz6xZ2rbH8WKeWvGT+MO4ma3kuMW9+Ucs8JZ/od1gt8T+mFj7ilBfYVSJqd5e2fMtWSz4+qJZ8fEwt8dyglvmzRS16t9s8/Dxq9xWqJR7MT3jep5Z4LJI+8vU1W6/599+Zly0Uf+Z5M8WReL1veQxvzGvWS/SWtrx9RXFgvOUWx8ttHe2na1rmM/P+WYsvzyvmQcnEiD/2B+jtEvW7ppf04y95Qj7+zZ6f5CH9E9SP60U2D1YJh4+5Fr92pWLxyJ0tnHkzRC18k0fg+zU+clzDN3+nCB5WRuP17i154nKXcMYvIV6I342SJ/5j9Hwh39ZqHPSyT4SvO6N+1VoKJ//O0zXyl9o6k6nx6LdCOPn3fqRvTy/5z3x6RdfMn7WWb3UkR/yz1MLPL7aONLB1h+cEbSfdJz6DdB9eWO/R8138CR5Kst8hn1qJR/i9X3bQTrL141PLl+GWf/fLT/KGvML/1tLHePeqH34Ml170bBUOn/PM/3S19KfF7k1q8a+H5PHrgFr6N9G4zIPJ0sd8HRDhzZlH2LlI/fCf5zz3mZfMfz1nSpF3Ns+f6Gh21tZ98onnJ/yfYs/VBzUefl2h+/hr69KG6TZenK6xt6Y9X++WPPw+oXFpfyodK8t82yueGId1j3k21PJ7qlr683wj7w/ZvkLfVNOvJPML/pjn2E2+0G+JxiOvmwknfxarH3x+Zu8TLW0drWzr1UzhjLfM8or9BHZ0lx/0vyIhVoL83qBr5Jh/xLWynvf0f8vyaKnGIV5tbT9brmysJPOjlvoxj89XC39n2PzsrXGQh2fWlcttXn6g8Zg/h4UTt9Nsn5FQ7oQdvYepP36vtnxqJXniznjMs0vEF/b+bvspnkusK/BO/JMlh72TInuOlVR/9BzQeMTxIckR//6SA//D/GofHzsOP6V0jR/kJfx8bHzfKxy/WZeZT+m2P32dlueCrY9DJQ+PX8bHzmVdW2Lr9NVJsYrkW5rksbuJcK7bxcce1H+cyXOHfG9k6+ZY3ce+L2xc9i/4WSmya+X3xuOpwvG3hlrsf1Qt+blbdnBf72Hx9L/dnt/87hD+/2p5UUI486+X2VVR4xP/GRoHP/EPPEv2YU+yrvHrEfGInPLnRH/2j/DBuo9+9pvMQ9Zh9FdUS14wj7Ez2fbr8IaeLVH/USM0LrxPtf1vga1TCcbLq2q57mD7us5qyZ8JUbtzrfG0z/Zlf2pc+pU2Pu+I8MHD5Q/29rN1aLha5ukM43WcrolPn0iuh/ZfVciLtZovXJMnzDv2s/AxLylWlTzlfQ57Rtg++C5d0w/eWKer2XOmqs03npvk8zpdMz9yLC+xHx5+sLxm/SaPmL/Mi2PCyW/e99GzQTh8zbTn6npa9uu2H22h/vTbauOfGumbbvmcfIXkmc/gzMNu6sc4ibqPv+x/4TdbLde3CMcv5OHhR8mj/ytdE9ftUd7tb2N2b4/wDbxvw/N2xZfx9XflSrJO8lxDf1XxQT7fqH607N+R53kNX+xPiV9lyTFf2JfQ7+fSsWTWh8w=
*/