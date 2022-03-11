// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_COMPARE_HPP
#define BOOST_GEOMETRY_POLICIES_COMPARE_HPP


#include <cstddef>

#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


/*!
\brief Less functor, to sort points in ascending order.
\ingroup compare
\details This functor compares points and orders them on x,
    then on y, then on z coordinate.
\tparam Point the geometry
\tparam Dimension the dimension to sort on, defaults to -1,
    indicating ALL dimensions. That's to say, first on x,
    on equal x-es then on y, etc.
    If a dimension is specified, only that dimension is considered
*/
template
<
    typename Point = void,
    int Dimension = -1,
    typename CSTag = void
>
struct less
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    inline bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct less<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    inline bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct less<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    inline bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct less<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    inline bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::less,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


/*!
\brief Greater functor
\ingroup compare
\details Can be used to sort points in reverse order
\see Less functor
*/
template
<
    typename Point = void,
    int Dimension = -1,
    typename CSTag = void
>
struct greater
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct greater<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct greater<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct greater<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::greater,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


/*!
\brief Equal To functor, to compare if points are equal
\ingroup compare
\tparam Geometry the geometry
\tparam Dimension the dimension to compare on, defaults to -1,
    indicating ALL dimensions.
    If a dimension is specified, only that dimension is considered
*/
template
<
    typename Point,
    int Dimension = -1,
    typename CSTag = void
>
struct equal_to
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point, Point,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension, typename CSTag>
struct equal_to<void, Dimension, CSTag>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point1, Point2,
                Dimension,
                CSTag, CSTag
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <typename Point, int Dimension>
struct equal_to<Point, Dimension, void>
{
    typedef Point first_argument_type;
    typedef Point second_argument_type;
    typedef bool result_type;

    bool operator()(Point const& left, Point const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point, Point,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};

template <int Dimension>
struct equal_to<void, Dimension, void>
{
    typedef bool result_type;

    template <typename Point1, typename Point2>
    bool operator()(Point1 const& left, Point2 const& right) const
    {
        typedef typename strategy::compare::services::default_strategy
            <
                strategy::compare::equal_to,
                Point1, Point2,
                Dimension
            >::type strategy_type;

        return strategy_type::apply(left, right);
    }
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_COMPARE_HPP

/* compare.hpp
6/XuuiXo9WzbBex57faNO3za139xebV8BniWfRB81L4HuLu6P/rW/zn6AQCI+9E/5l8FKATQ/WH59vv8PRNY+3SSBEzY8LgFZPnCfN/9puIBWAeEvWbIf3H/yv8QePY/+RRGACj74rMU7dUh7sCNyNv7zPjqLsdgZQT/NC73VfHhmN11Hvgq+/CBRPVQ/NLl3dNbIRj4/fKIuBn7htlvedia3p1/4h33WvSNb9v4LTls3RnH2v9lOBqhP8rS4Y1bcfsJeZ5gvwS8AsTZokrPB/S7h4QYipShj62mvRoKEfskF711TCSSNR7r8dL03zls2xFy69Xde+Ie9ZF6Bwz+/pX1hrMRzv1sC/7UD/rOu64Q1N/NhQPN7fVSnD3tKQOEszH84Tqg+N3u5lm24hC2B/ATHYsYsdTaXue6/dqd4uOzLZLrBu7hQvTGSPolPviVf/q1/sn5yl1lAcDAHAfMu6/0v/MH7CplxZBoTR0i6/MHGKh1cLGv5Mpj49GyMe8wp2pr09ZypIq1lOE0KbRwedPF8JStJjINlBX3IXHrBwSWA1j28zHi6ejtXV7qGvO9/yY0VLwC/Fqc7lQAehdHdcMvQAM9MueAK2WQi/pmEPcZ2fJIeygFAeTw5DSq88LcKvCvw98xihgFcAAIwd0fP4jtxaTI5reU6JkGOcAU1M7erAmVi03V23Fzv3bcfOs4vAb4Lq5GRTz+pCw4unC6sSW3NRpk4mzkbCQz4BEmSq7ViJ+GKgXv+fBnIRD9CAY9woRdTP6c3YOE+D4Q2idYWMNYgN9KeoSS3N229tKvrO9vwM3b7vdAQWzr9cHL+Q9qD/JtD8fLYRJWE1eX0BZH0/ulTBp3lanG2+QGnvtc3CEXodg6xuUToBzkRmnPpySkWF7tBd3eh3hujbYBOjy2F1zX7aklNHgbEkM02yb7ncz9RZ2jyu/uzIW9ksxJdRsC61tI107vAEcCe1R/CixQb4hLQsLAOWFPe+y519ulJX2SR9YdvFnWXWT55/pQoLaWrr/PEf2d4EUUKsMfu10k8CZcmwZKAQxFtqsgDzuc/gn7XIEbi94bItJMy3r3qsAk9pzq8RpFS8AsgaU0OCCo8VSQYqLnFg90h9p8ZcC3Bczd+UKOy27EQz/QP3H5dQJpxpYrjwQyllgXvYu3RSlC225B+RBwE5reelYveFW2Yecu8T4FFmlraDXIh1s4H4GAAOrwBkN64ft50ibAFaLfhPhotqO8Twm93xvhE/VhN4Il174IFP0Tve/pxUg+Bxub50E99uiziz6/a31hB8xI83pKBNAHvm1UqBLugBGXWGypQ+Z6K8RiVV8XVU/Ebsl9EEOjENjCLm/4MbwLfIPouOG1TP/J78Cso/J421K2/TA8ju61ro6M0eFAgYLV+Y3KLDbGmndptEGYYUBCcnZKzk3Zq1vfJQwTwlA7OBAand0VkqYFPaUQG/N+pqKg7bO5hlmVUIYAEKtoRrN/+D9Gu+GRsLgr5D6jYM+glJ1zo+lk8QIXCFA2P3welRK2zUNL7e2wx4ctlXGxJnKIalZ3ZI+SpUbtJXO46vQATf2DL9INfTTld8r7XKxcMCF+i4TasjByYZkav4+eMS7hzsOKH78wIte0SUAPIhYHmn7GcdbgcXB5ZKiD0bU2LAczbeht05SAbe8kjwcU/5My7Xhra3I21B+uVZwdf2CX1rrMLzZavp3/hJNWAqz5T6xvJStI3rwpiVLuHpMANbsRaeZ0ETlwEe7rUpbQuzvle2SpOeNNh5wzvw/USmpfyCr8IUIa01PqTpju7tp+onbZ5KG+ALiOPt3DlwgCNJXNb9HgmdmiS54SutWjrdWh6R3JVRFAvPItvxiauoc9+aHFOjhKvtE7VYYq4zDckZRvWItw3CdH77Am8b/CIWG9pS7lbWA5fSIyb6R8HyQigKdYQEkoy8IOq2DlhFZP5sRTYTXmSlrj3uWssSjdeFwJVi6bucYTRfRfb46zeN7TzcQn2pG9yvYP5bUjTmHi6hvrqiazdvAXqr5OLpiwbLDECkpNmtFxG1MRqY8FxdCLn6//q3egOexSOIOiPPKJuXxoUhiVd2PtwqTDYORLgHeaOKLzVp0/UfVpNJv2rCnFRgfy2WPwLL83RjWXFu8BrDGdSzHsAIFxy1GrT6SuEjxHWzudq221FfH4zu8qzQMIAbr0C0YxUx68Uw0YCLXv+VYM1gSoRoHiajnrE6oTBRhEbQ/di7iEWXQGhgamxRWBxcpcxQYKW1318hQeV53Oidpp6ZKme1jEPr300TjAFChp9Mszp0cRekUGRLdbxRoRaicJpNuTExMHVCaL87NuJMOhiv6vmC+JN1OZ90p59G1xkhjviDtDV6mJFzZLsRaTYJFnHAVwmdBSQXC9gy96mLpZ1K07e8oEMEyTPR3CYEnceEm/AfS1BRliXXVHxIewzHIfwZKsivr9PUI4YQOp2FColCsA7eYff5M53PGM+pLPSpEs73LktaHB70US3TgWOG7PEej3pvpVlZ0bxSFEYv2B1u5oaj2tNF5hDb2yvkK0p3kCKlr8FymopGS5p6jeQjcSQPjTCm+f6AOb7pdkRtnLXBIoL5t8tr+2Y1FIcq/4Udm9DgfeJ6DP85f5+Rcdlsdrdfg1wE+tb8fPUDNiChElEtBaRtRA3PnQ7p0bBsd/skRSCY92OILOUDRqPG4/wim5LlfJGW/15ZDX1e6FB2cDq+WLNpmG4u+nJFQm6dFlBgjoYbGYEPAnwoAcyk31oOcazYGWeiekXyU7WAuhPmJ8279xkYqdaKtR5SDMx/hd7vDk0tr5IYjs1+BVOVGsbUPtV2ExMbClRQcCqon64MNtyQBLYIJGyAdxpUMHmR3Zqy4FFqrM+1fd6a7nxeYEMFelZXx7D6tvUjzo4sZ+LkNS+e07263/lcE0Znv6Yz743+1bTPnzn6Jc0gl42OwcMgBAupc4YnnXw+bip+aQKDJ5Q578NDekIgiT6EiOYnRd/PVEeUc5QfYgrFNoOlHV4Gi/PVX7+gHGaN5Mz6hV44iqPgiwFX7ESm/ohJch8CkmaNxesLaPTz1zFIvbfhwYvzJjof/+8KNqqSS7+4YHND14R8Yy9gvXu0asdY146zbjRQAKLPXTAOxJsrAXFlZeO44qNwkteBKYwxtCfhiGC1g7jkaIdSu+kpZ7tXlgeuGA9nnN1lkdIuozM6X0LW3Qja9hlZvuubE152nIOsmL6F4kQWHuzkMlnZ95zp55ewD+iPbTWKngN5FfSAT28RCpTeneMnnl0x6LAFJxbjDSOGRYL50/b9/AuQ3WGmipYYCP6MSblQoQJOiU68n7visOfXd+P/33MjZqNFvqkgAUcIobDo2584MXT5QBpr8Oe4EjxjVS3sYQAoeg6dgqukz88QmIR7Q4BDZY/rnJluGn7fMkKZoJa+/NFWLVZXnRKy2BXpsT861CISBb4Lm7BDTjo9vKVVzE8pQOlYG37tNKVLQw4dbrdOnvXqmj8c+2fn7wRIJaEjLJrPuvwYAFrDDAeE06SRs0/P27k+bUfgTHrfaQ/JsBJ8J35mlQsgB0+0cJKk1ViNSxt2WMnY/V+khkgO9M/BNoXgwkCIJPO2Snn+GufMq7K+2NZMUhiSNN9QSIHZeG9HzqjhGPQtk/SxTYOK7WKkIQlV6M1R42ySImoucnTL68V+XjhF0A7rrrh+HK8Mm32EidgpYZzSywbngHcDvYsax9m6OUnkfQAyyJEfO/H0I7o1lPDKAu+Ueyx0bow7I8FccKdUOTCB4C2j+swcBPcnDdapFDBGpEyiPUJZricoBUaXaWEbVYgf7YDNUO30uQCdIECs+PdujcykGzn6AWwVnPW9fRHCnAHS10aCLYAmZJsU8Pg9GCUl1czeLQCHkAJ1e7gMhWRnvjYiTQh/qfCG6Q9s1KQM/ZbRzzn5CHJ/ELhnHdGUitYoZyG1tV1V5X3pxb+OOGFhsg441zyIgFPLRwd7nJTFugniXDxemJw6R/GrJEEr6jx4ibmtV6JOCy2tK+L6jrh/piaROjweh8XusRploRbkhMF475/lH5IFpBCOzuuSJVjT8GiKrft/mRTFUOBFlwLC4+6Uqd4ZtZKAUeUKmZAPP3b0vofiacfJA7FftgNRveYb84m/DtwBoKUa8AiW8jHWFQFjT0cHIJyxbx2KAQOl9K+ccmIoFrkcrK9BeUGqF+rqOcTOeLnxS4lw9jQjhGkwDr4s09GjBthDFYfFw+0VlH86RQWpYBBJlBfsQNyeenGmCF4gSHm14KQErZnrCfPe75M/O6RUQ8xdHiY+YkfOANE8nV8/xWTbYRnLt4HtBkpEqMBHMFqY4G1DhQpugmBsRHYhr/+hvzbncFB4RGbIhsTPojP9BTrsW0QCvhB+8WBbhkEul8MfsfVfgMwZW4thHnOn2xa29nLin7Hj48TfKXydrPcdutAvZWxtBLzxx7jyzlIlzbq97PUQ6JTZeKUuQqFv6pUXrcdxVIYLmVFeZdD1vZw1FZfWN7KEumX8df8KuYDbvu0RdcH3y/HVe08l1OX4z1T5jafXMN2eRjup0U+8hoevFi5leINIqEDdf2yJQPXpvptL8NkJnO+Tk+/2MhnN1g7GonLSunrPERwkRbvY3j5IU76d40jx1gtJe92fQLlQL0gM7O46fO3fOzjsHDI7/4Ds3We/D+Npf7/v39DVgGAAj8E/Qn+E/In9A/YX/C/0T8ifwT9Sf6T8yf2D9xf+L/JPxJ/JP0J/lPyp/UP2l/0v9k/Mn8k/Un+0/On9w/eX/y/xT8KfxT9Kf4T8mf0j9lf8r/VPyp/FP1p/pPzZ/aP3V/6v80/Gn80/Sn+U/Ln9Y/bX/a/3T86fzT9af7T8+f3j99f/r/DPwZ/DP0Z/jPyJ/RP2N/xv9M/Jn8M/Vn+s/Mn9k/c3/m/yz8Wfyz9Gf5z8qf1T9rf9b/bPzZ/LP1Z/vPzp/dP3t/9v8c/Dn8c/Tn+M/Jn9M/Z3/O/1z8ufxz9ef6z82f2z93f+7/PPx5/PP05/nPy5/XP29/3v98/Pn88/Xn+8/PH4CVv/lv93avT6OOdl/fyzMka7qe3Tc1m26w8Lc2/xnAu7Jea7iESbwaTMFuwi7YCneIBB4w13rZ0MrlvtzIXvHgo+wE6uFrh3fL+dd/Ss0Iy/WJ5Dqf+p3F597SqDVq9ObpSdR/xuqDFnZbvi28QWJ4grNFgV/nv06qgYC/B5JMjwxrEYjge7zevJbeBaH54AZ2p7F2MVwKGfYs0Cj+iG/3fAP/Nly9byL+7jqO6Z2pSjDjpqx3Bmu/6GLu3AbcEFf+16AsKp/Pdm4cgh8NvlU6mdHDlVAYTasQUBoqQShwHzXVsU3IF2rd6JzgIwwnSfqOSwJVFfVcOaPaDQRUXZGuIWsjI0PgTBcS8qLfOZh5eX98hNPb49yn/RUNTMhDPPlEMPRo8tiyCsRfTGPW4WPirs8HZIRMKF09cMlFoKPUXMXIDd+Npk6qWWQrfn4hFNq0+gZkh3iL+y/E7EzIpqgEaE3BJWb3cwaKOz65AUA3Dt9TrQlLmpxWqIxROs0hsOMAzMOvX8E77zV+NcMc2tyoX7ols69TWlLST1XVGhRup6BdibbCrnA93SYSpNC1xB71O7/YzS4Z5TTH/td6SCK7TrvVXBhTcS+oJ+CiIdQ8p7LYt3ytI4rvZLLTvgSjwC83rA1XbNhb9KZZtVAUxqldH61azZDPAJ127lhW+wq8tgtrQSq7xBe9NhjO2wOqdgY7LLKrUg+J4waEFW37sl/dPg7g3PW1cOCC6b100y0eT0nERvakBnZv6iN8+6eEIBZaaL/k26fzgwbB/euy1wPS5wyhbtagyefstsAq2nSU4WZQt8nswIIfKoMC5x2X8na+Y8WXqeHGhMSsVs4bvnJwFQshM3f5iUSDkAlgK/lJo8VGzYMQVuyp02LllXkfL4dNt/yKJK0sGqnAMpjQooem49TE9kCsJ3baqX5IMLuWEWJnbMns1caux3kfF5MJuYVMdXTkehWIoGX+7fkiIJTwy1OsJc7QAtw3QAzon49Sq7CVLXaPKS8IPc5iz5ztXlKd+2OhlRH6N20rIWefghd1Ur3R55fFQ9NemaFfRR4jkFV6+qSEHADZL8yEY6Rqs4osJcTWpUzOWTYrc/S8E9LdpuLb7zPtIkVjFaA4ykcDSLc2jyZoYYNMw111EXbdf2Kr8FpkUZ40W5dq843uc/H/mMnmqz2ziCpUot7BwKQUUw0nIJsj1TjNnncj6Sh6w1Tn0aAIKVMTLzF1PrNSH4H13pqEpgZ+slnTy2QoaRH11XlPbrBLyI86SvT51yy74KhYNKGcuQ7GdiJmIJWKbgIm/iGs5U0Hatrp5UaEekXcD3y7R30wv+BmJfhqLzKwzeFAZ6N6srGVUgmVICJK5eKaNWNsArazHScyrbDD5RkL/iw0CWooXQHNd/Zw+TwIdcRhur4zxJiBHZKi4pirz0/FcwvX4R+quIVVlWdBKvEa4E4sSep47OKG+JQlLjcrsnGGZdfnXWhyHT9wNpAwiywQIBB9BqqI/sex0CNvSQhj//DM9jyLytm/q9Vn0DUTsfCPihrV233GYxd9Xpoc00sRCUrUS6U3VJDHn6VFEjo3X50f8vQWeKOF6OMAop4sRW2/bU3ZUYF0+LlPDKmAavnl/k0iM8VjrABDf85ir9klpMteVdzV21Q98CDJeinr3wHtLKzBp/Mi3zIThV3ZW0bR8kMZcRMqWz+DmqwRrR0hygaEyY0sf6XMu87wjBu+QjS0GmxGv/OknHXseUtg4LmujqlGY3dec7KXfEdj9FvdfziWA8lVpbHoLFu9iIs4xYViTqvQmVdmsyN0Em3sOxg7DT3yTj3Z+P8ZDoDO0Bc3Htf9TrmxKqshNbfYqlFPmIYH9OzFzOq0cG+ZeD3A8YIax+wPBErSBGs4P4Ggg3R1jl+GLc6JKQ5aJ7ml14IVjJby4hCyaj6988B9UT5Bz+XlZsLICSLYa2oInBse4iSIzRB4UOxc++lk9DCaANwEw8FIC9KoMU4oK06Z3OXqKMjCk4nNW5HIGYzQkfXRZ3HUlgPi7+F3Z9WzjX8r34cfQgQEtJRIpMGllqpUFobGobwMV9whE3jdPej23gy/SdNyIgavsgEYVveSx01zyPESt1lg+1DRyLYSMObYcDYKCpiVmmMAX98MLeYB3eVemHvQX8I9U8O9lYtOkXzrbsp/D6emo4B6eOVeFbLdp0E0YzuxnVag3C/khNRNnv8j1r3QVWihyiPnnEGDS4dJr0q2AOdMQPCw7jVorhmQmnG+XJvh/H10DN0BTngRgr7o7H71RqzIntWVGpb/Z8AtxPOSsdlqUjuo/KR6iq/Fxe/35BQbgdyq0NSMX6DZkdpwCwAM4FOOLSkIuuybxYsquOLkd50GXlpBSPnpD85yLAxyaALZNS7UataF3tZGPLtFq0H5LLda9tiHq0zxONS47bRNr1l7OMcA5S887AAQaTwbz3//b+Iey3wUTdAXgSkmrHsJ8MgDEdDjlmLtuje/phBmhTqg/b+G6pF+nar4D6cX48aepT0D8xSegbOD96KiLyDUIf6k5PLmf/6DJ8iom1sdzyNl9X1ZJnpDijGkuFr8G01Fdi7iVjqGZQLB62XPfYGqjwVpzRSOkt30CTzb0a7kEKiDOWh40PtbOUoZWvHQh/9cBr5RkfcWstJUDBD7VXsjWHttUHZjTUb6dsoGOFRvXRgY+eg5AEvj1BHpAggVsD8lPo9xF2sds9oxGJegmimcTfnYGf97s2Qs1B2z19PI6F6tMyyQSlL6ZMJUfw+yAJeQ78oT45qlvxDlW6XmTDwgGftHY5Aexzwdt4TiqOJlguSwwS3hO7YmeuImzZNcr5laL7J20I3siG4YwCrf5N8Bo6v9wi75yAeyUZuNA0dUY2NjMx7CU5uC15Ef0ctCB9ZIxJ2LMGl9up4Dx4GQVN8ZBFGmSdhv5hA6H4zFwCY6ByJruuQ+gcbNVN6SkyDk5oEnrQZyIeA4M36NlOJGmFfaubhDh9Cl+PNyxpWmomaQTd9aAHlPp0owsBi3BePHAb0kN/u8WlNPetCwtIDRfRJ/PHskDfb5vppCRLA8AjJieLjMpC7Wo5Md3BHm0EhLP6BU0nOWF0U5muBTYZpR2vPp3gAkMElGJpARWSyamIs3zwebdQNhGwNiycI2Q/SIojqVLoF3eW7QiLqE4Xy+TMANa48amQMPWsMxLbjfFDrcu+byGfmZ1U+ZaOw/upFi3CokAgtTZqUfX8guOdwBvQGzxK36PAPDzBBiMv+DDKWzKP7oF85V21iRcwbk45zRQVXfkucuOrU27LfC/E6KTz0pXa83Mhgct5z2GB+nAiQSMGfptILlaWyJWPpmeyuTd6WbHiuQPi1EeqPBJPcsxWtqhqA9HaP6ZG0pWB9pXH9J3iPJLkprdald1D6fnEsZ9zkbXDGi1ImJT9/O9AWDi7IUoE/tEi9w11b2gnp36O41ZqGFvFbhHWnPQOOCDXHM0cl/HH1iSmi2kM6PWCzkOuYfSrz1AyQPvo+T6oUVxl+00kcmGJQGbieCVNcYk/DazMT+BrzzXuVtz0AN2rfTUwQ8wK68vjvXYDP18SGCLJnYPKueyWbPslcVPNLQuSbAre89wOLvYBzNI57Ik9z+35feGC1sedevaXqiLaXBhcFJ75KG0PKSDFF3FVh+z+B6CIk8cdRkopTpP0MB8tYByQlZeCpIDO3dTxfIevRV3LddyJKndejompxmKXiHdtgkl859LMrKwK4qntqBa9GkSL7TtVjJbfRg7D6pa/yCvdnM+s5/Uv80rgyAZMSrfBmXsoKfSDYgFgG4DXhSE8KHBjgoXdvcEUC8NM0PFzIXrIbjEmg3PMBFIG7/gyI2Hf7PxPAJvFDfTgyQWLKr9NlPmwVueL1tI0nnwDVBtHGmysmL/WB2RptSvrK0+Z8N5fPrY4zb2KzZkIftcFCZ9vHEmROMNFoNfYPhY7VKMvFUOI9GIl5Xn93ZFcFGof2OIkgoThrUuei2WTsl4bh0QqNOglmRlpn2UaF6YjvPmmJoEBqX1U3Bu7BMQ5LphlmJfRrGq882O/0OjaVoF7TEfVQZmaAJLHTqz2RbXdzCoD96tDBacwU=
*/