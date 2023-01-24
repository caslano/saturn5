/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   copy_cv.hpp
 * \author Andrey Semashev
 * \date   16.03.2014
 *
 * The header defines \c copy_cv type trait which copies const/volatile qualifiers from one type to another
 */

#ifndef BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The type trait copies top level const/volatile qualifiers from \c FromT to \c ToT
template< typename FromT, typename ToT >
struct copy_cv
{
    typedef ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< const FromT, ToT >
{
    typedef const ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< volatile FromT, ToT >
{
    typedef volatile ToT type;
};

template< typename FromT, typename ToT >
struct copy_cv< const volatile FromT, ToT >
{
    typedef const volatile ToT type;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_COPY_CV_HPP_INCLUDED_

/* copy_cv.hpp
zbgfRZ0+Ty4Oj8bByyh7LTpZJG5/61z/2pL8yu6DxS+bsVT6KoaOFhx2aqGyo3Hri3/tagCP3xBWf1oatXse07GVmEB0U80c3Pj8SZXE86Dhzf2O0rIJpaDrM+uShdXoR8dwwO+gPn3SG1N/BYsgPXWtXZcAYlxp/ogfFlUl3MFJIFRTrsi0PQS33kEHnFFEQBCBZhj5k71/9PCTq6zfL3qNbzrZPRpZYldAN3Mo54v1oSqx5U8uwovD/ZCb9AWfRphhIKZBNv0A6Fm6io5GhEIgHU0HP1sHnQ8gbZabFwnov6RPR/ofm567ETbmVkbgqCrt4Hd6OhDwqyOE1YGvEOaxpv1xA2/V8PWzfwi1WeAqy3XQHORgWBhWj8tjkAb623gd1jddRtYvCQubib1f6TXZdu7wPkToF7tIPIR9HK7LFAa+VYI3OhoiiMpEU1DtTEEAcK8xFJyzaytOYRysg1jay4Rptr7ESuGYiZZQK8E7ezU1MzGMLB0m8PbdaYqmwa/SPym4X1aM+jX4H2bbXhRk8/r+/s81wjX1fA3RESAUVK/TvvYW3S+/cTJ8ZNTbi37BiH4Hri/49e/9x6Vahzi71T5yj+lJRGPc1d5wY8pijgEL3GrkrHhtgdyHxQKQu9KE7h1Un582GWViEHV4dpXFmrMwXcaHdCSZWh6gkLS1aX/+BDzmWtxaih4iXbGPTT+Hql2tveIknV+j
*/