//  (C) Copyright Noel Belcourt 2007.
//  Copyright 2017, NVIDIA CORPORATION.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  PGI C++ compiler setup:

#define BOOST_COMPILER_VERSION __PGIC__##__PGIC_MINOR__
#define BOOST_COMPILER "PGI compiler version " BOOST_STRINGIZE(BOOST_COMPILER_VERSION)

// PGI is mostly GNU compatible.  So start with that.
#include <boost/config/compiler/gcc.hpp>

// Now adjust for things that are different.

// __float128 is a typedef, not a distinct type.
#undef BOOST_HAS_FLOAT128

// __int128 is not supported.
#undef BOOST_HAS_INT128

/* pgi.hpp
3LWak4MxQU6hp6gseY8OQJ7mC88hvv9AJlvlDyyZ/fLEGTAea/r1ukJqSMUX1Jr7KXP7pYrxq99A05czPGqvcP4dI5hD7tKcO+zqsyaj7KVIVJtaYChFsnaI5BzRLFFYXiMKbdPS5oiaEW2GXKtcA8s9MI/D5DtdH39Pfr3IfHniOClcbb76IqAEvRKihhpvGPJtLA/0S++W5bq8zxtX2X2OVqef6+iluJ0mGmKpMVxt9K0x0yafjR0gBjfli8FoKwfvUdc8qvY/5bBM9YfFCzMhJ1mv9VjqtbKcvLSO1239PAftzY5bnCozutWT9eYai1ecgTH7Gbi3e6+xhBCH2lfwVVj+DuPJzROjrO96iVsmMUNbUysMpkv31tQVM116tqZKpekS3ppaRbIZav975PbU6ky9tVj+KMsQZSON3OSZqVe7nFvSeEgVy72uzapY7vZsVsVyd+HmorrisqLdJZtLhxjestI9w7YN/9WIsuG7y7aNXDp8ROmqolJVar19ltqcEk/phGGe4cVlnpGeUvO9OF5RXF4qiq3zG/r7n0jV4zKv7oNlgDtPnAvDNZg79UJL6iJdbVZ30VOePqg0nk9Vl/rl4anDiUbrgF3PTV6tFmDOcCczJjz8RZf4aGjtO/ZW13U5292bPdPyJxqeipy2grLiVSVlxbXKjFTmr6X+YSdzvZNKS4snFRUWFhYU5BS4ZjsLHAX2SYZP
*/