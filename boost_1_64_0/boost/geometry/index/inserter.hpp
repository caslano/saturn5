// Boost.Geometry Index
//
// Insert iterator
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_INSERTER_HPP
#define BOOST_GEOMETRY_INDEX_INSERTER_HPP

#include <iterator>

/*!
\defgroup inserters Inserters (boost::geometry::index::)
*/

namespace boost { namespace geometry { namespace index {

template <class Container>
class insert_iterator
{
public:
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    typedef Container container_type;

    inline explicit insert_iterator(Container & c)
        : container(&c)
    {}
    
    insert_iterator & operator=(typename Container::value_type const& value)
    {
        container->insert(value);
        return *this;
    }

    insert_iterator & operator* ()
    {
        return *this;
    }

    insert_iterator & operator++ ()
    {
        return *this;
    }

    insert_iterator operator++(int)
    {
        return *this;
    }

private:
    Container * container;
};

/*!
\brief Insert iterator generator.

Returns insert iterator capable to insert values to the container
(spatial index) which has member function insert(value_type const&) defined.

\ingroup inserters

\param c    The reference to the container (spatial index) to which values will be inserted.

\return     The insert iterator inserting values to the container.
*/
template <typename Container>
insert_iterator<Container> inserter(Container & c)
{
    return insert_iterator<Container>(c);
}

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_INSERTER_HPP

/* inserter.hpp
a/gd/Mb2X8OZZu4RYsyv6Zchd0vqe27qXS3YCtaHbeBU2AHOhB213nbS8e2lcDHsCm+GPeArsCc8BHvBj2BveBReBv8F+0KPRb7DyrA/TIYDYRocBGvCMfBOOBE+AXPgC3AafAlOh1/AmdBOz1mwEpwN4+EcmAbzYS04FnaHc2E/eDUcAK+B5n0nBdWCxIP0CXwv2TrGN29tB5vC9rAl7ATHwkvheNgZ5sNeUN7nmbtc5A4ZkS/m9zhN95U8PwneBmvA22FtuAo2hnfDS+Fq2BveA/vBNXAIvBcOh4fhRHg/nAwfgPnwQTgfroXXqb2l8GH4N7gO3gvXw7VqvgluhsVwK7TbtadgW7gN9oGH4VD4DBwDd8A8uBMuh8/Cv8Hn4G1wF9wOd8MX4UvwFbgHfgBfhp/C/fA8PADZDCvPSYavwUbwIMyCh2BP+DrsLfa0PqJcvwbOH+R7Sc3HrRG+fNwBB8EX4BK4Bz4I98J1cB98DL4Mn4b/gNvhAbgfvgrfha/B9+Eh+DF8HR6DL8KTcDc8BZ+Fbjt9YAS05RqwBDaFb8LW8C3YFr6t7gvdzp0Vco8G8fHNgRlTy9+n4b5y8jVsAY/C1vBz2Fb1e8DjMBt+A4fDH+Bf4U/wNpVXqbwFnoIvwtPwZfgz/BaehX/AX2C0RVLDyvAcTIe/w8bwD9gcuohHF2jBCdADC2AY3AUrwVdhZbiQOCXAVbAKfAimwWJYFf4dpsO9MBG+A5Pg5zAFfg3D4VkYAV0e+lkYBmvAOFgbdoYNYTa8GK6BreB9Kj+o8nbYHu6DXeDb6u5j2Aceg33htyqfhpdBj9ennwr7wbqwP2wAB8KmcBBsAbvCLrAb7Ak7wBGwI8yBl8Jc2BrOg23gUtgW/hU2hvfCJvAl2AzuhXXgO7AuPALrwU/gj+TLj/AETLL3i6JfDQ6FdeAw2AKOgLJO4nbObccMd9MsaLcPWv464E9t2B32g73gGNgbToJ9YQHsB2+F2VrOBsN74RAtb8PgTjgcvgZHwvfhKHgSToLn4XTYgzDkw+HwajgezodTVc5TOV/la1ReABfAInjdv9k7E/gqijOAv9yBBMhFCBAgIggCQjjkEuWWcEkEhChoEnKQSEhiDg6LEhAVLEcURBQkKBJREaOCUkRFpYoWASsFvNOWKloVqoipZ/8779t572X3kQTpnffj459vdmb2m2t3dnZ2Bv4a3gxL4Xy4CpbA9XAB3Ahnw0fgHPgcnAt3w9vgm/B2+Hu4GB6CS+AHcBn8Ad4F/cmrlTAYroKN4d0wDq6G7eE6GA/Xw96wDCbAB+BY+BC8Cm6C18BymAIfhvlwMyyGFfBPcAc8BXdCox3sgk3h87AFfBG2gYdhO/g+vBQ+BYfDp+FouA1eC7fDaXA5zIIr4I2wFM6HufBWmAfvgfnwXngNvB9OgQ/BqfApeC3cBl+Bb8Lfwg/ga/DPcC88BV+Hp+EB6PDnegkD4VuwKzwK+8J34HD4LhwL34Nq/Fqva03Zy/33PDVWKvMRgrivwAx4P8yBD8CZ8DGYB3fAfPginAV/C2+Eb8CbYCW8Gf4ZzocnYIlc92+BxskXyXX/dtgBLoZd4R1wCvw1zIVL4Qq4DK6CK+BGeCd8DN4FH4d3w51wNdwLH4Q/wk2wlVE/YBs4HY6Aj8LJcAtMho/DVLhV2jl1SdYypizkeWuk0S6lnS/1Jz64DLaHK2BnuAr2hXfDa+BqmAzvg2WwDFbAB2Cg8XwMQ6ChNxY9Bj4Kz4NPwC5wO7wEGuGHw11wPPwdnA73wQL4JrwXHoDr4TOwHD4LH4NPwt/Ap+EL8DH4CtwCD8DH4SH4IHwHboQ/wE3Qx+iXw0D4exg=
*/