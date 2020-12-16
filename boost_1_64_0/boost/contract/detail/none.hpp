
#ifndef BOOST_CONTRACT_DETAIL_NONE_HPP_
#define BOOST_CONTRACT_DETAIL_NONE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

namespace boost { namespace contract { namespace detail {

// Tag for "no type".
struct none {
    // Some lib code use this to avoid unused local var warnings on #if, etc.
    static none& value() {
        static none none_value;
        return none_value;
    }
};

// Transform `void` to `none` type (for convenience, instead of using MPL).
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard


/* none.hpp
5zq/K+W+J+WsjFKjyOhGKXtTdp4W/PWY7L7yB2b+3mLm6A91TAgsBTFx+ZucrDObhBfPPz/Jc2W8ntvWOujvO4zc7hSa6Kv+ifDwwamZ99657M+MbnP9Olf0lGd028+l3U6Gh4336/777Ozf/xRf7MIcm2NNLJGi8H21vb2020miTZFH9ttZ0WxswXty9zktq91ndg7J19DS2Vjf3S7xegMhvP8L0mOC3dTS2hhqbqxtEJfW/tmsw9pGo9He0U3We22rFKgsF0rBQKZ3Esoia696/N1wpZNBE+36m6Ph3qyd+hu2bduHU2T2hQcEBnEB70M5jZPq27ql4i5kC/OZozuFn9lcenWYgg4Okd8A9qS+ld3e1xWNOAaSHvRXd2wwSpZhtCsVpi8b2X1URzw2ROZzd7xr2+D6+EB3eP0A+BYOy9JkcBLqK+Ax0N5nWqtw0oX1/WSyRoh6LEnbVVe2Tnxh94Mcph1kPweueW9izLl5+uBKf87sIHuwbUKufHkPqm95UvrMeKI1NrQxmtBNju7tWLOvjg1ZOM4XkVU97fAwf7LktwzFUrRNor972XzPyF/gtPUwGGjzywRt72scSiW2cY96aP/XhZOm7rls97fQRjvqgF7WHyVjp3aAxvtglAhl6Mzj8Z4FqKzKfNm0D0cT4RTte7u2JVPRQRECjJdjnYzGgLfAp8fMKVRhC5lGMGyRX442a0mmbOFL/LIWDu/TnhIbWrpEsn1/isKqpB+4YpDtCsn3x34SfGz1/dHIxq70YHY+NHiZqjM8NXkNAwNmmmAfNQv9LnfIodN3OSG8A+H18cHBWNZnszbL27AWVdg6gHEx6Od+rzXuWmN94AMZXdC5OVw71OsoKPx3zj7y3MBsiCX4HdxtHNPwKJo6D8Fcf+l/0MduvpLMxB/lYZrfcx4ah/M3GmIvEupHyousH2CfkeblubzhbB/lu3RiIII4kxknnOjvTXiad4ijHyOlNxDPwT2M6926X/5bKZ9WUNCdlIZ6C10dyfQglplGeTHAmc442XQJpQf6wsRtNm8m5cU3D8WVzsMk+1mUR+ohw/s8hxMdjPWCbOZLnvqa/uBsZ7/cEqVVyOOd6xyKbvG/9xeRWB+B/q3J6OH2rhxVbnPh28E/5F1SG0P7UaKr36e2cF5XmByunYsXeXs0b7LmLfb2HMW2yDjvTznfp+qTTQnf534u0Rpf7Gps3BqJ8qJFH4xIE6UponI0kk6JznY44/bH6YqGE5F+z4ePz8LbojSjezNJj+ETsPzAQIz8ej1Dzj/O69ck9sG4dj5OvJJzsb6RRzwtT110oK2lW5yPp5QHw0h4bFPgePdP8sL44TVra2wwPeiD4HtYXbqvz7dL1F/8ZO43vZ62lnoXj5hc0hpj2OTxt8PAdXj14iVVtVzE/zMzd5+GtVbTaiOfmTN3ncgT8YFT3AvU2B7Scql0krNh7SXbJrxBcDVvoicar3exl53bjYmEW38ibiGENVjy+/o4BjXMZc7v0oe9s3NZaS8BH67TfUIC5zDnKwmcy0pjqZf1oa/eWp9MZNKz/HRoNT2yrjSf4W+OTQPxcKozuiGW5G/DAvsLwXZ6awcHsxDOf+pIyh+n9ZXzN7gCEuez2T6nVGhtV+0aMrbaO1fL+ZScHOrFNcH93dndSsdqGzudR6G+savL9xE2dpPZymRGQ8j4Hp4b/ftgR2NdqLWhMxt7WnMw3vTzQsONLdIlsj56wb7+MY7x0/BMkBlTL7jvLmYsvMi+ZrYS3PF6/uCs+cOeW2nDQ72tvt2+Rnyxf4N+2PF/kOfC4Pbi5wBNZOS/R2QXeG4MNRSZz+2dDT4Rmyv98IrZl75KadcfL/M=
*/