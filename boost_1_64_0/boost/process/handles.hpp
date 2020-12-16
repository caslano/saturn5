// Copyright (c) 2019 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_HANDLES_HPP_
#define BOOST_PROCESS_HANDLES_HPP_

/**
 * \file boost/process/handles.hpp
 *
 * Defines functions to obtain handles of the current process and limit the amount for inherited ones.
 */

#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handles.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handles.hpp>
#endif

#include <boost/process/detail/used_handles.hpp>


namespace boost { namespace this_process
{

///The native type for handles
using native_handle_type = ::boost::process::detail::api::native_handle_type;

/**
 * Get a snapshot of all handles of the process (i.e. file descriptors on posix and handles on windows) of the current process.
 *
 * \note This function might not work on certain posix systems.
 *
 * \note On Windows version older than windows 8 this function will iterate all the system handles, meaning it might be quite slow.
 *
 * \warning This functionality is utterly prone to race conditions, since other threads might open or close handles.
 *
 * \return The list of all open handles of the current process
 */
inline std::vector<native_handle_type> get_handles()
{
    return ::boost::process::detail::api::get_handles();
}


/** \overload std::vector<native_handle_type> get_handles() */
inline std::vector<native_handle_type> get_handles(std::error_code &ec)
{
    return ::boost::process::detail::api::get_handles(ec);
}

/** Determines if a given handle is a a stream-handle, i.e. any handle that can be used with read and write functions.
 * Stream handles include pipes, regular files and sockets.
 *
 * \return Indicates if it's a stream handle.
 */
inline bool is_stream_handle(native_handle_type handle)
{
    return ::boost::process::detail::api::is_stream_handle(handle);
}


/** \overload bool is_stream_handle(native_handle_type handle) */
inline bool is_stream_handle(native_handle_type handle, std::error_code &ec)
{
    return ::boost::process::detail::api::is_stream_handle(handle, ec);
}

}
namespace process
{

namespace detail
{

using limit_handles_ = ::boost::process::detail::api::limit_handles_;


}

/**
 * The limit_handles property sets all properties to be inherited only expcitly. It closes all unused file-descriptors on posix after the fork and
 * removes the inherit flags on windows.
 *
 * \note This is executed after the fork on posix.
 *
 * \code{.cpp}
 * system("gcc", limit_handles);
 * \endcode
 *
 * Since limit also closes the standard handles unless they are explicitly redirected they can be ignored by `limit_handles` in the following way.
 *
 * \code{.cpp}
 * system("gcc", limit_handles.allowStd())
 * \endcode
 *
*/
const static ::boost::process::detail::api::limit_handles_ limit_handles;


}
}

#endif //BOOST_PROCESS_HANDLES_HPP_

/* handles.hpp
kzwLE6w2imuuOtf6heQzy5B7qrl8wGNth1bSV7Dekz1UlqWD7u/yW1UZrvFuwbV6Hnfl7qJfvAEPYS+udUscfuoWxzGnfJ5Cvb0sy3SjbbnL/nCuHxsj/Tazb3evXOcs9UpQmV76ePBcE5l9mtmS517GV3kZ81rLvF5Tck63n6P0LTVrXtmhct4263qCDKcz3En2r6WU81cpJy1hRvQP6r2Y3dZnlvr7AE+Tp+47tdtKu8RQhNwHaBrmPUtd6/NnnkU5XlX4p6pXQmLUZyEtmY++Bu9k5FvknO+42xGh+5wTZdq/RHo3jVKbI2bK9XxhmL4nU+3ezoFsv3WyLxbb+suciKbfTAtk9Qe3Sp7XOvV0tg1YE3Sdahz8eAtPP/lmOR4fuiKWJ7Q+6FvcXK5rKfd3maaZrdyScuNqSNmOo0khcg1ODUapCF2H6yStkp7UlSqX4ytW9/96K+mTJnSL9HMU8qDuWVHLG9/S4VXd97P6+XoHlbotZjnq9HXJkV9WUnqz+zM8ym0ix78jwdYfqMmvquG4t75z21Hvvwelfz7de6y6xL6ZpF50/EPd4zVLtXa+o35z3q2WuD6X+R6l3DBbG60PZfc1NMvUQsl5PaH28S4HoORZTJ4syfNmQq13Z+vt0Uja2nHm/cQrZBvs8+7A07FJs7WTb/JaiSva2O/v6ePFbM+9pc143bsRLfGzzgCvHnXaadrnOm3zX9Ravxa12ua2us/oL8dVo/DrmfcY3yDfh4PvUYMbf6IKQqJUkzD2Qft9Qc6Tclwb+6Csa7F1rLEPFk0vkT+lfSXPDsmTactjdNom3OzJ8zR5DkiexIRg+7ascdfpKsY7HNIe2dq0CfmlpePzCybnVhdUT1MRej2ulXwfdnk3Kjn4LP2LaPIHNtXXNZ4bxkXlE0vKi8xt8olcUwx3eNqUX6UtaBYTo8qjgo19mPlnS7nb6RvKOUaXxzV4tfV9lKcaSb+XZWHY7BNtZTve5nrCNTtOPp9mGe+U4+tezjd6/7Cdrwor5G62eZwNaibtkldj1dxsA/dLmp+K0NeJ90p5d3bNiKkMfrzjBdv3AUqMs2tJja5nP9bjtJJ23FaPBWWFpUU1NdwBtbeP7QOlnTXb/9vbSdusx3vWzZ9lsPfxN/k15ynoX3hvk7a4G/MLdMiyMj+9rrrPrk+r5r48Qu5NJrvaOhbw/s3ljlhJ99yjXMA9yi9dcd59eKZ9TViLSPf1a3vKHy/lb+gSXLsNMO8fxgZIufQP29Tb97ff4zTumHj2yT2UneUlx6G+76LPo3Xu0zdqLNvcrJfZtv5aHmU0lvr2lra0JMp2TafbOUWeAHMfde/vqaSNkfV6pUu02Veyfb2xvGgi29XcR+6U+x0ZtMRtZPpdTL9Epp9jvz9bkzstv7SkML/G/t2dh6V/1U/KqnPfU84HIynrHSlreK37wSUTy3OLKibI/OLJ45S6CiWPfre//P5C33/W2yJa2uCmMs1F9ts4meanznU+E6ipudmq3wdt96PmNXDtGGzV7TSl6zXy91p97Ro6N7a+Nv0Elnm7rFe2rY74jMr+WYD+/OA9yZfcpWNUTnAebYqRf0SMrc8vN2GseyU/yXqt6dTN1YV3FsTyHOk0dZZrppYBPvH6vo8+9z7SLpa3LzzvnRH74BXzHRF6Hb+X+bXu8lNkcXB/5mftf9PLKivlnq35mftX0v9p6z4nsk4Vsr89Ybs+mKxi9XKVSl2+4f0732uZ7rzb4esdwzsx2nCOZLztvFH7umm/+rPfCjlfXA74i+3+gVxw96yo6qU/B+K7BU45FrgydPGb7n7O+529eCdRH2dH38uOXpLHoesmrvP39BWDHJE=
*/