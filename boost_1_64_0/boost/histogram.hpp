// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_HPP
#define BOOST_HISTOGRAM_HPP

/**
  \file boost/histogram.hpp
  Includes all standard headers of the Boost.Histogram library.

  Extra headers not automatically included are:
    - [boost/histogram/ostream.hpp][1]
    - [boost/histogram/axis/ostream.hpp][2]
    - [boost/histogram/accumulators/ostream.hpp][3]
    - [boost/histogram/serialization.hpp][4]

  [1]: histogram/reference.html#header.boost.histogram.ostream_hpp
  [2]: histogram/reference.html#header.boost.histogram.axis.ostream_hpp
  [3]: histogram/reference.html#header.boost.histogram.accumulators.ostream_hpp
  [4]: histogram/reference.html#header.boost.histogram.serialization_hpp
*/

#include <boost/histogram/accumulators.hpp>
#include <boost/histogram/algorithm.hpp>
#include <boost/histogram/axis.hpp>
#include <boost/histogram/histogram.hpp>
#include <boost/histogram/indexed.hpp>
#include <boost/histogram/literals.hpp>
#include <boost/histogram/make_histogram.hpp>
#include <boost/histogram/make_profile.hpp>
#include <boost/histogram/storage_adaptor.hpp>
#include <boost/histogram/unlimited_storage.hpp>

#endif

/* histogram.hpp
Y7WdhKa3xaN0QXlq6hVgMtUkCz8kPZxLB1sES+S3ouCNaptNKJjY+uZoVNSgdPY6ukxDzg7UzCxicywoZmEixt4S721ImS1lXX6iq1PdvlgTRfsSp+pp8IzkSWVxkX5S4Z0yd5bfZdnFdWHeNmJLUIaZeCVO2wY6d3BpBe63BWvNNnazzVsLK2WAlXegtR0enQkKeDqdiw3ox6HKRN5s5IVBchGYw8B2TyUqVTb3ihACwKUh76TcLCtu78OI4r/XAI5s6FVBOpLjfvFEW/8Pbk2h4RnuLZGLkSjpa3hfQM1V0yG6EBqD0PNp5h8hW6edCl7ju0qlLftt2ndm2ZdW5qwINCKy7pY3tOR2pUbZw+IIXQ+hJlZiy666NcF/PhJ+Ov1kQ36J+aPrELh9xrccAzxVTj9lYkz8VZXRlQyV8coettoJMs61F0eVc7AP5Ky07J51Dm99Zbc82h0+j1hfWMURixNjEMkw6RVd71gRsNiy6zi+XIunjpFdPnUA/mf8tawtJyH7XcfuvT7bGWtsI3cr1bghTZm4CO3dxP5imPrVTeSYnrF6ou3Gym9sX1TstV2xEWW8d0tCtDIm/Q6mt42lxPxej60vk9Uh+G97XbYzqiY6bTdWaJnZmg9vsTijFS5H5S3JzmilK6cSe1+43/Rr2TqOd9k6IZT/jnPfjsqvLOHE+ywVrpzaaJUTvJE+LmX1QldqEdCQsFob3J82e4OCQQt+n+ayud/xFq+QYhDBxjRbULWQn3tFYlFpw5zr3KymvQ3VcHj7jcB8Z4uqnPu2s57U+yyr0KhAanQ9OBgux0e3DYisR44Pr0kzyXRoApIaTapgg6xIOwQtmgRxN+SZ/YQTLXEu7czjnc29xlu83xOMoilj2RSu22rX4EkmJDIHZijrSnfOSti31U1L+XUGPJRdB+PM0ap99SFIs1UeEHqY3S0bRa05tZ7iSjTKg0axdmX1kIULEsnd9kYrSjfPaedFx2cvq98EuoR1nPQGyavqBVlkcOeywEgiheRclJ/LqwBxmEEGPG9LKnI25lFJ+lE8OHM257wvGtm2DIRQNKfKslGpXsbWOXMqXYA+rkybV4Xjks1OrBXvamXTvg+yzLhqVT5wNlTa/b9Ea66iEe/eLkmqrRuhvO1VtnhxuX4Ah2yivJxDKHuNWJYDSrfNuVLOP5LyxMg7mKYsNVoW8BiQpXTb3K2R/sjS19ZdT5/ZLP2DWvpaIz17jOaciuRsUFPSKVrS3yOpRyHwwMj4eU3rEydZ5BFgZWSyLXclFglqsb+We3xM7rlrSxuwUjlGc5MLGqqt/ou1RvZv1si9jTJvT+YFt/lM0X+UPfg6GN1s0dAqLfm334vkc98v3Tmnz8RFRxyvB7W0tUgbBZzN3RqE3SvcsBNX7XsfeYJfsOjgerfMQdEY9Wot133IhfSDTbHTdlsXViMsbw8U6QKn1F+PhPr1pNpTyz2G7St2cXtqxFD2ZYfmHqlDe/dp/Tc6tG3W6YuOOJ81WtLGA2hZlXmmtFdTH8GrGlwPFqN62/r/dUb5/+inYHQsy2wmIcnzrU5g/MIjCQyyO0EQNIqjbL+xBzqbwBwyicvDbR5eFgK1Cvv2pRUjlB2Ucdsu4KdREBl7aTPDGS7MbKgqCJwO1D+rrTt8WT/vvq2RtIYq+BF0viHIizYNVYnYRupEcUCOKgIbqqz+rsEDVshyv98HIlo298rgATsa8dRVaSafza0qaxB1E6KEQbpzH0BwcAcu3VdDxrDR1h23xF5cZO+DS4i9zugK2FsC4h6EPSOxADh7BO/igbRPmV3nDB44xWlz7/UUH8aecYot+CbvDdHwvM24g8a+UWBy5VR7lZU=
*/