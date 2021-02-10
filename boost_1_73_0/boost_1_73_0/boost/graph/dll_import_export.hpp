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
NrTycpqJspUXx0SpQ/A4uaNVQFNH4bA7HWI4qE1rrb3i6KoKYz6PqD7QVkpbCFEyCC4ZqhUgRDD1d9MJ3p0EgshNlEQTaLLHlOutXUrYqJNUm9gN4iQ66HObgz5RhXPDPjGGCin1Q/wRufKTX5MnyD7lGcZPyfOJE/T59KmzJPhBbLcRbQ6TcbxQO80ithhKP6H9BkQnTpGkrTQ7FJOkDYp8RwZKVMMQvuCS2cSKdHHXLnefRHcauntqj++ibqk9yjuFNff4oOSmukIGSGbEO2kBdgtug4w9kpHCA+NTOdPCC2pEN700JKDKLrimWtc1TC4gqPE1XlcAUFsySRXmREZVzZ8RIjwFgEov5cg0Di/I2GRGYaFZykdf0VSG9uWjDsrPfKqGJ6y5EZ8x6Q4mTBgtwr13dec3umjN9KozO3HShzyaIJIpOkYLVJVzf0dT9pK047JhHInJu3K06knLzmWDKdmMHJ/9/jtXPJB35TEA5lDmlAjM0kUrq4KP1UJZY39FB5vm+877plOeojGrGqcxFQtyyw3ecZqN4sykaFHeOPsHSxt8JhnK6T0J69PtMAzqCySqEWhSBRgDzWScjKP76S6c9Dyo661F8xczuDLsYbtUGxsVLMeyF+VwF25/zS2j+cw18OBPJU6z
*/