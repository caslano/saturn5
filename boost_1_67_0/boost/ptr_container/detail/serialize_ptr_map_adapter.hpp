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