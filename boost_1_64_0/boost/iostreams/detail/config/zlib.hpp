// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp> // BOOST_STRINGIZE.

#if defined(BOOST_ZLIB_BINARY)
# if defined(BOOST_MSVC) || \
     defined(__BORLANDC__) || \
     (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) || \
     (defined(__ICL) && defined(_MSC_EXTENSIONS)) \
     /**/

// Specify the name of the .lib file.
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_ZLIB_BINARY))
# endif
#else 
# if !defined(BOOST_IOSTREAMS_SOURCE) && \
     !defined(BOOST_ALL_NO_LIB) && \
     !defined(BOOST_IOSTREAMS_NO_LIB) \
     /**/

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it.
#  define BOOST_LIB_NAME boost_zlib

// If we're importing code from a dll, then tell auto_link.hpp about it.
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif

// And include the header that does the work.
#  include <boost/config/auto_link.hpp>
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_ZLIB_HPP_INCLUDED

/* zlib.hpp
1DmIKp47JF30jagjk/S5l/rsCmU3n2W5HjMd8zDmCccZLS08ntFi13lNLvRW51E2uUbZdNR5lLkKZ1ImGc6kTK5wJqX3s93cZ7XIOZBqDX+/+pIetKWcd+B3v6SleOFsR7U1fUFeHs7u/ruhLlL380+3cXosZPqlDNFjoYptgqpj1X4Dw7PeyrOWGZ51bt6S7LmL8uUVm+4HeHgGWf+u4huTFBnfWzxb0BTfojkilzd/RC5Bl1yCHp4pLJc3tVwq5mFqg8jnvN0uN5Min7Ng0cKZXvOQ+13tSQGqaByja7+6rxRDunR+R5QR4nOltWvDyLS+w/1JhrQunpK/CIX1lC/c72pTZk0rMqdV+9V9sxjSqvPQfcaJxPfz+tZd4Ih9fc+M3ydc9vuu4/Mve8j/6t51qVW3V6D6W3fH51t3/5S1u/KT8U5H7v/OHh/rv2XMpf/+rePv7fpvtfY/PPcGsw3fzGtiqbX4UPpCsDNsCbvBdvA02Br2hylwBGwDJ8K28CLl7zCsFafmaNQcWADa7t/xTOG1z+1hJ3gW7AwHwK5wEDwNDoW9VDy9VfhnwIWwD1wGz4LFsB+8AZ4Ht8EBcAccCtvwEOPgSDgejoOT4YUwB14Lp8BSOBXeCmfB9fBieDfMh6/AOfANOBe+BxfDP8Ml8CO4FH4Ol8Gv4ApY18//+C8JXgFT4UqYDq+Ew+F1cCS8Ho6BpXASvBFOgzfDZXAtXA5vg9vh7fBhuB4+BjfBJ+C9MAA3w71wC9wHt8Ev4a/hv+AD8Ht4Powjz4bDRDgCNocjYTf4ETwDfgz7w7/ALPgJHA//Cier67PhZ3A+PASXwc/hchiEN8B/wI3wMHwYfglfhGPha/Bh+BZ8BH4AH4Xfwcdh23j6irAzfAqmwwCcDJ+GU+EzcDbcAxfAvfCX8Hl4I3wBroP74Cb4CtwBX4Mvw9fh1/AN2CQhpE8pcCDsBtNgT5gOz4TvwhHwPZgH34cz4AeqPHwSHluosWoANse8jbHUXoZz4LfwAujzkf/QD2fDODgPxsOrYQJcA+vBu2B9+CxMgs/BBvB92BB+DFvDb2EK/AG2gYRltYO14SlwEOwCJ8KucDHsDm+GPeFa2Bc+CVPhqzATHoDD4MdwuFrbnqL7otJXkLrIB5NVeqmXtL8yj/6CHv1Zk7z5S/oRf8NiXMNV/e3P6m9/elmP9bNdi/VQgrUHcwiTvCPB6oW5AFOEWbejeq1V9e/4/o7T+3/mnX769/9acabqOjrPtc6grbfsaWumn7KnL5qbW2h3d8V9TUPa3T5O99BZLHiQ9QM7HesHpqk16j1CkH2wm5LpV4bWD6SPGpUt50SokHiWhfoM0dqEcFkSptLxNZOHjnHzTF/0caR5HBx9vNjiG/v6e7VP7PZIcp3UT/vU7L/2yQtbRR+PmseX0cep5vFf1Y3bzOPC2MeXUeYDZDyXYam8hD2UvQZGfQNDxi0258CGcC5sCefBrnABPB0uhE1J365nWCP7TILnvoyzH+PswxzEqL6Ls9+i+ire+imfQNU/oW8i/RLpj6wy9EPWYJz9j366z6H7G/Q1Ku9fdMWY+hVHMPGq/0DfwdlvMPcZXP0FQ1/B2UdQ/QNn38DdLzD3Ccx9AO6Vdt9bm+9s72nfnW27btePPFPdZlf/qn/Vv+pf9a/6V/2r/lX//n9+x2n8z3d9fvr43x6/P9bM0uvadqj3ZKPV+v9RmC2dmAMfUPFbC2mjz8taMGvxlMK8oXlLPe4BIAz9zn1EC/zyfd4pjjX4pw6UszlN7+C51/uegOAAb3sCnGFOkNQXzOY0ef3drxoD1bfx+H87TAfWa+6wQuP+x5sRV3yzuoPrdqg=
*/