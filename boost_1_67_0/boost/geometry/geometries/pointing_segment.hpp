// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP

#include <cstddef>

#include <boost/concept/assert.hpp>
#include <boost/core/addressof.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

namespace boost { namespace geometry
{

namespace model
{

// const or non-const segment type that is meant to be
// * default constructible
// * copy constructible
// * assignable
// referring_segment does not fit these requirements, hence the
// pointing_segment class
//
// this class is used by the segment_iterator as its value type
template <typename ConstOrNonConstPoint>
class pointing_segment
{
    BOOST_CONCEPT_ASSERT( (
        typename boost::mpl::if_
            <
                boost::is_const<ConstOrNonConstPoint>,
                concepts::Point<ConstOrNonConstPoint>,
                concepts::ConstPoint<ConstOrNonConstPoint>
            >
    ) );

    typedef ConstOrNonConstPoint point_type;

public:
    point_type* first;
    point_type* second;

    inline pointing_segment()
        : first(NULL)
        , second(NULL)
    {}

    inline pointing_segment(point_type const& p1, point_type const& p2)
        : first(boost::addressof(p1))
        , second(boost::addressof(p2))
    {}
};


} // namespace model


// Traits specializations for segment above
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Point>
struct tag<model::pointing_segment<Point> >
{
    typedef segment_tag type;
};

template <typename Point>
struct point_type<model::pointing_segment<Point> >
{
    typedef Point type;
};

template <typename Point, std::size_t Dimension>
struct indexed_access<model::pointing_segment<Point>, 0, Dimension>
{
    typedef model::pointing_segment<Point> segment_type;
    typedef typename geometry::coordinate_type
        <
            segment_type
        >::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        BOOST_GEOMETRY_ASSERT( s.first != NULL );
        return geometry::get<Dimension>(*s.first);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        BOOST_GEOMETRY_ASSERT( s.first != NULL );
        geometry::set<Dimension>(*s.first, value);
    }
};


template <typename Point, std::size_t Dimension>
struct indexed_access<model::pointing_segment<Point>, 1, Dimension>
{
    typedef model::pointing_segment<Point> segment_type;
    typedef typename geometry::coordinate_type
        <
            segment_type
        >::type coordinate_type;

    static inline coordinate_type get(segment_type const& s)
    {
        BOOST_GEOMETRY_ASSERT( s.second != NULL );
        return geometry::get<Dimension>(*s.second);
    }

    static inline void set(segment_type& s, coordinate_type const& value)
    {
        BOOST_GEOMETRY_ASSERT( s.second != NULL );
        geometry::set<Dimension>(*s.second, value);
    }
};



} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINTING_SEGMENT_HPP

/* pointing_segment.hpp
iF1tiScwMDYhCTnuqbmwet7PsN/ONBIHCKoc7uzsCCUZWWfaMyo/IpZwl54h9yTTjfNbWVoi/MuGW1tb1y+fd7Z/nizZP9RwCP0m+NHhpghGjAyOmpOfCR8aId6/H/lC59XW2fk5CRqjWv74tnW0aWKMgVcrh5wT6bNxdLBj2bzd+Xpz+6kngBhsDfBoBoiK6lZpa2lEo+RbuAFVsrY3ovy2zsaCmI2hemjherANrSSITc3Sc2iM19YA/r36m6BMx/oImnOkGWGZ0NCycnKRmYioIw9wZWV9TBkgEi5wo7orcR+YcSR+5NwxKFWU1526oCUFcyO+B8sVYK4Bpe6IdKeCuXC0qHQQ0FT2HS1gEIAE5iqzHgEC0wDxvjF/w6DFQLDOe/lpaDUesL5kMXWXhNJZ3zLzsHL85F1jJXUXzIrdnjp/NkobRx+aQwKqCNt4mQCGCjV/O+o+Bz0dF8WIGuhgCZlnDAIJFxlnA56aV2SSnjd35t1ZX7WyvUnwOwsm0YD0EdJh7J8uGiIB5mu+ETb10OU0yq7SbWHG3LO+42uBpeTwKD9bdD2kCSRCFncns8FWfRPbowla/nVAcwVWO6HlwrX+hwxHmvONYCIYQfwTQA36J+C053vD14HImoKpD3yEeoKwAOzfWuASKMQgqMQgiuASPv9s6P/uoxI7anRkikH9p3hFfdCk5E5PypGiRlRBGfwkgyyTpqoes8w8OipqD7SHTeZ13UbMRyOpdXNzM3SylwDUJQ4I40e84x38nWc22LhuGbn/ct4A9jk6OnoMlOR3uWYPI7WAN5FOzbDv2r42McBemzV9gOHyxrWE63n8/Px8NsDO4j5ecJ8uP5CaX4ge3s/+p1uhenABtABQAAGg/HVxUsAwKPwOwAJg9kEWBNcn5S4hdv5NGd1I0vMKC74DKABQvJZnC6dBULNiqYCXtKJ9Pnxag3A8b01tSNb9rxr2/3Mu3P6/uHDp6f/hgfZa3Jzne5pQ118llB7BXII2qAUBjuP5Q/pGTG6N/I0dDBPogfwCRRUAhAcGBsQMk2mxYPJi1rCG30qQRRjBxWzyzc9Xl01EuKuLihr/UVFdXK6+HVA7U11MTkzEobw630i/JQZ4vK9vfylC796bvmAYfuyqdb8teh/iWXfculd3Pq0t670NFH81GAlef05Pf+1WNm+9GZsYdz+WZ7s9WgAWWHL0Xg+Ku56e1q2/a+LRoZsiIOJEUIGBiIKAhQYHAKgdgMpnLQl5B0L4BOCgJiSMI5QMFC2zJaPJrgtYaAoGU/FwWAY5GWkCGf1nGCVdbST0Z8GOmUAFdab3v2s9hYnxIcipNUOL6wOHniMLdgOtlcTzU6pCFFyWPAPy+TQ4umwXjLXSva1InvHE9WJYiy+/M2w3nh524AUZiLAAYVq37rG3wxWQ0hPk8Tn7uXTjHWKB6J+fthHNm8NQ9KC4vztCDDsk79AIfIh3rrD3L7E/ddNXy6yDDDZAXdjtuTuR7pryti3ngoZcLCNqoZB5JI2NnU9d1HbaZdZibCYxdOIcgZKrInC7DEMvuumx7FvyosMT+3Ta54TaXFfPW5xmIg9MoBuAGkRqo8jceeTfy3/0CYJJYmwFx1TDcfvy3eMXhjc3E8NgdWB/3aZZ7yOsW1lznDYF7wYNuhiCAk/F7DxwdJb/wNbGVu3v7eWjEccxBiHrrv3lkAFleT7vWlX2GTg3dqoHS5sIRe9rFNyqyPDbjnFQ2j+R4YG4wxVxyW3K1YrTHbMtbVUDMMC3qLRbkpmdtmOGA9kAqrwQYMh37uHVViBU0kVgNrMlAVLcVqrckrkqeHbPgiwLPjys578jdPJR26jUzRPddVH3lC15fnz9AnWF3hU8FP6Jg+cIawBC9T3baC5S+OmoT7DJJ2WZ5G8YcZPx9guVpR7Omo2ItLXMDguQdmD3rwy63mYdyDhRIWN3thWIjMmxUPijdDV4WGhODATIer7RycrKTkMyTsG69Mtg/6oC/vJkJxBJM654TdEITgekwG9q4in/HSTJwx8p0L48wy91FcInmF3pBLhKTSxnV3/WHHh2Q13dSdHDTaRIY+V81dV7X0pdATJLOOxOoys+JwFpdK0KRL/54+8V9fihtMxPqCS16YXvZ/fIfF7IcGrgQnFSmtHsPWl3scLOsA7JSkseIPaWkxcMOLiS+80I1amtZ3KZhjNRZqmyrVOEkCvxEyij+Iz9y3d6piT7jT8uJUB0EbWP/HIntJcq8vdsPSS4TxwXc+AYyQnzonRyze+sWZnMlt5C7f/ooEvKSW1dtAV5trD5aaOHpAFk3LWhDPPY7QHnRo7kBGYv9Xabmmauk3IOEXGOyTnScMQeP4jdhBlH0bopn7umUUEn1bE5onXUz2c/63imKAHj9sc02f0iZmW8QxmObR8OF8YewkhOV27viNKJyxld9XvoNEmZfpsV1W3A0wE0vx9LL/bLCpXsFSk/JYmU/VfL6W1CHR/3KHtP7fZQZMubiWoZVY52dRzrprAppjdsJqlcYGZPUPMWqC/lwwoDBn6LIOpnmxE476OOq1tffvJ5CrwXzGdV8agdbnh0SuMeHCxIlBm2jYQY4aRQChnBKYEIMwhVUGsX3Zv00PMIoUqe5fTLMuXk2eUXMH+flPyhANwjxGklNZgyHWPS4463UiLCQp4fSzmCqgOqiEPjQNLMV8FGa6eCiyCPnAtPGiNWF33MQHioOPDhlsTyGtfq5jrmcgtvFz+ThlgdQakhlP+6A2b8I94r5IbxhjDEbV4vGkFrnnkrXUgqcWVj/7VBF5gpfxKbNSOdhMzhzv0lyGJ7yEs79iVoRJkEiXevcj9FANqXlpM3gN1Q8UKdQSPwxH6uml/HFwv7yJYZKzpf5sZcfnLgdTLfz8meLsZvwIaIt+B1nsWg1RaVTHCP3ogSFmAkZszfbSCWg5aDZYLhYcDEboCsuNUVLnINrxq3yMWr+upwpDb7b0gtqr3nNA7xQ4OH1Rbxix0GkXXq8gKufHcJuXfJ50+B5AIA9ecP0IQ4qIWwVCiFKZY8FEFv+Jks8BY1grLCXqltV5g3NkmD3J9Z082hCuch+SltfYUxfkArzKKaye9gMlkf928TxmM0rqqCiR9K5IVHBQrhf1dy6bLa+HVAvU/B1VVboeVrsDBRpeatjNn35vYxfJKsXX49voC/xtKYYVhzSI5bQho6FqWlBvByxAm+0BIAIvdXhrGbDUGbtvu1FXjxebNSJzR/O5U16UiB1i0IHW5eMqnIHzKBCxrie2JDjtG5tnZdv9viN/snAA8y8AiK8LQSPyYjZQFPi1GULFP+F0rnQVcYjbFhC+byzJ3Ptc9ezenSvftcT57b1kSR+xzOtpaMkoVztloSUUCD+9Yks4AiBZ3DfmZBpZ3/rws6SVDmO1Gi7Ixr4dkTv6kfXz3YYIXP7cH02Qb/vSxYw98esk+QJzQmmhvnzuToXg3oaD6RtkfYEkYMhxJnJPhaT/qj4JcJKJah8vY1x6EBs1P7Zn4wEpFVMzOiBIJsWSLtG9CSCH8XHFQEoGTGTav/5Qlixu5ebSbjNVghRej7OUQmLKyMS4eJhUpzDdjpR37rIqJMdH/edPZ2en+6fG7D49QFl5RrNDCHVO6JhQfPIAQV4Ym1SzNCJuHMeP9gCGA51Q6JlWUR+KvkgAUYqJDKIi+EJqdzzwFOq5/EGeC32+IHfmDf6XndxWd3WBl/VwQjtXKW1UbtE40pUOCoM57CXX3pgPb8O06bGD+9m74cXgm8jKl13T2PjjtyVklPW/m1z+syv2YigUrIe3T339gDBKB8rrK7nv0Fvh+nPY4YBb5Go72vcARK3gSHWH5sPJ347f5e+Xp37roncLLxuJ2v9tqzf4cYVtVNx6ra73Uatmjmv1sHehdLxyqYoM4hvUqTog0bHfuFgq8TtIAfgiYDzwGB2mtmLjCgiUvBUdQp5YeOkiytGJLnCZJ0eLrJon0DGggSdMWHOWkvdIF1VXIMSs1wUnRIDMJQo4AwBMbdWHwHXJR5EoQ2G991Y1d8GwQzZEMNKVhDBsNG6tyHiETXWkYcH5C5TmPyAxoyXBEo5paF/v1NVZBIZqesuuuZULaR62fmrxYVwXUS0LuYDOGxA2fbm2xO2lzbl5SAaAoYV80SqqEvrEpQ3KEXYjXPdgY+ETGBCATpkuhnkgfW9SJCqiY40+NbwtLK1EDEHBh8iC0rDHn8R8EdKmoHBiZkMtNrdguRmXzBiLgVZgwXqHbBdt/GZcwDQRYZUtSemcZWQhhAhLIyIc4GdeSCQfl5LDGzhUmV+jGOboepIx8qgOn15x6ET5cIzcvfGcfqBtgT0oD0OI64IIZFTBvL+tWODbqcKau4lp93BsnjhVg60Iwc5Xa9VbSMmfJZfnqm+OkQCyjLzCBSEDkIo8YqU3QdxKZgPjqEKssXbkAAIE9fnzMa2tKJDxWdaQwMQE2SM/soAegZISZJ6JGaRNNa/wMrKk/4NO8InkIjMAnaRighnNSCLwrTEEQOJCm4HUeDxvGRqZeNonsUc3I19ZjnECWl4juWslqf74KZZJDji2B2IyRdIIlk/h+wuDKepKwB7mm7mdZhnZKErpYRn99PEA2J6daYTSfcs4WqgAAGQypqLtPeNYg/rRzCdf4jbC11p1zoLEEX6MC0QGNLCbNGuCMPKu7AJHL0uSnoRATyRwtVYWL/O4ckhsis5Eb4EP0R7JVD5nlTHkQckdQprlpLZ+ukjKPYOaM/nVQ+xktM6005ZUXykEmNWo8gdHKeRlCU9gmW6oemiriP26HzP85mqsaYp8OFQ0Xm/5QafzbNAQSdRlMYGoPWg7GnI3alJKjkTofBSfGU+w1M++Q3mhCXyM1kjsdq7q0cEplPJhFnLwjaci/QAUncoLVGhfY5iEWguJukJJzdvw7H5YjmplwM+/l7WYOAuRV27aogrWwJpeytMyc9P8Zb+GAkFcwIrx/AkSTi19cTkLmUfwklwMU1IfAGCvHzBtaBSteDzeYvYNUp8QaKI6zPXKDPgUD5BE+uxSyYwF+UtepMSo2QvbEIVM43/FHfRx1jY6dHZh5qIj/AZQmCyDEmRy/UEUgyqQB33g/ZtFquCAgiQWyfpYUZHLl0WqfL8cJ3DyeVzq0lyny+2rTAmmF64MCtPuQaMIhYsWqeVMzeZEI0gG+RrWu3sj0Rv9nqdJepu/x+0fP+zMf7ciZCez7lR33b1Hom2tn28mVshD5ZCvxextJ7f4D7flmSu2X28bif5PzG7Vn2djrf736qsLqr1eK0ef+CMolzJrK8xbu9igbxiAfc/IuWI/hU518uc3Z/HDJ+q0ABnq+3vVMPirV+kp0aAXaaux4ruzvtj6f0PL6cu29KjASbQau+T8QF3tqjDji/dqK/D5qWLTI4XtxeC5Otuj+f1rdPADtDkXidBSsNELH3iorpFstOivOJ82adUQ2D0MiFQbTF8TEpSjbDIYdvEZNddzzFJ527zMVQPsCHGYw45BIQhOX/D+opkzQ6eQCAQ0utvQNwLe267zti27YzY9u2bdu2bcwkM7adzNi2rZlkxrbvN7+111lr73NunX1v7apOqp+3H71vd1f3GPWr/2hBAIrk9hxIXcBW0PPwoWlBsHh0UpK/gS7HbXO1bz1t/H3YcoDWQJS0caw+FobbkUZQilu2ifnxNcyx3cUUIAFLh1MTA9fGkrCui4XDxKzu0sNEDSHOotkpxYb6AU3qkQwn2iscoI+HE8TDpveguT67134TW4qAfgt4oylwIqqW6K0kJBpA83b1tPQ9m+0OIU8duFszeUk/PRyNUx8IkwC+sZIwV+JEDruxKv+hixbPLht0W/kLtSRb0CN0s0Vg3+jfkXHMBwP2uKeamHFOxB/qoxP1D0Pdal06nUJ6cfe9NGgaeKS1CenODIMIiAprvo+eScrIM9NUDvFihx/EE92Jph2SqtoFy97Bd5bQbCich86wVTybfdfHR809BNqHoKD8h6iPnnoZy2+dz7mPpCnoqYt9R4VUz/nKGhtuTZ/LOY2JeH+IcZE/xDhV3XAqijA4egbfiL5RJ/UTAheBBhJcuHZMAXCv/ufmltOXh9ahCDhEjOfGfGcpyQnBdL+k3U5GRbxFqrBpcTlBOzKGfEr1grFvnkJuYxY1fwsnf42/d9Td6X0gYBIq87bE486cA8FYDI+U9YrxfTGpqrb5EQsgw1H9RzZ6uVWKjlPUbVqFzH6Ur2slq9JpXIBJ4FB0+xGnw+l99/t4Va8Tgmp2qu2PkVxTVb2/aXEga0JIxQVvDrxFZ5Cnp+QfWh6nGq8X48NLjCPEgg2umWorf7Sjlz1mh2mrx21xu6WwJk95Bwj2TY/OKdwLcH9xpk6cmoljC2GBhn8D5X3rLT8SmM1NQPfcGn1dP9v9oOV0JYW6aNxuGv8duOhxbfkyLe1RfGh3qcMZfrbikE1U6qLx2+mB/JAraQj/wjNbD+eYdhQFx4Wu/X5V1wzHaH2Rxv4HfBIyAnS8DlTDy/fsaMFOGdq5zXmfXFVNC6ee0u/AFVPjYDcSwhX7LRwt6Ln4FJC1I7j7B05pSfNtPpSSIwbNqPCNkzZJrsFNMn9Q8Yw/qDiNUThIo64m35Lzj+Tp9otNvJbcUIc9Uhug6W9oQ76sDjp6Mlon/0TFARxyripYzlYmcaLejqbwys4z8uxus7ZcLblxljfsFfj6b94zE5561EMI2PbEW3Smwn7HIfX216FgHE/YHfREeGPc8R/Vf31ckOywpPaukVt5crbZUFmM252stVlqfCGtUHUfoDDY4TJ4wQqQckYOV5wrY7brCJCkOZG9pytV1qjYSGGrZgSuBpl3vNPEnfWrN1kejyyCpoDm0jy0QJWtwshZVMI7D4itqVinSu9SC+emoqKLTx/iPOaR9VUZyc/MSA1btaq9SzCZseueLiUXnhkR0ci2Vj1yHNpfMjyook6/72PxbivoaYHldmZR1UuqucUZFISxQZqNHog8IVYqbpVb0fPUGDqPhRDeIc2pJ1pGrigsxatItOaL9/aMDFbGL3r4KVJdgmGZMS9zrqr+yWOL0QtMJ33jojudGmwlRXI6rC0anr5r4/akyS2NKDe/5MWZRBOpgpd82zz4CzQmzeikaZRAjndXbxUxfpB4mneGl7XI6rIyEuHyjQ9/a2mdHK0y+BtGPRsSaA3jlXGqcrIBMchKY1Ywk00DER1O1wi2jWO1Ko/oB3l0EQY2x9A6LRXlBpv836C4z63CSIBDXDErt3qkShUv3kwpXibe8cFWUmP9Jmd3hKzo1iiKTXfmXip70CoIMS7qdRuGgKQ2okYV0ubkXro8AvxLlgbEb5UfCWmBOu0xyogNzN/hPL/EQ2fnzgi1JIcDggUmi2/Xf22sGZPlTnNiTYWosCjwofySHso3EpZBUCkrJv05DM8RD2ukiLNSxccyGeYg4QwvpfMvSjyLCnjiSq7o1VQoBUnOUKvrARFSkVpn03xRz6aPWjtLxBrilMvbJndpJWlwkkjd1F3zWwaITXsPQan6Vefd9NPlZtvda3Tt52/3UlMhmnWSShtrpRhe+bJy8tYKZHNoaJiKfY1BsgveBemOx5e9xTxv/o8Zfq/DVPVueYDHUbZ798rTx5nFc/OaTffX2ozfI8IXAeqI3G9aw6iB/973eP89Thzxf+lGx1SfuKbtPOl+bS+5XvoOpbu5I89zsAWnmSIkwDYNkUKSykMiBYZgEeObJjAICDFhEZKSgscgQooCA6GQggcQm2DNJTqACgqRS0kEcV8WZbEVGZde2OUqp3/UPplef3RYrVQTDSdyHL66/PXWtf52/qW9085/tgPxU5P9zGyrKsu10W55qv3/bPjlRm9A+F8d+fvZfyxr546b3ZkL+mH3NgLloDvkHmx7sNb6FT55XnLrStZ4/brfu6y9eBL6tJb4Or6gyH2fn/k8jscH6W3y7TudYvd/RuB924zvuQ6m/ziF4L/t509dBFYiA4kIUusDKJUBBAo9L3u7tZN+d8Ie1UiygwqBr9piJVx43T2s6PnsN698Yu94HtEF+LuKSaz7fxrnPh/4t7tebQtvhGgnYB9DOsFIqkNfM3rRqNCt4fZsANP1F1u91+CANeH1uq3l2QL1huu/B7Jf8XmcZvVch/q/pdNBQt3Gy7Vevo+4lRYq1GErIuYrC5oRqkYQX+n84DGv3KIIuoXGaDt3qEMzGtGRrwIX+I1lw2I7bNEf0LcaEUiu6Gbs+rZNAshd7Z6pSSDguIxdgsaSV5w5pqwrUCMa33Q2yA/q3V0WGeHrZN35jJNhv4PNQ8yGDsPCM2kDCBaGgssMx36HwyHMW1NLwmQIRNBDTOpVHtlCR2bK0M4zma4HpWkIUjswcEOLgVvlQQvj9lvjBSXf5ic2jSRWjTZgBkyOqXUIMnwTshNAceqQCTFhG5ENhpzCLBnIKCnixggteoSPO8ohlbYqycr0TjKbdmLSrlD7rbY7ZcZ+n0jetC/QScqQDYmrA5vFSrHKuAJKRYhDukb4HcC2FCArtmXKnM+4oSwTlmfr5vS7nVsIGEL87sYqU0pC+UQyM57Jm6w5u2RzvVcFW4JaOZMZDhpzDjIWhcCWpc24ZXPOCx2FZw4T2SaMwC4ULUEK7mtn0kKJvMhMhsIsVExoNRvTsb+wjb3D0Gh9yrnn7SIcIbfb+U2OMfBE0wl5RoXZTsE5QMIKoMB2uZcsy7a1GDe+ylM6xtfldKqSlQq9S+SAyInlWKrkkDRYFMBxI0KYiITiYBGnfKYg8f44EI7gLtzfZC0zsuVxdfw892mVGfU4zJZdYrLaAp28eSJCZd88B7r0DWCrGN0/D+q5zC4/5cj4pFLMZG49DKU0Ikku0tJa8s1p0HGSuWCsaM9sUiy0biER4eglr2NGJIj5t1Q5Ph7+dPhI5tMyippCGUBtvslqHw6vtKp+or7NEMetVSIMVCbJObco/G7P3FtgdXJURSEsgMQW9htT1o0zEZu4QXL0VBjoYGahgxs2L4HrzN1wgcrPSR1B4hZSVZC7vpub3702wczHcVt57balS6xkcvPMVGwkUqRrRWukgvT89JkcJCWNSyYFF/uEKeekqYOCGvvmiaiS66aSMdCHmuVQt7QGQhopFRe/TAPNIbXOepkF5ovNtFz6bJwzUUQ=
*/