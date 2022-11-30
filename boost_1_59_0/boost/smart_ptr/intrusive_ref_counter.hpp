/*
 *          Copyright Andrey Semashev 2007 - 2013.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   intrusive_ref_counter.hpp
 * \author Andrey Semashev
 * \date   12.03.2009
 *
 * This header contains a reference counter class for \c intrusive_ptr.
 */

#ifndef BOOST_SMART_PTR_INTRUSIVE_REF_COUNTER_HPP_INCLUDED_
#define BOOST_SMART_PTR_INTRUSIVE_REF_COUNTER_HPP_INCLUDED_

#include <boost/config.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(_MSC_VER)
#pragma warning(push)
// This is a bogus MSVC warning, which is flagged by friend declarations of intrusive_ptr_add_ref and intrusive_ptr_release in intrusive_ref_counter:
// 'name' : the inline specifier cannot be used when a friend declaration refers to a specialization of a function template
// Note that there is no inline specifier in the declarations.
#pragma warning(disable: 4396)
#endif

namespace boost {

namespace sp_adl_block {

/*!
 * \brief Thread unsafe reference counter policy for \c intrusive_ref_counter
 *
 * The policy instructs the \c intrusive_ref_counter base class to implement
 * a reference counter suitable for single threaded use only. Pointers to the same
 * object with this kind of reference counter must not be used by different threads.
 */
struct thread_unsafe_counter
{
    typedef unsigned int type;

    static unsigned int load(unsigned int const& counter) BOOST_SP_NOEXCEPT
    {
        return counter;
    }

    static void increment(unsigned int& counter) BOOST_SP_NOEXCEPT
    {
        ++counter;
    }

    static unsigned int decrement(unsigned int& counter) BOOST_SP_NOEXCEPT
    {
        return --counter;
    }
};

/*!
 * \brief Thread safe reference counter policy for \c intrusive_ref_counter
 *
 * The policy instructs the \c intrusive_ref_counter base class to implement
 * a thread-safe reference counter, if the target platform supports multithreading.
 */
struct thread_safe_counter
{
    typedef boost::detail::atomic_count type;

    static unsigned int load(boost::detail::atomic_count const& counter) BOOST_SP_NOEXCEPT
    {
        return static_cast< unsigned int >(static_cast< long >(counter));
    }

    static void increment(boost::detail::atomic_count& counter) BOOST_SP_NOEXCEPT
    {
        ++counter;
    }

    static unsigned int decrement(boost::detail::atomic_count& counter) BOOST_SP_NOEXCEPT
    {
        return static_cast< unsigned int >(--counter);
    }
};

template< typename DerivedT, typename CounterPolicyT = thread_safe_counter >
class intrusive_ref_counter;

template< typename DerivedT, typename CounterPolicyT >
void intrusive_ptr_add_ref(const intrusive_ref_counter< DerivedT, CounterPolicyT >* p) BOOST_SP_NOEXCEPT;
template< typename DerivedT, typename CounterPolicyT >
void intrusive_ptr_release(const intrusive_ref_counter< DerivedT, CounterPolicyT >* p) BOOST_SP_NOEXCEPT;

/*!
 * \brief A reference counter base class
 *
 * This base class can be used with user-defined classes to add support
 * for \c intrusive_ptr. The class contains a reference counter defined by the \c CounterPolicyT.
 * Upon releasing the last \c intrusive_ptr referencing the object
 * derived from the \c intrusive_ref_counter class, operator \c delete
 * is automatically called on the pointer to the object.
 *
 * The other template parameter, \c DerivedT, is the user's class that derives from \c intrusive_ref_counter.
 */
template< typename DerivedT, typename CounterPolicyT >
class intrusive_ref_counter
{
private:
    //! Reference counter type
    typedef typename CounterPolicyT::type counter_type;
    //! Reference counter
    mutable counter_type m_ref_counter;

public:
    /*!
     * Default constructor
     *
     * \post <tt>use_count() == 0</tt>
     */
    intrusive_ref_counter() BOOST_SP_NOEXCEPT : m_ref_counter(0)
    {
    }

    /*!
     * Copy constructor
     *
     * \post <tt>use_count() == 0</tt>
     */
    intrusive_ref_counter(intrusive_ref_counter const&) BOOST_SP_NOEXCEPT : m_ref_counter(0)
    {
    }

    /*!
     * Assignment
     *
     * \post The reference counter is not modified after assignment
     */
    intrusive_ref_counter& operator= (intrusive_ref_counter const&) BOOST_SP_NOEXCEPT { return *this; }

    /*!
     * \return The reference counter
     */
    unsigned int use_count() const BOOST_SP_NOEXCEPT
    {
        return CounterPolicyT::load(m_ref_counter);
    }

protected:
    /*!
     * Destructor
     */
    BOOST_DEFAULTED_FUNCTION(~intrusive_ref_counter(), {})

    friend void intrusive_ptr_add_ref< DerivedT, CounterPolicyT >(const intrusive_ref_counter< DerivedT, CounterPolicyT >* p) BOOST_SP_NOEXCEPT;
    friend void intrusive_ptr_release< DerivedT, CounterPolicyT >(const intrusive_ref_counter< DerivedT, CounterPolicyT >* p) BOOST_SP_NOEXCEPT;
};

template< typename DerivedT, typename CounterPolicyT >
inline void intrusive_ptr_add_ref(const intrusive_ref_counter< DerivedT, CounterPolicyT >* p) BOOST_SP_NOEXCEPT
{
    CounterPolicyT::increment(p->m_ref_counter);
}

template< typename DerivedT, typename CounterPolicyT >
inline void intrusive_ptr_release(const intrusive_ref_counter< DerivedT, CounterPolicyT >* p) BOOST_SP_NOEXCEPT
{
    if (CounterPolicyT::decrement(p->m_ref_counter) == 0)
        delete static_cast< const DerivedT* >(p);
}

} // namespace sp_adl_block

using sp_adl_block::intrusive_ref_counter;
using sp_adl_block::thread_unsafe_counter;
using sp_adl_block::thread_safe_counter;

} // namespace boost

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif // BOOST_SMART_PTR_INTRUSIVE_REF_COUNTER_HPP_INCLUDED_

/* intrusive_ref_counter.hpp
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
*/