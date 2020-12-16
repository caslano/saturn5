// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_COMPARE_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_COMPARE_HANDLES_HPP_

#include <boost/winapi/handles.hpp>
#include <boost/winapi/file_management.hpp>
#include <boost/process/detail/config.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

inline bool compare_handles(boost::winapi::HANDLE_ lhs, boost::winapi::HANDLE_ rhs)
{
    if ( (lhs == ::boost::winapi::INVALID_HANDLE_VALUE_)
      || (rhs == ::boost::winapi::INVALID_HANDLE_VALUE_))
        return false;

    if (lhs == rhs)
        return true;

    ::boost::winapi::BY_HANDLE_FILE_INFORMATION_ lhs_info{0,{0,0},{0,0},{0,0},0,0,0,0,0,0};
    ::boost::winapi::BY_HANDLE_FILE_INFORMATION_ rhs_info{0,{0,0},{0,0},{0,0},0,0,0,0,0,0};

    if (!::boost::winapi::GetFileInformationByHandle(lhs, &lhs_info))
        ::boost::process::detail::throw_last_error("GetFileInformationByHandle");

    if (!::boost::winapi::GetFileInformationByHandle(rhs, &rhs_info))
        ::boost::process::detail::throw_last_error("GetFileInformationByHandle");

    return     (lhs_info.nFileIndexHigh == rhs_info.nFileIndexHigh)
            && (lhs_info.nFileIndexLow  == rhs_info.nFileIndexLow);
}

}}}}



#endif /* BOOST_PROCESS_DETAIL_WINDOWS_COMPARE_HANDLES_HPP_ */

/* compare_handles.hpp
xL8DT1sLvnl0CX3eJA98gbKs1w9dJHkQabfT+fOm2K0OyZ/rKDtPSZmxr2NqqtappMBq8pxlVLBvbntuD4u/DSmTERV0qCR1vGqLH8kV7FvY9kH8TPzoh4b9udvof+7ETR3lRuoLFa8PRKet0VTqC9b3+edS++f0YxkXPX9snDmIFSxh1yWLvhHFd0m/ftT86Q77folOgyjlp7mg2O+h0vuVX32DfsXMP6D9CtEpRmdUusTPFbp/1lyua3HtSdH7Z4l5Wu1DtUOtv1qezBiaMqXoLsJcZ9vLaD2/l2KuwFxEWAOw/0LsLfNH5FBMjm3NdQOX09pV2f6JdLeVdVtphqn3HqIO1nsPvX+13sdC75+xx5Lp/TOesWTN9N4vlkzvn3GzljXT+4Ass2R6T435lkzvqVFsyfSeH+Mtmd7zw7tcyyTOCcheRKbWc8o1z0mFvTh8y//+vTj89Q11EDKpgyqsT2POovy5A8COb+PVKR+Sx6Xjpk2ezIYV0nTo+tSU+tR5bSfudHvbVdrziawMdTrfUOvq+sjkWeMQofySWYbDOl6tr/fvNqXuDLrJYRlkwF2izV1iSJx8Eo4kSHRTbbqpNt30CmGgL94H3GTY3GTY3ISuRzPCrEv052Ga5KF1z8grZJJXen2urFuz5Ukt5KgZxAt5aNrFL0mPT9wRZ7UGLkO7saUlpBxkESB/SAJ/EZiJlIMyezmgqT3VclBmy3O3R/XrDOdyUPZPyD+3R5V52xq+pu7wa+mc18yFX+vmvLYv3Bq48Gv+qp3rl7t3JI0bc8nZt95470PDf67z6tjwawGd1/yFX0vHFtPI13x66/RtL1/U8JWOy/bPmLf5hcqvXavsGkHntW7h1gL+59b8Oa+xC7/mz3ntXfi1cZ+29Msfe+vht09W7zn7+U5T3nih5bPLw635q/wa03/1mr/v0G+A4U/6H8XoZbm5X9Zv+hLWb7KUdxf1nqXeFY/AoZgtql3nXbS0DuwLG8P+sDkcAFvD0XAizIXT4Bh4JZwMl8NCeC0shhvgJXAjnArvgSXwPjgbboFz4DZ4GdwOL4cvwFL+fx3Og2/CBfBduBCWwyvgR3AR/AIuhkfhVfAYXAZ/hMvhz3AFjDQD8U6Bq2EmXANrwxtgXXgjbADz4bnwYtgaToLt4U2wExwPs+EEOBLeDCfDW+Al8FZ4JbwN3gTvgrfCTfABeC98BN4Hn4X3w53wAbgXboYH4ZfwJDwMXdyjr2As/CtMgkdgJjwK28AtsDt8BPaCj8Ph8EmYC7fDAvgUnKKup8Md8DJYBhfDp+Ey+Cy8Fj4Hb4PPwy3K3TNwJ9wLD8L98GV4AL4Gj8A34HH4JnS5mQMKPXAPjIdvwzT4DmwJ98FseAAWw5fhlfAgvBYeVfe5abAth27MEcW66nnoiJ6fnaALdra5K1PuIh3cdVfuesAI2BO25Ecqgher8L0WcwwTl+iR+TY14G/NuRnIooQyyDyKSs9zWdfHPKW5Lv+r81yY4/K781uc5rZs62P+0+a3BOe2HMTPAujpa4ad41K3r3nKc1xGoFuMcZ7rgqyv+bvzXX5nrku4eS7/0ByXbX3NU57n8s+a43Kwr/lvmefy98xxqcz8ltC5Ld5+jD5ignNc+vL7N+a52Oe4/MfmtxQQx22wfaLnd+e5PIdZjH5wjssmf/pwV4BZmHh6Tsvpv9N/p/9O/53+O/33//bnwfzxX/b9P9f/6f8f+u6fzveHmf41u4/63+/yZpZw6j3dO5GXwFdFXjwlb2relOl5lvxNkU+emp+XM5F9X+VbfZbD/AFkIfMHkIXMH0hXMldAr3/PXv27o6rlbpEP6z64y4Ah3W1yj8i7Dug=
*/