// Boost.Geometry Index
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_INDEXABLE_HPP

#include <boost/mpl/assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/index/detail/is_indexable.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
struct remove_cr
    : boost::remove_const
        <
            typename boost::remove_reference<T>::type
        >
{};

template <typename From, typename To>
struct is_referencable
    : boost::is_same
        <
            typename remove_cr<From>::type,
            typename remove_cr<To>::type
        >
{};

template <typename Indexable, typename V>
inline Indexable const& indexable_prevent_any_type(V const& )
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        UNEXPECTED_TYPE,
        (V)
    );
    return Indexable();
}

/*!
\brief The function object extracting Indexable from Value.

It translates Value object to Indexable object. The default version handles Values which are Indexables.
This template is also specialized for std::pair<Indexable, T2>, boost::tuple<Indexable, ...>
and std::tuple<Indexable, ...>.

\tparam Value       The Value type which may be translated directly to the Indexable.
\tparam IsIndexable If true, the const reference to Value is returned.
*/
template <typename Value, bool IsIndexable = is_indexable<Value>::value>
struct indexable
{
    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Value>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Value)
    );

    /*! \brief The type of result returned by function object. */
    typedef Value const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(Value const& v) const
    {
        return v;
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Value>(v);
    }
};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from std::pair<Indexable, T2>.

\tparam Indexable       The Indexable type.
\tparam Second          The second type.
*/
template <typename Indexable, typename Second>
struct indexable<std::pair<Indexable, Second>, false>
{
    typedef std::pair<Indexable, Second> value_type;

    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Indexable>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Indexable)
    );

    /*! \brief The type of result returned by function object. */
    typedef Indexable const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(value_type const& v) const
    {
        return v.first;
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename S>
    inline result_type operator()(std::pair<I, S> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (std::pair<I, S>)
        );
        return v.first;
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Indexable>(v);
    }
};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from boost::tuple<Indexable, ...>
  or boost::tuples::cons<Indexable, ...>.

\tparam Value       The Value type.
\tparam Indexable   The Indexable type.
*/
template <typename Value, typename Indexable>
struct indexable_boost_tuple
{
    typedef Value value_type;

    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Indexable>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Indexable)
        );

    /*! \brief The type of result returned by function object. */
    typedef Indexable const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(value_type const& v) const
    {
        return boost::get<0>(v);
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename U1, typename U2, typename U3, typename U4,
              typename U5, typename U6, typename U7, typename U8, typename U9>
    inline result_type operator()(boost::tuple<I, U1, U2, U3, U4, U5, U6, U7, U8, U9> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (boost::tuple<I, U1, U2, U3, U4, U5, U6, U7, U8, U9>)
        );
        return boost::get<0>(v);
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename T>
    inline result_type operator()(boost::tuples::cons<I, T> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (boost::tuples::cons<I, T>)
        );
        return boost::get<0>(v);
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Indexable>(v);
    }
};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from boost::tuple<Indexable, ...>.

\tparam Indexable   The Indexable type.
*/
template <typename Indexable, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8, typename T9>
struct indexable<boost::tuple<Indexable, T1, T2, T3, T4, T5, T6, T7, T8, T9>, false>
    : indexable_boost_tuple
        <
            boost::tuple<Indexable, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
            Indexable
        >
{};

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from boost::tuples::cons<Indexable, ...>.

\tparam Indexable   The Indexable type.
*/
template <typename Indexable, typename Tail>
struct indexable<boost::tuples::cons<Indexable, Tail>, false>
    : indexable_boost_tuple
        <
            boost::tuples::cons<Indexable, Tail>,
            Indexable
        >
{};

}}}} // namespace boost::geometry::index::detail

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <tuple>

namespace boost { namespace geometry { namespace index { namespace detail {

/*!
\brief The function object extracting Indexable from Value.

This specialization translates from std::tuple<Indexable, Args...>.
It's defined if the compiler supports tuples and variadic templates.

\tparam Indexable   The Indexable type.
*/
template <typename Indexable, typename ...Args>
struct indexable<std::tuple<Indexable, Args...>, false>
{
    typedef std::tuple<Indexable, Args...> value_type;

    BOOST_MPL_ASSERT_MSG(
        (detail::is_indexable<Indexable>::value),
        NOT_VALID_INDEXABLE_TYPE,
        (Indexable)
        );

    /*! \brief The type of result returned by function object. */
    typedef Indexable const& result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    result_type operator()(value_type const& v) const
    {
        return std::get<0>(v);
    }

    /*!
    \brief Return indexable extracted from compatible type different than value_type.

    \param v The value.
    \return The indexable.
    */
    template <typename I, typename ...A>
    inline result_type operator()(std::tuple<I, A...> const& v) const
    {
        BOOST_MPL_ASSERT_MSG(
            (is_referencable<I, result_type>::value),
            UNEXPECTED_TYPE,
            (std::tuple<I, A...>)
        );
        return std::get<0>(v);
    }

    /*!
    \brief Prevent reference to temporary for types convertible to Value.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return indexable_prevent_any_type<Indexable>(v);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

namespace boost { namespace geometry { namespace index {

/*!
\brief The function object extracting Indexable from Value.

It translates Value object to Indexable object. By default, it can handle Values which are Indexables,
std::pair<Indexable, T2>, boost::tuple<Indexable, ...> and std::tuple<Indexable, ...> if STD tuples
and variadic templates are supported.

\tparam Value       The Value type which may be translated directly to the Indexable.
*/
template <typename Value>
struct indexable
    : detail::indexable<Value>
{
    /*! \brief The type of result returned by function object. It should be const Indexable reference. */
    typedef typename detail::indexable<Value>::result_type result_type;

    /*!
    \brief Return indexable extracted from the value.
    
    \param v The value.
    \return The indexable.
    */
    inline result_type operator()(Value const& v) const
    {
        return detail::indexable<Value>::operator()(v);
    }

    /*!
    \brief Return indexable extracted from the value. Overload for types
           compatible with Value but different yet holding referencable
           Indexable, e.g. tuple containing a reference.

    \param v The value.
    \return The indexable.
    */
    template <typename V>
    inline result_type operator()(V const& v) const
    {
        return detail::indexable<Value>::operator()(v);
    }
};

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_INDEXABLE_HPP

/* indexable.hpp
YldETEMoXcLQsPESPxnsx6os8sE/4tLeE9d/b8fAiWGOvLcPk4etfAo6P16H9mMd4+0JFihVvD3zbcX1cWWhHEfomQPBmSDDuNLHud3JeA7rkvRpbo/xxXpX6YVcg1iP/Qfr359gepnP1AZgm9YV8xoup0NBWilv26QNOmoMp86awb+TMrxCeSZ4MhkDfI3BcQo6RUGlcCDFlwxyqTQMbqkrbmSYGsFSp+ipMGUlxPVFEjDkeqrmVR3+At6R3TmDcXgFbvbhjdR1F3V92zzSU/aid7E/tkZI253SLRfa2LYbjOI7fKqGxWmtlCFSxh3C3ybfh39KKK3R2JdUabq31G3CffV2mgq/9jM6xFOTvDaxFgaHBEyvyegw03QXUneQFOAhat73SCxrEjdJW7TdDk4Byrf5JQ+xg2PfawJClY18uyadJ2ag5YLOE5eSmDSd6sXrqLqsp67l1HUzdd1CXbdS1x1UT1eq8KKZnV7rSIZTC2h8cX3LfRjg8BbI++S528HkMTIBUvDbb4g7e+vs5bO/n22wO6591PKQbGpJdXEEjFAXQcuvrLO5PaWAt5CT200KuAsYkWJqocJi0guYHPzG3O4YXLna7hBmt9wABGXLDapUDlAUsOinG6xzOK9xeAPFsQGLJKLpVvwlaP4YF07ZeC456ZH4mGH5n0ZjBXc6jPtnjR2vMujyAN/VEr8J8GMwvg/G3/AcvqxBQU94oUOb85yHPELIQ05qg6e+OHcqzp3SOTddXtgFSj2LKzm3nC9aFH0HMl96BJnX4cwjqMwYv7ShE9IujHQEIzG6qo/hh3b6B3BRMk4Hy5bPEZxbYzqTnopJ8xOA9GfPMOkyWcOt1t/NSFvJSVsAyQOQivWQoxUCI3EOP5xD84w+k+r/p7/esxDySEYoFGAawCyAQoC3AbYAuEF6M9x/wuFEhPYDnAC4BnAX4AkAPwkhIYAvQBjAEcBVQ75oAD8Al2S6rETAnQTgATACYAAAE6BpBp1ekGjCm4lQDsAKgHKACwBPANhApzeAAp69AEYADALgA7RBuacBDgPsBFgG5Q4A3PGQdg3C60xnemUlmc5kg/u7Sc/LY4Gf+de5HX/m3wTj17ULACpiAYLBjqpE7vhHs+AHfol8Ppwf5u7lYRlmmH7law7z+1qH12y4HXa8daX8UK8emuOPM1//IPznFsN4wYQ9k0+Ouujm+cvX925XOO5hR+74otds7c/uA/8kb3onpk4P113b9sVPH2Zk/vb79qS1TFH4x6uOejSXfbT3mParAffOOMm+emcra/KafiLipzHutz8+EPLVYmPw0KgY59e+u/bgSVDqhC/Ff0wZM7g5Y++XjC+8G1fJDjTHTP+pW9B4/6rovjsv9A6q8MhlcSZuWmLYOPWIm39o5Dfuz35xyHp1x6BM7+oeZSODDsrmftDj3Ie7Kybn/rTgV9uwXTu3XLi3K/yUywix0P7pxxEH7E8252fxx47+LrtyQ968CWWzij/KZNpG221ZsC1hjF3kt9rUX4R9crw0ac3vHu3lELQi/dCffUPmfr469rf6wVcCgz7IrSe/uS1NDHb2/vnMLptJByKFFeTOIxeStal5lvJbkGEdJlSI/4qp/bD3iL3KfIgj+Ijv4tcBlm37BoOPD7Vvv9t2m/p0418d92vPnJ/g33OY73xkDfhVeIOsgqMZ/WzSR8qDfet/2D4lhDqTPY86s11JfZOf/iI//sOnlKdQ39inT4AQtp/pYP7g7PN5wqZa82+Gtviu44XO1uEdTvR9F+DrTWlZ8Lx2EOIXjkF8vjtUxRPyARQC7ABwgfSgwV3T7wxX4hC/DnCz4K5/BWgAlOP7KMRvBFAMgbJGQNpwKGckzU8QxBNCxI+HPAh4aHJDfC48K4YCrg/wJAF+AHIAFBAuhPtagEaAOgA9tCt/GJTjC/nBcRYC3OLYOnG9+RNWxZ9MLjriMmxT3KG2T5dyJ78bmrGLK6l6A8tyAiXlEKRFudRJDdnUOQcZ0B5p0A5K6qwEui1iqPPs05AvtMhwiMlA9qgH1R5XoD343nTd15qeg7wt9arOdAxIo+luCDxFjV53AsP+BVuNPR0C/Ey8aIPPXU3yXqT4y2mg7Jso1fBNvVZ9hO1NqG9CjFyZIPFMUGYnz56ooW4ZmriM/InZeZrkrKy03CSRaKzHWCJpfG5ydoo6YXxGdnJuRlpeQlxGttg9wXRylFAWGZsQIY9QeNBnquWaznC1PiwF8UNVHfXG5cdAOMEcV9iRZnmGpWUe/OcKeKs70VkP4c2mONcX0FndiU4o4J23iMP2+iaEmyxoYZyuzhQ934lWKuAJ46xpERD2wzoaT8envoCWOR/HLCbAK4yzpm8ZxzB9cmEt7j8AbqBTGoDNpvS2wg56luUcAz4wHVYXPHQubz3gNcVZyxhBfo6pLutfIOOmTnT0gOcTb00nLL5DJvoX0LHMQ/UhXP9OdNZCeJ0p7soL6BR2ooNlc6wTnQYIN8Zbyw51ITtLOm4wXvCnWre3cGpHW5hxumpvy3yUWAEvYao1T1kWdHB6VzwldKJTCnibO/G0C8J6AM40Or70BTxt7kRrM+A1deIJTeugs/kFPDV1ogNTXFQB02wDgJMcoRSAUoCfATgTXnyurOV5ryVgq7dLabovOi/Wzs86vfO5tJcC6fRP4f49wIvOlR0/3pqO5bmyJ0MQ/1oIvUi2Q4b45rNy2dOf9wHNMsO4jRa4xEtw+fIO3ISX4CrkJv0w5cHtXfqSPIUW9Pe/BHeHiX6FnNaZKtP9jJy2IZdNtPCnVgwvoQUDaXu5Hgkvxo2fYfFtGvDvsxQI5VvErYO41RB3J6EjLjGJ/sbMFQu8fIhrgribFnFbIK4V4got4u5C3NuK/8x1XjTXEeGzInPTkjVpyuS5OVlpCJwvc0xE2tx5uYvGa9PT8XGkJRCv1CTnarQ5aDl+Vms1qfMWZmOf15yj/ah58MNHW9BJzUiOWZSThpIgzuqsUQgrspI1Y0PDw/G53+28ZGTPicvN0KTlynPnzY2NDoeU6LTkVCqOOtRyOzJhps1NzlHPy8Wnd0ajkKx5eaYjdNEzlsl1aUdB6DtTLvpEVJix4RNYqbMBEXrMjkvO0Mjn5ULhs7PS6PMEodZ0DgoJymgxY0VoszQZOWY8qC+PHZ2W105tFWuKVpOj1VAnuCpBKtmzIbf1+adi1sK8HEjRpMdZnTyahULmxWZntJ+0ilAgxHScvCrLhzloVpoJvfPpwpYnD3c+abjzOavWZwx3dQbw//S5w12fFvzi833/a2cS//eePvz/37nC11BoRl7yrCxTxwjPmJWbnLsoBBo+73/9zOGuT8M+g88KTslZ1JUdN6/HXEunx5jZJmgAu6cBDvgQ3wQjkgIm50HDwF4NgnEagD8GZDsYoR0YhkC6N8zQnMDvBCgEyAEod4YwgBB/pg2AAFwhQFMv8EFcIA/QKIdwI+Qtx/mcTZ90g7g6uDfij6VBWTtw/FAAZ/rZEhQxYJMB2qAWYXBfC6CH5y0ATQA3oxH+jTGCuTSCOTPiu9Pfn4M5NAoCPho9Ac8NaOHycTyUK8RxgN/UG/IAwNwawfwZwVwaNUKYj59x/GhIB/wgSIe5NdoBzzmQV4F/fzIS6EH9goAHBdAqxOV7wB3wFK5QP3guN8XBXBzBHB7BXBzVAR9BfaA8AJjzo0Z8thjQhLk/Kgf6O+C5HMptAiiE53vQPj2gwVwBlADzANYCHAS4AWAEcFYjNAdgHcBBgAcAgzOAD4DFAOsAvgE4A2AAYGTCGAjgBRADMBfgLYADABcA7gH0AksjBogHeA1gA8B5gJ5gDWQAswF0APsBHgLYz0VoFEAQQCrA6wB7AE4D/ALAhLHQDWA6QC0Adx6EAWIBXgPYDfAUYFgOjAQA8wE+BKgC+ANg0HyoD0ApwF4AO+isoQDZAJsBzgE8AxgJNiEGYAnAPoCbACzof0J8XjbADIA1ANsBagH+ALDTgiwAkgF2AlwAeALQbwH4JADTARYCfALQANBjIUJTFtJeGxNGZjayQbaoG8w5u6MeyA5xkT3qiXig6r1Qb9QHCZAD6ov6IUfUHw1AA5ETKPogNBh8gyGg9sOQCxqORoBCuaJR6BXwDdzAzxiLxiECPBB3JEYeoCBeyBv5IAnyRVLkh/xRAIx7QSgYjUchKBTJkByczDA0EU1CkxF4BCgSTQG3MIo6kzUGxSIVioMp7FSYxkxHCWgGSgR/YyZKRrNQCvp/KbzgKPAtAIBDS+w9CVRT17YRKKIIDiBOoBHFEfDce09yM4dAQKIIKAhUVIwhQgQSTMKktiIq1YpV0VqhtqKiVR5aB2pt60ArtNqHU5+ts8/61FL1WbVYrVL7zr03gYxg13p//fXX+jcrN7lnD+fsffbeZ8iBTe3nzGFZbWBQY55UCsJR8EIDGTPNoYeMsOhoNDYiUIQlPgOShSeBMKfQeNlUxRQ0FuhRiVxpVIZZobbPasLCFAg7xQnMYT22CB1UxczkInTafLXeCUOHKCnWUCoaO6dth9q3hCox6YUuMOsoUa3KTMjRGDPNjTVjOcIwV4zhr4icYoUlozPOG/4S505orCtwJhnDfao9944ITKzR/FeXjWaguUqVveodQNvIOugxB1CaDHNg+AzAxrCn2gAsLdEKZmdUDqBMI9oBHXWqPZYzFVpgWivJCuCwBdBeDTIZUl67BqG9ozvGsHFRB0iO3M4pWlt/2WJ04ggUOjI+SwuHr2bhHVF2YL0y2VSGbKoFmZ2x2knRmZxppI3iueEdSR7WMYnTQGRBZtmB3PA2iF2v2cEYEczFHbXSFqeDDrFFdSZBG561yi2K7Ropm63TG8Ps/XwC5RKy9HRZXrpGx1A5wEqZGI+8xwIzUWehOYdBwsw4SZOu1lGCJOpMDufEK1KoMQRxorYOzK6JiozKjHBF4iRZvCI2Ki46UiaPnEKVR8bLkmzED7OokF5LOBKkA440PbXwpRbDNjFCxiwrpbTwCi1a5sfoDMYwh1GARgwvMqoNNDZTfbqDxqRNpDCpNVekXq/TU19mK1VZYZ1EyJQJVEtNykvU2fScQ9VS3SeTMQo2odLqiszJNZq2e+gVXZh9aIym2hiFlqfUPgQtZQf9jfA0hky62Rpthq3ICissancHITE9ZV9vSjsmXUuHeGhlSatBlq/UZFOrWkfajrXEZLQgz2P+aX2Y/WiVNiFtYhhDYFrKWtDRWI5oUqwoKBGdtdu6M6zpaBP+SzV1rKJ4m643P1v5mklYmokhUSfX63LDlQZ1epyWwUgwKo12ejUbCCKkhG3beHMosLmrrCWzYcf4taW4JioLpXTYbSZ0WiOv0J5oJeOmCUa9Wpnj2KNpERValV6dg3Qdma3MRXqh2+OgBSkMsnnrzlHMjQ9PS1Yo6CVHO2KnAZWhUkxNGz9VIWf6a5IsJS1qimxSZEJaYlxa+NSoKBTLbCoE0eEIMYreKHXmkfHKPIPa2ehgCXQU6trgjhTBuIAuh1E8TZqoo3Z+HHS9icCgdhRYZe3wvBynbbWCOmpsO4Kj1ia8QhxJSYsNc4Zqy7MNlQ7wMRqDUa1FbDqZzqVYrKasCXGC7nYqbYsym1ItKnMyUjE4JvGd4VCb+85U2QZ0qCgKSDFvD/OOxoMEoy7XGf9EnVGZ/QpjABks5tMPzdN+emLnHXaDW3tMbDdAZt5i2ySZqUntFJaTFVsr7WQKQTOxm4R02tz/tevsFOa3u1CpLMliI51FnePdN+CY/E/TZYlnM/Oy4kGdibMC2tRhY1G2MEttO6azmNvY8lZ0ytuyH6xoO92/sKurAyd2htvB3N9O1radchuYwgb237rcTCcMTGfaivszqUCKreFd6P32eAflLsx5drvybm4WhTbl1H93qUK3eFcW65Yp58jDdSzWtC7tz/GukPofMKwEVhq6R9J7fwpWHCsWPSvQPQp9p64jbr+8pPi6sTxZ/bu4tn1KLep1sZF5jwtFkcAysvSm03hR6JP6hU2BnuawdAjnbRoHsCB68+nP2SwqdVEMyw+Vm8/uKRF+EWqNkj4xRl2J6FOFNJKASjSohkzTST89wqbuSlSmQd+0tHT9EC9z3XL0NiBaqk25FlgsxIs6E5hB82OzJqF+gOiz/UShGtGwEX0MerHonww8Lfgm0XCDBT8MvUIRj1AWgd446m8mKVM4qzeiU9Bn4yga5iRiu3STEE+mduu6TVm6aB6VLCHiEYPKM2hqSvZcpCM9fbYxk0XlnLEvY7N2oTdu2iUOMX0jUFlH+gxF32V0zWwLXgb6SU2fw9Sz8tE9HWFS1wRavjgTrsYkn1lP2r8kZyirK+IVj0opaB7CMlrZgWWfUZeA7hNrfNuecdYvctpzkhA/vQNLZbGG01aeSFuXFvHLtrIyFvK5vW4ipcGgzpmdXcQuzMnWGsSBeXqtwKDKRFNlQ0hbUrUQlS5HoDTkhOZjgewcpVYzR20wJqn1BhS/xIFYKAiUeHVns0VGfZ7BqEAjxityIxg6RGlQq/Ko9KmmZ1SiV8/LQ7Wo0+P1mnw0RcxQG9qAluDIQkRKBdIYdb46m51N3cWBSoNCm6/LUusD2XkamYr61VEcOEeZbVAHSkTjnBC3Vz7Oee2icVZtFY1rExo9i8aZ9SmhllVyuSJ2fEqK6cv/hWcq4BdSsRH4guFADqYDLZgPfgdJ2GbsY+wploVfwD2IECKGaOKf528UXBMYRUtF60VbRXdFUBwjnimeKy4RrxdXi8+L74tfirtLhksEkmrJYclpye+SPtLhUihNlGZL35S+Ld0qrZM2SG9JW6XMIHMCfXiDgWAayAA5wAjSsYVYBfY5loTPwd/CN+NH8Zv4A9yfCCKiiCQin1hGlBEVxKfEbcId9oT+MAomQx0sgm/CtfAHeAf+Ad04vpxlnG2cGs4PXHeyL6kgp5PfkE/I13gLeZ/zLvN8+CP4n/Mb+Kf5v/FdBKMFmGCGQC1wFfYUyoRJwhzhUuH3wmuiQeKp4hXijeId4lESKImR5ElWScoluyX7kUz3JB7SIGmkNEu6UVovbZZSrtmM5OgOwkEy0t5CsAkcBddR2BqIAUyBReIqPBMvQfIcxL/DH+FexGgiEsmxlthDHCDOEA+I7jAQCqAalnG3cP3JIDKcTCLV5AryXXIreYdsIT15obxK3kHeEd4pnq9gsiBVMEswShgq5AqlwjjhTKFaeFw4QiQQFYveFq1GPVMjOii6ILoteix6KgoQjxCT4jhxulgj1onfEpchqXaK94g/ETeJvxPfQf3lJ/GXjJPESWZJsiQGyfuSrZKPJLWSA5J6yTnJA8kLiY90jnSd9Ar1wxzrMJLTBwwAQ0AQGAswwANSEAUmgUSQCmaDuUCPLKcUrAbrQSWoBrvBIdAAToJLSBu3wF2kka5YL2woJsFWYmuQde3GDmFHsXPYHewR1hUfgo9GvZ6Fl+Fr8WhiEpFGvIF09B7xknCD3WEvOBSGQBlMh/PgG3AZXAUr4FfwW9TrV+FN2AwfwBb4HO7g1HK+5Tzn+HF53DxuJfck93vuE+5Ikpqw1FIZ2LAm/Cx+Eb+K38Bv4c34ffwhXk3sJGqJvUQdcYg4TNQTDcQJook4S5wnLhJXiRvELaKZuE88JFqIZ0QrwYJu0AP2QO3xhf2RBbLhcDgKBkMAIeRBEQyDchgNY2A8TIQpcDqchVqcCbNhLjTCQrgQFsOlcDksg2vgergRboJVsBruhLVwL6yDh+BhWA8b4AkIOTyOiBPGkXOikUR7OSJuGDeem8idzjVyl3KXczdyN3GruYe5Tdyz3BvcW9xm7kOuB9mf9CeDSUBCUkQmkulkJllILiTLyDXkenIjuYmsJg+T9eRFspm8T7aSLJ4Hj80DPMiT86J58bxMXiHykTLeGt5G3l5ePa+Bd553kXeD94znwe/B9+ez+cP5wXw5P5Gfws/kZ/ON/DL+Jn4Vfy+/jn+IX8+/yG/m3+e38lkCDwFbYBQUCjYKDgnqBQ2CG4JWAUvoIfQVQmGYcJYwW1gmXC+sEtYLm4T3hS3CVqGbqIeov4gnkouYnHF07ikwCkWjdFCM/KkeXAWtIBhLwZZj1dj/52z7b150bkEXFxYoGaBsz7jpUlUyYAoqinXp0oVOE2pOCAsyLRPAVk0DKYCwKOkJgly7sKrYWwcX+7NE9CsOTZgNaApi/vMWCfUCQy14uvku3d+rqY/XigOtxgO/Zo0q+hS4p4ZUlfgOACWuD9A7mUnm3evNdfdeLPw69vW7EysLzru3Cm1Tei9eaZHSdJoM60vnJXbz8OmRTA3tei07QpmrxnxBHyapqac8Tz9bqUXDfbYa64m40YlN3RMzlQVGNRYABjH5sX2ZAnYEWnZq5mhUTKLTIXQSZzdXHz8T2CrLKZPlG8MxHMcAfU3r54UDDCcATnD4HP40MNM6/6qpuu4+vglFaMZlVKus8qoCEMpUN7INTFXITjDXaErDbUBVs0PY4/FO83Hvqz2gSJz4nn+f7heDitYGJo/RXT00oiHCkPXVsdD4aS98v8p/J6JLUETdlpuRLc2fLjhubAq8ULee5fJ00r+P1X0qH551Ki1SeE5+OqKPoV/JSk3d2L9XDK7VDxoxad6Qfdi1F5OVLgk7ap4ogl8rjNw+bsXpnyp+ell2M1kq/rr86oRnC4hbRd1fPMxbLtv0Z6Pr5IqaC9mb12neUo9esuyrWb4NJ04KfS/XL344xMt4vTzwb98+fWFcOPLO0wmDFn10/MOQPW/f3XGnZqTfG8qnG+f1PnwzfsvE2zOe3/b+KHhzjZr9j4sbmk8s3B4bLf9zwE1513LPC5lLi2fMLUyPPDUr6s3EL30WNhY9OvnlPFM+7udg8VOLfNxplU+005uajJXnr73xi/TK/Zji0GsAt0iUPQJNkwLbEmV3KfUzJSTWqQy5oUbaFOiUxJSNBfhQ2a89gDv6cEGrSCmTtpsHqDzHeBUoDbVI291OO46xKEuDipDRGbs7z7PdxR2Mop57uw0FQ6qRUWEDQD/GcnpRDGl7CcEB5IVgthm5Fy9muXZ7f3XRL4teBzW/ZH7y/F/dAr6IK3GfQabtmLLZb9Vd//Jucu2TnHspC0Hz75pVwwyefXTjd+3h9342Zt/7ewcef+fe6xtYu0/3mLT/LLbDY/o=
*/