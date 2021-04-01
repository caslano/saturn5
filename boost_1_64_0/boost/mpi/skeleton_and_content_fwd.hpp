// (C) Copyright 2006 Douglas Gregor <doug.gregor -at gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor

/** @file skeleton_and_content_fwd.hpp
 *
 *  This header contains all of the forward declarations required to
 *  use transmit skeletons of data structures and the content of data
 *  structures separately. To actually transmit skeletons or content,
 *  include the header @c boost/mpi/skeleton_and_content.hpp.
 */

#ifndef BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP
#define BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

namespace boost { namespace mpi {

template <class T> struct skeleton_proxy;
template <class T> const skeleton_proxy<T> skeleton(T& x);
class content;
template <class T> const content get_content(const T& x);
class packed_skeleton_iarchive;
class packed_skeleton_oarchive;

} } // end namespace boost::mpi

#endif // BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

/* skeleton_and_content_fwd.hpp
wd+qVoUYDp1ubMSCwM6BstHwwRLr30b7TM3DHbshdnZUJUSq/QO8cLpNP/Gy+ZUdNTbdHqON+nQcn7q9IyYHPgtbJyXLDHGa8woSYQsPLkVygbLDrA5mqyuN4vW/s6lku87Ve5B/9T+34cBOaUnrtKS0qj2SM60rQtTW1BfxOQdxlrt2cJc1tpe8PswC2Tg7gfcqma5UC7SUkIFRQt2NbGdLFrTZ/MKPwYi33ih2iLGdMsNd6GR56N+i1+XpzE8+jTsSE9RfiQNbaBHjIuuexwU2bUu8sHtIo+QLIQ24RLI+gTG9xHbtQFJRGDOHufieH8zBymrsPXBiwJK43pypmKnBF0qkdOIKXgBBnRgYEGPCMjh+O0RChd8e13Vapn6i5N4CJYYDT4d/FJk8+vih8LIFtATiN/VbJpcc8Ybv4LzMcK6VW2xlmG8LtFFwXXKvn3ye4DeQXFPP/cgVkGolR7nSIudju+kQGyx/gOSKqDPzcN0CrcoH2cCWFRIl0XmOidLhxmFsSOt1cQ2J8Vadns/5v4LOZZJ4hMsG28XZyYBi1SKSLf5nQaDLHQ==
*/