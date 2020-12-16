// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP


#include <boost/range/adaptor/adjacent_filtered.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Filter, typename Geometry, bool DefaultPass>
#if BOOST_VERSION > 104500
struct tag<boost::adjacent_filtered_range<Filter, Geometry, DefaultPass> >
#else
struct tag<boost::range_detail::adjacent_filter_range<Filter, Geometry, DefaultPass> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP


/* adjacent_filtered.hpp
y8wydUX7NI/zbu9gnJE4lbPKT+DcGD9lLJO+lLVPlFV+bsgZHLd1BkftuJaZ+2zTr8geWuC4UOM2eJlZho7maC+8mLVAWeF8H9BeqHkaaoO6D9FeWH3ebexR+biPYwqLsNHh5lrlirw2yd/PQny/YeBHVr8u+fOzyLvD4m2LA9aoubc9YI44XOzkUdl0E6tx1jnCcvbaZM98xmmvqyzXtYa+pzVG7Sdj/4asDc+4mmNNV+2Mwg4NDP3AzD8Dv5sVmAZLl+ud4REzz3h5Auv7Vdn82uf367Nsfll2flS/sLMnmz9WeNGv8lxi57l0r7fmPZ8xEbvRht28zz1rPWM2/+aZ/oXNmko+B3zn5O7f7Rly3KyjyNZccjG9bAwz4rSgOGy34jBr4V3Smfup9LljZzvukn4UKrXjnv3l3eyU8ttJyW7nKeSiyOOQzfVwe5xQ1GbUUdSbStOsR37WslWVVr1H4MMx/rsoXlY/VYncPMTdFBn/Y71942fZ1tbRYw036AzFvmxr7UeyrbUn6Ho8bWuOO+CLkgtlcXtop5Emxqd1egYuAlrvRVj3XKh/vSz/AtZA1SzZMgte/9Tvxei3vHTtU92ctL7nFbDWo+ehH5G6TX7k9ckFP/HJNbJ9l37pKpv8HcIwHm6Bsl9wIni/IPR1GqHPdeT/wnA7z37H5tGybvpXOvTegWVewnqfIkb8WG6P4GxIqL3deDhZ7NTm/YX5treM77RrX1NE9Bfbs39TMEHdlRPz/PYujNVv8OtvTiCZ74Q20PdoGsI6qLqoJqiHA8rh9/d5T4pR7h740ip3930eomFw2Qna31mqB4e6a3610vyq+lWO/BpKKTOEUcPucmdmO3FTzX7ZyifTn6Khz99Y5tXt73EfW4J1ftsflK5vWvObCifl7LWMLfJq4twSP0qqnh0dy570rSsok5fX6PhqkKeMccy48v8YP28QP9uozLkb8a9UyHdIknXcs1HcFA4a97zj18OeWFS/HkBPxzmWXkHrHP1KcXdJ1qVmrqY/WGOeETbWSqLlXeUW6I1DrRf9Fxg25HJKu6tmmSh9b3SGNUZQ/y6s0bHIcLzzREk4i9A7Yvo30TfKETdq9iNqg+nGFR48H9d0/uMN0lnmVPGecE9pI6kb3iudR8hz1smZzsHjV6seTxP7H9nes1GPRc90U/uuY9dF4iZJZSuMoLwbJHaaBOXdk6L36H3nXYzmXSffM9nb0YrI+72k25w3NP+aG9nnzfnun541Gytuv+L8ix076FnPV0/8cuPPYJTkUScjj3xnrEyzmaiNGg5TVv8YVONx9Q3N95IMQeN10UfPWmZidgxljkEflqUbHeeq+WXUBnXvDYuVyVJgOaig5SBxrXxThXK5MdzBWYcoZyQOCoQhFOWHnIsOfI/ohI65gu+bv89vr5z8/94rNtq/P2C8k3KKfrR92wvDX640Z3u/7wv88+b1csV5IbBDuKE/IWbhBx8MT+hyfOXArWfLP1GTsUZ+Q/+dBm3+uF235ufzL35/uI+9zyeMI12G/vAHyhfbUmDe5r/Gb5v56XPXOrKO5TT0229b2+67O2+1/G39gkVRG0ovo3yFGfo3bkQtXltl7vSkoxkj4x76gc6FeQn6Gx6b0O1y+Nw1T62NPXvs9RcPGOXE0L/auH3h0eXmztkTnzQ38ux/fuHsnMT/XxM///DO9Rf+GD/7gQLvzHmCuL8s+gnvT5pzu2S33c+Oa7V5xq5Nx7iDQPyvWnVN55/+9Xd8x5MTC3dcXpjByiTxf/WXeeo842z7T/MyeXZ/XOb7D7lPWZ6rQbG+NyZ371/ROaa/Z9LFvp+TDqL/1YvnPmzcd8CrU36f0Ps=
*/