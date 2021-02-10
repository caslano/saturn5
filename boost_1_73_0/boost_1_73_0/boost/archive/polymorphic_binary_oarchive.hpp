#ifndef BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_binary_oarchive :
    public detail::polymorphic_oarchive_route<binary_oarchive>
{
public:
    polymorphic_binary_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<binary_oarchive>(os, flags)
    {}
    ~polymorphic_binary_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_binary_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP


/* polymorphic_binary_oarchive.hpp
zre/WZM8KzLS1eiuk/0nFANvSa9WmdTvH74RiJ3cVUfj8OTN8OODk9R6qbIc7OS0aCM+qPT7WFEtJp4AlxlEAVvqdDsWv4FgC7NabfW+v5jVgvvMyj9UTKu5DZINWTPjVqPTW6zJu/U8KSdXdrailTqjsMfcHCJLtTqQJk+yijvItFKUm6lJXWPWbU1ramrQupaqf3z0EUrilf4McSD59XKmX13/JPZFwM+NxT4bSfLortHavt3mDK8+Zi2R0ZXuxy1GiVqMAo3uqnjhqviykLmlfRvia1jeYW98PXIdsxbA2KVnW+8SYULbnZzMzXedZVI8jse1FHK1i28wf6CgsSUMQLSbbX5uOB9osH7FzMvVD3K+FwMu7/Ehw+NJfSvHitd/yFOD4TmP+mNuGpyctxn2R3zkR/31jynl6MyfK3eao8NP4ef0/AjHHxyfvBXGsfg/BLj48rElIl0eDH3Sd6LyqkDxzF76TCnxilV0TUiupXj9IJ9Vg4aQiX62NLmA53+H3CQ7sdOoLGpzzC6M7h6uRodi9DQ6clB8mIzoZoP+NqvsTv06GY/aGP3ZEfl1np5/uN5Sr3R5EiaZyuflojZi551s++kAVA9RB2m1MLZ0nUD8uqimB23CuP77mBus/o2ctBJxEmgr843o
*/