//=======================================================================
// Copyright 2001 University of Notre Dame.
// Copyright 2003 Jeremy Siek
// Authors: Lie-Quan Lee, Jeremy Siek, and Douglas Gregor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP
#define BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP

#include <boost/config.hpp>

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_GRAPH_DYN_LINK)
#ifdef BOOST_GRAPH_SOURCE
#define BOOST_GRAPH_DECL BOOST_SYMBOL_EXPORT
#else
#define BOOST_GRAPH_DECL BOOST_SYMBOL_IMPORT
#endif // BOOST_GRAPH_SOURCE
#endif // DYN_LINK

#ifndef BOOST_GRAPH_DECL
#define BOOST_GRAPH_DECL
#endif

#endif // BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP

/* dll_import_export.hpp
8AI2uCrUiyYeIH1qfo2WE1r6bIvsRcULsQydPIYMi0SCVjFiAcNYJRtKFr+Fh8ZIe16fypHrIu4PDAsx7bXSiZLzj4HArsPR6nJyB7Uz7+ey8hrE0x0VlF072tucQwNRlHJSncqQWjyGhw/knDZpED0BcG47tS4SMyKSQemNK2hqub4ulwD26aLuK+Yebdw9U4k/B5d+ZR8MUMw4Ks8YK6wp6y0k3doatGWQbFU8fhsJhvlkyqbbPCZNsoAFKKzWvPR7iGU0/qz99ZBaSHH1TBmbW0DdHYva6zu+dVzphCKfw7ZPITeTwOp+I9CgTvveBrp73RXjmQKtlHQkRBaxKyZV88CJppgSe19tckdtc615A1LZ8LT/lzNbi240DBcinMPmIu2rUcXd7IKeV86++QJZyoC3tS3sKVvD2ughEVznutu2g2SmvLhFkx85/sp6FGsEgVIx8fF/XjMJRtW1Td0PMT0PQTksMdjcVgRwIu0AzsT/6sbU53OTKcr9/nJVITAXGtdN9AJqYc38tmVm5k65YXogYHcqgcH/YjiwDI7vDBwCGzl9Cp3Mfw==
*/