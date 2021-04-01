//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/lockfree/detail/prefix.hpp>

#ifndef BOOST_LOCKFREE_PTR_COMPRESSION
#include <boost/lockfree/detail/tagged_ptr_dcas.hpp>
#else
#include <boost/lockfree/detail/tagged_ptr_ptrcompression.hpp>
#endif

#endif /* BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED */

/* tagged_ptr.hpp
Z0nMINQJB1hNSStONZzn3Ejjcu5cYDYtxfCUX0GBDP6weN9fr+u32jfPXpnGZPIFllSMKofiiWbGdXk0QyIXJgNqt/v7B1DY9CknDl2ejfC/WUYk2NE9pjG+Ks9D9eEq8dS+mFYkrowdJizG4EEovH44UousmbIyaFhx3sOk9Hl8498pxZ7iH0gGUMJ/BoTUoD7hDN6YnZSTt5MEknHWWBPXw28JRsAkOOoM0VKSos0pE9HF5p3oOEQxAQtHgbiR6n80N5NNGBr5pRF7B6ZUuQCzaYz9rp3YcVh4FpvZayPRzL7XVZW157EmYT6nBseMAk2iOAe2L6QB1EsJ9+s0/J5coCHmicV5H5HlFyFCLm499R+5NEG6ZfchvpEcqcgVVvRoox2ZUBs0m/CiRavHvska0Xt30taVnUN5vqBY+dnt2XaoV9d6gl5KaGeIePLrD/nXpoPFoa1QTH6ergABYC3NmLnpWalb6Iu5AGVQ5PbsV+afLDJzybds3GX8yAuwfcrjVB17hglWErnJ4MklfipRMllH+3W0pwjQ2HazMDepbdHqDT5n+jO7ww==
*/