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
WBQ7yL06iY6Hgm8jlQrLj67Dgxor4RlKoQEpTZ2hncHR3azWWCPyiokQ28n6cPrqPvVG58yx2IoxWpwVJwkkG43W1hcezKJbCezVM7qFVY75uW/fQ7omvtRPqrPqSU2tKOT4ATdDsb7aVrARb+7ijjOk+Umj3MDxvkPknXm2jW81Vm5jJVuGSmxY6PfTxMuNiPLWkzHo9GjTjUml7LZZwctHbBQxAg1CfFHgP2O57c6bIcPZEtIpHZVueJHvYsNf98aaHcfxQqMW6rv8tx3yUY+EakXFaROxro5KI2S0wc9Ax3alyn83dym4rNSGC8s37WMmc3kdqz8W5iYdavLrUqIsoIGVieITTKwxMWCtpPZbC+utTkQtO3fSaKh9dkV0FFwW9hqlNX5LWcUaKxvyr0lCwfg9vhJZGqPqF/TYSMcRGZLRRw9XVQSXJ7Vm+HlA6mHujHWUbn0AJUt4R4u5IG+hrCsrmJhoB6JWESt8WOC1Acx64BEcNEhaMAoxBaWUsZMNPL7Zwb8bqGpx6qIrdnzHU9xDk9uxnltHItZEZADWlJlsUDSd1Er1eA==
*/