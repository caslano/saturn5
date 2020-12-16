/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fallback_policy.hpp
 * \author Andrey Semashev
 * \date   18.08.2012
 *
 * The header contains definition of fallback policies when attribute value visitation or extraction fails.
 */

#ifndef BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The \c fallback_to_none policy results in returning an empty value reference if the attribute value cannot be extracted.
 */
struct fallback_to_none
{
    enum { guaranteed_result = false };

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT&)
    {
        return false;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT const&)
    {
        return false;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const&)
    {
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
    }
};

/*!
 * The \c fallback_to_throw policy results in throwing an exception if the attribute value cannot be extracted.
 */
struct fallback_to_throw
{
    enum { guaranteed_result = true };

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT&)
    {
        return false;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT const&)
    {
        return false;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const& t)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(invalid_type, "Attribute value has incompatible type", (t));
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
        BOOST_LOG_THROW_DESCR(missing_value, "Attribute value not found");
    }
};

/*!
 * The \c fallback_to_default policy results in a default value if the attribute value cannot be extracted.
 */
template< typename DefaultT >
struct fallback_to_default
{
    enum { guaranteed_result = true };

    //! Default value type
    typedef typename remove_cv< typename remove_reference< DefaultT >::type >::type default_type;

    /*!
     * Default constructor.
     */
    fallback_to_default() : m_default()
    {
    }

    /*!
     * Initializing constructor.
     */
    explicit fallback_to_default(default_type const& def_val) : m_default(def_val)
    {
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    bool apply_default(FunT& fun) const
    {
        fun(m_default);
        return true;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    bool apply_default(FunT const& fun) const
    {
        fun(m_default);
        return true;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const&)
    {
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
    }

private:
    //! Default value
    DefaultT m_default;
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_

/* fallback_policy.hpp
PnbJz+X+Ro8B7jW4dZSe+9zpOL3X0WxTbrtA2AAx5BxVkwkwAraBl2AiskfcNRF3QbC5uGsq7prBKrAFbAxbiXscyr40tXdPua9ljqvifiidUwU4HEbBkbAPvB2mwBQ4D46FS2A6fAhmwB1wPHwGToIH4GR4Ak6Dn8JcWIYwZ8EQmAfrwTkwEc6DXeHdcARcAKfCxXA+XAqXQ4RzlchX+BxcCU/Be+Hv4Sr4ARwFv4Gj4VUxv6TyTvZPwWjJxwAY4xmz0TMZLvojPHuTYFfRL2d5/9ZR9JNgRdgJxsLOsBHsChNhT3gj7AK7yPUlOF/v3yGu4n9FGWNUeYr/zWE0bAFrwURYG7aCN8A42Bq2huo8GdgbtoX9RL8/bAdvhu3hKDHX55dLPOpKPKzniDeQeDSUeDSGNWATWBM2gnXUteSbS+9rIYOVfyrvB0B1PqFZD+BJcfcqbAZfh13hG3AIzIdj4FtwLHwHzoXvwg3wEnwUmucvPw7fNOujXO+C70t9/BC+Dv8A/wAL4F/gx/Bz+AksT9w+haRF+UueK3/i4F/N8oOfwd5i3h9e4HoQ/ByOFvMU+CXXmeJPlpjnwG/MdgT/DheK+VJ4VZ37JPGG33P9W7l+HbrgO3LtOefvotTjMVJe1nP+IqS8ImEkjIIxsBqsC+vCejBa6k912FLMW8EasB2sCTuKeRKMgT1gLdhXzPvBWJgMa8PhYn4LrANHy/UluNqzph/uV/be573/lvSFwtdgTXgK1oZvwubwbdgbvgtvgb+HGfAMXAjfg0vhH+EK+CHcAP8An4AfSb34GO4VPTnHTNa9q/X1xMv7HLNP0asAL8NG8GvYQs59jIdXuE6E38LR8BqcAn+AC6Ah56UGwftgMHwIloVPw3LwAAyBz8MK8CQMhfkwDP4BVoJ/geHwc1gVVnVRjjABVocdYU2YBmvB+TAWLoN14HJYF94P68FNsCHcARvD12Bz+BZsCX8HW8HvYQKMJk8SYUfYEfaASXAw7ARvh91gBuwOp8Ce8E7YCy6EveEK2Bduhv3hbngT/DUcAF+Eg+HHcCi8DIfBa/BWSNqMFNgWjoXdYBrsC8fBATADjoLjYRqcAOfBTLgcToYb4RS4BU6Fu2CWnPO1Ra+vpU+S+loZrkUMOSc7BGbLuDtNxu0VMArmSj2ZJfUjDybB2bAHnAP7wXlwMlwAV8JF8BG4GD4Gl8Bt4u8OuAyekutLsMCQtZ2wqYzv1fn7tMSzg5z33QO2hD1hL9gH3gyHwXQ4HE6Et0j97Q9nw5ukHg+Eq+Ag+BAcDB+GQ+BOOBI+C0fBo3A0fBXeBj+GKfA8HAsvwDT4DRwHK7soJ1gNToB14ETYCGbqeYysuZN1gvZ5zCpppxtge3gCdoSb4Ei4Gc6Cj8A7xf5u+EvpL7bCdXAb3AS3w2fgDvhruFPS9aSkazf8BD4Fg+Tc8Gi4FzaB+2BLuB8OhgdhGnwejoeHpf9/Cd4HX4br4TH4CDwO98LfwBfgCcmHI3odlVoXpvIhEu5D+KnvMATAWFgX1ocdYSPYHzaGt8D2cDRMhGNgMzgONocTYEs4E7aCc2AcnA9bw03ibjNsA7fCtvAZ8Xef2O+HteHrsA58S8xlfiXrg9Scqsj86gEZxx6E6htyMs95CCbAh2EbuEHmOxvhTWIu821ZT8OYiNjn24+I/4/CqnCLdoeIuxoO7raKu22wOtwu7pZ51lfAD8Sd9ZxCbjtVf3FEyuMoTIbHJd9PSL6/A2fAV+F98DX4FHwXHoS/g8/D38MX4ZvwbZgPMcNctxd5d0+f5dBe3pf4fAAbwY9hb/hHmA4/geNhWTmX84LE63O4EH4B18KLcD38Ej4=
*/