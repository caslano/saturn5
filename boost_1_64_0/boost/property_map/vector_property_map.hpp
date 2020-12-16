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
y/lYVc7zOsdn83OUl3Zv8PJ4zv8R+sGkRqk/j3l8IDR+D9IfOe/nebyJ8Ts7jvO4kPNLP11ll/avfIDxpF7qezm/17N4XnXSH96gnbK924/TL37OfIp5xSraYwXlTuhmHKdcN5mXRDJ+OGi3O5qYl1PuExtpN5yf/qfDpX+Ow3X6ofc85WB7B18QfQ4w76so5vmmi/nrLsbdWZwPK9cf9NdV07neYlk4i3KspX0yjszg/GSyv1do79s7aG/lXG8wT7yJMiv0mf5+lXn1JNpptpN53Wzmc8/yPE/9ppWynvH++AKOE+Np9mWuP9j/Jep3nPquWcnx4HztYH+1M7neKOd59RkeN5P79fB8zzh45YDIN30116F+iXsJ3O8Ix/Mm5/H0gCJ5G/PUHTzfHvwJ2/0F9a+UdZjjZ+Gyn1vG6wDtZzPXFw7mUwkf4jxjfMJC8+EQeU5wHpeXSpnNvP4U84dFObTvEq6Xuf+VXZyvMvmcxHF/hXHnIM+DCRsZl5/mfLi43mP+f4n69n6RecsO2jX13/IGxyWZcb6FcZHnr608X7mf4bgwPnt/Rj+zy3WCSNrVZq5fbr/M+XxDJ+2W8DxsZ3x9RkrbRfrxBbZHO8rs4/xS7g7Gr7OMq6YfMM/l/OyivLs/JfWrKukHXsZPh0Hq9cw718hDF4suSN6ymXHmPOP3Yc7nYZ4fEl7k+udJroceoh/Hct35ce63TuS5TD/sp30nvMy4qMVv7TzC+mza8WUH7YHrixTmpYu06yeMG2e72W8q7ZPHX2iifV9lfKGdGWiv+/LZPuU/zzg1gXJc57ymMP4lWRhHShmPN0i7NhvjAe3WvY52mcf5fZ3zVM1xK6K9F9DOtfME/XZ7Hde3bunHQb/odUk5RTsPFogfnl8tZcVOjotDUdJQelU5n52mvklcN2/lulzleO55jn5FuU9s5XUut3y+wHXUYV6f0XF/L+3csYFxYz79biXzSp73vIwrN5dzHbmCx8XyPM94a+M6R6X973sv8xjGK6+Z62Yel81yOu1t9xquD1TGGdpHxSbGbe17F/WiX23nPG97Tcf1LddDtPdMrt+8FziPOD451O8c2j/td+GrXC+5mQ98gfk9xzmyyCBlIfWaT3sNMm9kXM+k3y3kfE7vpVy8HhHkfKx5RuZ9Wz3Xz1yfnKA+057VjVzHcjBPPDWT8/4G40uvfL+c7W7r53GMG9vOyf7R5eyP+e9W2nsk4+ZtjtNpqyLz+Dj9nHZ6NZXxdB6Pp19EMl7tS+J6tlTKaTyPZ/P7DtpZEvObRTzuxM85b7QLdwfPA5zX80s5b4wDC9sVaZfjv4brvpsuxrsZXG836kf85nAt+zvB9VA8x6NM9j88h+sO5iOOMpmPza1cZ2vX/XgeO7KLeRDntcPF+adf9dN+D5YrIpd2virl9Zv30j85nrd7WT+D6y/G40g/4wrn8TLj8LYiXl/neFxgv1MYt7YUMP/kODkYDyto/8FtjAMX5Lx+if5s4Lz0M//dxfODjvpOp1+cvsq4/FOuq3k9OthBv5rFeMB5ub6R66QfME9/hvP8KfazMXzkd3uucP9zuxTlgdC4WBWp/yDj0h/oj4xD09wSFwu5HnmlnePNuJe5iuO8RPxc5bhP38K43Md5u8y8l/o5GC9PMQ8+u55xBnLrQ3LZeX2S5/U9zBcPO3gdl3Ejk37zCv3y5vsYP1t5fe3jtBctX+J54Iie17UepD/m0a85f1d4vi3keeiql/PH/YN9tKN1lJPze+nPlIvzFP0i41Up/ZLzsoj2kUm72UH5LjD+6QKKzEcs82zGpelcn55dR78ex/nV/N3LfIDzdypcUSyh9p/lupxy11I=
*/