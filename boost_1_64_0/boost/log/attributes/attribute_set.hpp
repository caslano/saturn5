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
St9fk1ChexDJkb3ApgkRfR4Oe0axd5RRVF5lUb6i/WVLjSWdufJs6z32wlL5SSmy8+I6izKl8q8u43dDyQvZK22sfa+dL56Viw24Hy/3OyjdKK0bhfRW9x6n3O7DH+5zpfYeVW7UEl2f0h2rdD+jzB9T41zlhCdory/Zs+sg9+cp3bTwBrIvEy7mL89fvII/9H5b1yudxWF1wxrL/mr4o8peNjp22df21M5A8bKPV4mytzrsel8Ua0uv0Hso2l/7m4tOhNKZFn4Zox09wppar4R118/KQRW3Z32tfa2sOnq/sAwV9iOE3VJ2rw2vcLdImR3CLEqZXekwW6PMjmLWUpldEF4R9hUFBXNV0PU43i+UTlti/E9fYD/xhirO0cqdj3Bni9Kp5fBjtj6HqEyZXW01Y2RiFbFVe2lz59g42dcYN97AjYZK75Jw/dzLPq6BvS6/UOVobvhE8jgfMT772v985e5h3D1Dufsz3MXMuT8e5mWYd1bmReFe481fKvNI517m6rmYLuOWvZx7qIV47kQ/5SbPZJrsr+q6Thjrv17i2n97S/3Ke1I3ak75miB1s1TH+JS6ROp3V50s6Y9byk5L09izuOdz1qW6PPzKNiM361djr2Jn/J3xWWAHRI19cR+ZhVxMZpe640NcUrEeiA+Du5irRke3MU8qO1OsMR778pea4iRl64Aym8zeD76Q9+iyw9BYwuCcD7CroR4XVHk4HplOvqZPlDip83vs707FhUsqPvGocOWkyZ6aEqfhys4oU3zEPdmPTPK3uID6yrlfqdJpZ5w3IPaD20tJj1xl1slx5sDiwiWOfQmnKvOUU+7lHxi3J15qf874oD24dXgl/c7wnzMk+67PCufrGZwGJ9t974mB/eNUvaD6H/OWL12cOze/ON+q3AZ1cbQjDyu7J8J6cTUCudFXx2oVVsvKCsuwHoZtHe3Ln5Vub84ojKN2utHaT70V72sudbGEg9D9wjc1eG9dSU9T+2K3gw0zbPOvwozti6Rrf6VTHNZQ2pdGXN2dad/LMbYvzaWcDFT2loV1YAfdrb5Y6z5fSVAb01H0nlBhHBKerNI7EpMOvpt8S6yWhOqhsK5WA6kT101SbYavqa91UHuTIO3gLGV+p68OObmJ1UW1fC1Zw56i02igMj9ECmHf2SZJu/O0CsewSm3SScxeVmZ9q2yT+qj4tiKVvtJt0kMqnSL1Hpwjlc6TYaY2aZMyu0q1SSscbdKWTN0mqb7CCyosAzzbpEeV+YjwFNqeIe72R9rGZ5VOurH9OYH5a8q8l2f7c0OGP16X0PYkVrOftz7u9Pf17Gc+0dXmmc6eyFLPvHoWVZv2/sTgNu76jODrRzN0m+eYq1P9venMc1q85q54zwnpo+bYrLqxbeMhHyRcfGvjK47u73x8pteclurvAWieu+I9R8g8t8d7zpJ5Tkv159hUd26SeW6P15yr6s+t8prL9LmjLE6W/fdujfHP4SnR75XqvVaZnYFsEv16sf59ExpA+35D2Aw2hokwHraX625ynQqbwBtwrwXcAVvCh2Er+BhsB5+CifAF2Ba+LPftcOVIX8u5T08UMk7ClYGezUwYCbPgGXLdGE6BTeBU2BRmw9ZyLe5Lv4c+lsH96eiFwZkwDs6Co+V6IsyDWTAfZttuwFlyLfuuST+C/o5h37WO6PlgZ1gfJsNWsDtsJ9cpsAfsB1Og2icLjoe9xJ8jvkD7Shgl//oiB2Wd6y0x/vy7B3aD98KhMMZ2T64ny/V0uJfr+fA+eBG8H26CD8JL4UPwCvgofBc+BY/BA/Bj+DRsgd9/hJ3gQZgMn4Np8HmYAQ/BmfAFmA+PwKXwNbgWvg7Xw7c=
*/