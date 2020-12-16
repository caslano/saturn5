//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_POINT_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_POINT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Partition point algorithm
///
/// Finds the end of true values in the partitioned range [first, last)
/// \return Iterator pointing to end of true values
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param predicate Unary predicate to be applied on each element
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(1)
///
/// \see partition() and stable_partition()
///
template<class InputIterator, class UnaryPredicate>
inline InputIterator partition_point(InputIterator first,
                                     InputIterator last,
                                     UnaryPredicate predicate,
                                     command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::binary_find(first, last, not1(predicate), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_POINT_HPP

/* partition_point.hpp
nWjidDZzc0uJs4pnihi5xifEibNqHfvwBxKGFIN74UQ3/FraZTUT6tWET4yemBhL+ULmC5lzO2q4fYS7LBDOmxaY55MTohO6yYRPWGc+7X1obeSa2a5zewpsIv69nLrkGrT/mXcmdpuZuZU8YNc86P4o6sK0Y47uQ/s03vRHM+d+nET/kfysCbQXGe3X14pQNtpNw2ZEvG89Lv6tD7EHLNPeA+bMu2PezW2qcs4M2ubKr5LoA31D9QQvLl9WuqjyjPIyFmXlAY1sMgj1Xq5zqMm7xk01a4CYnID9Pm88/77n8dS7n0w0cYrNvPt0P3nfFzIXLTFnlXSV9C73PuxJCPG3581d4v8Hz4VIa6eq3pwScTvFW8F72ifwCXsfK2N9iVzzOLPuGidxunuSxJ8vLeLflt2Jm1SPj+1WhSSlY25UnQj9JY3zvdd42ofMu6VmDk8R/3967vV0Ub1FWnbe0nXhvxLrPFt/gK7zrJB9wX+XsORH7KFxd4TFq5y/OEQHwwEJ96iVJHY7XgvrJTNGr2zAe8hmVmIAPLMRHyYxnw+TtKxOk6b0y7HUbaDt1jfolm27ZQfdehi3nMFBtw62W27QrY3tNijo1tx2G2jpvYVy1dN/R5/V+0i4ztgyK4nyRNMZ8si516qqpM6MW0WdW+lKx17II3/P6f7e8ui99zvS95MH5f1kS9/UX4+b2ezcDVu7toq/fOK6SO8DI723jPS+8di/Z3Z/n3nk75Pd3xsf+ftP9z2MR+/98+f2vUXuma/AV626++wO/cZyEENV6jOgPBuLX2vMixr3VqtuD8A2mAvvhqPhvTAfbocT4H1wmsp2L4QPwmr4MFylst0Xwh3wJ/BXcCN8HN4Pn4APw53wdd27sxe+DN+Hv4cH4Suwucp+d4a7YHf4HFwEfwPPh7+F6+ELRiZWn0dgG8mHUyb2QpU9vggmwYthqtr1urrul+cPiZ+G2a3x9xJOvuXB1roXqBv8C8zRvUCj4MdwATwIF8NP4V3wM/gg/AI+Cf8G/R76IewDv4F58J9wMvSozLUXngR98DS1L4ZR8BzYBH4FW8DowP0bpkM/zIC4a/3o2hVmuNTPjVo/N0HZKwZbqV33NOqaED+J79zTeInuRbgMpsNLYTe1j4OXw4nwClio7jPUXgyvhGXwKrgCXg3PhNfCs+F1mg/madZFWg5ttxjMMIyl/SfAV6EXvqblel3L8wZsA/+g6VleXXfoumcHHF63Z0d+LS3dS6rly9DynQ/lLBzYB7aH42FneALsquOjG7wE9oFbYF94r36z2KXfLH4DB+k4GAKjPJQHxsPhsD0cqeMgD/aEo+FxcAzsC/NhLhwHh8ACOAKO1341EY6Fk+A4OAVOgFPhJDgNToVd4RzYA86HPWElPBnWwFPgGXA23AyL4W2wFN4Jy+HDcB58FK6Fv4Vr+P/38Dz4BTwffgMrYDPqvRL64QKYpvYsWAX7wKVwJKyB02EtXAxXwBp4OlwFV8Kz4Sq4Dp4BL4Gr4fXwLPgoXAt3w/PhWniobxAbnk+o+1bRQLn1Y/ltApn17+T7RKO8+rH5RrF+P7LqmH0Y/4fIm2MqMGs+bPxe0fhr/DX+Gn+Nv8Zf4++7+3033/85zfkonf//Yz/PU/ruep9X9xZj5J045k+Bb4Y97O8lXDmSTLeGSzfvqXuI/Q4rke/U5fqtep28p0aNrv19ROO1knhTsHcV+92WnwfKSkyojGmqfp/uJGFusFL4twqjsqaaVgp2eTdsy5ZqvCeNv9ETm2Op3toKmC/+V7idJa1+VZRklqusv4lr/OaYbz4l4reEZ9gmesaZfgs/AlniQhf58CJIneKmdYpbiS2fKmE=
*/