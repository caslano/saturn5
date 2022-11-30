//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_SUITE_HPP
#define BOOST_BEAST_UNIT_TEST_SUITE_HPP

#include <boost/beast/_experimental/unit_test/runner.hpp>
#include <boost/throw_exception.hpp>
#include <ostream>
#include <sstream>
#include <string>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

template<class String>
std::string
make_reason(String const& reason,
    char const* file, int line)
{
    std::string s(reason);
    if(! s.empty())
        s.append(": ");
    char const* path = file + strlen(file);
    while(path != file)
    {
    #ifdef _MSC_VER
        if(path[-1] == '\\')
    #else
        if(path[-1] == '/')
    #endif
            break;
        --path;
    }
    s.append(path);
    s.append("(");
    s.append(std::to_string(line));
    s.append(")");
    return s;
}

} // detail

class thread;

enum abort_t
{
    no_abort_on_fail,
    abort_on_fail
};

/** A testsuite class.

    Derived classes execute a series of testcases, where each testcase is
    a series of pass/fail tests. To provide a unit test using this class,
    derive from it and use the BOOST_BEAST_DEFINE_UNIT_TEST macro in a
    translation unit.
*/
class suite
{
private:
    bool abort_ = false;
    bool aborted_ = false;
    runner* runner_ = nullptr;

    // This exception is thrown internally to stop the current suite
    // in the event of a failure, if the option to stop is set.
    struct abort_exception : public std::exception
    {
        char const*
        what() const noexcept override
        {
            return "test suite aborted";
        }
    };

    template<class CharT, class Traits, class Allocator>
    class log_buf
        : public std::basic_stringbuf<CharT, Traits, Allocator>
    {
        suite& suite_;

    public:
        explicit
        log_buf(suite& self)
            : suite_(self)
        {
        }

        ~log_buf()
        {
            sync();
        }

        int
        sync() override
        {
            auto const& s = this->str();
            if(s.size() > 0)
                suite_.runner_->log(s);
            this->str("");
            return 0;
        }
    };

    template<
        class CharT,
        class Traits = std::char_traits<CharT>,
        class Allocator = std::allocator<CharT>
    >
    class log_os : public std::basic_ostream<CharT, Traits>
    {
        log_buf<CharT, Traits, Allocator> buf_;

    public:
        explicit
        log_os(suite& self)
            : std::basic_ostream<CharT, Traits>(&buf_)
            , buf_(self)
        {
        }
    };

    class scoped_testcase;

    class testcase_t
    {
        suite& suite_;
        std::stringstream ss_;

    public:
        explicit
        testcase_t(suite& self)
            : suite_(self)
        {
        }

        /** Open a new testcase.

            A testcase is a series of evaluated test conditions. A test
            suite may have multiple test cases. A test is associated with
            the last opened testcase. When the test first runs, a default
            unnamed case is opened. Tests with only one case may omit the
            call to testcase.

            @param abort Determines if suite continues running after a failure.
        */
        void
        operator()(std::string const& name,
            abort_t abort = no_abort_on_fail);

        scoped_testcase
        operator()(abort_t abort);

        template<class T>
        scoped_testcase
        operator<<(T const& t);
    };

public:
    /** Logging output stream.

        Text sent to the log output stream will be forwarded to
        the output stream associated with the runner.
    */
    log_os<char> log;

    /** Memberspace for declaring test cases. */
    testcase_t testcase;

    /** Returns the "current" running suite.
        If no suite is running, nullptr is returned.
    */
    static
    suite*
    this_suite()
    {
        return *p_this_suite();
    }

    suite()
        : log(*this)
        , testcase(*this)
    {
    }

    virtual ~suite() = default;
    suite(suite const&) = delete;
    suite& operator=(suite const&) = delete;

    /** Invokes the test using the specified runner.

        Data members are set up here instead of the constructor as a
        convenience to writing the derived class to avoid repetition of
        forwarded constructor arguments to the base.
        Normally this is called by the framework for you.
    */
    template<class = void>
    void
    operator()(runner& r);

    /** Record a successful test condition. */
    template<class = void>
    void
    pass();

    /** Record a failure.

        @param reason Optional text added to the output on a failure.

        @param file The source code file where the test failed.

        @param line The source code line number where the test failed.
    */
    /** @{ */
    template<class String>
    void
    fail(String const& reason, char const* file, int line);

    template<class = void>
    void
    fail(std::string const& reason = "");
    /** @} */

    /** Evaluate a test condition.

        This function provides improved logging by incorporating the
        file name and line number into the reported output on failure,
        as well as additional text specified by the caller.

        @param shouldBeTrue The condition to test. The condition
        is evaluated in a boolean context.

        @param reason Optional added text to output on a failure.

        @param file The source code file where the test failed.

        @param line The source code line number where the test failed.

        @return `true` if the test condition indicates success.
    */
    /** @{ */
    template<class Condition>
    bool
    expect(Condition const& shouldBeTrue)
    {
        return expect(shouldBeTrue, "");
    }

    template<class Condition, class String>
    bool
    expect(Condition const& shouldBeTrue, String const& reason);

    template<class Condition>
    bool
    expect(Condition const& shouldBeTrue,
        char const* file, int line)
    {
        return expect(shouldBeTrue, "", file, line);
    }

    template<class Condition, class String>
    bool
    expect(Condition const& shouldBeTrue,
        String const& reason, char const* file, int line);
    /** @} */

    //
    // DEPRECATED
    //
    // Expect an exception from f()
    template<class F, class String>
    bool
    except(F&& f, String const& reason);
    template<class F>
    bool
    except(F&& f)
    {
        return except(f, "");
    }
    template<class E, class F, class String>
    bool
    except(F&& f, String const& reason);
    template<class E, class F>
    bool
    except(F&& f)
    {
        return except<E>(f, "");
    }
    template<class F, class String>
    bool
    unexcept(F&& f, String const& reason);
    template<class F>
    bool
    unexcept(F&& f)
    {
        return unexcept(f, "");
    }

    /** Return the argument associated with the runner. */
    std::string const&
    arg() const
    {
        return runner_->arg();
    }

    // DEPRECATED
    // @return `true` if the test condition indicates success(a false value)
    template<class Condition, class String>
    bool
    unexpected(Condition shouldBeFalse,
        String const& reason);

    template<class Condition>
    bool
    unexpected(Condition shouldBeFalse)
    {
        return unexpected(shouldBeFalse, "");
    }

private:
    friend class thread;

    static
    suite**
    p_this_suite()
    {
        static suite* pts = nullptr;
        return &pts;
    }

    /** Runs the suite. */
    virtual
    void
    run() = 0;

    void
    propagate_abort();

    template<class = void>
    void
    run(runner& r);
};

//------------------------------------------------------------------------------

// Helper for streaming testcase names
class suite::scoped_testcase
{
private:
    suite& suite_;
    std::stringstream& ss_;

public:
    scoped_testcase& operator=(scoped_testcase const&) = delete;

    ~scoped_testcase()
    {
        auto const& name = ss_.str();
        if(! name.empty())
            suite_.runner_->testcase(name);
    }

    scoped_testcase(suite& self, std::stringstream& ss)
        : suite_(self)
        , ss_(ss)
    {
        ss_.clear();
        ss_.str({});
    }

    template<class T>
    scoped_testcase(suite& self,
            std::stringstream& ss, T const& t)
        : suite_(self)
        , ss_(ss)
    {
        ss_.clear();
        ss_.str({});
        ss_ << t;
    }

    template<class T>
    scoped_testcase&
    operator<<(T const& t)
    {
        ss_ << t;
        return *this;
    }
};

//------------------------------------------------------------------------------

inline
void
suite::testcase_t::operator()(
    std::string const& name, abort_t abort)
{
    suite_.abort_ = abort == abort_on_fail;
    suite_.runner_->testcase(name);
}

inline
suite::scoped_testcase
suite::testcase_t::operator()(abort_t abort)
{
    suite_.abort_ = abort == abort_on_fail;
    return { suite_, ss_ };
}

template<class T>
inline
suite::scoped_testcase
suite::testcase_t::operator<<(T const& t)
{
    return { suite_, ss_, t };
}

//------------------------------------------------------------------------------

template<class>
void
suite::
operator()(runner& r)
{
    *p_this_suite() = this;
    try
    {
        run(r);
        *p_this_suite() = nullptr;
    }
    catch(...)
    {
        *p_this_suite() = nullptr;
        throw;
    }
}

template<class Condition, class String>
bool
suite::
expect(
    Condition const& shouldBeTrue, String const& reason)
{
    if(shouldBeTrue)
    {
        pass();
        return true;
    }
    fail(reason);
    return false;
}

template<class Condition, class String>
bool
suite::
expect(Condition const& shouldBeTrue,
    String const& reason, char const* file, int line)
{
    if(shouldBeTrue)
    {
        pass();
        return true;
    }
    fail(detail::make_reason(reason, file, line));
    return false;
}

// DEPRECATED

template<class F, class String>
bool
suite::
except(F&& f, String const& reason)
{
    try
    {
        f();
        fail(reason);
        return false;
    }
    catch(...)
    {
        pass();
    }
    return true;
}

template<class E, class F, class String>
bool
suite::
except(F&& f, String const& reason)
{
    try
    {
        f();
        fail(reason);
        return false;
    }
    catch(E const&)
    {
        pass();
    }
    return true;
}

template<class F, class String>
bool
suite::
unexcept(F&& f, String const& reason)
{
    try
    {
        f();
        pass();
        return true;
    }
    catch(...)
    {
        fail(reason);
    }
    return false;
}

template<class Condition, class String>
bool
suite::
unexpected(
    Condition shouldBeFalse, String const& reason)
{
    bool const b =
        static_cast<bool>(shouldBeFalse);
    if(! b)
        pass();
    else
        fail(reason);
    return ! b;
}

template<class>
void
suite::
pass()
{
    propagate_abort();
    runner_->pass();
}

// ::fail
template<class>
void
suite::
fail(std::string const& reason)
{
    propagate_abort();
    runner_->fail(reason);
    if(abort_)
    {
        aborted_ = true;
        BOOST_THROW_EXCEPTION(abort_exception());
    }
}

template<class String>
void
suite::
fail(String const& reason, char const* file, int line)
{
    fail(detail::make_reason(reason, file, line));
}

inline
void
suite::
propagate_abort()
{
    if(abort_ && aborted_)
        BOOST_THROW_EXCEPTION(abort_exception());
}

template<class>
void
suite::
run(runner& r)
{
    runner_ = &r;

    try
    {
        run();
    }
    catch(abort_exception const&)
    {
        // ends the suite
    }
    catch(std::exception const& e)
    {
        runner_->fail("unhandled exception: " +
            std::string(e.what()));
    }
    catch(...)
    {
        runner_->fail("unhandled exception");
    }
}

#ifndef BEAST_PASS
#define BEAST_PASS() ::boost::beast::unit_test::suite::this_suite()->pass()
#endif

#ifndef BEAST_FAIL
#define BEAST_FAIL() ::boost::beast::unit_test::suite::this_suite()->fail("", __FILE__, __LINE__)
#endif

#ifndef BEAST_EXPECT
/** Check a precondition.

    If the condition is false, the file and line number are reported.
*/
#define BEAST_EXPECT(cond) ::boost::beast::unit_test::suite::this_suite()->expect(cond, __FILE__, __LINE__)
#endif

#ifndef BEAST_EXPECTS
/** Check a precondition.

    If the condition is false, the file and line number are reported.
*/
#define BEAST_EXPECTS(cond, reason) ((cond) ? \
    (::boost::beast::unit_test::suite::this_suite()->pass(), true) : \
    (::boost::beast::unit_test::suite::this_suite()->fail((reason), __FILE__, __LINE__), false))
#endif

/** Ensure an exception is thrown
*/
#define BEAST_THROWS( EXPR, EXCEP ) \
    try { \
        EXPR; \
        BEAST_FAIL(); \
    } \
    catch(EXCEP const&) { \
        BEAST_PASS(); \
    } \
    catch(...) { \
        BEAST_FAIL(); \
    }

} // unit_test
} // beast
} // boost

//------------------------------------------------------------------------------

// detail:
// This inserts the suite with the given manual flag
#define BEAST_DEFINE_TESTSUITE_INSERT(Library,Module,Class,manual) \
    static ::boost::beast::unit_test::detail::insert_suite <Class##_test>   \
        Library ## Module ## Class ## _test_instance(             \
            #Class, #Module, #Library, manual)

//------------------------------------------------------------------------------

// Preprocessor directives for controlling unit test definitions.

// If this is already defined, don't redefine it. This allows
// programs to provide custom behavior for testsuite definitions
//
#ifndef BEAST_DEFINE_TESTSUITE

/** Enables insertion of test suites into the global container.
    The default is to insert all test suite definitions into the global
    container. If BEAST_DEFINE_TESTSUITE is user defined, this macro
    has no effect.
*/
#ifndef BEAST_NO_UNIT_TEST_INLINE
#define BEAST_NO_UNIT_TEST_INLINE 0
#endif

/** Define a unit test suite.

    Library   Identifies the library.
    Module    Identifies the module.
    Class     The type representing the class being tested.

    The declaration for the class implementing the test should be the same
    as Class ## _test. For example, if Class is aged_ordered_container, the
    test class must be declared as:

    @code

    struct aged_ordered_container_test : beast::unit_test::suite
    {
        //...
    };

    @endcode

    The macro invocation must appear in the same namespace as the test class.
*/

#if BEAST_NO_UNIT_TEST_INLINE
#define BEAST_DEFINE_TESTSUITE(Class,Module,Library)

#else
#include <boost/beast/_experimental/unit_test/global_suites.hpp>
#define BEAST_DEFINE_TESTSUITE(Library,Module,Class) \
        BEAST_DEFINE_TESTSUITE_INSERT(Library,Module,Class,false)
#define BEAST_DEFINE_TESTSUITE_MANUAL(Library,Module,Class) \
        BEAST_DEFINE_TESTSUITE_INSERT(Library,Module,Class,true)

#endif

#endif

//------------------------------------------------------------------------------

#endif

/* suite.hpp
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
*/