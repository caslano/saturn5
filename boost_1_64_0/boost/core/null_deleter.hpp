/*
 *          Copyright Andrey Semashev 2007 - 2014.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   null_deleter.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * This header contains a \c null_deleter implementation. This is an empty
 * function object that receives a pointer and does nothing with it.
 * Such empty deletion strategy may be convenient, for example, when
 * constructing <tt>shared_ptr</tt>s that point to some object that should not be
 * deleted (i.e. a variable on the stack or some global singleton, like <tt>std::cout</tt>).
 */

#ifndef BOOST_CORE_NULL_DELETER_HPP
#define BOOST_CORE_NULL_DELETER_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

//! A function object that does nothing and can be used as an empty deleter for \c shared_ptr
struct null_deleter
{
    //! Function object result type
    typedef void result_type;
    /*!
     * Does nothing
     */
    template< typename T >
    void operator() (T*) const BOOST_NOEXCEPT {}
};

} // namespace boost

#endif // BOOST_CORE_NULL_DELETER_HPP

/* null_deleter.hpp
t8cRt8qN3v8dgzEtplLd3oO4/7zhxojk6XrLix8RUcKaESEmK33rQ1uuR9av9+LduMMKXs59vvymJbY1CGOPR5as0iyNP3YNHRKVkQ3isXzMrOhILskGoCQFJTumssFVHX6DoXH9wGJi1fMrrm1vJ+Z8NmPJjJbTYi2LLmMiG2Yr8QIVem0EtT4efh5VHWCXHu6bq6tLyfWWQystIDsycbZSyZ/DpyQwXEBNndlCxtYssoiwAYlWR8g4hmBZTlBlSKH1uFjZ4X2Ba7M6APQ/jK6xuPr3yUCx+pSDYoD2aLrnsKpxx3L0JoImdFi8EZS4l0nEYd+py5t8F0G41d6p9oqakHaH+qrMu5FBZB7Erj1z85MJJO4zdc4wxCvAmLFMgR7jbwkf637hxT6Fy3H0TNkXXo7RJPuF7LBMKP1EL3yfu22d/33inBSCdLENwdkOwDDVTDnOmUPAr0SQ4RRcZWkKZiAlvlPUgbxT17DO/8UHIJYBnIJfVQwrAOvUxY3fPuIRuEesPx4aN0I/Xf5KVBp+BpeSE/1oTO2OrVJ5qaZbIUY9+jPdJPorKA==
*/