// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_ERROR_HPP
#define BOOST_PROCESS_DETAIL_ERROR_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits.hpp>


#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif

#include <system_error>

#include <type_traits>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/container/set/convert.hpp>
#include <boost/type_index.hpp>

/** \file boost/process/error.hpp
 *
 *    Header which provides the error properties. It allows to explicitly set the error handling, the properties are:
 *
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::ignore_error">ignore_error</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::throw_on_error">throw_on_error</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::error">error</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::error_ref">error_ref</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::error_code">error_code</globalname>;
  }
}
</programlisting>
\endxmlonly
 *     For error there are two aliases: error_ref and error_code
 */

namespace boost { namespace process {

namespace detail {

struct throw_on_error_ : ::boost::process::detail::api::handler_base_ext
{
    constexpr throw_on_error_() = default;

    template <class Executor>
    void on_error(Executor&, const std::error_code & ec) const
    {
        throw process_error(ec, "process creation failed");
    }

    const throw_on_error_ &operator()() const {return *this;}
};

struct ignore_error_ : ::boost::process::detail::api::handler_base_ext
{
    constexpr ignore_error_() = default;
};

struct set_on_error : ::boost::process::detail::api::handler_base_ext
{
    set_on_error(const set_on_error&) = default;
    explicit set_on_error(std::error_code &ec) : ec_(ec) {}

    template <class Executor>
    void on_error(Executor&, const std::error_code & ec) const noexcept
    {
        ec_ = ec;
    }

private:
    std::error_code &ec_;
};

struct error_
{
    constexpr error_() = default;
    set_on_error operator()(std::error_code &ec) const {return set_on_error(ec);}
    set_on_error operator= (std::error_code &ec) const {return set_on_error(ec);}

};


template<typename T>
struct is_error_handler : std::false_type {};

template<> struct is_error_handler<set_on_error>    : std::true_type {};
template<> struct is_error_handler<throw_on_error_> : std::true_type {};
template<> struct is_error_handler<ignore_error_>   : std::true_type {};



template<typename Iterator, typename End>
struct has_error_handler_impl
{
    typedef typename boost::fusion::result_of::deref<Iterator>::type ref_type;
    typedef typename std::remove_reference<ref_type>::type res_type_;
    typedef typename std::remove_cv<res_type_>::type res_type;
    typedef typename is_error_handler<res_type>::type cond;

    typedef typename boost::fusion::result_of::next<Iterator>::type next_itr;
    typedef typename has_error_handler_impl<next_itr, End>::type next;

    typedef typename boost::mpl::or_<cond, next>::type type;
};

template<typename Iterator>
struct has_error_handler_impl<Iterator, Iterator>
{
    typedef boost::mpl::false_ type;
};


template<typename Sequence>
struct has_error_handler
{
    typedef typename boost::fusion::result_of::as_vector<Sequence>::type vector_type;

    typedef typename has_error_handler_impl<
            typename boost::fusion::result_of::begin<vector_type>::type,
            typename boost::fusion::result_of::end<  vector_type>::type
            >::type type;
};

template<typename Sequence>
struct has_ignore_error
{
    typedef typename boost::fusion::result_of::as_set<Sequence>::type set_type;
    typedef typename boost::fusion::result_of::has_key<set_type, ignore_error_>::type  type1;
    typedef typename boost::fusion::result_of::has_key<set_type, ignore_error_&>::type type2;
    typedef typename boost::fusion::result_of::has_key<set_type, const ignore_error_&>::type type3;
    typedef typename boost::mpl::or_<type1,type2, type3>::type type;
};

struct error_builder
{
    std::error_code *err;
    typedef set_on_error result_type;
    set_on_error get_initializer() {return set_on_error(*err);};
    void operator()(std::error_code & ec) {err = &ec;};
};

template<>
struct initializer_tag<std::error_code>
{
    typedef error_tag type;
};


template<>
struct initializer_builder<error_tag>
{
    typedef error_builder type;
};

}
/**The ignore_error property will disable any error handling. This can be useful
on linux, where error handling will require a pipe.*/
constexpr boost::process::detail::ignore_error_ ignore_error;
/**The throw_on_error property will enable the exception when launching a process.
It is unnecessary by default, but may be used, when an additional error_code is provided.*/
constexpr boost::process::detail::throw_on_error_ throw_on_error;
/**
The error property will set the executor to handle any errors by setting an
[std::error_code](http://en.cppreference.com/w/cpp/error/error_code).

\code{.cpp}
std::error_code ec;
system("gcc", error(ec));
\endcode

The following syntax is valid:

\code{.cpp}
error(ec);
error=ec;
\endcode

The overload version is achieved by just passing an object of
 [std::error_code](http://en.cppreference.com/w/cpp/error/error_code) to the function.


 */
constexpr boost::process::detail::error_ error;
///Alias for \xmlonly <globalname alt="boost::process::error">error</globalname> \endxmlonly .
constexpr boost::process::detail::error_ error_ref;
///Alias for \xmlonly <globalname alt="boost::process::error">error</globalname> \endxmlonly .
constexpr boost::process::detail::error_ error_code;


}}

#endif

/* error.hpp
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
*/