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
PO+ov1OWdXgg9kp88xnEe7AJW/w1bUBeO/Z31em/dunnjnoFXly5FWO6z7Fn8OMgZPfts5DJSvTIEbQP/U9t5qrbaKMvFiOPu6PvbkC/Oa7adRSyTxoX05emoA+u8/u5P5+Ebqs9w1FvI3+PMs756Gnsk99HBjFWuZg0hqGHXnWVty00P3jqb7mu2qAvvCS8r7+3Igf78pmn3rnWU9/c5KqHT8RHeA99im96YAd+G2OtPviDN53lqj/Ct2fh9fH3IfMPMh4AP+JhR6d1DN8iZDW/l6MWXcN8TRt+PfXpzbj92ktd9ezf6S/YuIX0jctvQU9eTHtVMgZOsOcQX3P5eYGftXM//Gv6wOn45leBjcCHu+dT5jt6Y+/pI39exXjsDWQAW3nwdfShv1O/0eiLIkc9TL95jHJ8ShttUI3/z1zIXtu66t1PGGdiE58c76qb60iPNBN7MU9A+r2Q0UFn4+/NgF+noiOfpG2uxT5RholLaP9HkTl89jJ0xifV9MGljnrqHU+9P5Ux8qH43ROxVY3I6tnofP9sMTaijvYu2YK0vyXdP2I7/8p4tZXwdZDPTxz1+3WRyx2Q3TL8IeZW7pzG3M859NsL8Ml3dFVf2mvY98yvlfKe5mHowNHo7xMZP6K/tn/fUZe9j045XDHYwH+k755zgqPb6yP07w6F9GNF+w9GN/Fd0Y/xNvLyYD/648ekkeOoBfgXpYTN5CsfTDK/RYciQ2X0/56MAV8a6utr9AJzouv1ZX6K/ngXbein+Rx+4cJcT/2wHNm4Ez8W27BsgaPuZRzSQPgy5iAWborOZVxUvhi7vTGyyrjhSMJ6VSAz/2TOCF0y/Hv8262wV+CH+2M47NUcfMwVz+P/X4ksnarQMchvkrqchi5nPsjNx89qxWd/FDvVH9nZA7/iMcak9OWlhczNYTfueR3ezUcn4Sv86jlkCpltR0eq8Yw18A329ZiPI7/X+d4eTBopfIQPsXc3MdY+BPk7HHl5gX2a09AD+9IX8BunoFNfhPY1vjf5FLr1hecZS+fS35Z66mL2lI08hjkbaFvQZdPO9dTTleiyHT0KwdgbO3Uh7Xvl09jHNnyOMczd7Mm4H93/Ygk+12j6RBJ/Dx1VPIi5IvgwGf+51xDs6MvMTzyEb/4Ueu5z5qHB/DnFD8njtBnMYX6FbmMuZ7vTmC+6FT1xHLodmmsYN8Ae9Sfa8zPyeQD79+osfHq/vxH+xXzmzwqoOz7QqJnUeTNH3Y0O/OTJ4Jzc766FHl9w9yT57OeoT/Gxt34e3k6iTb+Bd4yZbq9kTNDEeOxP9BHiTEf2V9NPe6Cvd1yN300Zv9mIej4Mjz5Ebvs4agK+VCm0O/R11D+xSz9wMee7k/DHkaPb8SUGXYye+QXY6fjkR5HO6+iJk1zmz9BzxBv+Nu2yEWOGY5gHoDx1ecjmWMbn6L1q9OZrM5Hrb9Bx9Pe3DsXXvBX7Qjx/f2fhK+hwZHDc7vha/2rvvMNrOsMAfs49UTUyzBAzao8KrT0qCKJEjCBorQbRJJIQo0apqk1tasYOtalYRWsTs0YQq1KjFK09qr9737dtWm06nv7T57nn6e85ved8Z3zf9+7vpKWusJI8ZiR+6Opx4hB86UxiPs9kdOBdywgMwy6/ajPs31ttIxZ56IX9rMU9uxEXuOADecdOWclZq6Kn2amxPaVOPwBfwVg+YwzH4wMWEct5TiOOi8Du50OXueYotdf0EdRMAk1jSxObUelD8ukh5IUBjIkHf1OxnjiL98/PO0UHmEYi9cNuM6nZ9iN+mEwO8JRYkBzdn5yoeyFyE2KPXAW470l8w+e0H0R/hzKnbYhjjiLf2KoTs4n98ck=
*/