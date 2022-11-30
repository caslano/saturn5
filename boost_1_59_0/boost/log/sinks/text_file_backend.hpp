/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   text_file_backend.hpp
 * \author Andrey Semashev
 * \date   09.06.2009
 *
 * The header contains implementation of a text file sink backend.
 */

#ifndef BOOST_LOG_SINKS_TEXT_FILE_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_TEXT_FILE_BACKEND_HPP_INCLUDED_

#include <ios>
#include <string>
#include <ostream>
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>
#include <boost/optional/optional.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/gregorian/greg_day.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/log/keywords/max_size.hpp>
#include <boost/log/keywords/max_files.hpp>
#include <boost/log/keywords/min_free_space.hpp>
#include <boost/log/keywords/target.hpp>
#include <boost/log/keywords/target_file_name.hpp>
#include <boost/log/keywords/file_name.hpp>
#include <boost/log/keywords/open_mode.hpp>
#include <boost/log/keywords/auto_flush.hpp>
#include <boost/log/keywords/rotation_size.hpp>
#include <boost/log/keywords/time_based_rotation.hpp>
#include <boost/log/keywords/enable_final_rotation.hpp>
#include <boost/log/keywords/auto_newline_mode.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/sinks/auto_newline_mode.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

namespace file {

//! The enumeration of the stored files scan methods
enum scan_method
{
    no_scan,        //!< Don't scan for stored files
    scan_matching,  //!< Scan for files with names matching the specified mask
    scan_all        //!< Scan for all files in the directory
};

//! The structure contains filesystem scanning results
struct scan_result
{
    //! The number of found files
    uintmax_t found_count;
    //! If populated, the largest file counter that was used in the found file names
    boost::optional< unsigned int > last_file_counter;

    scan_result() BOOST_NOEXCEPT :
        found_count(0u)
    {
    }
};

/*!
 * \brief Base class for file collectors
 *
 * All file collectors, supported by file sink backends, should inherit this class.
 */
struct BOOST_LOG_NO_VTABLE collector
{
    /*!
     * Default constructor
     */
    BOOST_DEFAULTED_FUNCTION(collector(), {})

    /*!
     * Virtual destructor
     */
#if !defined(BOOST_LOG_NO_CXX11_DEFAULTED_VIRTUAL_FUNCTIONS)
    BOOST_DEFAULTED_FUNCTION(virtual ~collector(), {})
#else
    virtual ~collector() {}
#endif

    /*!
     * The function stores the specified file in the storage. May lead to an older file
     * deletion and a long file moving.
     *
     * \param src_path The name of the file to be stored
     */
    virtual void store_file(filesystem::path const& src_path) = 0;

    /*!
     * The function checks if the specified path refers to an existing file in the storage.
     *
     * \param src_path The path to be checked
     */
    virtual bool is_in_storage(filesystem::path const& src_path) const = 0;

    /*!
     * Scans the target directory for the files that have already been stored. The found
     * files are added to the collector in order to be tracked and erased, if needed.
     *
     * The function may scan the directory in two ways: it will either consider every
     * file in the directory a log file, or will only consider files with names that
     * match the specified pattern. The pattern may contain the following placeholders:
     *
     * \li %y, %Y, %m, %d - date components, in Boost.DateTime meaning.
     * \li %H, %M, %S, %f - time components, in Boost.DateTime meaning.
     * \li %N - numeric file counter. May also contain width specification
     *     in printf-compatible form (e.g. %5N). The resulting number will always be zero-filled.
     * \li %% - a percent sign
     *
     * All other placeholders are not supported.
     *
     * \param method The method of scanning. If \c no_scan is specified, the call has no effect.
     * \param pattern The file name pattern if \a method is \c scan_matching. Otherwise the parameter
     *                is not used.
     * \return The result of filesystem scanning. The last file counter is only populated if
     *         \a method is \c scan_matching, the \a pattern contains %N placeholder, and at least
     *         one file matching the pattern is found.
     *
     * \note In case if \a method is \c scan_matching the effect of this function is highly dependent
     *       on the \a pattern definition. It is recommended to choose patterns with easily
     *       distinguished placeholders (i.e. having delimiters between them). Otherwise
     *       either some files can be mistakenly found or not found, which in turn may lead
     *       to deletion of an unintended file.
     */
    virtual scan_result scan_for_files(scan_method method, filesystem::path const& pattern = filesystem::path()) = 0;

    BOOST_DELETED_FUNCTION(collector(collector const&))
    BOOST_DELETED_FUNCTION(collector& operator= (collector const&))
};

namespace aux {

    //! Creates and returns a file collector with the specified parameters
    BOOST_LOG_API shared_ptr< collector > make_collector(
        filesystem::path const& target_dir,
        uintmax_t max_size,
        uintmax_t min_free_space,
        uintmax_t max_files = (std::numeric_limits< uintmax_t >::max)()
    );
    template< typename ArgsT >
    inline shared_ptr< collector > make_collector(ArgsT const& args)
    {
        return aux::make_collector(
            filesystem::path(args[keywords::target]),
            args[keywords::max_size | (std::numeric_limits< uintmax_t >::max)()],
            args[keywords::min_free_space | static_cast< uintmax_t >(0)],
            args[keywords::max_files | (std::numeric_limits< uintmax_t >::max)()]);
    }

} // namespace aux

#ifndef BOOST_LOG_DOXYGEN_PASS

template< typename T1 >
inline shared_ptr< collector > make_collector(T1 const& a1)
{
    return aux::make_collector(a1);
}
template< typename T1, typename T2 >
inline shared_ptr< collector > make_collector(T1 const& a1, T2 const& a2)
{
    return aux::make_collector((a1, a2));
}
template< typename T1, typename T2, typename T3 >
inline shared_ptr< collector > make_collector(T1 const& a1, T2 const& a2, T3 const& a3)
{
    return aux::make_collector((a1, a2, a3));
}
template< typename T1, typename T2, typename T3, typename T4 >
inline shared_ptr< collector > make_collector(T1 const& a1, T2 const& a2, T3 const& a3, T4 const& a4)
{
    return aux::make_collector((a1, a2, a3, a4));
}

#else

/*!
 * The function creates a file collector for the specified target directory.
 * Each target directory is managed by a single file collector, so if
 * this function is called several times for the same directory,
 * it will return a reference to the same file collector. It is safe
 * to use the same collector in different sinks, even in a multithreaded
 * application.
 *
 * One can specify certain restrictions for the stored files, such as
 * maximum total size or minimum free space left in the target directory.
 * If any of the specified restrictions is not met, the oldest stored file
 * is deleted. If the same collector is requested more than once with
 * different restrictions, the collector will act according to the most strict
 * combination of all specified restrictions.
 *
 * The following named parameters are supported:
 *
 * \li \c target - Specifies the target directory for the files being stored in. This parameter
 *                 is mandatory.
 * \li \c max_size - Specifies the maximum total size, in bytes, of stored files that the collector
 *                   will try not to exceed. If the size exceeds this threshold the oldest file(s) is
 *                   deleted to free space. Note that the threshold may be exceeded if the size of
 *                   individual files exceed the \c max_size value. The threshold is not maintained,
 *                   if not specified.
 * \li \c min_free_space - Specifies the minimum free space, in bytes, in the target directory that
 *                         the collector tries to maintain. If the threshold is exceeded, the oldest
 *                         file(s) is deleted to free space. The threshold is not maintained, if not
 *                         specified.
 * \li \c max_files - Specifies the maximum number of log files stored.  If the number of files exceeds
 *                    this threshold, the oldest file(s) is deleted to free space.  The threshhold is
 *                    not maintained if not specified.
 *
 * \return The file collector.
 */
template< typename... ArgsT >
shared_ptr< collector > make_collector(ArgsT... const& args);

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * The class represents the time point of log file rotation. One can specify one of three
 * types of time point based rotation:
 *
 * \li rotation takes place every day, at the specified time
 * \li rotation takes place on the specified day of every week, at the specified time
 * \li rotation takes place on the specified day of every month, at the specified time
 *
 * The time points are considered to be local time.
 */
class rotation_at_time_point
{
public:
    typedef bool result_type;

private:
    enum day_kind
    {
        not_specified,
        weekday,
        monthday
    };

    unsigned char m_Day : 6;
    unsigned char m_DayKind : 2; // contains day_kind values
    unsigned char m_Hour, m_Minute, m_Second;

    mutable posix_time::ptime m_Previous;

public:
    /*!
     * Creates a rotation time point of every day at the specified time
     *
     * \param hour The rotation hour, should be within 0 and 23
     * \param minute The rotation minute, should be within 0 and 59
     * \param second The rotation second, should be within 0 and 59
     */
    BOOST_LOG_API explicit rotation_at_time_point(unsigned char hour, unsigned char minute, unsigned char second);

    /*!
     * Creates a rotation time point of each specified weekday at the specified time
     *
     * \param wday The weekday of the rotation
     * \param hour The rotation hour, should be within 0 and 23
     * \param minute The rotation minute, should be within 0 and 59
     * \param second The rotation second, should be within 0 and 59
     */
    BOOST_LOG_API explicit rotation_at_time_point(
        date_time::weekdays wday,
        unsigned char hour = 0,
        unsigned char minute = 0,
        unsigned char second = 0);

    /*!
     * Creates a rotation time point of each specified day of month at the specified time
     *
     * \param mday The monthday of the rotation, should be within 1 and 31
     * \param hour The rotation hour, should be within 0 and 23
     * \param minute The rotation minute, should be within 0 and 59
     * \param second The rotation second, should be within 0 and 59
     */
    BOOST_LOG_API explicit rotation_at_time_point(
        gregorian::greg_day mday,
        unsigned char hour = 0,
        unsigned char minute = 0,
        unsigned char second = 0);

    /*!
     * Checks if it's time to rotate the file
     */
    BOOST_LOG_API bool operator() () const;
};

/*!
 * The class represents the time interval of log file rotation. The log file will be rotated
 * after the specified time interval has passed.
 */
class rotation_at_time_interval
{
public:
    typedef bool result_type;

private:
    posix_time::time_duration m_Interval;
    mutable posix_time::ptime m_Previous;

public:
    /*!
     * Creates a rotation time interval of the specified duration
     *
     * \param interval The interval of the rotation, should be no less than 1 second
     */
    explicit rotation_at_time_interval(posix_time::time_duration const& interval) :
        m_Interval(interval)
    {
        BOOST_ASSERT(!interval.is_special());
        BOOST_ASSERT(interval.total_seconds() > 0);
    }

    /*!
     * Checks if it's time to rotate the file
     */
    BOOST_LOG_API bool operator() () const;
};

} // namespace file


/*!
 * \brief An implementation of a text file logging sink backend
 *
 * The sink backend puts formatted log records to a text file.
 * The sink supports file rotation and advanced file control, such as
 * size and file count restriction.
 */
class text_file_backend :
    public basic_formatted_sink_backend<
        char,
        combine_requirements< synchronized_feeding, flushing >::type
    >
{
    //! Base type
    typedef basic_formatted_sink_backend<
        char,
        combine_requirements< synchronized_feeding, flushing >::type
    > base_type;

public:
    //! Character type
    typedef base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef base_type::string_type string_type;
    //! Stream type
    typedef std::basic_ostream< char_type > stream_type;

    //! File open handler
    typedef boost::log::aux::light_function< void (stream_type&) > open_handler_type;
    //! File close handler
    typedef boost::log::aux::light_function< void (stream_type&) > close_handler_type;

    //! Predicate that defines the time-based condition for file rotation
    typedef boost::log::aux::light_function< bool () > time_based_rotation_predicate;

private:
    //! \cond

    struct implementation;
    implementation* m_pImpl;

    //! \endcond

public:
    /*!
     * Default constructor. The constructed sink backend uses default values of all the parameters.
     */
    BOOST_LOG_API text_file_backend();

    /*!
     * Constructor. Creates a sink backend with the specified named parameters.
     * The following named parameters are supported:
     *
     * \li \c file_name - Specifies the active file name pattern where logs are actually written to. The pattern may
     *                    contain directory and file name portions, but only the file name may contain
     *                    placeholders. The backend supports Boost.DateTime placeholders for injecting
     *                    current time and date into the file name. Also, an additional %N placeholder is
     *                    supported, it will be replaced with an integral increasing file counter. The placeholder
     *                    may also contain width specification in the printf-compatible form (e.g. %5N). The
     *                    printed file counter will always be zero-filled. If \c file_name is not specified,
     *                    pattern "%5N.log" will be used.
     * \li \c target_file_name - Specifies the target file name pattern to use to rename the log file on rotation,
     *                           before passing it to the file collector. The pattern may contain the same
     *                           placeholders as the \c file_name parameter. By default, no renaming is done,
     *                           i.e. the written log file keeps its name according to \c file_name.
     * \li \c open_mode - File open mode. The mode should be presented in form of mask compatible to
     *                    <tt>std::ios_base::openmode</tt>. If not specified, <tt>trunc | out</tt> will be used.
     * \li \c rotation_size - Specifies the approximate size, in characters written, of the temporary file
     *                        upon which the file is passed to the file collector. Note the size does
     *                        not count any possible character conversions that may take place during
     *                        writing to the file. If not specified, the file won't be rotated upon reaching
     *                        any size.
     * \li \c time_based_rotation - Specifies the predicate for time-based file rotation.
     *                              No time-based file rotations will be performed, if not specified.
     * \li \c enable_final_rotation - Specifies a flag, whether or not perform log file rotation on
     *                                sink backend destruction. By default, is \c true.
     * \li \c auto_flush - Specifies a flag, whether or not to automatically flush the file after each
     *                     written log record. By default, is \c false.
     * \li \c auto_newline_mode - Specifies automatic trailing newline insertion mode. Must be a value of
     *                            the \c auto_newline_mode enum. By default, is <tt>auto_newline_mode::insert_if_missing</tt>.
     *
     * \note Read the caution note regarding file name pattern in the <tt>sinks::file::collector::scan_for_files</tt>
     *       documentation.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(text_file_backend, construct)
#else
    template< typename... ArgsT >
    explicit text_file_backend(ArgsT... const& args);
#endif

    /*!
     * Destructor
     */
    BOOST_LOG_API ~text_file_backend();

    /*!
     * The method sets the active file name wildcard for the files being written. The wildcard supports
     * date and time injection into the file name.
     *
     * \param pattern The name pattern for the file being written.
     */
    template< typename PathT >
    void set_file_name_pattern(PathT const& pattern)
    {
        set_file_name_pattern_internal(filesystem::path(pattern));
    }

    /*!
     * The method sets the target file name wildcard for the files being rotated. The wildcard supports
     * date and time injection into the file name.
     *
     * This pattern will be used when the log file is being rotated, to rename the just written
     * log file (which has the name according to the pattern in the \c file_name constructor parameter or
     * set by a call to \c set_file_name_pattern), just before passing the file to the file collector.
     *
     * \param pattern The name pattern for the file being rotated.
     */
    template< typename PathT >
    void set_target_file_name_pattern(PathT const& pattern)
    {
        set_target_file_name_pattern_internal(filesystem::path(pattern));
    }

    /*!
     * The method sets the file open mode
     *
     * \param mode File open mode
     */
    BOOST_LOG_API void set_open_mode(std::ios_base::openmode mode);

    /*!
     * The method sets the log file collector function. The function is called
     * on file rotation and is being passed the written file name.
     *
     * \param collector The file collector function object
     */
    BOOST_LOG_API void set_file_collector(shared_ptr< file::collector > const& collector);

    /*!
     * The method sets file opening handler. The handler will be called every time
     * the backend opens a new temporary file. The handler may write a header to the
     * opened file in order to maintain file validity.
     *
     * \param handler The file open handler function object
     */
    BOOST_LOG_API void set_open_handler(open_handler_type const& handler);

    /*!
     * The method sets file closing handler. The handler will be called every time
     * the backend closes a temporary file. The handler may write a footer to the
     * opened file in order to maintain file validity.
     *
     * \param handler The file close handler function object
     */
    BOOST_LOG_API void set_close_handler(close_handler_type const& handler);

    /*!
     * The method sets maximum file size. When the size is reached, file rotation is performed.
     *
     * \note The size does not count any possible character translations that may happen in
     *       the underlying API. This may result in greater actual sizes of the written files.
     *
     * \param size The maximum file size, in characters.
     */
    BOOST_LOG_API void set_rotation_size(uintmax_t size);

    /*!
     * The method sets the predicate that defines the time-based condition for file rotation.
     *
     * \note The rotation always occurs on writing a log record, so the rotation is
     *       not strictly bound to the specified condition.
     *
     * \param predicate The predicate that defines the time-based condition for file rotation.
     *                  If empty, no time-based rotation will take place.
     */
    BOOST_LOG_API void set_time_based_rotation(time_based_rotation_predicate const& predicate);

    /*!
     * The method allows to enable or disable log file rotation on sink destruction.
     *
     * By default the sink backend will rotate the log file, if it's been written to, on
     * destruction.
     *
     * \param enable The flag indicates whether the final rotation should be performed.
     */
    BOOST_LOG_API void enable_final_rotation(bool enable);

    /*!
     * Sets the flag to automatically flush write buffers of the file being written after each log record.
     *
     * \param enable The flag indicates whether the automatic buffer flush should be performed.
     */
    BOOST_LOG_API void auto_flush(bool enable = true);

    /*!
     * Selects whether a trailing newline should be automatically inserted after every log record. See
     * \c auto_newline_mode description for the possible modes of operation.
     *
     * \param mode The trailing newline insertion mode.
     */
    BOOST_LOG_API void set_auto_newline_mode(auto_newline_mode mode);

    /*!
     * \return The name of the currently open log file. If no file is open, returns an empty path.
     */
    BOOST_LOG_API filesystem::path get_current_file_name() const;

    /*!
     * Performs scanning of the target directory for log files that may have been left from
     * previous runs of the application. The found files are considered by the file collector
     * as if they were rotated.
     *
     * The file scan can be performed in two ways: either all files in the target directory will
     * be considered as log files, or only those files that satisfy the target file name pattern.
     * See documentation on <tt>sinks::file::collector::scan_for_files</tt> for more information.
     *
     * \pre File collector and the proper file name pattern have already been set.
     *
     * \param method File scanning method
     * \param update_counter If \c true and \a method is \c scan_matching, the method attempts
     *        to update the internal file counter according to the found files. The counter
     *        is unaffected otherwise.
     * \return The number of files found.
     *
     * \note The method essentially delegates to the same-named function of the file collector.
     */
    BOOST_LOG_API uintmax_t scan_for_files(
        file::scan_method method = file::scan_matching, bool update_counter = true);

    /*!
     * The method writes the message to the sink
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);

    /*!
     * The method flushes the currently open log file
     */
    BOOST_LOG_API void flush();

    /*!
     * The method rotates the file
     */
    BOOST_LOG_API void rotate_file();

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Constructor implementation
    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            filesystem::path(args[keywords::file_name | filesystem::path()]),
            filesystem::path(args[keywords::target_file_name | filesystem::path()]),
            args[keywords::open_mode | (std::ios_base::trunc | std::ios_base::out)],
            args[keywords::rotation_size | (std::numeric_limits< uintmax_t >::max)()],
            args[keywords::time_based_rotation | time_based_rotation_predicate()],
            args[keywords::auto_newline_mode | insert_if_missing],
            args[keywords::auto_flush | false],
            args[keywords::enable_final_rotation | true]);
    }
    //! Constructor implementation
    BOOST_LOG_API void construct(
        filesystem::path const& pattern,
        filesystem::path const& target_file_name,
        std::ios_base::openmode mode,
        uintmax_t rotation_size,
        time_based_rotation_predicate const& time_based_rotation,
        auto_newline_mode auto_newline,
        bool auto_flush,
        bool enable_final_rotation);

    //! The method sets file name pattern
    BOOST_LOG_API void set_file_name_pattern_internal(filesystem::path const& pattern);
    //! The method sets target file name pattern
    BOOST_LOG_API void set_target_file_name_pattern_internal(filesystem::path const& pattern);

    //! Closes the currently open file
    void close_file();
#endif // BOOST_LOG_DOXYGEN_PASS
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_TEXT_FILE_BACKEND_HPP_INCLUDED_

/* text_file_backend.hpp
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
*/