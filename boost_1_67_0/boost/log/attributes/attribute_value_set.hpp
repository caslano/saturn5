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