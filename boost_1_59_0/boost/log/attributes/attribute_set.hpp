/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_set.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * This header contains definition of the attribute set container.
 */

#ifndef BOOST_LOG_ATTRIBUTE_SET_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTE_SET_HPP_INCLUDED_

#include <cstddef>
#include <utility>
#include <iterator>
#include <boost/move/core.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

class attribute_set;
class attribute_value_set;

namespace aux {

//! Reference proxy object to implement \c operator[]
class attribute_set_reference_proxy
{
private:
    //! Key type
    typedef attribute_name key_type;
    //! Mapped attribute type
    typedef attribute mapped_type;

private:
    attribute_set* const m_pContainer;
    const key_type m_key;

public:
    //! Constructor
    explicit attribute_set_reference_proxy(attribute_set* pContainer, key_type const& key) BOOST_NOEXCEPT :
        m_pContainer(pContainer),
        m_key(key)
    {
    }

    //! Conversion operator (would be invoked in case of reading from the container)
    BOOST_FORCEINLINE operator mapped_type() const BOOST_NOEXCEPT
    {
        return read_mapped_value();
    }
    //! Assignment operator (would be invoked in case of writing to the container)
    mapped_type& operator= (mapped_type const& val) const;

private:
    //! Reads the referenced mapped value from the container
    mapped_type read_mapped_value() const BOOST_NOEXCEPT;
};

} // namespace aux

/*!
 * \brief An attribute set class.
 *
 * An attribute set is an associative container with attribute name as a key and
 * pointer to the attribute as a mapped value. The container allows storing only one element for each distinct
 * key value. In most regards attribute set container provides interface similar to \c std::unordered_map.
 * However, there are differences in \c operator[] semantics and a number of optimizations with regard to iteration.
 * Besides, attribute names are stored as a read-only <tt>attribute_name</tt>'s instead of \c std::string,
 * which saves memory and CPU time.
 */
class attribute_set
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(attribute_set)

    friend class attribute_value_set;
    friend class aux::attribute_set_reference_proxy;

public:
    //! Key type
    typedef attribute_name key_type;
    //! Mapped attribute type
    typedef attribute mapped_type;

    //! Value type
    typedef std::pair< const key_type, mapped_type > value_type;
    //! Reference type
    typedef value_type& reference;
    //! Const reference type
    typedef value_type const& const_reference;
    //! Pointer type
    typedef value_type* pointer;
    //! Const pointer type
    typedef value_type const* const_pointer;
    //! Size type
    typedef std::size_t size_type;
    //! Difference type
    typedef std::ptrdiff_t difference_type;

private:
    //! \cond

    //! Implementation
    struct implementation;
    friend struct implementation;

    //! A base class for the container nodes
    struct node_base
    {
        node_base* m_pPrev;
        node_base* m_pNext;

        node_base();

        BOOST_DELETED_FUNCTION(node_base(node_base const&))
        BOOST_DELETED_FUNCTION(node_base& operator= (node_base const&))
    };

    //! Container elements
    struct node;
    friend struct node;
    struct node :
        public node_base
    {
        value_type m_Value;

        node(key_type const& key, mapped_type const& data);
    };

    //! Iterator class
#ifndef BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
    template< bool fConstV > class iter;
    template< bool fConstV > friend class iter;
#endif
    template< bool fConstV >
    class iter
    {
        friend class iter< !fConstV >;
        friend class attribute_set;

    public:
        //  Standard typedefs
        typedef attribute_set::difference_type difference_type;
        typedef attribute_set::value_type value_type;
        typedef typename boost::conditional<
            fConstV,
            attribute_set::const_reference,
            attribute_set::reference
        >::type reference;
        typedef typename boost::conditional<
            fConstV,
            attribute_set::const_pointer,
            attribute_set::pointer
        >::type pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

    public:
        //  Constructors
        BOOST_CONSTEXPR iter() BOOST_NOEXCEPT : m_pNode(NULL) {}
        explicit iter(node_base* pNode) BOOST_NOEXCEPT : m_pNode(pNode) {}
#if !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
        template< bool fOtherConstV, typename = typename boost::enable_if_c< !fOtherConstV && fOtherConstV != fConstV >::type >
        iter(iter< fOtherConstV > const& that) BOOST_NOEXCEPT : m_pNode(that.m_pNode) {}
#else
        template< bool fOtherConstV >
        iter(iter< fOtherConstV > const& that, typename boost::enable_if_c< !fOtherConstV && fOtherConstV != fConstV, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) BOOST_NOEXCEPT :
            m_pNode(that.m_pNode)
        {
        }
#endif

        //! Assignment
        template< bool fOtherConstV >
        typename boost::enable_if_c< !fOtherConstV && fOtherConstV != fConstV, iter& >::type operator= (iter< fOtherConstV > const& that) BOOST_NOEXCEPT
        {
            m_pNode = that.m_pNode;
            return *this;
        }

        //  Comparison
        template< bool fOtherConstV >
        typename boost::enable_if_c< !fOtherConstV || fOtherConstV == fConstV, bool >::type operator== (iter< fOtherConstV > const& that) const BOOST_NOEXCEPT { return (m_pNode == that.m_pNode); }
        template< bool fOtherConstV >
        typename boost::enable_if_c< !fOtherConstV || fOtherConstV == fConstV, bool >::type operator!= (iter< fOtherConstV > const& that) const BOOST_NOEXCEPT { return (m_pNode != that.m_pNode); }

        //  Modification
        iter& operator++ () BOOST_NOEXCEPT
        {
            m_pNode = m_pNode->m_pNext;
            return *this;
        }
        iter& operator-- () BOOST_NOEXCEPT
        {
            m_pNode = m_pNode->m_pPrev;
            return *this;
        }
        iter operator++ (int) BOOST_NOEXCEPT
        {
            iter tmp(*this);
            m_pNode = m_pNode->m_pNext;
            return tmp;
        }
        iter operator-- (int) BOOST_NOEXCEPT
        {
            iter tmp(*this);
            m_pNode = m_pNode->m_pPrev;
            return tmp;
        }

        //  Dereferencing
        pointer operator-> () const BOOST_NOEXCEPT { return &(static_cast< node* >(m_pNode)->m_Value); }
        reference operator* () const BOOST_NOEXCEPT { return static_cast< node* >(m_pNode)->m_Value; }

        node_base* base() const BOOST_NOEXCEPT { return m_pNode; }

    private:
        node_base* m_pNode;
    };

    //! \endcond

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Iterator type
    typedef iter< false > iterator;
    //! Const iterator type
    typedef iter< true > const_iterator;
#else
    /*!
     * Iterator type. The iterator complies to the bidirectional iterator requirements.
     */
    typedef implementation_defined iterator;
    /*!
     * Constant iterator type. The iterator complies to the bidirectional iterator requirements with read-only capabilities.
     */
    typedef implementation_defined const_iterator;
#endif // BOOST_LOG_DOXYGEN_PASS

private:
    //! Pointer to implementation
    implementation* m_pImpl;

public:
    /*!
     * Default constructor.
     *
     * \post <tt>empty() == true</tt>
     */
    BOOST_LOG_API attribute_set();

    /*!
     * Copy constructor.
     *
     * \post <tt>size() == that.size() && std::equal(begin(), end(), that.begin()) == true</tt>
     */
    BOOST_LOG_API attribute_set(attribute_set const& that);

    /*!
     * Move constructor
     */
    attribute_set(BOOST_RV_REF(attribute_set) that) BOOST_NOEXCEPT : m_pImpl(that.m_pImpl)
    {
        that.m_pImpl = NULL;
    }

    /*!
     * Destructor. All stored references to attributes are released.
     */
    BOOST_LOG_API ~attribute_set() BOOST_NOEXCEPT;

    /*!
     * Copy assignment operator.
     *
     * \post <tt>size() == that.size() && std::equal(begin(), end(), that.begin()) == true</tt>
     */
    attribute_set& operator= (attribute_set that) BOOST_NOEXCEPT
    {
        this->swap(that);
        return *this;
    }

    /*!
     * Swaps two instances of the container.
     *
     * \b Throws: Nothing.
     */
    void swap(attribute_set& that) BOOST_NOEXCEPT
    {
        implementation* const p = m_pImpl;
        m_pImpl = that.m_pImpl;
        that.m_pImpl = p;
    }

    /*!
     * \return Iterator to the first element of the container.
     */
    BOOST_LOG_API iterator begin() BOOST_NOEXCEPT;
    /*!
     * \return Iterator to the after-the-last element of the container.
     */
    BOOST_LOG_API iterator end() BOOST_NOEXCEPT;
    /*!
     * \return Constant iterator to the first element of the container.
     */
    BOOST_LOG_API const_iterator begin() const BOOST_NOEXCEPT;
    /*!
     * \return Constant iterator to the after-the-last element of the container.
     */
    BOOST_LOG_API const_iterator end() const BOOST_NOEXCEPT;

    /*!
     * \return Number of elements in the container.
     */
    BOOST_LOG_API size_type size() const BOOST_NOEXCEPT;
    /*!
     * \return true if there are no elements in the container, false otherwise.
     */
    bool empty() const BOOST_NOEXCEPT { return (this->size() == 0); }

    /*!
     * The method finds the attribute by name.
     *
     * \param key Attribute name.
     * \return Iterator to the found element or end() if the attribute with such name is not found.
     */
    BOOST_LOG_API iterator find(key_type key) BOOST_NOEXCEPT;
    /*!
     * The method finds the attribute by name.
     *
     * \param key Attribute name.
     * \return Iterator to the found element or \c end() if the attribute with such name is not found.
     */
    const_iterator find(key_type key) const BOOST_NOEXCEPT
    {
        return const_iterator(const_cast< attribute_set* >(this)->find(key));
    }
    /*!
     * The method counts the number of the attribute occurrences in the container. Since there can be only one
     * attribute with a particular key, the method always return 0 or 1.
     *
     * \param key Attribute name.
     * \return The number of times the attribute is found in the container.
     */
    size_type count(key_type key) const BOOST_NOEXCEPT { return size_type(this->find(key) != this->end()); }

    /*!
     * Combined lookup/insertion operator. The operator semantics depends on the further usage of the returned reference.
     * \li If the reference is used as an assignment target, the assignment expression is equivalent to element insertion,
     *     where the element is composed of the second argument of the \c operator[] as a key and the second argument of assignment
     *     as a mapped value.
     * \li If the returned reference is used in context where a conversion to the mapped type is required,
     *     the result of the conversion is equivalent to the mapped value found with the second argument of the \c operator[] as a key,
     *     if such an element exists in the container, or a default-constructed mapped value, if an element does not exist in the
     *     container.
     *
     * \param key Attribute name.
     * \return A smart reference object of unspecified type.
     */
    aux::attribute_set_reference_proxy operator[] (key_type key) BOOST_NOEXCEPT
    {
        return aux::attribute_set_reference_proxy(this, key);
    }
    /*!
     * Lookup operator
     *
     * \param key Attribute name.
     * \return If an element with the corresponding attribute name is found in the container, its mapped value
     *         is returned. Otherwise a default-constructed mapped value is returned.
     */
    mapped_type operator[] (key_type key) const BOOST_NOEXCEPT
    {
        const_iterator it = this->find(key);
        if (it != end())
            return it->second;
        else
            return mapped_type();
    }

    /*!
     * Insertion method
     *
     * \param key Attribute name.
     * \param data Pointer to the attribute. Must not be NULL.
     * \returns A pair of values. If second is true, the insertion succeeded and the first component points to the
     *          inserted element. Otherwise the first component points to the element that prevents insertion.
     */
    BOOST_LOG_API std::pair< iterator, bool > insert(key_type key, mapped_type const& data);

    /*!
     * Insertion method
     *
     * \param value An element to be inserted.
     * \returns A pair of values. If second is true, the insertion succeeded and the first component points to the
     *          inserted element. Otherwise the first component points to the element that prevents insertion.
     */
    std::pair< iterator, bool > insert(const_reference value)
    {
        return this->insert(value.first, value.second);
    }

    /*!
     * Mass insertion method.
     *
     * \param begin A forward iterator that points to the first element to be inserted.
     * \param end A forward iterator that points to the after-the-last element to be inserted.
     */
    template< typename FwdIteratorT >
    void insert(FwdIteratorT begin, FwdIteratorT end)
    {
        for (; begin != end; ++begin)
            this->insert(*begin);
    }

    /*!
     * Mass insertion method with ability to acquire iterators to the inserted elements.
     *
     * \param begin A forward iterator that points to the first element to be inserted.
     * \param end A forward iterator that points to the after-the-last element to be inserted.
     * \param out An output iterator that receives results of insertion of the elements
     */
    template< typename FwdIteratorT, typename OutputIteratorT >
    void insert(FwdIteratorT begin, FwdIteratorT end, OutputIteratorT out)
    {
        for (; begin != end; ++begin, ++out)
            *out = this->insert(*begin);
    }

    /*!
     * The method erases all attributes with the specified name
     *
     * \post All iterators to the erased elements become invalid.
     * \param key Attribute name.
     * \return Tne number of erased elements
     */
    BOOST_LOG_API size_type erase(key_type key) BOOST_NOEXCEPT;
    /*!
     * The method erases the specified attribute
     *
     * \post All iterators to the erased element become invalid.
     * \param it A valid iterator to the element to be erased.
     * \return Tne number of erased elements
     */
    BOOST_LOG_API void erase(iterator it) BOOST_NOEXCEPT;
    /*!
     * The method erases all attributes within the specified range
     *
     * \pre \a end is reachable from \a begin with a finite number of increments.
     * \post All iterators to the erased elements become invalid.
     * \param begin An iterator that points to the first element to be erased.
     * \param end An iterator that points to the after-the-last element to be erased.
     */
    BOOST_LOG_API void erase(iterator begin, iterator end) BOOST_NOEXCEPT;

    /*!
     * The method removes all elements from the container
     *
     * \post <tt>empty() == true</tt>
     */
    BOOST_LOG_API void clear() BOOST_NOEXCEPT;
};

/*!
 * Free swap overload
 */
inline void swap(attribute_set& left, attribute_set& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

namespace aux {

//! Reads the referenced mapped value from the container
inline attribute_set_reference_proxy::mapped_type attribute_set_reference_proxy::read_mapped_value() const BOOST_NOEXCEPT
{
    attribute_set::iterator it = m_pContainer->find(m_key);
    if (it != m_pContainer->end())
        return it->second;
    else
        return mapped_type();
}

//! Assignment operator (would be invoked in case of writing to the container)
inline attribute_set_reference_proxy::mapped_type& attribute_set_reference_proxy::operator= (mapped_type const& val) const
{
    std::pair< attribute_set::iterator, bool > res = m_pContainer->insert(m_key, val);
    if (!res.second)
        res.first->second = val;
    return res.first->second;
}

} // namespace aux

#ifndef BOOST_LOG_DOXYGEN_PASS
inline attribute& attribute::operator= (aux::attribute_set_reference_proxy const& that) BOOST_NOEXCEPT
{
    attribute attr = that;
    this->swap(attr);
    return *this;
}
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTE_SET_HPP_INCLUDED_

/* attribute_set.hpp
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
*/