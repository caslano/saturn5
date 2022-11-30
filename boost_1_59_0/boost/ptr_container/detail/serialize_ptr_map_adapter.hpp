// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_PTR_MAP_ADAPTER_HPP
#define BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_PTR_MAP_ADAPTER_HPP

#include <boost/ptr_container/ptr_map_adapter.hpp>
#include <boost/ptr_container/detail/serialize_xml_names.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class VoidPtrMap, class CloneAllocator, bool Ordered>
void save(Archive& ar, const ptr_container_detail::ptr_map_adapter_base<T, VoidPtrMap, CloneAllocator,Ordered>& c, unsigned int /*version*/)
{
    typedef ptr_container_detail::ptr_map_adapter_base<T, VoidPtrMap, CloneAllocator,Ordered> container;
    typedef BOOST_DEDUCED_TYPENAME container::const_iterator const_iterator;

    ar << boost::serialization::make_nvp( ptr_container_detail::count(), 
                                          ptr_container_detail::serialize_as_const(c.size()) );

    const_iterator i = c.begin(), e = c.end();
    for(; i != e; ++i)
    {
        ar << boost::serialization::make_nvp( ptr_container_detail::first(), i->first );
        ar << boost::serialization::make_nvp( ptr_container_detail::second(),
                                              ptr_container_detail::serialize_as_const(i->second) );
    }
}

template<class Archive, class T, class VoidPtrMap, class CloneAllocator, bool Ordered>
void load(Archive& ar, ptr_map_adapter<T, VoidPtrMap, CloneAllocator,Ordered>& c, unsigned int /*version*/)
{
    typedef ptr_map_adapter<T, VoidPtrMap, CloneAllocator,Ordered> container;
    typedef BOOST_DEDUCED_TYPENAME container::key_type key_type;
    typedef BOOST_DEDUCED_TYPENAME container::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME container::iterator iterator;

    c.clear();
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );

    for(size_type i = 0u; i != n; ++i)
    {
        key_type key;
        T* value;
        ar >> boost::serialization::make_nvp( ptr_container_detail::first(), key );
        ar >> boost::serialization::make_nvp( ptr_container_detail::second(), value );
        std::pair<iterator, bool> p = c.insert(key, value);
        ar.reset_object_address(&p.first->first, &key); 
    }
}

template<class Archive, class T, class VoidPtrMap, class CloneAllocator, bool Ordered>
void load(Archive& ar, ptr_multimap_adapter<T, VoidPtrMap, CloneAllocator,Ordered>& c, unsigned int /*version*/)
{
    typedef ptr_multimap_adapter<T, VoidPtrMap, CloneAllocator,Ordered> container;
    typedef BOOST_DEDUCED_TYPENAME container::key_type key_type;
    typedef BOOST_DEDUCED_TYPENAME container::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME container::iterator iterator;

    c.clear();
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );

    for(size_type i = 0u; i != n; ++i)
    {
        key_type key;
        T* value;
        ar >> boost::serialization::make_nvp( ptr_container_detail::first(), key );
        ar >> boost::serialization::make_nvp( ptr_container_detail::second(), value );
        iterator p = c.insert(key, value);
        ar.reset_object_address(&p->first, &key);
    }
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_map_adapter.hpp
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
*/