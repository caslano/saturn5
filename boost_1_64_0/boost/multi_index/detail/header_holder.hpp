/* Copyright 2003-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP
#define BOOST_MULTI_INDEX_DETAIL_HEADER_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/noncopyable.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* A utility class used to hold a pointer to the header node.
 * The base from member idiom is used because index classes, which are
 * superclasses of multi_index_container, need this header in construction
 * time. The allocation is made by the allocator of the multi_index_container
 * class --hence, this allocator needs also be stored resorting
 * to the base from member trick.
 */

template<typename NodeTypePtr,typename Final>
struct header_holder:private noncopyable
{
  header_holder():member(final().allocate_node()){}
  ~header_holder(){final().deallocate_node(&*member);}

  NodeTypePtr member;

private:
  Final& final(){return *static_cast<Final*>(this);}
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* header_holder.hpp
EaVJkLuO5j14/TLE8yfJY46kjuvlkTA20aJyVkZfKfz+Sb7eLZPQCZMiHnENuqrCG9pKWutinob/bxY/OLdUMqrExaYfYX4jCmK31/HEGtNJmrhuXhh+syaA6d0eF49kvL7qYC/OU1V288mu131UoZBXWLx5Eaj/Klfs9He0gcMMK857LuF9nEee64JHMJvKJ9uB24m1P+aWqR/IsObt7vT3zyszGneDcR55G+OTwg9lDBa8AI3UJne9itjq99bZFEjWnDcSay5KMj8LskDLwKAhYIluXKmjpmL4DdTR7yeWX42XRW6R2SLsWCLI/+fEfqPc94Msi0EAaLg9vGz+2ZSPEc+Lyyx0EwEm00GLWGoHpbwdUy+vEs8RZhY/qAsN/5NTXv6oLLIsi1LR3xiNkcX+Zq0+uI7Dflzl+St+KfMkdQQbZvyTbvfjbmrFEAvdIo6LTMl44b76DHUnrse4jGtcBuzzxV6Z5yhj8lKMv0uYcntChkHg5lFAZDRLXLCiuxsDLW6zZwYy7ruk/G6z9IO8KsVgS63DYStjp8v74LepNedkVZbDw2Jafw40BnroP5TxPlBVT51C1IcAMIzYTgBWHH297s/4Hdh7k2UG+euZxvRd3z4Tm8usvbek9Mo4jTlfXW1b71+dWXvWMg6kk5QCTNeD1bZn2vg65T8NQQTzXHU70TKO/zDFLyVO6CVBFQmrZiP8Z5j8wI0dv5BVjVcquL1t9cHXMuvsu5Shk2ahgP46WPd6uPeWWfN3WCoJUUL5uXsfuaue8bOqEC5Sh5XY34HNEMiOfSudxNhBOY8FmIZl5FaZLyzz51Z7aXhGl3NfHzdM3SSPhLnMZ30/9syYi3O+DgurRAZhGhpGE0VPtQFuc5lnQcXUyK9mN7fOZ6VfhoXnGjlo15IB5BobJ7ferwnSNJWZh7z0WVQUwNdF78utfbHId/PQLUcyMAAUqQG3775BZeT6Lb7ULTIUQWyGMxgP1O7DuIyyJJKKCce7XkOq9usqB0T4bc2qhOmLqYLXoSyqwC3dnMk6uC0c9McqrD0e6csk9qXQKoQ7H5Qb7a+K8UaiqNLAS8LI8I7nzu8UbRfMHyD2VTfkpbCNrkV4g+sJT1FnWfpZJeO/rsPWDwcqDehLin59htHVjDpQo3h07+9vEOCvFSwvK4/T+ijJ+A8M8K7DtSfxWMyVLJzSDQ991wHKdFqVSegyD4YdMEk22k0A9Dou+pMU/X3PArrykEbSqLw34e5bK3h6VR9ygGh9AkTvXG5MT8S01WeoQ2RBpWycCXWFmFdwDPrB0vzEzGQMNCSVtTA7jsP4Ohg7i2IwQDur3yOPTMbou70Ed+/bTMSpOu7v0DuWbxzHwekRynnObSkdg72bOO2I+/NkHNYR75EenYyDTSqKe/jtJuP0ypzglm5/AK4+q0fcPw/C6TGp7B+jF8cm45RJuK+mvSvgd0/16DrHQ1dgrPsHYlwwwJRu0l4bqPvQ61vtDig33tf4kKbrNH0T+hH4Fj5Lb7srgbPsxW0vr9phMZL/NcDpN1+ZjuK7UNfurOhwpwKLqYd6HqzGpV+jEXvv47fCgmaMsG+7NXb/4girRvetsHBFhMi9JXag5nIi9663wDY3RwqzB8HmMrgwVhS+Wxz6HRQa5z5o2U6zo/tFj2wZOpKm7kl4wxbc1ASdWcf03WlM391X6fjG2fY0vHGm+1elg6UJPl9DaOP7mm+gnlvbNehiH57Ob2OMiyfSumcihI15rzj0+03Lxu5+El+/VrnjRH5Z6cgdc/Mb/8Vfz7Lvr0wt0HtwoQzS3E0ham2UG8eq8Flm7cfyz0SRenEWFuzdcojZYbI8yf9hSBsabt0=
*/