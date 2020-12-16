//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_STABLE_PARTITION_HPP
#define BOOST_COMPUTE_ALGORITHM_STABLE_PARTITION_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Partitioning algorithm
///
/// Partitions the elements in the range [\p first, \p last) according to
/// \p predicate. The order of the elements is preserved.
/// \return Iterator pointing to end of true values
///
/// \param first Iterator pointing to start of range
/// \param last Iterator pointing to end of range
/// \param predicate Unary predicate to be applied on each element
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(3n)
///
/// \see is_partitioned() and partition()
///
template<class Iterator, class UnaryPredicate>
inline Iterator stable_partition(Iterator first,
                                 Iterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    // make temporary copy of the input
    ::boost::compute::vector<value_type> tmp(first, last, queue);

    // copy true values
    Iterator last_true =
        ::boost::compute::copy_if(tmp.begin(),
                                  tmp.end(),
                                  first,
                                  predicate,
                                  queue);

    // copy false values
    Iterator last_false =
        ::boost::compute::copy_if(tmp.begin(),
                                  tmp.end(),
                                  last_true,
                                  not1(predicate),
                                  queue);

    // return iterator pointing to the last true value
    return last_true;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_STABLE_PARTITION_HPP

/* stable_partition.hpp
5AHGvd9YcCjZw8ZSanO9R+Tr3uE+rlx+I+uiuEO4Xg9joQ7cv71VWzuyAbIrQw0GGcu8n+sNlc7u72FHyW4t13tePWrM/CbK7ieyqVpvObWaJQ3c30EmlHN7xlignN3zxhJpeo5zsFzsKmt7Q/qNYG1vS7813JcfqI5wFrA1smvEHm1QHUHO/Rbld5n5bVNtGxhjp2qrxXr3KcZO+h5SzlWZyzFpmoV1nNa81GN+GcbazuQ19jtjqe6M7Gf5nnff/1OMz3iP+kOsMe2uGYvO4/79T2w07bIV1PMBWe6C+lzGGPnt36R7H1pIvtNYb7GCFqMBZ+NOrXeNc1rO/k00Ydy77d9YR9pVtX+Dh3jfCtu/qX/Rrp7YMebS2P7NjLrzP9Xh1mul/IJkD9m/kTHsUXv7NzCRz5iPab2s1KWzWDXm0t3+DR3LDvaU6u2SA6y//RveRN9n7N+0DtwzQ5RfRdqN1HoJsrH2b/w6+xFX385xnl+QVsOp1Uz7N+VO+s6Rby/qMl85/8v9tlhaudl9TRq4zxArNS9ns4C9pfXmkL2v/rp3sx8rv1nUZb3qbUXfzfJ178q3Sj/3Nz87NGs/MOe90iXMvZCuefmIvkdVxxZ3/qc5aMk9fU49akF2QXW8xZx/kt1aavqrdPmadfyu2ehCDf5W3D+4P26oH01ZW9ZCVu891DSXsWRRsnzGMhwraCzN1VHUWHg9cy5lLHMQtQrJdymf4e4ylvoz9auiuJ8xRk1jcXftrKu4dYJgjRSjHuttrtpe4P2tpWLczdoeVIyl7vt/inGZuXSQfnW4XifF7cnauhlLCXGGehmLuO/Q91MuCfb3f4p7hnXEpFUx2o3Qeu6z/Rix7935n3JewHmZovVK03eGfN1z7GzV5u7xLxtLr0oNXjEWcJ/zlsn3H3f+JzaEdm+KufOw94zF3LPUR+pRnD1aJ9/dzO9T1XuQ66Upvxvu+3+qYxnZHmnwJ3M+qH4czgJ2xFhiJH1PKudOZF/L1/2d+rfK5V/Oxo+agzVklzRDYWpwRbW5d15/KYZ7T/yvtHJn11nusNouMUZOYxn38n50m7F4GeoXNBZeRA2KGEvbQLuSxlLcvbassXR376loLODOi+9RjMOcvxqyG+X+/lc5x7kXGhoLfswYzVRHI+Z8n9abydl9QDlXYC5tlUs6+/ao4h5ifh2lqbuePmkscz6va1HFqMO57yv93HvTp42lzmXcZ42FdtN3uHLp7s7/jCXHsx/jZefe4U6WLkepy3Tlchdre0l22xl3nnIZQN9FxhJuxpdK5xzu73+l6QT2crWxqLv+vSsNZnAmU7VeVs7zJ2JlyDbd8qUGn0sXdw/drn48yTp2q44JnI0D6uVSzsZXxmLXWe8Jxb1JdlbaH2B/v9FeWMG4PyiXq/S9qPWm8553WVr5v//Veiep6T/KOTfrDRTWGQB1yWEs8yR7nldsAXtewFjAfbYvbCzWleuVMJZ0f09cxljEvVOqIPY2rxGVC2svMG51YxnuXLm2sZTm3G8NjKV3oaZNFeN52t0ru6epS2vFTaNdG2PRGcw5Il3uoAZPqN4j1KCrfN37rZ7GUpeT9VEdz3N/DDQWd/oNlt1FzsYw9eMUcxltLLHJnf9Jv1qMMUn5DWTO07ReGmO8KJaLGswV285+LDQWGk+7VzVrcWqaVG2u3lXGggGyd7TeV+zlh1qvpTv/k53TeaNiTGDcz1TvXPf9P7Ened3YpXkuQd/9mg23Pw5rrqpS5+PSZX0usDPq20jWdl79+I5z/71m4xDr/UW1ueewTPn2oAZXNZMDGfe66jjG2m5q7l9jj7IXsfweYb15jMXfY223G0vry57fYSw=
*/