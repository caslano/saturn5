/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record.hpp
 * \author Andrey Semashev
 * \date   09.03.2009
 *
 * This header contains a logging record class definition.
 */

#ifndef BOOST_LOG_CORE_RECORD_HPP_INCLUDED_
#define BOOST_LOG_CORE_RECORD_HPP_INCLUDED_

#include <boost/move/core.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

class core;

/*!
 * \brief Logging record class
 *
 * The logging record encapsulates all information related to a single logging statement,
 * in particular, attribute values view and the log message string. The record can be updated before pushing
 * for further processing to the logging core.
 */
class record
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(record)

    friend class core;

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Private data
    typedef record_view::public_data public_data;

private:
    //! A pointer to the log record implementation
    public_data* m_impl;

private:
    //  A private constructor, accessible from core
    BOOST_CONSTEXPR explicit record(public_data* impl) BOOST_NOEXCEPT : m_impl(impl) {}

#endif // BOOST_LOG_DOXYGEN_PASS

public:
    /*!
     * Default constructor. Creates an empty record that is equivalent to the invalid record handle.
     *
     * \post <tt>!*this == true</tt>
     */
    BOOST_CONSTEXPR record() BOOST_NOEXCEPT : m_impl(NULL) {}

    /*!
     * Move constructor. Source record contents unspecified after the operation.
     */
    record(BOOST_RV_REF(record) that) BOOST_NOEXCEPT : m_impl(that.m_impl)
    {
        that.m_impl = NULL;
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~record() BOOST_NOEXCEPT
    {
        reset();
    }

    /*!
     * Move assignment. Source record contents unspecified after the operation.
     */
    record& operator= (BOOST_RV_REF(record) that) BOOST_NOEXCEPT
    {
        swap(static_cast< record& >(that));
        return *this;
    }

    /*!
     * \return A reference to the set of attribute values attached to this record
     *
     * \pre <tt>!!*this</tt>
     */
    attribute_value_set& attribute_values() BOOST_NOEXCEPT
    {
        return m_impl->m_attribute_values;
    }

    /*!
     * \return A reference to the set of attribute values attached to this record
     *
     * \pre <tt>!!*this</tt>
     */
    attribute_value_set const& attribute_values() const BOOST_NOEXCEPT
    {
        return m_impl->m_attribute_values;
    }

    /*!
     * Conversion to an unspecified boolean type
     *
     * \return \c true, if the <tt>*this</tt> identifies a log record, \c false, if the <tt>*this</tt> is not valid
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Inverted conversion to an unspecified boolean type
     *
     * \return \c false, if the <tt>*this</tt> identifies a log record, \c true, if the <tt>*this</tt> is not valid
     */
    bool operator! () const BOOST_NOEXCEPT
    {
        return !m_impl;
    }

    /*!
     * Swaps two handles
     *
     * \param that Another record to swap with
     * <b>Throws:</b> Nothing
     */
    void swap(record& that) BOOST_NOEXCEPT
    {
        public_data* p = m_impl;
        m_impl = that.m_impl;
        that.m_impl = p;
    }

    /*!
     * Resets the log record handle. If there are no other handles left, the log record is closed
     * and all resources referenced by the record are released.
     *
     * \post <tt>!*this == true</tt>
     */
    void reset() BOOST_NOEXCEPT
    {
        if (m_impl)
        {
            public_data::destroy(m_impl);
            m_impl = NULL;
        }
    }

    /*!
     * Attribute value lookup.
     *
     * \param name Attribute name.
     * \return An \c attribute_value, non-empty if it is found, empty otherwise.
     */
    attribute_value_set::mapped_type operator[] (attribute_value_set::key_type name) const
    {
        return m_impl->m_attribute_values[name];
    }

    /*!
     * Attribute value lookup.
     *
     * \param keyword Attribute keyword.
     * \return A \c value_ref with extracted attribute value if it is found, empty \c value_ref otherwise.
     */
    template< typename DescriptorT, template< typename > class ActorT >
    typename result_of::extract< typename expressions::attribute_keyword< DescriptorT, ActorT >::value_type, DescriptorT >::type
    operator[] (expressions::attribute_keyword< DescriptorT, ActorT > const& keyword) const
    {
        return m_impl->m_attribute_values[keyword];
    }

    /*!
     * The function ensures that the log record does not depend on any thread-specific data. Then the record contents
     * are used to construct a \c record_view which is returned from the function. The record is no longer valid after the call.
     *
     * \pre <tt>!!*this</tt>
     * \post <tt>!*this</tt>
     * \returns The record view that contains all attribute values from the original record.
     */
    BOOST_LOG_API record_view lock();
};

/*!
 * A free-standing swap function overload for \c record
 */
inline void swap(record& left, record& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_RECORD_HPP_INCLUDED_

/* record.hpp
zZpztnUuCDld2eXucF+zQu0rMuV09wnN2tsaqq/gYtfqZ1Ke+ilr9YvJrqnXtfpRJLdRuaeXJbstRgjqQm5Puv40m/Mqy+nGk5XbNO1Oc19Mdy/jVF27e4HlitP/PbqL70NSfldSed6ptLsNZHdA0f99R3YX5PFM2UP0Sz61X/G+Vzfn+KvMX3TzjXfc6z1e19YyNOOZbtxbYR0fIacrry7u8Sbp5jlZ1nqCnC68+O3u+/t19Vlxp9v+/hR5H3AqxVfOJpebLp82Sn+oUm46vdY893ErWaeHqU7pD1HGN53+K3qHb2vfpSm8VL9g4xY/uS91oHTH4z2aw8r6XAWSf1Ua3yl2cT9oTeWyS+xnupuug5X7gfw8W5/cq4r3PtvT9TJlbX2kZR/DBjFfkWTS3Mt0hrueJ1VXVle2afquZixYvt37+vRq6rsN2I7X/RxlKem0FiKfe8mupt3b+nRnfp6R4/iJ0hFmREr6m1vJrhrq6y1lXSWI2sF7NofuePrv0I/rdMdR2U6Pmaw7HsO646yCIt1xggfdsX2/R90x/HvWHT9Q4FF3DH++6Y7r7PNNd3zLHu+64wLKxy3KGSVDCul+ht5Z32hrqbMnya2y0i62kV1rRa9cADuE61Gv/DjlNVfolT+l6y896pULC1S98pO7adwS4XXBtaxXPkjyVQM86ZWn7fZNr/zyHt/0yo12e9crN9/nm1552F7qe9ArRyh65ccoLe0xz/hA0StPIvl7veqVo/f5plf+rdA3vXLVvb7plX/eq9crR0syo6n89tlLG5Pts+2JcJP26pHbKruNxra/2uVnw5/2ueuYv4WdVcdcjsJ4vVgdcw/qC+WUud1dlPZwpKdoDlOP7FogjDpGouX8rVHktlDRPweR3Qmv+ucN+znd8nlOVBehiv55GNldwNh3v6J/vkb2//Sof/6a3MsL/fN8KpOxNn/sKcg25xg2W1MxL3ioQNU//0iyMUL//CS53x7gSf+cDXlZ/7y0QNU/r6TrtgGe9M8vF6j65yN0HRXgSf/8VoGqf36PrksHeNI/XyX3SK/6553OMdSr/jlhn2/65/17i9c/z6V0vetR/1x+n6p/XlWg6p/HUvgVeZ6M6z2q/jmP5JsFWPXPcn9LJT9R6G9RqPHLynmAd5BbFWX+Pp7s5it66XCyO+5VL31+N7/7LO/hoTzeTnrpGlJfH06yryFdy4zV0I8/iTN6ttgrKLrpKJI5ouimfyG704puOoDS94FH3fQ8Ksds6KbHCN30YxTOOPSX0WaO+YGokyAKy+5VN712r2+66TyKp7RX3fTMQt900813+6abLlfom2568X533XQX8huiPMfOovzWwd62Q4pu+i6SneNRN72zQNVN78Y1wgnwpptuttc33XRsoW+66XXOPu1VN11mj2+66aV7fNNN31Oo103LfaQJyaTZKhgRNvnedJ3KoAtqIg4n8dsUnWk38jNF0VN3JLslip7aOh85Re3nuq208ZVNvl9OoHYQrr5PQnlsbMi667UUR1PMeoO4ffC+fwo3ie6jcjo/JPkIRX89k2QHedVfbyW/mzBHWqzor3+lcnkH98xdiv76RZKP9aq/XkZycUpecyivwcr8eNA+Cs90ponzQ2nfhHFruV1O03qy/xx1dUjRWT9M9n0VnfX9FNeHis56LtlletRZ+1OePxD3AhuFe6/QWVej65e86qxL7/ZNZ72I5II96qznUT/eLXTWASSf6VFnva5A1Vl/Qdc3vOqs6xf6prN+fq9vOuvlzvmkV511472+6awPUXjBSvv8C9kNQPts71Fn/SbKSz7ve0EB1afQWV+g64EeddZbClSd9fN03TDAm856IeU=
*/