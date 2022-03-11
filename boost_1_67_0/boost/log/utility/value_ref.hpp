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