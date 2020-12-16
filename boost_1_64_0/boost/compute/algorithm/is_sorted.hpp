//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/functional/bind.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/algorithm/adjacent_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the values in the range [\p first, \p last)
/// are in sorted order.
///
/// \param first first element in the range to check
/// \param last last element in the range to check
/// \param compare comparison function (by default \c less)
/// \param queue command queue to perform the operation
///
/// \return \c true if the range [\p first, \p last) is sorted
///
/// Space complexity: \Omega(1)
///
/// \see sort()
template<class InputIterator, class Compare>
inline bool is_sorted(InputIterator first,
                      InputIterator last,
                      Compare compare,
                      command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::placeholders::_1;
    using ::boost::compute::placeholders::_2;

    return ::boost::compute::adjacent_find(
        first, last, ::boost::compute::bind(compare, _2, _1), queue
    ) == last;
}

/// \overload
template<class InputIterator>
inline bool is_sorted(InputIterator first,
                      InputIterator last,
                      command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::is_sorted(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IS_SORTED_HPP

/* is_sorted.hpp
Lm4P43JHg76vzxhNp6vRPfeM2F9o2Id1jlQv/r8We6aJnxL4TmnetV4R/wsofYzEmWHiDNUwvnzu9uRT+lVuglPfTaLpT/kFy/TZ5FvjOuwK4nrP4sLuLLOjH+pYd0j86+22LGk65z8dJM0IM288W+yzdY2CM7+h+nMCPCHhok06FZJOvPr70okImq7oXlHZ+jBMVrxQ7DmNWJOf7Hif1vZj5qIN23Wmo12beSg5a6hvJ1fcKsU+yfTHclmfKPdb0/eft65v5c0c3laKcjlhjlzha/MFFXlkJocLNTPtPk/bu4ajB3XR+f5Zq+S+sxaTs+sw9yB9OkRvinB1985b7Oe0xIkwaVS5xlI7SzE/ZVz6B31opKutZT+ryYoOA12kjWs8cjyS8b8I87zVDVlEFyudqwf0K/MuESv5m+7ap+1ohknnnMC+ZXQBxkicmS7mRI7nOPHMc64Gu/188MyB9b5qPS2XNNqQQkvGedywXStuB+jlna251NMWK0nSuNK3/6FIXp+NDkCpP00fX+2Htk69bfFqzFrpk4/f6X56KLPtsdJ8F0gJGI/LzXhs7oWErQ7Sbmuc7Vbip8IrJZwpm4RNMdeSckl7fXiVaa9ifyfA/tdVwdvz3tb8p2v6OytXEqb+Sl975sI6jge2EZ0ba9i+OnYhHxf7GpnJBRt/J5s4vU2beV/s69hX3yzIfJ32a+Jkmjlk/GqP/SJGot5B596JqjvqHYm30VqrOieLTVrd/Oc/ps1/Jn7LGSk76vPCZV0o1+rgPxabZ8N7En6DVaLtcbW0R+rNu0zLN2Zrfhc0ag1VRpA2MinI2JYZZB4xL3AeoXoC15DeQflmTd7yi0nC3t+0Wq5l8ixtZsTq4G0mpa2e5YXpqFxLmB2rfW3GfAcI1WY0bKppM/vFPpYvf7Gh2ozG6W7azE/EPgE5enTQbzHmfE8JN8noDy0yaXXxn2ubtXs/Fr/JfCGNb9S9Sgtyr9KD9OeMwO8kWs9HQtRzuV74QQarHrAWLiVM2hpfPZfmLC3gW1foetaww40etWKxL4sIUccafpB5b8sT+/KIZvY3MtOeF4rf2gjtnxo3I/h3MeJ0g7+XMH92u60Eap/+ou/Dn2o+W1uxZo+Oe630ObEXm/QnmO8OfWu8+6ySJTyzdgl/A+/zOa4al7vBN7Z2mu4WSScuYqyrlVXqGueKiohyPKe4jnlOpbl0zaf5XmOZuWq2N88RH7oyXGfpXPXmdR638eb9eJfkcag72aRRUVCetXS5TtVMWV+RcK1CliVZdby+Ide0IppbzRlx4/V570s3X9L0fc94VcLmU9NNrAGYcwlNvqS9DpHr3e/W+CZfcq/0PfB3Ev81dzTP4R7OvmL2Ka2RdDq7R1hPutq55VxheW5dJe6XuD11t0DeE6QhmPfIJ8X/WzqG+uqthb4b63XY45dVVl7pr9O6SOJl+OaaWr8W9XvEpXN3fnyN85u7T5K6nOFaaa1UN/94r7k8ec72u1eJ+r3RspAg6ntPO+0fqyWtyyw3LbU9ddqN9mm3jzxTxpbwckmvv7Zxl0kf6bTL913oSnHLcbYP7qOvfSTqt5imEu4h4nbX+nG+VyfquDZH6jGG/EUEm9Pjpu8GUo4utKy2rmR9b58n93t9xD5cD7ubSPwft9R60OeC7n1z3iNZ5ku5tV9Ml7SD9Qk915c4lt/65XQJv9EaRQu7CON75o6SeE20fht+310i/mepXa9jyq35Jop/+3lXrjVX20/IdleSrzdA+iNcLvG2kLsWzD972v1U4t8g32ZrSMOjq7RbW2TbZ3v1X0VHxLnX1Xq0lEbFxsamev5o1uB7tvbXn8g1egf9np0EnxY=
*/