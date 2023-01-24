// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_REVERSIBLE_PTR_CONTAINER_HPP
#define BOOST_PTR_CONTAINER_DETAIL_SERIALIZE_REVERSIBLE_PTR_CONTAINER_HPP

#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
#include <boost/ptr_container/detail/serialize_xml_names.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost 
{

namespace ptr_container_detail
{

template<class Archive, class Config, class CloneAllocator>
void save_helper(Archive& ar, const ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::const_iterator const_iterator;
    typedef BOOST_DEDUCED_TYPENAME container_type::value_type value_type;

    const_iterator i = c.begin(), e = c.end();
    for(; i != e; ++i)
        ar << boost::serialization::make_nvp( ptr_container_detail::item(), 
                ptr_container_detail::serialize_as_const(static_cast<value_type>(*i.base()))); 
    }

template<class Archive, class Config, class CloneAllocator>
void load_helper(Archive& ar, ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c,
                 BOOST_DEDUCED_TYPENAME ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>::size_type n)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::value_type value_type;

    //
    // Called after an appropriate reserve on c.
    //

    c.clear();            
    for(size_type i = 0u; i != n; ++i)
    {
        //
        // Remark: pointers are not tracked,
        // so we need not call ar.reset_object_address(v, u)
        //
        value_type ptr;
        ar >> boost::serialization::make_nvp( ptr_container_detail::item(), ptr ); 
        c.insert(c.end(), ptr);
    }
}

} // namespace ptr_container_detail

namespace serialization 
{

template<class Archive, class Config, class CloneAllocator>
void save(Archive& ar, const ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c, unsigned int /*version*/)
{   
    ar << boost::serialization::make_nvp( ptr_container_detail::count(), 
                                          ptr_container_detail::serialize_as_const(c.size()) );
    ptr_container_detail::save_helper(ar, c);
}

template<class Archive, class Config, class CloneAllocator>
void load(Archive& ar, ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c, unsigned int /*version*/)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    ptr_container_detail::load_helper(ar, c, n);
    
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_reversible_cont.hpp
bS+EXyEh7TCF4PUJ3NhUYoInUx46uYs8++GSvP+qd7WTvI5P3e/dYBzPX+PfD5Rsc0mHB60JD82JLpuCxIngmkaE743Ar6QQ2YCu3oAwHhldpaVhAyVg/k6ES/DK4l4P/2PSWFUYOXYdRiQgTcF0G4s/2A3NeuS5KaCiQN5m3amRTQ8fz0MreMxHs+jLXBVTaGru0f4hjABbJpMeyvofOpNbF+jv5rCZjHi/yEBkAjOufxhzGs412Qq4InqTFAI6vN4xsB/pIuMKqEL0er3ecYR6+dmToWFIV3dFkkxps7/ou20whG6krokrdU86Nyn+eaDBcxMM1M46uCL7QBCorU11OH8WinGWF7oqQwIx7vbuthSEIfX+AIRpQRqhRHenuFUMZr/ii7MBdBDTlVsDaGg/Mh5O12iChethyxAZjQgTPnGzqt68hwzquQHgmhC9M6638BF7e2x4LrsxgZdjPnf7Ttd/z+dGhASj/sxJK8Ys3Qc9Ukdrt37an9Lt6Yod/u4k1Kbmrm4omiFzU7bLy7cGwJ5hu7kA1phsyu7rhl0PIuC7ar7HIVSSqGNftGKDN8xmX0pGmBak2WyLwXKSwtClisxwQxxE6FOIvFF2dIec+eCAG1CdxEsHXl/KHlMLd1ktO9UPmNCv3Kq6y94ChvVHyyAfUIf1FyYqyKfCOUDz+5AJSOYATSRe1+Bu/OENCNSETAzuPJ9c/PMi
*/