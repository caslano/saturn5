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
zCPWEluIA8RZIuQIdUQkEiOJGmIpsZ7YRRwlLhKRnDh7EhlEKbGQWEtsJQ4T54iQo5RFJBJjiRpiIbGW2ELsI04RrmPUI9GHCBnF/dExlMvfxm92ThGuNNoqoh+RR8wkFhNH/8G1Mh4mLhLx6Zxrh1HeQb4zxt+VxEJiLbGVOEqcJQIz2M+IbKKGWEZsIS4S4dezLYmxxGxiFbGeOEHsI84T3Sg/MpPz/jjqAMcSNcQ8Yi2xidhFnCXCszivE2OJSmIhsYLYShwmXNnkIfoQY4m5xNPEduIo4cph3YlBRB4xm1hl6GQ5qaed/H2AuEjEj+CamZhJLCbWE4XU4wE8QVwktlI/zW8gnZhHrCK2E/uI80T4SK4TiQyimJjJ9LNxFbGVOEycJRYb36thW2UTpyizFF2p7FO4jDhsDI9m/EG2J7ZhXCKOJIqJ2cQqYidxmDhHhI9hnYjpTLOU+Y5kmkojSFtMrCK2EweJi8Tag6Qzfhd2G0vZRDExk1hKrCV2EicYfwDPEX6HiBtZdmIoUUosJlYRW4l1zLdfNcNO6p9hNY56JYYSecRcIpIyVuAmYidxmLhINM/lnEgUEvOIp4ktxE7KPEoc4O+zhF8e82K5z5PWPo9yiYXEJmIncZgIzKfOiD7EUGIsMZNYSKwndhEHiVOEGs8yEX2IkUQlsYzYROwiAj/nOMOQAvIz386YSGQQNcRCYj2xjwgpZBsQGcR0YhmxhdhFHCTOEoFFLBsxlBhJzCZWEZuIg0TgBOqXyCCKiYXEWmIPcYq4SGxysswT2W7EUKKYWEisJdqzvIOo4+38fYLwKyYv0ZlIJDKI6cTMapYPB5F/Kx4kzhN+wzkuieYltBlEKn/n4WxiMbGW2EkcJdQkyiUSibHEbMND5ME9xAnCbzLLRAwlSonZxFpip5NlxH3EeSKwlHoh+hF5xExiFTGS5duOh4lzhKuMfZ1oQ6QSlUaQZxmWDmddcA9xlggpZ95EIpFHVBJziZ3EPPIexfOEXwX7G8PzKGctsZU4TJwnwo/TthLZxExiFbGVOEhcJCJPUF9EKlFMzCPWE7uI///7/7//xX8uYoJyhIIa1HdsRWVReXXF1KqCIvef1aVd5P02XbondE/oNqHLtOoe3br3NsdN79OrS3VxflVRYZeqotKi/OoiT478ysrqsTxGs7SEt+ElVIyfJL/h4In28Ur58mP1APVavjIdXlJQVVFdMaEmvn1mh/j0Sp7PUjKjpHxi/MCKskqeOVClwpRvKC9PMb4BnZ6RnZucmamsNCVJ6YOVleaQtKHJqfRVgnWal6T1NIedMtzLnMZbhjPSM+lPROg0H0kbmJ6WljyQZDOvr6TnpKWMtPL6S9qI5MyUwaOULW+Au4xkyjXTGrnTMlPJF63TAj1puYPSb0hLTU8aZJXd2CxjcHrmcCs9xDONO1nF6vRQ27LkZiZLjaVnWvMKs4+/Picl2bZsTWTcgMyU5MFmWlNzPla+CEmTic20ZpKWNiAl3coXJWmZSWm29YmWtJQhabLdrOWKcU+fbo2yymku4wYlD8gZYuZvIWnZqVnJI7PdY6x5xMq4rOyk7Jwseznxkj48y563pSdtcEpqsi29lXvfShuSkpZsL6O1e76ZSQOTzTpv455f8sCczJTsUXpB+ddWj7+invHGJhiQnkXZ1jzbmXWYm52cZdVte3N9ks20ju59NmuYbdm6ufNlpf7JqtfunjRjXx6cMsQ+vx6eOuye28Oe/icrvbt93Xua6Vbale5tQ6KV1kunkdEss7dO0zMz0/u4y0wZnpyeYz/OrnJvl+wcW96+kjYseZTs81beq911kZSVZa13P89xw/+GJqWk2dc=
*/