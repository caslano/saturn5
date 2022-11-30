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
#include <boost/current_function.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/log/detail/config.hpp>
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
         * \param t Scope name type.
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