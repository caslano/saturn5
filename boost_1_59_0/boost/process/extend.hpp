// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXTENSIONS_HPP_
#define BOOST_PROCESS_EXTENSIONS_HPP_

#include <boost/process/detail/handler.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <memory>

#if defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/executor.hpp>
#include <boost/process/detail/windows/async_handler.hpp>
#include <boost/process/detail/windows/asio_fwd.hpp>
#else
#include <boost/process/detail/posix/executor.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <boost/process/detail/posix/asio_fwd.hpp>
#endif


/** \file boost/process/extend.hpp
 *
 * This header which provides the types and functions provided for custom extensions.
 *
 * \xmlonly
   Please refer to the <link linkend="boost_process.extend">tutorial</link> for more details.
   \endxmlonly
 */


namespace boost {
namespace process {
namespace detail {
template<typename Tuple>
inline asio::io_context& get_io_context(const Tuple & tup);
}


///Namespace for extensions \attention This is experimental.
namespace extend {

#if defined(BOOST_WINDOWS_API)

template<typename Char, typename Sequence>
using windows_executor = ::boost::process::detail::windows::executor<Char, Sequence>;
template<typename Sequence>
struct posix_executor;

#elif defined(BOOST_POSIX_API)

template<typename Sequence>
using posix_executor = ::boost::process::detail::posix::executor<Sequence>;
template<typename Char, typename Sequence>
struct windows_executor;

#endif

using ::boost::process::detail::handler;
using ::boost::process::detail::api::require_io_context;
using ::boost::process::detail::api::async_handler;
using ::boost::process::detail::get_io_context;
using ::boost::process::detail::get_last_error;
using ::boost::process::detail::throw_last_error;
using ::boost::process::detail::uses_handles;
using ::boost::process::detail::foreach_used_handle;
using ::boost::process::detail::get_used_handles;

///This handler is invoked before the process in launched, to setup parameters. The required signature is `void(Exec &)`, where `Exec` is a template parameter.
constexpr boost::process::detail::make_handler_t<boost::process::detail::on_setup_>   on_setup;
///This handler is invoked if an error occured. The required signature is `void(auto & exec, const std::error_code&)`, where `Exec` is a template parameter.
constexpr boost::process::detail::make_handler_t<boost::process::detail::on_error_>   on_error;
///This handler is invoked if launching the process has succeeded. The required signature is `void(auto & exec)`, where `Exec` is a template parameter.
constexpr boost::process::detail::make_handler_t<boost::process::detail::on_success_> on_success;

#if defined(BOOST_POSIX_API) || defined(BOOST_PROCESS_DOXYGEN)
///This handler is invoked if the fork failed. The required signature is `void(auto & exec)`, where `Exec` is a template parameter. \note Only available on posix.
constexpr ::boost::process::detail::make_handler_t<::boost::process::detail::posix::on_fork_error_  >   on_fork_error;
///This handler is invoked if the fork succeeded. The required signature is `void(Exec &)`, where `Exec` is a template parameter. \note Only available on posix.
constexpr ::boost::process::detail::make_handler_t<::boost::process::detail::posix::on_exec_setup_  >   on_exec_setup;
///This handler is invoked if the exec call errored. The required signature is `void(auto & exec)`, where `Exec` is a template parameter. \note Only available on posix.
constexpr ::boost::process::detail::make_handler_t<::boost::process::detail::posix::on_exec_error_  >   on_exec_error;
#endif

#if defined(BOOST_PROCESS_DOXYGEN)
///Helper function to get the last error code system-independent
inline std::error_code get_last_error();

///Helper function to get and throw the last system error.
/// \throws boost::process::process_error
/// \param msg A message to add to the error code.
inline void throw_last_error(const std::string & msg);
///\overload void throw_last_error(const std::string & msg)
inline void throw_last_error();


/** This function gets the io_context from the initializer sequence.
 *
 * \attention Yields a compile-time error if no `io_context` is provided.
 * \param seq The Sequence of the initializer.
 */
template<typename Sequence>
inline asio::io_context& get_io_context(const Sequence & seq);

/** This class is the base for every initializer, to be used for extensions.
 *
 *  The usage is done through compile-time polymorphism, so that the required
 *  functions can be overloaded.
 *
 * \note None of the function need to be `const`.
 *
 */
struct handler
{
    ///This function is invoked before the process launch. \note It is not required to be const.
    template <class Executor>
    void on_setup(Executor&) const {}

    /** This function is invoked if an error occured while trying to launch the process.
     * \note It is not required to be const.
     */
    template <class Executor>
    void on_error(Executor&, const std::error_code &) const {}

    /** This function is invoked if the process was successfully launched.
     * \note It is not required to be const.
     */
    template <class Executor>
    void on_success(Executor&) const {}

    /**This function is invoked if an error occured during the call of `fork`.
     * \note This function will only be called on posix.
     */
    template<typename Executor>
    void on_fork_error  (Executor &, const std::error_code&) const {}

    /**This function is invoked if the call of `fork` was successful, before
     * calling `execve`.
     * \note This function will only be called on posix.
     * \attention It will be invoked from the new process.
     */
    template<typename Executor>
    void on_exec_setup  (Executor &) const {}

    /**This function is invoked if the call of `execve` failed.
     * \note This function will only be called on posix.
     * \attention It will be invoked from the new process.
     */
    template<typename Executor>
    void on_exec_error  (Executor &, const std::error_code&) const {}

};


/** Inheriting the class will tell the launching process that an `io_context` is
 * needed. This should always be used when \ref get_io_context is used.
 *
 */
struct require_io_context {};
/** Inheriting this class will tell the launching function, that an event handler
 * shall be invoked when the process exits. This automatically does also inherit
 * \ref require_io_context.
 *
 * You must add the following function to your implementation:
 *
 \code{.cpp}
template<typename Executor>
std::function<void(int, const std::error_code&)> on_exit_handler(Executor & exec)
{
    auto handler_ = this->handler;
    return [handler_](int exit_code, const std::error_code & ec)
           {
                handler_(static_cast<int>(exit_code), ec);
           };

}
 \endcode

 The callback will be obtained by calling this function on setup and it will be
 invoked when the process exits.

 *
 * \warning Cannot be used with \ref boost::process::spawn
 */
struct async_handler : handler, require_io_context
{

};

///The posix executor type.
/** This type represents the posix executor and can be used for overloading in a custom handler.
 * \note It is an alias for the implementation on posix, and a forward-declaration on windows.
 *
 * \tparam Sequence The used initializer-sequence, it is fulfills the boost.fusion [sequence](http://www.boost.org/doc/libs/master/libs/fusion/doc/html/fusion/sequence.html) concept.


\xmlonly
As information for extension development, here is the structure of the process launching (in pseudo-code and uml)
<xi:include href="posix_pseudocode.xml" xmlns:xi="http://www.w3.org/2001/XInclude"/>

<mediaobject>
<caption>
<para>The sequence if when no error occurs.</para>
</caption>
<imageobject>
<imagedata fileref="boost_process/posix_success.svg"/>
</imageobject>
</mediaobject>

<mediaobject>
<caption>
<para>The sequence if the execution fails.</para>
</caption>
<imageobject>
<imagedata fileref="boost_process/posix_exec_err.svg"/>
</imageobject>
</mediaobject>

<mediaobject>
<caption>
<para>The sequence if the fork fails.</para>
</caption>
<imageobject>
<imagedata fileref="boost_process/posix_fork_err.svg"/>
</imageobject>
</mediaobject>

\endxmlonly


\note Error handling if execve fails is done through a pipe, unless \ref ignore_error is used.

 */
template<typename Sequence>
struct posix_executor
{
    ///A reference to the actual initializer-sequence
     Sequence & seq;
    ///A pointer to the name of the executable.
     const char * exe      = nullptr;
     ///A pointer to the argument-vector.
     char *const* cmd_line = nullptr;
     ///A pointer to the environment variables, as default it is set to [environ](http://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap08.html)
     char **env      = ::environ;
     ///The pid of the process - it will be -1 before invoking [fork](http://pubs.opengroup.org/onlinepubs/009695399/functions/fork.html), and after forking either 0 for the new process or a positive value if in the current process. */
     pid_t pid = -1;
     ///This shared-pointer holds the exit code. It's done this way, so it can be shared between an `asio::io_context` and \ref child.
     std::shared_ptr<std::atomic<int>> exit_status = std::make_shared<std::atomic<int>>(still_active);

     ///This function returns a const reference to the error state of the executor.
     const std::error_code & error() const;

     ///This function can be used to report an error to the executor. This will be handled according to the configuration of the executor, i.e. it
     /// might throw an exception. \note This is the required way to handle errors in initializers.
     void set_error(const std::error_code &ec, const std::string &msg);
     ///\overload void set_error(const std::error_code &ec, const std::string &msg);
     void set_error(const std::error_code &ec, const char* msg);
};

///The windows executor type.
/** This type represents the posix executor and can be used for overloading in a custom handler.
 *
 * \note It is an alias for the implementation on posix, and a forward-declaration on windows.
 * \tparam Sequence The used initializer-sequence, it is fulfills the boost.fusion [sequence](http://www.boost.org/doc/libs/master/libs/fusion/doc/html/fusion/sequence.html) concept.
 * \tparam Char The used char-type, either `char` or `wchar_t`.
 *

\xmlonly
As information for extension development, here is the structure of the process launching (in pseudo-code and uml)<xi:include href="windows_pseudocode.xml" xmlns:xi="http://www.w3.org/2001/XInclude"/>
<mediaobject>
<caption>
<para>The sequence for windows process creation.</para>
</caption>
<imageobject>
<imagedata fileref="boost_process/windows_exec.svg"/>
</imageobject>
</mediaobject>
\endxmlonly

 */

template<typename Char, typename Sequence>
struct windows_executor
{
    ///A reference to the actual initializer-sequence
     Sequence & seq;

     ///A pointer to the name of the executable. It's null by default.
     const Char * exe      = nullptr;
     ///A pointer to the argument-vector. Must be set by some initializer.
     char  Char* cmd_line = nullptr;
     ///A pointer to the environment variables. It's null by default.
     char  Char* env      = nullptr;
     ///A pointer to the working directory. It's null by default.
     const Char * work_dir = nullptr;

     ///A pointer to the process-attributes of type [SECURITY_ATTRIBUTES](https://msdn.microsoft.com/en-us/library/windows/desktop/aa379560.aspx). It's null by default.
     ::boost::detail::winapi::LPSECURITY_ATTRIBUTES_ proc_attrs   = nullptr;
     ///A pointer to the thread-attributes of type [SECURITY_ATTRIBUTES](https://msdn.microsoft.com/en-us/library/windows/desktop/aa379560.aspx). It' null by default.
     ::boost::detail::winapi::LPSECURITY_ATTRIBUTES_ thread_attrs = nullptr;
     ///A logical bool value setting whether handles shall be inherited or not.
     ::boost::detail::winapi::BOOL_ inherit_handles = false;

     ///The element holding the process-information after process creation. The type is [PROCESS_INFORMATION](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684873.aspx)
     ::boost::detail::winapi::PROCESS_INFORMATION_ proc_info{nullptr, nullptr, 0,0};


     ///This shared-pointer holds the exit code. It's done this way, so it can be shared between an `asio::io_context` and \ref child.
     std::shared_ptr<std::atomic<int>> exit_status = std::make_shared<std::atomic<int>>(still_active);

     ///This function returns a const reference to the error state of the executor.
     const std::error_code & error() const;

     ///This function can be used to report an error to the executor. This will be handled according to the configuration of the executor, i.e. it
     /// might throw an exception. \note This is the required way to handle errors in initializers.
     void set_error(const std::error_code &ec, const std::string &msg);
     ///\overload void set_error(const std::error_code &ec, const std::string &msg);
     void set_error(const std::error_code &ec, const char* msg);

     ///The creation flags of the process
    ::boost::detail::winapi::DWORD_ creation_flags;
    ///The type of the [startup-info](https://msdn.microsoft.com/en-us/library/windows/desktop/ms686331.aspx), depending on the char-type.
    typedef typename detail::startup_info<Char>::type    startup_info_t;
    ///The type of the [extended startup-info](https://msdn.microsoft.com/de-de/library/windows/desktop/ms686329.aspx), depending the char-type; only defined with winapi-version equal or higher than 6.
    typedef typename detail::startup_info_ex<Char>::type startup_info_ex_t;
    ///This function switches the information, so that the extended structure is used. \note It's only defined with winapi-version equal or higher than 6.
    void set_startup_info_ex();
    ///This element is an instance or a reference (if \ref startup_info_ex exists) to the [startup-info](https://msdn.microsoft.com/en-us/library/windows/desktop/ms686331.aspx) for the process.
    startup_info_t startup_info;
    ///This element is the instance of the  [extended startup-info](https://msdn.microsoft.com/de-de/library/windows/desktop/ms686329.aspx). It is only available with a winapi-version equal or highter than 6.
    startup_info_ex_t  startup_info_ex;
};



#endif

}
}
}

#endif

/* extend.hpp
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
*/