//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Performs left rotation such that element at n_first comes to the
/// beginning and the output is stored in range starting at result.
///
/// Space complexity: \Omega(1)
///
/// \see rotate()
template<class InputIterator, class OutputIterator>
inline void rotate_copy(InputIterator first,
                        InputIterator n_first,
                        InputIterator last,
                        OutputIterator result,
                        command_queue &queue = system::default_queue())
{
    size_t count = detail::iterator_range_size(first, n_first);
    size_t count2 = detail::iterator_range_size(n_first, last);

    ::boost::compute::copy(first+count, last, result, queue);
    ::boost::compute::copy(first, first+count, result+count2, queue);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

/* rotate_copy.hpp
ofXP3fWx533HblfwQWRn+/UIGtl5/vxBS5fMX29uy/rnjKmt/WKF3boG+/UL+VSuO3/+LjBnw/xIQ+OtW3z+0led9mcQXED6C5qOHPf11uObl9+x4aD57j6w/RLSD24X+vjH98Ilhz88eYe3Tu7/qhDzyM5pg09dHDzqh4cOO3fKOm8P+u1nu/Uda289xd03ULvsF7r024cXX75w4QslLyyY6xXi0xHy+tDt3lr37SdO+Mi5vOS2b9ZvahLifdKfc/agZ3OfeCJS/fqBt644q3SxEA+TvmeC9/oHz25aNOz+q1xHVay7WfKdVa3gvst9+hDu15sJgN9RybCbzxrsB67g9RoLeX2G3dqMt38v5vUZvDYjbV1GNdZjTO3BuoxlSMd2z4gMazLmp63JKBOulDUZg8Wq58E+XarevykoKCgoKCgoKPy/0Rv7/7WG9URcC67xWF+Oy+/wSBshZerZXUFBQUFBQUFBQUFBQUHhz6I3/P/1SCCs+SOJ6Frw/++t+f7FtJ9A6nmBfY39Anm+v8xuvl+fE9UQbm3Pvq5Anv8/gOdeqxtobt/cp3Ap5+tKy3doSr6JSMacgT7wK5BJvFGT3Q7Dp2CFw25u3G4u3e4c/tWfA7fzZVj3Rnl93o6Vh8S8Py1/0RuZ/ejKOWetvs+CjU+Eje+Ana+E3Zx/7/s42Pgg2PoO/Ej1OVS7YvYG3ueG3brfUy+XXPfWRCE6RlD9z1h2+o1bxAq9wwoOf7/++Bzj/EPu19zf56adf1jG61fcYEN/KOu7MuhXsv664E4bX4Fyt0s4fyvO6jNQCz3rfo5PQ7y41p3fQDXStfoOTIUcDlmQwYegEbpWP4IFEB3pt+B6+ZawBX9n8ik4PItfwYOIt9St3k8qKCgoKCgoKCj889Eb43+54x7kAH8ossY+AIOEy63DtkM+k+vsfT7kGvD5dd0faNOCQvTa+wFPjYDdpVQv03MEwcv1tQOkqh7lOYPG6VxUH202GIpH/XqgDXbVuR3QcYhQJK77IwFNriPYxr2jg+MhlWEYSY0UTtLdYV2pG9P88faIAPpBdx3Busi5WIwlveV1Sb24FjtICybT9DpMPTPNCrwbkLb+4BFiGWQUyrNlTfa1BxXC7Ya6kLbv4rDYjuu1uA47cZ3tZP0GMOzCddMuet+wLdffvDze/x929mceiPRHn5lef9S8WjzOLSxExnrsS/VoxF+Pwns6kD+Ff0LOjVSGDPVFujuZcSsp3IRwE4W/obgoJ67XIQ2JVn8onIw3CXrtpPcShx1ibwoXiiroD64XwCrnSZDuFMTtJN3+HHaIYXNluIzsLKG42LMyosV1GAodar82ipMHnW1lPXN+XyHHYjEebVyCa7/D0M8geWjfr8GjwWMgYyFbQb7AtVpwAWQcJJ/7weDM3UD2A+SX794had/QpuaarQRfW0L5C3ltjOhBf0nvF0Z/KSF9a3nHuYdSfkJsUJ/sP83cfy7JF4QBkALL+7LyldR/Wuw70Cbjx7fU4L/WUGSox3xfVtBt+cuOHcJlHbzSLOuWRvnX77o2StjUk7VOmm3qpNmmTpq76iTlHqotFITTIKXMg+rBc23voaDG91AV9y+HQNryaz0kv8EjswQg+1mOMNLpR+FGFPAyCuvGvWTXR+meeJh08xDelsr3GIX3FMNQ307R1TdXgMeDt4Z0epLtUEhtsTt9xx97o8DFDN/xyMcNvoZtdIqcHvXfyrOoXVLa6vO5ZvshZ+TNbcX9Mb1+jDZL768p/bPaKQgDuX/iIsFj3z/ROKv2T14nhrrpWR/ti/JsY/bHcRQeZ4ZrV6mD9PI225XXpi+O5fI29hGEHyFVkE/593DCWSk=
*/