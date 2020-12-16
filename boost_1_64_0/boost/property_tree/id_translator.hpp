// ----------------------------------------------------------------------------
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifndef BOOST_PROPERTY_TREE_ID_TRANSLATOR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_ID_TRANSLATOR_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>

#include <boost/optional.hpp>
#include <string>

namespace boost { namespace property_tree
{

    /// Simple implementation of the Translator concept. It does no translation.
    template <typename T>
    struct id_translator
    {
        typedef T internal_type;
        typedef T external_type;

        boost::optional<T> get_value(const T &v) { return v; }
        boost::optional<T> put_value(const T &v) { return v; }
    };

    // This is the default translator whenever you get two equal types.
    template <typename T>
    struct translator_between<T, T>
    {
        typedef id_translator<T> type;
    };

    // A more specific specialization for std::basic_string. Otherwise,
    // stream_translator's specialization wins.
    template <typename Ch, typename Traits, typename Alloc>
    struct translator_between< std::basic_string<Ch, Traits, Alloc>,
                               std::basic_string<Ch, Traits, Alloc> >
    {
        typedef id_translator< std::basic_string<Ch, Traits, Alloc> > type;
    };

}}

#endif

/* id_translator.hpp
r3gBu3kJP15v//lbBT3Xk1f3pseKO8TLhvqPFfJ1ODpVXjOhNj80790/ilvz8ZM89eoO8tlP4epLeHoBvz1e/Lo+9gd+9i/5/FL1h730cAa7wTsasP/MP9jXpeztS3l5KX1ciu90pgf703UhP1sG38+IxqXn2K/B/CF+vsINXr8MLz2B3o5O6Ufxw6D3CE/wiy7idi/8p5dzz2fE+Y3+wtCk+Iu/XIJHzsKnLhUHl6tH9UipxybUi9K9X33afuQ5t1eHv8/rKI4m8LA59HY/fLvA+f8WeGh/+3kSHmfeBb9Zz8V4zVL+/6brvQGHO+lPnIJHJsy7UZr6TTSmxLeu9Li6gXXn0deN+MEoeh2bUKfz+bvYx7HuMwB/WCvOwNmec+GNOlzyfvEEfq6k16kDzZs/LT3ETuk/vzF+vjYaG+LrxafYx7ujcUcWHHaOvrXrj8q3jg3p/Dwdv8Rf2NeCv8Kf1vDCubVx7Cj1X/l4LechfmLXD4r34vf6L/TVqvjldP5LX3XG4omD8eVHo7EITvaeKu58LX/yvtnxOXrv7x3/vZ/fDtD/uYff/BR/r419qcMWr8L7xuGd1pezSl1KfjXBOamcO9UF3Dd7IP30wwf9/4IUHvOzuFXqvs635VpHpfNfI27DR42D+8CLHfS3S5z2uZm1o7H8B3wuy3rxrKo71KdK6LFdNBby7/LR9vFyeXkruGi+czbw2/jcwWR5SoKd1fDnYdGYs5xdvgGXM/E/uNJuKt4gvuxlB6kt9PwEP6D/pva9cKlzHQPlbcvgkPPlc9Sdt+7i9/jl+oH4zSX4QrY8xH3qVNJDXvR60Tb6SarTnWXdbaKx2HndriPg7DRx7Sa4dzm93MGO8/mLcfWT6qlt5RGb4Kc4VlVXXKlQH9uLD4gzO+rbz/h7xXPSonEpe8eft46i7xL891W4fjp+9Yt5PYGfqs+Ustsc+WTWNnrroq6GJ6Ret57Z4vNN+NPP4tbj8D2J9zyFT5+DNzzNHuuIb/vMu0k0zmwRjXkDXO919eXj8B59n9151tEI/xyN9+7OwPPh6FD22Aw/XOac22z790T8PRk8aixcnZXBXvVp7WuzKnW2aXhsoXpoR378V59fpO47n377wuXP7UeDaBwhvmcn+EUzfteaHeSY1yif38OvhsLpZ/jvi/QCN0tz4W8ZXqEekVuP3fPbpe3p43v8bwPeO4S/dlRv/Rd9noTHOydcOMZ+XYOndBPH27jv1Xiw6zaXl5StVo89gf/j5dk/yEuT/v8O9sYOC/6mPzgTrpv3pMXx93/54SnsucI+7sPfz7ZvD7OXB+D23fZlA73gJ3n61UXHwyXj5nfk693hpeeY5B2Ah0/D5XeiceoJ4oK+2piH8LA35dVp8GctHrMH7ukL935Nvnif7wF0wf/b418t4NNZ1mv/UlXqfI+67pP6SPF5ktvljy3VbcXJrCn0dGWaOMaev4Ozh+zPsfCzmP7PZe+L+aU6VfV6+fYur6fhsfnyGvvTO4GvizvZ96bwRHwWX5/5MnzsSy998bHP8Kre6os98cta9HAY/+LHC+6Gn1vZ51P2/+T4+au+71cNr+bar5ujMfmN+N8rxZ5cb5LrVNDLPPrXhxv8Cbxn14O/FR9a4L3ygILH+BU9bobrhUPxi/h899QEv4QD2XE9kX2a35yW7Pgy9v0EP70eP0nA/y30AR/LMsXZyXBqljjDzibWt09j0tXlo7H3M3jbJvukHpf/oXzQOZsx29lZhxTepY6lfpULhye67tLrU85J68uW0Ov1eNPH9LmIn/h7jL93ZPGvpvR9uvlsEm8vxpdbyOs785vN0Tj9oOufop5VIX8dkKb+YV5nW88=
*/