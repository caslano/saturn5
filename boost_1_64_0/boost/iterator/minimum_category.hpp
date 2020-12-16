// Copyright David Abrahams 2003. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ITERATOR_MINIMUM_CATEGORY_HPP_INCLUDED_
# define BOOST_ITERATOR_MINIMUM_CATEGORY_HPP_INCLUDED_

# include <boost/static_assert.hpp>
# include <boost/type_traits/is_convertible.hpp>
# include <boost/type_traits/is_same.hpp>

# include <boost/mpl/placeholders.hpp>
# include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {
namespace iterators {
namespace detail {

template <bool GreaterEqual, bool LessEqual>
struct minimum_category_impl;

template <class T1, class T2>
struct error_not_related_by_convertibility;

template <>
struct minimum_category_impl<true,false>
{
    template <class T1, class T2> struct apply
    {
        typedef T2 type;
    };
};

template <>
struct minimum_category_impl<false,true>
{
    template <class T1, class T2> struct apply
    {
        typedef T1 type;
    };
};

template <>
struct minimum_category_impl<true,true>
{
    template <class T1, class T2> struct apply
    {
        BOOST_STATIC_ASSERT((is_same<T1,T2>::value));
        typedef T1 type;
    };
};

template <>
struct minimum_category_impl<false,false>
{
    template <class T1, class T2> struct apply
      : error_not_related_by_convertibility<T1,T2>
    {
    };
};

} // namespace detail

//
// Returns the minimum category type or fails to compile
// if T1 and T2 are unrelated.
//
template <class T1 = mpl::_1, class T2 = mpl::_2>
struct minimum_category
{
    typedef boost::iterators::detail::minimum_category_impl<
        ::boost::is_convertible<T1,T2>::value
      , ::boost::is_convertible<T2,T1>::value
    > outer;

    typedef typename outer::template apply<T1,T2> inner;
    typedef typename inner::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,minimum_category,(T1,T2))
};

template <>
struct minimum_category<mpl::_1,mpl::_2>
{
    template <class T1, class T2>
    struct apply : minimum_category<T1,T2>
    {};

    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2,minimum_category,(mpl::_1,mpl::_2))
};

} // namespace iterators

} // namespace boost

#endif // BOOST_ITERATOR_MINIMUM_CATEGORY_HPP_INCLUDED_

/* minimum_category.hpp
wks+qfyLN/KP77P0y7yDvm29wa5vw72FDrMj7m1x3aH2gH/QUpeQzFN943lZwtS21SPGZ47rIDK73qVfe51JBJ8W91aY5+la6wzD6/Z2W1KwXossQftozjsO3a/g/kDcY+FgbUd+N+M6D9dEXIsQZ8xGyU9kpHcQZNhY1sPAMTM+Yzfx38WWl4zLzB+Jy5qX8GsfT2MfpIm417Plow6bQN1A3TFMNATjiABbbeSYhTLjr97KLLO9y/N8f+5DznaqnbgPlTTd2VTrHF2nT7E3x6W2OmifL84yYt6EGIOQ+6k0xDMNZlmur+vI7weePfUdrnmqbgSW5eTc/MB1ES0Mef1Q/G9y+uA/a91gPpvhWxpjCm+J+2En2+lsK2OGt9eXKuAL4n4A6wua2MqZ4UPvpXFc3B/DzhXdbG2MDm/sOa/bpoPi9grN2BfiIZhPvQ6gp20dQAvL2FLL06wD0GXNOtqS5bqfgw2NcZXF1QjXQiWHm3S5jsydMGJshhO6fxK+KeSelYzHDdmfKC/uNa1lybAh2+MYcQ8z+hI23WbPS6QlsI7Azp5HReewXXCRjw4ucDb8dizOI+9g6LCxwe0B58WMFL8Jrm8/nmFiruB2Qmkvcnrb8o7xm7Is47jF+wwyju5OJawPv9GWhzoOY4x9mJzkaOwHNVr8hLttnVjUq0I9l+NVse+l96h5RcwPsM/Ad5hheQX5xjjxMvHTHn5g1nHc7VSB9m+Jd4+DkLde53j7g2XLRpefcVfZiGhPdFSZqPSoK9E39JSL6h/VBX9EtogOi7b0Dbm3izfe+/V922yWfdb02MzHlElfG3JEzLFB6Srj3MgwqImbxU9IeftMhUGIxniOFEwS636OV+bUU0R74qI9UVHlo+pHdYnqGXVZVP2ysdFlImw6n/dJDanz1XuY+S72XqxXrlPPwrig6AYlR5TxZj4Z58Y0TSg3jXHNRPiDm7WM5xRMDRqr1/OmXhN/9f2+T3wEO5Vf5nyp98UuXo3V0y8kT9uH2+oB0+BaxvY5307ca5227ldkvtSVPMgx1iyFXmvUS9YmtX1306vXjB/83PoX73ggfUD5vmdvrZF9rdTZW4NkXysVei3WX2VNkPzkW00iWIu6NZFzoB7m35fiKuLfQ3B9jeugnlMIew8uzjfawzgrQ5jiuZ9KNe6n0on7qAwH64ALwLrcX6U+uAFsCD4MNjL2WfkKbAI2cL3hW4EqXHuwJdgZbAX2AFuDI7m/ylSwPTgD/AP4BNgRfBfsDH4CdgW/BS/hPiwd9dwsyQN5rjJGXrXANg/iBpYDzwPrKHewBdgalHMdfHOL+Lfv3JOxuBzue6J4EKzFfU/q8IzOxtz/5Fzuf3Ie9z/pw/1PBoJvgoPAw2AO+AY4ifa4P8qc82E4h8hXvuE8V2Ijy+Ux8HJwBzgYfApMA3eBo8Dd3B9nj8pP8BfwZvAZcCu4j+X0PPgqeBD8RT0PWNbFc4B1wUPcB+cw2A48Al4HHgWfBN8BfwBVPGEeb/gI8EOwIvgRGAd+ArYBPwe7gF+BI8G/gpPBv4EzwO/B9eBP4EMg0s184XdvlXZLvlzBfBnMfBnKfMlgvoxivoxmvmQyX1YzX65lvmQzX3KZLxOYLxOZL5OZL9cxX6aBWeB0cD44A7wHnA3iWSQej4fhwXlgBXABWAVcCLYGbwc7g0vBdPBulU5wOTgdXAE+AK4EN4KrmS/D9Xcy+SYo+VIOV1/fXoeQ6xQwCmwKRoPXKL/gHWBF8BkwBnwNjAePgAngSbAa68Uy/U0DeoX3icE1H5fDfZ9c7vtUGXyA552s59mzz3Kd5Fawl5Jfnj27A1T5/2fwAXAnuFfJM/gp9yE=
*/