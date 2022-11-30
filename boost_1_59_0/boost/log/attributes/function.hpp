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
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
*/