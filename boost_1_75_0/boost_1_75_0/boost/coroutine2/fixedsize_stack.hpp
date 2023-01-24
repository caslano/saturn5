
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_FIXEDSIZE_H
#define BOOST_COROUTINES2_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_FIXEDSIZE_H

/* fixedsize_stack.hpp
0YwKzPSrokrTKx/NkbNMMs+j52SvQ68hUfiydJzk3XRBHPAGahp3D90jc5Cfvd7irkHtj7w/mEZh0LEmnzdaZWdLsUZ3ltk2J/3Jzd5wo3lkYphoMS8BxEhEDgD+5EpLyTtVVGmQlBmmPIvsbLdHki99GIPNP2TUHsPIxKBwwukeuzLUfF0sNvz6KD47o0djmSt8+IP6A9WaI9Ib9UyEr12XxPlHvQ/qeSTUiTHIzSN7brBTQkqcnn1iN/mO6C8++RdvXRyGjf78/CCeXIl+R50C/EA1mIjpdWPAv/H99NsAy68Brk6smj2Bs6gLKv2BZf7Qp+u3UW0lTi0BaMy/yKI7Fzn2bxy/9YBtz1HJcA29OQFHqWcia1DHpdweARUJy51yH9ugiXH8yCdcU6Iq590iV/dsqal7nHuZc5keel37xYqSWz8Uv1LnlhQ4FvQqM/IeqNHjkAG9F54/twbrViBT/xIXqI/KrNsaBDVWOxqFINuPcuRupJORaALNAqsUQqa3xyP35rn8qcMLTSfao1ePIM9voH3h0wfsiACQtKmeBi3cev3U4xbnZU/UeB0vwZKUpzxIoMzPsz1FkjJk/8So5ug65Hzl/S3gZxMEFHRxhLUEud+6XD7f9czfol2XaOXcpG8Ddi6ef28uCKCyFF7IQ0nsbE04IYhkkcSolocR94D7/ULfpR0UL/H5vaPSoRQf8bHijWyzfH9E
*/