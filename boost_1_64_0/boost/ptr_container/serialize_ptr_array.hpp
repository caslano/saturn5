// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_ARRAY_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_ARRAY_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_array.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, std::size_t N, class CloneAllocator>
void save(Archive& ar, const ptr_array<T, N, CloneAllocator>& c, unsigned int /*version*/)
{
    ptr_container_detail::save_helper(ar, c);
}

template<class Archive, class T, std::size_t N, class CloneAllocator>
void load(Archive& ar, ptr_array<T, N, CloneAllocator>& c, unsigned int /*version*/)
{
    typedef ptr_array<T, N, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    for(size_type i = 0u; i != N; ++i)
    {
        T* p;
        ar >> boost::serialization::make_nvp( ptr_container_detail::item(), p );
        c.replace(i, p);
    }
}

template<class Archive, class T, std::size_t N, class CloneAllocator>
void serialize(Archive& ar, ptr_array<T, N, CloneAllocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_array.hpp
27CGNmI7lWcCo7yUg686F5lfhZ/lfGsxOaYQudAPmdfF7xEX9RCTL1O+DV0mx1swLQubz7xYb4Q4e9G6DP2M+lJ4930+tqscOw7v+ynfuJb+RvK8n7q/NoP93oo8EHv0NrFNmPWN/i14ryiTu/+MOR0M2o7skneYgp89Fxw/HLtxBnPJeYqxD8fuetiPZbRpQm7xD3tjN9ais5XDqFdQlPHgrF2JxjhX/Xh88z/PCVTe/qcPjp3221E3TYa2u/rShX714e7qZcNxz+7xWNvunfr97K28DHyl/mrxUP5TPcA0/b8R/He8/soR3s3QtjC/X9x3Rgafde7oVS/zVe9ylN9ig97H5+qiAb4pGBS1NpaKb7N5sj2iNp/rMt/vSqGZb3cVJL8LZn09zh4Pbxrp9thjdwd6Ah3623QxPc4wPU6mGsff1+Z3Xj3J1/n7mJA/HumNtYXKbPqcOfoThWYe1t/z0tac5+qQWYpvl8WjoeR39OL6OzAHM59MM58hP2E+EV7z2E0P9pzMv3/SvA5M827JzZ2BfuHk5o70qflebnbqu8Kzsp3vp6qyLbOtb7wO47dH0ajn8bjryO9tm+9ZezzUoD8PZdnWd42zR1v9670y7+nfgn8LvulvoW8DLf0CzbtaKbd68ah/6z6G2L0YWqF+H7f9kUyLr1t6Rmb+LFu8r/V/xNfypGyFyiN8/TDQ4zHyH6rmlf8doZjH6ECoqisSSNj6gWWpjPS26nc3n4YMDjEy+PN0MtgZ6uJV3imkviJ/oCsBX35ESdLUmzeouzRL+/XmyebmzUwz9d+difk+sUt2s4XsqrKRRnZzzJ7vbWQwW8ig/j4v/043QyVH2ULWWD8UtlbI0JD/0/o/yUzKWFkPnzXBlHqMjFVE9BdUHVomtPpaJXqxdl7obhUYmePbea4Ciz7ME6oNqfcjW0RNy1a0RGckKGj5or0sVGXzRJnoTJcdkZynKRFjezLsMtOjLMsKze+KtAa6TJFci2eIKVOf4hBz9AwLCY6YutnO3JLvY5ZtCs1yXIW6bF6ourKmVn+yUvaZeYTnCHYj0jPQHekV/B9yhPLU+rXHwVB7Kp29ae7h5cCyH+jIVcjLVz3M+hw6+1IZaueTH02BDncb9senv/Rv1mHoao9q1Ef73fXZnwbrgwAD7nHU/niVxXO3YW+aQnxOF6PqaqPLJFMcemaouqsr1MEM5NrVfpXFB3raeLFzDwxz9ff94fto2YbVpr9fYxMnGJs4djNtYi9NHeUy/7btofnHPPX7J2rgYf+2LTSDSTPwb4yv7N84l/3rFX5ZleVp++d8l3yOsX+5/Nvmg7J/2/Fv16w2Ou8A79Pf5DrM2L7tf7Lt+++sd6HxqUS7vGQ+oRCqsW1xvmrWlZQblSkN2bLn6Qn18tmnLiO/W3haIwm+7dGHHG1h5GhiOjlKdMYA2/SbnKOg2cIjCPPcDdJju9bNkxnRmWTa5o2hv4Xukot84RdV2WQjFzuYvXSVpcVyOxostxO/y40cqX4lWxR2myJpLnmiflKeFC+GIE87S3n6L/NCxCGgt5jxj+ozr/0gfmOz+Xd/YEDHRDIO2SWdXAQ6OmKYMf2lmx+GWKLmfwXvu/oTrNjckQze39UlG9OEbKiy3YxsTDf74ipLKxsFRjZ2F7IxTWAsJReF/FtO1Y3ppwmcdaCRjSIpG/8jnvRtXuzJ5/VCYWRoc6JPUTf9yFvfX5Qxy8TUF47DHpdkgK2//54UPT+z9HqPnmL918DfT06x+b3lmAzaZJhoPxPeKdq20Gbqbwg4tDGGtpOoN8HQigRtqqFdluHQig0tP9OhzTW040TbRYb2qmnLNxnG8E/Ot1qCwZY=
*/