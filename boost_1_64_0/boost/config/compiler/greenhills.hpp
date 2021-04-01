//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Greenhills C++ compiler setup:

#define BOOST_COMPILER "Greenhills C++ version " BOOST_STRINGIZE(__ghs)

#include <boost/config/compiler/common_edg.hpp>

//
// versions check:
// we don't support Greenhills prior to version 0:
#if __ghs < 0
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0:
#if (__ghs > 0)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "boost: Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif



/* greenhills.hpp
g467FiNbqcQIBsqyK4xTp1/mOCi4kSoRuD5IWixMo06EgV+OUxqU+JJKU1Ut6+QEkTHcARqRjJJ4YAgspl/nwnBBqcEjszWrEDJ+vhGqz2ypgvu1YfbLZHkUNbaKe/it0s13Xz/W4hGqTSnAIc+NVdHo//uqP5mwQfG1NKtXH2zSZmLEwjZSjG4sg8JO2o346MhfGGAPvJQj4011gipiW5RVzpjNRsK09dXwWiolxBeP3RJ5Atg8Qc1D7DzQEsU0bgbVQ1ETxpTi4qC7wgHXq7eQsVUiyjyWm4qt1FbPlhRdQ7QMU5qqzbIMxbgiT+zDcYRHqImmsKCwCDzko3x9KDYoHnU8UCmkE12VHKYGgry2aA6a1CwRVR5LZTZgSHLyxxUujlYB7VAf22ipMwrt3xDgRROAUNQUsQkMNPetg55LnA1OlHKKTOCHjiN6r7tEyx60n2lkxDe807lvLeSg+gbBZuohksUcPBKm57dab6lJsk8Orga58MekMIYenZOUBtC0nMXOf7llErDd4JUeTHOLyaqROHw20rS6R1a8tXFSLcOwilJLTqMDvQ==
*/