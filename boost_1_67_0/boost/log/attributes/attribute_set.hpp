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
/BoI1LOzkUmzrdkwQOBAKTejm2xkTsXDSPBJVIG/HJhr4MBcTLWq4Ku92R9lcaNS3F+A2fAuC0q50VyzC6KzaUwwlBJZRzefCx99h0SLQ1Gd+6xViXILrw9sZY7nGI+N3ypDY/0UDQdj3aq/IzF5/6vnb66QwtAmkRNyrJBlhDMOmI1WVcdqDyHso1nsQ7SF2qDuYAh1ABq5fSaoaypqzCItvm84J6m9kID5k3X5a5F0JgwzVyzYKeVpewqHjh5wJ99knDRhxY7yK8funV5RoOCHPg5g3f7fzhyuT0QgXYc7s8RSQAaj1JfGtvq2kQs1x5oJts5AJI4c31b5aKlJg1CSvSsBAPsKoE1k/XkWVYXkI777LcbnYjeyQFKut8RVIJPMLeSj8UkLB5jDAvjT21/KclaiqVqke2aczoM4+m/MDPAtlSNzD9NbPILLXgZhlP1dbJJrhu3zauP6qrmeNNYjQKlNts7V5y+NNzMpjcn4bvxiy8n/8dOR6wguSg/SAFIGh8yoPW7kSwwyQGfyUfRWOZxNH0nosUIVjdQoDpkKOr0SMrPVrMgfZNmo3DCH7G8iS3bcz2utI8w79k6N5lwCJNbiqtGOfZK5A6EP5KW7TMekU7afd+HXEgWV0T1nfqHb50wfLbduzxu/0ZuSuC+Fj1HTKdskIjZ4uJDDNxj+jFPom9os0GpjpRb6xX3h6rU1UqVUGFfycsxjSSca6Q+yMhjPwxDc7B3oEEU88d/EuO04WJDtbRbD9oGwZmF9rQ2+lFiWWX8PjJ9Xm1VyOFka2KfaWBQJ3VZf+9xWgALwP8+qtBnPad3n5qhYO6HjQ5tTy3ZKRaRpW7Z2znocVb+CaiWi7AjQKLvcoOx2VQavVS20oT6EVXQ83jrnLjG5kpQ2VExgvNmWuAkBK7if5JMbiSOYMB1G7Ej1NC5p0ORuVGphpqHLH/aQrQiW1QsPJUCviWuQZ/U/DLuT1vZ6wlqtG1i0uH2zl/TACu1uFDaWIYFMd9/hJeuzFCLmsOVJEH5PSRSbScUEje4S8cVPnAK3hayGHSKhutYTi4cD00PqiKTnzKQjyL20C4RX5f9e2E8qG/YQnVnFtVGHm4BH2ptfrjvc0qIOLgOMePGch8E7Adrdh/YqlJBPEDwa2ue+s1teh9COxq7f5a0OeyeHDhuzDUW5XkNr5DmL+bTSwiXTFVd5MgnKT2ZEUsHr0yBhqagu3YfB61NcvBWyJ7lpSR2YkjV2htu44k7nH7tXJErdGO97nmr4oV1kzMTMzFnQ3KzBTjQgxIu0eIbUI9TU1zUoVew3C62Di74lJak9J1jZOwmFz9riUCvvUgH4tG5+jzdah0E5tBz6lOp4a7uweC8+LeiqL4UIGdsESp8q6TBhOUkbiY/1krZKUUtqVvQTKLhoTHFz6OXosWygpVWwsFSAd7GEm71da70fBuK4Xb3cs0k8z7g8V+noi5QbLlxsjGrJqsfud0d6O8i/xoyyz3I4kNjLYL4VSjxMBWQYs08Jwz5mmDHL/ycwgiGbUJwTPxyFg+NMvVk5zgwMc5TBL20Za0OfYWJLZOK6IR1rh2lC2qRoTh7RqqI+2meC3GW3nyof0Q4nHpDcxGC+eFkhFYPODYdYY6JFgb5FrCAnbzIvsNCoeJ/JU1lZujXx0HA9f7RFTH74cPCfvN62zVpEKN5DadycGbAjZICe3BeyEbaxhW91V8fmNtScNrLGXe0lwMZZ9OEawXpQXIqk3jwoLiUFLlPWNSWGr6W5bSuIJdfOf3qDDzd4xLfqaUWKLjvQ+9KHkKYkzTXxl3wfSkGmioScm0Bjdf0xHPcuBrGdEDPMJgXYpPjeDOWIoIXJU+dggBpEzy0nS9rCsIpL2ZqGC72xactL5OzAv1YphvVyjrHhmtH62Es26m7TXqVD/bg5wGO66aMMtmPVPeJmy2t5Ed4PrEcI/BS8I67pcgMPISxGRgmzia/p6QqxJ9Jkk9GSyTrD1TJJ6RzFrCN+0dQouoJ9kQbMKdVRzx+tEkrSJz2X9NEsW8dEP862Wmss25ED3dr/TRDvPxTQ6OoByNg6wRurZ0M3ZeU4i2FYZOPXYPrRhi/oJywb1L6Vnsst9EI0Yh+hETkLGyi4SMK7Bf3TqEkpU81qglQbKyBLX2xxYdcsXodMy4bQQ7RnggZsr+RdpCd8yjn9ZNyPSNBveuBgcnB6ln9++XaOn0i3mX25/Fco4iOa0GxklPQIdvRUeiBVinVFwDjQM8HloFEc+IwZaagJGCCfRjO8yt3LYUOM9Fgj8KDqEAMMJRLUM+y/bbZdEcElOTDwT6aHUl5MoL6vldjJ1b6tmrUNHHjg6723iCmN1DPACUI3Btk3J9OGk4USP6GAhpFadfJXmlNIumpEVi0+QdweF1ubxctsRtQ6x7RB36PdqqB3Sbh9h2lpUcrlOPjylGSVSWrv+XjuxxxKIw/kOqgmaVfp1hoPeMrBz6t/fgd83zwWAkWyve+JTS64wQIPJFGKyZJJ045O+fTFLrz5q1ZJz5186GkeHKvOYPRHKgXH9FbgQuTwnZYOd3v5NCZcBqRV3HCBPhZ/FYVLppJ61RwKkcNCpu0UJiTRbgvziQiyfZzRAtRln0IJZdn+9rxscX+LEd31K53tKl0lOoGPCua6YrZL99OePEvofqfCUG8lzeLqict0rqfhAqUYKhikIV2y/ngtyykkOGzpzJ+1yEe4CSKT3VOpHAlQPeioKC2j5b+R3wmLpP0Jm3B00Qw17YUAzqaimw0vqH4OqVQjK8JaHKQJhWr91aU977MOzJ7hBEBNgsW6AtLMw9mlrFb78c7IfN+CpMQUg1lmSkdlb/KXha8BQKNcbyBP+JYaOy1/46Ugt/NWlbKBuQWTFPjtsAXZEZgQl4SiXzalGg/KncSIBIhnuByyXsEeCX69Iuzk5W21hIEvEidztX9xHOy4hScwb1yLioXFmlSrUW9Y93c12BLGPNIcSMFQZ8j3cS5cjumq9UYOLOLhT2ZpG+8Ob4kVXHZIiU3KxtCorSoR3af9qiiUKCSxSqUYalqIZ8tYUS5at/PYWrf+oMx2uRS6MosBKSx8MpsfQwGhwCM7UabMC+FCmP+dU3zWS7JLSLPPKhJBF1huyzHQneY+Z+5kEaUbGMdTUSwcSPHOsylMN8IOujUcM1C3vkvtyfgNTfn6xEi+6vS2f5X2832OoXt1uNJxjudvsODU90Q2PmWOz6H7MdogpcUKd2MuRvWxUBiVju7tLEkQkhuNI4h7lgyTRW34S6Wtywj0AKZ1oUN8uB+iAEFdh/GxAaSHNgo84on6hi0aEkEGNG2kroYtb04+x/NwJ1AX3rkpiJNTPVptblet8HbqBqJJmUCtnUXqcVH5aLRRRxErLtzrVntomnJGDl/rDd9SZKyG2G5/+vZY3fzwAg7fdIUiVb6P/CRhkQKgc7NuHLxywZ8v02+JVfosbzK9uxe2RAbHnzRcg/hTsqQGn34h/zQ0IUc/Tw2NYf6DCtLt1tr60CtT0Odaz0bZPnm75OGNwSCU+fHZltlsPTamfqIGjL6u7csBpgJ06fKfIaNBZhFC2FXthVTke5KFXtj6by36W65r6WBvb26E0+SZGwdBiJoSvRz5Aa1+gROClK9ItM3EaRERW32ZD1aTNrZ1Ib8SFZVvAEfgtGis/TTQ8a3hCFVT1Q0Drgiw4Ai4yUJm9DRDV1JpC7oy3fpX+x52XJBaGjp2OvxzGeNy32hFe3jNZtybqnpTrL2AaNzdqVsYEIbpBfqCMPDSgtLKVCYQlpM3du5+xJiK6Mc/CrYGronrB15LzMvgcz1I53wuEQqIzPBQHR1pg4lBQk0yQgIVK2aboGy88A2+PIuJpdf0YtMPRXaCc+7HHztDoQxiJp0lL1OwsnqVF9swyuKmaJ4RmNhEiNOIpHJj6fzHsXYVTFfVIRx1qxpYmPbUgoJXBuCkgTrhlJEGIvAW/moZDX8GoOpXW3siF4Zizhn4u4fga8i9kVfsbd0PSUYLwpxViX6NGoUb5wwaUe3E/xy9pEC4HVWq+VAgb9W3bctjMu6DL1c/t6gWcnr1S9t5lLkzZmXGvmSqep2KMcSOA2d9AFHmKIrszq3ChSy+xCcjPfkNWLovSOy0PuTbLSKRk+QWBPq4ICsKzeVXzsYyuN2BmCzPUhrSsFiSl0gwyNp3gdk/UBzSA/9n8nmBioPe5PZsvS23pxn9+sr0rSWhZ7zNk1vEsVDV5pnW/ZOXXD7v9ysnm7E0LLmmLhM5/XInnYNxJQihbYxPJ3RUEzyn0j9fvHdmEqWErBRcAeTJuc5RvM995y7QzfIT1MdqruQ/ILyM5k7XD0d+drhOnPv7V/bvLV+vzOXanA+I/+JwM4oecEVjJQUToPNHQlPCF//zJlXTXS0s3TWzMDrzrdCLfjTpdsHBJAK83dBxbn7FEJBH3sBe1zuJAldLrU/RqZH9Jem1kjoleIFJO1vijWunMQmBkJPuJuebRtY5kSVooBxBXqhUymaTam04ETwYfa08R3KF0oBCZ7brnK56ldAkTlKaVf7G0ppLZm3/9P3dGHKGfGYH4tmCHYCB5KBUGf6r0/hOn+CD7HFbYvnFrZIcHGeVga4Dplyvv+NumU0uj759Shrw9CvTiVyxmdbG6taE5NCLFcvhnJcF43ytognEkN+hACTOtevbKlRqwxCCVMPLSPqo7A4F4PLr4+6F0ZvpBMVwc9bQD1n5DDPQTwKlk/68B3npm+QsDK2fY9Pz6YKLas807BB8JTwpMOW5VuMtKGdjuVC5S8rvXHOTepdU8nFP+/ohNGNjYbARtpQqG20DkOnBtZtr5obd9Xf9YEkmTGrMqbAt+d5uwJyKV11ht/fC/QI2ne8DiWcSbJ9fV0scaJ/Rc1c/QgP6xdZ4Rt/n/Ga9RvuePpvH8CfCmkiJLFqHaivKP/h8s7fq4wzrXP+Md3X2+m42CziqLwthbh386KtKDQ8P2tH2le663V5dv9jSviV2azbIwtGAF3Z8tfbrn7YWWAx7P6a70d9Y16H31vjMf7D5cT7o54GuB7zy6IwIL2rhskdcXKDQbAOcM8tDTC3N0QhbuaejIIwHrjib1cHrrLkh3eUl3fS7ClSVWfcgwGEgOOnJkM365SUEjfWAn1mLzRJ5SH80xRde7mUB86QW+Lj5IrEd9sZU0natag7tf5PQoNm/YtrxeDtvkwvbFdFU4l8CbvWrn0VemjFebxi5+m2nyIRiFP0CEwAkIXmJ9ZkCdxgkCXQk/dSNLh/z4vxG7Mvad0HRk2UZz4X3tNuFZpA4sFmxHxpCCV3Fl/KhcJgGS7jXijcEtIM06lA5LPp/HJYsrM+9uLUGOeYXVcFQc9Fl31uZqOcb9H88zTHEw4VDIriKNTyq/MOe+5pIQ0QAYt3sGu12+5TV/rEbWbSxvrQjeC38VuZdEJTSXMeveoQPN8ILarahigfObLsqyHjPSxt7/DuNP7ynRqUepwgzXFZocTELd9GOvMoFvUgGNCuu7FPfSLO31riQflucA9gqLZRQg6R+iqVjsbN1AlN/ze+0SeLVfa7doRBRogIuqvbHetPviHJQRtZvhdVPGrWg9mJmVGZcdNCCeLivAkeRluMXfvk11om1Umwvnb9VqaJN/xdxsoMs2rLdc1/dEnGm1zHxTMAaH+gapGFueSel2/XfwxDgpBCXC8226Sr3YFabeK7T/Ojnm6L55egNdis4FC8lwQnCOy2D51JZNgNjlEWedJuxUx8x84XrzflUv5F9QHp/JcnWAA2n5k27ZUHaUV0fbUK61t07Lve+4Nzgytm3CyEZMZ2YYlJ8cFM3dTA59bEgBdSVxsGZVvpEiTs2mHMP4oHkPTmQjod1UldwzeTQlmbPShrhZ1qIIYh23JZDfYBhkV2pkc0eXpz4h7Dq1cfc4J2JRxNLqKc2mXAbAZ+FBfXn0LqhA+bjQoO6pJuLjgd1mFQZ5pDzOnubJJTHR7bq2y2Nkuh/LYtoudAc6edpdeiUtm4TOkZABLLLD9ecUeTH2yM0VBVeotcPOyUMOWxEOMRY7QwFGeQprZf9/u8jSiZck/osMc4jHoibYhbzKn7Xour5aNdlE/zxBX0pXEoKMhfFy85SkLLxO3zC+gYEF63yrAvmjjcLg1KGdqQqXtVt2UO2pZLjqxXmI3NZAjiiOHXljX6qgmFYGxKU0BLZoZilz8/RbXMXTDsdathaYFzGjkgDU83dVl4yIP9RTQBObFRAjKjV8CocydYxPnHqPRlo4uyua45uHCK+/fskLgFxkXMSNqPy48SZ+G/C1o2+7SFigThn3FM4HNrpOVu9imyI7+JlwMieGNkz7O6/qgk3LVh40X+e6Vj65O8FI0/dJarFgpiLoBKA5pljrpVpFXO5fI5NjjUG5sjf0EOdRBGuUNvsqOVHtQ1yUyjtQnXQSCo1M4/WUkVkNg4Gqpdip1wkx1ozteru6yPnRZX4aoyV7LdjReQNAPQmdtRDrar4Pvi8ydA52EClRsIWcArHFf6Zv11Y2/6sUv8YFIUiF0s700fK9A4bCwK0Hk1IDYsLLaSDM6ULk0DbR5kiYPHEEj2LJc7WHkp7LqxmXLuckzAkYqEnmG69Pr4Kt3x+uIWnhvRoJaSIhKrqZ2rL3h1u/U4IOM1mHAqsos/p+qU7U9OoCdtd4Up3lTvaIhdN+G79HcoDq4XBZugphZyAHgdalj3VIf6pJhl40xpo5uxizjaFkG6JFt8V7uW6Tk3tO5bQF56BfbIgvjESq/yuJs4uY/yjmHZS/vabOtQYoZ8WzPJvAevcgR3P1vUKQoButIzcbJoEUg4AR5rRVgvTZoaXhVin7X7mAGJxnmktg/zG6jFkZSQs1dQLFPbjTc3RMc+MgRTwV7d6pyYRNP36obQnwBr5/Qb4rPZHkGggh+n9tIIi2li2zxLU/qAaXNgg0ExUt5pqyurdAEbJxJiLmcd194gLatZa/MpxyZXGa6OIaxEpO9lkrxRTMDS5TK+W2KZ3+ySvgtjh4QTEApxu5yQUj5/YRzglnzVOdafhlLFjIXiLWyiMflTyxJBqAu2nM81nATPQ1pT/yUhzqcTjCdkrnURHRLGxk8Q/j1UwwIib0V845kQPcHeLNYdGu3zqocxR7mPFsoZ2msyusAUSB6yi5UMNjWUd1S57UiNVDxzNznHKCpeRYfcQJorxboohwXRhVwrQM9PXAJvqrAmb6153mvxx9nrBQofP1h1d3GAZsiSavo/iH784lJXicCkg4SWk/aoqh/MGDCTn32CKthGelFFyoymJ4zB/+/aSnJgZFFbWYMelrQhR22ITAPIR6RqQX9udXWwUlQSyuJBfqw7hOz2y6Cvoyt23Ldao4OYypKoXH9yO3J9Nlop1Wu1qTrl6fX2Q1J+qOQ1R+IJ5Nwe/Ptkv91LDYCWyRojLb3HvXPzJZw/L/SSrRfJk12Ly/vrHTQwh7RxhLiP4NXmsVPGbuhYsG8OcAPfzTR2bmto/AysvmfYCBs0+I23Rm4F77Pq04G6XhPjFZAxJXE8eHepFcFf7EVl/wcSZFJTGN/sPyx93R38L+DvhS0LaCpRaz5Cr0OvJTkC9uw0A9Z2LI08gvZdcvRv6gbtQkmpmRQUF3yyNo/PguWPvskBEUoHJ+Lgislks1nOdO1wX64jj3slIAAIs/dN9/vaO1qTElJWTbZB0141dQS1bxTlK2ZO2w4gzsq/NxKjeExumekNFd6wYRQR2Q12jg6B3h5fsDQYNMjsXLvpuMgsRr+YOO6eUI/LBkBOI50GGNP29CWMDkHuBylKTEp/iShxCZqPJjRo/E/HkjIIKhAbn45JG7ZPKbMqybk7yHNqnI41VchKVhsHCZoCXVU7sKwfd7ocg+rJ3NzsAjLb1HPnHcJlAvCMUjwd/u2q6tBMfEubTZq9MgQXF52su7ZOvUEupRbUnIVZ7UuyZIUZvt9pLV9BxE0+kYklB2P/rzn0Sm1vEHrWCsMnpl7Qd9m1du1LV5hSZ7fUCL5EBiCkZqBEoWz1uI8bf5ER0LqzvrteBoKs2FyHbldauQ00tcqwRXSmYLiEPt5d/pXwx8p/uZQDn3BhTspqQAkqFmaXx0XE1RcyQ2jKSCh/4qaS7lTdsyjXd6hxQcOYNv4HUjrHCOZ3hFPPJd4Feh1XHHIZn6ceqkrVhZxBCu3Kv00jHis58JBEPgSfdnrNyHjPBBb9hSyx4lNt+pdp6FLBIYwT7463JCuZY95PbmoA7jAN+izRe3Vg0OjX0bYYlhjd6qxWC3UORRkyGv2VblEz1JfP52ctqUTDszbqXEZVPkCgESfPm8Di4IQdWZsTNtHIE3X3W2zxuUT5+/DWscbF0aqicBCarqt5MYV+X4foq2jnXhNEAOXZ9sdk3PjeQ/fTDSERrrHgl1DwYu0yNYDOLw5AwszfRMov/Y1B/BZjsv31WN2a6h44EQMwglvoIyzVr1YkYlBvHfaiiWGP5BJRvn5WkXsCorijQ2EncMi6UQlawi9MynYhRVTp5D+VXaUu2rTGJpdMfzEbYKEdsDTFth8ZPJQ+RWsu6f5lm5xNf+HPG2F4Rof4kn3yXlKSZr37oxK4VwcxpLiTEVz86BtNCXP3U3924JfGQVcMo4mKQ/7ri+NBoxOzebUItwNEhF71mjU0aUbVIVNpk7pgCZoGbG2TQm9RDTVlJub3SNHqU173fwuqnWtYipt3AtRyzWEbSwbuB1Gl8dUyYdAx8+6dkrC51QbCxr4xm+eEziX/k8LVj6bxHu506sgGVlKc7whNCS+ubNeWIqZJAXhUrzHI8Y6xL7uz1RPVrUHTngQ3b5cnkU/bWWiCIefq9EG6YEFDgYrq0L9XbjTFgEYlXj3s8PTShA0axJackIdx1QiD5oLje9hszU2CuHKlbnmikiiySD41t+hmezbg13aylnGRz0iN0pXvtEtfVyjXlPx0JiFUvjHHp9u9qeqhHEJNiIuN4srF8VYGUWarPqzqMx71cnFh+Lu48DB1ZMRA8RE86Z8RhjCo0rYtRTYFRPtVCSYN1gyV1T5MEKd3ic9ggHeNl6TvsvyVptX8BxIZgfWxMMxs18BtjiBcoCTofNW5atjMd7vLUwCqfjVAHKZYbo7jg6eLPrrBl8wNV2NfLm3Riz//5oUMo1FCtMPM=
*/