//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENCV_OCL_HPP
#define BOOST_COMPUTE_INTEROP_OPENCV_OCL_HPP

#include <opencv2/ocl/ocl.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>

namespace boost {
namespace compute {

context opencv_ocl_get_context()
{
    void *ocl_context = cv::ocl::getoclContext();
    if(!ocl_context){
        return context();
    }

    return context(*(static_cast<cl_context *>(ocl_context)));
}

command_queue opencv_ocl_get_command_queue()
{
    void *ocl_queue = cv::ocl::getoclCommandQueue();
    if(!ocl_queue){
        return command_queue();
    }

    return command_queue(*(static_cast<cl_command_queue *>(ocl_queue)));
}

buffer opencv_ocl_get_buffer(const cv::ocl::oclMat &mat)
{
    return buffer(reinterpret_cast<cl_mem>(mat.data));
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENCV_OCL_HPP

/* ocl.hpp
ORBdyACq2pW4p0+oafVbpy77vScTncdsAb9YQ196OtHac5UBk060YIw3695nADMyB9ndCjPavvog0e9B1nDpEHCj7asPC0w9DVplDd9o4jSeXnqkQTd5Qg5VE2fKGsaPNjDgG3E5gdGmZ6uv0eljTazJ/z/bMeAN+eiOt+LAH+JDP0zXfXlFHNv+/ecaQozqM2pMziKjpZZkMY9/bTq/LMj73GG1zBGPLvGk2beZ1hdw7Z1xRuX5eJE7Sdf2E2pDrLO2NvpaGTcIM4epNBB/eqIqgFhNr6/wyNNfBmGSeZbnTyK4C7BvVrFHosJ3/CwoLLZyJNhm+orHM//WjzI7gkWeRbpyyKK5K2g3OY2TFlhyJgHgedCeQnS2POQ95TPiv2UIkCcoudE81YeRxKvcD5FVq+zN18dG4DhrhIO83sBR5mmtPti+tuJQH+S+mwwc6gKG4smamCZf33vAKAwllVL2/jMP0nFmW3e3tdCN3C8nHqJjKpdP0Cn/mE43+/y9hzboaAR3kodzDPxA1TMDuo2dOkZmjMbYPqKmy/JyYwNml4qhOurpVsvdH2lihpdUPiYepdPN/t5R6ILHRh7c3+xhGNxt6jPj0ex7zZQ5Fjgz9jZwGA/knHgMw1Ten8JtGbTO4zhtiX0Xvydo/3w8aLJvoP34SYz2CuaxOD/LfS/rs+elT2E0XkBlG/RjB0BX2QXdeyqjjz5Pf8Ho93CefudpTZx5Ln3g6YRZPWcx+Hr9BMNePCSi88g9E/RfPEOji8FRYrgcruiSouZ6gb/KTzS7wDDP3NR1oyonm6vnfZP77i+2q290r+ulpWPn1izQig3Zbb1+z41ssllLq/qn9JxvsIvR6ucmTElUWAMFfVJiN31krcoLySb9JPeRFU2TO/94k3pehAlJQkI3tXiUH9Mm8O523e7CC9MgJEFEwSPQE+taZq/OmGxjfIcqu+1GRRIk3dRaOvtKJPWCbHC/ij0WRDnZQNgBmZ/wnsJMEX09rNmjMYvbsghi8VPZel9PqNgjcZiGaeHz3HwS2QEfIcfCxizyyR/IRwq7Zt2ntT4GQeiRuXBcjaPEwsZVYhGDj+TZZGRjDiRaUebBZb0PqR/Fue+zsQQW+fHeZrTjlYkflTRrvPlXzA9nFqqGWLbmpg3bVa2sY7EgblFUZNZcVRYlDZusr2vlbMuL3S79glEl4Jrs9VfmKiNewzb5hlqutLqlm5dFtyB57WKjEGKhGzwmue1Gjp9XxtP+4ux8n3QnF+QCRLnOQw37vCh30yLuMuPpZqla17RTK+da3byM7DillTAznGk2qOcqeajOa+okSRJRB+eobLMkxiV8qC4fLeLCccO06qL9Ctod60Kw836o7jtY5GFS+AXrnlGi5u+8wZ+f5l1aTKFuXzzVyFl4WS2XWXQBLoqsG7G2WMm6gGITeIWXwb3cZXl+7bxKo6gUsOScv6rij0ah47oerfHZybTJzzV9vFw7p8pjz5JDfPIIsz/Sy1zXx8vxAy9lqVZ6ogxKEBbzVW8nSBy7dP2u5fVGt3NTbyeN6OYfuDQFes12EKNWLUPYJCnJeNW7bx9dJkM982wa+w/zO/+AP9enuetsldZQYGYI0/8IwyDgkIZCThiSJbrM36R6lNdmx+pZPUaYVfw1dq8FvXE3QN47jiG9b7MdxLxdUOPuHvS6WWzHIb2nZoxYpJcrHNZvmZRu1/WsRo7GqtwaWf8HtPrj1LZJyWBbcsMtcjlPKxx+K6q7LPIkv9/fSsZhuMFjRTW4g8xajR3vjDVxzfwJrTgjf0I7xsyf4HBZWwOn5U9wmJyrDYP8CRXmYhODOXRpPWFWmUMk7jfpDRuL33DMxTY=
*/