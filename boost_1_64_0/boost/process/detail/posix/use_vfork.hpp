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
hZ4gazddRlIL6xDlaQuZT905pVd4/C8+u8lzj076lWpjMHX66icBn13ymCAh4Piniw0rHCwpidRghtl3bmfly7FPDPjlMZOzQV4simb5IWBHyDxxZRFdlfNIov/wB6Pmepv0MXxhCC4Mu1ToPx7PzRUJ4b04K9658CR3HnW71PY35k7i4I7o29amJCkv5ICtQqb/nVxonN+kMuSMvM6pRClVEKB8TFbwBtmmGIbCFSOds6PUyi1HWuVA4eIo0BMM4xnLcxEIEvqFBKJhA4PsLQslibjznCJPUQEwfi7xAHjWO2otZGsNXEA5kOMg7SL8AtfTer6Ft5MtFfwRvfoveOCyKZ6RzIeqNXKtaJ4dd60W9/vyL5LyFgLwrnASwtWhqoNqsdzSudAKJFFMO5/0VHVrMuMHTIehZGUk7/WJlNuN9eCLhBA1ciA8C2OASSUIcm8LdhAy9Enmuoq3ExWEVHtHp0GzgEu8UC/rh8sil+7cq0jUeWXaPrWmiyOeRVXeiiIEozn4HjJzLk411/EY4L7VbS87eWrvc9t59ePvVYuoxSxIw/o7dJyLHA==
*/