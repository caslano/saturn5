// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/execute.hpp
 *
 * Defines a function to execute a program.
 */

#ifndef BOOST_PROCESS_EXECUTE_HPP
#define BOOST_PROCESS_EXECUTE_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/executor.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/executor.hpp>
#endif

#include <boost/process/detail/basic_cmd.hpp>
#include <boost/process/detail/handler.hpp>

#include <boost/fusion/view.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/container/vector/convert.hpp>

#include <type_traits>
#include <utility>

namespace boost { namespace process {

class child;

namespace detail {


template<typename ...Args>
struct has_wchar;

template<typename First, typename ...Args>
struct has_wchar<First, Args...>
{
    typedef has_wchar<Args...> next;
    typedef typename std::remove_cv<
                typename std::remove_reference<First>::type>::type res_type;

    constexpr static bool my_value = is_wchar_t<res_type>::value;
    constexpr static bool value = my_value || next::value;

    typedef std::integral_constant<bool, value> type;
};

template<typename First>
struct has_wchar<First>
{
    typedef typename std::remove_cv<
                typename std::remove_reference<First>::type>::type res_type;

    constexpr static bool value = is_wchar_t<res_type>::value;

    typedef std::integral_constant<bool, value> type;
};


#if defined(BOOST_WINDOWS_API)
//everything needs to be wchar_t
#if defined(BOOST_NO_ANSI_APIS)
template<bool has_wchar>
struct required_char_type
{
    typedef wchar_t type;
};
#else
template<bool has_wchar> struct required_char_type;
template<> struct required_char_type<true>
{
    typedef wchar_t type;
};
template<> struct required_char_type<false>
{
    typedef char type;
};
#endif

#elif defined(BOOST_POSIX_API)
template<bool has_wchar>
struct required_char_type
{
    typedef char type;
};
#endif

template<typename ... Args>
using required_char_type_t = typename required_char_type<
                    has_wchar<Args...>::value>::type;


template<typename Iterator, typename End, typename ...Args>
struct make_builders_from_view
{
    typedef boost::fusion::set<Args...> set;
    typedef typename boost::fusion::result_of::deref<Iterator>::type ref_type;
    typedef typename std::remove_reference<ref_type>::type res_type;
    typedef typename initializer_tag<res_type>::type tag;
    typedef typename initializer_builder<tag>::type builder_type;
    typedef typename boost::fusion::result_of::has_key<set, builder_type> has_key;

    typedef typename boost::fusion::result_of::next<Iterator>::type next_itr;
    typedef typename make_builders_from_view<next_itr, End>::type next;

    typedef typename
            std::conditional<has_key::value,
                typename make_builders_from_view<next_itr, End, Args...>::type,
                typename make_builders_from_view<next_itr, End, Args..., builder_type>::type
            >::type type;

};

template<typename Iterator, typename ...Args>
struct make_builders_from_view<Iterator, Iterator, Args...>
{
    typedef boost::fusion::set<Args...> type;
};

template<typename Builders>
struct builder_ref
{
    Builders &builders;
    builder_ref(Builders & builders) : builders(builders) {};

    template<typename T>
    void operator()(T && value) const
    {
        typedef typename initializer_tag<typename std::remove_reference<T>::type>::type tag;
        typedef typename initializer_builder<tag>::type builder_type;
        boost::fusion::at_key<builder_type>(builders)(std::forward<T>(value));
    }
};

template<typename T>
struct get_initializers_result
{
    typedef typename T::result_type type;
};

template<>
struct get_initializers_result<boost::fusion::void_>
{
    typedef boost::fusion::void_ type;
};

template<typename ...Args>
struct helper_vector
{

};

template<typename T, typename ...Stack>
struct invoke_get_initializer_collect_keys;

template<typename ...Stack>
struct invoke_get_initializer_collect_keys<boost::fusion::vector<>, Stack...>
{
    typedef helper_vector<Stack...> type;
};


template<typename First, typename ...Args, typename ...Stack>
struct invoke_get_initializer_collect_keys<boost::fusion::vector<First, Args...>, Stack...>
{
    typedef typename invoke_get_initializer_collect_keys<boost::fusion::vector<Args...>, Stack..., First>::type next;
    typedef helper_vector<Stack...> stack_t;

    typedef typename std::conditional<std::is_same<boost::fusion::void_, First>::value,
            stack_t, next>::type type;


};


template<typename Keys>
struct invoke_get_initializer;

template<typename ...Args>
struct invoke_get_initializer<helper_vector<Args...>>

{
    typedef boost::fusion::tuple<typename get_initializers_result<Args>::type...> result_type;

    template<typename Sequence>
    static result_type call(Sequence & seq)
    {
        return result_type(boost::fusion::at_key<Args>(seq).get_initializer()...);;
    }
};





template<typename ...Args>
inline boost::fusion::tuple<typename get_initializers_result<Args>::type...>
        get_initializers(boost::fusion::set<Args...> & builders)
{
    //typedef boost::fusion::tuple<typename get_initializers_result<Args>::type...> return_type;
    typedef typename invoke_get_initializer_collect_keys<boost::fusion::vector<Args...>>::type keys;
    return invoke_get_initializer<keys>::call(builders);
}


template<typename Char, typename ... Args>
inline child basic_execute_impl(Args && ... args)
{
    //create a tuple from the argument list
    boost::fusion::tuple<typename std::remove_reference<Args>::type&...> tup(args...);

    auto inits = boost::fusion::filter_if<
                boost::process::detail::is_initializer<
                    typename std::remove_reference<
                        boost::mpl::_
                        >::type
                    >
                >(tup);

    auto others = boost::fusion::filter_if<
                boost::mpl::not_<
                    boost::process::detail::is_initializer<
                     typename std::remove_reference<
                            boost::mpl::_
                            >::type
                        >
                    >
                >(tup);

   // typename detail::make_builders_from_view<decltype(others)>::type builders;

    //typedef typename boost::fusion::result_of::as_vector<decltype(inits)>::type  inits_t;
    typedef typename boost::fusion::result_of::as_vector<decltype(others)>::type others_t;
    //  typedef decltype(others) others_t;
    typedef typename ::boost::process::detail::make_builders_from_view<
            typename boost::fusion::result_of::begin<others_t>::type,
            typename boost::fusion::result_of::end  <others_t>::type>::type builder_t;

    builder_t builders;
    ::boost::process::detail::builder_ref<builder_t> builder_ref(builders);

    boost::fusion::for_each(others, builder_ref);
    auto other_inits = ::boost::process::detail::get_initializers(builders);


    boost::fusion::joint_view<decltype(other_inits), decltype(inits)> complete_inits(other_inits, inits);

    auto exec = boost::process::detail::api::make_executor<Char>(complete_inits);
    return exec();
}

template<typename ...Args>
inline child execute_impl(Args&& ... args)
{
    typedef required_char_type_t<Args...> req_char_type;

    return basic_execute_impl<req_char_type>(
        boost::process::detail::char_converter_t<req_char_type, Args>::conv(
                std::forward<Args>(args))...
            );
}

}}}


#endif

/* execute_impl.hpp
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
*/