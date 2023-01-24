// Boost.Geometry Index
//
// R-tree query iterators
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP

#include <boost/scoped_ptr.hpp>

//#define BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace iterators {

template <typename Value, typename Allocators>
struct end_query_iterator
{
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    reference operator*() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not dereferencable");
        pointer p(0);
        return *p;
    }

    const value_type * operator->() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not dereferencable");
        const value_type * p = 0;
        return p;
    }

    end_query_iterator & operator++()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    end_query_iterator operator++(int)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(false, "iterator not incrementable");
        return *this;
    }

    friend bool operator==(end_query_iterator const& /*l*/, end_query_iterator const& /*r*/)
    {
        return true;
    }
};

template <typename MembersHolder, typename Predicates>
class spatial_query_iterator
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef visitors::spatial_query_incremental<MembersHolder, Predicates> visitor_type;
    typedef typename visitor_type::node_pointer node_pointer;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename MembersHolder::value_type value_type;
    typedef typename allocators_type::const_reference reference;
    typedef typename allocators_type::difference_type difference_type;
    typedef typename allocators_type::const_pointer pointer;

    inline spatial_query_iterator()
    {}

    inline spatial_query_iterator(parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
    {}

    inline spatial_query_iterator(node_pointer root, parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
    {
        m_visitor.initialize(root);
    }

    reference operator*() const
    {
        return m_visitor.dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_visitor.dereference());
    }

    spatial_query_iterator & operator++()
    {
        m_visitor.increment();
        return *this;
    }

    spatial_query_iterator operator++(int)
    {
        spatial_query_iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(spatial_query_iterator const& l, spatial_query_iterator const& r)
    {
        return l.m_visitor == r.m_visitor;
    }

    friend bool operator==(spatial_query_iterator const& l, end_query_iterator<value_type, allocators_type> const& /*r*/)
    {
        return l.m_visitor.is_end();
    }

    friend bool operator==(end_query_iterator<value_type, allocators_type> const& /*l*/, spatial_query_iterator const& r)
    {
        return r.m_visitor.is_end();
    }
    
private:
    visitor_type m_visitor;
};

template <typename MembersHolder, typename Predicates, unsigned NearestPredicateIndex>
class distance_query_iterator
{
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;
    typedef typename MembersHolder::allocators_type allocators_type;

    typedef visitors::distance_query_incremental<MembersHolder, Predicates, NearestPredicateIndex> visitor_type;
    typedef typename visitor_type::node_pointer node_pointer;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef typename MembersHolder::value_type value_type;
    typedef typename allocators_type::const_reference reference;
    typedef typename allocators_type::difference_type difference_type;
    typedef typename allocators_type::const_pointer pointer;

    inline distance_query_iterator()
    {}

    inline distance_query_iterator(parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
    {}

    inline distance_query_iterator(node_pointer root, parameters_type const& par, translator_type const& t, Predicates const& p)
        : m_visitor(par, t, p)
    {
        m_visitor.initialize(root);
    }

    reference operator*() const
    {
        return m_visitor.dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_visitor.dereference());
    }

    distance_query_iterator & operator++()
    {
        m_visitor.increment();
        return *this;
    }

    distance_query_iterator operator++(int)
    {
        distance_query_iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(distance_query_iterator const& l, distance_query_iterator const& r)
    {
        return l.m_visitor == r.m_visitor;
    }

    friend bool operator==(distance_query_iterator const& l, end_query_iterator<value_type, allocators_type> const& /*r*/)
    {
        return l.m_visitor.is_end();
    }

    friend bool operator==(end_query_iterator<value_type, allocators_type> const& /*l*/, distance_query_iterator const& r)
    {
        return r.m_visitor.is_end();
    }

private:
    visitor_type m_visitor;
};


template <typename L, typename R>
inline bool operator!=(L const& l, R const& r)
{
    return !(l == r);
}


template <typename Value, typename Allocators>
class query_iterator_base
{
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    virtual ~query_iterator_base() {}

    virtual query_iterator_base * clone() const = 0;
    
    virtual bool is_end() const = 0;
    virtual reference dereference() const = 0;
    virtual void increment() = 0;
    virtual bool equals(query_iterator_base const&) const = 0;
};

template <typename Value, typename Allocators, typename Iterator>
class query_iterator_wrapper
    : public query_iterator_base<Value, Allocators>
{
    typedef query_iterator_base<Value, Allocators> base_t;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    query_iterator_wrapper() : m_iterator() {}
    explicit query_iterator_wrapper(Iterator const& it) : m_iterator(it) {}

    virtual base_t * clone() const { return new query_iterator_wrapper(m_iterator); }

    virtual bool is_end() const { return m_iterator == end_query_iterator<Value, Allocators>(); }
    virtual reference dereference() const { return *m_iterator; }
    virtual void increment() { ++m_iterator; }
    virtual bool equals(base_t const& r) const
    {
        const query_iterator_wrapper * p = dynamic_cast<const query_iterator_wrapper *>(boost::addressof(r));
        BOOST_GEOMETRY_INDEX_ASSERT(p, "iterators can't be compared");
        return m_iterator == p->m_iterator;
    }

private:
    Iterator m_iterator;
};


template <typename Value, typename Allocators>
class query_iterator
{
    typedef query_iterator_base<Value, Allocators> iterator_base;
    typedef boost::scoped_ptr<iterator_base> iterator_ptr;

public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef typename Allocators::const_reference reference;
    typedef typename Allocators::difference_type difference_type;
    typedef typename Allocators::const_pointer pointer;

    query_iterator()
    {}

    template <typename It>
    query_iterator(It const& it)
        : m_ptr(static_cast<iterator_base*>(
                    new query_iterator_wrapper<Value, Allocators, It>(it) ))
    {}

    query_iterator(end_query_iterator<Value, Allocators> const& /*it*/)
    {}

    query_iterator(query_iterator const& o)
        : m_ptr(o.m_ptr.get() ? o.m_ptr->clone() : 0)
    {}

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE
    query_iterator & operator=(query_iterator const& o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.reset(o.m_ptr.get() ? o.m_ptr->clone() : 0);
        }
        return *this;
    }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    query_iterator(query_iterator && o)
        : m_ptr(0)
    {
        m_ptr.swap(o.m_ptr);
    }
    query_iterator & operator=(query_iterator && o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.swap(o.m_ptr);
            o.m_ptr.reset();
        }
        return *this;
    }
#endif
#else // !BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE
private:
    BOOST_COPYABLE_AND_MOVABLE(query_iterator)
public:
    query_iterator & operator=(BOOST_COPY_ASSIGN_REF(query_iterator) o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.reset(o.m_ptr.get() ? o.m_ptr->clone() : 0);
        }
        return *this;
    }
    query_iterator(BOOST_RV_REF(query_iterator) o)
        : m_ptr(0)
    {
        m_ptr.swap(o.m_ptr);
    }
    query_iterator & operator=(BOOST_RV_REF(query_iterator) o)
    {
        if ( this != boost::addressof(o) )
        {
            m_ptr.swap(o.m_ptr);
            o.m_ptr.reset();
        }
        return *this;
    }
#endif // BOOST_GEOMETRY_INDEX_DETAIL_QUERY_ITERATORS_USE_MOVE

    reference operator*() const
    {
        return m_ptr->dereference();
    }

    const value_type * operator->() const
    {
        return boost::addressof(m_ptr->dereference());
    }

    query_iterator & operator++()
    {
        m_ptr->increment();
        return *this;
    }

    query_iterator operator++(int)
    {
        query_iterator temp = *this;
        this->operator++();
        return temp;
    }

    friend bool operator==(query_iterator const& l, query_iterator const& r)
    {
        if ( l.m_ptr.get() )
        {
            if ( r.m_ptr.get() )
                return l.m_ptr->equals(*r.m_ptr);
            else
                return l.m_ptr->is_end();
        }
        else
        {
            if ( r.m_ptr.get() )
                return r.m_ptr->is_end();
            else
                return true;
        }
    }

private:
    iterator_ptr m_ptr;
};

}}}}}} // namespace boost::geometry::index::detail::rtree::iterators

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_QUERY_ITERATORS_HPP

/* query_iterators.hpp
eLfYWW01MwtirlNRM2dc1Z7Vrh/UeGZ/MZtWUaWzXE31aymw8f6weza5olBHzYSyHbxr/9fh9uxBhWD1mGGHr+f1YVUFSMfFpAPk+cTarh1Qda2/2rjSiHRImM+qaTR06Jjzgm80XjuszmNUJxiSd3ghlxYaeedfzjPWqJi0uzntLo061M87G2W3e90v5TpczC9cHR41zh9V71XPm7j8WvPv2AEfXTUdYdY0myA6ga4B28j9q+n5/mpIq3EL0DcAiUw44p13MYZ0BB4hV66W5xGGkK6xE7Ehe1TrSnWjUvYZYvcIpLRFQevEZ1v2BmI8kiWc1YiQHgWzBtc2Lm0hTWYiRpzpCPKIzJ7RHse/tM2qXdtdS7hMTLdmtxq3PLdaz5BnfWe7Z2lnc2dNZ2Fb8K3VLcAW/VbhVkl/f994PGkfU39Jv0v8ePw6BYSyix8oGOj3MHb7ICRqENB07bi6uLKIrE+wyR5vynESX/a63li8rl+1wRxLzKEU90MeLyzy2uDYMI2rQjrcvHaPR+vrbVxyc0X97o9z6y9sFlsPQY17h2M7Y7MQB7F5sPPxSiYoApSyVzy+KiQIOtltXQQ1j43mVrR/bVcPKjiTHo6Yw3EixTO27ZoIMLvsOcCxIMVzt6V9I963m87NSHuWLoTcBbGjhDSBMMcbIUdAQVfn7ZX91mnU6BWg997K3ytRDXENUQ3B5OxSiG2ObZ5t
*/