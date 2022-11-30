#ifndef BOOST_DESCRIBE_OPERATORS_HPP_INCLUDED
#define BOOST_DESCRIBE_OPERATORS_HPP_INCLUDED

// Copyright 2020, 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/detail/config.hpp>

#if defined(BOOST_DESCRIBE_CXX14)

#include <boost/describe/bases.hpp>
#include <boost/describe/members.hpp>
#include <boost/describe/modifiers.hpp>
#include <boost/mp11/algorithm.hpp>
#include <type_traits>
#include <iosfwd>

namespace boost
{
namespace describe
{

namespace detail
{

template<class T,
    class Bd = describe_bases<T, mod_any_access>,
    class Md = describe_members<T, mod_any_access>>
bool eq( T const& t1, T const& t2 )
{
    bool r = true;

    mp11::mp_for_each<Bd>([&](auto D){

        using B = typename decltype(D)::type;
        r = r && (B const&)t1 == (B const&)t2;

    });

    mp11::mp_for_each<Md>([&](auto D){

        r = r && t1.*D.pointer == t2.*D.pointer;

    });

    return r;
}

template<class T,
    class Bd = describe_bases<T, mod_any_access>,
    class Md = describe_members<T, mod_any_access>>
bool lt( T const& t1, T const& t2 )
{
    int r = 0;

    mp11::mp_for_each<Bd>([&](auto D){

        using B = typename decltype(D)::type;
        if( r == 0 && (B const&)t1 < (B const&)t2 ) r = -1;
        if( r == 0 && (B const&)t2 < (B const&)t1 ) r = +1;

    });

    mp11::mp_for_each<Md>([&](auto D){

        if( r == 0 && t1.*D.pointer < t2.*D.pointer ) r = -1;
        if( r == 0 && t2.*D.pointer < t1.*D.pointer ) r = +1;

    });

    return r < 0;
}

template<class Os, class T,
    class Bd = describe_bases<T, mod_any_access>,
    class Md = describe_members<T, mod_any_access>>
void print( Os& os, T const& t )
{
    os << "{";

    bool first = true;

    mp11::mp_for_each<Bd>([&](auto D){

        if( !first ) { os << ", "; }
        first = false;

        using B = typename decltype(D)::type;
        os << (B const&)t;

    });

    mp11::mp_for_each<Md>([&](auto D){

        if( !first ) { os << ", "; }
        first = false;

        os << "." << D.name << " = " << t.*D.pointer;

    });

    os << "}";
}

} // namespace detail

namespace operators
{

template<class T> std::enable_if_t<
    has_describe_bases<T>::value && has_describe_members<T>::value && !std::is_union<T>::value, bool>
    operator==( T const& t1, T const& t2 )
{
    return detail::eq( t1, t2 );
}

template<class T> std::enable_if_t<
    has_describe_bases<T>::value && has_describe_members<T>::value && !std::is_union<T>::value, bool>
    operator!=( T const& t1, T const& t2 )
{
    return !detail::eq( t1, t2 );
}

template<class T> std::enable_if_t<
    has_describe_bases<T>::value && has_describe_members<T>::value && !std::is_union<T>::value, bool>
    operator<( T const& t1, T const& t2 )
{
    return detail::lt( t1, t2 );
}

template<class T> std::enable_if_t<
    has_describe_bases<T>::value && has_describe_members<T>::value && !std::is_union<T>::value, bool>
    operator>=( T const& t1, T const& t2 )
{
    return !detail::lt( t1, t2 );
}

template<class T> std::enable_if_t<
    has_describe_bases<T>::value && has_describe_members<T>::value && !std::is_union<T>::value, bool>
    operator>( T const& t1, T const& t2 )
{
    return detail::lt( t2, t1 );
}

template<class T> std::enable_if_t<
    has_describe_bases<T>::value && has_describe_members<T>::value && !std::is_union<T>::value, bool>
    operator<=( T const& t1, T const& t2 )
{
    return !detail::lt( t2, t1 );
}

template<class T, class Ch, class Tr> std::enable_if_t<
    has_describe_bases<T>::value && has_describe_members<T>::value && !std::is_union<T>::value,
    std::basic_ostream<Ch, Tr>&>
    operator<<( std::basic_ostream<Ch, Tr>& os, T const& t )
{
    os.width( 0 );
    detail::print( os, t );
    return os;
}

} // namespace operators

} // namespace describe
} // namespace boost

#endif // defined(BOOST_DESCRIBE_CXX14)

#endif // #ifndef BOOST_DESCRIBE_OPERATORS_HPP_INCLUDED

/* operators.hpp
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
*/