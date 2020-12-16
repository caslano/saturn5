// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/set_adaptor.hpp
/// \brief Container adaptor to easily build a std::set signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::set signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class set_adaptor :

    public ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{

    typedef ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit set_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef set_adaptor set_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP



/* set_adaptor.hpp
c+Rkwjj8uxmxF2H7dLKiZS5PZeAIM/upM4Z5gG8i/ohQnZe77T12F0+ft6jcyVO+tze7nzAWIJ8RbyJUV2W3l2cuoXrG7LqFpm/fVZndAo/+ghj9FdKPzMV8p21YMCcAD1w2Gso74hKfd1Kz+Nnenu7NdS91gWPyJa48ts3YkubYMwNxJKIY8Xv8LIxrk2dXz67zyUO3TZ5g5s92OvBf+So3cnzbw9EBZKbf0/G2nQ20i2c25h2zNz1seLXeMcsQ7/Bj5ZGx8YEV5dUJy6TMExqVlW+ZvNzpzX/NwfEr5Fw0Db5pZmYSo1SVQblDGdQ+Mx7tM1Ma7DD91pIHnIdMHnTySBOac2tH7mRQ/HYb8gomdTi0skO4UbNwx9TnpzIde95AdEE8qXQrbRGbbjajR8o1UJ9lp68757vW5L2UlgFnu8kX0tc6v15aKt3kxrHufPc1Jt/oO7fXBgYt3bpKHnC6m/xIM5/d0eZLZ87wlNdvmXvXIk+Kzxs3zx8wM/PoRyX7hz2+XKv9usLMXCh5NCzdyNN0TCcR4B+3D+drgN93iW8j7m4fzt+iA+RvqU/+Vsblr7delDZ37NmI6Ii4DvEe9jfF9QvZHNlQ3sr8QNPPT4397nOMq9/HTYtXTV5j+yi7RMzPU/lRXvzWzMxW2ys31PYmh9v8GQs9azrPm/5Fer9HzBeE/XBkXn7kqp7tNzMnMmeUhloQsyOzzw7YvI3sB0itEZaufmUsGx6XETKXLnnAOdXkrc38IjO/cF5dFXElmwqR7TN3y+hFH1m//qtcv2FmKuLLkpW3CejvNP1BvGOzpUaPyPwd4RwV6htRpoLYmkO5+Uv7Q2sbyE/3u9lcvVe6RNSUnuoXaN8u6SyzpdZuSE1mI34tMnVLm5gyeceRjj3XqkwuQ3wYaqszYsqkvlhOWCZlfqDKS1yZlL63TH7f5FNVXuLKpMrY98zMDJVJueFXJlWGN8pNlUnMH7hMbjcz/fzKJPYbUybpvagMJipf95r++ITl646MaPlqofK1W+nlLVvvHWLZIs3qly3n85etyPrJjqb1ky9s/eS97JD6Hc/+KfuB1G+WDP/O4ClphUMJ+3UpIfUWO5qtntXl9aHvPzDg/tZVZ1QmXlcZbuEZ8nGP7pM+Wn7F3aOmtt2bdvVF5KO5s+uSsmtvb/P+/Xtaz3h9+6UP9/zvX4eps3S49LvffOGtJ/v2XfXkxKWzr7l9L+9/U6/Lu/LDVePXT72s53nfyhqQ8SZr+w7qCB6bb6gMWPnX/mnNzWiOpzJu//Mw7X8eDjvAETBfcuzzJtZcCFwn+0fAMtk/HnO58ASYJ3lHyafBE+F0eBKcBU+GVXAwXASHwBXwFHgxHCp/0yPjcM1L4C/tCXVC/mJ3ZUu4WP4ugePg9XATvAFuhTfCB+E34CPwYvgEvAf+Gt4MX5F8D7wdhvy+AzaHIfW2cBk8Gl4IC+DF8BjpD4BL4DB4OZwHV8M18Ep4rcx9A14Nb5b970j9HngR/DVcBV+Q/svSf8/W4jTG1Bi6EtGM3/OUHpu17nQvHAC3wFPg/Ur/R+EC+CN4KdwKr4E/hpul/wh8ED4PH4JOAHW3HGh8Bmf4lIOjMZcDu8ACWACPgX3hcbAbPAH2gIPhMfB02AueCXvDCfA4WCx7irfGRJam9eL9hsrBmyq3b8Gh8G1ofSo4Bu6BRfAP8Bz4J1gO/6xy+A5cJvOXSP4epCxpbIFf8r8l3Cj/n8BcF7gddoe/hAPhUwrHr+Bw+Aw8C+5QOH4NJ8Jn4fnwOVgKn4eV8AU4D/4G3gxfgt+FL8Pvwd+qXL8CH4evwifha266qZ+qsMan2xmqp+Ngf3i28qVI9Wg=
*/