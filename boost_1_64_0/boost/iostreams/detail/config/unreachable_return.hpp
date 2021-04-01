// (C) Copyright 2010 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>

#if defined(_MSC_VER) || defined(__GNUC__)
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    BOOST_UNREACHABLE_RETURN(x)
#else
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    return x;
#endif

#endif

/* unreachable_return.hpp
KL2xHlXghOTQWZCxw4WAZDYip7xSX3HNBfmjQKuys2ybYaq60W7EIWvqAwOz72QXlRkBiSajMn6Lj8akgygxP0/KluCq0jtCyMpLQAs53WIEMCfi16W2wQjpEx7OPB5qp58wMJuHynZHh5NotUwqB3cHE4kgOTnUnSzY2iFNYmkY4alYbxV+7Nh++I0LeYmUr3Ni566sXkpcSwM9kUxVf9WWyuRXDs/VzgUEkcl4K+Qd4j3jscyDmDgHZW6V2HvKt8u0ztvTXXmP+scosTpCwMhN74lI/AOdkzw1Bg4xi78oPpdI5kdObmrSxD2OEnpWC8iNtZQkq3/mYCzzaAsm3C01KAmDG7sXn7I++dkEPcO1puMpHD6E2/w9iQEwN9PgPd62ZptGP4MwVFOSOHACfq0L6s66Jw7YS5/PJYOtcrARNDa5mitFGWthuIc+FmaofP7kUFolPsd1CAH635sz0BZ79SYNyhMQcxl7Q/vyNhaseKD50r/hd22TsgEYr2j1hTbJXtYe434BfLToptIFFdAneGIqItxC20bzwxoiCwZXN048bWL+Evl5EQ==
*/