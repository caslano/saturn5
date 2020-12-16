/*
 *             Copyright Andrey Semashev 2018.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   allocator_traits.hpp
 * \author Andrey Semashev
 * \date   03.01.2018
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_ALLOCATOR_TRAITS_HPP_INCLUDED_
#define BOOST_LOG_ALLOCATOR_TRAITS_HPP_INCLUDED_

#include <memory>
#include <boost/log/detail/config.hpp>
#if defined(BOOST_NO_CXX11_ALLOCATOR)
#include <boost/container/allocator_traits.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// A portable name for allocator traits
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
using std::allocator_traits;
#else
using boost::container::allocator_traits;
#endif

/*!
 * \brief A standalone trait to rebind an allocator to another type.
 *
 * The important difference from <tt>std::allocator_traits&lt;Alloc&gt;::rebind_alloc&lt;U&gt;</tt> is that this
 * trait does not require template aliases and thus is compatible with C++03. There is
 * <tt>boost::container::allocator_traits&lt;Alloc&gt;::portable_rebind_alloc&lt;U&gt;</tt>, but it is not present in <tt>std::allocator_traits</tt>.
 * It will also attempt to instantiate the allocator type to test if it provides the nested <tt>rebind</tt> template. We don't want
 * that to happen because it prohibits using <tt>std::allocator&lt;void&gt;</tt> in C++17 and later, which deprecated
 * this allocator specialization. This standalone trait does not use the nested <tt>rebind</tt> template in this case.
 */
template< typename Allocator, typename U >
struct rebind_alloc
{
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
    typedef typename std::allocator_traits< Allocator >::BOOST_NESTED_TEMPLATE rebind_alloc< U > type;
#else
    typedef typename boost::container::allocator_traits< Allocator >::BOOST_NESTED_TEMPLATE portable_rebind_alloc< U >::type type;
#endif
};

template< typename U >
struct rebind_alloc< std::allocator< void >, U >
{
    typedef std::allocator< U > type;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ALLOCATOR_TRAITS_HPP_INCLUDED_

/* allocator_traits.hpp
+sUYFUorzLo6U8aBPP3WvEMZNbx+kz7g2/KXiV9ohW0F5Tl8O77bXWq7N8S3JzcKJpDPSb58FqZNzmZKz8zOTC+0rGEKzW/d3CPhOod00TzF7PHqk1whxnmcK9HoA0fxrNtCeC/6DvgRemXXeVjzSzSGwGr++wpJ61J3uvGVyz8PzXtPfqcx1w3he+VZCKe6Is/2329Yq+YWQKe1goa11X8VnYfni1+K029kZrxq5npielZOUYH3dLb7lX20/7TbsJUhY2JzHQ/P8zAemns/Oxr4RffINF4x8T7EzTNz3lqr+9LbdAyvMu8BmWfUfZ3fvdK82zzh+n1S9YtcpHmYlxHdmhxEV/OEUBanPFj2uovM+n5B6n+ALc0JpPkR4cMjPKHzRkRXiu5NwiHWPjrLfEZ4vcSvY0Txr/97SgekDo+6rWmu1XySYn3u7FqRYpUq55DPuXKe7rZ8HivLp3seMxH7EZJRp3zOlPgNuH8KtaXR/3atv5Ivpf6qUX/nn0O+LpR0e9rSLL29LF8l70VHnqn+OlrqT9YjmsZ+M18rNV8Vz9PPco32seUp4Q5Lnm73hESeoa5+kPj1yZO9rgrv8Ocp1ayreudQVxv2nF5XG6z5Gnbmunpqj3NdRS7256v+OdfVbEnzQt9aRdMbttiSJ090GF/CdYV4sxVhOOYrR+sr3HDZyrZK88V62qyv2HOor3aSbn9bmgcteSt+48z1lWSvLzONbkv812LxYq7ulpK1c8jXr3J9d5A0m2qaC5f48uVx9/Nwr0ruIj0hUdGXkHaoi2I75W+HpHMR54iStFprWpPupP/L/URnT2iUJyycn0pIJzLSExbtiZA/K3nCfPtCpZx3DyL3H5EFOOu6Xv06kdYu8RtN7HA38W3PaTTVvFSXurrDFc7d/sXk6Wa4E8a4uhqXIv77n0/kev3KV596jgl6DjO/nCZc9/Gs9b6CcB/L3mzdkKreZgvxhDIG2ud+vU9dJHUzw7yfX3iOe6g/6Xq3mt82ooGu86X+rmKuF+LQF5hrZHO+k7Wusde+9q1i0a37Bnl3676BUcZvSW/t+7LOmNm2ffs2nXXvINW7eaBrwoQzf6OZ+Dofm+tHXxqG87xvhjfXm5Q5K6fQaa43w/rv27Y2MM661qpm/f1d8x1nuwfR/GlYj+ku+ZA666V1tmaFPlcaQeJwIvTW2eby6ix1amZOZn5WukPdye/2v7E3LnFHRfjXkJ+KHu1s3/EMdeuPf0jC1HS28+hc1+ba/h/iP9Sp7okb+Dv6zNPf7flQ8m77zXyJ1U3z8aDVTdPfYHXTa+b1ADexIWNxi9Xfp3uLW7ZpS7UxkiNug+U3m272b3ZPz2vj64sZNveZ5jfBSy3ukcY1p72v8a2k/YYrwthse2fiF3HfjvsLpnskEvWR2LjH/XnT3YPUEvetuK833WOQZuL+Eu76+7yWvYu4b8D9MZf19/zB4v4k7g+6qll+z5/wUZnN5zh1G7zfN6dLOK2/OZZwtdQtQ8J1McM1Rm61hKuubtkSrpfU2+HfrPVGPSfb3yFo+7Hsp9lsJncWt75q91t/kxW3fuIWp3V1sbrZ6kncXuJN8FsMaz0NEffHuEspsj33MFPc19CH5xjW5x5uEPcncF9sWJ97WCLuz+J+r2F97uEBcX+BXrhKyh2re5cb4rz5z5Qy36tlPi7XTSNx+7Pm+6S4VTGsbdV4n9w7Snr77f3vdLsWUucRtussVtxCbddZI6ub1mNbq5vmp6fVTetwgtVN62+GxS1O3b77QN7nMNuvLjJAwg3y9Sd1C5Vr4yrzGk1ALpVwIyVcNa3baeL2sNTDtt9s12cbvT7lmXHz2S2dI/3PNd0=
*/