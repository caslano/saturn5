// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_TAGS_HPP
#define BOOST_GEOMETRY_CORE_TAGS_HPP


namespace boost { namespace geometry
{

// Tags defining strategies linked to coordinate systems

/// Tag used for undefined coordinate system
struct cs_undefined_tag {};

/// Tag used for casting spherical/geographic coordinate systems
struct spherical_tag {};


/// Tag indicating Cartesian coordinate system family (cartesian,epsg)
struct cartesian_tag {};

/// Tag indicating Spherical polar coordinate system family
struct spherical_polar_tag : spherical_tag {};

/// Tag indicating Spherical equatorial coordinate system family
struct spherical_equatorial_tag : spherical_tag {};

/// Tag indicating Geographic coordinate system family (geographic)
struct geographic_tag : spherical_tag {};


// Tags defining coordinate systems reference models

/// For reference spheroid defining parameters of geographical coordinate system
struct srs_spheroid_tag {};

/// For reference sphere defining parameters of spherical coordinate system
struct srs_sphere_tag : srs_spheroid_tag {};


// Tags defining tag hierarchy

/// For single-geometries (point, linestring, polygon, box, ring, segment)
struct single_tag {};


/// For multiple-geometries (multi_point, multi_linestring, multi_polygon)
struct multi_tag {};

/// For point-like types (point, multi_point)
struct pointlike_tag {};

/// For linear types (linestring, multi-linestring, segment)
struct linear_tag {};

// Subset of linear types (polygon, multi_polygon)
struct polylinear_tag : linear_tag {};

/// For areal types (polygon, multi_polygon, box, ring)
struct areal_tag {};

// Subset of areal types (polygon, multi_polygon, ring)
struct polygonal_tag : areal_tag {};

/// For volume types (also box (?), polyhedron)
struct volumetric_tag {};


// Tags defining geometry types


/// "default" tag
struct geometry_not_recognized_tag {};

/// OGC Point identifying tag
struct point_tag : single_tag, pointlike_tag {};

/// OGC Linestring identifying tag
struct linestring_tag : single_tag, polylinear_tag {};

/// OGC Polygon identifying tag
struct polygon_tag : single_tag, polygonal_tag {};

/// Convenience (linear) ring identifying tag
struct ring_tag : single_tag, polygonal_tag {};

/// Convenience 2D or 3D box (mbr / aabb) identifying tag
struct box_tag : single_tag, areal_tag {};

/// Convenience segment (2-points) identifying tag
struct segment_tag : single_tag, linear_tag {};


/// OGC Multi point identifying tag
struct multi_point_tag : multi_tag, pointlike_tag  {};

/// OGC Multi linestring identifying tag
struct multi_linestring_tag : multi_tag, polylinear_tag {};

/// OGC Multi polygon identifying tag
struct multi_polygon_tag : multi_tag, polygonal_tag {};

/// OGC Geometry Collection identifying tag
struct geometry_collection_tag : multi_tag {};

/// Tag identifying dynamic geometries, e.g. variants
struct dynamic_geometry_tag {};


/*!
\brief Meta-function to get for a tag of a multi-geometry
    the tag of the corresponding single-geometry
*/
template <typename Tag>
struct single_tag_of
{};

#ifndef DOXYGEN_NO_DETAIL

template <>
struct single_tag_of<multi_point_tag>
{
    typedef point_tag type;
};

template <>
struct single_tag_of<multi_linestring_tag>
{
    typedef linestring_tag type;
};

template <>
struct single_tag_of<multi_polygon_tag>
{
    typedef polygon_tag type;
};

#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_TAGS_HPP

/* tags.hpp
P7Is1OF0mBBTtUWBgDqjxwmVXkf7ekmNAJEm8YMxzJrKg7tiU5AL7buGhkKCEcyoIvApEUilh+y1AIpYCcZ4ARpKvwIrhgcRTTqD5rMZVU3qRIo7nBVyhnkQyzGaoS9cVYkGJrY0Hw3XRvJhI2uZTk71anBtudHBtWiBUsOI9hye/qq4mFwq0VdpzudZlAd96rdoTtjyn/8QH6XD2fHs2kF5/43+3fq7h4dinnND87Y+eUfg9kJws2CUYiIKoA+11bfRM/8UNvkku22EH55+gUpaBsI6VpvYP1PgevX3WbjzstKLRWUdjqM1j4+aoGnrO9iprOWVdr3Wc6Ga8qQIQOeTEo/lZEvMKjvnWtBMtwGFYO3S2WKBHU5f66reA27tRPjSQ6uMdgY/XzHmorranMTfJyZGP/7xAlHJ8ksNWD0ZWumjXXn0+ruos2WC6vo36sTlXML+93iFFfq13oOlmqGuBW6z1q6dIMk/z+LiynrRC8v5pq/LRTa+/avMDNDT1b39grpDc7YzP70rPFx+DeXCUOGl7yrZ5BrWmLlHmep9fn2Igwwf7KWKGCSQ+6YRAECvAyScPeXRy31pJe7CDkcktwb+ZnjIGqZ4WWrNqRf07PZExrxYRx6zA3sZMUCP2MCtvkRLJ8ALrBi2pUzX/o6AvEoGyV5k3Nsjs1ZdFxn2x32x3siJvp1a+bjc1Ich6ptOCCxerODlLAfcdqdV8YsCqD8Zd4p4H3TuesK9YugeSrH3CVjldv18NpVbScG3c1ha6m50fNg4R5yv1CkkyEU9NGHlfPgjy2ohuLqkBk/tkJAZhOvrKpzPgILUgYXuEtXKbz+eM6lXeZw/afmPCKiT37B26uCLv5O78eX6UUxZ/J8FZUePgYlBGYdOUQ5kucJ8OEl8YPHFxRMXn23YnxgALqBoWQKHOEGAO26xZfN25JfLorBZ/9N0F0o1A70unE0Hdefj3XWjAGnaVKHOAJGC9GO8Vnt8psqekkfCvuFpaEHMOBa8T5D+t2sKVq+9hacFD63OCpLmXtOTD280lat00UrwCSuU7IV99stB0Ptpubai3vJWa3cLpfyFJVx2lNdefNlDYGWAnUbOQ7dissiICMYTggXi3YMkyhh4T8F9wt2OodOxAAQng+yTUemXrvtCkUQ8Pom+3Ly2BmYmJ7diy4d2b/ka3PCx13rAkwEom5bVmwZ7P0UlPtbA8YGHWxNppEMBSKkARSDUonwAmfPgqN/hkBfDZ8PjNUs4WdtHb/7XMCxaBvro37PnAVe6fYT51IjjT4/wPxz3haaO+vtngMYjSpTgoBqI7KJo2wvOJRYzDbwXh8emvJkL12xYZ6YvV4OzLwZtCP/Wx3DbE0/cAbqZB7/ll45c7f23+tY34+22M1WPTKSlFCAlEDlBB7+dJVNjg/Iie9tDLZ2NC9feXpm+eqOSFuIUqX9+m10DLyY62kuiqI6/ztO3A0Fs3V0zU9DAT6+stTIjd51vG6cDDemMCElfnOHkjk0s7UM/FuNNML2Fy92XgADgFEqgkEO8+kdSMnMye/EztHSqlxNGXDQF6oMO1e/dMydpr7fHwRsOxfU7e+iQHogh+386N/fe8i9vvUEfgICvSvf1PvCtTnn4Ma5/S85Zh0wz0pNkikY/AVerlxxpVzNKLgCwCtmRgIyMjKUCa1+lSdsxlsm4Kxhf0AlN0g8bEs1qHu8jAbvP13LwCrmdMck6/6xi244qxix4DatwrBIKeeHY/qz7dqF/v1hh+O9xRPRhWR74/k46kvOLX8KaTfRIXR3a1qDrIgxf6Puvbm7ARA43CF3z0Xe1JitJkTgGCrhAsVx9SpG+Js4tauAsdtJfMfHZx2w1cNgFRzwTCgdm6QyKtmzQBuTRAcRtIBrwYw+osh6rJ4IobMjdhcHXgRBAORoMBZyBkrMS2AtoHo+AcibQ9h/jQZdvzHcH5Hg8pJrw6+ECc0WHFUH8QUkwxNgGCcmpZengqS1hIxwH1eOmsgKdA0rPrW1ixNbcLQdEwbQ9awTcwPHYmuh45oJPRcPydEQXbXA2rYTSEpNKVCqbca4TyRU459FW5fYXbTCSyBRisNegRs09VC6UrK0q51/VwP9tsl0bWVxh/cqOSpt385Hxk1klS7iUsecGfNuYsKjPf7HnImljdjazB/zb9Lsc1LO6wtwN7Fe0CuKbluSIY0PgjfXhc2TRhhIBzi9f+urkDyQnJ0a2t2HHpEq3DLgv4SQfX8bi5CX1G3/x6ZMGTQeqTAcYGcr6OrmwxjY8HMR2YfnXByOTt3HezLkd/6Xw3QygVO9r97dAwcz4oFhpYlH7w4tdlYDhHm1CWb9oi9/WIx6OzWvwpe/TDsCD0Cfk2DPdnO3Ct1fk5bIDdxrPyZbrLUQbSDs9UCTZMpI3l7admZN9XWagBUG+13bHr+8Of0zIK7/AycWHv/9vjViolSwJFusnff9dnVg4qr7zO3b0TX64ZWO/Ldp3cQHYv7tvwpzTRRJ5cCfnTk/CHQVxZD6MoFHNgBzJjthxacwdO+SQnLBBfy0NGBi4Q0Cx33IlQ7Guc30dn/uGd29vRFxcWj/nnY9kBv/DJayCoY3HHii3zpENrO2pdTQmm2O7No35YLznPSfOeggagM8ArJuGtjWjgJa8SdO2A2mE3bpV7TakZLopyxJwwmDESbwHqNYnRNyYDkxutV/ogX/b7kuYvYh5wz6Ob/iMoUeBWuxc/IWBvEiBZmLJpRar1rSnZLvPcWgDY3hy8x7NQ/xezmBohXHWjIOBooWRz6TTB34Mzv7KvdGvI489W5fWFlQRKJJ6xbOp3Xv34yOr6kgjI0O5ROo3lD+q382NZHUDQPb2aqrfT+44QXoLHLIBc5bYgXAjW44bvv3cxuwYZu9mBBz7p3up6uJxr06bgPolmevTyl7xCJl5a7v65XcbNPTVG2aYT9++h4ZMqJ+X74E+lmjHEWGEeN8GhKDbz7oOIs36LU+bqNXrqCEphe7XfDZ/ydTVsxu8d75s6aUtl5eRxi2JBgbF9ROg/+De5y6wrTvXMC8Xv65kOr22dtB4ctTjkhsLZUwWO2xpbZYPvWgsqEL5w3kDrCxxFsp6UZ+JcNvCHA+tNWoRVpdpKAT8WKiPQeOnKV3wtohBtk6fskwQpKnm850AJFRDZ/RYyGcx+txF05fd3cBpvh5S7Y1NSNNN2JYNQmvTggbbwR657CCQHerGLpD5sVUhB5ZDdnSDiM1FlOOTTj6TzUpSHT32LVslS1hnE3lnMXBnDau7qQBsRerEOu6E3QSGj092sMzCqoSHl8cvCZzwT25pBayoCjUe6OoclJ2C2PvDOqJNTa7n53PzW7FT55f3Mmvf59IAi6uemvlrqfUtsYVkzhKE6vVGYcD+S6aLUGIJR7Iy+XYpkb3GALRP9wo04WgWww+vGzorBGOZzmFfSmaUUCaAxGa0GaCwIYdae5JO7ecBZiuH7AALww888rw3P5OPek778rKq76h2o4spkzQgkfeWJgXIuMSClV7x5vXqcWytuhjZNgGmNTtRWHgMiyZ/0d207DVuXefzQ8Ca7q6MW/9yzKEjMQfPej+r5LmPcFMeze93hKMQL1xOca3run5JRK/3bDhZ2TRK8t0ds/vm/EvT5Nln4QlM8xaKLlkD32UgvcX5yOvnDURtHmpPchknU9Wysa0q5mR1de5maMcZBquzI8YRNfP5M92z0H89iTJPR/lKsAO313XgUeDiUbWVJMiKxHKMQqeaLGKJXnBFrUZCzVddhY7utl9U3iLA4d+7Xl5HqBUrz/bMRgNhQ+fdQCQ2/nvJTUqGkfKp42E0hps1hRchcHKyylDYalKUEzpr1+4Wf/0vz0YwxPZqH1iDzMd4TKE4sDjHk7b9YweN5ZDaz43mKr96BreZ5uMjM2TabQ1ZJ1GWCPOUrkS9//XgOaym+cBv8FrFpLq4vMZGisc8D2gUmgy9U4HgC3GgUn6qZk22PZ0qsPL6GlSqtl3Oqh3rdpcsPxT5PeFwqEkyv6x5gJWi7jl20CSaR0fhwG1ofBkNN8W4uaJeDjS7/xnpE6W/ptSPnveeNxAcsOzWTsyjeyBxIFIQLpZ9JQgbVZW3rplrfV1Bs6e0MggKIVoBSYBUdN2Rkoq0YqDqqPWkbNHfiPMlNFj+kFmASM4CFwB+9ZWIJoIZK3FBDVkcwufnlaJi8tlDsrLXWT1J5uRPQpKJAqIxUjncr7mSSFUJF8l+IIClf2uHLfC+brauLfRfZWqif4PW5JPxD16B0RQgEkExRzcP0kAs0TZzcfEiT3ITE2nf4dOjWaSKJavRRpPMsum9dfooWSAvd31v63YuTyOFrOlccQ6JrAZePbNI7iMZGAVkA0cnD54JMskXHQnTvqhscvjB+L+3JqNs5kG7WlNwg+cXgnHhFEp3k6Po5CcdS0UC4D4ffnOKRLP440XdSWr4iUI7Cob0fT8/tMylTe8/lNqc65NeGOAhmABXgMA8yPBWD5t2Kvu5HD7Xa+xoA6SI4HVaSEHP/oiQnOfr5HQRq919h64K09fminZF5GtfxVIgoSwKISgsUYQ8ynUWBliYQQnDp4GlsTfomn1GTBU1ou068J990VKsGzzTh0uDDqvbWXAIK/VzwCEua/KgaSixxuYuGPjKV+4Ziz9Suh3DfCdzPHh9TMn6hGZzGH9iKsA6EMX4yLqYkxU18CUmTSv8Gsq4CddJ0LdCnQs3anF+ZCYlfoVihl/hauSl8yLgPquvG/wLHaP5338XzWtTg2VO6HP2ZRue/cWUQFuDfLDtaASmdlOGcudAVfg1Fq2YjaZafsBsJZsStinSnFcxv1qtnW8HCR7ig81HmgHgFqOkk78Alfw+3AW6UZbHDSFXb0FJbRc+V5yBF+EHg0hE/e3PdnVLdthdH1gDjdHuhtbz84I5MjloOErTeMJ/stPy6/YYSLQ7kkBZutevQeDb8y4bbKLV30hnX77cyF0OG2Qef9rFwZnL8YiJGsEDY4ZgiTczCBh3gNV/9wP4rRkOgvPD6LA/Yz++ZjbVfFoHgxnU2Hi8IzE6FzRQ7K/R0ab9WtW13+lJaK10naz+HdffKn2CN9NBRl3E/37h+Ym5k4pehozEaGOgKV3u27o5QM6815mBELD6861FnFa7Y/K0EmjUs9FkAvIjY83e0nH6Hk++rCgY/D6ocOQ8u3gVpYoBpNT8gSmHyYxjFdsGtgquSUURtT4PCmIyGLP73iw9BKK8zZOmEtMKaptXrdUNMWfk0sGlk0EkbapL4PN5ArRC0Apqq7bqzqFT2pkak3kyNpUbq8tcHoL6yiNMPUyFd6PZ4Mt6z7jCz2jICOWhk4eKj44GsKhM/dsd8knVfPYDv5UVwe06SI9e1z/UoeDEpJs3qeJ4Y8Veokecmhb11ySr6aAN/XTCyHQn4Vo4TWIi05yxGzdQ3O5YRAcqMb+7IWY6Q1q2XAWkyzelCkJipblV0joz/j38fDIOsYo4gxdvuQg3ZupWtrIqO4d1cpumLC6C7zBjtTlgctuTQm88FbFqNanVqiWq/g7qQLdtsFQ16OcWXYV/HibfghLqkBR1b4Rqj8hTZ/KlT2mPXXKQkH1gXX2p65RNnZOC22o2KZKs1aRG0CEUT0t/+0CnqI6Ma/i0VJTEoNmgHa3+PrwLhTTuydIaLrvyFkzQx6KRsLj6tgyeBI1KQQPPkj64mPhhQieA57n2pb/NlfvT/TaQ28TqsXamXJqxbB3YpXHLd1Y5wMCBh2bwwUAcYtF7EYEQa5E1nmKFRsa8ARr7VOWzx9LiRiWetMx5ubnghQNQhPoaSAaG7CWpZas1V04uBqoGh5CJppaHS6Moj/oogfaR6VZXij6tdDEYKbuwDkBuisUCl4dIl5X4p/Jr+6Eay2ZCY9HgbuB5qVoYpdqbq8/vRWCsFbFd7eJRD61d8lJhrKhEJKLxbk2wpqIPMjMiqJ7npWjWA5Eu9ITLsGhNaLdYLCX2SGVF+7xGmf2eiERV2u0uoD+g5vwoW29YM6P+iZlVFBmn1NDf/K1zZZMB5pRMf8JWNvOFGqqCqom1mE0q9GBvQfYz2MEJKSW3KjU+cmRUj+WDSg8MEYAl/Xi96804l5P7HTVrnES67+KmOgYu4YTkeBKr3LRoZhgDwfIyoKYy3ugZLniNAX4XcGgjtjyuAOBTqdx3Dlf9M+weNGfyDoh1WwtLyo/+nBVRYFeyUoClj6sdK3m6BkmRRWs8Ofh5571VbdeZBdu6Pv1ECetiwDHIaJcRXxFrDzfORKZzgBRjo0gViwNN3lu8NDdtbQpdoOnyfEblUw5qNBtagXuaEKxtdsvCrDgGklE2ZH3IUFQCNFcT0RUCUGAFFBL7Y3PSOs5UcP0p26jPhmomLonS/JQbXGnm0kWlVGM6IX5Wr4tJlrnvoyigymlQHnHf/KC1JUuytrreegmMD6u8et3lHpYQQFdISH6nxvLdcLM0G8qiVjEJMXtOffDYwwFDo6vKZCDTHksMCNSIWgJfAwVRfyGN9REUpn0nWZqHPTd5zku3tf+ndSjFz+hcBHIk9sy6v7l0IgnhuWhLJUTKDYQLy8DZmvpL/wOKOBNMeJOThfHD/2DcCAAg8HczFk0iPfuDPxvkL/1L/yfRmroEiG3D0FfInEOtWzozB/8TgsS3JvT57NLD3nhcZABFe4KVR6uyGOyVWmyHEN/Fa8B/69mqnjYczYAEgKNAeJs2/H3A3BkGOAKJ/0ghtoGRicqT7ndvynKxJW3jjeZTKsF26J2XLKxHs9Txcv9NR5wiJ+AicVRt/E1eTSENijwyXq/tPpAaE4JAKAIEquhYWm7BJU8ElbZYDY00R5HK7AAAlQGjXxLbdnUQrQ3m8Rr9l235Ox7+e99uBjjEaOVVRbT87tHLHBxNtMwA+cFEYo2auZQsB7mVwIOsxpjmUD5u02Qg9RzF3Va2rXW1Bqb3ZZ/U8MB6Py3qSL5bsAE9WHVvkq5yiw8LL6wXx9gMyyZh0QCTOBD8uZCqyfRkDmLiES3IxlahHbc3if7xZtoQHpsqc4/l4b1rUrKf422YHJt6svvY2aUwU66qQEHsyoZAwZL2IgPIpkhxW1pDUrTQqh4mqaMREoIuFxyLOeiQIw9hRCuv/sIGvfKpvukQsfKpSJh109InKR21UvlM62rcDsVSPZaLk3QxbuQiETlF9s0QzhupRoA5sVr3ra9TzL13PHNsvmjdHjEODc6DDR8rU8rPV8/t2n6lat5BRlJLPnRaj1/MZkOKAX0c378vBBnKgPP7fBh/2iucRTvJjz/oO56LRrCtPpM2Y/AOnaTdJsDjrodoAVKKGI+kxKycgdE8+vjdDTWbvHTEXYhJNEIxHSLAmEmjX9+m47FooQOzmGuDffkvWTdeS/HWNDY6ITrPYn/oHuzsjVaBybtroaHrJHaY0ZlDsYTI8qs6urUYk3VhjcX6vk0y2huijnp8VqHe/OTMwwF86Qkj64cp3gICcaREjTQJxP1ZJ+/ITwhpIQEZZSuWXQIjEd8TqmYRb4pNlgyR+b5Q4b+9rJPGbjBI9fzvye4Xh2b1NjfIQk7do6QB9W8dNnaQMM0z3Yv0j0ZKQ8tvuDvPi6Y4LE8O3iHYoLofAyJy
*/