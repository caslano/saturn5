// Copyright (C) Vladimir Prus 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/graph/vector_property_map.html for
// documentation.
//

#ifndef BOOST_PROPERTY_MAP_VECTOR_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_VECTOR_PROPERTY_MAP_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <iterator>
#include <vector>

namespace boost {
    template<typename T, typename IndexMap = identity_property_map>
    class vector_property_map
        : public boost::put_get_helper< 
              typename std::iterator_traits< 
                  typename std::vector<T>::iterator >::reference,
              vector_property_map<T, IndexMap> >
    {
    public:
        typedef typename property_traits<IndexMap>::key_type  key_type;
        typedef T value_type;
        typedef typename std::iterator_traits< 
            typename std::vector<T>::iterator >::reference reference;
        typedef boost::lvalue_property_map_tag category;

        vector_property_map(const IndexMap& index = IndexMap())
        : store(new std::vector<T>()), index(index)
        {}

        vector_property_map(unsigned initial_size, 
                            const IndexMap& index = IndexMap())
        : store(new std::vector<T>(initial_size)), index(index)
        {}

        typename std::vector<T>::iterator storage_begin()
        {
            return store->begin();
        }

        typename std::vector<T>::iterator storage_end()
        {
            return store->end();
        }

        typename std::vector<T>::const_iterator storage_begin() const
        {
            return store->begin();
        }

        typename std::vector<T>::const_iterator storage_end() const
        {
            return store->end();
        }

        IndexMap&       get_index_map()       { return index; }
        const IndexMap& get_index_map() const { return index; }

    public:
        // Copy ctor absent, default semantics is OK.
        // Assignment operator absent, default semantics is OK.
        // CONSIDER: not sure that assignment to 'index' is correct.

        reference operator[](const key_type& v) const {
            typename property_traits<IndexMap>::value_type i = get(index, v);
            if (static_cast<unsigned>(i) >= store->size()) {
                store->resize(i + 1, T());
            }
            return (*store)[i];
        }
    private:
        // Conceptually, we have a vector of infinite size. For practical 
        // purposes, we start with an empty vector and grow it as needed.
        // Note that we cannot store pointer to vector here -- we cannot
        // store pointer to data, because if copy of property map resizes
        // the vector, the pointer to data will be invalidated. 
        // I wonder if class 'pmap_ref' is simply needed.
        shared_ptr< std::vector<T> > store;
        IndexMap index;
    };

    template<typename T, typename IndexMap>
    vector_property_map<T, IndexMap>
    make_vector_property_map(IndexMap index)
    {
        return vector_property_map<T, IndexMap>(index);
    }
}

#ifdef BOOST_GRAPH_USE_MPI
// Hide include from dependency trackers; the right fix
// is not to have it at all, but who knows what'll break
#define BOOST_VPMAP_HEADER_NAME <boost/property_map/parallel/vector_property_map.hpp>
#include BOOST_VPMAP_HEADER_NAME
#undef BOOST_VPMAP_HEADER_NAME
#endif

#endif

/* vector_property_map.hpp
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
*/