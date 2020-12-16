/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   thread_id.hpp
 * \author Andrey Semashev
 * \date   08.01.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/cstdint.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The thread id descriptor
struct thread
{
#if defined(BOOST_WINDOWS)
    typedef uint32_t native_type;
#else
    typedef uintmax_t native_type;
#endif
    typedef boost::log::aux::id< thread > id;
};

namespace this_thread {

//! The function returns current thread identifier
BOOST_LOG_API thread::id const& get_id();

} // namespace this_thread

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, thread::id const& tid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_

/* thread_id.hpp
4MXwM+3/Rvt57km/j4YFsB3sBHvBP8CBsBBeDTvDKfBSeAe8DC6DXeA22A2+AbvDd2FPmEh/vRzWh71hY9gXTodXwpmwH5wLB8HH4GC4A14L6Wsq6Xes3/evrN03jO90puNW4nbgDuLU8si3O5EjckSOyBE5IsfvOc7C/P+BQ87g+n8bA77/3xen5Jjs4f1JM68x8ilmfIW8g9b/Cx5f0XuSb5nqDf9gVD17qZ2s97ePvcUr6+p6225jxtWiRBZvbLvZ4n/O2PFWSTrDo2Ksqtb59jEz9pF2u9g3jR1vzm1FcxhbO6+nT/kdx1+MvbSO5NPUMzyqo/OaAzp+sow56D3trxo6bqzy287vnSbzglUsLZGCa80Z31zCnyV+obsNI/eN3ZWc1yqYEnZMxnm9AsIHj78YM5bMK9xLnVtyXX08vvo+KXHinNc0mOI4PmPW7q8uaZ3vTUvipor/Av9+X9IGTbSfWabi9ziviTDFeQzHaW55cFgOvTd7JX1NCVKOGu5otcV63eps5qcelfZo6NqjbrJ8tvedN8s8VOZL/8H2XtcuritJ4nfyeNP/SvYsGGvq/LAeF9L5Kt8c9MYSp6HnoagyKmDP/KzANRLuljC2qqrL01P8UZ5cZPdb+9Q3rn3quqjKyqls3jxr6LEoXx/6o8S3mO3wk7XQ7hk0r91X3ncob7jxg0sl/hZ7lKpnVxIZPpGlRVVV2fYI5tv663jM4OG6b6fCBhLue/etWPOW2xWZH5JiJQbde62lnxwk/7YStorHXy+DMpVOKxl+Jeezo7xzm/7B1SVYn7t8YyzN5f7vYdeil1xEL7+S+2iooqSMaKVYfzPja+9KXd3pcjMDo7K+liSJ28lVFUvAw+z8uMtuY55HvnNeWUC5pL1q6H6UJ2GqWvXJr52qyCzqBO7mbL4GqOx/Psm1djX7IR6Sa8mNSuZafuZJUd662pplx6rHcGts9rxkhnFVPR72pKS/yk6gpSrhMtQA63brKzM+0tL7TENaNahtHqRtfrDq2S+ro/bHVlpU0TXtCHtNE0xdl4NrJY0c+xz1hvqaujyFlS7ZN59Fzg2IasiME187r5V7Zo8rhnHvKdYyemOiJc8O084xxZ+5SJZK22+hTBMkzc+j9LogQeMlbUq534QeK9H1oYw/rZj/1G3B/r23+cdWFt9ixgsyM7VsdoAsS8vGB8iytWzKbT5ZUzMmMcEvM2MSI/yyJj7ZEL/MjKMM9MtyfLI+flm2T9bVLzNjK5f4ZZk+2U5T5iYmvc1+mUnvL36ZSe9Jv8ykd7mR5Zprmz3NjEOZ8Zs7/LJmyldXfpm/rvwyk95Yv8zU1XV+mb+u/DJ/Xfll5tqa+GXm2ur7Zebaqk8LHTs7xy8z15Hsl5nriPHLzHX8MjV07Ox7vyz3Xxmb4m9k+n1Cy5OcxqwC54qb33o9PuUwZpUWOmYlv2f8xiHjN07L3gkYxyr6/Wpe7hO5dmyDtYr8ubcavxnnugbBFBnfObX3pZg/Tbl57sUffD9gaJ/a+xi7kfGpv9749s5fv5tzfNLd1VKendmHd8leMt70j6YDpowY+PmMDr92bj0mpSI/dL9KOh0KB1b+tNfxBrGj0vZNbXJis4zpID/SrnPa+HNnz3whteXs2H2/fMXYhqRf+cXJM0/V7LXpzokFT9+xYdWuMzde1knGsw7PzHig4dYRp24+9ui6Wx6t9iTPTBn/GrV7+B3fHam78+35F6Y1+LTZ5tMf/wo3PvhHSWf5kqXtb3W7fmk3MO+JEQfyeJP3jV/Ju5B+L88MHL/Sa+WeA6vCvrARvBZmwbEwGz4Jc+AzMBduhT3hPthM22+bazvt+XAwbAmHwlY=
*/