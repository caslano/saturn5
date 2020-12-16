// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP

#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg.hpp
IM0Dy6KfhHnK9pEF8f8qWYT6uUHNQ4lM1sQmYVLpO6a9F5YFMigqDndweZN5NyWIvDvMqOuEUdVxkqV/P0dargzCc3Uawe+aNXz0vKjv/L5JO3L+kYHIZ3+9b/hx4wtGuuHTPOHT3PCed2yVhIyY7n7jdRKuF88qVT1hPRNRWt8ZcK2GjQqHkCm65/10s4RLLBvOKbIn3IcSLmDVZxyJx96ERjVWx5LFFO6lcui+qa/tx6nTOlF1atpRCn5u3aleCNXzYuau9RkLU8etC32+Uncjc7OvmIYbe7+u//7Siu8H9t+PGmvfacX3i/rv1634/tWK7qOOta/4hAmO+yUD785/peG5qd07Xvj+l7ua1Yq9f9t/H3LF92nP6uK4Pzlx8pf3XTvkxObfTDjt57kD6xy6fdf++6srvm+5ovuo/fdLx95v7L/vOvb+55/0GZ6fvNu9aMv+K979Qn8X8vd8/du5/6ZpmCv5e7r+fa2FXf9e4NzP+vfd/L1Q4zrPhJ+o+0r+lv254TVbMAODX8TZPNeQncNrYV3dP2vOItxPvPkab4HGW+iJV6rxGvnEm6TxJsOGcIobj7UrseNdqvEu03iXe+L11nhpPvGma7wrYW04wxNvmMZr7BNvtMYrhI3gGE+8eRqvmk+8PI03AlaFI6GpB41X2yfeMo13N0yF93jrYT/xVmi8lRrvAY3XL06/Iek36gH8Mcv5Wxd6XG3p2Xzwak3nCfgofAs+Bj+A6+EX8En4jaYfr/uUm8M1sLXuU24HX4AnwpfgGfBVeB58DWbp/ucS+DmcA7+A8+GX8Gbo7Ku/FW6Hq+BTuL8In4ab4Sb4IXwOfgy3wp/hR/AX+An8Db4Ba9MPbIEZ8B3YC34PB8If4IWwCvkMg2lwOmwBZ8HW8O+wHZwPu8GH4fFwMzwB/hP2gR/Dk+Bn8GS4B54Bf4ZnwupUWH/YEQ6AZ8Kz4AA4EE6Hg+DtcDBcCofA1fBcuB4OhTvhBfBzeCH8GWZBizodDg+HebADHAGPgePhyXASvABOhhPgFHg9vBjeDS+B6+BE+BycCrfBS+En8HL4byj7l531U/AoOB0eCx3/AfBKOA5eBafB62ApvAF+ChfAHWr/Ec6Hv6ndTgjZm0DHPgjeCLPhTXAkXASL4M3wUngbvAHeBRfCxfBmdb9V7bep/Xa1363hl6v7/er+sLqvUftata9X+zNqfw4uhy+o/SX4IHwDroZvw0fgLvg4TK7C/QObwg2wC9wIh8Gn4U1qX6r2R+E8+Drc5KQHn4MfwhfgL/Al+Ad8BdZOpL3D8+AnMAd+CvPgdngFfAvOg1vgM/Bd+CN8H1ahf/gA1obbYD34IWwCia9npOq8hs6dDLAjz0g9X/uhodrvXQgP0/7vcFgA26h7Z+0nu6q7OUtZ078MMyBqX3c7Tf8o2By2h8fDDjALdoSXwk6a3gDz7k2b0vSqwL7heR9NrztsBnvA4+DR8Dx4DJwIe8Ib4LGmP9b3WH3nHhDVH/fWdE+En8GT3Xj6zid1WCbeqRqvP3wev7M03jDzrsK9q/mZM4tVn4jD3VDOLIZNYa0A+41Vn0hXmKD6RBLhBbAmnKTh3guWb7+u797cmPtydU/uQe7HnTw68Kf35B7K/biHai9uRffhlmBW+uy9nY18IvffHpp9t4tGB/703ttDte/Wu+c2cTBxKFumd79t9F7bQ7jPtswe2//y/trw3tqNXHMpJo4NAC0w/TCFmLmYlZjNmL2YzDHcL5gSzCLMekzpmMr9tpW/yl/lr/JX+av8Vf4qf5W/yl/lr/IXvfdx7F+0/z+0jsj5s5OuKfrzugDqo8u8Nh8lWmQ431lJOrTkuAPFN34=
*/