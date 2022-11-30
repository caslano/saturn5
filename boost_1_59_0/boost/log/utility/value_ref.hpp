/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_ref.hpp
 * \author Andrey Semashev
 * \date   27.07.2012
 *
 * The header contains implementation of a value reference wrapper.
 */

#ifndef BOOST_LOG_UTILITY_VALUE_REF_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_VALUE_REF_HPP_INCLUDED_

#include <cstddef>
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/index_of.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/core/addressof.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/detail/value_ref_visitation.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/utility/functional/logical.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/functional/bind_output.hpp>
#include <boost/log/utility/functional/bind_to_log.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>
#include <boost/log/utility/value_ref_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The function object applies the function object to the bound visitable object and argument
template< typename VisitableT, typename FunT >
struct vistation_invoker
{
    typedef typename FunT::result_type result_type;

    vistation_invoker(VisitableT& visitable, result_type const& def_val) : m_visitable(visitable), m_def_val(def_val)
    {
    }

    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        return m_visitable.apply_visitor_or_default(binder1st< FunT, ArgT const& >(FunT(), arg), m_def_val);
    }

private:
    VisitableT& m_visitable;
    result_type m_def_val;
};

//! Traits for testing type compatibility with the reference wrapper
struct singular_ref_compatibility_traits
{
    template< typename T, typename U >
    struct is_compatible
    {
        BOOST_STATIC_CONSTANT(bool, value = false);
    };
    template< typename T >
    struct is_compatible< T, T >
    {
        BOOST_STATIC_CONSTANT(bool, value = true);
    };
};

//! Attribute value reference implementation for a single type case
template< typename T, typename TagT >
class singular_ref
{
public:
    //! Referenced value type
    typedef T value_type;
    //! Tag type
    typedef TagT tag_type;

protected:
    //! Traits for testing type compatibility with the reference wrapper
    typedef singular_ref_compatibility_traits compatibility_traits;

protected:
    //! Pointer to the value
    const value_type* m_ptr;

protected:
    //! Default constructor
    singular_ref() BOOST_NOEXCEPT : m_ptr(NULL)
    {
    }

    //! Initializing constructor
    explicit singular_ref(const value_type* p) BOOST_NOEXCEPT : m_ptr(p)
    {
    }

public:
    //! Returns a pointer to the referred value
    const value_type* operator-> () const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(m_ptr != NULL);
        return m_ptr;
    }

    //! Returns a pointer to the referred value
    const value_type* get_ptr() const BOOST_NOEXCEPT
    {
        return m_ptr;
    }

    //! Returns a pointer to the referred value
    template< typename U >
    typename boost::enable_if_c< compatibility_traits::is_compatible< value_type, U >::value, const U* >::type get_ptr() const BOOST_NOEXCEPT
    {
        return m_ptr;
    }

    //! Returns a reference to the value
    value_type const& operator* () const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(m_ptr != NULL);
        return *m_ptr;
    }

    //! Returns a reference to the value
    value_type const& get() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(m_ptr != NULL);
        return *m_ptr;
    }

    //! Returns a reference to the value
    template< typename U >
    typename boost::enable_if_c< compatibility_traits::is_compatible< value_type, U >::value, U const& >::type get() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(m_ptr != NULL);
        return *m_ptr;
    }


    //! Resets the reference
    void reset() BOOST_NOEXCEPT
    {
        m_ptr = NULL;
    }

    //! Returns the stored type index
    static BOOST_CONSTEXPR unsigned int which()
    {
        return 0u;
    }

    //! Swaps two reference wrappers
    void swap(singular_ref& that) BOOST_NOEXCEPT
    {
        const void* p = m_ptr;
        m_ptr = that.m_ptr;
        that.m_ptr = p;
    }

    //! Applies a visitor function object to the referred value
    template< typename VisitorT >
    typename VisitorT::result_type apply_visitor(VisitorT visitor) const
    {
        BOOST_ASSERT(m_ptr != NULL);
        return visitor(*m_ptr);
    }

    //! Applies a visitor function object to the referred value
    template< typename VisitorT >
    typename boost::enable_if_c< is_void< typename VisitorT::result_type >::value, bool >::type apply_visitor_optional(VisitorT visitor) const
    {
        if (m_ptr)
        {
            visitor(*m_ptr);
            return true;
        }
        else
            return false;
    }

    //! Applies a visitor function object to the referred value
    template< typename VisitorT >
    typename boost::disable_if_c< is_void< typename VisitorT::result_type >::value, optional< typename VisitorT::result_type > >::type apply_visitor_optional(VisitorT visitor) const
    {
        typedef optional< typename VisitorT::result_type > result_type;
        if (m_ptr)
            return result_type(visitor(*m_ptr));
        else
            return result_type();
    }

    //! Applies a visitor function object to the referred value or returns a default value
    template< typename VisitorT, typename DefaultT >
    typename VisitorT::result_type apply_visitor_or_default(VisitorT visitor, DefaultT& def_val) const
    {
        if (m_ptr)
            return visitor(*m_ptr);
        else
            return def_val;
    }

    //! Applies a visitor function object to the referred value or returns a default value
    template< typename VisitorT, typename DefaultT >
    typename VisitorT::result_type apply_visitor_or_default(VisitorT visitor, DefaultT const& def_val) const
    {
        if (m_ptr)
            return visitor(*m_ptr);
        else
            return def_val;
    }
};

//! Traits for testing type compatibility with the reference wrapper
struct variant_ref_compatibility_traits
{
    template< typename T, typename U >
    struct is_compatible
    {
        BOOST_STATIC_CONSTANT(bool, value = (mpl::contains< T, U >::type::value));
    };
};

//! Attribute value reference implementation for multiple types case
template< typename T, typename TagT >
class variant_ref
{
public:
    //! Referenced value type
    typedef T value_type;
    //! Tag type
    typedef TagT tag_type;

protected:
    //! Traits for testing type compatibility with the reference wrapper
    typedef variant_ref_compatibility_traits compatibility_traits;

protected:
    //! Pointer to the value
    const void* m_ptr;
    //! Type index
    unsigned int m_type_idx;

protected:
    //! Default constructor
    variant_ref() BOOST_NOEXCEPT : m_ptr(NULL), m_type_idx(0)
    {
    }

    //! Initializing constructor
    template< typename U >
    explicit variant_ref(const U* p) BOOST_NOEXCEPT : m_ptr(p), m_type_idx(mpl::index_of< value_type, U >::type::value)
    {
    }

public:
    //! Resets the reference
    void reset() BOOST_NOEXCEPT
    {
        m_ptr = NULL;
        m_type_idx = 0;
    }

    //! Returns a pointer to the referred value
    template< typename U >
    typename boost::enable_if_c< compatibility_traits::is_compatible< value_type, U >::value, const U* >::type get_ptr() const BOOST_NOEXCEPT
    {
        if (m_type_idx == static_cast< unsigned int >(mpl::index_of< value_type, U >::type::value))
            return static_cast< const U* >(m_ptr);
        else
            return NULL;
    }

    //! Returns a reference to the value
    template< typename U >
    typename boost::enable_if_c< compatibility_traits::is_compatible< value_type, U >::value, U const& >::type get() const BOOST_NOEXCEPT
    {
        const U* const p = get_ptr< U >();
        BOOST_ASSERT(p != NULL);
        return *p;
    }

    //! Returns the stored type index
    unsigned int which() const BOOST_NOEXCEPT
    {
        return m_type_idx;
    }

    //! Swaps two reference wrappers
    void swap(variant_ref& that) BOOST_NOEXCEPT
    {
        const void* p = m_ptr;
        m_ptr = that.m_ptr;
        that.m_ptr = p;
        unsigned int type_idx = m_type_idx;
        m_type_idx = that.m_type_idx;
        that.m_type_idx = type_idx;
    }

    //! Applies a visitor function object to the referred value
    template< typename VisitorT >
    typename VisitorT::result_type apply_visitor(VisitorT visitor) const
    {
        BOOST_ASSERT(m_ptr != NULL);
        return do_apply_visitor(visitor);
    }

    //! Applies a visitor function object to the referred value
    template< typename VisitorT >
    typename boost::enable_if_c< is_void< typename VisitorT::result_type >::value, bool >::type apply_visitor_optional(VisitorT visitor) const
    {
        if (m_ptr)
        {
            do_apply_visitor(visitor);
            return true;
        }
        else
            return false;
    }

    //! Applies a visitor function object to the referred value
    template< typename VisitorT >
    typename boost::disable_if_c< is_void< typename VisitorT::result_type >::value, optional< typename VisitorT::result_type > >::type apply_visitor_optional(VisitorT visitor) const
    {
        typedef optional< typename VisitorT::result_type > result_type;
        if (m_ptr)
            return result_type(do_apply_visitor(visitor));
        else
            return result_type();
    }

    //! Applies a visitor function object to the referred value or returns a default value
    template< typename VisitorT, typename DefaultT >
    typename VisitorT::result_type apply_visitor_or_default(VisitorT visitor, DefaultT& def_val) const
    {
        if (m_ptr)
            return do_apply_visitor(visitor);
        else
            return def_val;
    }

    //! Applies a visitor function object to the referred value or returns a default value
    template< typename VisitorT, typename DefaultT >
    typename VisitorT::result_type apply_visitor_or_default(VisitorT visitor, DefaultT const& def_val) const
    {
        if (m_ptr)
            return do_apply_visitor(visitor);
        else
            return def_val;
    }

private:
    template< typename VisitorT >
    typename VisitorT::result_type do_apply_visitor(VisitorT& visitor) const
    {
        BOOST_ASSERT(m_type_idx < static_cast< unsigned int >(mpl::size< value_type >::value));
        return apply_visitor_dispatch< value_type, VisitorT >::call(m_ptr, m_type_idx, visitor);
    }
};

template< typename T, typename TagT >
struct value_ref_base
{
    typedef typename mpl::eval_if<
        mpl::and_< mpl::is_sequence< T >, mpl::equal_to< mpl::size< T >, mpl::int_< 1 > > >,
        mpl::front< T >,
        mpl::identity< T >
    >::type value_type;

    typedef typename mpl::if_<
        mpl::is_sequence< value_type >,
        variant_ref< value_type, TagT >,
        singular_ref< value_type, TagT >
    >::type type;
};

} // namespace aux

/*!
 * \brief Reference wrapper for a stored attribute value.
 *
 * The \c value_ref class template provides access to the stored attribute value. It is not a traditional reference wrapper
 * since it may be empty (i.e. refer to no value at all) and it can also refer to values of different types. Therefore its
 * interface and behavior combines features of Boost.Ref, Boost.Optional and Boost.Variant, depending on the use case.
 *
 * The template parameter \c T can be a single type or an MPL sequence of possible types being referred. The reference wrapper
 * will act as either an optional reference or an optional variant of references to the specified types. In any case, the
 * referred values will not be modifiable (i.e. \c value_ref always models a const reference).
 *
 * Template parameter \c TagT is optional. It can be used for customizing the operations on this reference wrapper, such as
 * putting the referred value to log.
 */
template< typename T, typename TagT >
class value_ref :
    public aux::value_ref_base< T, TagT >::type
{
#ifndef BOOST_LOG_DOXYGEN_PASS
public:
    typedef void _has_basic_formatting_ostream_insert_operator;
#endif

private:
    //! Base implementation type
    typedef typename aux::value_ref_base< T, TagT >::type base_type;
    //! Traits for testing type compatibility with the reference wrapper
    typedef typename base_type::compatibility_traits compatibility_traits;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Referenced value type
    typedef typename base_type::value_type value_type;
#else
    //! Referenced value type
    typedef T value_type;
    //! Tag type
    typedef TagT tag_type;
#endif

public:
    /*!
     * Default constructor. Creates a reference wrapper that does not refer to a value.
     */
    BOOST_DEFAULTED_FUNCTION(value_ref(), BOOST_NOEXCEPT {})

    /*!
     * Copy constructor.
     */
    BOOST_DEFAULTED_FUNCTION(value_ref(value_ref const& that), BOOST_NOEXCEPT : base_type(static_cast< base_type const& >(that)) {})

    /*!
     * Initializing constructor. Creates a reference wrapper that refers to the specified value.
     */
    template< typename U >
    explicit value_ref(U const& val
#ifndef BOOST_LOG_DOXYGEN_PASS
// MSVC-8 can't handle SFINAE in this case properly and often wrongly disables this constructor
#if !defined(_MSC_VER) || (_MSC_VER + 0) >= 1500
        , typename boost::enable_if_c< compatibility_traits::BOOST_NESTED_TEMPLATE is_compatible< value_type, U >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()
#endif
#endif
    ) BOOST_NOEXCEPT :
        base_type(boost::addressof(val))
    {
    }

    /*!
     * The operator verifies if the wrapper refers to a value.
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * The operator verifies if the wrapper does not refer to a value.
     */
    bool operator! () const BOOST_NOEXCEPT
    {
        return !this->m_ptr;
    }

    /*!
     * \return \c true if the wrapper does not refer to a value.
     */
    bool empty() const BOOST_NOEXCEPT
    {
        return !this->m_ptr;
    }

    /*!
     * Swaps two reference wrappers
     */
    void swap(value_ref& that) BOOST_NOEXCEPT
    {
        base_type::swap(that);
    }
};

//! Free swap function
template< typename T, typename TagT >
inline void swap(value_ref< T, TagT >& left, value_ref< T, TagT >& right)
{
    left.swap(right);
}

//! Stream output operator
template< typename CharT, typename TraitsT, typename T, typename TagT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, value_ref< T, TagT > const& val)
{
    if (!!val)
        val.apply_visitor(boost::log::bind_output(strm));
    return strm;
}

//! Log formatting operator
template< typename CharT, typename TraitsT, typename AllocatorT, typename T, typename TagT >
inline basic_formatting_ostream< CharT, TraitsT, AllocatorT >& operator<< (basic_formatting_ostream< CharT, TraitsT, AllocatorT >& strm, value_ref< T, TagT > const& val)
{
    if (!!val)
        val.apply_visitor(boost::log::bind_to_log< TagT >(strm));
    return strm;
}

// Equality comparison
template< typename T, typename TagT, typename U >
inline bool operator== (value_ref< T, TagT > const& left, U const& right)
{
    return left.apply_visitor_or_default(binder2nd< equal_to, U const& >(equal_to(), right), false);
}

template< typename U, typename T, typename TagT >
inline bool operator== (U const& left, value_ref< T, TagT > const& right)
{
    return right.apply_visitor_or_default(binder1st< equal_to, U const& >(equal_to(), left), false);
}

template< typename T1, typename TagT1, typename T2, typename TagT2 >
inline bool operator== (value_ref< T1, TagT1 > const& left, value_ref< T2, TagT2 > const& right)
{
    if (!left && !right)
        return true;
    return left.apply_visitor_or_default(aux::vistation_invoker< value_ref< T2, TagT2 >, equal_to >(right, false), false);
}

// Inequality comparison
template< typename T, typename TagT, typename U >
inline bool operator!= (value_ref< T, TagT > const& left, U const& right)
{
    return left.apply_visitor_or_default(binder2nd< not_equal_to, U const& >(not_equal_to(), right), false);
}

template< typename U, typename T, typename TagT >
inline bool operator!= (U const& left, value_ref< T, TagT > const& right)
{
    return right.apply_visitor_or_default(binder1st< not_equal_to, U const& >(not_equal_to(), left), false);
}

template< typename T1, typename TagT1, typename T2, typename TagT2 >
inline bool operator!= (value_ref< T1, TagT1 > const& left, value_ref< T2, TagT2 > const& right)
{
    if (!left && !right)
        return false;
    return left.apply_visitor_or_default(aux::vistation_invoker< value_ref< T2, TagT2 >, not_equal_to >(right, false), false);
}

// Less than ordering
template< typename T, typename TagT, typename U >
inline bool operator< (value_ref< T, TagT > const& left, U const& right)
{
    return left.apply_visitor_or_default(binder2nd< less, U const& >(less(), right), false);
}

template< typename U, typename T, typename TagT >
inline bool operator< (U const& left, value_ref< T, TagT > const& right)
{
    return right.apply_visitor_or_default(binder1st< less, U const& >(less(), left), false);
}

template< typename T1, typename TagT1, typename T2, typename TagT2 >
inline bool operator< (value_ref< T1, TagT1 > const& left, value_ref< T2, TagT2 > const& right)
{
    return left.apply_visitor_or_default(aux::vistation_invoker< value_ref< T2, TagT2 >, less >(right, false), false);
}

// Greater than ordering
template< typename T, typename TagT, typename U >
inline bool operator> (value_ref< T, TagT > const& left, U const& right)
{
    return left.apply_visitor_or_default(binder2nd< greater, U const& >(greater(), right), false);
}

template< typename U, typename T, typename TagT >
inline bool operator> (U const& left, value_ref< T, TagT > const& right)
{
    return right.apply_visitor_or_default(binder1st< greater, U const& >(greater(), left), false);
}

template< typename T1, typename TagT1, typename T2, typename TagT2 >
inline bool operator> (value_ref< T1, TagT1 > const& left, value_ref< T2, TagT2 > const& right)
{
    return left.apply_visitor_or_default(aux::vistation_invoker< value_ref< T2, TagT2 >, greater >(right, false), false);
}

// Less or equal ordering
template< typename T, typename TagT, typename U >
inline bool operator<= (value_ref< T, TagT > const& left, U const& right)
{
    return left.apply_visitor_or_default(binder2nd< less_equal, U const& >(less_equal(), right), false);
}

template< typename U, typename T, typename TagT >
inline bool operator<= (U const& left, value_ref< T, TagT > const& right)
{
    return right.apply_visitor_or_default(binder1st< less_equal, U const& >(less_equal(), left), false);
}

template< typename T1, typename TagT1, typename T2, typename TagT2 >
inline bool operator<= (value_ref< T1, TagT1 > const& left, value_ref< T2, TagT2 > const& right)
{
    if (!left && !right)
        return true;
    return left.apply_visitor_or_default(aux::vistation_invoker< value_ref< T2, TagT2 >, less_equal >(right, false), false);
}

// Greater or equal ordering
template< typename T, typename TagT, typename U >
inline bool operator>= (value_ref< T, TagT > const& left, U const& right)
{
    return left.apply_visitor_or_default(binder2nd< greater_equal, U const& >(greater_equal(), right), false);
}

template< typename U, typename T, typename TagT >
inline bool operator>= (U const& left, value_ref< T, TagT > const& right)
{
    return right.apply_visitor_or_default(binder1st< greater_equal, U const& >(greater_equal(), left), false);
}

template< typename T1, typename TagT1, typename T2, typename TagT2 >
inline bool operator>= (value_ref< T1, TagT1 > const& left, value_ref< T2, TagT2 > const& right)
{
    if (!left && !right)
        return true;
    return left.apply_visitor_or_default(aux::vistation_invoker< value_ref< T2, TagT2 >, greater_equal >(right, false), false);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_VALUE_REF_HPP_INCLUDED_

/* value_ref.hpp
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
*/