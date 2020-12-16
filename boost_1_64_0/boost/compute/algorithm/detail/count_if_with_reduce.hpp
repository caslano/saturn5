//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_REDUCE_HPP

#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Predicate, class Arg>
struct invoked_countable_predicate
{
    invoked_countable_predicate(Predicate p, Arg a)
        : predicate(p), arg(a)
    {
    }

    Predicate predicate;
    Arg arg;
};

template<class Predicate, class Arg>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_countable_predicate<Predicate, Arg> &expr)
{
    return kernel << "(" << expr.predicate(expr.arg) << " ? 1 : 0)";
}

// the countable_predicate wraps Predicate and converts its result from
// bool to ulong so that it can be used with reduce()
template<class Predicate>
struct countable_predicate
{
    typedef ulong_ result_type;

    countable_predicate(Predicate predicate)
        : m_predicate(predicate)
    {
    }

    template<class Arg>
    invoked_countable_predicate<Predicate, Arg> operator()(const Arg &arg) const
    {
        return invoked_countable_predicate<Predicate, Arg>(m_predicate, arg);
    }

    Predicate m_predicate;
};

// counts the number of elements matching predicate using reduce()
template<class InputIterator, class Predicate>
inline size_t count_if_with_reduce(InputIterator first,
                                   InputIterator last,
                                   Predicate predicate,
                                   command_queue &queue)
{
    countable_predicate<Predicate> reduce_predicate(predicate);

    ulong_ count = 0;
    ::boost::compute::reduce(
        ::boost::compute::make_transform_iterator(first, reduce_predicate),
        ::boost::compute::make_transform_iterator(last, reduce_predicate),
        &count,
        ::boost::compute::plus<ulong_>(),
        queue
    );

    return static_cast<size_t>(count);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_REDUCE_HPP

/* count_if_with_reduce.hpp
yI81d8lO+v9seWR8TN4peew9z9Yr3guxj+cF8+I2+cX4D9jz/vL4WGmu+Xt6+P2Wvfc+ZXWUb20e4D/tDMWBfrxXwP/TusaeX+05d1wt9pxq+fiq+pP3e2xffI1a8iFD4xGfuZbXTSWPXp4HyD8UjfvcafY8f9j2S9xH31CLC+/v8HencPg51fa3mZanX0uOln0A9upvHyQSl9PtfShRODz3ia5XMp/Jy6Nqie9htdjD8wH9XSwvS9hz9hv1Z7wf1OL/VHs+sv+A9+qyD/lL1ILfqf0R83WKrtH7hM3/+WrhYZJw9NwiveTT87Kfeb5S9/GP9zd4pH7Eun2VcHhmXSCvt6oljku4j37Lr1mWz6OlHz+32/gTS8TaoXeFPZd+s/zgfZb+zFOuL7J1jHWdfjXkL/w8Kznilm/75LXGSxnlL3kbpxa8ufrDN+91jFccL963mB/sm+CJegV59oI9d8eLT/xi/8/6UzPCK5SyeIw0f1Tvief6U8uzK+nH/lb24J89j1cU2DpE/YB8uMnyh3mGP1OFMw9/lxz9iRP+HI36P/y47jP/d9l730CNT/x438Yf3ufw9x17v/xE1/DI7+uSHw1sXaeeQJxutLrHl9H9M49Eel670/pR50F/DfGI329ZnmAX7Y/SQ8s8Jz6st/jHOg5/1Bvhl7ogefex7IXfXzUu98dF/fc11bjk483CmV/sY+iXp3Gx513tl+H5Td1n3k60+G1QS143kj1c8/4C/22130BPN+H0Zz9N3vC+RTvO9l3ry8hO+f2WPd9fVH/aI7omr7dHdiWfK3niUqtk9Hxi3YePVzUu+teoBafOBA8p6kfedFBL3OaqRX6TrQu32nrc1PZx2VaX6hX5N+xz47NQLXlSOjHygyJunPp1trizLsPbo7bfuFp2Icf7Gnx/D2/YY+/bK6wObfue2X/omniRX9wvIzn6rbHn6C7JMc95P8Ze5hl5+rRa8vB34408ZJwbbR290a6fj4/VJI68p5L/s6x+1Ml43ig+aMcJJw//0DXtGbYPqiuemFfdjG/yA75VVzgdPfiLXfBJXlAXIJ72vjiwvXD4pyUv8kz/UbtfvN+fIZy84L2UdaK/1WWX2z7/XOmBn2q2T7vd1oH2XLOuqx9yzG/47xHh11AnQA/v48T5TuP7R8mjN0vyXGtfkUC+bpI8/r4qHrGjQjSfBlNfx0/qisSF+jm83WX5/KXsY54yL+H7HasPUZ9gHu+3uiDrGnHormvizzpAPlh+1qLuR3ypfzLearXYz7yF7xH2/niz7dt4vnCN39g7xJ538y2utt4enCd59CsO8fDPPGDcptJHPJHDP94HiGO67ZPA4dXanRN0H75HG39vmFw1q4/MUX2B8ebZPLD3jPk8r7Ajw+rmnYr318bnKtM7X/L4zXOL+Uj9DbsaCYdX/T2URPyFB9bXe3UfvRWM/9rG3+kRvmaYPV83l4nWL+YDerpIDn+oixCneyzfW0frVr2/2X62PfNdei3++3h+Y8f5Nr95n4RX6zeKfRB6mtv72AclYwnE6Tnh+Ms5Cvepy6F3PS11DfNzsHggv4eaf9nyi37MR9YZ6hPwWdnmb0fbf7xk+yXqU+TXInvfZn3Bf/ax2MlzhXlAi5+zbXzOrdCrek4J+HvU6ou3yl7an42vkbKPfOD5gVxxnscUf/rfbOM+ofHg61Gd2zGPyyfFSrMv5L0HPyvJfvK/jVriTN0Nvm+xfdh4jUteMc/RP832O4tN72Lbh5Dv4Idt3aIOij/vWj35C9lDmy15+KxicftOLbwzLnlzne1vqGNiP+sk+fqzcObV5/beSf0QPX0kh13bLN+o5+Ev6xT8WP8m+IU=
*/