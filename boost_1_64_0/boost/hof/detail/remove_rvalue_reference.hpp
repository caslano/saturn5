/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    remove_rvalue_reference.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H
#define BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H

namespace boost { namespace hof { namespace detail {

template<class T>
struct remove_rvalue_reference
{
    typedef T type;
};

template<class T>
struct remove_rvalue_reference<T&&>
: remove_rvalue_reference<T>
{};

}}} // namespace boost::hof

#endif

/* remove_rvalue_reference.hpp
ivagXAH+jSixoidtxI0hE9bEmO9wRPW76Phvi4o/Zfx96MkcPbF3lIQrOoknToQncavjM7s2QNs/CyaHp8dHBXgPVqn/Den+XSMvDOOzOVhpdcPuSM1S7rd2bQPs4z7yE3Url8aj+ySjJ/P3Lvro4g85AVH+ne6wODxXuMXP8xFmsBaQ9j0fQC+X+55aCg+qKYS++KveUr945UotKJjNm53iRbnei6q2ZKq2AYe42lL1apv3YXtQGaonLQZwwhlIlLlVJJzW54ts5J0nqOefe6H+rfiO3czmkxjpylA5v9GilfPiGK2cFRXTneLdRI0bhxlll9xwP+pQ7XKxDkLKY2CpeFf5zV6qFjTmp+xQ3O1vanFnaHGzej9F/yMt+ik3IQHqFPE5JLPrTLL9+EfYMsGB34Jre9J11Scu552wQCes+3aXspNGDlRhguuVvZlpI9ePksJdaZ6Fuy3kvi/CHW7rL9VjfjbCTcnX8suWYV/vo6kM0USaq1ynudIBxm9+zIubwTQtK4UguiDiEN85Rb3aAeWRyIhHakGxGJsubmJfdpLI5Uf4Y65pVCrZrrAODAbPBJPIgmRbVzx/Qs8xpnHKdJlWqviwM0jZKxWnrBFxcE+sYl8JolnztDvCkzIxoqTHZG3RCSKnskImYBbLtLAPRIadgrCtV6DVZFL10r9FTNf8KxH+pbx2dLxe6d/4VH5L/aPSxVBrdFWwQZzYub1K/d9KE70iM1Gp12glarQLki4VHd3COxe66hwuHk5Iyxu/KPHt3c6SuF08FUEO9eWLXtf68t16gnOoI28wy7SQ7A8jwpYvfSi3p30D/p7N62l/B3+X5eMEO96/jd9G/LXh73W8z8JvNf5O4fmOvJ7/t2ePpf0U5fhDNIUPOMGdiG5sVkYl6B+cVezDdKeMDlHMookoxSFKslhDlG+EKNj/JEqJRnGJZawdk/e5JnTlKi18RbY40EtT2hgS6iUf79N6SXZC6EOfQbfUaefEGguYi2ssSI/jH4t8SzXVx+AnTb5ldHh7fvb8WhY4Ik1OLU/Sptgt/qLTpYHJWLN6rThKaCl1KakraOppPs5DjW9BssnzXd7eDLroJ5hyO+Yxf9ER4s7IAnBcvaineXVz0HvEXyScEf4CRQJjw0IF/jpK6ZRy0UFnMMUi51oFvrwHgylWvCozQlX9m54hPZFqEvqE6uuF17T6+l5YfZXjhvcYtb5qZ+wloePY01kvimMkbX93cthXGdDDT9XDf4/Cfy3m07N0UQdN0ndgUsKjPkfvbqeOkBqZkl9NSanQ+9Bcq5iG6ZzmgblW/1S5IAkPU8ZhvhLDxOcAqe/6EEYd3solYSgviVS1ok8cPNhhN92TyLbsLA1SICfPHj6LvWhlnlY+ed+2WHCcawOih/PQwlSZ53t2n4V5fvvlKOb5rIudYxBUhi923sF7xGKnLuZzWNyvK2T5R9dwfrMAC3JpFGCCOziM2KAsnKA8hCwz55KGnTll6XJiRB//IIhiJPOC548m2WUdEFReG+puqXu07vZOHNcbyy4rse90pl12VykgLyD9P57QCxuwKp+Q7AmLZM+rWiRCj2Q+RTL705HEqJFwi7JJDjMYKIx5UKaUTHJFKOK79Ij/rkd8M0V8AUcczbIW09cw8wCzrE79c9hymDtAeCbmWzkTxG9VxLIGZoqDEw/n9WL0xD/UEy+nxH/9CScuFh4LBlutsVLJi7Q3aDtFs3BAF2xYWcclJV1GnaZ8osdzW0WlyOzg8UvkUDRb0CtEyzvtYDrFa/TTQVboV4BKG6cPxJCorTD9a0tgGKQGvDm9XFozhgkpIKQQYSAIl4LQG4TeREgHYSAIfUDoQ4Q=
*/