//
// Copyright 2010 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <csetjmp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4324) //structure was padded due to __declspec(align())
#endif

class jpeg_io_base
{

protected:

    jpeg_error_mgr _jerr;
    jmp_buf        _mark;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* base.hpp
Jo6DRVjhLulhCXNF0BGscsEAkia8mGwNo889YXBFatjXjiAjyFzZeZFtKTn8kRqtKyN+IVKBEGB+953EPARmjdK84HtbS0grjnkI0f1JQWY9G2vHzIenNjM6P8aWjqWg/oGB5FdAAJ+FGG7WAau0pEvdw+hIKiW2KqaWKm3xLYeohzhFsePfHi/uUHSyZMKS3VtXXqXlT4O9OYUd/6oQJhEPLIkZgoUA18n+IHZ7kZslDOxeLqCOt2W7ee3qH17HfOQNcuvBqHuEZLXuuzlS9tRpSQ7M/gq+zlODhBFaPu7sN9ys7w5cA4/b6faFi5ahKU+ErG9/P3vCejT9NfAhPv6HOJMApd4LzKH/9jarjTSxoksXTJilnS0XF6NJoFqhIK6wiGLly5UTemTYyau9m9jw20LKOTJTQaCOmC9i3SUkmUhfmg01+vRV/VuJSMMbD8iMwGTh91qn9RtPadzckd2F14eGGB1O8KHdmN0y7SOGBFrfl2DfLAZSywgR6oYY36phqfIYvU5U0k840FwgudQw8wytVGxKZlkwwYt3Ah5XGhYqbbH3DYu84Wthm5cUn/xnnqa70vKK2PeaxPdrhrpfbp67qRRitMiPT9TXTrx0y33I3R68GJItf2CdgGkaPyP+UFtyOfQvnCtgsXj6axO7U0B/V46tl87sR/WutDdRH1ra8juIgxHcCTGMPodvTHV5AMgLZKcQ/6oS
*/