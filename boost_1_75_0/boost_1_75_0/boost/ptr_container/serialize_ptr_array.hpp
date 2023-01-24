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
4/fKlnZsE5SD1aUaEpTK/vt1QDdMCfLVrNBecGfvD1zutoyGU0qYxUw5kD9IVP7UbOy1QsfKMLTOuXTH7hnXcUp7y7AUlUo7Jag0Z9UzM44eVHDhhLabp9v4Q1+ntUsoWgL3PIfDx+wigyrAGmvD17UFXzD6lPnhHSPH6YtFXXz9bawLBK6vObwSRG9BdsZvedc2sZNDJIf/58/AUFqwSuM0oFJTCAOqQVTjSv/MyYzmWbOZCYA+/SO+QVreDcGCZ+WorOKQvNmsUX00uZPFwC1tthTqcygvzQf9OZsXgSn+HknTpxHFAotEUwTAHrGYrQlIfzTut5xaQYsfKr23LT+17VWEfgFiWtmH2UrPRyKf/mBFUR3e+7hOQxjYUA++00v8U2XXAU/l3scPMkJW2aJCIXurbCUUQotUxqFTVo6VpNwGbUmkoqFyG0paVBqkoaI0pUHKaApRUr3nqPe91/E9nv/r8+l2U+fr//z+v70eaeXMO8Muq53oMn5mn7XiYtstiROPhlkvX13kXW5ysChxRbPjBbfyT2uLkjvXfo0Zl/hszM/pE2Uelcr7ZXmXZtVLllTMrn8f4WpuNsFwgpbvL0bRhWNmuiJdB6rPzlPYPffa8AsyXQ1VI1XcxM5JRxbU5SSqfmw+OS2vIfGiVOwrnxbTox1xW1663nLfIegUskdP44JedeYC1edJPgn83dp5hh1HDvzaP+Oo
*/