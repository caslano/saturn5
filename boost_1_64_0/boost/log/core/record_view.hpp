/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record_view.hpp
 * \author Andrey Semashev
 * \date   09.03.2009
 *
 * This header contains a logging record view class definition.
 */

#ifndef BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_
#define BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#ifndef BOOST_LOG_NO_THREADS
#include <boost/detail/atomic_count.hpp>
#endif // BOOST_LOG_NO_THREADS
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#ifndef BOOST_LOG_DOXYGEN_PASS
class core;
class record;
#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Logging record view class
 *
 * The logging record encapsulates all information related to a single logging statement,
 * in particular, attribute values view and the log message string. The view is immutable,
 * it is implemented as a wrapper around a reference-counted implementation.
 */
class record_view
{
    BOOST_COPYABLE_AND_MOVABLE(record_view)

    friend class core;
    friend class record;

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Private data
    struct private_data;
    friend struct private_data;

    //! Publicly available record data
    struct public_data
    {
        //! Reference counter
#ifndef BOOST_LOG_NO_THREADS
        mutable boost::detail::atomic_count m_ref_counter;
#else
        mutable unsigned int m_ref_counter;
#endif // BOOST_LOG_NO_THREADS

        //! Attribute values view
        attribute_value_set m_attribute_values;

        //! Constructor from the attribute value set
        explicit public_data(BOOST_RV_REF(attribute_value_set) values) BOOST_NOEXCEPT :
            m_ref_counter(1),
            m_attribute_values(boost::move(values))
        {
        }

        //! Destructor
        BOOST_LOG_API static void destroy(const public_data* p) BOOST_NOEXCEPT;

    protected:
        ~public_data() {}

        BOOST_DELETED_FUNCTION(public_data(public_data const&))
        BOOST_DELETED_FUNCTION(public_data& operator= (public_data const&))

        friend void intrusive_ptr_add_ref(const public_data* p) BOOST_NOEXCEPT { ++p->m_ref_counter; }
        friend void intrusive_ptr_release(const public_data* p) BOOST_NOEXCEPT { if (--p->m_ref_counter == 0) public_data::destroy(p); }
    };

private:
    //! A pointer to the log record implementation
    intrusive_ptr< public_data > m_impl;

private:
    //  A private constructor, accessible from record
    explicit record_view(public_data* impl) BOOST_NOEXCEPT : m_impl(impl, false) {}

#endif // BOOST_LOG_DOXYGEN_PASS

public:
    /*!
     * Default constructor. Creates an empty record view that is equivalent to the invalid record handle.
     *
     * \post <tt>!*this == true</tt>
     */
    BOOST_CONSTEXPR record_view() BOOST_NOEXCEPT
#if !defined(BOOST_LOG_NO_CXX11_DEFAULTED_NOEXCEPT_FUNCTIONS) && !defined(BOOST_LOG_NO_CXX11_DEFAULTED_CONSTEXPR_CONSTRUCTORS)
        = default;
#else
    {}
#endif

    /*!
     * Copy constructor
     */
    record_view(record_view const& that) BOOST_NOEXCEPT : m_impl(that.m_impl) {}

    /*!
     * Move constructor. Source record contents unspecified after the operation.
     */
    record_view(BOOST_RV_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~record_view() BOOST_NOEXCEPT {}

    /*!
     * Copy assignment
     */
    record_view& operator= (BOOST_COPY_ASSIGN_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl = that.m_impl;
        return *this;
    }

    /*!
     * Move assignment. Source record contents unspecified after the operation.
     */
    record_view& operator= (BOOST_RV_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
        return *this;
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
     * Equality comparison
     *
     * \param that Comparand
     * \return \c true if both <tt>*this</tt> and \a that identify the same log record or both do not
     *         identify any record, \c false otherwise.
     */
    bool operator== (record_view const& that) const BOOST_NOEXCEPT
    {
        return m_impl == that.m_impl;
    }

    /*!
     * Inequality comparison
     *
     * \param that Comparand
     * \return <tt>!(*this == that)</tt>
     */
    bool operator!= (record_view const& that) const BOOST_NOEXCEPT
    {
        return !operator== (that);
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
    void swap(record_view& that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
    }

    /*!
     * Resets the log record handle. If there are no other handles left, the log record is closed
     * and all resources referenced by the record are released.
     *
     * \post <tt>!*this == true</tt>
     */
    void reset() BOOST_NOEXCEPT
    {
        m_impl.reset();
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
};

/*!
 * A free-standing swap function overload for \c record_view
 */
inline void swap(record_view& left, record_view& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_

/* record_view.hpp
y+5VZ71gn28667/u9v6u2ov7+Z1k+bzVffxcirl3d8OmlGlnuFnXgwaQXZSiz+5Pdn/zqM9+rUDVZx/HNcIN8KTPjtyn6rNnUp/8DSPdVa/67DZ7fNNn31voXZ/9rvP506s+exm30eLOld1JeSqj6ASmkt0wE/cV6AT8lfH6Jae8V113OochzxH8yG4v6nSEV1335ELfdN3ddvum607c45uu+5E93nXdM6m9pijPiQ9SWQ9CybQ2elna69vkVk5pr6fJbrKiB/+C7G541INvKlD14Dfo+guvevB1e3zTg3fc65sefL7zOdWrHrzSHt/04DHOe45XPXj4Xt/04MH7iteD/9P5POpVD/4v9s49wKZqDeD7nHmbQ4MxGK/J+zGjwXgrbyGvkLfGmBlMjZlpHiHSDCrdplJU6ipuKLenSlFUSEUpKkml0uOW5JYrSVHd3/nOd/bsfexh3Nt9/HF2fX7zrdder73W2uvs/e1tz1VsH3z+CxXbB3dtrNg+ePimiu2Dfy71O5K9o262ffDq4n4x+6of2PbBfxT3Q+Xug//sm7PNffAqUv4B5e6Dfyjh48198O9FP3LGffCxvrY+6z74jBcqtg++wXf9n3UfvGTjab/tmXtx1TXMLqmfmmIZN86yzntf3H8OqWE8GmLdCz0s7otse+S3iduws+6Rd3/x9D3yg5LHyrY98mhxS6YtP7btkf8o7of+0D3yPoXO3w8q3mzukRdNLucZ8oWby/1+kMZ3/n7QLZvL/X6QxnP+ls6CzeV+P4h4/7nvB7XVuto9o8xGb3uYB4+38y5m/HVVmCtfKtH6SpD6KjDL3Xar771fp/oiDXu5tZ4lz+KXpO+2+cO2NOOrW4CdVfktwGyrqJe9/i3Mb5gkbfHb73jJ8K/X24hbb7clDdveVZz493BZ/G12nOqKf5HVv411b6u2+I+2+rezpj9L6qeLWV8NJPzjkj9v/98h+iPW+CnW9FdI/DKbBZ0k/DQX8eX7eJ+Ifperkhn/KqOD1vFw8buQ9g4xIhAPUhWJQ+ogDfW7SclIR8SSh07WPLSUem5szjspkm6cWabqW/V3RL1H6yf+ra11blvTd91i/11kgKRfx0y/nqSXKGX0rn+7S/j21vQ6WPP3hYRvbcZvusW+v/im6P3MvtZS9IHW9Gx7zjslvQSzX8VK+E/RG0sa3vvYRuJ2qYxbtSowbvm+XVhguzYDv3v2qA6AA0Lol7AvrJRC3G1yLU7lXVM+fOa7DsNx53lWc6/5uIQpcNfXOv7Lq1JGUo8yaiCNkXZGtPl+aWsJ/3d2bbHlrvXY+hXZZ3U/ZSxmF3GgeQ0cEPf6Zv0mSdr9zPr9TfxDy+7Zxb+V4xhKWcwxIVLKkFfWr8TvMpfDGEq8wG8fXmWe/0LxC3c5jKHEs9n+Jq3C0/Zzm0j+w2x7J19IGUJs7wa0l3D2/alxEm6JGS4SucgSrqa6ZUm4m81wHmSgJVwtdcu1htP+NNoSLlbdiiVcsRnO6z7JEi5O3e6VcNnmeqsWkiXhNrncxjpzz6cuki/uL+O+0XRPQGaL++u4bzXdGyMLxP0d3F+32b+SOqf3+txKXDtPc9vi2n2am8u95zS3nu59p7sZh08/h3Hk9HMYx04/h+vE6em5TlncvPb698ygfmfrN1WvmLfRE3OlJ7yqJzxCv5Eap2GWzdZvpBbfMa9FgN8Gv19oyaueobHi11D9Dmja+FXyhMR5Qj2ekC6esRGemIm2cJFzNI2QErfHHe6pFu6JquHpUNkT2lnCxWu45nM0PdIale6JmBiQlz5mOvU8o8J9fvqNT7VPX2Y/vkcFxjLGHsaUfHMsixQ9T3SP+c3Pq2Rs6+A=
*/