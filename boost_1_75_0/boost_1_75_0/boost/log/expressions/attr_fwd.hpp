/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attr_fwd.hpp
 * \author Andrey Semashev
 * \date   21.07.2012
 *
 * The header contains forward declaration of a generic attribute placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_ATTR_FWD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_ATTR_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

template< typename >
struct actor;

} // namespace phoenix

#endif

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * An attribute value extraction terminal
 */
template<
    typename T,
    typename FallbackPolicyT = fallback_to_none,
    typename TagT = void
>
class attribute_terminal;

/*!
 * An attribute value extraction terminal actor
 */
template<
    typename T,
    typename FallbackPolicyT = fallback_to_none,
    typename TagT = void,
    template< typename > class ActorT = phoenix::actor
>
class attribute_actor;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_EXPRESSIONS_ATTR_FWD_HPP_INCLUDED_

/* attr_fwd.hpp
gaAfEQtfR0JP0XoS+vYyDzqlAsjkyfkKsJ9wjeCWZkBQQ5AmqCNGZymBKYJZgjuLlHw7Q9BGzNuI8QjVwyWCOwKeFy3rMX9CJ8sSYA/3MsHdElWX2CMdIrhEcJugrkzJIMiWUYIrGBdlKn54Djay80rROdidr2dCtME52MjZ2dBcGa9bVZZF61aqXjoc2ZkMyW9bdrrzdXOIry07IWeNPNTyW9PqvmTPU1qnrqH/sIeF/SrsTWEfalj6RbG2xDlF1rPn7gmeh+d7au2SK1dpIg72MrQOeK5c5WMSIN9xljIt37HWuFWu9TjTflXO3F1C3agkmya6hKx7s9wW8M+Au/ZlHKeU4lCMUxi9Nq5UqRE4ouD9oukFikeNp/TwJqdcPVwu5A17VvWSN+inreW675Vkq8oVD6zjWp34OX/tjfhDEgfnM0MyPwB/pkKN01anzDkuczAuvl+JiNtu9eEaKiJ0mYTQeAtd+hLpFDULVdmqMFfI93qrf9fyPKj6N9ZGhYW6bRLWOGzm9bfdNjR6shQrS709m6f0sD8zQ4B9kGHplKinQekLNzylIxXT7eruQ7ezdTPILlsXu3KPdFrvI510orgOmUvcW4dMOjLCrkuSgRxuy4Vm3rPQn5EIHVSP7VOU/wsEE4tU+a8QzETopBgMY9IWRXXThJLfqJco+Vph6ZvhOoyvo+lAGRAHeR+qNHmFDGr1gmPrpD+2
*/