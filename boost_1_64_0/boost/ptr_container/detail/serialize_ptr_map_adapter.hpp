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
o0Ls5+NPkiY2fyB2q+0U+vElyAcycD06b+mZ9KU/4mNjp6etpj9jv8pZFGmsw//7xFPH+b4gumnvv7jq4w2wqf9ATrDX71+HTt4QXZ3k75HY/TdddcZl2L/f0Fb7Ywe2xjd6D9/vG/zl+5GxYa4a96yrJlc56oY7sDOvuGoj/K/5tHPDZfiE6LyL6Rvnf+KqSuxZT/TocOR2h3xk9mt8U/I66HHsew5ydK2j2m+Gr9jmPfEL2/Pxh/DLjhyCzJyGfcHX2m429BejPy8lnUmu6tnAW4Zfu+pPn6PXkM3D78Hfw6aciA2qpk6+Htp7hauerPHUX5ChidiAkh6uGns0OuhZdMcJ6PKXPPULF5+I/M+j796GDG5zFnrmQ9rtQE/lboh/9mvWceBh352Rx1x084n4j43ojhX4put6asHznnr4IE+98T227yPi0w4j0KPL8I/2PRD9jvysvsFVf9sau7MNbcy3EV9Pvk35BvBtsU0Q9v0A6nUB6broY3zFU89X6kBkbVk7/sWLnpo2jLDr0d/VrEuig3o9iP3GdnzyB/roptiQj1115je0K/Fe+IH3fFbDR/zYXXfDL/wNPvsLrrrlY+QcP7o39va35FnPt2sZ5Zmr1P2VyMYWnvKudtSHv6RclOGFFfh/9L+rV+Kn4VPOQPamf0V61xOGHSsagdtJfX/AJz8VO7+M+u59lKfu/9hRF5wDT5rwd25i3If/2esX6ELs9UfHeeqWIxnfYTdemEI9kIsL0H+VhI9upj5VnrqhGR1dQFsyTiyvo50PxF6v66jG4diaKfR/eLL75tixbfibbzXfM/hvO73oqLazWaNDhl/dCV8V/3VhylWLnnZV2RH025vpc9iHM5DH70l32CxPXYCt2ABdVLaGdr3cVYd+hO+1EfJ2GXp7hKfupd+tor1rv6XPj3eUf37s4nmu2rkF/4txwcgk7fVL/KgG+gR6JHUKfOqgvvDr+Db8x3JPHTYaHYV+/HJcUN6rC5HHl/D9DnZV1WLs6BEO9/ti1z7FHt0I/0vw20bRnx931NMPYxOJ82gPyjAW3bo3dRnqqn3g7+yHlPIeUOpufNAH73TUt7nIq38eBnv8NXZthyGe+mCxp359Lv4a5flhKL7Jeui4FvyCzbEHMx1VVkA7YA++G4CdxaecR3o3ttDv/DEtNnow6bXhA6ymvyRIZ2wD9go/9PH70ef4XAq53AK9O9XFByaP72eTz06OanjEVQc0eGoSfv1+/N6xKXbxPniI7OxC37iI8OGN2M0G5gmq6BfYiln0t133xd/AX7trELocbAY+wtU3Y6ufwy+h/utS99y9qccWrjrmNWQMmSrHlzqLseGCh6gn47IW+FePD9ynEpuwAD/9MPopdbiQch1fg7/dg75/JHKccLTN6KDs71CXO//uqMPQYUfm0R+wy9viGw0h3+PySPtg8v8zvtlIbBA682F8uxVr8Jdn01cJX/Eu+uUyfvEbyvF3/Xchf0ff/KTEVRWPQ7cfvtal+Js3OerSOfiYjHN+Mx6dgr90CXZ56sOeumcfVlGx89Xwfu/TkJU8ykg/HoptL8Tnr6lh/AK233eu2u12V5XiJ33FePPv62PracOlDyCzhPfB1vd8FF25B2Ml6lO3D2VkDPI0Y70z/uiofq2uOnol9qDMUfvsRX7v0kZ7eqrMf1sVOXSR+cHL8KvRl1+g2w9rc9Vvv8BekvbJ9I/nvnDUzLvoV8j7b/HjP9rXVc21nnqT8L/yvZ2HD87XGx0++wP2JF5HG6GbWh/hHVp/jsNjHDrPUb/4Ch8IeZxM/29Hb0w7gz7Uh/72FLKM/90vhU16xsGvZSyJ/foVY/DL8P1Wgtc=
*/