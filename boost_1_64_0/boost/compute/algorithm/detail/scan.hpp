//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP

#include <boost/compute/device.hpp>
#include <boost/compute/algorithm/detail/scan_on_cpu.hpp>
#include <boost/compute/algorithm/detail/scan_on_gpu.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator scan(InputIterator first,
                           InputIterator last,
                           OutputIterator result,
                           bool exclusive,
                           T init,
                           BinaryOperator op,
                           command_queue &queue)
{
    const device &device = queue.get_device();

    if(device.type() & device::cpu){
        return scan_on_cpu(first, last, result, exclusive, init, op, queue);
    }
    else {
        return scan_on_gpu(first, last, result, exclusive, init, op, queue);
    }
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP

/* scan.hpp
LlT8j+s6e3BI172dGn+16vkOjcufPc/I3+ZRxa9+1RSF++gnle8e1auQxn3zdP9C5/f0C4znsLdo/nCf7mfPuE3zejo+z46qv/Xt0rhT/XSVw0JdN6c71L/7izFPM+kCtc8P6DxUPbljno7vCj3fcZbRr5mq+YcD6q+to70u/n2N+jV37FM/TvPWO+9Xe6X7IFP1XoVpq1Ruaief+qbaL12n7lL7NcOh+7OaF2t3qR6vVj3fonGU+vnjame3ahzYrv7UXI3DN+q5zNs1H71wq86H696o80bnkVPztGqX5vxW98v0fNFVV+i+ra7by96r+duk1v14Wf2J3+i+Xel7SH/WfVmvnjtQP/rp6435x3s0vt36DfWvv3a62jP1u87RvHde1yPV190OpaNLx3u1zt8WpXtc1xk9r32P3rO3Rvdd1oRU7tt1nm9RP03zNtv1uX3rNL9des6lU783ar5H671feLHm79We71S/4Zw9GqdU6Lq8V9cH3Q+c8sHifsV+iPqbzJecN5n8q19+oEHjL32Pd1zXr81ar+0q7sP8mj/MvUv9y+f0HF/0DI1Ljc/dp37L4XnGc1LbblQ/8RrLK+3TND1fsUXj4+ln6Dnh6Okaz56meq3vN52n5zMO6LmlL2i7yvle9UeWrdA8youaD9H9tC2nGc973a/x85PK14W9up7ofsTshM6zj6i8dX1fqPvfj6sdXeDQ9S2veYjTdV2Zq/bp41N1H1Ltmdqtbfr71vOmalxs9Jdnx1XOP1O/donma3Wf59wZuh+m69vh0v2l0nPiz+t7eboe3dOu+1bbNQ/4ZT3/o/zN1+dXLNB4eJfa64LS1675Da2HtLI03ivT/SXdBz6s55efeFHzr+NqH6/V/VyX+gkLVL+eUvg+jZuU37O36bhqvu2cbXpOX+f9bSr/e8d0XVI//+CXVO436LxvVX/wPl1PNK7afpXu1+s5lO0mlZvmgXf/R+fvx5QO3W8+oPsyV2xQv1fpOfOA7iPq/uN23Rd88gz1w96renKrnsNXOa3R9xSu0LzVA+do/vlhjXv1vPWSBo2DImpX36nzXvc3Vs5QP+AtKtflGncOal5Dz1NM1XzEAe03fZPmaXVfbLf+fo3K73y9F+v8b6i9uk73my4zG/NTEY1fynSduEn1ol/9Oc0bTBtTe9arftov1J7P0Thd9yF36jp0ruYxtpaXxjd63nGKxgt/Ur9zpfq/DaSm2L9fr/N3WOfdBep3q327V/M4SzTuvU3jznu+p+uu5iEfV34fPaDy/K3a+VEdt7k6PrrOzFY+7uV6Ma3Y/r2gebTZaoc0H7ikUd+nvNDoZ9w/qvO2XON/fb9lp34v/I/GazM0vnqTrpu6Pq/U/deLdN1Zs1Pv/dd9x+1Xq11coucQNI+3Z7fG96dpPPNpjce0/76Hjev6dM3bPa3+9wL1Zxfq/s1B3Q/cslnH7ZtTVZ9U//S+n906fx/nufS3F8P7oeb5lhr9oulnqz+keebH1Q4+ofuu7der//2w5pd0v+lxzauuG1A91PkwJaTzQfOq42oHLlwyVeM1s9Y3Urv0bc0Xaj7+6bepHdN82S7N293Vf5r6sZqH0n2ndRpfT/+dnuPS/cL7r9XzK0rvulI7pX7xRvVDz92pccGfdd7N03n9QY376tRfe171Vd9HmqLnNrYyv/+B4vXkA3rPxZs0H695tHHdD7zoKo0/Nd+5c67mXaZpPHar6ov+vYv+wUP8xx6Nk+Z+0Pj+71T1N65SONNL99cf1jhY6W3fpnmcn6pfdabCcU/Rc/Wab+lW/17Xo0c3al7LrOvl03pO/wW1IwWV17DuW67VfEla7bHmN7YcOV3XI50=
*/