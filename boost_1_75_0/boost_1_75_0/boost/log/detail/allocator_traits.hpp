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
/tdK1+sa4s9iiNop+ViEtLUR65EU/8E3Msenb+Mc7PwqxTw7K394+obxDJV5BK/sPuu4Hlg0zeIS184qmbRB2N2gdHW0/NjeVg4OTmzteXpan6JPIdNNN6R8+3CRnEHMWYZji6vu9tsgpVmxIX1bXbfit7wl4B9l+qc24POpQdD0bstN9MBNwEncScdL6dRKGY8aKMFrjkzq2qNW1GPLaNe00CB/UP9cKc5a3ZrBhHtwIEWwmG8Y1gTO7zfgOTmZ8vyDQpRczWz2/yuNqVzHbOHx9qWD22V0+PZx271yoYHrG1uKIzTmVaWMdl5KmWi9Wst3nX5MXToxQCO8RUDR/K4TsXV2Ef3BM6a4q/N6BXMtgxC1H1Uj3W3xJW/4aqHSVjpB2nmT/VOSkgP75fvmdaFNjGewRep2l4h71uYNUtGVLlNqWaJvEypmrPhe+DvZaMXKp1aNGO7pG7W/QxFQe3f9zWLb5BRtYWFq2ckl/eMfw4r1rLY3eTF1/nycHsntCUR8OaPm8KFm4yLvJscbCv94tujK5dpaKIzf/Tklz4t04jm+UtJtaO13shiwev4owWe3yu4Iv3T2im6OAIfcgwZ8v4LMKjQk3PgE9OeIDgNlbDPdYp46w5Vgw2CsXi33PutdertOoYmndJoaVVvQ17Nu1Fmiz/m0fBNYBmjGv4q8uhLMwN3XCJL6XBTP+iT0b93awTPe34cVvw5d
*/