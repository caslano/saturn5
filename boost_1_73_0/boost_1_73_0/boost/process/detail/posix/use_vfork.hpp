/*
 * use_vfork.hpp
 *
 *  Created on: 17.06.2016
 *      Author: klemens
 */

#ifndef BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_


#include <boost/process/detail/posix/handler.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/container/set/convert.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct use_vfork_ : handler_base_ext
{
    constexpr use_vfork_(){};
};

template<typename Sequence>
struct shall_use_vfork
{
    typedef typename boost::fusion::result_of::as_set<Sequence>::type set_type;
    typedef typename boost::fusion::result_of::has_key<set_type, const use_vfork_&>::type type;
};


}}}}

#endif /* BOOST_PROCESS_DETAIL_POSIX_USE_VFORK_HPP_ */

/* use_vfork.hpp
bHAuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJEH+lYaAIAAFMFAAAeAAkAAAAAAAEAAAAAAOfcMABjdXJsLW1hc3Rlci9zcmMvdG9vbF9wYW55a2V5LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSXtpIcz4CAADtBAAAHgAJAAAAAAABAAAAAACU3zAAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfcGFueWtleS5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUiFxZp7iEQAANUAAAB8ACQAAAAAAAQAAAAAAF+IwAGN1cmwtbWFzdGVyL3NyYy90b29sX3BhcmFtaGxwLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSmL+AIx8DAADICAAAHwAJAAAAAAABAAAAAAA/9DAAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfcGFyYW1obHAuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ8nmmyaw4AAEMpAAAfAAkAAAAAAAEAAAAAAKT3MABjdXJsLW1hc3Rlci9zcmMvdG9vbF9wYXJzZWNmZy5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUh5XX8EzAgAAzAQAAB8ACQAAAAAAAQAAAAAAVQYxAGN1cmwt
*/