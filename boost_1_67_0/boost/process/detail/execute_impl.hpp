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