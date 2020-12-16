// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_direct
{
    result_direct()
        : lon2(0)
        , lat2(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T lon2;
    T lat2;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP

/* result_direct.hpp
+369e9c1oy6GzG/GdHe+dY/zil8ov3Dmfh/uFP1h7lnQGyI+zRuqeGfuN+NWT4xYvs9WP4D+2xG/sqZiZl3PwmVTp0zb7rxjzx0J921DGP7GlV+5rjnxvPPmf/JUx45nvPs2jHNo5wEXnvb8ew/W1Oz7YPtA5MgLYFPqkWjPdpX6d3t19myRt7BnjT0/0mET9Yeo//6hZbcF6uru3bZgi8m7behenz1DZ/h5L6w9+cC8ll+nj1779sdHv/UwzIGxXGpqzve//8zP6/pe2mOE78wRD8G4WsbwDV4IrRHdedb+b6x+UGKTzdvgox864uef3O27Lv+z128/d/TvS084BD7ycTPiuedGRm2y93eTK36oKBl2Q9crrE4z/MuG1hH9Y4464o51px61+vLfPob2tQ7Dbzx6t+PHHXFT91vDf73s2zEb1UE/VMDw774bcupFWx51wNRHlqTKt3obJlhulH9mj2cf/v3bo79ZfPjI4dcesSPU1eMRr7h7zyN+2Xju7QcPzLz6oFuvhA3yryFePjTseXKHT/vGbnryoXsuvuRbqLeFDN+99OR77tmtYvZTZ+96w/LNd5wI5TuM4ddu1/zNL1MmPnviR289GMoJPQHzVMzn3UZuXnnd8BOu/mnxjYc8eegKH6yZxHrVeuNF3jd/v9zzxSUnnTLk0k3hQy5s76uYNOxezPvvV+D3CjjmavQOid5N1efw72s3k/ze0LFsxO8Xl9TBeT84T4TzYXD2wHl/OAfgfACc2Xh3EJyXEc/0s99fkv7SHK6ftfUTSD8U0RLWTa8D5+FwHgbn9eBcA+eR/Lnqkno29sC5ibVzOLP+cT04d/J76SW9fM61JM3nYEuWwHkDOB/B71OWnMKf0y5ZCucqOLM9n1vCeWgOT0fkQ9vx1K9kyIdTQI6dT4Uz69+WMj1wvgbOTO50OA+B85VwXgTnq+G8J+NJP/PhS9I/kvTnw3kc6b8X8mtNON8HZzYW3Q/nCrwW8endBPpoj/8UxX8azmxseBbOw/Faxm87IXv6V1P8ayj9ayn9a5T4SwaJfwPFv5Hi30zxb1TiXzVI/Mso/uUU/wqKf7kSf/kg/j9M8R/5g71rgc+yKuPn/e7fvm9jG+NjzDHH1TG5jIGCgtzlDhuIgEpuY/tgk7GNXWQg2rijIkxFoyRdSgZCSIpGSalFikVFRUVJRYZFRYVmiUrZ/zzvc973/S7v2ISsfvH9eHh2zvM85zznnOfcLy+n/zCn/9sW+eSH7OW/xvJfZ/mXWP7rph1j3dPejgexHQ9mO76K7biQ7fhqtuMhbMdD2Y6vYTu+lu14GNvxcLbj69iOR7Adj2Q7nsZ2XMB2XKjsTK1r0nqp7u4p0yk98LtB6Pk7G3iAbvdNiEPcDDwF+BPANwEXAy8ELgWuAS5juw4D3wW8AHgt8ELWrxz4QeAK1u824M8BLwKW/WMl8PPAi4G/QfuncEOnTwIfBG7Cv1eAVwGfBV4DnAH97wUeBLwReCTwfVJP4E3Ac4A3A5cCNwNXA98PfAfwA8DrgR+UegHPAX4I+CHgFuD1wLuB7wb+EvuznfA6KLUpMXayRZOqgh9YjtM/xXa61WJno1qRv4/lN7F8M8vfb5GvaUX+cZZ/guU/z/JPWuRbWpF/hOW3sfyjLP8Yy+eoNTJq83X57rLOsP38GfnUFfgvwP1kmwZ8DfBbwGP1PqWpAPivwLOB/wYs29a/sz2dBa7U1yaaGoHfZzv6APh+4HNs5/9kO/oQeCewBv32ADuAvwrsBH4V2AX8I2A3sOzTvMDHgX3AfwROAIYOIgCMMEQQOAU4EbgrcBJwT+Bk4N6yTgPnA3cEHgEcAp4P3AW4Arg=
*/