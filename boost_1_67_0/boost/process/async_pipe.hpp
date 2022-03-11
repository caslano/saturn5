// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_ASYNC_PIPE_HPP
#define BOOST_PROCESS_ASYNC_PIPE_HPP

#include <boost/config.hpp>
#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/async_pipe.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/async_pipe.hpp>
#endif

namespace boost { namespace process {


#if defined(BOOST_PROCESS_DOXYGEN)


/** Class implementing and asnychronous I/O-Object for use with boost.asio.
 *  It is based on the corresponding I/O Object, that is either boost::asio::windows::stream_handle or
 *  boost::asio::posix::stream_descriptor.
 *
 *  It can be used directly with boost::asio::async_read or async_write.
 *
 * \note The object is copyable, but that does invoke a handle duplicate.
 */
class async_pipe
{
public:
    /** Typedef for the native handle representation.
     * \note This is the handle on the system, not the boost.asio class.
     *
     */
    typedef platform_specific native_handle_type;
    /** Typedef for the handle representation of boost.asio.
     *
     */
    typedef platform_specific handle_type;

    typedef typename handle_type::executor_type executor_type;

    /** Construct a new async_pipe, does automatically open the pipe.
     * Initializes source and sink with the same io_context.
     * @note Windows creates a named pipe here, where the name is automatically generated.
     */
    inline async_pipe(boost::asio::io_context & ios);

    /** Construct a new async_pipe, does automatically open the pipe.
     * @note Windows creates a named pipe here, where the name is automatically generated.
     */
    inline async_pipe(boost::asio::io_context & ios_source,
                      boost::asio::io_context & ios_sink);

    /** Construct a new async_pipe, does automatically open.
     * Initializes source and sink with the same io_context.
     *
     * @note Windows restricts possible names.
     */
    inline async_pipe(boost::asio::io_context & ios, const std::string & name);


    /** Construct a new async_pipe, does automatically open.
     *
     * @note Windows restricts possible names.
     */
    inline async_pipe(boost::asio::io_context & ios_source,
                      boost::asio::io_context & ios_sink, const std::string & name);

    /** Copy-Constructor of the async pipe.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    async_pipe(const async_pipe& lhs);

    /** Move-Constructor of the async pipe.
     */
    async_pipe(async_pipe&& lhs);

    /** Construct the async-pipe from a pipe.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    template<class CharT, class Traits = std::char_traits<CharT>>
    explicit async_pipe(boost::asio::io_context & ios, const basic_pipe<CharT, Traits> & p);

    /** Construct the async-pipe from a pipe, with two different io_context objects.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    template<class CharT, class Traits = std::char_traits<CharT>>
    explicit async_pipe(boost::asio::io_context & ios_source,
                        boost::asio::io_context & ios_sink,
                        const basic_pipe<CharT, Traits> & p);


    /** Assign a basic_pipe.
     * @note Windows requires a named pipe for this, if a the wrong type is used an exception is thrown.
     *
     */
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline async_pipe& operator=(const basic_pipe<CharT, Traits>& p);

    /** Copy Assign a pipe.
     * @note Duplicates the handles.
     */
    async_pipe& operator=(const async_pipe& lhs);
    /** Move assign a pipe */
    async_pipe& operator=(async_pipe&& lhs);

    /** Destructor. Closes the pipe handles. */
    ~async_pipe();

    /** Explicit cast to basic_pipe.  */
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline explicit operator basic_pipe<CharT, Traits>() const;

    /** Cancel the current asynchronous operations. */
    void cancel();
    /** Close the pipe handles. */
    void close();
    /** Close the pipe handles. While passing an error_code
     *
     */
    void close(std::error_code & ec);

    /** Check if the pipes are open. */
    bool is_open() const;

    /** Async close, i.e. close after current operation is completed.
     *
     *  \note There is no guarantee that this will indeed read the entire pipe-buffer
     */
    void async_close();

    /** Read some data from the handle.

     * See the boost.asio documentation for more details.
     */
    template<typename MutableBufferSequence>
    std::size_t read_some(const MutableBufferSequence & buffers);

    /** Write some data to the handle.

     * See the boost.asio documentation for more details.
     */
    template<typename MutableBufferSequence>
    std::size_t write_some(const MutableBufferSequence & buffers);

    /** Get the native handle of the source. */
    native_handle native_source() const {return const_cast<boost::asio::windows::stream_handle&>(_source).native();}
    /** Get the native handle of the sink. */
    native_handle native_sink  () const {return const_cast<boost::asio::windows::stream_handle&>(_sink  ).native();}

    /** Start an asynchronous read.
     *
     * See the [boost.asio documentation](http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/reference/AsyncReadStream.html) for more details.
     */
    template<typename MutableBufferSequence,
             typename ReadHandler>
    detail::dummy async_read_some(
        const MutableBufferSequence & buffers,
              ReadHandler &&handler);

    /** Start an asynchronous write.

     * See the [boost.asio documentation](http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/reference/AsyncWriteStream.html) for more details.
     */
    template<typename ConstBufferSequence,
             typename WriteHandler>
    detail::dummy async_write_some(
        const ConstBufferSequence & buffers,
        WriteHandler && handler);

    ///Get the asio handle of the pipe sink.
    const handle_type & sink  () const &;
    ///Get the asio handle of the pipe source.
    const handle_type & source() const &;

    ///Get the asio handle of the pipe sink. Qualified as rvalue
    handle_type && sink  () &&;
    ///Get the asio handle of the pipe source. Qualified as rvalue
    handle_type && source() &&;

    /// Move the source out of this class and change the io_context. Qualified as rvalue. \attention Will always move.
    handle_type source(::boost::asio::io_context& ios) &&;
    /// Move the sink out of this class and change the io_context. Qualified as rvalue. \attention Will always move
    handle_type sink  (::boost::asio::io_context& ios) &&;

    /// Copy the source out of this class and change the io_context. \attention Will always copy.
    handle_type source(::boost::asio::io_context& ios) const &;
    /// Copy the sink out of this class and change the io_context. \attention Will always copy
    handle_type sink  (::boost::asio::io_context& ios) const &;



};

#else
using ::boost::process::detail::api::async_pipe;
#endif


}}



#endif

/* async_pipe.hpp
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
*/