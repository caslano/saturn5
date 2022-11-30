/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_value_set.hpp
 * \author Andrey Semashev
 * \date   21.04.2007
 *
 * This header file contains definition of attribute value set. The set is constructed from
 * three attribute sets (global, thread-specific and source-specific) and contains attribute
 * values.
 */

#ifndef BOOST_LOG_ATTRIBUTE_VALUE_SET_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTE_VALUE_SET_HPP_INCLUDED_

#include <cstddef>
#include <utility>
#include <iterator>
#include <boost/move/core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute_set.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief A set of attribute values
 *
 * The set of attribute values is an associative container with attribute name as a key and
 * a pointer to attribute value object as a mapped type. This is a collection of elements with unique
 * keys, that is, there can be only one attribute value with a given name in the set. With respect to
 * read-only capabilities, the set interface is close to \c std::unordered_map.
 *
 * The set is designed to be only capable of adding elements to it. Once added, the attribute value
 * cannot be removed from the set.
 *
 * An instance of attribute value set can be constructed from three attribute sets. The constructor attempts to
 * accommodate values of all attributes from the sets. The situation when a same-named attribute is found
 * in more than one attribute set is possible. This problem is solved on construction of the value set: the three
 * attribute sets have different priorities when it comes to solving conflicts.
 *
 * From the library perspective the three source attribute sets are global, thread-specific and source-specific
 * attributes, with the latter having the highest priority. This feature allows to override attributes of wider scopes
 * with the more specific ones.
 *
 * For sake of performance, the attribute values are not immediately acquired from attribute sets at construction.
 * Instead, on-demand acquisition is performed either on iterator dereferencing or on call to the \c freeze method.
 * Once acquired, the attribute value stays within the set until its destruction. This nuance does not affect
 * other set properties, such as size or lookup ability. The logging core automatically freezes the set
 * at the right point, so users should not be bothered unless they manually create attribute value sets.
 *
 * \note The attribute sets that were used for the value set construction must not be modified or destroyed
 *       until the value set is frozen. Otherwise the behavior is undefined.
 */
class attribute_value_set
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(attribute_value_set)

public:
    //! Key type
    typedef attribute_name key_type;
    //! Mapped attribute type
    typedef attribute_value mapped_type;

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
    //! Pointer difference type
    typedef std::ptrdiff_t difference_type;

#ifndef BOOST_LOG_DOXYGEN_PASS

private:
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
        bool m_DynamicallyAllocated;

        node(key_type const& key, mapped_type& data, bool dynamic);
    };

public:
    class const_iterator;
    friend class const_iterator;
    class const_iterator
    {
    public:
        //  Standard typedefs
        typedef attribute_value_set::difference_type difference_type;
        typedef attribute_value_set::value_type value_type;
        typedef attribute_value_set::const_reference reference;
        typedef attribute_value_set::const_pointer pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

    public:
        //  Constructors
        BOOST_CONSTEXPR const_iterator() : m_pNode(NULL), m_pContainer(NULL) {}
        explicit const_iterator(node_base* n, attribute_value_set* cont) BOOST_NOEXCEPT :
            m_pNode(n),
            m_pContainer(cont)
        {
        }

        //  Comparison
        bool operator== (const_iterator const& that) const BOOST_NOEXCEPT
        {
            return (m_pNode == that.m_pNode);
        }
        bool operator!= (const_iterator const& that) const BOOST_NOEXCEPT
        {
            return (m_pNode != that.m_pNode);
        }

        //  Modification
        const_iterator& operator++ ()
        {
            m_pContainer->freeze();
            m_pNode = m_pNode->m_pNext;
            return *this;
        }
        const_iterator& operator-- ()
        {
            m_pContainer->freeze();
            m_pNode = m_pNode->m_pPrev;
            return *this;
        }
        const_iterator operator++ (int)
        {
            const_iterator tmp(*this);
            m_pContainer->freeze();
            m_pNode = m_pNode->m_pNext;
            return tmp;
        }
        const_iterator operator-- (int)
        {
            const_iterator tmp(*this);
            m_pContainer->freeze();
            m_pNode = m_pNode->m_pPrev;
            return tmp;
        }

        //  Dereferencing
        pointer operator-> () const BOOST_NOEXCEPT { return &(static_cast< node* >(m_pNode)->m_Value); }
        reference operator* () const BOOST_NOEXCEPT { return static_cast< node* >(m_pNode)->m_Value; }

    private:
        node_base* m_pNode;
        attribute_value_set* m_pContainer;
    };

#else

    /*!
     * Constant iterator type with bidirectional capabilities.
     */
    typedef implementation_defined const_iterator;

#endif // BOOST_LOG_DOXYGEN_PASS

private:
    //! Pointer to the container implementation
    implementation* m_pImpl;

public:
    /*!
     * Default constructor
     *
     * The constructor creates an empty set which can be filled later by subsequent
     * calls of \c insert method. Optionally, the amount of storage reserved for elements
     * to be inserted may be passed to the constructor.
     * The constructed set is frozen.
     *
     * \param reserve_count Number of elements to reserve space for.
     */
    BOOST_LOG_API explicit attribute_value_set(size_type reserve_count = 8);

    /*!
     * Move constructor
     */
    attribute_value_set(BOOST_RV_REF(attribute_value_set) that) BOOST_NOEXCEPT : m_pImpl(that.m_pImpl)
    {
        that.m_pImpl = NULL;
    }

    /*!
     * The constructor adopts three attribute sets into the value set.
     * The \a source_attrs attributes have the greatest preference when a same-named
     * attribute is found in several sets, \a global_attrs has the least.
     * The constructed set is not frozen.
     *
     * \param source_attrs A set of source-specific attributes.
     * \param thread_attrs A set of thread-specific attributes.
     * \param global_attrs A set of global attributes.
     * \param reserve_count Amount of elements to reserve space for, in addition to the elements in the three attribute sets provided.
     */
    BOOST_LOG_API attribute_value_set(
        attribute_set const& source_attrs,
        attribute_set const& thread_attrs,
        attribute_set const& global_attrs,
        size_type reserve_count = 8);

    /*!
     * The constructor adopts three attribute sets into the value set.
     * The \a source_attrs attributes have the greatest preference when a same-named
     * attribute is found in several sets, \a global_attrs has the least.
     * The constructed set is not frozen.
     *
     * \pre The \a source_attrs set is frozen.
     *
     * \param source_attrs A set of source-specific attributes.
     * \param thread_attrs A set of thread-specific attributes.
     * \param global_attrs A set of global attributes.
     * \param reserve_count Amount of elements to reserve space for, in addition to the elements in the three attribute sets provided.
     */
    BOOST_LOG_API attribute_value_set(
        attribute_value_set const& source_attrs,
        attribute_set const& thread_attrs,
        attribute_set const& global_attrs,
        size_type reserve_count = 8);

    /*!
     * The constructor adopts three attribute sets into the value set.
     * The \a source_attrs attributes have the greatest preference when a same-named
     * attribute is found in several sets, \a global_attrs has the least.
     * The constructed set is not frozen.
     *
     * \pre The \a source_attrs set is frozen.
     *
     * \param source_attrs A set of source-specific attributes.
     * \param thread_attrs A set of thread-specific attributes.
     * \param global_attrs A set of global attributes.
     * \param reserve_count Amount of elements to reserve space for, in addition to the elements in the three attribute sets provided.
     */
    attribute_value_set(
        BOOST_RV_REF(attribute_value_set) source_attrs,
        attribute_set const& thread_attrs,
        attribute_set const& global_attrs,
        size_type reserve_count = 8) : m_pImpl(NULL)
    {
        construct(static_cast< attribute_value_set& >(source_attrs), thread_attrs, global_attrs, reserve_count);
    }

    /*!
     * Copy constructor.
     *
     * \pre The original set is frozen.
     * \post The constructed set is frozen, <tt>std::equal(begin(), end(), that.begin()) == true</tt>
     */
    BOOST_LOG_API attribute_value_set(attribute_value_set const& that);

    /*!
     * Destructor. Releases all referenced attribute values.
     */
    BOOST_LOG_API ~attribute_value_set() BOOST_NOEXCEPT;

    /*!
     * Assignment operator
     */
    attribute_value_set& operator= (attribute_value_set that) BOOST_NOEXCEPT
    {
        this->swap(that);
        return *this;
    }

    /*!
     * Swaps two sets
     *
     * \b Throws: Nothing.
     */
    void swap(attribute_value_set& that) BOOST_NOEXCEPT
    {
        implementation* const p = m_pImpl;
        m_pImpl = that.m_pImpl;
        that.m_pImpl = p;
    }

    /*!
     * \return Iterator to the first element of the set.
     */
    BOOST_LOG_API const_iterator begin() const;
    /*!
     * \return Iterator to the after-the-last element of the set.
     */
    BOOST_LOG_API const_iterator end() const;

    /*!
     * \return Number of elements in the set.
     */
    BOOST_LOG_API size_type size() const;
    /*!
     * \return \c true if there are no elements in the container, \c false otherwise.
     */
    bool empty() const { return (this->size() == 0); }

    /*!
     * The method finds the attribute value by name.
     *
     * \param key Attribute name.
     * \return Iterator to the found element or \c end() if the attribute with such name is not found.
     */
    BOOST_LOG_API const_iterator find(key_type key) const;

    /*!
     * Alternative lookup syntax.
     *
     * \param key Attribute name.
     * \return A pointer to the attribute value if it is found with \a key, default-constructed mapped value otherwise.
     */
    mapped_type operator[] (key_type key) const
    {
        const_iterator it = this->find(key);
        if (it != this->end())
            return it->second;
        else
            return mapped_type();
    }

    /*!
     * Alternative lookup syntax.
     *
     * \param keyword Attribute keyword.
     * \return A \c value_ref with extracted attribute value if it is found, empty \c value_ref otherwise.
     */
    template< typename DescriptorT, template< typename > class ActorT >
    typename result_of::extract< typename expressions::attribute_keyword< DescriptorT, ActorT >::value_type, DescriptorT >::type
    operator[] (expressions::attribute_keyword< DescriptorT, ActorT > const& keyword) const
    {
        typedef typename expressions::attribute_keyword< DescriptorT, ActorT >::value_type attr_value_type;
        typedef typename result_of::extract< attr_value_type, DescriptorT >::type result_type;
        const_iterator it = this->find(keyword.get_name());
        if (it != this->end())
            return it->second.extract< attr_value_type, DescriptorT >();
        else
            return result_type();
    }

    /*!
     * The method counts the number of the attribute value occurrences in the set. Since there can be only one
     * attribute value with a particular key, the method always return 0 or 1.
     *
     * \param key Attribute name.
     * \return The number of times the attribute value is found in the container.
     */
    size_type count(key_type key) const { return size_type(this->find(key) != this->end()); }

    /*!
     * The method acquires values of all adopted attributes.
     *
     * \post The set is frozen.
     */
    BOOST_LOG_API void freeze();

    /*!
     * Inserts an element into the set. The complexity of the operation is amortized constant.
     *
     * \pre The set is frozen.
     *
     * \param key The attribute name.
     * \param mapped The attribute value.
     *
     * \returns An iterator to the inserted element and \c true if insertion succeeded. Otherwise,
     *          if the set already contains a same-named attribute value, iterator to the
     *          existing element and \c false.
     */
    BOOST_LOG_API std::pair< const_iterator, bool > insert(key_type key, mapped_type const& mapped);

    /*!
     * Inserts an element into the set. The complexity of the operation is amortized constant.
     *
     * \pre The set is frozen.
     *
     * \param value The attribute name and value.
     *
     * \returns An iterator to the inserted element and \c true if insertion succeeded. Otherwise,
     *          if the set already contains a same-named attribute value, iterator to the
     *          existing element and \c false.
     */
    std::pair< const_iterator, bool > insert(const_reference value) { return this->insert(value.first, value.second); }

    /*!
     * Mass insertion method. The complexity of the operation is linear to the number of elements inserted.
     *
     * \pre The set is frozen.
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
     * The complexity of the operation is linear to the number of elements inserted times the complexity
     * of filling the \a out iterator.
     *
     * \pre The set is frozen.
     *
     * \param begin A forward iterator that points to the first element to be inserted.
     * \param end A forward iterator that points to the after-the-last element to be inserted.
     * \param out An output iterator that receives results of insertion of the elements.
     */
    template< typename FwdIteratorT, typename OutputIteratorT >
    void insert(FwdIteratorT begin, FwdIteratorT end, OutputIteratorT out)
    {
        for (; begin != end; ++begin, ++out)
            *out = this->insert(*begin);
    }

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Constructs the object by moving from \a source_attrs. This function is mostly needed to maintain ABI stable between C++03 and C++11.
    BOOST_LOG_API void construct(
        attribute_value_set& source_attrs,
        attribute_set const& thread_attrs,
        attribute_set const& global_attrs,
        size_type reserve_count);
#endif // BOOST_LOG_DOXYGEN_PASS
};

/*!
 * Free swap overload
 */
inline void swap(attribute_value_set& left, attribute_value_set& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTE_VALUE_SET_HPP_INCLUDED_

/* attribute_value_set.hpp
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
*/