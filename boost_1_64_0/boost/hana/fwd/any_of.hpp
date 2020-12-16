/*!
@file
Forward declares `boost::hana::any_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ANY_OF_HPP
#define BOOST_HANA_FWD_ANY_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether any key of the structure satisfies the `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to be satisfied
    //! after looking at a finite number of keys for this method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/any_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto any_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct any_of_impl : any_of_impl<S, when<true>> { };

    struct any_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr any_of_t any_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ANY_OF_HPP

/* any_of.hpp
ZCEtn7QdgHz0RI9CPN5ZC+X7n7Hcg2tvGe9ktOcfXxvVvRvX41wZsojhfqLdTsgDK9eAYFWrYNXSzdIF8gPtFkR4KrszngscrIZsjQzc3gIpOsE7P05p3wLva/qAiwtjA44oZZKyQ8jXfMyR/1RvcWJeSJx4g1GJBohPRI1LtOnwZIiFVw8d9kQ08AQ+Vyfh8zcd/LYFA+LzuR74xBs0JBoc2UF8UPHaRMVXkyquTFTUMebyefXDk1i2veTJmtIe8oSyJOHaFTM1OXSLBPdhbo3UsOfzZxx5UUwcROiRvRQw1h4Cpu5Z4h4dL+r0U/x30qGJhQBKQQQOhCCCk+NM3fQsBBFtCaeUnfSQMB6e/5f0Hk82x5MkH0MLJeTaT0Q+vnpGT/lY6zoJrGDUQv/FUnzybf7TvO/2nHwcqDinm+fFLVoRj5D/59JX/NxF1FvQHfQWu/dogsk+F29WNi+hdkWOFEuCbTJ8Ro+6KC/uLKo6MVRF4q1/EgndCfOZer9Dd+90RAcLMh4B5WCIGuZ9NoHLedEqMkq52raSdWncwssVY8QLD7p1pZKJt1fU+y5AXnO6cO7nmnTX+odmOEAKVZxr3Or6SWxjQ5uzvC/F4FPF/Ks+1qsLdG39CL25ny1K8uZGytV3suKdy3CFVyOODhfYptGBDjqWq2Oh4pEcamga7ZWVn9gj2Z/+fBZmiYvFJqRsheakWUGl9MdoyIFUTOgW1ombcIifom4bHnOIL6RGDIeyiaZl0uIaR9xQMMM7u5sWNA2SFpfO7eXd9hT28G4DCVpFXWQij44IY3sNfs4GucSYo/utqz+VxzpudT7N+/XEJvQyniiuiOavLkhwNd0x3DLL5W1j616rFXZfIJAV7DIGsrHAaEC3NpqwBUmHd3c1bzauiEWLNJqcO2nd9cDSkvEQ8/CWHZ02RwuscGrhi435h9aNiMVzYfMaPi+jM/+Zte/DBqXJd7ewLiBPl7fNN05infy9AYf3dwls/5yErRTHFg7WCO0pOYdApDFH9o3dh/v6ZRRObvOTZR41oOtl1SuU1pNZXR+fIL94/i3pLb8yyVm6AHPQAEfjnjZTsNlNXWQhYAMusge7LOvO8n7WlKwQ+K7G0KacL4bGS0eV3LQgyB4E11KQEV5YwNN1q8kASCu2HQfg248I4ZcH+zk4C41uvegkpN9A49Ngeu61FLLUnwzjOPCYVl3FHmKLgXYAfcxKkYHWePrRXUm/6A9V00rF8OABTW9aJQIcwO2ZCIJo+jzfTufq8t5Pyy7oQmfIYxfSdoB+YDs4Tw8h+R2K9VLvV3R+eC+/1yJ7p4AZWMqwricjSfDg5hxySO1sQ0BmyOWQeSUhvHOqXGXlavrdw1mP+4gRxPX+Ot4dl2gWpDWN8VUWggqlJWJK7IyWbEWHVZ+C6h+pv1CjtvA8aqDXWigU6iiMierPAPJuLiJE4zvF2TudzZuhOgLjVfxcB7iwSt42ejZQD8C5vGndRWIZs0o4Oy+6CLFhfK47xrW4bogoZEFe4DTnznCZMf+ddRlYxefNh+L5/Nr3j7wwdifuhQT3G+MQ0n/HJs7DZAuYxSYoFQY4q0dzz9wMq7nJ7SlToRETf2OlgSboyCcWb3H7b1HSeqQCS+cyzlt4kYQ6wYkS9qO++gTPLC6yb5JikQnFQv1lV1zdsVGtmFJyIhpnI4jAncYKwQswL3MKeGvd3AUKgfQT5W3lWniFhmtR4U2a8znUzzbv2JwOdIJvGwOvVH9MKA4lSr+hhyXjiF5278ZNBWL/K0ymzxzQpoRIuhAzYI1HmMSNSlzOi0PCtBc8rgWGKS+GLzI2mhcIp9ILvCjyUNpk7g2IsgN5Lgs=
*/