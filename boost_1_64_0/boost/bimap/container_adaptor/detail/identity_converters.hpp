// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/identity_converters.hpp
/// \brief Value and iterators identity converters.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Details of the container adaptor toolbox

namespace detail {

/// \brief Iterator identity converter used by default in container adaptors.
/**
If Iterator and ConstIterator are of the same type one of the convert function is not
included.
                                                                                    **/

template
<
    class BaseIterator              , class Iterator,
    class BaseConstIterator         , class ConstIterator
>
struct iterator_to_base_identity
{
    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }

    BaseConstIterator operator()(ConstIterator iter) const
    {
        return BaseConstIterator(iter);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class BaseIterator, class Iterator >
struct iterator_to_base_identity<BaseIterator,Iterator,BaseIterator,Iterator>
{
    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Iterator from base identity converter used by default in container adaptors.
/**
If Iterator and ConstIterator are of the same type one of the convert function is not
included.
                                                                                    **/

template
<
    class BaseIterator              , class Iterator,
    class BaseConstIterator         , class ConstIterator
>
struct iterator_from_base_identity
{
    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }
    ConstIterator operator()(BaseConstIterator iter) const
    {
        return ConstIterator(iter);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class BaseIterator, class Iterator, class ConstIterator >
struct iterator_from_base_identity<BaseIterator,Iterator,BaseIterator,ConstIterator>
{
    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Value to base identity converter used by default in container adaptors.

template< class BaseValue, class Value >
struct value_to_base_identity
{
    BaseValue operator()(const Value & val) const
    {
        return BaseValue(val);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Value >
struct value_to_base_identity< Value, Value >
{
    const Value & operator()(const Value & val) const
    {
        return val;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Value from base identity converter used by default in container adaptors.

template< class BaseValue, class Value >
struct value_from_base_identity
{
    Value operator()(const BaseValue & val) const
    {
        return Value(val);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Value >
struct value_from_base_identity<Value,Value>
{
    Value & operator()(Value & val) const
    {
        return val;
    }

    const Value & operator()(const Value & val) const
    {
        return val;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Key to base identity converter used by default in container adaptors.

template< class BaseKey, class Key >
struct key_to_base_identity
{
    BaseKey operator()(const Key & k) const
    {
        return BaseKey(k);
    }
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Key >
struct key_to_base_identity< Key, Key >
{
    // As default accept any type as key in order to allow container
    // adaptors to work with compatible key types

    template< class CompatibleKey >
    const CompatibleKey & operator()(const CompatibleKey & k) const
    {
        return k;
    }
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_IDENTITY_CONVERTERS_HPP



/* identity_converters.hpp
zrbk1KlGZ59Xp3v1FX6d+dLxp/cAOoe8Oq0z2jRp27q5SXBSs5B7lcu9Tde7DiatJ8vtT2tCUJv+iPh7xDTsG8pDL7p/Q3G28eKgNh76/STQBmRPWbp2PTf+1dIPbevLQtq6rjO6VvjqWjvFq3sTbud1p0zPtdG+59q2ltm6I231jDaN/apNOVUHHugLKslC2PW3pN/Jvm6uiK5/DLDbemHOZ6lDbd2fpWpC0taYZ/z8bbWepTT2mePJznQ3lUVHZIj33cR3vIK0krygdwtL7TkdHWzuqCykTyzmGhFjbKHZ7TY7JDzWXK84wQovdoTbbaIBZdlOZUlaKMuZ9r2G4+M2x9e9Bpp6ZY4ZVBcOtnfP/+FA/p3vOa55P1x33gmvO++Hj3Le7ftkdO28j02mXbxk513PsL5zPjrZmW/phc834XXmm/BG5fs0Z75HJzc+3/5zvi/G/ZznOPOtdhauvufUk/ecevKe07i8f+1zPkDXl9wOltmm6d3JPF9xAdz9W9s2p/kgH3iuoI+HkRMl8+fJVpt0iSHRiuG9o5PJ4x2mDMoumFnKdUf3zLeM3mirM/8zEJWN9o81+93uKzsOxX56P3HGPxQ9ngtMntDXGITCKj6XG/1Jbvp6Jjf3Oo0h2NCA59f4oOdXO992OZNH/E0e7XK+3fj50q9nWH3TN2kMutYmd6xd72ZwLqt99a4krcD9Wjs9qO5JX3VrqSk/Y9JI5WuHB57nG1G3pofULeLHTfwhbehQmLzU2HkJum665qOmznwQ/i3mw38NrImrnY/JyVwb7XwEXwPHhVwD99eZB8IblwfnNY5+mYadi6p493MRvceZB13P3OsUunXmg/BG5aNR5+JjWPY/ZBvLfZxHuPE3jbeN1dg1Jd3HzTR+vA62QfBvt7vNsqJebw7/6NH0B+PmjufB/jYzjqdJn0fef/GDW7bfddUL3Uel/XXDNzeu6LuymfWpGb9iNvNOtsbYxeVdUb+T+f13h/8h/e7C7w/N+4P63/W8Tpj53VFxTuVS7NfLqUOvUHo5SL70RknPab+rB3pe9oQd5I6HyTAJHgf7wN5wGOxj4pUtXsWboHid8+j6Kd7+sBlMga3hD2A0HAA7wRMc+dkfNj/QcdzD0pvkctzO6LWHXeBxMBH2g11hFuwGs2GSHZ/6LuH5LvGlaX3UQbA/HAwHwSEqj6GK9yTFV2z3tXENUHyt4AzFV6ZyLYfHw4XwZFgBM2ElHAcvgOPhEjgVVsH5cDG8Xv4fwhp/n4r6ptZoDeg7dbzL0UuGy2AKvBIOhlfBDHgNHA2vhmPlztJ+2XIvgdfCarhCY7NWauzVKvgMXA1fgzfAz+Aarbd6IxwJb4Kj4c1KN8fWuy7nXuXU1NQT9X9rHuYc1ZNSmCi36gvvr+HrywyH3jbpdXPRm+bQO1yH3nkBPd4xwuvFO9tnHXrnSq/MfvYlLdJrDQukNwI9M35Y7XKk6s8o2Btm67yOhQPhqXAozIJjFY5Yp8EcuZU+nukaVi41LzWsXPY3sFy479dZLodkJ2j93JbWTuQg0mZeS6svkoUUz2tZrw2hstZNrEsRN1tCWzd/9+P+vg17Qq9sPno2hY5srn8sYJv7KRvcKfd/e2MCv6p9oTZLvvrYwOXUvw3ILuQg0nR+S6s7MgzJRcqQ5ch6ZDtyAGlahg4yDJmKVCCrkZqyyDjDyBbZIltki2yRLbJFtsgW2SJbZIts/9tbU2TeURj/z9z7Yp8FwK9nA9A7Pn57omWPm9museoLvGP+xBHJ/PiN77v2/Dzv4csw3ldhvnHdFG3m/ZdZgfE80k2x59mnGPfJnsD3sip9D/PrHm+PuTreuMd52gW+mxc=
*/