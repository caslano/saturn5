// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED 

#if defined(_MSC_VER)
# pragma once
#endif                    

#define BOOST_IOSTREAMS_PUSH_PARAMS() \
    , std::streamsize buffer_size = -1 , std::streamsize pback_size = -1 \
    /**/

#define BOOST_IOSTREAMS_PUSH_ARGS() , buffer_size, pback_size     

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED

/* push_params.hpp
CklzNtR8SInkmRRnu6vgNiOaktGv7/uuf4Z6mkPQrocdAPP2WytE9df5acP9PY/9GdiGbxkM9foMyb038hVrIKOvw4SJAjzX9O//EhtrFXQlJMsWuaP79B9pAVIHIeAcdH0NDKR/jsgdycy2uLTW/C4YSMkhdn8MO+SeGbjU7uD3rac5Aai8YfcYfp09O+s+lhhJNoPJ0cdsAvcuxxezybg3683eDi76k8zObkw/w1qnrJ8YFrTMya4vyeVniv6EkmYpjG28wk5IcgxaoVzIusQjldtVLiLxvgoJs5iEKSZhViYxrhQKv5iFvyMWfmUanwsk2fIKhQFJkD+h6y4WoZKJdBnYcZ05JND3KtgbzXegngVVsKQ+zfQQakll9CqyQ2t+F1ayWGOf5PfsxnKeN6sYGHfOPFoo1ZPvc0H6lbB3nYW1PGZUzIqjhTkZeVXQqZwVwImcFbCJnFUpMzmrolM5K1jk5axgwOWsNo0vBq/3LGjkbFte0CiTqgWNkNivoFmObkcGplcJgsqWhW2UuGr9sMGWueeDrR7xPQsnY1FaODmNaoWT0Ph4fjl9/wD511oUmuIkYJj7pQKjtV9CZGkJ5EppVRft49+Xg33P/rTLfyNLdA2QYO4ZLUrrAdHitITRimndI1qTyYNS
*/