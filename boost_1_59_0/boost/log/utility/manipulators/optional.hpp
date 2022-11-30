/*
 *             Copyright Andrey Semashev 2020.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/manipulators/optional.hpp
 * \author Andrey Semashev
 * \date   12.05.2020
 *
 * The header contains implementation of a stream manipulator for inserting an optional value.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_OPTIONAL_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_OPTIONAL_HPP_INCLUDED_

#include <cstddef>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Stream manipulator for inserting an optional value.
 */
template< typename OptionalT, typename NoneT >
class optional_manipulator
{
private:
    typedef typename conditional<
        is_scalar< OptionalT >::value,
        OptionalT,
        OptionalT const&
    >::type stored_optional_type;

    typedef typename conditional<
        is_scalar< NoneT >::value,
        NoneT,
        NoneT const&
    >::type stored_none_type;

private:
    stored_optional_type m_optional;
    stored_none_type m_none;

public:
    //! Initializing constructor
    optional_manipulator(stored_optional_type opt, stored_none_type none) BOOST_NOEXCEPT :
        m_optional(opt),
        m_none(none)
    {
    }

    //! The method outputs the value, if it is present, otherwise outputs the "none" marker
    template< typename StreamT >
    void output(StreamT& stream) const
    {
        if (!!m_optional)
            stream << *m_optional;
        else
            stream << m_none;
    }
};

/*!
 * Stream manipulator for inserting an optional value. Specialization for no "none" marker.
 */
template< typename OptionalT >
class optional_manipulator< OptionalT, void >
{
private:
    typedef typename conditional<
        is_scalar< OptionalT >::value,
        OptionalT,
        OptionalT const&
    >::type stored_optional_type;

private:
    stored_optional_type m_optional;

public:
    //! Initializing constructor
    optional_manipulator(stored_optional_type opt) BOOST_NOEXCEPT :
        m_optional(opt)
    {
    }

    //! The method outputs the value, if it is present
    template< typename StreamT >
    void output(StreamT& stream) const
    {
        if (!!m_optional)
            stream << *m_optional;
    }
};

/*!
 * Stream output operator for \c optional_manipulator. Outputs the optional value or the "none" marker, if one was specified on manipulator construction.
 */
template< typename StreamT, typename OptionalT, typename NoneT >
inline typename boost::enable_if_c< log::aux::is_ostream< StreamT >::value, StreamT& >::type operator<< (StreamT& strm, optional_manipulator< OptionalT, NoneT > const& manip)
{
    manip.output(strm);
    return strm;
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \param none Marker used to indicate when the value is not present. Optional. If not specified, nothing is output if the value is not present.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a opt and \a none objects must outlive the created manipulator object.
 */
template< typename OptionalT, typename NoneT >
inline typename boost::enable_if_c<
    is_scalar< OptionalT >::value && is_scalar< NoneT >::value,
    optional_manipulator< OptionalT, NoneT >
>::type optional_manip(OptionalT opt, NoneT none) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, NoneT >(opt, none);
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \param none Marker used to indicate when the value is not present. Optional. If not specified, nothing is output if the value is not present.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a opt and \a none objects must outlive the created manipulator object.
 */
template< typename OptionalT, typename NoneT >
inline typename boost::enable_if_c<
    is_scalar< OptionalT >::value && !is_scalar< NoneT >::value,
    optional_manipulator< OptionalT, NoneT >
>::type optional_manip(OptionalT opt, NoneT const& none) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, NoneT >(opt, none);
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \param none Marker used to indicate when the value is not present. Optional. If not specified, nothing is output if the value is not present.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a opt and \a none objects must outlive the created manipulator object.
 */
template< typename OptionalT, typename NoneElementT, std::size_t N >
inline typename boost::enable_if_c<
    is_scalar< OptionalT >::value,
    optional_manipulator< OptionalT, NoneElementT* >
>::type optional_manip(OptionalT opt, NoneElementT (&none)[N]) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, NoneElementT* >(opt, none);
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \param none Marker used to indicate when the value is not present. Optional. If not specified, nothing is output if the value is not present.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a opt and \a none objects must outlive the created manipulator object.
 */
template< typename OptionalT, typename NoneT >
inline typename boost::enable_if_c<
    !is_scalar< OptionalT >::value && !is_array< OptionalT >::value && is_scalar< NoneT >::value,
    optional_manipulator< OptionalT, NoneT >
>::type optional_manip(OptionalT const& opt, NoneT none) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, NoneT >(opt, none);
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \param none Marker used to indicate when the value is not present. Optional. If not specified, nothing is output if the value is not present.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a opt and \a none objects must outlive the created manipulator object.
 */
template< typename OptionalT, typename NoneT >
inline typename boost::enable_if_c<
    !is_scalar< OptionalT >::value && !is_array< OptionalT >::value && !is_scalar< NoneT >::value,
    optional_manipulator< OptionalT, NoneT >
>::type optional_manip(OptionalT const& opt, NoneT const& none) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, NoneT >(opt, none);
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \param none Marker used to indicate when the value is not present. Optional. If not specified, nothing is output if the value is not present.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a opt and \a none objects must outlive the created manipulator object.
 */
template< typename OptionalT, typename NoneElementT, std::size_t N >
inline typename boost::enable_if_c<
    !is_scalar< OptionalT >::value && !is_array< OptionalT >::value,
    optional_manipulator< OptionalT, NoneElementT* >
>::type optional_manip(OptionalT const& opt, NoneElementT (&none)[N]) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, NoneElementT* >(opt, none);
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note \a opt object must outlive the created manipulator object.
 */
template< typename OptionalT >
inline typename boost::enable_if_c<
    is_scalar< OptionalT >::value,
    optional_manipulator< OptionalT, void >
>::type optional_manip(OptionalT opt) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, void >(opt);
}

/*!
 * Optional manipulator generator function.
 *
 * \param opt Optional value to output. The optional value must support contextual conversion to \c bool and dereferencing, and its dereferencing result must support stream output.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note \a opt object must outlive the created manipulator object.
 */
template< typename OptionalT >
inline typename boost::enable_if_c<
    !is_scalar< OptionalT >::value && !is_array< OptionalT >::value,
    optional_manipulator< OptionalT, void >
>::type optional_manip(OptionalT const& opt) BOOST_NOEXCEPT
{
    return optional_manipulator< OptionalT, void >(opt);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_OPTIONAL_HPP_INCLUDED_

/* optional.hpp
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
*/