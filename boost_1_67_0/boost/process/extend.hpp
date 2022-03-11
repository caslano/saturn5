// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXTENSIONS_HPP_
#define BOOST_PROCESS_EXTENSIONS_HPP_

#include <boost/process/detail/handler.hpp>
#include <boost/process/detail/used_handles.hpp>

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