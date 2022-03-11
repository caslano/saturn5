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
    constexpr throw_on_error_() {};

    template <class Executor>
    void on_error(Executor&, const std::error_code & ec) const
    {
        throw process_error(ec, "process creation failed");
    }

    const throw_on_error_ &operator()() const {return *this;}
};

struct ignore_error_ : ::boost::process::detail::api::handler_base_ext
{
    constexpr ignore_error_() {};
};

struct set_on_error : ::boost::process::detail::api::handler_base_ext
{
    set_on_error(const set_on_error&) = default;
    explicit set_on_error(std::error_code &ec) : ec_(ec) {}

    template <class Executor>
    void on_error(Executor&, const std::error_code & ec) const
    {
        ec_ = ec;
    }

private:
    std::error_code &ec_;
};

struct error_
{
    constexpr error_() {}
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