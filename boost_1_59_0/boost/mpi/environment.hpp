// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file environment.hpp
 *
 *  This header provides the @c environment class, which provides
 *  routines to initialize, finalization, and query the status of the
 *  Boost MPI environment.
 */
#ifndef BOOST_MPI_ENVIRONMENT_HPP
#define BOOST_MPI_ENVIRONMENT_HPP

#include <boost/mpi/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <string>
#include <iosfwd>

namespace boost { namespace mpi {
namespace threading {
/** @brief specify the supported threading level.
 * 
 * Based on MPI 2 standard/8.7.3
 */
enum level {
  /** Only one thread will execute. 
   */
  single     = MPI_THREAD_SINGLE,
  /** Only main thread will do MPI calls.
   * 
   * The process may be multi-threaded, but only the main 
   * thread will make MPI calls (all MPI calls are ``funneled''
   * to the main thread).
   */
  funneled   = MPI_THREAD_FUNNELED,
  /** Only one thread at the time do MPI calls.
   * 
   * The process may be multi-threaded, and multiple 
   * threads may make MPI calls, but only one at a time:
   * MPI calls are not made concurrently from two distinct 
   * threads (all MPI calls are ``serialized'').
   */
  serialized = MPI_THREAD_SERIALIZED,
  /** Multiple thread may do MPI calls.
   * 
   * Multiple threads may call MPI, with no restrictions.
   */
  multiple   = MPI_THREAD_MULTIPLE
};

/** Formated output for threading level. */
std::ostream& operator<<(std::ostream& out, level l);

/** Formated input for threading level. */
std::istream& operator>>(std::istream& in, level& l);
} // namespace threading
/** @brief Initialize, finalize, and query the MPI environment.
 *
 *  The @c environment class is used to initialize, finalize, and
 *  query the MPI environment. It will typically be used in the @c
 *  main() function of a program, which will create a single instance
 *  of @c environment initialized with the arguments passed to the
 *  program:
 *
 *  @code
 *  int main(int argc, char* argv[])
 *  {
 *    mpi::environment env(argc, argv);
 *  }
 *  @endcode
 *
 *  The instance of @c environment will initialize MPI (by calling @c
 *  MPI_Init) in its constructor and finalize MPI (by calling @c
 *  MPI_Finalize for normal termination or @c MPI_Abort for an
 *  uncaught exception) in its destructor.
 *
 *  The use of @c environment is not mandatory. Users may choose to
 *  invoke @c MPI_Init and @c MPI_Finalize manually. In this case, no
 *  @c environment object is needed. If one is created, however, it
 *  will do nothing on either construction or destruction.
 */
class BOOST_MPI_DECL environment : noncopyable {
public:
#ifdef BOOST_MPI_HAS_NOARG_INITIALIZATION
  /** Initialize the MPI environment. 
   *
   *  If the MPI environment has not already been initialized,
   *  initializes MPI with a call to @c MPI_Init. Since this
   *  constructor does not take command-line arguments (@c argc and @c
   *  argv), it is only available when the underlying MPI
   *  implementation supports calling @c MPI_Init with @c NULL
   *  arguments, indicated by the macro @c
   *  BOOST_MPI_HAS_NOARG_INITIALIZATION.
   *
   *  @param abort_on_exception When true, this object will abort the
   *  program if it is destructed due to an uncaught exception.
   */
  explicit environment(bool abort_on_exception = true);
  /** Initialize the MPI environment. 
   *
   *  If the MPI environment has not already been initialized,
   *  initializes MPI with a call to @c MPI_Init_thread. Since this
   *  constructor does not take command-line arguments (@c argc and @c
   *  argv), it is only available when the underlying MPI
   *  implementation supports calling @c MPI_Init with @c NULL
   *  arguments, indicated by the macro @c
   *  BOOST_MPI_HAS_NOARG_INITIALIZATION.
   *
   *  @param mt_level the required level of threading support.
   *
   *  @param abort_on_exception When true, this object will abort the
   *  program if it is destructed due to an uncaught exception.
   */
  explicit environment(threading::level mt_level, bool abort_on_exception = true);
#endif

  /** Initialize the MPI environment.
   *
   *  If the MPI environment has not already been initialized,
   *  initializes MPI with a call to @c MPI_Init.
   *
   *  @param argc The number of arguments provided in @p argv, as
   *  passed into the program's @c main function.
   *
   *  @param argv The array of argument strings passed to the program
   *  via @c main.
   *
   *  @param abort_on_exception When true, this object will abort the
   *  program if it is destructed due to an uncaught exception.
   */
  environment(int& argc, char** &argv, bool abort_on_exception = true);

  /** Initialize the MPI environment.
   *
   *  If the MPI environment has not already been initialized,
   *  initializes MPI with a call to @c MPI_Init_thread.
   *
   *  @param argc The number of arguments provided in @p argv, as
   *  passed into the program's @c main function.
   *
   *  @param argv The array of argument strings passed to the program
   *  via @c main.
   *
   *  @param mt_level the required level of threading support
   *
   *  @param abort_on_exception When true, this object will abort the
   *  program if it is destructed due to an uncaught exception.
   */
  environment(int& argc, char** &argv, threading::level mt_level,
              bool abort_on_exception = true);

  /** Shuts down the MPI environment.
   *
   *  If this @c environment object was used to initialize the MPI
   *  environment, and the MPI environment has not already been shut
   *  down (finalized), this destructor will shut down the MPI
   *  environment. Under normal circumstances, this only involves
   *  invoking @c MPI_Finalize. However, if destruction is the result
   *  of an uncaught exception and the @c abort_on_exception parameter
   *  of the constructor had the value @c true, this destructor will
   *  invoke @c MPI_Abort with @c MPI_COMM_WORLD to abort the entire
   *  MPI program with a result code of -1.
   */
  ~environment();

  /** Abort all MPI processes.
   *
   *  Aborts all MPI processes and returns to the environment. The
   *  precise behavior will be defined by the underlying MPI
   *  implementation. This is equivalent to a call to @c MPI_Abort
   *  with @c MPI_COMM_WORLD.
   *
   *  @param errcode The error code to return to the environment.
   *  @returns Will not return.
   */
  static void abort(int errcode);

  /** Determine if the MPI environment has already been initialized.
   *
   *  This routine is equivalent to a call to @c MPI_Initialized.
   *
   *  @returns @c true if the MPI environment has been initialized.
   */
  static bool initialized();

  /** Determine if the MPI environment has already been finalized.
   *
   *  The routine is equivalent to a call to @c MPI_Finalized.
   *
   *  @returns @c true if the MPI environment has been finalized.
   */
  static bool finalized();

  /** Retrieves the maximum tag value.
   *
   *  Returns the maximum value that may be used for the @c tag
   *  parameter of send/receive operations. This value will be
   *  somewhat smaller than the value of @c MPI_TAG_UB, because the
   *  Boost.MPI implementation reserves some tags for collective
   *  operations.
   *
   *  @returns the maximum tag value.
   */
  static int max_tag();

  /** The tag value used for collective operations.
   *
   *  Returns the reserved tag value used by the Boost.MPI
   *  implementation for collective operations. Although users are not
   *  permitted to use this tag to send or receive messages, it may be
   *  useful when monitoring communication patterns.
   *
   * @returns the tag value used for collective operations.
   */
  static int collectives_tag();

  /** Retrieves the rank of the host process, if one exists.
   *
   *  If there is a host process, this routine returns the rank of
   *  that process. Otherwise, it returns an empty @c
   *  optional<int>. MPI does not define the meaning of a "host"
   *  process: consult the documentation for the MPI
   *  implementation. This routine examines the @c MPI_HOST attribute
   *  of @c MPI_COMM_WORLD.
   *
   *  @returns The rank of the host process, if one exists.
   */
  static optional<int> host_rank();

  /** Retrieves the rank of a process that can perform input/output.
   *
   *  This routine returns the rank of a process that can perform
   *  input/output via the standard C and C++ I/O facilities. If every
   *  process can perform I/O using the standard facilities, this
   *  routine will return @c any_source; if no process can perform
   *  I/O, this routine will return no value (an empty @c
   *  optional). This routine examines the @c MPI_IO attribute of @c
   *  MPI_COMM_WORLD.
   *
   *  @returns the rank of the process that can perform I/O, @c
   *  any_source if every process can perform I/O, or no value if no
   *  process can perform I/O.
   */
  static optional<int> io_rank();

  /** Retrieve the name of this processor.
   *
   *  This routine returns the name of this processor. The actual form
   *  of the name is unspecified, but may be documented by the
   *  underlying MPI implementation. This routine is implemented as a
   *  call to @c MPI_Get_processor_name.
   *
   *  @returns the name of this processor.
   */
  static std::string processor_name();

  /** Query the current level of thread support.
   */
  static threading::level thread_level();

  /** Are we in the main thread?
   */
  static bool is_main_thread();
  
  /** @brief MPI version.
   *
   * Returns a pair with the version and sub-version number.
   */
  static std::pair<int, int> version();

private:
  /// Whether this environment object called MPI_Init
  bool i_initialized;

  /// Whether we should abort if the destructor is
  bool abort_on_exception;
  
  /// The number of reserved tags.
  static const int num_reserved_tags = 1;
};

} } // end namespace boost::mpi

#endif // BOOST_MPI_ENVIRONMENT_HPP

/* environment.hpp
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
*/