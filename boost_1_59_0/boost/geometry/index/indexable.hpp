// Boost.Geometry Index
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_INDEXABLE_HPP

#include <boost/tuple/tuple.hpp>

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/is_indexable.hpp>

#include <boost/geometry/util/type_traits.hpp>

namespace boost { namespace geometry { namespace index { namespace detail
{

template <typename From, typename To>
struct is_referencable
    : std::is_same
        <
            typename util::remove_cref<From>::type,
            typename util::remove_cref<To>::type
        >
{};

template <typename Indexable, typename V>
inline Indexable const& indexable_prevent_any_type(V const& )
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE("Unexpected type.", V);
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
    BOOST_GEOMETRY_STATIC_ASSERT(
        (detail::is_indexable<Value>::value),
        "Value has to be an Indexable.",
        Value);

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

    BOOST_GEOMETRY_STATIC_ASSERT(
        (detail::is_indexable<Indexable>::value),
        "The first type of std::pair has to be an Indexable.",
        Indexable);

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
        BOOST_GEOMETRY_STATIC_ASSERT(
            (is_referencable<I, result_type>::value),
            "Unexpected type.",
            std::pair<I, S>);
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

    BOOST_GEOMETRY_STATIC_ASSERT(
        (detail::is_indexable<Indexable>::value),
        "The first type of boost::tuple has to be an Indexable.",
        Indexable);

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
        BOOST_GEOMETRY_STATIC_ASSERT(
            (is_referencable<I, result_type>::value),
            "Unexpected type.",
            boost::tuple<I, U1, U2, U3, U4, U5, U6, U7, U8, U9>);
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
        BOOST_GEOMETRY_STATIC_ASSERT(
            (is_referencable<I, result_type>::value),
            "Unexpected type.",
            boost::tuples::cons<I, T>);
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

    BOOST_GEOMETRY_STATIC_ASSERT(
        (detail::is_indexable<Indexable>::value),
        "The first type of std::tuple has to be an Indexable.",
        Indexable);

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
        BOOST_GEOMETRY_STATIC_ASSERT(
            (is_referencable<I, result_type>::value),
            "Unexpected type.",
            std::tuple<I, A...>);
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
v7nv1o3rn930vrwNWkSTjaBHomsWumLPVo2nH14Kyhd0N06HRId+PSmCzmDGShRbIcndp5eF+jD7FMAtr6K36x0TptXcPzcChPVDM2dES/m4KsHXXAV8EdEhEtxQ2CzVPgxVka8pSDnk9iylMPFBSb/y2W2kQruUvl5anENR4YDj393ZH8QduodCGeskpa0/Y5EITdP4KM1pqgFoD9zyj6Ic02Y5QLFYokJAfhVv1eWyhTc/GeF6OlclI6sNzEp+e8lnaH1IoAJI/0+dNeDRXeNT9B++0bBFmcZc+H29IhuvmOPAbhs72qF3w7M0wapzSQu/rYtcXJW8fEzLRZnmXN4VC5rlzXq/jkxg56fG8PpICh5XjT0Yo7SxNB3b5UvStWr2Kc9jGBWYyfWxajYdfC32mVbeLHqTVrPde/rrjUMHWQYFcnugrH2YQ6eu4sDVIlLbxwWSE03S8n0BS9xxH3CV4EMB7t5aE4Rv2dh5u5DHzy5lmyUhrefrUyzBaUIkwqNL+fR2bNiW/s9txiYhzhrBVj/GO1VuzyUm58RgPDUregddIJsm2+t2iERiXA1bI8SJOk0J31gkjT/W4h1bcinRkI0rX/UFY1H0Swecci9CK2jEuXeKW9dPXtKpBx9XMbc+ieXe0eqDG+JptRkM20ItTEH4kTPg+rpRO1dfuZSqHcHz38yr527zp1YvSp1W0szgfSeQgT/O9q/Ap2eFN93DL5n53+EbnlFhV3a5N3iKpux7yQ091T6XrxqtHtP/Tl5UVn4YkKUe9Kwb2sOs4vtLGrKGRvYVSNykkvYzBuuexWQGedWOlu/q9LaTywp7fLbCEfBC9ZE3jSwyrcfi3eMawda07U0iTxEQIHU0Mzkmz+VD1qyRn1csSjW8VZSyDa5q3rwJpJISX2o1vEGxzBBsXcTi7tCa0mtMfZM6Rv0BQcfp0HcloWcXB/AqP9/do29vp/sB2LrblYUam7Xlo9uNRpUi5hoB9QaqWHCY3n7AD1O/J9m8AAKEpau+gGPppprpoHpsN4ZttBvMN9JtN5ptnZt/q9lvs9HS0/TM63jtPxPRdTCsj4iZlJR0o13ANOJxPxaXlvQYRy0lm+M/vMN6hWaaXmFjVv9XhSkQO8I1q84Xuw+/cnIoq/o+SQvHxe/7cq89YxmAsdx38amYiTyFbYm/95wDYoZFSlu1RIpTvgxhIn/TUqfBcKFQamzhE6NMKi2yrTBx5b1s3/XJlrCOKBqR5OA0j20z6Rvcdz9Bdsq6mFOQ/F3OXkxENy0tIiGCpnIEeL/Lkfz+4DQOTJ3+FUkZpmL1dblONRz13PkPulXPwsc7905TACevEwXEVKAy/IfcVsP0BgxQQiUTqZ8gwxS4MAM2D62mXsxrs5gQ9XMViUa49aJl4BCT8jLh3CS2UAUBgOfXm8vpS6rQRTKd7mCEgzHF7SntOuxPJ/OG+dmF2Qn/CZoASdf0aqlXm5JYpT8E87JAj4oru+touZQhvjVMoup0wQrcrP3gS0C9pXGQ8Ij+JbzdSbHq7KZIDVNIhfqiit1tMe6hXcoWVRTPWukEW83zydfY+sIcE/ZKXnI7woahTz/qWlao+rBlg8DaZ2KdKVd5yhO7jdPI/YT5GKgKcCBcaDdY/6xw1hBm9IwHlcJU85pRxhMHAhKvJ6fUy/nF2sFL47ZZlBwMwqcFdFX2sP7JSyVQC1hHLbrJR5TNZKlz1DcAo/o3PB4nG1Tey2ulJrwrVIf11vVJsJXMUS/B3GpBbzA0QQPJ4VwcCv2dZziQ8g2O4IuVO8cqvMPZThVPzYrWTaeqDGFJrl9f7c+VV6//MLXQN6seIm5swSP+cE0cxY91p1BDR6bY4luDdJ/lRHC4GE3SjxcOT2Yx2r3PKvwQgBCW7xx5b2DnZkNN3A45BzxcTX8MQj7kwLyCq0mRXAu7T4CYK+fIgdVXCPC3yl2ei11gxpulaGHknp7TuGOF1vBJWEJL5dVbSOZuyO4DCXbug+Q5tBRE0CnhgDmq4SvaMwKu/hqb67rL3LZKF8+zBrSC7g/I9vJi2fFXx9MdAXLHI+o/6VYzuG4Yh5k5fCRgnXnoOP28MS5beIC8j/pHCz5E3sm0V25gttz3r3PGWry1EtVPrJLruYzO8V1QTtnz6nHkPI2RWNcMCIlXqKWFVVZAOt6W3omOf+HNAu+lxcJ4xsNkLCHSi41v/WUetKXFYShdGnTea6nTyuIdvMaS4gfdPNQ5vYxxuyU2Z/kZ16zxmZKYfg40Ib1GUbd4Cxm2u5TwM+G7LAIsVAsvpYwKbGQlYV01eh2k9a2E6Jir9Gz7XXsD2+Qs+26nt/PSFu3KVbQEsrnUDSUcCYbjKwyc/jHFhkdfIIO7CYUKRizQkgEvgSpZ6exAUQJkTgKE/0oBi8pAFTHlro1Ll7PwlDlskPwvocV1plg4uNAzU+LdWFa+yPGG+saC/kruQTuYuooKjLI2jrugqiadKficfT72octaBzyoClzN4ifgmdFEWIl+eZX5VuxSRyUKmAaAvQKlWi9/6Zxi6EgO7TrzeMi+lC6zctX6MvqQS3Mq4akz/Ymnt5Usrn2u0wnU/Uc1f4dxLi/6fUypExCUnV7eB3jkVL7WVXBkshikHvvhlDYYp89eSq4EVMji9Pz2j/0edJ1eror3UjnhmgdaMT+wRvAggtRdkDGlorxob3W/wh/6EfTxsBFXB8FK5rBvdN8sgpMlL8yU4Sl3c6Z0qoEcfXTNYC04CsvwZSLZGcS61qyI87PZuuHUUwBotPD6p9WMYVmIiyyI2SbXYWPZpA/uUqIe1GKKjkFdeNAjpsBMkbbg+t/Y2THEZUrDUOWGaqD5p4MmB0DRnjIywN+XVyCBCYOrAh7g6owvUG1vG8KEfeEMFYqPj42fzXjxY/ZBVEpBXkCX1qgAcPVqgZF1G9JCZgNOX1mOce9/4BShF+Ne1QmsyDwC9m7IXjeCbUFXoqM8bUdf/iZgea8isJ+jPTT9LBGV/8BsPP9BMcqteyc2tPCF1NIUBDD5rc9Qz2evKc5BokdNsa0W4JMorKuT8hoYxpKL2s47s9H9a4HFQTkAbx/l2sLm9yfKq68QeBxqsZ+9s8sFunt1SCFMsDxOdKeOKN7+w7mi7XZQ+d2lALHt61979u6lefFNIc7RVG4YXgTuEsA3w6YKzHVeXL7CzwiwPhFlF1NLKoYficqrsAAFzsnTW91sjTClz7wtn4uyAr+0pX/5gkHWy9upjz7H981Gr62OzwzBx7tVw71GznWTo73BrZ0hbDyWO6p0fpSSVMQiICHsqKBUXX/oL9mU66xiSjnpT45Oh7IdLCX3ZwbzMVnfV+nBB+0hAuWPWC1JMnl9/FR/HhNYZNABtwWJTvyN3HE5t+JAzHkX6qYZEjx64+yCx6EkAj77F+6Cr1ftaUm1Ap2OS68Dl5VIVVVquBCrCJWtW+VYxl1GGXKgdXir2Ie0VgF9d5cZYe0g1YR4cAghVZTMJf3bh00gCk11vnieKF8nirjDFDpw6FjQwSQrvK8o4r4aYCWMVuVzK1XoIMPyLcCUUFb/XAz9AGUDopEMtpjnGae5kQvbA3wpkSz10WE1o1VZNSLJ7bBGJ5WFMuzTIPRGlTeF1rDCqZ2MyFKH6d+lsMQ06aac59BYBZiydVrDoxN9Z78OkMGyBgyQwaaX7KolX7woKXFQhKc7V60Xp904UF5ZjSsgv32MAiHAu4ZI6Qdc0u9iHXWqKraP13LFChKWXYjGVSWAMyDa81riyNSMpHbiYB49EiVZ0f6nMTlinOVU1TIvgJ2tDh+zdge5DKOwz1hUgpgxvc9bNSga2u0rr8Piq30Z6Aor7nbwLRNAPcfwQghXWwlfZZmIMCVLSTyusliQkOZRuG1XyZ7s6oVRE4Ge/mVqtzV03AK0L9tGSTyeSiLKudsW7lof1XmMzOKu4iUTJDr8RKbNsB9q/s7xag1bMTgynaG4+MOk9Jvec3u1V44jycO9ODg9NyURCLYmIMgzZeHVcNubcydsji3mx8L2OZASNKvao0f9gHCuZ9ZOEK4ioMYwjrizaDVhgxOjjEydjbelAxwXZWxrrPZaXRtB8U5BRrfpMYewgmLExtLwhUmzz4tS0QdDEI50sB22bnblMq3iGH7vWWPO3d3KpkwqbFE5JAFggmWVjQojPAtVcbWodmDMfKv+zg//P4vUZdjeJGWqY0n159T4alLFdVl0fkMM74W9VSnZa38E33oV5kx50Exb2e55h64batKeJcBrV9nXmyhuwx0yuTHzgkoTGz4z9UyYRsZLufIoomRy/o2VKltHmL2I7rEBFX53edyz9gtCT0tBxQQdVbDqitRqLu0GtBiFO9rwRT2ZkzSFiNPSdMTPKkgFbpT3KBLZT4FDSykpOOhHllTIurEYMvqOiVN0Hz4LZQPvb8Kk2Bj3F+n60mF7cqjo27g09ifkUgxp2WYdKf+V6NF31rdVZkR8jigklbWVcCEZjpmJHLGNLGZBwnbN6+C+H8Z+rTIWDNxqR/VkJgGlG2reScmj5TonskUCAqk6sAtIMXgfgM8wTgMDosUvEcrDWJeWcbSMMD8G28bJtpk4OIXYvXhL51LGg7h3v5QkFhkd1UPOP0Mv4GPnhBPeSPah6UNH2m1fGNLu0N76YBv3tpV9BNmvePkie1d2vjznfUv8nshTh940BCIq2kWI0tCZMbYOwdNsVLOmr2FQelWvSFqL5DT952OqqSmPu49RiwbbcnzowrhaYewwkvBw0XC6PGlFE2c/rDRMZCBZlHmLlq4B5b1ax+yhQGZD+lYYhecp40cD7O8k1aZlLCdsHOh2JxMQl7e4Dsw3vG/Y7pMkWhid81EjyfZtrRT6fsOpWAnb74UFfUCiLPUV7hchR6+woAh9Z4rLTvnVWge2LPF6iSHpHj3doeuZx2AJi4CQujkfAZrRCejk53IHOc7ZiQJeizIgZLicGidyvAUG+ncRkASH+6SBdeh1aMEb1NJlrp9LYzyfp9vUnVazH7YEYyxuDgaNycyYlMaGhyCd0LzNaDaav2qYWvLxARTrU8wjtumVKCqjo+taq4ifUa2q+DSEdCPej4kzw874gO6NDiCx6to4V1HaFxrfi6r3QPNfxNu+iqioQqhuqWvHXb9oConQ1iu1F+/OYLJT2DgFUSA4hZUl2mqU1YytVbS/x6tEufHgt417OimtFQuwbdwLMs059l4FOia26oqly9+43BblP3K1y2p9b6LAWSUaDxvz+rkB+oBEyxrw3S7yG9839sAelgyuinGDYkioO0IGWSQxOar88NiTeub6ffCuR8i+a6oS0rPRRKzoTTRJn+/2qZWOww5WbvjYTW8r6ba2KTeP3tBPhMcbQpRLMX4iH0d0Z1G5QxPkQDxUJUwJESVazeBX0OT7JF7nPlOfIACXVsqIepr+EveBuZP2e9H2f6QbhMXemGGCJ1GEXKgzJv84p7NY0LqMD90unzBAkKMLSoP3P3gHvsA6o9/HQ1fCgBzV8CqrZqG9lOB/YqP8MV3KTFfwDP/0n06hZRIzsk/EpAw4ea8uYcJ+q/DMjSbcbxeeNCChMc6zVSSq9p0uWRPP9B07iR890EkoZ6NgNX4yIO2NPxUUoqciWxomlRpiw6xkSJMtSNu8xI+hex7lCuh9mVJMtZGkCk5tUVtdfamtWc+GxMJIrZBU1+iHVsu+zXlRCQl0FB8/eZCWjW5p52ds1G9/DXUKVBF5Mt0oouy2VNeYF1eAZ2EreL9OH7NyKuSoRrzCjomxiefpzY01xoRXNWozR5YErAErCSnhaDcsmVyjGy5Oz0J9c1Q8sdc4pn9+NOAGh3wjzH2ZKggApb0NMl5QuVcv9M8OfFlw2ZW/3czn4FqvCBv5RBVHrMFedHnvaP/ZchDhJx1LTmzIeooBk+2PHZpxTDqcNnMAvAIkjhIkn9tGRI0OOUtX6YunFm6NBRTKN0Bor36mMbWOgqWMFoJdMG2hwJymqlZF3usJkLZhfl/bI/NMGfKlkOCoMxYpgSDhP3D/yqkOsaan2Xv715IfxsK558FT4/BabGTD97ZlPzpDF/8uJyHSEo3Y/X4gc0koN0ry6mXbOVac9jPW/Cwg7/B5TqXGmtIAL6bhGyF1BsZWeRfbCvmZ6bJnuHx1PGI83zfBCs/TkE978Fi+C4bBuspxVK0JTnnZiKP62U2TJFez4b3Guc4+9kxVvnyGpzJ3p/Qe7tc5HCjLrakt68bVCy2uOTtI9bOZtHtTf/Qn7+BLyAq+fSOqB057Htf4jlIuze9F+Xn/wnQCSW1xm5Bxjd3HI+iG0upKdqSjMyq26y0zMZga0zdoX9mZCE6/bju5aBcnDBajY77a0X3J7kzT4ur8DAA6CO8mG+Y7zDep5A26DCmSzRf+NGgweJZkDFyUgwXc3Bu0ktZEkiSUcxhYATZEfgOsrrzvu3qq7bPTPK409Jam7AUC43Ed54tn4XFsJHwWzG8uJMeI+4OK7hi8DscKQtPrsQPkXOtT+4fR+Z2SQIVAa6acHdt1uB5mV4zvy1S9wQkxOj1/mbMBtsNWF0Sj3dfij/tfp61vE3DHJH2L4/Tj4WsIZ5QYy2HWs+cyarn6rzJl2xUDxbZjahDmp5XxCZ7JB75o1aBBrxMatEkT634XcHuhVksIN++/OIiWfsPlG4hhnhHoWHosUD4ZiIWmE3mn6kZNIu4Y3Dn5+PqP2Jds8I9b6GmSrkZH9gwdlzs8rW7Tj4/Vy3vVSf56zQyyEOfjbLxknslaFVrsPPnpOrG7UovZHvvcp9Ckgt/fNs70PZmPXUD1dBV5gYgbURZ8Jbo21AK2dJg0JmkrHovM3429vKI7mZtfscD8k5mbh6jAnge6go5VUrPx0bB94ksrrLyaazbnPl7MltVTiwrnlTOSqUdd9VL8s7GkIB7bMAavPpqm3lv+3bq+d/7bI+I7Hac+nrtt5jwU3Kr2bdI+jPLbZhxGBkVta/k0AXz+5gbhw9zT6KpRYuy21Ei29st5KyQ+spBzHtxsWfBKd1vg2MTdKU7YoypFQ7qHdTkMKHJnsb1Htk7/IDgjL5f7BFoaCDze8o9QUM5WbdMHs09v8ZGHBHT2JYPxV4DwmNvUKp/y36Fs9UGINA7Tjv6eAm9kB/31bnjfbKuz6Max94xa+uo89oCBbJErlwP9HsBBdmJhOJ1dxriqrG9zRnYeZLiAciGxYRTBaqcj2DKnzzV61tWDJvbRfqXCHjfGfPKuyH9yUkdLM1/FhvZQJUIsGKCCmNayL2YzuMsy+zd1nNzK4G3gQhiN2xc9J7r4D3g+p251ZdY/A84iGrn4rjMlkwMcu0BzCjIhK54rlirfRMMmADgoK0r9Lp8W4tbMJyUEo8lZ2rBAcaRCaql9rfS9h1lbI/rgox5w82hd673YCoc4iBmA9y/6G2B4PGuP2TdLsKqIQ9QGpWlwiwbd/WV/nT5AmQg674EgvIU3Mp26J2hMYbhJreF62FPHmelzxrSNhogGgo4KJgdWtQYJ9g7BWEIoDr/V/eAWgqpH3CK342wCE/CVvl8PaeN2dZW7OnTNuNSfFGLoD0TQvOJK/pmJhM/wroKJ6/LSoOW/4lg6D5l286+Mkuew8naL/H+M
*/