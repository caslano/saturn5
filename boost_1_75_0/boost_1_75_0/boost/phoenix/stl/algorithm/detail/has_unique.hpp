// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_unique.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_unique
        : is_std_list<T>
    {
    };
}

#endif

/* has_unique.hpp
Ir54Zyo5n1Ko+4Rj83A+7+hbRYhX5H1B+L0OTWx/uJ67WXz8cU0QmziR9zWmQg2nXrKh2MOoyFP8V0QYxYcHjtF/GBLwNxiOTYVt6HkrLf2+LWv7Jt24D2wG0umZvTxGUlg9HTEED9ZLaPLf1sh9/o1Mj6mp4iquv1G/CJrhUtXwvMnj+Gl/oncAO7DS8DSzGfkVkp2UOx+KaAAlht2/akYHlt0iO/JWJTURmdwWqDiB4OHSnYt43yD1CfWQNYaGne8Z2yMQ920Ljn97jjWrjTsu6pgH0KUCGviceR79Mv6EvSvpNLD3jQFB4pGHg4OBjVr4mfmhT8eGpDdu5KngSfeZ4NKaNB+s/cvRGut8sHd9YFjzaIZa7zGVa3v3Pv32vg5hNjCT6Ml5hKLeP7e8x+gF6zJpZg+wqrkX6YI8TfXExk4oz845cTSfPXfoC/QdaycQapGVdbbhEHLydmcnqnWPi8oa3ngha1UvmzYvkdf0hw7mm6i8RkPNmODULRUFeVmWAWjv+go4Du3f9+VpaTWmBVmqKIHKPxsvubRbfgXU1c6bfwqkLrDhpD5xEnw1ZU0W8HtHYdvdsUPiuyGPDe89y7q6fCfLle816fXSxdcdIiCg/TYWUINXx23DC2ex6WRsMt9MZgDk417PEZi71uwe0vtqbZdk2QTl99VbPTPqaN0UweyqB9USNkyy1rVKx8zvSf7d11/kOrcp
*/