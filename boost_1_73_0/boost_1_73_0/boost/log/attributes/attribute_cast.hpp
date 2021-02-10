/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_cast.hpp
 * \author Andrey Semashev
 * \date   06.08.2010
 *
 * The header contains utilities for casting between attribute factories.
 */

#ifndef BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * The class holds a reference to the attribute factory implementation being casted
 */
class cast_source
{
private:
    attribute::impl* m_pImpl;

public:
    /*!
     * Initializing constructor. Creates a source that refers to the specified factory implementation.
     */
    explicit cast_source(attribute::impl* p) : m_pImpl(p)
    {
    }

    /*!
     * The function attempts to cast the aggregated pointer to the implementation to the specified type.
     *
     * \return The converted pointer or \c NULL, if the conversion fails.
     */
    template< typename T >
    T* as() const { return dynamic_cast< T* >(m_pImpl); }
};

} // namespace attributes

/*!
 * The function casts one attribute factory to another
 */
template< typename T >
inline T attribute_cast(attribute const& attr)
{
    return T(attributes::cast_source(attr.get_impl()));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_

/* attribute_cast.hpp
Gsez8FYe3MaTVUv0UJiXFYi/NjchMcyjPh8Xc5AAqQjRZICqVqQ0Ztt5nBGGVBf00Zxk2akuKHzDX3AUSdr99AHNXG1NM1xT0xB95YvRxVC9JozvBONlHuGdZRXLDhUr7+MkESOpbwHRF/UY45TRtvzSFVhCmwLWwVi+O0jnSULLcGQkRPNk1FwzbTmgVp6EDxCL0790cQ5826/eV67U6N4HeQi2R9mO0jEeXZT6GfATV8mBMKqEJ8ldBEaeiV6QIJrgeQgiXHw7L/DqmEoVJwt6QVjPu49nJ1wVQFBVZueyKLUYpbeAEn7HFcEPg5s+BgTI0Yt6eK7pT7hVB09JnOMh7zTG13LA5NB9LyjcyDRT7qbUyLvvBbOa4fn3vfMf8HBPl0xjF50lXaQg1n7ebnFtaX3PTSAJOtMU4H4fIhKc/gFIGOsTtODjsXuropUlAWjm5ruc3q6DtDJueRRO/ovIyr5uCsSDZI90ItM/huYM6cNHjGyCpOuRh4G9AKrfGwzxsPmQX3sZ3HRmKsLZTFo/tZxSVoBe+g9DEq4OdmYBvgpEyzK3guA0dpVN/KlTja7DMGHo4048uSec6JKNeofFw9B0TrjIsk27qlM/9d50qMmL2ng7G3ehEBHx+k1/gFY11Mcq9QV0tAWm
*/