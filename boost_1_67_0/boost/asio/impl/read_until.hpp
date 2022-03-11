//
// impl/read_until.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_READ_UNTIL_HPP
#define BOOST_ASIO_IMPL_READ_UNTIL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  // Algorithm that finds a subsequence of equal values in a sequence. Returns
  // (iterator,true) if a full match was found, in which case the iterator
  // points to the beginning of the match. Returns (iterator,false) if a
  // partial match was found at the end of the first sequence, in which case
  // the iterator points to the beginning of the partial match. Returns
  // (last1,false) if no full or partial match was found.
  template <typename Iterator1, typename Iterator2>
  std::pair<Iterator1, bool> partial_search(
      Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
    for (Iterator1 iter1 = first1; iter1 != last1; ++iter1)
    {
      Iterator1 test_iter1 = iter1;
      Iterator2 test_iter2 = first2;
      for (;; ++test_iter1, ++test_iter2)
      {
        if (test_iter2 == last2)
          return std::make_pair(iter1, true);
        if (test_iter1 == last1)
        {
          if (test_iter2 != first2)
            return std::make_pair(iter1, false);
          else
            break;
        }
        if (*test_iter1 != *test_iter2)
          break;
      }
    }
    return std::make_pair(last1, false);
  }
} // namespace detail

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

template <typename SyncReadStream, typename DynamicBuffer_v1>
inline std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers, char delim,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers), delim, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    char delim, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  typename decay<DynamicBuffer_v1>::type b(
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers));

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v1::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers = b.data();
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    iterator iter = std::find(start_pos, end, delim);
    if (iter != end)
    {
      // Found a match. We're done.
      ec = boost::system::error_code();
      return iter - begin + 1;
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    b.commit(s.read_some(b.prepare(bytes_to_read), ec));
    if (ec)
      return 0;
  }
}

template <typename SyncReadStream, typename DynamicBuffer_v1>
inline std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers), delim, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  typename decay<DynamicBuffer_v1>::type b(
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers));

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v1::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers = b.data();
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    std::pair<iterator, bool> result = detail::partial_search(
        start_pos, end, delim.begin(), delim.end());
    if (result.first != end)
    {
      if (result.second)
      {
        // Full match. We're done.
        ec = boost::system::error_code();
        return result.first - begin + delim.length();
      }
      else
      {
        // Partial match. Next search needs to start from beginning of match.
        search_position = result.first - begin;
      }
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    b.commit(s.read_some(b.prepare(bytes_to_read), ec));
    if (ec)
      return 0;
  }
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename SyncReadStream, typename DynamicBuffer_v1>
inline std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    const boost::regex& expr,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers), expr, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    const boost::regex& expr, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  typename decay<DynamicBuffer_v1>::type b(
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers));

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v1::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers = b.data();
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    boost::match_results<iterator,
      typename std::vector<boost::sub_match<iterator> >::allocator_type>
        match_results;
    if (regex_search(start_pos, end, match_results, expr,
          boost::match_default | boost::match_partial))
    {
      if (match_results[0].matched)
      {
        // Full match. We're done.
        ec = boost::system::error_code();
        return match_results[0].second - begin;
      }
      else
      {
        // Partial match. Next search needs to start from beginning of match.
        search_position = match_results[0].first - begin;
      }
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    b.commit(s.read_some(b.prepare(bytes_to_read), ec));
    if (ec)
      return 0;
  }
}

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename SyncReadStream,
    typename DynamicBuffer_v1, typename MatchCondition>
inline std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    MatchCondition match_condition,
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      match_condition, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream,
    typename DynamicBuffer_v1, typename MatchCondition>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    MatchCondition match_condition, boost::system::error_code& ec,
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  typename decay<DynamicBuffer_v1>::type b(
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers));

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v1::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers = b.data();
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    std::pair<iterator, bool> result = match_condition(start_pos, end);
    if (result.second)
    {
      // Full match. We're done.
      ec = boost::system::error_code();
      return result.first - begin;
    }
    else if (result.first != end)
    {
      // Partial match. Next search needs to start from beginning of match.
      search_position = result.first - begin;
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    b.commit(s.read_some(b.prepare(bytes_to_read), ec));
    if (ec)
      return 0;
  }
}

#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename SyncReadStream, typename Allocator>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), delim);
}

template <typename SyncReadStream, typename Allocator>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim,
    boost::system::error_code& ec)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), delim, ec);
}

template <typename SyncReadStream, typename Allocator>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_STRING_VIEW_PARAM delim)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), delim);
}

template <typename SyncReadStream, typename Allocator>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_STRING_VIEW_PARAM delim, boost::system::error_code& ec)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), delim, ec);
}

#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename SyncReadStream, typename Allocator>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), expr);
}

template <typename SyncReadStream, typename Allocator>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    boost::system::error_code& ec)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), expr, ec);
}

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename SyncReadStream, typename Allocator, typename MatchCondition>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, MatchCondition match_condition,
    typename enable_if<is_match_condition<MatchCondition>::value>::type*)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), match_condition);
}

template <typename SyncReadStream, typename Allocator, typename MatchCondition>
inline std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    MatchCondition match_condition, boost::system::error_code& ec,
    typename enable_if<is_match_condition<MatchCondition>::value>::type*)
{
  return read_until(s, basic_streambuf_ref<Allocator>(b), match_condition, ec);
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

template <typename SyncReadStream, typename DynamicBuffer_v2>
inline std::size_t read_until(SyncReadStream& s,
    DynamicBuffer_v2 buffers, char delim,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers), delim, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    char delim, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  DynamicBuffer_v2& b = buffers;

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v2::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers =
      const_cast<const DynamicBuffer_v2&>(b).data(0, b.size());
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    iterator iter = std::find(start_pos, end, delim);
    if (iter != end)
    {
      // Found a match. We're done.
      ec = boost::system::error_code();
      return iter - begin + 1;
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    std::size_t pos = b.size();
    b.grow(bytes_to_read);
    std::size_t bytes_transferred = s.read_some(b.data(pos, bytes_to_read), ec);
    b.shrink(bytes_to_read - bytes_transferred);
    if (ec)
      return 0;
  }
}

template <typename SyncReadStream, typename DynamicBuffer_v2>
inline std::size_t read_until(SyncReadStream& s,
    DynamicBuffer_v2 buffers, BOOST_ASIO_STRING_VIEW_PARAM delim,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers), delim, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  DynamicBuffer_v2& b = buffers;

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v2::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers =
      const_cast<const DynamicBuffer_v2&>(b).data(0, b.size());
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    std::pair<iterator, bool> result = detail::partial_search(
        start_pos, end, delim.begin(), delim.end());
    if (result.first != end)
    {
      if (result.second)
      {
        // Full match. We're done.
        ec = boost::system::error_code();
        return result.first - begin + delim.length();
      }
      else
      {
        // Partial match. Next search needs to start from beginning of match.
        search_position = result.first - begin;
      }
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    std::size_t pos = b.size();
    b.grow(bytes_to_read);
    std::size_t bytes_transferred = s.read_some(b.data(pos, bytes_to_read), ec);
    b.shrink(bytes_to_read - bytes_transferred);
    if (ec)
      return 0;
  }
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename SyncReadStream, typename DynamicBuffer_v2>
inline std::size_t read_until(SyncReadStream& s,
    DynamicBuffer_v2 buffers, const boost::regex& expr,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers), expr, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    const boost::regex& expr, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  DynamicBuffer_v2& b = buffers;

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v2::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers =
      const_cast<const DynamicBuffer_v2&>(b).data(0, b.size());
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    boost::match_results<iterator,
      typename std::vector<boost::sub_match<iterator> >::allocator_type>
        match_results;
    if (regex_search(start_pos, end, match_results, expr,
          boost::match_default | boost::match_partial))
    {
      if (match_results[0].matched)
      {
        // Full match. We're done.
        ec = boost::system::error_code();
        return match_results[0].second - begin;
      }
      else
      {
        // Partial match. Next search needs to start from beginning of match.
        search_position = match_results[0].first - begin;
      }
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    std::size_t pos = b.size();
    b.grow(bytes_to_read);
    std::size_t bytes_transferred = s.read_some(b.data(pos, bytes_to_read), ec);
    b.shrink(bytes_to_read - bytes_transferred);
    if (ec)
      return 0;
  }
}

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename SyncReadStream,
    typename DynamicBuffer_v2, typename MatchCondition>
inline std::size_t read_until(SyncReadStream& s,
    DynamicBuffer_v2 buffers, MatchCondition match_condition,
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_until(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      match_condition, ec);
  boost::asio::detail::throw_error(ec, "read_until");
  return bytes_transferred;
}

template <typename SyncReadStream,
    typename DynamicBuffer_v2, typename MatchCondition>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    MatchCondition match_condition, boost::system::error_code& ec,
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  DynamicBuffer_v2& b = buffers;

  std::size_t search_position = 0;
  for (;;)
  {
    // Determine the range of the data to be searched.
    typedef typename DynamicBuffer_v2::const_buffers_type buffers_type;
    typedef buffers_iterator<buffers_type> iterator;
    buffers_type data_buffers =
      const_cast<const DynamicBuffer_v2&>(b).data(0, b.size());
    iterator begin = iterator::begin(data_buffers);
    iterator start_pos = begin + search_position;
    iterator end = iterator::end(data_buffers);

    // Look for a match.
    std::pair<iterator, bool> result = match_condition(start_pos, end);
    if (result.second)
    {
      // Full match. We're done.
      ec = boost::system::error_code();
      return result.first - begin;
    }
    else if (result.first != end)
    {
      // Partial match. Next search needs to start from beginning of match.
      search_position = result.first - begin;
    }
    else
    {
      // No match. Next search can start with the new data.
      search_position = end - begin;
    }

    // Check if buffer is full.
    if (b.size() == b.max_size())
    {
      ec = error::not_found;
      return 0;
    }

    // Need more data.
    std::size_t bytes_to_read = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(65536, b.max_size() - b.size()));
    std::size_t pos = b.size();
    b.grow(bytes_to_read);
    std::size_t bytes_transferred = s.read_some(b.data(pos, bytes_to_read), ec);
    b.shrink(bytes_to_read - bytes_transferred);
    if (ec)
      return 0;
  }
}

#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  class read_until_delim_op_v1
  {
  public:
    template <typename BufferSequence>
    read_until_delim_op_v1(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        char delim, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        delim_(delim),
        start_(0),
        search_position_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_delim_op_v1(const read_until_delim_op_v1& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        delim_(other.delim_),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(other.handler_)
    {
    }

    read_until_delim_op_v1(read_until_delim_op_v1&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(other.buffers_)),
        delim_(other.delim_),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t bytes_to_read;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v1::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers = buffers_.data();
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            iterator iter = std::find(start_pos, end, delim_);
            if (iter != end)
            {
              // Found a match. We're done.
              search_position_ = iter - begin + 1;
              bytes_to_read = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read = 0;
            }

            // Need to read some more data.
            else
            {
              // Next search can start with the new data.
              search_position_ = end - begin;
              bytes_to_read = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read == 0)
            break;

          // Start a new asynchronous read op_v1eration to obtain more data.
          stream_.async_read_some(buffers_.prepare(bytes_to_read),
              BOOST_ASIO_MOVE_CAST(read_until_delim_op_v1)(*this));
          return; default:
          buffers_.commit(bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v1 buffers_;
    char delim_;
    int start_;
    std::size_t search_position_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_delim_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_delim_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_delim_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_delim_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_delim_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_delim_v1
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_delim_v1(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v1>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
        char delim) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_delim_op_v1<AsyncReadStream,
        typename decay<DynamicBuffer_v1>::type,
          typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
            delim, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_delim_op_v1<AsyncReadStream,
      DynamicBuffer_v1, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_delim_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_delim_op_v1<AsyncReadStream,
      DynamicBuffer_v1, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_delim_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    char delim, BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_delim_v1<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers), delim);
}

namespace detail
{
  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  class read_until_delim_string_op_v1
  {
  public:
    template <typename BufferSequence>
    read_until_delim_string_op_v1(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        const std::string& delim, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        delim_(delim),
        start_(0),
        search_position_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_delim_string_op_v1(const read_until_delim_string_op_v1& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        delim_(other.delim_),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(other.handler_)
    {
    }

    read_until_delim_string_op_v1(read_until_delim_string_op_v1&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(other.buffers_)),
        delim_(BOOST_ASIO_MOVE_CAST(std::string)(other.delim_)),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t bytes_to_read;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v1::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers = buffers_.data();
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            std::pair<iterator, bool> result = detail::partial_search(
                start_pos, end, delim_.begin(), delim_.end());
            if (result.first != end && result.second)
            {
              // Full match. We're done.
              search_position_ = result.first - begin + delim_.length();
              bytes_to_read = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read = 0;
            }

            // Need to read some more data.
            else
            {
              if (result.first != end)
              {
                // Partial match. Next search needs to start from beginning of
                // match.
                search_position_ = result.first - begin;
              }
              else
              {
                // Next search can start with the new data.
                search_position_ = end - begin;
              }

              bytes_to_read = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read == 0)
            break;

          // Start a new asynchronous read op_v1eration to obtain more data.
          stream_.async_read_some(buffers_.prepare(bytes_to_read),
              BOOST_ASIO_MOVE_CAST(read_until_delim_string_op_v1)(*this));
          return; default:
          buffers_.commit(bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v1 buffers_;
    std::string delim_;
    int start_;
    std::size_t search_position_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_delim_string_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_delim_string_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_delim_string_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_delim_string_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_delim_string_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_delim_string_v1
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_delim_string_v1(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v1>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
        const std::string& delim) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_delim_string_op_v1<AsyncReadStream,
        typename decay<DynamicBuffer_v1>::type,
          typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
            delim, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_delim_string_op_v1<AsyncReadStream,
      DynamicBuffer_v1, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_delim_string_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_delim_string_op_v1<AsyncReadStream,
      DynamicBuffer_v1, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_delim_string_op_v1<AsyncReadStream,
        DynamicBuffer_v1, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_delim_string_v1<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      static_cast<std::string>(delim));
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename RegEx, typename ReadHandler>
  class read_until_expr_op_v1
  {
  public:
    template <typename BufferSequence>
    read_until_expr_op_v1(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        const boost::regex& expr, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        expr_(expr),
        start_(0),
        search_position_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_expr_op_v1(const read_until_expr_op_v1& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        expr_(other.expr_),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(other.handler_)
    {
    }

    read_until_expr_op_v1(read_until_expr_op_v1&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(other.buffers_)),
        expr_(other.expr_),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t bytes_to_read;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v1::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers = buffers_.data();
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            boost::match_results<iterator,
              typename std::vector<boost::sub_match<iterator> >::allocator_type>
                match_results;
            bool match = regex_search(start_pos, end, match_results, expr_,
                boost::match_default | boost::match_partial);
            if (match && match_results[0].matched)
            {
              // Full match. We're done.
              search_position_ = match_results[0].second - begin;
              bytes_to_read = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read = 0;
            }

            // Need to read some more data.
            else
            {
              if (match)
              {
                // Partial match. Next search needs to start from beginning of
                // match.
                search_position_ = match_results[0].first - begin;
              }
              else
              {
                // Next search can start with the new data.
                search_position_ = end - begin;
              }

              bytes_to_read = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read == 0)
            break;

          // Start a new asynchronous read op_v1eration to obtain more data.
          stream_.async_read_some(buffers_.prepare(bytes_to_read),
              BOOST_ASIO_MOVE_CAST(read_until_expr_op_v1)(*this));
          return; default:
          buffers_.commit(bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v1 buffers_;
    RegEx expr_;
    int start_;
    std::size_t search_position_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename RegEx, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_expr_op_v1<AsyncReadStream,
        DynamicBuffer_v1, RegEx, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename RegEx, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_expr_op_v1<AsyncReadStream,
        DynamicBuffer_v1, RegEx, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename RegEx, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_expr_op_v1<AsyncReadStream,
        DynamicBuffer_v1, RegEx, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename RegEx, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_expr_op_v1<AsyncReadStream,
        DynamicBuffer_v1, RegEx, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename RegEx, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_expr_op_v1<AsyncReadStream,
        DynamicBuffer_v1, RegEx, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_expr_v1
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_expr_v1(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v1, typename RegEx>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers, const RegEx& expr) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_expr_op_v1<AsyncReadStream,
        typename decay<DynamicBuffer_v1>::type,
          RegEx, typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
            expr, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename RegEx, typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_expr_op_v1<AsyncReadStream,
      DynamicBuffer_v1, RegEx, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_expr_op_v1<AsyncReadStream,
        DynamicBuffer_v1, RegEx, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename RegEx, typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_expr_op_v1<AsyncReadStream,
      DynamicBuffer_v1, RegEx, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_expr_op_v1<AsyncReadStream,
        DynamicBuffer_v1, RegEx, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_expr_v1<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers), expr);
}

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename MatchCondition, typename ReadHandler>
  class read_until_match_op_v1
  {
  public:
    template <typename BufferSequence>
    read_until_match_op_v1(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        MatchCondition match_condition, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        match_condition_(match_condition),
        start_(0),
        search_position_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_match_op_v1(const read_until_match_op_v1& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        match_condition_(other.match_condition_),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(other.handler_)
    {
    }

    read_until_match_op_v1(read_until_match_op_v1&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(other.buffers_)),
        match_condition_(other.match_condition_),
        start_(other.start_),
        search_position_(other.search_position_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t bytes_to_read;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v1::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers = buffers_.data();
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            std::pair<iterator, bool> result = match_condition_(start_pos, end);
            if (result.second)
            {
              // Full match. We're done.
              search_position_ = result.first - begin;
              bytes_to_read = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read = 0;
            }

            // Need to read some more data.
            else
            {
              if (result.first != end)
              {
                // Partial match. Next search needs to start from beginning of
                // match.
                search_position_ = result.first - begin;
              }
              else
              {
                // Next search can start with the new data.
                search_position_ = end - begin;
              }

              bytes_to_read = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read == 0)
            break;

          // Start a new asynchronous read op_v1eration to obtain more data.
          stream_.async_read_some(buffers_.prepare(bytes_to_read),
              BOOST_ASIO_MOVE_CAST(read_until_match_op_v1)(*this));
          return; default:
          buffers_.commit(bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v1 buffers_;
    MatchCondition match_condition_;
    int start_;
    std::size_t search_position_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename MatchCondition, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_match_op_v1<AsyncReadStream, DynamicBuffer_v1,
        MatchCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename MatchCondition, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_match_op_v1<AsyncReadStream, DynamicBuffer_v1,
        MatchCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename MatchCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_match_op_v1<AsyncReadStream, DynamicBuffer_v1,
        MatchCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename MatchCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_match_op_v1<AsyncReadStream, DynamicBuffer_v1,
        MatchCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename MatchCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_match_op_v1<AsyncReadStream, DynamicBuffer_v1,
      MatchCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_match_v1
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_match_v1(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler,
        typename DynamicBuffer_v1, typename MatchCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
        MatchCondition match_condition) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_match_op_v1<AsyncReadStream,
        typename decay<DynamicBuffer_v1>::type,
          MatchCondition, typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
            match_condition, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename MatchCondition, typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_match_op_v1<AsyncReadStream,
      DynamicBuffer_v1, MatchCondition, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_match_op_v1<AsyncReadStream,
        DynamicBuffer_v1, MatchCondition, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename MatchCondition, typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_match_op_v1<AsyncReadStream,
      DynamicBuffer_v1, MatchCondition, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_match_op_v1<AsyncReadStream,
        DynamicBuffer_v1, MatchCondition, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream,
    typename DynamicBuffer_v1, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    MatchCondition match_condition, BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_match_v1<AsyncReadStream>(s), handler,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers), match_condition);
}

#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    char delim, BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_read_until(s, basic_streambuf_ref<Allocator>(b),
      delim, BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_read_until(s, basic_streambuf_ref<Allocator>(b),
      delim, BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_read_until(s, basic_streambuf_ref<Allocator>(b),
      expr, BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

template <typename AsyncReadStream, typename Allocator, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    MatchCondition match_condition, BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<is_match_condition<MatchCondition>::value>::type*)
{
  return async_read_until(s, basic_streambuf_ref<Allocator>(b),
      match_condition, BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  class read_until_delim_op_v2
  {
  public:
    template <typename BufferSequence>
    read_until_delim_op_v2(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        char delim, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        delim_(delim),
        start_(0),
        search_position_(0),
        bytes_to_read_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_delim_op_v2(const read_until_delim_op_v2& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        delim_(other.delim_),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(other.handler_)
    {
    }

    read_until_delim_op_v2(read_until_delim_op_v2&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(other.buffers_)),
        delim_(other.delim_),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t pos;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v2::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers =
              const_cast<const DynamicBuffer_v2&>(buffers_).data(
                  0, buffers_.size());
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            iterator iter = std::find(start_pos, end, delim_);
            if (iter != end)
            {
              // Found a match. We're done.
              search_position_ = iter - begin + 1;
              bytes_to_read_ = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read_ = 0;
            }

            // Need to read some more data.
            else
            {
              // Next search can start with the new data.
              search_position_ = end - begin;
              bytes_to_read_ = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read_ == 0)
            break;

          // Start a new asynchronous read op_v2eration to obtain more data.
          pos = buffers_.size();
          buffers_.grow(bytes_to_read_);
          stream_.async_read_some(buffers_.data(pos, bytes_to_read_),
              BOOST_ASIO_MOVE_CAST(read_until_delim_op_v2)(*this));
          return; default:
          buffers_.shrink(bytes_to_read_ - bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v2 buffers_;
    char delim_;
    int start_;
    std::size_t search_position_;
    std::size_t bytes_to_read_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_delim_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_delim_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_delim_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_delim_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_delim_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_delim_v2
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_delim_v2(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v2>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v2) buffers, char delim) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_delim_op_v2<AsyncReadStream,
        typename decay<DynamicBuffer_v2>::type,
          typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
            delim, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_delim_op_v2<AsyncReadStream,
      DynamicBuffer_v2, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_delim_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_delim_op_v2<AsyncReadStream,
      DynamicBuffer_v2, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_delim_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    char delim, BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_delim_v2<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers), delim);
}

namespace detail
{
  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  class read_until_delim_string_op_v2
  {
  public:
    template <typename BufferSequence>
    read_until_delim_string_op_v2(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        const std::string& delim, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        delim_(delim),
        start_(0),
        search_position_(0),
        bytes_to_read_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_delim_string_op_v2(const read_until_delim_string_op_v2& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        delim_(other.delim_),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(other.handler_)
    {
    }

    read_until_delim_string_op_v2(read_until_delim_string_op_v2&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(other.buffers_)),
        delim_(BOOST_ASIO_MOVE_CAST(std::string)(other.delim_)),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t pos;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v2::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers =
              const_cast<const DynamicBuffer_v2&>(buffers_).data(
                  0, buffers_.size());
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            std::pair<iterator, bool> result = detail::partial_search(
                start_pos, end, delim_.begin(), delim_.end());
            if (result.first != end && result.second)
            {
              // Full match. We're done.
              search_position_ = result.first - begin + delim_.length();
              bytes_to_read_ = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read_ = 0;
            }

            // Need to read some more data.
            else
            {
              if (result.first != end)
              {
                // Partial match. Next search needs to start from beginning of
                // match.
                search_position_ = result.first - begin;
              }
              else
              {
                // Next search can start with the new data.
                search_position_ = end - begin;
              }

              bytes_to_read_ = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read_ == 0)
            break;

          // Start a new asynchronous read op_v2eration to obtain more data.
          pos = buffers_.size();
          buffers_.grow(bytes_to_read_);
          stream_.async_read_some(buffers_.data(pos, bytes_to_read_),
              BOOST_ASIO_MOVE_CAST(read_until_delim_string_op_v2)(*this));
          return; default:
          buffers_.shrink(bytes_to_read_ - bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v2 buffers_;
    std::string delim_;
    int start_;
    std::size_t search_position_;
    std::size_t bytes_to_read_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_delim_string_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_delim_string_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_delim_string_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_delim_string_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_delim_string_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_delim_string_v2
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_delim_string_v2(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v2>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v2) buffers,
        const std::string& delim) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_delim_string_op_v2<AsyncReadStream,
        typename decay<DynamicBuffer_v2>::type,
          typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
            delim, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_delim_string_op_v2<AsyncReadStream,
      DynamicBuffer_v2, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_delim_string_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_delim_string_op_v2<AsyncReadStream,
      DynamicBuffer_v2, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_delim_string_op_v2<AsyncReadStream,
        DynamicBuffer_v2, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream,
    typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    DynamicBuffer_v2 buffers, BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_delim_string_v2<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      static_cast<std::string>(delim));
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename RegEx, typename ReadHandler>
  class read_until_expr_op_v2
  {
  public:
    template <typename BufferSequence>
    read_until_expr_op_v2(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        const boost::regex& expr, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        expr_(expr),
        start_(0),
        search_position_(0),
        bytes_to_read_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_expr_op_v2(const read_until_expr_op_v2& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        expr_(other.expr_),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(other.handler_)
    {
    }

    read_until_expr_op_v2(read_until_expr_op_v2&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(other.buffers_)),
        expr_(other.expr_),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t pos;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v2::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers =
              const_cast<const DynamicBuffer_v2&>(buffers_).data(
                  0, buffers_.size());
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            boost::match_results<iterator,
              typename std::vector<boost::sub_match<iterator> >::allocator_type>
                match_results;
            bool match = regex_search(start_pos, end, match_results, expr_,
                boost::match_default | boost::match_partial);
            if (match && match_results[0].matched)
            {
              // Full match. We're done.
              search_position_ = match_results[0].second - begin;
              bytes_to_read_ = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read_ = 0;
            }

            // Need to read some more data.
            else
            {
              if (match)
              {
                // Partial match. Next search needs to start from beginning of
                // match.
                search_position_ = match_results[0].first - begin;
              }
              else
              {
                // Next search can start with the new data.
                search_position_ = end - begin;
              }

              bytes_to_read_ = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read_ == 0)
            break;

          // Start a new asynchronous read op_v2eration to obtain more data.
          pos = buffers_.size();
          buffers_.grow(bytes_to_read_);
          stream_.async_read_some(buffers_.data(pos, bytes_to_read_),
              BOOST_ASIO_MOVE_CAST(read_until_expr_op_v2)(*this));
          return; default:
          buffers_.shrink(bytes_to_read_ - bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v2 buffers_;
    RegEx expr_;
    int start_;
    std::size_t search_position_;
    std::size_t bytes_to_read_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename RegEx, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_expr_op_v2<AsyncReadStream,
        DynamicBuffer_v2, RegEx, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename RegEx, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_expr_op_v2<AsyncReadStream,
        DynamicBuffer_v2, RegEx, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename RegEx, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_expr_op_v2<AsyncReadStream,
        DynamicBuffer_v2, RegEx, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename RegEx, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_expr_op_v2<AsyncReadStream,
        DynamicBuffer_v2, RegEx, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename RegEx, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_expr_op_v2<AsyncReadStream,
        DynamicBuffer_v2, RegEx, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_expr_v2
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_expr_v2(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v2, typename RegEx>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v2) buffers,
        const RegEx& expr) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_expr_op_v2<AsyncReadStream,
        typename decay<DynamicBuffer_v2>::type,
          RegEx, typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
            expr, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename RegEx, typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_expr_op_v2<AsyncReadStream,
      DynamicBuffer_v2, RegEx, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_expr_op_v2<AsyncReadStream,
        DynamicBuffer_v2, RegEx, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename RegEx, typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_expr_op_v2<AsyncReadStream,
      DynamicBuffer_v2, RegEx, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_expr_op_v2<AsyncReadStream,
        DynamicBuffer_v2, RegEx, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    const boost::regex& expr, BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_expr_v2<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers), expr);
}

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename MatchCondition, typename ReadHandler>
  class read_until_match_op_v2
  {
  public:
    template <typename BufferSequence>
    read_until_match_op_v2(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        MatchCondition match_condition, ReadHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        match_condition_(match_condition),
        start_(0),
        search_position_(0),
        bytes_to_read_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_until_match_op_v2(const read_until_match_op_v2& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        match_condition_(other.match_condition_),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(other.handler_)
    {
    }

    read_until_match_op_v2(read_until_match_op_v2&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(other.buffers_)),
        match_condition_(other.match_condition_),
        start_(other.start_),
        search_position_(other.search_position_),
        bytes_to_read_(other.bytes_to_read_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      const std::size_t not_found = (std::numeric_limits<std::size_t>::max)();
      std::size_t pos;
      switch (start_ = start)
      {
      case 1:
        for (;;)
        {
          {
            // Determine the range of the data to be searched.
            typedef typename DynamicBuffer_v2::const_buffers_type
              buffers_type;
            typedef buffers_iterator<buffers_type> iterator;
            buffers_type data_buffers =
              const_cast<const DynamicBuffer_v2&>(buffers_).data(
                  0, buffers_.size());
            iterator begin = iterator::begin(data_buffers);
            iterator start_pos = begin + search_position_;
            iterator end = iterator::end(data_buffers);

            // Look for a match.
            std::pair<iterator, bool> result = match_condition_(start_pos, end);
            if (result.second)
            {
              // Full match. We're done.
              search_position_ = result.first - begin;
              bytes_to_read_ = 0;
            }

            // No match yet. Check if buffer is full.
            else if (buffers_.size() == buffers_.max_size())
            {
              search_position_ = not_found;
              bytes_to_read_ = 0;
            }

            // Need to read some more data.
            else
            {
              if (result.first != end)
              {
                // Partial match. Next search needs to start from beginning of
                // match.
                search_position_ = result.first - begin;
              }
              else
              {
                // Next search can start with the new data.
                search_position_ = end - begin;
              }

              bytes_to_read_ = std::min<std::size_t>(
                    std::max<std::size_t>(512,
                      buffers_.capacity() - buffers_.size()),
                    std::min<std::size_t>(65536,
                      buffers_.max_size() - buffers_.size()));
            }
          }

          // Check if we're done.
          if (!start && bytes_to_read_ == 0)
            break;

          // Start a new asynchronous read op_v2eration to obtain more data.
          pos = buffers_.size();
          buffers_.grow(bytes_to_read_);
          stream_.async_read_some(buffers_.data(pos, bytes_to_read_),
              BOOST_ASIO_MOVE_CAST(read_until_match_op_v2)(*this));
          return; default:
          buffers_.shrink(bytes_to_read_ - bytes_transferred);
          if (ec || bytes_transferred == 0)
            break;
        }

        const boost::system::error_code result_ec =
          (search_position_ == not_found)
          ? error::not_found : ec;

        const std::size_t result_n =
          (ec || search_position_ == not_found)
          ? 0 : search_position_;

        handler_(result_ec, result_n);
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v2 buffers_;
    MatchCondition match_condition_;
    int start_;
    std::size_t search_position_;
    std::size_t bytes_to_read_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename MatchCondition, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_until_match_op_v2<AsyncReadStream, DynamicBuffer_v2,
        MatchCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename MatchCondition, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_until_match_op_v2<AsyncReadStream, DynamicBuffer_v2,
        MatchCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename MatchCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_until_match_op_v2<AsyncReadStream, DynamicBuffer_v2,
        MatchCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename MatchCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      read_until_match_op_v2<AsyncReadStream, DynamicBuffer_v2,
        MatchCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename MatchCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_until_match_op_v2<AsyncReadStream, DynamicBuffer_v2,
      MatchCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_until_match_v2
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_until_match_v2(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler,
        typename DynamicBuffer_v2, typename MatchCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v2) buffers,
        MatchCondition match_condition) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      read_until_match_op_v2<AsyncReadStream,
        typename decay<DynamicBuffer_v2>::type,
          MatchCondition, typename decay<ReadHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
            match_condition, handler2.value)(boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename MatchCondition, typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_until_match_op_v2<AsyncReadStream,
      DynamicBuffer_v2, MatchCondition, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_until_match_op_v2<AsyncReadStream,
        DynamicBuffer_v2, MatchCondition, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename MatchCondition, typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_until_match_op_v2<AsyncReadStream,
      DynamicBuffer_v2, MatchCondition, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_until_match_op_v2<AsyncReadStream,
        DynamicBuffer_v2, MatchCondition, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream,
    typename DynamicBuffer_v2, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    MatchCondition match_condition, BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_until_match_v2<AsyncReadStream>(s), handler,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers), match_condition);
}

#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_READ_UNTIL_HPP

/* read_until.hpp
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
*/