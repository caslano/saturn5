
#ifndef BOOST_CONTRACT_DETAIL_NOOP_HPP_
#define BOOST_CONTRACT_DETAIL_NOOP_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Following must be expressions, not statements (as used with if.., etc.).

#define BOOST_CONTRACT_DETAIL_NOOP ((void)0)

// Following always compiles but never evaluates cond (so check correct syntax).
#define BOOST_CONTRACT_DETAIL_NOEVAL(cond) \
    (true || (cond) ? BOOST_CONTRACT_DETAIL_NOOP : BOOST_CONTRACT_DETAIL_NOOP)

#endif // #include guard


/* noop.hpp
mnx1GOTh/xzx91fuyaDfez7xNN4LMB19CrrHQN8nbxc/b9CP2H7v+iYO1b/GX6LAyO+9Pd6vvN86X3Sp8T077fr1122wVNxfQOtKwOjrWxTe+TtVBvxBwo2UL3WJDNsICbeXFWFGpoB3xgT8nU5CzlBzGwGzMI3Pk0a3O0+akNEQV0Ol+uvCaLwfwZS5eWepx+RoOSKjbJCFkGl5eXUXZId0Xz8mAVOLOYoAS8JxbQQzsyJ+
*/