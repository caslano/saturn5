// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_VOID_050329_HPP
#define BOOST_PARAMETER_VOID_050329_HPP

namespace boost { namespace parameter { 

    // A placemarker for "no argument passed."
    // MAINTAINER NOTE: Do not make this into a metafunction
    struct void_
    {
    };
}} // namespace boost::parameter

namespace boost { namespace parameter { namespace aux {

    inline ::boost::parameter::void_& void_reference()
    {
        static ::boost::parameter::void_ instance;
        return instance;
    }
}}} // namespace boost::parameter::aux

#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))

namespace boost { namespace parameter { namespace aux {

    typedef void* voidstar;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* void.hpp
fDiUg73xkg8dRod9jshLVv0dbLmt+2fkxbUTAw52FYdTkQeMvu2skLyQh6ulIf2b2tNG6Xd2zRvc0um9VNnDEbe8cehGqbHKotplmLvkA7qtm/cvbZ1Op6XqmrDY0gk/McNPR18SPclay9BG1jJsosw2hkknGTyxp5X7GmZbfIuVnrKo32O2qPtdXNPKbrfeo8uxS1q56NIHl0m6Jth0E7Sufr5XzxFzWlEenelcrK5VvBzvxVLvMEswzSRc9jJaPjngSan04yXILaT9AZe0l07cnu66Tv5G6RewutbrPofIlkZJyi9mKdja699JGW/j3t9gP3zfHZ+jztmmN4jWY5QDlBnXWj/43L03zlJ28C1NyoNpx/e58yIJ6Szxsj/jZsgmVsPFkWFIOomWl6PTmAaFJCaBK+pXh+wjoM+AVPp93NIXt+xlUKevS1q66S6tqK9zaQdcdasqStzLNrrO9qW6nuNolW6yTTdZ6UbWvrjtg2D/Pi7p7Sj7Kj6Osk+4RS9Zt0UqfGq96WoVHubZY8H+DH7wbEfeyfzxJp13Ot/sa6t0nm1Sen3d55S2Is+aWpFnTa3Is6ZW5FlThHnmWAv2L8mvhx35NU2++6XNlLVmss9bf7gcnQOh+VVQUlpW1FBJu1ZUWbk0sOWBzkP7vINXlN0e3mX8ezeyB3kaSfSGaesknZz1WNoenvkD/U7HcG1dmHKRIva7jecuIweJjNJ8FTfcysAB1/LiXgYOuJcXHd55yr+ZjIL6dFv5njKLcS0nB9zLlK4TDym7mcpuqs1uqqvd0lVmnUiz6aZZurZzdVdUVAWiqb+n9VJ+Pe8p4xvok2pNDeaYvKXMEzGx9xGVrA6o1PF+PUe/Q+hnsXeVWbzX7L/PJcLzW9F/O+uEs13zu9STBJd6kuxST1Id9QQz0kzMJB278QR7K4bX0pD5zPQqqDdOAQ56Jps6R77t+kh7GA9L8SBvgq5HK0trK8pWB03bcbybSv1Zqey85p3DuPSNiEudEXe9zjFn/Y5/nrof66vm35+o+RhTvYz3kIZil5COZu6Orkd2N/V3Ses9NxXepe7v9PYmBOWI7fuiLqvPBdx2nTuzb6IqQ6oW9Da/4xn6JO1yUvMBpIYxwiuYUfR3r882V0WSTp5jTffWKbvd8TsKCcTtGmV2o4rDS8ouE4KLVuhv/p1UGKZ4p3smaDupymyi13g3Sp9JHs42v5EluM4rQYe9FuVdN64h5F03RXTyZ5vfl9be4I9JDH3PEr016K3upNZ1dnD6dzHXpFPIN6ZcuEDq0kJkBjION86Di5DFyBSu8+EkZBYyGZkp9hdxLzeisZmYxOm5gfHJqpKw73n2OYaqv3lSpSn7hCcGz8XbKfVkkHgyUNY2H1F+NIbZaMsa6z4/2dPiWdb2/m3GOaHPI/fhX/ok8e80G3t5ZM3mLsKcgTsX4He8h0PNk5Nt4ZHvmRGssR5h9rlzQ+cjfkQmFwbCtEqt1JF9Jqy1VEVu7YDY8dr0lrr2kaKnw/1aQuTfSALrq4oc662WBsVpl0ucLk2jrEmc9ErtCOJU4wjrhRHs9+QMqz1sG+eFnrH+Mnca7WFjFihJrsL2m8SwYRM7XtELn96NXyC9cdee3nK9VJ9XnhrV+vOpW3v+eGvPoXY/9zzc+enhzyXfV2mY77wuf/ehxekNR+/a1BSXsuHm8OdZu59jHv48bvdzwMOft+5+znj4c8zdz5EPd0536889dz9vPdy53uHPhX840TB/4lf573y/svvRz27cMvXVPg8eZ48FZb7j9fN73VZ4X7ur4/d7Uz689+Hw5867n7fe+nPPW3vufLhz2z/06DNJ1ff0Rn5j7Dlq+/0=
*/