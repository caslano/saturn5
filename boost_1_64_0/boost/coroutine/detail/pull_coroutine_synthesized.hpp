
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PULL_COROUTINE_SYNTHESIZED_H
#define BOOST_COROUTINES_DETAIL_PULL_COROUTINE_SYNTHESIZED_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/pull_coroutine_impl.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class pull_coroutine_synthesized : public pull_coroutine_impl< R >
{
private:
    typedef pull_coroutine_impl< R >                                    impl_t;

public:
    pull_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind,
                                R * result) :
        impl_t( caller, callee, unwind, result)
    {}

    void destroy() {}
};

template< typename R >
class pull_coroutine_synthesized< R & > : public pull_coroutine_impl< R & >
{
private:
    typedef pull_coroutine_impl< R & >                                    impl_t;

public:
    pull_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind,
                                R * result) :
        impl_t( caller, callee, unwind, result)
    {}

    void destroy() {}
};

template<>
class pull_coroutine_synthesized< void > : public pull_coroutine_impl< void >
{
private:
    typedef pull_coroutine_impl< void >                                    impl_t;

public:
    pull_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    inline void destroy() {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PULL_COROUTINE_SYNTHESIZED_H

/* pull_coroutine_synthesized.hpp
9RyjrYHY8FL2ZceQ+y3jHAfy/CP2YccscBQ8qx+DHydWqHcQmV1Ee9iEQ7nE/7fA/wbkxEaCAYhZBDpRbxDxIXrl2onNwea9Sv6lYzf2PafBp++R2XsUdB1f+SpyRZy9jvFd0Yg8y27OkuFLOr+AXemEbGFT3i9hreBJ0Ub0vI5g7ugKdnIY+LUH6/OwBs6szTqC/WO+Yi/WDk7AD9Qi762uJS7Mw4ZTf0k+8sE5oPUl2F+wjm8O8usmP/oL/AEfZ8WSA2fdPp7CfhV5kgX0FdOVnA62d3Q/fBc2PekOYnb9uQ940Yd77h2EfrDOup8qPEu+G3/fkjVs/yUxP/vgqwZjf25m/mXs3SAbDe4Hv2SSp2GNlq/i/gHYbfI3XYmbPkEmtmCnJrdDPv5CDo/+H6EM0HkEluvcgtwvOHPAXDCqiu3bA/87o2tnFOwq+aA89h8f08Rr6OqNLMPpscgbeleVtqrjl7awdntYL+8Y/ATye/cqfGUq8RF2IBKd+p31Cv8JG/s2ec3h6EMqcZyDOOdZZKAGNgu9Ovgh/M5ArieyD9yMMd7FOSzyds+fIZdzA3n2qcTNaWAw8NfTb7NWjdgDYw5fUI5QatVFdyh1KB+A29QizrQ0JO5DjlNsMNZGzMi1ke3INYAz4iOJh4kFC4gXMqBvOItdGU5MvRhZXkd+YSJ6vR8Mh29f/SewLjK0CHxcPAl8+Tt894Az3kVeoN+2hfGhK7tZh1SNNaC9eykPUA4y5+6bkbcvkH/8mp1x9f4APAvGf/gsdgnfWtNOLOLCL5CfvfMGYpRvwfhRXPsGXYcvTzPe3Q0pS7CNQ8l/YGNaQHutNXmPLvjRwdiZF7ARD5EHfwm7BZ9+b0V8RdzzRR/0FJ386Hl9n5N8XRP8MWM6mUTcdx/xTy42EP4+Sp29jDezG2uzEP/6JHqA/bwVOUgiTjl5GXHIzaz/AfwcOcEtLmQA25k+jvaIJ9PBDXXIF01oQox0iHEtAH/jl/bQ5hc24jL6mPgFce57yKINjFsfmaD/Gujubs6Ppd9PXIz81ka/h7yCL97JmJ5h77AUG/80WDOT/eHl6Cq2Moq4rBsYtzn5zvDvyLuwtzWY3PtX5CCemwVuGoJtQ3fWkqMa3oF2GH8i+vY5dt85lvoKPL6buA7+HMQuDxzIeYk/cyaAvj9MJG7GrjdCj52dyGthD+8AF6Yifz+1pQ/WsCrngmzo9ozOyN5vjBm9OYIcZIODBsOfvsQzj8H3S3bh36dj44l7vkOOzhB7tqbd57AdVXpjozKQY/JkjdqQE3mafY8F7JNOBSc1RM4LsaWRnEXrRaxF/DGTc4kpi9CnRtDfx76gT08Ra0eTb/Ee4b8/IpYrQW93E4PNR2ex6zFh7B9XJV8ylPXAtu2LJU44ShwJr/dH8OzXSOG3W0c3kXf+CL5xfsoZTU6HOHjuDexl4zMPIG9zkIkyxv4Gtqgaev3mu+QYaWche1P9r6OQrxmEf3g3mvsKVPpARpeiD9nYP+abQbmOcsgGpsIu9S1mv6cW8cRNzI++rkLeWhEXdLwHPLoMuwZ2suPDVjekH+LKFjuZdw76URu5oJ0llF9/Id4ah0ywrgXsFeS9QSwNboizkXe7Eh8fixweAKsOZs2Z48P4iq4/Y7NY220fkH9HhlZ8Tr+ziUGQsW5g1AT9DC/Y95fe2FzOc7h82Dfa1PNnn/THd+NPX66CHqdjY5j/0LeRsSjsGnYkkjx28heMKwIMHQ7WSAAroMeLGetDlAlnya+wVrcxz/qvs5fOPsnScWDzQcT8tNVoDXOgjZs7YEvxdfp+wS2p2LyXkFH2xeyfYBvQq0uR+e3YkyhsT7uqrNE=
*/