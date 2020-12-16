/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   constant.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains implementation of a constant attribute.
 */

#ifndef BOOST_LOG_ATTRIBUTES_CONSTANT_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CONSTANT_HPP_INCLUDED_

#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
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
 * \brief A class of an attribute that holds a single constant value
 *
 * The constant is a simplest and one of the most frequently used types of attributes.
 * It stores a constant value, which it eventually returns as its value each time
 * requested.
 */
template< typename T >
class constant :
    public attribute
{
public:
    //! Attribute value type
    typedef T value_type;

protected:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl :
        public attribute_value_impl< value_type >
    {
        //! Base type
        typedef attribute_value_impl< value_type > base_type;

    public:
        /*!
         * Constructor with the stored value initialization
         */
        explicit impl(value_type const& value) : base_type(value) {}
        /*!
         * Constructor with the stored value initialization
         */
        explicit impl(BOOST_RV_REF(value_type) value) : base_type(boost::move(value)) {}
    };

public:
    /*!
     * Constructor with the stored value initialization
     */
    explicit constant(value_type const& value) : attribute(new impl(value)) {}
    /*!
     * Constructor with the stored value initialization
     */
    explicit constant(BOOST_RV_REF(value_type) value) : attribute(new impl(boost::move(value))) {}
    /*!
     * Constructor for casting support
     */
    explicit constant(cast_source const& source) : attribute(source.as< impl >())
    {
    }

    /*!
     * \return Reference to the contained value.
     */
    value_type const& get() const
    {
        return static_cast< impl* >(this->get_impl())->get();
    }
};

/*!
 * The function constructs a \c constant attribute containing the provided value.
 * The function automatically converts C string arguments to \c std::basic_string objects.
 */
template< typename T >
inline constant<
    typename boost::log::aux::make_embedded_string_type<
        typename remove_reference< T >::type
    >::type
> make_constant(BOOST_FWD_REF(T) val)
{
    typedef typename boost::log::aux::make_embedded_string_type<
        typename remove_reference< T >::type
    >::type value_type;
    return constant< value_type >(boost::forward< T >(val));
}

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CONSTANT_HPP_INCLUDED_

/* constant.hpp
fQnp69nPDFtIP1MGSZJ4bglyf0vkl7A8fByGw60wGm6DzeF26PEvW/yLdfBvJ3omn4ShcJf4t1v8ewrWgk+Lf3WQLeJfGfHPhUSIf/dbwt0jeh0cwl0v6dgAq8GNsCZ8GLaDm+CNcLP4N1HvNcUP8S8EGSP+7UUvAP4KVoH7YCzcD2+AB2Az+GvYEh6UcJ6DifBZ2FGuPd/KSZbwchH7t3IOoRcCj0p4x2AEfFfy7TisC38DG8KTEu5vYTx8DbaFr8Nu8E14C3wLpsK34Tj4DswWfz35f1HiVcUh/6mboocUU075Wk/2HMKw6/gX18R3uB9a/Ssm3Pcsesk+wxX/xDxb9AbKdSgyWfQqoyfuVP2pBmNhI1gb1oANIHaqHsTAeFgbtod1YCfR7wzrwgHqWsJ3yd4w2dOWB5sjk12SHgb/CvBjGAv/CFvDT+AAeA4OgX+GN8PP4RT4NzgbfgHnwa/gKngZboRfw0fht/BpeBU+D7+DL8Ef4G8gA+L894ALfggD4F9gIPwbDIZqcT6sCsvClrAcjIMhsBOsCHvDMNgfVoK3wHA4AlaBE2BVOAlGwGwYCafD6vBOWAPeDWvCVTAGPgBrwadgQ7gXNoJHYWP4G9gEnoT14Otybeb/Sb2/ib+l/KOQQ1L+zdFzwZYwGMbB8rA1jIHxsD1MgB3gcNgRtoPdYHs4CCbCUfBGmAmT4BzYFS6E3eBS2AOug73gejgA7oFD4ItwKDwq4RyHw+Arcn0JLvPsnYGLJT1hyFxJTxepz11hedhL6uVA2BsOgn3hYJgMk+FwOATeBofCNDgMToTYqfT0hQtgf7hIzD39ar7EJ8WhX20q8Wkm8YmT9tMedoCJMAl2gN1hR9gDxsPRsA28XcwvwT2BsudD9qDkwRxkq5wTMoJ8CoMpsB2cAO+Ak6GpOwXOhVPhQzALboHT4AtwOnwJ5sDXYC7Mh3nSPmbD83ChlMdieAUugf+AS2GYi3KS9rICxsKVsCm8F7aC98MOcA3sBtfBvvAhOAyuhyPhwzAFbpb2shX+Am6HS+CTcAV8BG6EW+CjYv4kfErazdPSbp6RdvMsPA8PwavwRUgbNo7AuvAobAuPw74wH46Gb8Gx8ADMggdhLjwB74SvwKXwJFwJX4Ob4TvwCfg7+Cv4e3gMvg/z4QfwNDwLC+CH8FNYAMtStp/CCPgnWBP+GbaCF2B3eAn2hl/B2+FleAe8AnPgt3AxvAp3w+/gK/AaPAV/gB9CI5BvhQUCGBZEPwcjYCjsAMPhcFgFZsOqcAasBpfCaPgYrA53wJrwt7A2/ADWgd/AuvA72BD+ABvBsGD6MxgOW8DGsCXsDlvBnrAJvBneAKfCpjAbxsAZsBacA4PgEhgMV8CPSd9q+Df4EFwKd8N22P8Ktocvww7wFdgRvg6T4DuwE/wIdoafwi7wL+Lf3+AX8CLMhNfgHdBF+0yVdlLOJXsrZH9Hnswnr3lu6vDPZG9YDvaB9WFf2BCOg43gTbAFHADbwoGwJxwEk+HtMAWmwDRxNw4OhRlwFJwK0+A0sZ8Ob4az4HC4CN4Cl8Fb4Vrx93Hxd7u42yH+/Ur82y/mB+Bo+IK4+524e0/sZf5C5vueD523zsPa+Z4PnbPOr0Qv7Dr+HWno27/d1vlVMfHbb9HLL8a/X1n0sh3i5+SfUcz87xWLXkEx4R6y6F0sRu9li97qYtK71aK3pxj/fmnVc0ivk3/5olfDQe9B67xd6/me7+Z71o/CY6KnziASvYnUPxecBMvAKbCSXEfJdTM4FfaAWXAIzIbD4QJ4K8yB42EunAdnwJVwJrxf9NbA2fBhOAdug3dKu5kn7eZueECun5PrQ3A+PKo=
*/