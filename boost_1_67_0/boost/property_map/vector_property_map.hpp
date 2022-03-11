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
#include <boost/shared_ptr.hpp>
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
#include <boost/property_map/parallel/vector_property_map.hpp>
#endif

#endif

/* vector_property_map.hpp
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
*/