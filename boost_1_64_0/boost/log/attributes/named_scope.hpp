/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file
 * \author Andrey Semashev
 * \date   24.06.2007
 *
 * The header contains implementation of named scope container and an attribute that allows to
 * put the named scope to log. A number of convenience macros are also provided.
 */

#ifndef BOOST_LOG_ATTRIBUTES_NAMED_SCOPE_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_NAMED_SCOPE_HPP_INCLUDED_

#include <ostream>
#include <memory>
#include <iterator>
#include <cstddef>
#include <boost/log/detail/config.hpp>
#include <boost/current_function.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/log/utility/string_literal.hpp>
#include <boost/log/utility/unique_identifier_name.hpp>
#include <boost/log/utility/unused_variable.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/detail/allocator_traits.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

namespace aux {

    //! Double-linked list node
    struct named_scope_list_node
    {
        mutable named_scope_list_node* _m_pPrev;
        mutable named_scope_list_node* _m_pNext;

        named_scope_list_node() BOOST_NOEXCEPT { _m_pPrev = _m_pNext = this; }
    };

} // namespace aux

/*!
 * \brief The structure contains all information about a named scope
 *
 * The named scope entries are stored as elements of \c basic_named_scope_list container, which
 * in turn can be acquired either from the \c basic_named_scope attribute value or from a thread-local
 * instance.
 */
struct named_scope_entry
    //! \cond
    : public aux::named_scope_list_node
    //! \endcond
{
    /*!
     * \brief Scope entry type
     *
     * Describes scope name specifics
     */
    enum scope_name_type
    {
        general,   //!< The scope name contains some unstructured string that should not be interpreted by the library
        function   //!< The scope name contains a function signature
    };

    /*!
     * The scope name (e.g. a function signature)
     */
    string_literal scope_name;
    /*!
     * The source file name
     */
    string_literal file_name;
    /*!
     * The line number in the source file
     */
    unsigned int line;
    /*!
     * The scope name type
     */
    scope_name_type type;

    /*!
     * Initializing constructor
     *
     * \post <tt>scope_name == sn && file_name == fn && line == ln</tt>
     *
     * \b Throws: Nothing.
     */
    named_scope_entry(string_literal const& sn, string_literal const& fn, unsigned int ln, scope_name_type t = general) BOOST_NOEXCEPT :
        scope_name(sn),
        file_name(fn),
        line(ln),
        type(t)
    {
    }
};

/*!
 * \brief The class implements the list of scopes
 *
 * The scope list provides a read-only access to a doubly-linked list of scopes.
 */
class named_scope_list
    //! \cond
    : protected std::allocator< named_scope_entry >
    //! \endcond
{
public:
    //! Allocator type
    typedef std::allocator< named_scope_entry > allocator_type;

    //  Standard types
    typedef log::aux::allocator_traits< allocator_type >::value_type value_type;
    typedef log::aux::allocator_traits< allocator_type >::size_type size_type;
    typedef log::aux::allocator_traits< allocator_type >::difference_type difference_type;
    typedef log::aux::allocator_traits< allocator_type >::pointer pointer;
    typedef log::aux::allocator_traits< allocator_type >::const_pointer const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;

#ifndef BOOST_LOG_DOXYGEN_PASS

protected:
    //! Iterator class
#ifndef BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
    template< bool fConstV > class iter;
    template< bool fConstV > friend class iter;
#endif
    template< bool fConstV >
    class iter
    {
        friend class iter< !fConstV >;

    public:
        //  Standard typedefs
        typedef named_scope_list::difference_type difference_type;
        typedef named_scope_list::value_type value_type;
        typedef typename boost::conditional<
            fConstV,
            named_scope_list::const_reference,
            named_scope_list::reference
        >::type reference;
        typedef typename boost::conditional<
            fConstV,
            named_scope_list::const_pointer,
            named_scope_list::pointer
        >::type pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

    public:
        //  Constructors
        iter() : m_pNode(NULL) {}
        explicit iter(aux::named_scope_list_node* pNode) : m_pNode(pNode) {}
        iter(iter< false > const& that) : m_pNode(that.m_pNode) {}

        //! Assignment
        template< bool f >
        iter& operator= (iter< f > const& that)
        {
            m_pNode = that.m_pNode;
            return *this;
        }

        //  Comparison
        template< bool f >
        bool operator== (iter< f > const& that) const { return (m_pNode == that.m_pNode); }
        template< bool f >
        bool operator!= (iter< f > const& that) const { return (m_pNode != that.m_pNode); }

        //  Modification
        iter& operator++ ()
        {
            m_pNode = m_pNode->_m_pNext;
            return *this;
        }
        iter& operator-- ()
        {
            m_pNode = m_pNode->_m_pPrev;
            return *this;
        }
        iter operator++ (int)
        {
            iter tmp(*this);
            m_pNode = m_pNode->_m_pNext;
            return tmp;
        }
        iter operator-- (int)
        {
            iter tmp(*this);
            m_pNode = m_pNode->_m_pPrev;
            return tmp;
        }

        //  Dereferencing
        pointer operator-> () const { return static_cast< pointer >(m_pNode); }
        reference operator* () const { return *static_cast< pointer >(m_pNode); }

    private:
        aux::named_scope_list_node* m_pNode;
    };

public:
    typedef iter< true > const_iterator;
    typedef iter< false > iterator;
    typedef std::reverse_iterator< const_iterator > const_reverse_iterator;
    typedef std::reverse_iterator< iterator > reverse_iterator;

protected:
    //! The root node of the container
    aux::named_scope_list_node m_RootNode;
    //! The size of the container
    size_type m_Size;
    //! The flag shows if the contained elements are dynamically allocated
    bool m_fNeedToDeallocate;

#else // BOOST_LOG_DOXYGEN_PASS

    /*!
     * A constant iterator to the sequence of scopes. Complies to bidirectional iterator requirements.
     */
    typedef implementation_defined const_iterator;
    /*!
     * An iterator to the sequence of scopes. Complies to bidirectional iterator requirements.
     */
    typedef implementation_defined iterator;
    /*!
     * A constant reverse iterator to the sequence of scopes. Complies to bidirectional iterator requirements.
     */
    typedef implementation_defined const_reverse_iterator;
    /*!
     * A reverse iterator to the sequence of scopes. Complies to bidirectional iterator requirements.
     */
    typedef implementation_defined reverse_iterator;

#endif // BOOST_LOG_DOXYGEN_PASS

public:
    /*!
     * Default constructor
     *
     * \post <tt>empty() == true</tt>
     */
    named_scope_list() : m_Size(0), m_fNeedToDeallocate(false) {}
    /*!
     * Copy constructor
     *
     * \post <tt>std::equal(begin(), end(), that.begin()) == true</tt>
     */
    BOOST_LOG_API named_scope_list(named_scope_list const& that);
    /*!
     * Destructor. Destroys the stored entries.
     */
    BOOST_LOG_API ~named_scope_list();

    /*!
     * Assignment operator
     *
     * \post <tt>std::equal(begin(), end(), that.begin()) == true</tt>
     */
    named_scope_list& operator= (named_scope_list const& that)
    {
        if (this != &that)
        {
            named_scope_list tmp(that);
            swap(tmp);
        }
        return *this;
    }

    /*!
     * \return Constant iterator to the first element of the container.
     */
    const_iterator begin() const { return const_iterator(m_RootNode._m_pNext); }
    /*!
     * \return Constant iterator to the after-the-last element of the container.
     */
    const_iterator end() const { return const_iterator(const_cast< aux::named_scope_list_node* >(&m_RootNode)); }
    /*!
     * \return Constant iterator to the last element of the container.
     */
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    /*!
     * \return Constant iterator to the before-the-first element of the container.
     */
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    /*!
     * \return The number of elements in the container
     */
    size_type size() const { return m_Size; }
    /*!
     * \return true if the container is empty and false otherwise
     */
    bool empty() const { return (m_Size == 0); }

    /*!
     * Swaps two instances of the container
     */
    BOOST_LOG_API void swap(named_scope_list& that);

    /*!
     * \return Last pushed scope entry
     */
    const_reference back() const { return *rbegin(); }
    /*!
     * \return First pushed scope entry
     */
    const_reference front() const { return *begin(); }
};

//! Stream output operator
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, named_scope_list const& sl)
{
    if (strm.good())
    {
        named_scope_list::const_iterator it = sl.begin(), end = sl.end();
        if (it != end)
        {
            strm << it->scope_name.c_str();
            for (++it; it != end; ++it)
                strm << "->" << it->scope_name.c_str();
        }
    }
    return strm;
}

/*!
 * \brief A class of an attribute that holds stack of named scopes of the current thread
 *
 * The basic_named_scope attribute is essentially a hook to the thread-specific instance of
 * scope list. This means that the attribute will generate different values if get_value is
 * called in different threads. The attribute generates value with stored type
 * <tt>basic_named_scope_list< CharT ></tt>.
 *
 * The attribute class can also be used to gain access to the scope stack instance, e.g. to
 * get its copy or to push or pop a scope entry. However, it is highly not recommended to
 * maintain scope list manually. Use \c BOOST_LOG_NAMED_SCOPE or \c BOOST_LOG_FUNCTION macros instead.
 */
class BOOST_LOG_API named_scope :
    public attribute
{
public:
    //! Scope names stack (the attribute value type)
    typedef named_scope_list value_type;
    //! Scope entry
    typedef value_type::value_type scope_entry;

    //! Sentry object class to automatically push and pop scopes
    struct sentry
    {
        /*!
         * Constructor. Pushes the specified scope to the end of the thread-local list of scopes.
         *
         * \param sn Scope name.
         * \param fn File name, in which the scope is located.
         * \param ln Line number in the file.
         */
        sentry(string_literal const& sn, string_literal const& fn, unsigned int ln, scope_entry::scope_name_type t = scope_entry::general) BOOST_NOEXCEPT :
            m_Entry(sn, fn, ln, t)
        {
            named_scope::push_scope(m_Entry);
        }

        /*!
         * Destructor. Removes the last pushed scope from the thread-local list of scopes.
         */
        ~sentry() BOOST_NOEXCEPT
        {
            named_scope::pop_scope();
        }

        BOOST_DELETED_FUNCTION(sentry(sentry const&))
        BOOST_DELETED_FUNCTION(sentry& operator= (sentry const&))

    private:
        scope_entry m_Entry;
    };

private:
    //! Attribute implementation class
    struct BOOST_SYMBOL_VISIBLE impl;

public:
    /*!
     * Constructor. Creates an attribute.
     */
    named_scope();
    /*!
     * Constructor for casting support
     */
    explicit named_scope(cast_source const& source);

    /*!
     * The method pushes the scope to the back of the current thread's scope list
     *
     * \b Throws: Nothing.
     */
    static void push_scope(scope_entry const& entry) BOOST_NOEXCEPT;
    /*!
     * The method pops the last pushed scope from the current thread's scope list
     *
     * \b Throws: Nothing.
     */
    static void pop_scope() BOOST_NOEXCEPT;

    /*!
     *  \return The current thread's list of scopes
     *
     *  \note The returned reference is only valid until the current thread ends. The scopes in the
     *        returned container may change if the execution scope is changed (i.e. either \c push_scope
     *        or \c pop_scope is called). User has to copy the stack if he wants to keep it intact regardless
     *        of the execution scope.
     */
    static value_type const& get_scopes();
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_NAMED_SCOPE_INTERNAL(var, name, file, line, type)\
    BOOST_LOG_UNUSED_VARIABLE(::boost::log::attributes::named_scope::sentry, var, (name, file, line, type));

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * Macro for scope markup. The specified scope name is pushed to the end of the current thread scope list.
 */
#define BOOST_LOG_NAMED_SCOPE(name)\
    BOOST_LOG_NAMED_SCOPE_INTERNAL(BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_named_scope_sentry_), name, __FILE__, __LINE__, ::boost::log::attributes::named_scope_entry::general)

/*!
 * Macro for function scope markup. The scope name is constructed with help of compiler and contains the current function signature.
 * The scope name is pushed to the end of the current thread scope list.
 *
 * Not all compilers have support for this macro. The exact form of the scope name may vary from one compiler to another.
 */
#define BOOST_LOG_FUNCTION()\
    BOOST_LOG_NAMED_SCOPE_INTERNAL(BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_named_scope_sentry_), BOOST_CURRENT_FUNCTION, __FILE__, __LINE__, ::boost::log::attributes::named_scope_entry::function)

/*!
 * Macro for function scope markup. The scope name is constructed with help of compiler and contains the current function name. It may be shorter than what \c BOOST_LOG_FUNCTION macro produces.
 * The scope name is pushed to the end of the current thread scope list.
 *
 * Not all compilers have support for this macro. The exact form of the scope name may vary from one compiler to another.
 */
#if defined(_MSC_VER) || defined(__GNUC__)
#define BOOST_LOG_FUNC() BOOST_LOG_NAMED_SCOPE(__FUNCTION__)
#else
#define BOOST_LOG_FUNC() BOOST_LOG_FUNCTION()
#endif

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_NAMED_SCOPE_HPP_INCLUDED_

/* named_scope.hpp
fzPBg7ieA74IzgdfApeAL4PPgofAzeAr4C7wMLgfPAIeBY+C74Ovgp+Bx8CvwNdBR2beAMuDb4EVwLfBOPA9sCl4ArwDPAmOAD8ER4IfgQ+An4FLwVPgTvAL8Dh4GrwAngXtaE/nwErgebABeBGMA78Gk8FvwKHg9+AD4I/gU+DPYD54HXwZ/BU8CdpQPpdAO1jKD3UJRoKBYF0wGGwOhoK3gZcd5Q2G43o0WA6cCJYH7wMjQHHmEutosk2qZ+XMpel8RtkDYH1wJtgSXAO2Ax8E+4JzwMHgXPBv7D6Prx/n66fAeeDfwUfBjeB8cAu4ANzJcrvBx8ED4CLwFXAx+Ab4BPgB+CR4HnwK/BpcBvoj/SvAKuDTYE/wGbAP+Cw4CFwNjgbzwEwQ8fFZK7zPDqys6ScxkHOwChgNxgp/vC8MrKbxd4X9fQdWBa9K/sLYX3WNv9Ps7wxYDTwrp5P9VdH4u8D+LoIx4CX2t17sOUHe2V85mBXs72c+G+o3sCwIQZx5BIAxoA1MBSuDrcEYsANYBewIlgK7gYFgPzAIHAiGgDlgefAhsBI4D4wGn+DwnubwVnN4V8AssVcD4x6nNxhmBKf3fqTTBGfwmUQPgBXAmWA1cBZ4CzgbbAQ+CCaDfwObgw+B7cA5YBdwLsjlxHsiMLZoymkhx/sYWAV8nONbC1YHF4GJ4BNgB/ApDn8JeAe4FLwLXAYOApeDw8EV4GhwJTgHXAVuAleD28E8cD+4BkR/EGdZtXbtaQBrcHr9YZI4vTmc3klcTpO5nKaA3O64vHnNHRykKe93+D5xAgwD3wdrgF+BNcGPwFvBj8Fm4Cku38/B3uAZsD94DhzI/sT9ieMN17TnyxzvtxzvFRAGcvhxvnvxdQjMWPY3lPM9TDqzqgI4AowGR3K7GAsmgeO4fWRw+kdx+keD3cF7uf4gx2dt8too8BnHL5+1uZnjzwdjwOfBxuB2MA3cwe3gNXAA+A8ul91gFlgIzgf3g0+CL4IbwUPgUfAw+A77/5D9f8TXn/K164yqLB7X+nI65TOqqmN8oLYD1gbrgM3AemBzsC7Yja+7g7XAPnztqr9THH6Ypv4a8XjUGCwLxon7Dq8PAT019500vu+04ftOWzAenAAmg53AO8DbwTvZfgDYBRwOdgXHg93AiWB3MJfl7gPvAGeBvcC5YG9wCdgHXAUOAreDg/n+MxQ8AQ4Hz4Hp4E9gBhjKZ35WAceAjcBxYAI4HmwGZoIdwSywK4h08Fl0vDYAcrtWzqLbCLky4FYwEXye62U72AHcwfXzBtgDLOD78W4ujz3gWHAvmAXuBx8CD4LLwJfA58BD4H7wMOf3KPga+A/wOHgMfB98HTwFHgfPcrznwXzwMl/zGd2sO0db4XzJZ3Snmc521xQsAzYDK4DNwWpgC7Au2JLvB0OE7hl1xeEFwfTh8DpweLeBVcCOHE4PsDrYCUwEO/N9qyvYBewO9mI5Hk+hA/Y8nsZzPAmc7kROdxLHkwzy+MD6SZS1Znx4EHI2cA5YCZwLJoGPgE3AZ8A0cD7YHVwAjmP7THAROAVczPfVJ8HHwSXgMnApuBFcDu4EV4KF4CrwAIfD7Q36Pc/jaHXObw3Ob03Oby0wGqwDNgIbcPobgsngLWAzsC7YDqzH+agP3sFyrjO2w7icVnD88hnb6ZBzMAOk91bAOmAm2BjMAtuCE7k+s8Eh4CRwLDgZzAangLngNHA6+BfwPnAUuAS8F1zO9q52cIrbQaymHdzF6eoH2sH+YBR4N7e/AaA4M5af49tpxt8TNqf/D8BI8EOwIV8ng5/yePwZ2Ar8CGzL1+jrjrP+vJ7xhzP95LP8xDl+BQ+IM/s=
*/