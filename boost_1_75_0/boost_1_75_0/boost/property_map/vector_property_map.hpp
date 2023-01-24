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
kJuwaDEQ6LTs5zMckB5y8IKtcdzH7GjvGe0WJULgtobtCZw+CtCCkMvRhJvlBEoZDYj4zz3Ojeb4S4N6Rl4RYF4GZqh9/UuYvcQPtf4nYmQsYrwJgVHk2JWI5xMe05kf+EgpF/M4BLsXuPq8SQ6GXCFeBQ2LPcx+NLcE8Us9r3NanAat8mUa4ccQ/zl+RWcVn7yFhlnqXFQoZLX8inKl3EU6dqz28EZR/XmBi9kBly+Vx70hi5xzq3TaDX6qLtXv5RdM/hkKbcc91t5JicyCTU6eJ+Ego2NquvPoUVvpHPTBIeJBSTC3tBaDWh/9nFwEQqNFW8ue0UcKEhXLeto0+rp9jphsgxzdpcsVc/He6dy6RVK8z5vV5X7lU/YWEzr3tp8/WDlJ4N/TxnetWxrXw4Qt32tLLi6Jaw2eIIwj9w+DI4n7adlB5qW9/oQia9keTgAMxgl/KyI6j3IRn3Jtl9l+sSTdM+/ePEXU/The/gi082be/1BtZ5qSS1EVEPg1fUqIj34Y6zxmsziPQxa1kBtHbMDkJ2xXVhF5C0bmGMrBIgYMY764BcXZj5V6PV81DKZvTlvn3Nc1PxbHryHdn1Yh91Q/NDU41M5kPxIjszoYdlh7Ic2ehVrk0MmLSv5qRA1qnB0wmY46brzV4pXt7hOD83NPCh6VpTtD9tqkWegyv5xY46itLvZ6l393XzQqrPtNEuX42hswcs+5
*/