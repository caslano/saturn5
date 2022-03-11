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