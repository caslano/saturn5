// Copyright 2005 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine

// Indexed properties -- used for CSR and CSR-like graphs

#ifndef BOOST_GRAPH_INDEXED_PROPERTIES_HPP
#define BOOST_GRAPH_INDEXED_PROPERTIES_HPP

#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <iterator>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/integer.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
namespace detail
{

    template < typename Derived, typename Property, typename Descriptor,
        typename IndexMap >
    class indexed_vertex_properties
    {
    public:
        typedef no_property vertex_property_type;
        typedef Property vertex_bundled;
        typedef iterator_property_map<
            typename std::vector< Property >::iterator, IndexMap >
            vertex_map_type;
        typedef iterator_property_map<
            typename std::vector< Property >::const_iterator, IndexMap >
            const_vertex_map_type;

        // Directly access a vertex or edge bundle
        Property& operator[](Descriptor v)
        {
            return m_vertex_properties[get(vertex_index, derived(), v)];
        }

        const Property& operator[](Descriptor v) const
        {
            return m_vertex_properties[get(vertex_index, derived(), v)];
        }

        vertex_map_type get_vertex_bundle(
            const IndexMap& index_map = IndexMap())
        {
            return vertex_map_type(m_vertex_properties.begin(), index_map);
        }

        const_vertex_map_type get_vertex_bundle(
            const IndexMap& index_map = IndexMap()) const
        {
            return const_vertex_map_type(
                m_vertex_properties.begin(), index_map);
        }

    protected:
        // Default-construct with no property values
        indexed_vertex_properties() {}

        // Initialize with n default-constructed property values
        indexed_vertex_properties(std::size_t n) : m_vertex_properties(n) {}

    public:
        // Clear the properties vector
        void clear() { m_vertex_properties.clear(); }

        // Resize the properties vector
        void resize(std::size_t n) { m_vertex_properties.resize(n); }

        // Reserve space in the vector of properties
        void reserve(std::size_t n) { m_vertex_properties.reserve(n); }

        // Add a new property value to the back
        void push_back(const Property& prop)
        {
            m_vertex_properties.push_back(prop);
        }

        // Write an element by raw index
        void write_by_index(std::size_t idx, const Property& prop)
        {
            m_vertex_properties[idx] = prop;
        }

        // Access to the derived object
        Derived& derived() { return *static_cast< Derived* >(this); }

        const Derived& derived() const
        {
            return *static_cast< const Derived* >(this);
        }

    public: // should be private, but friend templates not portable
        std::vector< Property > m_vertex_properties;
    };

    template < typename Derived, typename Descriptor, typename IndexMap >
    class indexed_vertex_properties< Derived, void, Descriptor, IndexMap >
    {
        struct secret
        {
        };

    public:
        typedef no_property vertex_property_type;
        typedef void vertex_bundled;
        typedef secret vertex_map_type;
        typedef secret const_vertex_map_type;

        secret operator[](secret) { return secret(); }

        vertex_map_type get_vertex_bundle() const { return vertex_map_type(); }

    protected:
        // All operations do nothing.
        indexed_vertex_properties() {}
        indexed_vertex_properties(std::size_t) {}

    public:
        void clear() {}
        void resize(std::size_t) {}
        void reserve(std::size_t) {}
    };

    template < typename Derived, typename Property, typename Descriptor,
        typename IndexMap >
    class indexed_edge_properties
    {
    public:
        typedef no_property edge_property_type;
        typedef Property edge_bundled;
        typedef Property edge_push_back_type;
        typedef iterator_property_map<
            typename std::vector< Property >::iterator, IndexMap >
            edge_map_type;
        typedef iterator_property_map<
            typename std::vector< Property >::const_iterator, IndexMap >
            const_edge_map_type;

        // Directly access a edge or edge bundle
        Property& operator[](Descriptor v)
        {
            return m_edge_properties[get(edge_index, derived(), v)];
        }

        const Property& operator[](Descriptor v) const
        {
            return m_edge_properties[get(edge_index, derived(), v)];
        }

        edge_map_type get_edge_bundle(const IndexMap& index_map = IndexMap())
        {
            return edge_map_type(m_edge_properties.begin(), index_map);
        }

        const_edge_map_type get_edge_bundle(
            const IndexMap& index_map = IndexMap()) const
        {
            return const_edge_map_type(m_edge_properties.begin(), index_map);
        }

    protected:
        // Default-construct with no property values
        indexed_edge_properties() {}

        // Initialize with n default-constructed property values
        indexed_edge_properties(std::size_t n) : m_edge_properties(n) {}

        // Get the size of the properties vector
        std::size_t size() const { return m_edge_properties.size(); }

        // Clear the properties vector
        void clear() { m_edge_properties.clear(); }

        // Resize the properties vector
        void resize(std::size_t n) { m_edge_properties.resize(n); }

        // Reserve space in the vector of properties
        void reserve(std::size_t n) { m_edge_properties.reserve(n); }

        // Write an element by raw index
        void write_by_index(std::size_t idx, const Property& prop)
        {
            m_edge_properties[idx] = prop;
        }

    public:
        // Add a new property value to the back
        void push_back(const Property& prop)
        {
            m_edge_properties.push_back(prop);
        }

        // Move range of properties backwards
        void move_range(
            std::size_t src_begin, std::size_t src_end, std::size_t dest_begin)
        {
            std::copy_backward(m_edge_properties.begin() + src_begin,
                m_edge_properties.begin() + src_end,
                m_edge_properties.begin() + dest_begin + (src_end - src_begin));
        }

        typedef typename std::vector< Property >::iterator iterator;
        iterator begin() { return m_edge_properties.begin(); }
        iterator end() { return m_edge_properties.end(); }

    private:
        // Access to the derived object
        Derived& derived() { return *static_cast< Derived* >(this); }

        const Derived& derived() const
        {
            return *static_cast< const Derived* >(this);
        }

    public: // should be private, but friend templates not portable
        std::vector< Property > m_edge_properties;
    };

    struct dummy_no_property_iterator
    : public boost::iterator_facade< dummy_no_property_iterator, no_property,
          std::random_access_iterator_tag >
    {
        mutable no_property prop;
        no_property& dereference() const { return prop; }
        bool equal(const dummy_no_property_iterator&) const { return true; }
        void increment() {}
        void decrement() {}
        void advance(std::ptrdiff_t) {}
        std::ptrdiff_t distance_to(const dummy_no_property_iterator) const
        {
            return 0;
        }
    };

    template < typename Derived, typename Descriptor, typename IndexMap >
    class indexed_edge_properties< Derived, void, Descriptor, IndexMap >
    {
        struct secret
        {
        };

    public:
        typedef no_property edge_property_type;
        typedef void edge_bundled;
        typedef void* edge_push_back_type;
        typedef secret edge_map_type;
        typedef secret const_edge_map_type;

        secret operator[](secret) { return secret(); }
        void write_by_index(std::size_t /*idx*/, const no_property& /*prop*/) {}

        edge_map_type get_edge_bundle(const IndexMap& = IndexMap()) const
        {
            return edge_map_type();
        }

    protected:
        // All operations do nothing.
        indexed_edge_properties() {}
        indexed_edge_properties(std::size_t) {}
        std::size_t size() const { return 0; }
        void clear() {}
        void resize(std::size_t) {}
        void reserve(std::size_t) {}

    public:
        void push_back(const edge_push_back_type&) {}
        void move_range(std::size_t /*src_begin*/, std::size_t /*src_end*/,
            std::size_t /*dest_begin*/)
        {
        }

        typedef dummy_no_property_iterator iterator;
        iterator begin() { return dummy_no_property_iterator(); }
        iterator end() { return dummy_no_property_iterator(); }
    };

}
}

#endif // BOOST_GRAPH_INDEXED_PROPERTIES_HPP

/* indexed_properties.hpp
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
*/