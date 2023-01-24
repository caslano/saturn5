// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_
#define BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_

#include <boost/process/detail/windows/handler.hpp>
#include <type_traits>

namespace boost { namespace process { namespace detail { namespace windows {

struct require_io_context {};

struct async_handler : handler_base_ext, require_io_context
{
};

template<typename T>
struct is_async_handler :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<T&> :  std::is_base_of<async_handler, T> {};
template<typename T>
struct is_async_handler<const T&> :  std::is_base_of<async_handler, T> {};

template<typename T>
struct does_require_io_context : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<T&> : std::is_base_of<require_io_context, T> {};

template<typename T>
struct does_require_io_context<const T&> : std::is_base_of<require_io_context, T> {};


}}}}

#endif /* BOOST_PROCESS_WINDOWS_ASYNC_HANDLER_HPP_ */

/* async_handler.hpp
3NzrL1JRtaHkUK+Ivpzcvm7cWv1zogW7xH3zjGDuBtWJ8o6KBtvvy3mOdgL1ifWf985zZlcbdOoaLcs38nLm3L0NL+qhKudVnP5CH5aEsKsz37z1Zh269D1s8FWFA+1y54UhT1FgFFRji942xr2t+BZDbQRSommWV60yGBwAgQPndLbsEbbtQx2NTg6PbJGASkWALgfSOAGJJ/+8tmbbDlPtBCMdcuyykDn7M71AUDkZr+S1CcaIyTPyqh2yl83l6wgHP5kYzok0hgBAaDHaXc9uevcQa+AEcN2vPaCSfDkf2pVyC5DgQVd8VkSeIpG2E8guw1dhelFdhkjfDlNRJCD2yyESoPMI8y943rNamsxgfkaSgZQe550aHhGRs8WLrA/A0ocw8IbHY+jgeQ6EY8BuG8kw0qF6vXXss4WEPSPsHiHvk0cXaZE39aZIfPrKZGSfKs13JPLl36P82tivVp//K5qz/fdi/L+J+EdJD3d3J8d/JXoh7L/34sEiNvEkr17/5KZBxQ9m/EBorcPGoOf/+ynigP5n/F9Mf6Yyn0v5eje0bQZE/+UVuLQ2Q3koPYi5XgU9NpOsbUI5XyGT30ZIRfQiZq1ooqsysUih2EbRan3wI+55fbNnuyjsxlNnjM5GK13B0nUqE3YBXne7EIVlum21QQJOM9gC70d0lp7o9wsDPr+EFGfVsBTjMV5rYkrTjkKK52zahJ7K
*/