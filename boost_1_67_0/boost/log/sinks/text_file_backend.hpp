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
    virtual ~collector() {}

    /*!
     * The function stores the specified file in the storage. May lead to an older file
     * deletion and a long file moving.
     *
     * \param src_path The name of the file to be stored
     */
    virtual void store_file(filesystem::path const& src_path) = 0;

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
     * \param counter If not \c NULL and \a method is \c scan_matching, the method suggests initial value
     *                of a file counter that may be used in the file name pattern. The parameter
     *                is not used otherwise.
     * \return The number of found files.
     *
     * \note In case if \a method is \c scan_matching the effect of this function is highly dependent
     *       on the \a pattern definition. It is recommended to choose patterns with easily
     *       distinguished placeholders (i.e. having delimiters between them). Otherwise
     *       either some files can be mistakenly found or not found, which in turn may lead
     *       to an incorrect file deletion.
     */
    virtual uintmax_t scan_for_files(
        scan_method method, filesystem::path const& pattern = filesystem::path(), unsigned int* counter = 0) = 0;

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