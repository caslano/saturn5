#ifndef BOOST_MP11_TUPLE_HPP_INCLUDED
#define BOOST_MP11_TUPLE_HPP_INCLUDED

//  Copyright 2015, 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integer_sequence.hpp>
#include <boost/mp11/detail/config.hpp>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cstddef>

#if BOOST_MP11_MSVC
# pragma warning( push )
# pragma warning( disable: 4100 ) // unreferenced formal parameter 'tp'
#endif

namespace boost
{
namespace mp11
{

// tuple_apply
namespace detail
{

template<class F, class Tp, std::size_t... J> BOOST_MP11_CONSTEXPR auto tuple_apply_impl( F && f, Tp && tp, integer_sequence<std::size_t, J...> )
    -> decltype( std::forward<F>(f)( std::get<J>(std::forward<Tp>(tp))... ) )
{
    return std::forward<F>(f)( std::get<J>(std::forward<Tp>(tp))... );
}

} // namespace detail

template<class F, class Tp,
    class Seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>>
BOOST_MP11_CONSTEXPR auto tuple_apply( F && f, Tp && tp )
    -> decltype( detail::tuple_apply_impl( std::forward<F>(f), std::forward<Tp>(tp), Seq() ) )
{
    return detail::tuple_apply_impl( std::forward<F>(f), std::forward<Tp>(tp), Seq() );
}

// construct_from_tuple
namespace detail
{

template<class T, class Tp, std::size_t... J> BOOST_MP11_CONSTEXPR T construct_from_tuple_impl( Tp && tp, integer_sequence<std::size_t, J...> )
{
    return T( std::get<J>(std::forward<Tp>(tp))... );
}

} // namespace detail

template<class T, class Tp,
    class Seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>>
BOOST_MP11_CONSTEXPR T construct_from_tuple( Tp && tp )
{
    return detail::construct_from_tuple_impl<T>( std::forward<Tp>(tp), Seq() );
}

// tuple_for_each
namespace detail
{

template<class Tp, std::size_t... J, class F> BOOST_MP11_CONSTEXPR F tuple_for_each_impl( Tp && tp, integer_sequence<std::size_t, J...>, F && f )
{
    using A = int[sizeof...(J)];
    return (void)A{ ((void)f(std::get<J>(std::forward<Tp>(tp))), 0)... }, std::forward<F>(f);
}

template<class Tp, class F> BOOST_MP11_CONSTEXPR F tuple_for_each_impl( Tp && /*tp*/, integer_sequence<std::size_t>, F && f )
{
    return std::forward<F>(f);
}

} // namespace detail

template<class Tp, class F> BOOST_MP11_CONSTEXPR F tuple_for_each( Tp && tp, F && f )
{
    using seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>;
    return detail::tuple_for_each_impl( std::forward<Tp>(tp), seq(), std::forward<F>(f) );
}

} // namespace mp11
} // namespace boost

#if BOOST_MP11_MSVC
# pragma warning( pop )
#endif

#endif // #ifndef BOOST_TUPLE_HPP_INCLUDED

/* tuple.hpp
UpXWBB9niE9IfxQokuoQZSGp0IYi624ChyJn3MQERWR/kCcnk0P6BlKmLnIx7o4316k99E6Vh96Z5A6bUjrujvqkKm1ylWT9Un6j4g1rijeUhaRCE4pY1oFDkSfXskGRuCq2zE86mVs86lH8yWvZongNKPJNSB8Uic+59sxzLloNExaS/PSFZEkocQDkJ4wpl6JYyphykYVEMapSOl7l/klV2hMXEs0oPv54WGgWkPz0BeShTjVlnIoymg+INf0BKUuq0ppQZWbqJDyYAEU6d5GVIExqtAol8FXFU19L4FCkU2KDIvHh5aRZQdzpK8iuUuYlPT683JmGV3zKSh9er67JMGWRzk4wZ7loVpAMUKRkDTgU2RFkgiJxh7gpVpDctBWkLZh5QY9HWLnqERaZslKDk8lJVdoTVpAJpt1cihUkHYqEO8ChSG0HGxSJOyNPa/L1qEfxIzeyRfFu9Sj+/hvVAl6LesBLoIjWMuhQx1PH38iGp+zqeKp/tWrAW/gWgSLqUbw85KM6aQbxHvUgfs5qtiBeIyniWK0vKYJmADMZZDTrSIbEzm0BNh00gEhRIKNf6iYCIn1DfDjk3XZwHNLcrg+H9A1wwhBHOzgMea4t47K+ZAIY0jfEhULObgNHIdtW6UIhfQNcIOSGVeAg5OhVGZfzpROAEKQJJwZ5eiU4BqlaqQ+D9A1xQpCfW8EhyJ2tGSFI3QQQBOnCiUAOagVHIO+t0IdA+gY5AUjlCnAA4kqq0ppp4VCZqjjxx/obwPHH2Tfowx99A5zwY2sLOPy4viXjfFU3AfzoG+JCH9YWcPTx9HJd6KNvgAt8FC0HBx+/Xp8RfCydAHwgBTmxx7XXg2OPQ6/Xhz36Bjihx7PXgUOP+dephLgEegQmgB64f5wbsr5uZovbNbBHZ7M+7IEGHeeGrL2b2VI5Ghuyeq5l3ZBl4duQNfVatshdY0PWP8v0bsiycG7ICi5jU0IDfpy8jCkLgmYDrg1Zry5lC981NmQtXqpzQ5aFa0PWziY2DTQAyGNNbFkQNF1xbsia3ASOQL5s1IdA0Iji3JBV08imhMaGrL0aWTdkWTg3ZN3TwBa/a2zImtKgd0OWhXND1mf1bEpogJDV9WxZEKQM54Ysdz1bBK+xIevFJXo3ZFk4N2RduIRNCQ0YMlLHlAVBDuHakNVSxxbGa2zIOqpO54YsC9eGrJeuYdNAA4hUX8OWBUHO4NyQ9XMtWxSvsSHrzlq9G7IsnBuyjqxlg1MaG7I+vpp3Q1YW54asiqvZoniNDVnmq/VuyMri3JC1bjEbntLIg5yxmHVDVhZfIuT1GvBESF2NvkQIcghnJuRfPzgUedzPBEWQP7hSISf6wVMhg4t0pUJQz7lyIfWLwKHIAYvYoAhShTMZ8nA1WxSvAUXKq/VBETSiOLMhAwvBsyGhhawbsrI40yG7LQRPh2y+Sl86BC0onPmQqVeBQ5F/rmSDIsgjnAmRlVeCJ0SOu1JfQgQ96JwZke4rwKHIoiuYoAhyCFdK5LcF4CmRexfoSokgb3DlRCYvAIciX17OBkWQMziTIgsuZ4viNZIinsv1JUVQJZxZkXvms+EpjazIlPl8G7LQTM6ZFXlrHlsUr5EVWTpPb1bEypkVyZ7Hhqc0siJPVbFmRax8WZFTq9iieI2syHeVerMiVs6sSEMlmxIaUKSgkgmKoNiLKyvy6Fy2QF4jKzJjrs6siJUrK/L9ZWwaaECRDZexQRE0XXFmRfa+DByK9MzRB0XQiOLMivjmsCmhkRXJmsOaFbFyZkU6ZrNF8RpZkZNm682KWDmzIq9fyqaEBhSpu5QNiiBlOLMif85ii+I1siIPztKbFbFyZkU=
*/