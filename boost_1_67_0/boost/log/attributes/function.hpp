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