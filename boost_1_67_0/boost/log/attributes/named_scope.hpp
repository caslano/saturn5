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
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
*/