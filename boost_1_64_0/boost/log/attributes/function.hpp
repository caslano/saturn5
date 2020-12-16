/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   function.hpp
 * \author Andrey Semashev
 * \date   24.06.2007
 *
 * The header contains implementation of an attribute that calls a third-party function on value acquisition.
 */

#ifndef BOOST_LOG_ATTRIBUTES_FUNCTION_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_FUNCTION_HPP_INCLUDED_

#include <boost/static_assert.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * \brief A class of an attribute that acquires its value from a third-party function object
 *
 * The attribute calls a stored nullary function object to acquire each value.
 * The result type of the function object is the attribute value type.
 *
 * It is not recommended to use this class directly. Use \c make_function convenience functions
 * to construct the attribute instead.
 */
template< typename R >
class function :
    public attribute
{
    BOOST_STATIC_ASSERT_MSG(!is_void< R >::value, "Boost.Log: Function object return type must not be void");

public:
    //! The attribute value type
    typedef R value_type;

protected:
    //! Base class for factory implementation
    class BOOST_LOG_NO_VTABLE BOOST_SYMBOL_VISIBLE impl :
        public attribute::impl
    {
    };

    //! Factory implementation
    template< typename T >
    class impl_template :
        public impl
    {
    private:
        //! Functor that returns attribute values
        /*!
         * \note The constness signifies that the function object should avoid
         *       modifying its state since it's not protected against concurrent calls.
         */
        const T m_Functor;

    public:
        /*!
         * Constructor with the stored delegate initialization
         */
        explicit impl_template(T const& fun) : m_Functor(fun) {}

        attribute_value get_value()
        {
            return attributes::make_attribute_value(m_Functor());
        }
    };

public:
    /*!
     * Initializing constructor
     */
    template< typename T >
    explicit function(T const& fun) : attribute(new impl_template< T >(fun))
    {
    }
    /*!
     * Constructor for casting support
     */
    explicit function(cast_source const& source) :
        attribute(source.as< impl >())
    {
    }
};

#ifndef BOOST_NO_RESULT_OF

/*!
 * The function constructs \c function attribute instance with the provided function object.
 *
 * \param fun Nullary functional object that returns an actual stored value for an attribute value.
 * \return Pointer to the attribute instance
 */
template< typename T >
inline function<
    typename remove_cv<
        typename remove_reference<
            typename boost::result_of< T() >::type
        >::type
    >::type
> make_function(T const& fun)
{
    typedef typename remove_cv<
        typename remove_reference<
            typename boost::result_of< T() >::type
        >::type
    >::type result_type;

    typedef function< result_type > function_type;
    return function_type(fun);
}

#endif // BOOST_NO_RESULT_OF

#ifndef BOOST_LOG_DOXYGEN_PASS

/*!
 * The function constructs \c function attribute instance with the provided function object.
 * Use this version if your compiler fails to determine the result type of the function object.
 *
 * \param fun Nullary functional object that returns an actual stored value for an attribute value.
 * \return Pointer to the attribute instance
 */
template< typename R, typename T >
inline function<
    typename remove_cv<
        typename remove_reference< R >::type
    >::type
> make_function(T const& fun)
{
    typedef typename remove_cv<
        typename remove_reference< R >::type
    >::type result_type;

    typedef function< result_type > function_type;
    return function_type(fun);
}

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_FUNCTOR_HPP_INCLUDED_

/* function.hpp
kDcE8dbzW+5R7l8OsJ1Jr/c01Av07Bfkmr8S1HUZfY7MN8r/0YEh2v9cZXcRux3K7ycDLGHHyRk07rPdlP3fAgrd5uizfB5WdusDmgYMQR8zHXa0JS2z46xnDU5Rbs4FVJG8YnVHxqwUlV/6TOG/qfiOC7TEqbXHjwLsZyk/3g+whKHtz2G/QNnnW+11fhJv3tub9g5xlrOC1yj3LwasY612A/SnxBJLxGQBHjSlYje7jmwVeTnW+++ruH+8tpcos9sry7WDxCB34TYePz6JcrfvOtc5K4c0FdlrZbbPSGmfnr2ZtDfMpqvrUK5pA3rvZri+TjP9UPWWMuPaU143Vn7aJe8XW7uvX5Hrr+S6Z4C3fU6At/0b2t67DzokG1ly5J1qFjyMzp4y5Rz6IDbnOvRBsVLeLyk3Y12taH+zkIXIdh/nrOK/vY/R++aPK7uvjRvoX6YheWhtNso59FUO/pCH9aQ/+LuyK+/qZLo0KvAesTzv0nl+7gpw7KPwy2f/Ug3eVNa0f0udre/QP2n3tv5D7yG8rNzfQAyCiUmgpe2mjbT2Q88pvZ5y7TK+V9d1dbvdqK7vsbhPHcF/uq+Zo+x3Wu1HWs+7WqTsHzUc+wZpm2+otAx3WeI4wtq/rFJ+PGj0p+1WlrbrkW+jlPhsw7RPROtJe/PvbCqjnH/tzdq+Qm3tK9zavmxjcpMQvYZI72Xci9uuQU7tIT1tskN7cKrvuPdr7EXP3i70WQ59lV0lp7qLO8e661hPRVfvkdlagj0yJenbfOS1nncdqaC/iaB+tZHXcJsd4pTX4zMz2ECUnjnTr/xWfvBPxlPn/Lbp3an0Uh3y10kvzSlv0XMsB8f5iOjqctj2L5YD6fQqB+JpHWO4to8xzuUyoqLtmxVSLuHFlMuUGZP9KpdwP8sl3M9yCfezXMJLUC7htnLZ/l9SLgdlA2gtCTgGecPsm4opl5xp0/0ql65+lktXP8ula0gJ+iNbfu/4N+W3r/5okORvroS4FSmPPI6sIH+PfOd0P6bCTBk3kb3L9Eo546Zznzk1lZ3b9vzW9w91rpn+VHTMf8Iodu5xQtlvoi4EOJYL7p3mHvre6KSyf9joJGUnY7qeq0equCU4zQn02QavKT/WsX41UO+dZoxXi9o+sYz1T9RW82yvcd24zrjeh/CLG9fVfkyHsusvZde3cuHZgC7kJmSeee99pZiy40nDdNrJ1MyciajrPeS63CTvtyk/ejuVm/jv0ntv86M8cv1vLXnSSZg6nWaaukua5lZxK59AyiC/QRaQJuPbYtLEF5e805KekZNbWI+CldsjzG9cTukRv12WOpwzfZylDoQo++eNqs5nwmr3cqYZ92OFsvOf7J0HeFTFFsfv3WxCQkJIIIQQQugISEkPoVdBuhQFAakhICWBBAg8fCLgExQBBZXqQwkdIUgxQCgqAvoQO2JHBR5SFBEVFfT99+zZyczd2eyivvK9L8s3/HJnzvRy556ZO7eq02wk48s79XL5UD64HXDb4LTJZdapvDOAGtwOqnM7yPLcDrgFeK7/SeQ3Rj/PsNR/fpjL/P76v43zMqoC75fkshkI8xDyUq2Y8SgD5wPjuyuT093npaIOG5D/bohTfz47wrfcC7LEHLQWuVXQ1r3Vnzx37UhuZTT3Cp2/YcLfYPanu2/An8/39GrFjI8VwVvIvS/6Bdel0na9t1XHGJb7Symfnk2c9yfndQhfy/OBgOLnA6J9VIt0JgAXYlxdivhWeWkfI9IzcFaEb88tCEu5N38S+fvuzXIfvc7p7sV99A6Y6Y5xrZg+ii6aoxujxbhGfrsajT2Na9xPXeftPxfmMn9un7VXcgp/xnn7FGY=
*/