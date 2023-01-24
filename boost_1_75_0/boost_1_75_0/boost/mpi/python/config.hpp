// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file config.hpp
 *
 *  This header provides auto-linking and configuration support for the 
 *  Boost.MPI python bindings.
 */
#ifndef BOOST_MPI_PYTHON_CONFIG_HPP
#define BOOST_MPI_PYTHON_CONFIG_HPP

#include <boost/mpi/config.hpp>

/*****************************************************************************
 *                                                                           *
 *  DLL import/export options                                                *  
 *                                                                           *
 *****************************************************************************/

#if (defined(BOOST_MPI_PYTHON_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_MPI_PYTHON_STATIC_LINK)
#  if defined(BOOST_MPI_PYTHON_SOURCE)
#     define BOOST_MPI_PYTHON_DECL BOOST_SYMBOL_EXPORT
#     define BOOST_MPI_PYTHON_BUILD_DLL
#  else
#     define BOOST_MPI_PYTHON_DECL BOOST_SYMBOL_IMPORT
#  endif
#endif

#ifndef BOOST_MPI_PYTHON_DECL
#  define BOOST_MPI_PYTHON_DECL
#endif

#if !defined(BOOST_MPI_PYTHON_NO_LIB) && !defined(BOOST_MPI_PYTHON_SOURCE) && !defined(BOOST_ALL_NO_LIB)
#  define BOOST_LIB_NAME boost_mpi_python
#  if defined(BOOST_MPI_PYTHON_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  ifdef BOOST_MPI_PYTHON_DIAG
#     define BOOST_LIB_DIAGNOSTIC
#  endif
#  include <boost/config/auto_link.hpp>
#endif

#endif // BOOST_MPI_PYTHON_CONFIG_HPP

/* config.hpp
q893JVZOEOJWhdJui1LvITxMbr4dG2smGu2aguPOMbUb1qQu50atYis5Dse888pCxJK2kR6ijHp3rsTQ082UfnyiQHEXKEoNwlUmNZAY4bijEfsdgWPc+nUmTznRiCC1lx+7hpim9v7IkEC+bnlAgm64QWjuExaIbtFJk9RCcBRoH//5iyAt8nQ+lai2LybsC/Uj6yqCy7N6yIulhmNtfRUgNj1f8haKw8d73Y+UyzPbx6idx1Lb+j1rUdPeDZx4wpS7Ta2HUawl/BnjtlGQNEHGI5A0rmTHt49rylvDrurhNbNuTz3UhGw58kfjReWMia7u5XxFlaHW+bxDzzfmQYZRzsQvtoQMnRsUSszoZ7q/95b1ourlsY2QVknGR2iMAHZvrJ+nJdC8ovdvNdcFPzXhd/yssde4S+3JlBnz+FY4sfbFnudmh30kLGPoR6urouZI6Ilc+Xs/bCmucO6K5pKavPT9+bHLlG2Kav2Xbprg2cwh3SgPpaNEp7Uv9KTt7tV0zJpVxn+Ed2qPXna//ftpk4o63PlIkF6X7j7j7c1Lh6i/hQpoo7zsSifiXG4QHmnn6espsCY7zj02KfVMEK394N6tvL6pEun904a1pdGtJVMvoQ3udDUxWoHb4tRXTVGpO3dlEEr2Z+/013PqAiQDEfnnyQW2LGqoExPLZrDS5qauelZS0gkJVW37nXWMfqsknPS2j7DT6Jda
*/