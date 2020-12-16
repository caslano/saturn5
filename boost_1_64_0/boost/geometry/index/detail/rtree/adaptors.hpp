// Boost.Geometry Index
//
// R-tree queries range adaptors
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ADAPTORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ADAPTORS_HPP

#include <deque>
#include <boost/static_assert.hpp>

#include <boost/geometry/index/adaptors/query.hpp>

namespace boost { namespace geometry { namespace index {

template <typename Value, typename Options, typename IndexableGetter, typename EqualTo, typename Allocator>
class rtree;

namespace adaptors { namespace detail {

template <typename Value, typename Options, typename IndexableGetter, typename EqualTo, typename Allocator>
class query_range< index::rtree<Value, Options, IndexableGetter, EqualTo, Allocator> >
{
public:
    typedef std::vector<Value> result_type;
    typedef typename result_type::iterator iterator;
    typedef typename result_type::const_iterator const_iterator;

    template <typename Predicates> inline
    query_range(index::rtree<Value, Options, IndexableGetter, EqualTo, Allocator> const& rtree,
                Predicates const& pred)
    {
        rtree.query(pred, std::back_inserter(m_result));
    }

    inline iterator begin() { return m_result.begin(); }
    inline iterator end() { return m_result.end(); }
    inline const_iterator begin() const { return m_result.begin(); }
    inline const_iterator end() const { return m_result.end(); }

private:
    result_type m_result;
};

}} // namespace adaptors::detail

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ADAPTORS_HPP

/* adaptors.hpp
18n87iYypNwFKReAm6TcvdXM+bsPGxrrGSca+fAGXIsZuA7n4UN4h6SXSfpeXI8P4gZ8BB/GTZiPT8p0DuAWfAsfxxP4KH6JG/EbGa7bKX+1X94ucv/YFatht3L3j8VSrrXF/eOD0s6wBusYyyH3fw9hsDH/8nzmetTt/+ftrw+flOdWCuW5lafk+mgfOucn9Lz9/Dwq87NR5meTzM9mmZ8CmZ8t6Hz+KlamN99R+fmrZ6uZ/RgvYD18Udbvq9gM9+MALMZofAkn4cvSr/YKJkv+NDyAs1VaLw8bkv3y3CrPxeTJczELZX4WYQtcgq1wabnpRcr0mlpM7y6Z3nKsjyuxEd6NjXEFNjHT+niUIdMbZXE82iH9STvRmN4uDMYn0ZjOHmnn24tDZLi+n5LpBlv148h2cBQD8X0Mwg9kO4gkfH+rWG8eGCHlP/Ixt4Pj2ABLsKGkw8y0nk70ZabzuUznC5nO18Z0JB0mad1/8Jvd/oXSDt1c+gNboLNc/mXKtZZybaRcW9T3WVIuxKL+9st+UIx+eADrqrSUJ3+JlJ8j96NhRnlUbwd6m/WejMb0U7ARPosdMB17YAZOlOEpxrRwFt6MuZiDeTgXV+J83IB34A68B/fiA/g0Poiv4Rp8B9fiJ7gBv8SH8Wd8BF1cqDv0xEfRGzdiMG7GhliAzXErtsbtxvzjDuyMu7A7PoG98Unsi4U4Dp/GKbgPZyLLebE/7w/789ZR6cf8u/Rjvo+BktbtVlJ+oMV6T5DnlxIxEpNQ9kfCVZUbY7E/HiCfLx7EEDyEffANHIR/w2GSHiFp3Q/OdO22ww1yfnhYzg+PoO4Hl3LVrLb72rLdy3NtLdB5nCqRciGVjlPoYZa7TrbfIRiIQ7GBpIPNtL4O5n0dqc/K18FtpZ2zA4ZiR2yJnbEddpX2yu7SLt5D3h+IwOskrY+HLvb1/7bU/7tS/+9L/R+T+v8Qh0l6hKT18ZDp2j3P+bwcD4vkvPgCqu+9Rn0ecbWvz+5yHdQD/fBaDDTGS39STww203p64ZeZXkeZXieZXoRMr4tMr7NMr0v56y2mZ/d8YIhsXw3RGN6o/HOMUs7DotxYd+l/Rncch/p619V+u6wh25c3eqIP6n4oKTfQYrlTZL9Mw2aYjq0wA408s2R/zUS9nzM9u+vTL6Uev5Lr01Pl++vdXG37lT+Qcsekf/VDKRdtlKWc3fn6aTlfPyPn631yvn5BztfPy/m6SM7XDNf3Afky3fYW9wFN5b6kGbob8yn3m61Qne8wTNLNJd1O0vp4wPTt+inayvTby3SuwRbYEVtiOLYx0jK9Y0Sou2y/cn4zts/DzudYq6l6YCHM/m5PHIpuOELS47GaPIcWjDOxOuahD96FNXEX1sKnsA4WY118SfK/Ium/YX08JsM/wwb4LfpjmXyOj3FvirVdzOF+6IIByPiL1xse9vtTC9mfWsr+1Ar19YaH/f40SJ7THYzuGIX6/sHD/vzwheyHX8pzul+hPk9Szu48+ansT5/Jc7qfY6Ck9f7jYb8fH5fP/Vie0z2hyxkr0b7c41I/BdJfthX1/aiUC7SY30ZyPdgYa2MoBkha739Svq3F/jdBlnci1sMbsAHGYUNJN8VYbGEO1+e3DJnuZIvz22yZ7lz0wzkyXdJqP5uHPXC+nI9ycQwuwPF4Czrvh0r5HLv3UU66mvvf99gGf8AO+E8Mx59wJJ7FODyHc/BnXCDpPEkvxzJcj7+gs/5Kqpmf39Oi/oLlPB6GTbG5nMdbyft/LTFc0l0krZ9j8pLzq8X2sMVVnt+S54oKUD+372W/nx2U4/AraAx/FVU/hPFsspQ76W6WM+olV9r9q7uaxx8=
*/