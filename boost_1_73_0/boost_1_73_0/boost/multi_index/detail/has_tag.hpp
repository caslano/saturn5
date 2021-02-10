/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP
#define BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/contains.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* determines whether an index type has a given tag in its tag list */

template<typename Tag>
struct has_tag
{
  template<typename Index>
  struct apply:mpl::contains<BOOST_DEDUCED_TYPENAME Index::tag_list,Tag>
  {
  }; 
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* has_tag.hpp
YK1X+28buRH+XX/FQEUPkrvWI0UfF+eMU2w5J1SWDElukCLAgtrlSrzs60iuZLe5/70fyX3J59QucGsn3CXnPd8Mx8Oz3+/p0Bm9+Pj2n48Hq+W4k9nPPNDPU/v+V3I/4PqM9SUlQ2pYvvp9epnlK/Usi19qeWfeff8lRZ+Nbea/oeH87JtX7IDNcF5l+aMUu72m3lWfxt9//3c6pzejNyOPrlkqeExrzdMtlzuP3oV258c9e3gYKH7pEdfE4kEparMXilQW6SOTnPAei4CniofEFIVcBVJs8SFS0ntOkYg5XS3vPs0WHzw67kWwN0Ies4LUPivikPbswEnygIuDk5EzqSmLwA7hoVAaAgstsnQA3Zw0l4kyMox6FquM2IGJmG2hiGnaa52rt8NhUMgY1g/DLFDDoHJ/sNdJ7cknGJGwR8pyTTqjQnGPDKVHSRaKyKwICDbzYhsLtfcaa6AqDYeZJMXj2MgCn+DKmc1pXYbHM2SUw2KhzaKyVBlVx32WnBAijkZKVMgUihAHEIUZwuxRkYZcWmLreaWijKkN8DdT09gbUpbCGOpO1jRbd2nLlFAefZxtflreb+jjZLWaLDafaHlDk8UnI+wfs8U1Ui+gTBJ/yCVXUC5JJHkseFjq/P2eYecPIg3iIuTU
*/