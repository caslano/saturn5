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