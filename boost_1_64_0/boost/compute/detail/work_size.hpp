//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_WORK_SIZE_HPP
#define BOOST_COMPUTE_DETAIL_WORK_SIZE_HPP

#include <cmath>

namespace boost {
namespace compute {
namespace detail {

// Given a total number of values (count), a number of values to
// process per thread (vtp), and a number of threads to execute per
// block (tpb), this function returns the global work size to be
// passed to clEnqueueNDRangeKernel() for a 1D algorithm.
inline size_t calculate_work_size(size_t count, size_t vpt, size_t tpb)
{
    size_t work_size = static_cast<size_t>(std::ceil(float(count) / vpt));
    if(work_size % tpb != 0){
        work_size += tpb - work_size % tpb;
    }
    return work_size;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_WORK_SIZE_HPP

/* work_size.hpp
U+HPYrh1pqK14fzG1nE8n5iZFFpXUxbfLVizyftuX165Cl3eyB6NHeHl6vtaP3/NXt9m5zvzU3Isb8nGrlGmNZVCRizqVY+1lNS32voFWWl3+hhlzdGeXek0Kd7QaVo8y7+3kbm5/sjNE3Mnit/s63xtXcEGEnTkd4FsD33NmGJezZbsjZL+WvzcpMrf+l1tHdQcIXmu+t8l20/Yyh3Gp5mueYO95pxTVqFN3HVPntzKy40hNfKrg8Sh7dnKPnznaX2+wDVjXGPf09IP2Je8OJPWttfZxY/Z3gN8eiAub5RPnxF61kO75I/psvh0GPs9kg/8iaxe1RbrOWX213C59m1Ohq+wT+dD9da5P9FYYY3fmsbrbOFH/GxPY4BzhR3o2X5i4ZtkZb/r6Eh9+AsZvit+KCvbwg+VXfwXf9g3zu7Yz8/i9qehu3fYcpz9aWNqupzlbce+VH7dWGsRylJ/eUc6j4t7np8Lho3zWWsQ9jfKW9tIWp9ZqG2Zq9n+lsZsfcv+Up2tVdY+xJbF7Ht3ay670+/vyMPvD1NvsM55jvjpOZbi6exgK3I/s4KMxHzlJo6g52q/lXWJVdbKk/LHXL2cULtLz6n7WzLczfzPOmZhpdhXqy9T+Z9ctnQqvbCT1EJjSn6y9UBrX4utYfOZhHWacCf5NDsrnkGW1tzKD8tzt/SprMCYH9w7iv3K6Rap0z3+5yFbpOMa+U4ffR9i7OkXh9STXxnXbr7g2rCaDWpr7k19VW+C3hOHuocv5wfI5TbyNd6WIuMjGSbayFWuVFxtren0UdZetHN0hbVbMchzUpn32YI8JFxLb56dWaCchDEgJY8vnsk+ta1wOb98RnzvFoc8fxWxjfJbbJM+kv8Yoz62sp49fWit4wDyHW28G+H7/Ljz2sLm0gdp12ztf7+SzSg/BzrMnKDPngsuyxnCxez0Jj5lH+HEe+r51Jg0VjnW89KnsnP6SvLh3Nn03mT8vd6nOXz4e7ZFD4lf0cfjMTHOGEHHxa3Vd65Y9H0ZnlFt1LdgC/ZuXSX8ORmfqE+ekyiPo6tt6Pf5iiAnHy1trW0jjX/3mhOE8vqFrh9U7jVsxNw6eTF72UEOGxinl/IFuVRy67HGAn2X85fpL1jHN85lJ9qXu0Q7m2NyY+27XGxutb+huW3WMz9RXjsHzEGeJ8/NtPWHPl9nG7ezsznsiG8HdF5qrDCu0PeL5p/qKSgn9QdtekrupL7Cz9jyK/Sl/tLx1jbYRKFEtw8YI/rEbvGzHBkf3maTx46xbqJ9i+jrCfHPMzzBXqP5tzHzMrFVHE7w/eBRNiPXL30jnpFt4TxjDRvO1dKl3wEGWvWh17qIvfFKO7Hp07XtIPb6HP8S6/K3kekB+uN9gdJ27PRTc7N/8YM/iqH/1LbfiMOL9PV09f1K/Z7dYH+ez2fHHVXiLF/3HFXgN+osmyyLP4mN5Vb70q/7g9/yG9cXthdL7mbn+haa30TqTCboZ38yOVjMXO7zdXrYh00fKVb8mL4vkxtE7GZvurw9Jjd1jT38EieTxcXaeInc82BxpE89m+nv0frx9kj6m0T/o10jLorL6evYiXcDIrnSQm0JDzJ37BETP+Lrno0reYa3kBlHtsrTnsT8uDLEuMv4xfn097JxoUU/fiLX29099iIr6luDdZjsJuLVxeyjt0K5cqZ6clFusGlMefQhn0lfRN58Ir3eeJYfbzwI9YHvzNfuux27Qb0viUG/0/Yb2d9nbH423xe7c9aWCtfp95vKGiQX+WDJOk8pR+b6lp2vPnVnZsfpNS43JpsrzTP+49y++uC6cC/5hWfMEwfJR2exn+Q4duA8mSZWOb+p6w/jz19olxg=
*/