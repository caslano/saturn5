/*
 *             Copyright Andrey Semashev 2020.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/manipulators/tuple.hpp
 * \author Andrey Semashev
 * \date   11.05.2020
 *
 * The header contains implementation of a stream manipulator for inserting a tuple or any heterogeneous sequence of elements, optionally separated with a delimiter.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_TUPLE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_TUPLE_HPP_INCLUDED_

#include <cstddef>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Stream manipulator for inserting a heterogeneous sequence of elements, optionally separated with a delimiter.
 */
template< typename TupleT, typename DelimiterT >
class tuple_manipulator
{
private:
    typedef typename conditional<
        is_scalar< DelimiterT >::value,
        DelimiterT,
        DelimiterT const&
    >::type stored_delimiter_type;

    template< typename StreamT >
    struct output_visitor
    {
        typedef boost::true_type result_type;

        output_visitor(StreamT& stream, stored_delimiter_type delimiter) BOOST_NOEXCEPT :
            m_stream(stream),
            m_delimiter(delimiter)
        {
        }

        template< typename T >
        result_type operator() (boost::true_type, T const& elem) const
        {
            m_stream << m_delimiter;
            return operator()(boost::false_type(), elem);
        }

        template< typename T >
        result_type operator() (boost::false_type, T const& elem) const
        {
            m_stream << elem;
            return result_type();
        }

    private:
        StreamT& m_stream;
        stored_delimiter_type m_delimiter;
    };

private:
    TupleT const& m_tuple;
    stored_delimiter_type m_delimiter;

public:
    //! Initializing constructor
    tuple_manipulator(TupleT const& tuple, stored_delimiter_type delimiter) BOOST_NOEXCEPT :
        m_tuple(tuple),
        m_delimiter(delimiter)
    {
    }

    //! The method outputs elements of the sequence separated with delimiter
    template< typename StreamT >
    void output(StreamT& stream) const
    {
        boost::fusion::fold(m_tuple, boost::false_type(), output_visitor< StreamT >(stream, m_delimiter));
    }
};

/*!
 * Stream manipulator for inserting a heterogeneous sequence of elements. Specialization for when there is no delimiter.
 */
template< typename TupleT >
class tuple_manipulator< TupleT, void >
{
private:
    template< typename StreamT >
    struct output_visitor
    {
        typedef void result_type;

        explicit output_visitor(StreamT& stream) BOOST_NOEXCEPT :
            m_stream(stream)
        {
        }

        template< typename T >
        result_type operator() (T const& elem) const
        {
            m_stream << elem;
        }

    private:
        StreamT& m_stream;
    };

private:
    TupleT const& m_tuple;

public:
    //! Initializing constructor
    explicit tuple_manipulator(TupleT const& tuple) BOOST_NOEXCEPT :
        m_tuple(tuple)
    {
    }

    //! The method outputs elements of the sequence
    template< typename StreamT >
    void output(StreamT& stream) const
    {
        boost::fusion::for_each(m_tuple, output_visitor< StreamT >(stream));
    }
};

/*!
 * Stream output operator for \c tuple_manipulator. Outputs every element of the sequence, separated with a delimiter, if one was specified on manipulator construction.
 */
template< typename StreamT, typename TupleT, typename DelimiterT >
inline typename boost::enable_if_c< log::aux::is_ostream< StreamT >::value, StreamT& >::type operator<< (StreamT& strm, tuple_manipulator< TupleT, DelimiterT > const& manip)
{
    if (BOOST_LIKELY(strm.good()))
        manip.output(strm);

    return strm;
}

/*!
 * Tuple manipulator generator function.
 *
 * \param tuple Heterogeneous sequence of elements to output. The sequence must be supported by Boost.Fusion, and its elements must support stream output.
 * \param delimiter Delimiter to separate elements in the output. Optional. If not specified, elements are output without separation.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a tuple and \a delimiter objects must outlive the created manipulator object.
 */
template< typename TupleT, typename DelimiterT >
inline typename boost::enable_if_c<
    is_scalar< DelimiterT >::value,
    tuple_manipulator< TupleT, DelimiterT >
>::type tuple_manip(TupleT const& tuple, DelimiterT delimiter) BOOST_NOEXCEPT
{
    return tuple_manipulator< TupleT, DelimiterT >(tuple, delimiter);
}

/*!
 * Tuple manipulator generator function.
 *
 * \param tuple Heterogeneous sequence of elements to output. The sequence must be supported by Boost.Fusion, and its elements must support stream output.
 * \param delimiter Delimiter to separate elements in the output. Optional. If not specified, elements are output without separation.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a tuple and \a delimiter objects must outlive the created manipulator object.
 */
template< typename TupleT, typename DelimiterT >
inline typename boost::disable_if_c<
    is_scalar< DelimiterT >::value,
    tuple_manipulator< TupleT, DelimiterT >
>::type tuple_manip(TupleT const& tuple, DelimiterT const& delimiter) BOOST_NOEXCEPT
{
    return tuple_manipulator< TupleT, DelimiterT >(tuple, delimiter);
}

/*!
 * Tuple manipulator generator function.
 *
 * \param tuple Heterogeneous sequence of elements to output. The sequence must be supported by Boost.Fusion, and its elements must support stream output.
 * \param delimiter Delimiter to separate elements in the output. Optional. If not specified, elements are output without separation.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note Both \a tuple and \a delimiter objects must outlive the created manipulator object.
 */
template< typename TupleT, typename DelimiterElementT, std::size_t N >
inline tuple_manipulator< TupleT, DelimiterElementT* > tuple_manip(TupleT const& tuple, DelimiterElementT (&delimiter)[N]) BOOST_NOEXCEPT
{
    return tuple_manipulator< TupleT, DelimiterElementT* >(tuple, delimiter);
}

/*!
 * Tuple manipulator generator function.
 *
 * \param tuple Heterogeneous sequence of elements to output. The sequence must be supported by Boost.Fusion, and its elements must support stream output.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note \a tuple object must outlive the created manipulator object.
 */
template< typename TupleT >
inline tuple_manipulator< TupleT, void > tuple_manip(TupleT const& tuple) BOOST_NOEXCEPT
{
    return tuple_manipulator< TupleT, void >(tuple);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_TUPLE_HPP_INCLUDED_

/* tuple.hpp
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
*/